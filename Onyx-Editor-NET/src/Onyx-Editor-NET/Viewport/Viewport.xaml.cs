using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Onyx_Editor_NET
{
    /// <summary>
    /// Interaction logic for Viewport.xaml
    /// </summary>
    public partial class Viewport : UserControl, IDisposable
    {
        private Thread m_ViewportRenderThread;
        private bool m_ViewportThreadTerminated = false;

        private void ViewportRenderThread_Worker()
        {

            //Initialize the Engines Graphics context in viewport
            //As OpenGL / GLFW must only operate on one thread

            DirectBitmap b = new DirectBitmap(960, 540);

            Stopwatch sw = new Stopwatch();
            sw.Start();

            int frames = 0;

            while (true)
            {

                byte[] s = OnyxEditor.GetRenderedFramea();

                if (s == null)
                    continue;

                int pos = 0;
                for (int y = 539; y >= 0; y--)
                {
                    for (int x = 0; x < 960; x++)
                    {
                        b.SetPixel(x, y, System.Drawing.Color.FromArgb(255, s[pos], s[pos + 1], s[pos + 2]));
                        pos += 3;
                    }
                }

                var bitmapData = b.Bitmap.LockBits(
                new System.Drawing.Rectangle(0, 0, b.Bitmap.Width, b.Bitmap.Height),
                System.Drawing.Imaging.ImageLockMode.ReadOnly, b.Bitmap.PixelFormat);

                var bitmapSource = BitmapSource.Create(
                   bitmapData.Width, bitmapData.Height, 96, 96, PixelFormats.Bgra32, null,
                   bitmapData.Scan0, bitmapData.Stride * bitmapData.Height, bitmapData.Stride);

                b.Bitmap.UnlockBits(bitmapData);
                bitmapSource.Freeze();
                Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Render,
                    (Action)(() => { m_EngineFrame.Source = bitmapSource; }));

                ++frames;

                if (sw.ElapsedMilliseconds >= 1000)
                {
                    Console.WriteLine("Viewport FrameTime {0}", (float)frames);
                    frames = 0;
                    sw.Restart();
                }


            }
        }


        public Viewport()
        {
            InitializeComponent();
        }

        public void Dispose()
        {
            m_ViewportThreadTerminated = true;
        }

        private void ViewportUC_Loaded(object sender, RoutedEventArgs e)
        {
            m_ViewportRenderThread = new Thread(new ThreadStart(ViewportRenderThread_Worker));
            m_ViewportRenderThread.Start();
        }

        private void ViewportUC_Unloaded(object sender, RoutedEventArgs e)
        {
            m_ViewportThreadTerminated = true;
        }
    }
}
