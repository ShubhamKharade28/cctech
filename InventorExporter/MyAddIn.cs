
using Inventor;
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace InventorExporter
{
    [Guid("836974a0-2e5b-4213-ad0a-d031ded57dee")]
    [ProgId("InventorExporter.MyAddIn")]
    public class MyAddIn : ApplicationAddInServer
    {
        private Inventor.Application _inventorApp;

        public void Activate(ApplicationAddInSite addInSiteObject, bool firstTime)
        {
            _inventorApp = addInSiteObject.Application;
            System.Windows.Forms.MessageBox.Show("InventorExporter loaded!");
        }

        public void Deactivate() => _inventorApp = null;
        public void ExecuteCommand(int CommandID) { }
        public object Automation => null;
    }
}


