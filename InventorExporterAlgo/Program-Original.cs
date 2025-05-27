
// using System.Runtime.InteropServices;
// using Inventor;
 
// namespace InventorExporterAlgo
// {
//     class Program
//     {
//         static void Main(string[] args)
//         {
//             string iamFilePath;
 
//             if (args.Length == 0)
//             {
//                 // Replace with your full .iam file path here for testing:
//                 iamFilePath = @"C:\Users\Shubham Kharade\Downloads\CasterWheel\CasterWheel.iam"; 

//                 Console.WriteLine("No argument given. Using hardcoded path:\n" + iamFilePath);
//             }
//             else
//             {
//                 iamFilePath = args[0];
//             }
 
//             try
//             {
//                 // Inventor.Application inventorApp = null;
//                 Application? inventorApp = null;
//                 bool startedInventor = false;
 
//                 try
//                 {
//                     // Use custom P/Invoke method to get running Inventor instance
//                     inventorApp = (Inventor.Application)NativeMethods.GetActiveObject("Inventor.Application");
//                 }
//                 catch
//                 {
//                     // If Inventor is not running, create a new instance
//                     Type inventorAppType = Type.GetTypeFromProgID("Inventor.Application");
//                     inventorApp = (Application)Activator.CreateInstance(inventorAppType);
//                     if (inventorApp != null) inventorApp.Visible = false;
//                     startedInventor = true;
//                 }
 
//                 // Open the assembly document (read-only)
//                 AssemblyDocument assemblyDoc = (AssemblyDocument)inventorApp.Documents.Open(iamFilePath, false);
//                 AssemblyComponentDefinition asmCompDef = assemblyDoc.ComponentDefinition;
 
//                 Console.WriteLine("\nModel Tree for Assembly:");
//                 PrintComponents(asmCompDef.Occurrences, 0);
 
//                 Console.WriteLine("\nJoints in the Assembly:");
//                 PrintJoints(asmCompDef.Joints);
                
 
//                 Console.WriteLine("\nConstraints (Relationships) in the Assembly:");
//                 PrintConstraints(asmCompDef.Constraints);
 
//                 // Close the document without saving
//                 assemblyDoc.Close(false);
 
//                 // Quit Inventor only if we started it
//                 if (startedInventor)
//                 {
//                     inventorApp.Quit();
//                 }
//             }
//             catch (Exception ex)
//             {
//                 Console.WriteLine("Error: " + ex.Message);
//             }
 
//             Console.WriteLine("\nPress any key to exit...");
//             Console.ReadKey();
//         }
 
//         static void PrintComponents(ComponentOccurrences occurrences, int level)
//         {
//             foreach (ComponentOccurrence occurrence in occurrences)
//             {
//                 Console.WriteLine(new string(' ', level * 2) + "- " + occurrence.Name + " (" + occurrence.DefinitionDocumentType + ")");

//                 // Recursively print children if this occurrence is an assembly
//                 if (occurrence.DefinitionDocumentType == DocumentTypeEnum.kAssemblyDocumentObject)
//                 {
//                     AssemblyComponentDefinition subAsmDef = (AssemblyComponentDefinition)occurrence.Definition;
//                     PrintComponents(subAsmDef.Occurrences, level + 1);
//                 }
//             }
//         }
 
//         static void PrintJoints(AssemblyJoints joints)
//         {
//             foreach (AssemblyJoint joint in joints)
//             {
//                 ComponentOccurrence occ1 = joint.OccurrenceOne;
//                 ComponentOccurrence occ2 = joint.OccurrenceTwo;

//                 string comp1 = occ1._DisplayName;
//                 string comp2 = occ2._DisplayName;
 
//                 Console.WriteLine($"Joint: {joint.Name}, Type: {joint.Type}, Between: {comp1} <--> {comp2}");
//             }
//         }
 
//         static void PrintConstraints(AssemblyConstraints constraints)
//         {
//             foreach (AssemblyConstraint constraint in constraints)
//             {
//                 ComponentOccurrence occ1 = constraint.OccurrenceOne;
//                 ComponentOccurrence occ2 = constraint.OccurrenceTwo;

//                 string comp1 = occ1._DisplayName;
//                 string comp2 = occ2._DisplayName;

//                 Console.WriteLine($"Constraint: {constraint.Name}, Type: {constraint.Type}, Between: {comp1} <--> {comp2}");
//             }
//         }
//     }
    
    
 
//     static class NativeMethods
//     {
//         [DllImport("oleaut32.dll", CharSet = CharSet.Unicode, PreserveSig = false)]
//         public static extern void GetActiveObject([MarshalAs(UnmanagedType.LPWStr)] string progID, IntPtr reserved, out object ppunk);

//         public static object GetActiveObject(string progID)
//         {
//             GetActiveObject(progID, IntPtr.Zero, out object obj);
//             return obj;
//         }
//     }
// }