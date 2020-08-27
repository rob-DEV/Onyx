using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Onyx_Editor_NET
{
    /// <summary>
    /// List of engine key-codes
    /// </summary>
    public static class Keycodes
    {
        //Theoretical max amount of keys Onyx can handle
        public static short ONYX_KEYCODE_COUNT = 350;

        public static short ONYX_KEY_UNKNOWN = -1;                         
        /* Printable keys */                     
        public static short ONYX_KEY_SPACE = 32;
        public static short ONYX_KEY_APOSTROPHE = 39; /* ' */
        public static short ONYX_KEY_COMMA = 44; /* , */
        public static short ONYX_KEY_MINUS = 45; /* - */
        public static short ONYX_KEY_PERIOD = 46; /* . */
        public static short ONYX_KEY_SLASH = 47; /* / */
        public static short ONYX_KEY_0 = 48;
        public static short ONYX_KEY_1 = 49;
        public static short ONYX_KEY_2 = 50;
        public static short ONYX_KEY_3 = 51;
        public static short ONYX_KEY_4 = 52;
        public static short ONYX_KEY_5 = 53;
        public static short ONYX_KEY_6 = 54;
        public static short ONYX_KEY_7 = 55;
        public static short ONYX_KEY_8 = 56;
        public static short ONYX_KEY_9 = 57;
        public static short ONYX_KEY_SEMICOLON = 59; /* ; */
        public static short ONYX_KEY_EQUAL = 61; /* = */
        public static short ONYX_KEY_A = 65;
        public static short ONYX_KEY_B = 66;
        public static short ONYX_KEY_C = 67;
        public static short ONYX_KEY_D = 68;
        public static short ONYX_KEY_E = 69;
        public static short ONYX_KEY_F = 70;
        public static short ONYX_KEY_G = 71;
        public static short ONYX_KEY_H = 72;
        public static short ONYX_KEY_I = 73;
        public static short ONYX_KEY_J = 74;
        public static short ONYX_KEY_K = 75;
        public static short ONYX_KEY_L = 76;
        public static short ONYX_KEY_M = 77;
        public static short ONYX_KEY_N = 78;
        public static short ONYX_KEY_O = 79;
        public static short ONYX_KEY_P = 80;
        public static short ONYX_KEY_Q = 81;
        public static short ONYX_KEY_R = 82;
        public static short ONYX_KEY_S = 83;
        public static short ONYX_KEY_T = 84;
        public static short ONYX_KEY_U = 85;
        public static short ONYX_KEY_V = 86;
        public static short ONYX_KEY_W = 87;
        public static short ONYX_KEY_X = 88;
        public static short ONYX_KEY_Y = 89;
        public static short ONYX_KEY_Z = 90;
        public static short ONYX_KEY_LEFT_BRACKET = 91; /* [ */
        public static short ONYX_KEY_BACKSLASH = 92; /* \ */
        public static short ONYX_KEY_RIGHT_BRACKET = 93; /* ] */
        public static short ONYX_KEY_GRAVE_ACCENT = 96; /* ` */
        public static short ONYX_KEY_WORLD_1 = 161;/* non-US #1 */
        public static short ONYX_KEY_WORLD_2 = 162;/* non-US #2 */
                                              
        /* Function keys */                           
        public static short ONYX_KEY_ESCAPE = 256;
        public static short ONYX_KEY_ENTER = 257;
        public static short ONYX_KEY_TAB = 258;
        public static short ONYX_KEY_BACKSPACE = 259;
        public static short ONYX_KEY_INSERT = 260;
        public static short ONYX_KEY_DELETE = 261;
        public static short ONYX_KEY_RIGHT = 262;
        public static short ONYX_KEY_LEFT = 263;
        public static short ONYX_KEY_DOWN = 264;
        public static short ONYX_KEY_UP = 265;
        public static short ONYX_KEY_PAGE_UP = 266;
        public static short ONYX_KEY_PAGE_DOWN = 267;
        public static short ONYX_KEY_HOME = 268;
        public static short ONYX_KEY_END = 269;
        public static short ONYX_KEY_CAPS_LOCK = 280;
        public static short ONYX_KEY_SCROLL_LOCK = 281;
        public static short ONYX_KEY_NUM_LOCK = 282;
        public static short ONYX_KEY_PRINT_SCREEN = 283;
        public static short ONYX_KEY_PAUSE = 284;
        public static short ONYX_KEY_F1 = 290;
        public static short ONYX_KEY_F2 = 291;
        public static short ONYX_KEY_F3 = 292;
        public static short ONYX_KEY_F4 = 293;
        public static short ONYX_KEY_F5 = 294;
        public static short ONYX_KEY_F6 = 295;
        public static short ONYX_KEY_F7 = 296;
        public static short ONYX_KEY_F8 = 297;
        public static short ONYX_KEY_F9 = 298;
        public static short ONYX_KEY_F10 = 299;
        public static short ONYX_KEY_F11 = 300;
        public static short ONYX_KEY_F12 = 301;
        public static short ONYX_KEY_F13 = 302;
        public static short ONYX_KEY_F14 = 303;
        public static short ONYX_KEY_F15 = 304;
        public static short ONYX_KEY_F16 = 305;
        public static short ONYX_KEY_F17 = 306;
        public static short ONYX_KEY_F18 = 307;
        public static short ONYX_KEY_F19 = 308;
        public static short ONYX_KEY_F20 = 309;
        public static short ONYX_KEY_F21 = 310;
        public static short ONYX_KEY_F22 = 311;
        public static short ONYX_KEY_F23 = 312;
        public static short ONYX_KEY_F24 = 313;
        public static short ONYX_KEY_F25 = 314;
        public static short ONYX_KEY_KP_0 = 320;
        public static short ONYX_KEY_KP_1 = 321;
        public static short ONYX_KEY_KP_2 = 322;
        public static short ONYX_KEY_KP_3 = 323;
        public static short ONYX_KEY_KP_4 = 324;
        public static short ONYX_KEY_KP_5 = 325;
        public static short ONYX_KEY_KP_6 = 326;
        public static short ONYX_KEY_KP_7 = 327;
        public static short ONYX_KEY_KP_8 = 328;
        public static short ONYX_KEY_KP_9 = 329;
        public static short ONYX_KEY_KP_DECIMAL = 330;
        public static short ONYX_KEY_KP_DIVIDE = 331;
        public static short ONYX_KEY_KP_MULTIPLY = 332;
        public static short ONYX_KEY_KP_SUBTRACT = 333;
        public static short ONYX_KEY_KP_ADD = 334;
        public static short ONYX_KEY_KP_ENTER = 335;
        public static short ONYX_KEY_KP_EQUAL = 336;
        public static short ONYX_KEY_LEFT_SHIFT = 340;
        public static short ONYX_KEY_LEFT_CONTROL = 341;
        public static short ONYX_KEY_LEFT_ALT = 342;
        public static short ONYX_KEY_LEFT_SUPER = 343;
        public static short ONYX_KEY_RIGHT_SHIFT = 344;
        public static short ONYX_KEY_RIGHT_CONTROL = 345;
        public static short ONYX_KEY_RIGHT_ALT = 346;
        public static short ONYX_KEY_RIGHT_SUPER = 347;
        public static short ONYX_KEY_MENU = 348;

    }

}
