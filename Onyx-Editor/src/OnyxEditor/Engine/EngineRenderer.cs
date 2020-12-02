using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OnyxEditor
{
    public class EngineRenderer
    {
        private volatile OnyxCLR.EditorApplicationCLR m_Instance;

        private RendererSurface m_DirectBitmap = new RendererSurface(1130, 636);

        public RendererSurface RenderSurface { get { return m_DirectBitmap; } }

        internal EngineRenderer(ref OnyxCLR.EditorApplicationCLR instanceRef)
        {
            m_Instance = instanceRef;
        }


        internal unsafe void Update()
        {
            m_Instance.GetRenderedFrame(m_DirectBitmap.GetBitmapBuffer());
        }


    }
}
