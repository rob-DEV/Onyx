using System;
using System.Diagnostics;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace OnyxEditor
{
    /// <summary>
    /// Interaction logic for Viewport.xaml
    /// </summary>
    public partial class Viewport : UserControl, IDisposable
    {
        private Thread m_ViewportRenderThread;
        private bool m_ViewportThreadTerminated = false;

        private unsafe void ViewportRenderThread_Worker()
        {
            while (EngineCore.Renderer == null);

            Stopwatch sw = new Stopwatch();
            sw.Start();

            System.Drawing.Rectangle renderTarget = new System.Drawing.Rectangle(0, 0, EngineCore.Renderer.RenderSurface.Bitmap.Width, EngineCore.Renderer.RenderSurface.Bitmap.Height);
            int frames = 0;

            while (!m_ViewportThreadTerminated)
            {
                while (EngineCore.Instance == null);

                var bitmapData = EngineCore.Renderer.RenderSurface.Bitmap.LockBits(renderTarget, System.Drawing.Imaging.ImageLockMode.ReadOnly, EngineCore.Renderer.RenderSurface.Bitmap.PixelFormat);

                var bitmapSource = BitmapSource.Create(
                    bitmapData.Width, bitmapData.Height, 96, 96, PixelFormats.Bgra32, null,
                    bitmapData.Scan0, bitmapData.Stride * bitmapData.Height, bitmapData.Stride);

                EngineCore.Renderer.RenderSurface.Bitmap.UnlockBits(bitmapData);

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

                Thread.Sleep((int)(1000.0f/60.0f));
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
