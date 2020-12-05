using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;
using System.Threading;
using System.Diagnostics;
using Microsoft.Win32;
using System.Windows.Controls;
using System.Windows.Data;
using System.Globalization;
using System.Windows.Threading;

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

            //set onyx window
            while(EngineCore.NativeEngineWindowPtr == IntPtr.Zero) { }

            IntPtr ptr = EngineCore.NativeEngineWindowPtr;
            if (ptr.ToInt32() != 0)
            {
                Point windowAnchorPosition = EmbededWindow.TransformToAncestor(Application.Current.MainWindow).Transform(new Point(0, 0));

                EmbededWindow.SetWindowAndUpdate(ptr, windowAnchorPosition);
            }

            BuildAssetBrowser();
        }

        private void BuildAssetBrowser()
        {
            string basePath = "res/";

            foreach(string s in System.IO.Directory.GetLogicalDrives())
            {
                try
                {
                    //Only list drives that are plugged
                    //This throws an Exceptions which skips unplugged drives
                    System.IO.Directory.GetDirectories(s);
                    TreeViewItem item = new TreeViewItem();
                    item.Header = s;
                    item.Tag = new AssetTag(AssetType.DRIVE, s);
                    item.FontWeight = FontWeights.Normal;
                    item.Items.Add(null);
                    item.Expanded += new RoutedEventHandler(FolderExpanded);
                    AssetBrowser.Items.Add(item);
                }
                catch(Exception ex)
                {

                }
            }
        }

        private void FolderExpanded(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = (TreeViewItem)sender;

            AssetTag tag = (AssetTag)item.Tag;

            if(item.Items.Count == 1 && item.Items[0] == null)
            {
                item.Items.Clear();

                try
                {
                    foreach (string s in System.IO.Directory.GetDirectories(tag.Path))
                    {
                        //Folder (sub-directories)
                        TreeViewItem subItem = new TreeViewItem();
                        subItem.Header = s.Substring(s.LastIndexOf("\\") + 1);
                        subItem.Tag = new AssetTag(AssetType.FOLDER_EXPANDED, s);
                        subItem.Items.Add(null);
                        subItem.Expanded += new RoutedEventHandler(FolderExpanded);
                        subItem.Collapsed += new RoutedEventHandler(FolderCollapsed);
                        item.Items.Add(subItem);

                    }


                    foreach (string s in System.IO.Directory.GetFiles(tag.Path))
                    {
                        //Files cannot be nested
                        TreeViewItem subItem = new TreeViewItem();
                        subItem.Header = s.Substring(s.LastIndexOf("\\") + 1);
                        subItem.Tag = new AssetTag(AssetType.FILE, s);
                        item.Items.Add(subItem);
                    }
                    
                }
                catch (Exception ex)
                {

                }
            }else
            {
               if(tag.Type != AssetType.DRIVE)
                {
                    //Already searched recursively, just set tag
                    item.Tag = new AssetTag(AssetType.FOLDER_EXPANDED, ((AssetTag)item.Tag).Path);
                    //update element accordingly
                    ((UIElement)item).Dispatcher.Invoke(new Action(() => { }), DispatcherPriority.Render);
                }
            }

        }


        private void FolderCollapsed(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = (TreeViewItem)sender;

            item.Tag = new AssetTag(AssetType.FOLDER, ((AssetTag)item.Tag).Path);

            //update element accordingly
            ((UIElement)item).Dispatcher.Invoke(new Action(() => { }), DispatcherPriority.Render);
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