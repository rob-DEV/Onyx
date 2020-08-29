using System;
using System.Collections.Generic;
using System.Drawing;
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


        private static bool[] Keys = new bool[Keycodes.ONYX_KEYCODE_COUNT];
        private static Point MousePosition = new Point(640,360);



        /// <summary>
        /// Process a windows key event and convert to Onyx key-code
        /// </summary>
        /// <param name="key"></param>
        public static void ProcessKeyEvent(Key key, bool pressed)
        {
            //Only supporting ASCII in the editor :D
            //Windows 'A' key  = A = 44 GLFW = 65
            //ASCII A-Z
            if ((uint)key >= 44 && (uint)key <= 69)
            {
                Keys[(uint)key + 21] = pressed;
            }

        }

        /// <summary>
        /// Process a mouse move event
        /// </summary>
        /// <param name="key"></param>
        public static void ProcessMouseMove(Point position)
        {
            MousePosition = position;
        }
        
        public static bool[] GetKeys()
        {
            return Keys;
        }

        public static Point GetMousePosition()
        {
            return MousePosition;
        }

    }
}
