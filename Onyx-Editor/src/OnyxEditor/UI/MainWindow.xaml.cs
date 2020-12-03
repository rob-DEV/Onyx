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

        public MainWindow()
        {
            InitializeComponent();
            this.Title = OnyxMenuHeader.GetHeaderText();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            EngineCore.Start();

            //set onyx window
            while(EngineCore.NativeEngineWindowPtr == IntPtr.Zero) { }

            IntPtr ptr = EngineCore.NativeEngineWindowPtr;
            if (ptr.ToInt32() != 0)
            {
                Point windowAnchorPosition = EmbededWindow.TransformToAncestor(Application.Current.MainWindow).Transform(new Point(0, 0));

                EmbededWindow.SetWindowAndUpdate(ptr, windowAnchorPosition);
            }

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
            this.Close();
        }


        private void Window_Closing(object sender, CancelEventArgs e)
        {
            EngineCore.Stop();
            EmbededWindow.Dispose();
        }

    }
}