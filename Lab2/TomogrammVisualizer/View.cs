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
    }
}
