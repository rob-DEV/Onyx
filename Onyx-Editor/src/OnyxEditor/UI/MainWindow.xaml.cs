using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;
using System.Threading;
using System.Diagnostics;
using Microsoft.Win32;
using System.Windows.Controls;

namespace OnyxEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool ViewPortInFocus = false;

        private double ViewportWidth = 1130;
        private double ViewportHeight = 1130 / 1.7777777;

        public MainWindow()
        {
            InitializeComponent();
            this.Title = OnyxMenuHeader.GetHeaderText();
            UpdateUI();
        }

        private void UpdateUI()
        {
            //Set viewport size proportional to the window in 16:9 proportion
            double windowWidth = this.Width;

            double windowSlack = 1920 - windowWidth;
            double viewportWidth = 1130 - windowSlack;

            EditorGrid.ColumnDefinitions[1].Width = new GridLength(viewportWidth);

            EditorGrid.RowDefinitions[2].Height = new GridLength(viewportWidth / 1.77777777);

            ViewportWidth = viewportWidth;
            ViewportHeight = viewportWidth / 1.77777777;

        }
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            EngineCore.Start();
        }

        private void MenuItem_New_Click(object sender, RoutedEventArgs e)
        {
            if (EngineCore.SceneEditor.CurrentScene.FilePath != "")
            {
                MessageBoxResult mbResult = MessageBox.Show("Do you want to save changes to this Scene?", "Onyx Editor", MessageBoxButton.YesNoCancel);

                if (mbResult == MessageBoxResult.Yes)
                {
                    EngineCore.SceneEditor.SaveScene();
                    EngineCore.SceneEditor.NewScene();
                }
                else if (mbResult == MessageBoxResult.No)
                {
                    EngineCore.SceneEditor.NewScene();
                }
            }
        }

        private void MenuItem_Open_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Onyx Scene Files (*.osc) | *.osc| XML Files (*.xml)|*.xml";

            if (openFileDialog.ShowDialog() == true)
            {
                string filePath = openFileDialog.FileName;
                EngineCore.SceneEditor.OpenScene(filePath);
            }
        }

        private void MenuItem_Save_Click(object sender, RoutedEventArgs e)
        {
            EngineCore.SceneEditor.SaveScene();
        }

        private void MenuItem_SaveAs_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Onyx Scene Files (*.osc) | *.osc| XML Files (*.xml)|*.xml";

            if (saveFileDialog.ShowDialog() == true)
            {
                string filePath = saveFileDialog.FileName;
                EngineCore.SceneEditor.SaveScene(filePath);
            }
        }

        private void MenuItem_Close_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (ViewPortInFocus)
                Input.ProcessKeyEvent(e.Key, true);
        }
        private void Window_KeyUp(object sender, KeyEventArgs e)
        {
            Input.ProcessKeyEvent(e.Key, false);
        }

        private void Window_MouseMove(object sender, MouseEventArgs e)
        {
            Point viewportCenterPoint = ViewportMain.TransformToAncestor(Application.Current.MainWindow)
                .Transform(new Point(ViewportWidth / 2, ViewportHeight / 2));

            if (e.MiddleButton == MouseButtonState.Pressed)
            {
                Point s = this.PointToScreen(viewportCenterPoint);
                System.Windows.Forms.Cursor.Position = new System.Drawing.Point((int)s.X, (int)s.Y);
                this.Cursor = Cursors.None;
            }
            else
            {
                this.Cursor = Cursors.Arrow;
            }

            Point pos = e.GetPosition(ViewportMain);

            Point mouseViewportPos = new Point((ViewportWidth - pos.X) - (ViewportWidth / 2), -((ViewportHeight - pos.Y) - (ViewportHeight / 2)));

            float toEngineX = (float)((ViewportWidth / 2) - mouseViewportPos.X);
            float toEngineY = (float)((ViewportHeight / 2) + mouseViewportPos.Y);

            if (toEngineX >= 0 && toEngineX <= ViewportWidth && toEngineY >= 0 && toEngineY <= ViewportHeight)
            {
                ViewPortInFocus = true;
            }
            else
            {
                ViewPortInFocus = false;
            }

            Input.ProcessMouseMove(new System.Drawing.Point((int)toEngineX, (int)toEngineY));
        }

        private void Window_Closing(object sender, CancelEventArgs e)
        {
            ViewportMain.Dispose();
            EngineCore.Stop();
        }

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            Point viewportCenterPoint = ViewportMain.TransformToAncestor(Application.Current.MainWindow)
                .Transform(new Point(ViewportWidth / 2, ViewportHeight / 2));

            //set mouse position to viewport center

            if (e.MiddleButton == MouseButtonState.Pressed)
            {
                Point s = this.PointToScreen(viewportCenterPoint);
                System.Windows.Forms.Cursor.Position = new System.Drawing.Point((int)s.X, (int)s.Y);
                this.Cursor = Cursors.None;
            }
            else
            {
                this.Cursor = Cursors.Arrow;
            }

            if (ViewPortInFocus)
                Input.ProcessMouseEvent(e);
        }

        private void Window_MouseUp(object sender, MouseButtonEventArgs e)
        {
            Input.ProcessMouseEvent(e);
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            UpdateUI();
        }

        private void Window_StateChanged(object sender, EventArgs e)
        {
            UpdateUI();
        }
    }
}