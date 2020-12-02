using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace OnyxEditor
{

    /// <summary>
    /// Purely static Onyx Engine binding for multiple thread use
    /// </summary>
    public partial class EngineCore
    {

        public static void Start()
        {
            engineThread = new Thread(new ThreadStart(EngineThreadWorker));
            engineThread.Priority = ThreadPriority.Highest;
            engineThread.Start();
        }

        public static void Stop()
        {
            aborted = true;
            Thread.Sleep(200);
            engineThread.Abort();
        }

        public static volatile OnyxCLR.EditorApplicationCLR Instance = null;

        public static EngineRenderer Renderer { get; private set; } = null;

        public static SceneEditor SceneEditor { get; private set; } = null;

        public static IntPtr NativeEngineWindowPtr { get; private set; } = IntPtr.Zero;


        private static void EngineThreadWorker()
        {

            Stopwatch sw = new Stopwatch();
            sw.Start();

            int frames = 0;

            InitEngine();

            while (!aborted)
            {
                UpdateEngine();

                ++frames;
                if (sw.ElapsedMilliseconds >= 1000)
                {
                    Console.WriteLine("Editor Thread FrameTime {0}", (float)frames);
                    frames = 0;
                    sw.Restart();
                }
            }
        }

        private static void InitEngine()
        {
            if (Instance == null)
            {
                Instance = new OnyxCLR.EditorApplicationCLR();

                //Get engine window pointer
                NativeEngineWindowPtr = (IntPtr)Instance.GetNativeWindowHandle();
                Input = new EngineInput(ref Instance);
                Renderer = new EngineRenderer(ref Instance);
                SceneEditor = new SceneEditor(ref Instance);
            }
        }

        private unsafe static void UpdateEngine()
        {
            //CORE ONYX UPDATES
           
            //Update Onyx engine input
            //Input.Update();
            
            SceneEditor.Update();
            //Update Onyx engine state
            Instance.Update();
            

        }

        private static Thread engineThread;
        private static volatile bool aborted = false;
        private static EngineInput Input = null;

    }
}
