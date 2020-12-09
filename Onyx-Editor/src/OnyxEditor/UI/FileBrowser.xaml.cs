using System;
using System.Collections.Generic;
using System.Diagnostics;
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
using System.Windows.Threading;

namespace OnyxEditor
{
    /// <summary>
    /// Interaction logic for FileBrowser.xaml
    /// </summary>
    public partial class FileBrowser : UserControl
    {
        public FileBrowser()
        {
            InitializeComponent();
            BuildAssetBrowser();
        }

        private void BuildAssetBrowser()
        {
            string basePath = "res/";

            foreach (string s in System.IO.Directory.GetLogicalDrives())
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
                catch (Exception ex)
                {

                }
            }
        }


        private void FolderExpanded(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = (TreeViewItem)sender;

            AssetTag tag = (AssetTag)item.Tag;


            if (tag.Type != AssetType.DRIVE)
            {
                AssetType type;

                if (item.IsExpanded)
                    type = AssetType.FOLDER_EXPANDED;
                else
                    type = AssetType.FOLDER;

                //update element accordingly
                //Already searched recursively, just set tag
                item.Tag = new AssetTag(type, ((AssetTag)item.Tag).Path);
                ((UIElement)item).Dispatcher.Invoke(new Action(() => { }), DispatcherPriority.Render);
            }

            if (item.Items.Count == 1 && item.Items[0] == null)
            {
                item.Items.Clear();

                try
                {
                    foreach (string s in System.IO.Directory.GetDirectories(tag.Path))
                    {
                        //Folder (sub-directories)
                        TreeViewItem subItem = new TreeViewItem();
                        subItem.Header = s.Substring(s.LastIndexOf("\\") + 1);
                        subItem.Tag = new AssetTag(AssetType.FOLDER, s);
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

                        //Add handler for opening files
                        subItem.MouseDoubleClick += SubItem_MouseDoubleClick;

                    }

                }
                catch (Exception ex)
                {

                }
            }

        }

        private void SubItem_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            TreeViewItem item = (TreeViewItem)sender;
            AssetTag tag = (AssetTag)item.Tag;

            if (System.IO.File.Exists(tag.Path))
            {
                Process fileopener = new Process();
                fileopener.StartInfo.FileName = "explorer";
                fileopener.StartInfo.Arguments = "\"" + tag.Path + "\"";
                fileopener.Start();
            }

        }


        private void FolderCollapsed(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = (TreeViewItem)sender;

            AssetTag tag = (AssetTag)item.Tag;

            if (tag.Type != AssetType.DRIVE)
            {
                AssetType type;

                if (item.IsExpanded)
                    type = AssetType.FOLDER_EXPANDED;
                else
                    type = AssetType.FOLDER;

                //update element accordingly
                //Already searched recursively, just set tag
                item.Tag = new AssetTag(type, ((AssetTag)item.Tag).Path);
                ((UIElement)item).Dispatcher.Invoke(new Action(() => { }), DispatcherPriority.Render);
            }
        }


    }
}
