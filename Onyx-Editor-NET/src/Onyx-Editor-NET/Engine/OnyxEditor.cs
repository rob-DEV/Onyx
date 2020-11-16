using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Onyx_Editor_NET
{

    /// <summary>
    /// Purely static Onyx Engine binding for multiple thread use
    /// </summary>
    public static class OnyxEditor
    {
        public static volatile OnyxCLR.OnyxEditor m_Instance = null;

        public static DirectBitmap DirectBitmap = new DirectBitmap(1280, 720);

        public static string OpenedScene = "";

        public static bool NeedsToOpenScene = false;

        public static void Init()
        {
            if (m_Instance == null)
                m_Instance = new OnyxCLR.OnyxEditor();
        }

        public unsafe static void UpdateEngine()
        {
            //open scene test
            if (NeedsToOpenScene) {
                m_Instance.OpenScene(OpenedScene);
                NeedsToOpenScene = false;
            }



            m_Instance.Update();
            m_Instance.GetRenderedFrame(DirectBitmap.GetBitmapBuffer());
        }

        public static void UpdateEngineInput()
        {
            if (m_Instance != null)
                m_Instance.UpdateEngineInput(Input.GetKeys(), Input.GetMouseButtons(), Input.GetMousePosition());
        }

        internal static void OpenScene(string filePath)
        {
            OpenedScene = filePath;
            NeedsToOpenScene = true;

        }
    }
}
