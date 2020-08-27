using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Onyx_Editor_NET
{
    /// <summary>
    /// Data structure containing viewport input to be sent to and 
    /// processed by the engine
    /// </summary>
    public class Input
    {
        static bool[] Keys = new bool[Keycodes.ONYX_KEYCODE_COUNT];
        float MouseX = 0.0f;
        float MouseY = 0.0f;

        /// <summary>
        /// Process a Windows Key and Convert to Onyx Key-code
        /// </summary>
        /// <param name="key"></param>
        public static void ProcessKeyEvent(Key key)
        {
            if (key == Key.W)
                Keys[Keycodes.ONYX_KEY_W] = true;
            if (key == Key.A)
                Keys[Keycodes.ONYX_KEY_A] = true;
            if (key == Key.S)
                Keys[Keycodes.ONYX_KEY_S] = true;
            if (key == Key.D)
                Keys[Keycodes.ONYX_KEY_D] = true;
        }

        public static void Reset()
        {
            for (int i = 0; i < Keys.Length; i++)
            {
                Keys[i] = false;
            }
        }

        public static bool[] GetKeys()
        {

            return Keys;
        }

    }
}
