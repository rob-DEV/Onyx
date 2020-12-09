using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OnyxEditor
{
    public delegate void SceneGraphSelectionChangedHandler(SceneGraphSelectionArgs e);
    public class SceneGraphSelectionArgs : EventArgs
    {
        public string SelectedGuid;
        public SceneGraphSelectionArgs(string selectedGuid)
        {
            this.SelectedGuid = selectedGuid;
        }
    }
}
