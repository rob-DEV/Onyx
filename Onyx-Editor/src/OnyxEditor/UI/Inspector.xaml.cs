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

using OnyxCLR;

namespace OnyxEditor
{
    /// <summary>
    /// Interaction logic for Inspector.xaml
    /// </summary>
    public partial class Inspector : UserControl
    {
        public Inspector()
        {
            InitializeComponent();
            TagIdentifier.Text = "NO TAG COMPONENT";
        }

        public void SetSelectedEntity(string sceneNodeGuid)
        {
            SelectedEntityGuid.Text = sceneNodeGuid;

            //Get Entity attached to SceneNode
            uint a = EngineCore.Instance.SceneEditorInstance.GetEntityFromSceneNode(sceneNodeGuid);
            InternalEntityID.Text = a.ToString();

            //Get all components which are possessed by the entity
            List<OnyxCLR.Component> components = EngineCore.Instance.SceneEditorInstance.GetEntityComponents(sceneNodeGuid);

            TagIdentifier.Text = "NO TAG COMPONENT";

            foreach(var component in components)
            {

                switch (component.Type)
                {

                    case ComponentType.TagComponent:
                        TagIdentifier.Text = ((TagComponent)component).Tag;
                        break;
                    case ComponentType.TransformComponent:
                        TransformX.Text = ((TransformComponent)component).Position.X.ToString("0.0000");
                        TransformY.Text = ((TransformComponent)component).Position.Y.ToString("0.0000");
                        TransformZ.Text = ((TransformComponent)component).Position.Z.ToString("0.0000");

                        RotationX.Text = ((TransformComponent)component).Rotation.X.ToString("0.0000");
                        RotationY.Text = ((TransformComponent)component).Rotation.Y.ToString("0.0000");
                        RotationZ.Text = ((TransformComponent)component).Rotation.Z.ToString("0.0000");

                        ScaleX.Text = ((TransformComponent)component).Scale.X.ToString("0.0000");
                        ScaleY.Text = ((TransformComponent)component).Scale.Y.ToString("0.0000");
                        ScaleZ.Text = ((TransformComponent)component).Scale.Z.ToString("0.0000");
                        break;
                    default:
                        Console.WriteLine("Inspector ERROR: {0}", "Invalid Component Type!");
                        break;
                }
            }
        }
    }
}
