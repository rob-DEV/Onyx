using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
using System.Threading;
using System.Diagnostics;
using Onyx_Editor_NET.Framebuffer;

namespace Onyx_Editor_NET
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Thread m_ViewportThread;

        private void EditorThread()
        {
            m_OnyxEditorCLR = new OnyxCLR.OnyxEditor();

            DirectBitmap b = new DirectBitmap(960, 540);

            Stopwatch sw = new Stopwatch();
            sw.Start();

            int frames = 0;

            while (true)
            {
                m_OnyxEditorCLR.Update();

                byte[] s = m_OnyxEditorCLR.GetRenderedFrame();



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
                Dispatcher.Invoke(() => m_Viewport.Source = bitmapSource);

                ++frames;

                if (sw.ElapsedMilliseconds >= 1000)
                {
                    Console.WriteLine("Viewport FrameTime {0}", (float)sw.ElapsedMilliseconds / (float)frames);
                    frames = 0;
                    sw.Restart();
                }



            }
        }

        public MainWindow()
        {
            InitializeComponent();

        }


        private OnyxCLR.OnyxEditor m_OnyxEditorCLR;

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            m_ViewportThread = new Thread(new ThreadStart(EditorThread));
            m_ViewportThread.Start();
        }

        void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            m_ViewportThread.Abort();
        }
    }
}
