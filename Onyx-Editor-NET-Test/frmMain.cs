using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using OnyxCLR;

using System.Runtime.InteropServices;



namespace Onyx_Editor_NET_Test
{
    public partial class frmMain : Form
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();

        private OnyxCLR.OnyxEditor m_EditorInstance;
        private Thread m_ViewportThread;

        private void EditorThread()
        {
            m_EditorInstance = new OnyxEditor();

            DirectBitmap b = new DirectBitmap(960, 540);
     
            while (true)
            {

                m_EditorInstance.Update();

                //Bitmap test = m_EditorInstance.GetRenderedFrame();
                byte[] s = m_EditorInstance.GetRenderedFrame();

                

                int pos = 0;
                for (int y = 539; y >= 0; y--)
                {
                    for (int x = 0; x < 960; x++)
                    {
                        b.SetPixel(x, y, Color.FromArgb(255, s[pos], s[pos + 1], s[pos + 2]));
                        pos += 3;
                    }
                    //    pos += offset;  
                }

                
                //set Viewport image in UI thread
                m_Viewport.Invoke(new MethodInvoker(delegate ()
                {

                    m_Viewport.Image = b.Bitmap;

                    //m_Viewport.SizeMode = PictureBoxSizeMode.Zoom;
                }));


            }
        }

        public frmMain()
        {
            InitializeComponent();
         
            m_ViewportThread = new Thread(new ThreadStart(EditorThread));
            
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            m_ViewportThread.Start();
            AllocConsole();
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            m_ViewportThread.Abort();
        }

        private void frmMain_Resize(object sender, EventArgs e)
        {
            m_Viewport.Size = new Size(m_Viewport.Size.Width, (int)(m_Viewport.Size.Width / 1.777777f));
        }
    }
}
