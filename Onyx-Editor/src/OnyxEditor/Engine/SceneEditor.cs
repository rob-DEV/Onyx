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
        public void OpenScene(string filePath)
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

        public bool IsSceneUpdateRequired { get { return m_SceneUpdateRequired; } set { m_SceneUpdateRequired = value; } }
        public string CurrentScenePath { get { return m_ScenePath; } }

        private bool m_SceneUpdateRequired = false;

        private string m_ScenePath = "";
    }

}
