
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
            string inputPath = args.Length > 0 ? args[0] : "input-assemblies/scissors/scissors.iam";
            string outputPath = args.Length > 1 ? args[1] : "outputs/scissors_data.json";
            

            // Build the assembly
            Assembly assembly = AssemblyBuilder.BuildAssembly(inputPath, inventorApp);
            AssemblyMetadata assemblyMetadata = new AssemblyMetadata(assembly);

            // assembly.ExportToOBJ(directory: "data", fileName: "assembly_geometry.obj");
            assemblyMetadata.ExportToJson(outputPath);

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