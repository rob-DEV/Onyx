using System;
using System.ComponentModel;
using System.Windows;
using Microsoft.Win32;
using System.Windows.Data;
using System.Globalization;
using System.Collections.Generic;

namespace OnyxEditor
{
    public enum AssetType
    {
        DRIVE,
        FOLDER,
        FOLDER_EXPANDED,
        FILE
    }
    public class AssetTag {
        public AssetType Type;
        public string Path;

        public AssetTag(AssetType type, string path)
        {
            this.Type = type;
            this.Path = path;
        }
    }

    public class AssetTagToIconPathConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            AssetTag tag = (AssetTag)value;

            switch(tag.Type)
            {
                case AssetType.DRIVE:
                    return "pack://application:,,,/res/images/icons/hard_drive.png";
                case AssetType.FOLDER:
                    return "pack://application:,,,/res/images/icons/folder.png";
                case AssetType.FOLDER_EXPANDED:
                    return "pack://application:,,,/res/images/icons/folder_open.png";
                case AssetType.FILE:
                    return "pack://application:,,,/res/images/icons/file.png";

            }

            //default
            return "pack://application:,,,/res/images/icons/folder.png";

        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return "";
        }
    }

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
            InitializeUIComponents();
        }

        private void InitializeUIComponents()
        {
            //Halt until the window HWND is available
            while (EngineCore.NativeEngineWindowPtr == IntPtr.Zero) { }

            Point windowAnchorPosition = EmbededWindow.TransformToAncestor(Application.Current.MainWindow).Transform(new Point(0, 0));

            EmbededWindow.Initialize(EngineCore.NativeEngineWindowPtr, windowAnchorPosition);

            SceneGraph.SelectionChanged += SceneGraph_SelectionChanged;
        }

        private void SceneGraph_SelectionChanged(SceneGraphSelectionArgs e)
        {
            Inspector.SetSelectedEntity(e.SelectedGuid);
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