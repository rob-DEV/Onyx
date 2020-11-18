using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OnyxEditor
{
    public class EngineRenderer
    {
        private volatile OnyxCLR.OnyxEditor m_Instance;

        private RendererSurface m_DirectBitmap = new RendererSurface(1280, 720);

        public RendererSurface RenderSurface { get { return m_DirectBitmap; } }

        public EngineRenderer(ref OnyxCLR.OnyxEditor instanceRef)
        {
            m_Instance = instanceRef;
        }


        public unsafe void Update()
        {
            m_Instance.GetRenderedFrame(m_DirectBitmap.GetBitmapBuffer());
        }


    }
}
