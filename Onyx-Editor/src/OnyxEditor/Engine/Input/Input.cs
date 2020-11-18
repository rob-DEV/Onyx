using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace OnyxEditor
{
    /// <summary>
    /// Data structure containing viewport input to be sent to and 
    /// processed by the engine
    /// </summary>
    public class Input
    {
        private static bool[] Keys = new bool[Keycodes.ONYX_KEYCODE_COUNT];
        private static bool[] MouseButtons = new bool[MouseCodes.ONYX_MOUSEBUTTON_COUNT];

        private static Point MousePosition = new Point(640,360);

        public static bool[] GetKeys()
        {
            return Keys;
        }

        public static bool[] GetMouseButtons()
        {
            return MouseButtons;
        }
        public static Point GetMousePosition()
        {
            return MousePosition;
        }

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
        /// Process a windows mouse event and convert to Onyx key-code
        /// </summary>
        /// <param name="key"></param>
        public static void ProcessMouseEvent(MouseEventArgs eventArgs)
        {
            MouseButtons[MouseCodes.ONYX_MOUSE_BUTTON_LEFT] = eventArgs.LeftButton == MouseButtonState.Pressed ? true : false;
            MouseButtons[MouseCodes.ONYX_MOUSE_BUTTON_RIGHT] = eventArgs.RightButton == MouseButtonState.Pressed ? true : false;
            MouseButtons[MouseCodes.ONYX_MOUSE_BUTTON_MIDDLE] = eventArgs.MiddleButton == MouseButtonState.Pressed ? true : false;
        }

        /// <summary>
        /// Process a mouse move event
        /// </summary>
        /// <param name="key"></param>
        public static void ProcessMouseMove(Point position)
        {
            MousePosition = position;
        }
    }
}
