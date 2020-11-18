using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OnyxEditor
{

    /// <summary>
    /// Purely static Onyx Engine binding for multiple thread use
    /// </summary>
    public partial class EngineCore
    {

        public static volatile OnyxCLR.EditorCoreCLR m_Instance = null;

        private static EngineInput m_EngineInput = null;
        
        private static EngineRenderer m_OnyxEngineRenderer = null;

        private static SceneEditor m_OynxSceneEditor = null;

        public static EngineRenderer Renderer { get { return m_OnyxEngineRenderer; } }

        public static SceneEditor SceneEditor { get { return m_OynxSceneEditor; } }

        internal static void Init()
        {
            if (m_Instance == null)
            {
                m_Instance = new OnyxCLR.EditorCoreCLR();
                m_EngineInput = new EngineInput(ref m_Instance);
                m_OnyxEngineRenderer = new EngineRenderer(ref m_Instance);
                m_OynxSceneEditor = new SceneEditor(ref m_Instance);
            }
        }

        internal unsafe static void UpdateEngine()
        {
            //CORE ONYX UPDATES
           
            //Update Onyx engine input
            m_EngineInput.Update();
            
            //Update Onyx engine state
            m_Instance.Update();

            //Poll rendered data
            m_OnyxEngineRenderer.Update();

            //SCENE EDITOR UPDATES
            m_OynxSceneEditor.Update();
        }
    }
}
