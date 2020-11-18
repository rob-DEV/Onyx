using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OnyxEditor
{
    public class EngineInput
    {
        private volatile OnyxCLR.OnyxEditor m_Instance;

      
        public EngineInput(ref OnyxCLR.OnyxEditor instanceRef)
        {
            m_Instance = instanceRef;
        }


        public unsafe void Update()
        {
            m_Instance.UpdateEngineInput(Input.GetKeys(), Input.GetMouseButtons(), Input.GetMousePosition());
        }

    }
}
