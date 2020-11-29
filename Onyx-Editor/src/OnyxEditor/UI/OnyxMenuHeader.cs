using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OnyxEditor
{
    public static class OnyxMenuHeader
    {

        public static string GetHeaderText()
        {
            if (!initialized)
                Init();

            OnyxCLR.SceneCLR scene = null;

            if (EngineCore.SceneEditor != null && EngineCore.SceneEditor.CurrentScene != null)
                scene = EngineCore.SceneEditor.CurrentScene;

            if (scene != null && scene.Indentifier.Length > 5)
                    return string.Format("Onyx Editor - {0} ({1}) - {2} Build {3}", scene.Name, scene.Indentifier, build, platform);
                else
                    return string.Format("Onyx Editor - {0} Build {1}", build, platform);
        }

        private static void Init()
        {
#if DEBUG
            build = "Debug";
#else
            build = "Release";
#endif
            if (IntPtr.Size == 4)
                platform = "x32";

            else
                platform = "x64";
        }

        private static string build = "";
        private static string platform = "";
        private static bool initialized = false;
    }
}
