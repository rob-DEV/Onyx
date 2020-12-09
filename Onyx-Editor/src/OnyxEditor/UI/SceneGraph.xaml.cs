using System;
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

namespace OnyxEditor
{
    /// <summary>
    /// Interaction logic for SceneGraph.xaml
    /// </summary>
    public partial class SceneGraph : UserControl
    {
        public event SceneGraphSelectionChangedHandler SelectionChanged;

        public SceneGraph()
        {
            InitializeComponent();
            SceneTreeview.SelectedItemChanged += SceneTreeview_SelectedItemChanged;
        }

        private void SceneTreeview_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            TreeViewItem item = (TreeViewItem)SceneTreeview.SelectedItem;

            if (item != null)
            {
                SceneGraphSelectionArgs args = new SceneGraphSelectionArgs(item.Tag.ToString());
                SelectionChanged(args);
            }
        }
        public void UpdateSceneGraph()
        {
            SceneTreeview.Items.Clear();

            SceneNodeCLR sceneGraph = EngineCore.Instance.SceneEditorInstance.GetSceneGraphCLRTest();

            IterateSceneGraph(sceneGraph, null);
        }



        private void IterateSceneGraph(SceneNodeCLR node, TreeViewItem position)
        {
            TreeViewItem insertedItem = null;

            //Add Scene Node (The global scene node)
            if (position == null)
            {
                TreeViewItem sceneNode = new TreeViewItem();
                sceneNode.Header = node.Name;
                sceneNode.Tag = node.UUID;
                int sceneNodeIndex = SceneTreeview.Items.Add(sceneNode);

                insertedItem = (TreeViewItem)SceneTreeview.Items[sceneNodeIndex];
            }
            else
            {
                TreeViewItem subItem = new TreeViewItem();
                subItem.Header = node.Name;
                subItem.Tag = node.UUID;
                int index = position.Items.Add(subItem);

                insertedItem = (TreeViewItem)position.Items[index];
            }

            foreach (SceneNodeCLR subNode in node.Nodes)
            {
                IterateSceneGraph(subNode, insertedItem);
            }

        }
    }
}
