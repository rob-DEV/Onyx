using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows;

namespace OnyxEditor
{
    public enum SceneEditorCommandType
    {
        NO_COMMAND,
        OPEN_SCENE,
        SAVE_SCENE,
        NEW_SCENE
    }

    public class SceneCommand
    {
        public SceneEditorCommandType CommandType;
        public String ScenePath;
        public bool Executed = true;
    }

    public class SceneEditor
    {
        private volatile OnyxCLR.EditorApplicationCLR instance;

        private SceneCommand sceneCommand = new SceneCommand();

        public SceneEditor(ref OnyxCLR.EditorApplicationCLR instance)
        {
            this.instance = instance;
        }

        internal void OpenScene(string filePath)
        {
            if (File.Exists(filePath))
            {
                sceneCommand.CommandType = SceneEditorCommandType.OPEN_SCENE;
                sceneCommand.ScenePath = filePath;
                sceneCommand.Executed = false;
            }
        }

        internal void NewScene()
        {
            sceneCommand.CommandType = SceneEditorCommandType.NEW_SCENE;
            sceneCommand.ScenePath = "";
            sceneCommand.Executed = false;
        }
        internal void SaveScene()
        {
            sceneCommand.CommandType = SceneEditorCommandType.SAVE_SCENE;
            sceneCommand.ScenePath = "";
            sceneCommand.Executed = false;
        }

        internal void SaveScene(string path)
        {
            sceneCommand.CommandType = SceneEditorCommandType.SAVE_SCENE;
            sceneCommand.ScenePath = path;
            sceneCommand.Executed = false;
        }

        public List<OnyxCLR.Entity> GetAllEntities()
        { 
            return instance.SceneEditorInstance.GetAllEntitiesTest();
        }

        internal void Update()
        {
            bool updateUI = false;
            if(!sceneCommand.Executed)
            {
                switch(sceneCommand.CommandType)
                {
                    case SceneEditorCommandType.NO_COMMAND:
                        break;
                    case SceneEditorCommandType.NEW_SCENE:
                        currentScene = instance.SceneEditorInstance.NewScene();
                        updateUI = true;
                        break;
                    case SceneEditorCommandType.OPEN_SCENE:
                        currentScene = instance.SceneEditorInstance.OpenScene(sceneCommand.ScenePath);
                        updateUI = true;
                        break;
                    case SceneEditorCommandType.SAVE_SCENE:
                        instance.SceneEditorInstance.SaveScene(sceneCommand.ScenePath);
                        updateUI = true;
                        break;
                    default:
                        Console.WriteLine("WARN: Invalid SceneCommandType");
                        break;

                }

                sceneCommand.Executed = true;
            }

            if(updateUI)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    foreach (Window window in Application.Current.Windows)
                    {
                        if (window.GetType() == typeof(MainWindow))
                        {
                            window.Title = OnyxMenuHeader.GetHeaderText();
                            //update scene graph
                            ((MainWindow)window).SceneGraph.UpdateSceneGraph();
                        }
                    }
                });
            }

        }

        public OnyxCLR.SceneCLR CurrentScene { get { return currentScene; } }


        private OnyxCLR.SceneCLR currentScene = new OnyxCLR.SceneCLR();


    }

}
