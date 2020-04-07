using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TomogrammVisualizer
{
    public partial class Form1 : Form
    {
        public Bin bin;
        public View view;
        public int currentLayer;
        public bool loaded;
        public bool needReload;
        
        int FrameCount;
        DateTime NextFPSUpdate;

        public Form1()
        {
            InitializeComponent();
            bin = new Bin();
            view = new View();
            loaded = false;
            needReload = false;
            currentLayer = 0;
            trackBar1.Hide();
            FrameCount = 0;
            NextFPSUpdate = DateTime.Now.AddSeconds(1);
            checkQuads.Checked = true;
            checkQuads.Hide();
            checkTexture.Checked = false;
            checkTexture.Hide();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                string path = dialog.FileName;
                bin.ReadBin(path);
                view.SetupView(glControl1.Width, glControl1.Height);
                loaded = true;
                glControl1.Invalidate();
                trackBar1.Maximum = Bin.Z - 1;
                trackBar1.Show();
                checkQuads.Show();
                checkTexture.Show();
            }
        }

        private void glControl1_Paint(object sender, PaintEventArgs e)
        {
            if (loaded)
            {
                if (checkQuads.Checked)
                    view.DrawQuads(currentLayer);

                if (checkTexture.Checked)
                {
                    if (needReload)
                    {
                        view.GenerateTextureImage(currentLayer);
                        view.Load2dTexture();
                        needReload = false;
                    }

                    view.DrawTexture();
                }

                glControl1.SwapBuffers();
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            currentLayer = trackBar1.Value;
            needReload = true;
            glControl1.Invalidate();
        }

        private void Application_Idle(object sender, EventArgs e)
        {
            while (glControl1.IsIdle)
            {
                DisplayFPS();
                glControl1.Invalidate();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Application.Idle += Application_Idle;
        }

        private void DisplayFPS()
        {
            if (DateTime.Now > NextFPSUpdate)
            {
                label1.Text = String.Format("FPS {0}", FrameCount);
                NextFPSUpdate = DateTime.Now.AddSeconds(1);
                FrameCount = 0;
            }

            FrameCount++;
        }
    }
}
