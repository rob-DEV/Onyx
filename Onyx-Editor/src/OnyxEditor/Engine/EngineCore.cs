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

        public static volatile OnyxCLR.EditorApplicationCLR Instance = null;

        private static EngineInput m_EngineInput = null;

        public static EngineRenderer Renderer { get; private set; } = null;

        public static SceneEditor SceneEditor { get; private set; } = null;

        internal static void Init()
        {
            if (Instance == null)
            {
                Instance = new OnyxCLR.EditorApplicationCLR();
                m_EngineInput = new EngineInput(ref Instance);
                Renderer = new EngineRenderer(ref Instance);
                SceneEditor = new SceneEditor(ref Instance);
            }
        }

        internal unsafe static void UpdateEngine()
        {
            //CORE ONYX UPDATES
           
            //Update Onyx engine input
            m_EngineInput.Update();
            
            //Update Onyx engine state
            Instance.Update();

            //Poll rendered data
            Renderer.Update();

            //SCENE EDITOR UPDATES
            SceneEditor.Update();
        }
    }
}
