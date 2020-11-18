using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OnyxEditor
{
    public class EngineInput
    {
        private volatile OnyxCLR.EditorCoreCLR m_Instance;


        internal EngineInput(ref OnyxCLR.EditorCoreCLR instanceRef)
        {
            m_Instance = instanceRef;
        }


        internal unsafe void Update()
        {
            m_Instance.UpdateEngineInput(Input.GetKeys(), Input.GetMouseButtons(), Input.GetMousePosition());
        }

    }
}
