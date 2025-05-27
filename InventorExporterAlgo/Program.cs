
using System.Runtime.InteropServices;
using Inventor;
using AssemblyModel;

namespace InventorExporterAlgo
{
    class Program
    {
        static void Main(string[] args)
        {

            // Start or get Inventor application
            Inventor.Application inventorApp = GetInventorApplication();

            // Path to your assembly file (.iam)
            string iamFilePath = @"C:\Users\Shubham Kharade\Downloads\CasterWheel\CasterWheel.iam";
            if (args.Length > 0) iamFilePath = args[0];

            // Build the assembly
            Assembly assembly = AssemblyBuilder.BuildAssembly(iamFilePath, inventorApp);

            // Example: Print the number of parts
            Console.WriteLine($"Assembly loaded: {assembly.FilePath}");
            Console.WriteLine($"Number of parts: {assembly.Parts.Count}");

            Console.WriteLine($"Meta data for assembly {assembly.FilePath}:");
            assembly.PrintMetadata();

            assembly.ExportAsSTL(inventorApp, "assembly-stls");

            // Clean up
            inventorApp.Quit();
        }

        static Inventor.Application GetInventorApplication() {
            Inventor.Application inventorApp;
            try
            {
                inventorApp = (Inventor.Application)NativeMethods.GetActiveObject("Inventor.Application");
            }
            catch
            {
                Type inventorAppType = Type.GetTypeFromProgID("Inventor.Application");
                inventorApp = (Inventor.Application)Activator.CreateInstance(inventorAppType);
                inventorApp.Visible = true;
            }
            return inventorApp;
        }
    }

    static class NativeMethods
    {
        [DllImport("oleaut32.dll", CharSet = CharSet.Unicode, PreserveSig = false)]
        public static extern void GetActiveObject([MarshalAs(UnmanagedType.LPWStr)] string progID, IntPtr reserved, out object ppunk);

        public static object GetActiveObject(string progID)
        {
            GetActiveObject(progID, IntPtr.Zero, out object obj);
            return obj;
        }
    }

}