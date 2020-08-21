using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using OnyxCLR;


namespace Onyx_Editor_NET_Test
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            //MessageBox.Show(WrapperTest.add().ToString());
            OnyxCLR.EditorWrapper wrapper = new EditorWrapper();
            
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
