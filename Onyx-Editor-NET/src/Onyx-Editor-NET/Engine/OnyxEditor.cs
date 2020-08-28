using System;
using System.Collections.Generic;
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

        public static Queue<byte[]> SwapChain = new Queue<byte[]>();

        public static void Init()
        {
            if (m_Instance == null)
                m_Instance = new OnyxCLR.OnyxEditor();
        }


        public static byte[] GetRenderedFramea()
        {
            if (m_Instance == null)
                return null;

            if(SwapChain.Count > 0)
                return SwapChain.Dequeue();
            else
                return null;
        }


        public static void UpdateEngine()
        {
            m_Instance.Update();
            SwapChain.Enqueue(m_Instance.GetRenderedFrame());
        }

        public static void UpdateEngineInput()
        {
            if (m_Instance != null)
                m_Instance.UpdateEngineInput(Input.GetKeys(), Input.GetMousePosition());
        }
    }
}
