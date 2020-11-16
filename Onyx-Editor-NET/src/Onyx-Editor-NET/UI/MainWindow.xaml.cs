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
using System.Windows.Media.Media3D;
using System.Windows.Threading;
using System.Timers;
using Microsoft.Win32;

namespace Onyx_Editor_NET
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Thread m_RenderThread;
        private volatile bool m_Aborted = false;

        private bool ViewPortInFocus = false;

        private void EngineThread()
        {
          
            Stopwatch sw = new Stopwatch();
            sw.Start();

            int frames = 0;

            OnyxEditor.Init();

            while (!m_Aborted)
            {

                OnyxEditor.UpdateEngine();
                OnyxEditor.UpdateEngineInput();

                ++frames;
                if (sw.ElapsedMilliseconds >= 1000)
                {
                    Console.WriteLine("Editor Thread FrameTime {0}", (float)frames);
                    frames = 0;
                    sw.Restart();
                }
            }
        }

      

        public MainWindow()
        {
            InitializeComponent();
        }

        private void MenuItem_New_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void MenuItem_Open_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Onyx Scene Files (*.osc) | *.osc| XML Files (*.xml)|*.xml";

            if(openFileDialog.ShowDialog() == true)
            {
                string filePath = openFileDialog.FileName;

                OnyxEditor.OpenScene(filePath);

            }
           
        }
        private void MenuItem_Save_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void MenuItem_Close_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }


        private void m_CreateEntityButton_Click(object sender, RoutedEventArgs e)
        {
            float x, y, z;
            x = (float)Convert.ToDecimal(PositionTextboxX.Text);
            y = (float)Convert.ToDecimal(PositionTextboxY.Text);
            z = (float)Convert.ToDecimal(PositionTextboxZ.Text);

        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            Input.ProcessKeyEvent(e.Key, true);

            //give user focus back to the window
            if(e.Key == Key.Escape)
            {
                ViewPortInFocus = false;
            }
        }
        private void Window_KeyUp(object sender, KeyEventArgs e)
        {
            Input.ProcessKeyEvent(e.Key, false);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            m_RenderThread = new Thread(new ThreadStart(EngineThread));
            m_RenderThread.Start();


           
        }

        private void Window_MouseMove(object sender, MouseEventArgs e)
        {

            Point viewportCenterPoint = ViewportMain.TransformToAncestor(Application.Current.MainWindow)
                .Transform(new Point(ViewportMain.Width / 2, ViewportMain.Height / 2));

            //set mouse position to viewport center

            if (ViewPortInFocus)
            {
                Point s = this.PointToScreen(viewportCenterPoint);
                System.Windows.Forms.Cursor.Position = new System.Drawing.Point((int)s.X, (int)s.Y);
            }

            Point pos = e.GetPosition(ViewportMain);

            Point mouseRelativeToVPCenter = new Point(pos.X - (1280 / 2), -(pos.Y - (720 / 2)));

            //add relative to 640 360
            float toEngineX = (float)(640 - mouseRelativeToVPCenter.X);
            float toEngineY = (float)(360 + mouseRelativeToVPCenter.Y);


            if(ViewPortInFocus)
                Input.ProcessMouseMove(new System.Drawing.Point((int)toEngineX, (int)toEngineY));
            else
                Input.ProcessMouseMove(new System.Drawing.Point(640, 360));

        }

        private void ViewportMain_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.MiddleButton == MouseButtonState.Pressed)
            {
                this.Cursor = Cursors.None;
                ViewPortInFocus = true;
            }
        }

        private void ViewportMain_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (e.MiddleButton == MouseButtonState.Released)
            {
                this.Cursor = Cursors.Arrow;
                ViewPortInFocus = false;
            }
        }

        private void Window_Closing(object sender, CancelEventArgs e)
        {
            ViewportMain.Dispose();
            m_Aborted = true;
        }

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            Input.ProcessMouseEvent(e);
        }

        private void Window_MouseUp(object sender, MouseButtonEventArgs e)
        {
            Input.ProcessMouseEvent(e);
        }

        
    }
}
