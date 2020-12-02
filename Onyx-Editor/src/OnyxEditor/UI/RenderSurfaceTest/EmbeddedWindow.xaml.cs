using System;
using System.Windows;
using System.Windows.Controls;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Windows.Interop;
using System.Threading;

namespace OnyxEditor
{
    /// <summary>
    /// AppControl.xaml 
    /// </summary>
    public partial class EmbeddedWindow : UserControl, IDisposable
    {
        

        Point position;

        IntPtr nativeWindowHandle;

        public EmbeddedWindow()
        {
            InitializeComponent();
            this.SizeChanged += new SizeChangedEventHandler(OnSizeChanged);
            this.SizeChanged += new SizeChangedEventHandler(OnResize);
        }

        ~EmbeddedWindow()
        {
            this.Dispose();
        }


        public void SetWindowAndUpdate(IntPtr ptr, Point position)
        {
            this.position = position;
            nativeWindowHandle = ptr;
            // Put it into this form
            var helper = new WindowInteropHelper(Window.GetWindow(this.AppContainer));
            SetParent(nativeWindowHandle, helper.Handle);

            // Remove border and whatnot
            SetWindowLongA(nativeWindowHandle, GWL_STYLE, WS_VISIBLE);

            // Move the window to overlay it on this window
            MoveWindow(nativeWindowHandle, (int)position.X, (int)position.Y, (int)this.ActualWidth, (int)this.ActualHeight, true);
        }

        protected void OnSizeChanged(object s, SizeChangedEventArgs e)
        {
            this.InvalidateVisual();
        }

        protected void OnResize(object s, SizeChangedEventArgs e)
        {
            if (this.nativeWindowHandle != IntPtr.Zero)
            {
                MoveWindow(nativeWindowHandle, (int)position.X, (int)position.Y, (int)this.ActualWidth, (int)this.ActualHeight, true);
            }
        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
        }

        [DllImport("user32.dll", EntryPoint="GetWindowThreadProcessId",  SetLastError=true,
             CharSet=CharSet.Unicode, ExactSpelling=true,
             CallingConvention=CallingConvention.StdCall)]
        private static extern long GetWindowThreadProcessId(long hWnd, long lpdwProcessId); 
            
        [DllImport("user32.dll", SetLastError=true)]
        private static extern IntPtr FindWindow (string lpClassName, string lpWindowName);

        [DllImport("user32.dll", SetLastError=true)]
        private static extern long SetParent (IntPtr hWndChild, IntPtr hWndNewParent);

        [DllImport("user32.dll", EntryPoint="GetWindowLongA", SetLastError=true)]
        private static extern long GetWindowLong (IntPtr hwnd, int nIndex);

        [DllImport("user32.dll", EntryPoint="SetWindowLongA", SetLastError=true)]
        public static extern int SetWindowLongA([System.Runtime.InteropServices.InAttribute()] System.IntPtr hWnd, int nIndex, int dwNewLong);

        [DllImport("user32.dll", SetLastError=true)]
        private static extern long SetWindowPos(IntPtr hwnd, long hWndInsertAfter, long x, long y, long cx, long cy, long wFlags);
        
        [DllImport("user32.dll", SetLastError=true)]
        private static extern bool MoveWindow(IntPtr hwnd, int x, int y, int cx, int cy, bool repaint);

        private const int SWP_NOOWNERZORDER = 0x200;
        private const int SWP_NOREDRAW = 0x8;
        private const int SWP_NOZORDER = 0x4;
        private const int SWP_SHOWWINDOW = 0x0040;
        private const int WS_EX_MDICHILD = 0x40;
        private const int SWP_FRAMECHANGED = 0x20;
        private const int SWP_NOACTIVATE = 0x10;
        private const int SWP_ASYNCWINDOWPOS = 0x4000;
        private const int SWP_NOMOVE = 0x2;
        private const int SWP_NOSIZE = 0x1;
        private const int GWL_STYLE = (-16);
        private const int WS_VISIBLE = 0x10000000;
        private const int WS_CHILD = 0x40000000;

    }
}
