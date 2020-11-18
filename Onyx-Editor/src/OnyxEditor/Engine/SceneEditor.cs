using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace OnyxEditor
{

    public class SceneEditor
    {
        private volatile OnyxCLR.EditorCoreCLR m_Instance;

        public SceneEditor(ref OnyxCLR.EditorCoreCLR instance)
        {
            m_Instance = instance;
        }

        internal void OpenScene(string filePath)
        {
            if (File.Exists(filePath))
            {
                m_SceneUpdateRequired = true;
                m_ScenePath = filePath;
            }
            else
            {
                //TODO: handle
            }
        }

        public List<OnyxCLR.Entity> GetAllEntities()
        {
            List<OnyxCLR.Entity> e = m_Instance.SceneEditorInstance.GetAllEntitiesTest();

            return e;
        }

        internal void Update()
        {
            if(m_SceneUpdateRequired)
            {
                m_Instance.SceneEditorInstance.OpenScene(m_ScenePath);
                m_SceneUpdateRequired = false;
            } 
        }

        public string CurrentScenePath { get { return m_ScenePath; } }

        private bool m_SceneUpdateRequired = false;

        private string m_ScenePath = "";

        
    }

}
