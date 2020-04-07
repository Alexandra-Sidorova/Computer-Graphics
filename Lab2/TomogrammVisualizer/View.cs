using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;

using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace TomogrammVisualizer
{
    public class View
    {
        int VBOtexture;
        Bitmap textureImage;

        public void SetupView(int width, int height)
        {
            GL.ShadeModel(ShadingModel.Smooth);
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(0, Bin.X, 0, Bin.Y, -1, 1);
            GL.Viewport(0, 0, width, height);
        }
        protected int Clamp(int Val, int Min, int Max)
        {
            if (Val > Max)
                return Max;
            else if (Val < Min)
                return Min;
            else
                return Val;
        }

        protected Color TransferFunction(short value)
        {
            int min = 0;
            int max = 2000;
            int newVal = Clamp((value - min) * 255 / (max - min), 0, 255);
            return Color.FromArgb(255, newVal, newVal, newVal);
        }

        public void DrawQuads(int layerNumber)
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.Begin(BeginMode.Quads);
            for(int xCoord = 0; xCoord < Bin.X - 1; xCoord++)
                for(int yCoord = 0; yCoord < Bin.Y - 1; yCoord++)
                {
                    short value;

                    value = Bin.array[xCoord + yCoord * Bin.X + layerNumber * Bin.X * Bin.Y];
                    GL.Color3(TransferFunction(value));
                    GL.Vertex2(xCoord, yCoord);

                    value = Bin.array[xCoord + (yCoord + 1) * Bin.X + layerNumber * Bin.X * Bin.Y];
                    GL.Color3(TransferFunction(value));
                    GL.Vertex2(xCoord, yCoord + 1);

                    value = Bin.array[(xCoord + 1)+ (yCoord + 1) * Bin.X + layerNumber * Bin.X * Bin.Y];
                    GL.Color3(TransferFunction(value));
                    GL.Vertex2(xCoord + 1, yCoord + 1);

                    value = Bin.array[(xCoord + 1) + yCoord * Bin.X + layerNumber * Bin.X * Bin.Y];
                    GL.Color3(TransferFunction(value));
                    GL.Vertex2(xCoord + 1, yCoord);
                }

            GL.End();
        }

        public void Load2dTexture()
        {
            GL.BindTexture(TextureTarget.Texture2D, VBOtexture);
            BitmapData data = textureImage.LockBits(
                new Rectangle(0, 0, textureImage.Width, textureImage.Height),
                ImageLockMode.ReadOnly,
                System.Drawing.Imaging.PixelFormat.Format32bppArgb);

            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba,
                data.Width, data.Height, 0, OpenTK.Graphics.OpenGL.PixelFormat.Bgra,
                PixelType.UnsignedByte, data.Scan0);

            textureImage.UnlockBits(data);

            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter,
                (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter,
                (int)TextureMinFilter.Linear);

            ErrorCode error = GL.GetError();
            string str = error.ToString();
        }

        public void GenerateTextureImage(int layerNumber)
        {
            textureImage = new Bitmap(Bin.X, Bin.Y);
            
            for(int i = 0; i < Bin.X; i++)
                for(int j = 0; j < Bin.Y; j++)
                {
                    int pixelNumber = i + j * Bin.X + layerNumber * Bin.X * Bin.Y;
                    textureImage.SetPixel(i, j, TransferFunction(Bin.array[pixelNumber]));
                }
        }

        public void DrawTexture()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.Enable(EnableCap.Texture2D);
            GL.BindTexture(TextureTarget.Texture2D, VBOtexture);

            GL.Begin(BeginMode.Quads);
            GL.Color3(Color.White);
            GL.TexCoord2(0f, 0f);  
            GL.Vertex2(0, 0);            
            GL.TexCoord2(0f, 1f);
            GL.Vertex2(0, Bin.Y);        
            GL.TexCoord2(1f, 1f);
            GL.Vertex2(Bin.X, Bin.Y);           
            GL.TexCoord2(1f, 0f);
            GL.Vertex2(Bin.X, 0);      
            GL.End();

            GL.Disable(EnableCap.Texture2D);
        }
    }
}
