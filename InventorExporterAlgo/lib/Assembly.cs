using System.Collections.Generic;

namespace AssemblyModel
{
    public class ConstraintData
    {
        public string Name { get; set; }
        public string Type { get; set; }
        public string EntityOne { get; set; }
        public string EntityTwo { get; set; }
    }

    public class JointData
    {
        public string Name { get; set; }
        public string Type { get; set; }
        public string OccurrenceOne { get; set; }
        public string OccurrenceTwo { get; set; }
    }

    public class Assembly
    {
        public string FilePath { get; set; }
        public List<AssemblyPart> Parts { get; set; } = new();
        public List<ConstraintData> Constraints { get; set; } = new();
        public List<JointData> Joints { get; set; } = new();

        public void PrintMetadata()
        {
            Console.WriteLine($"\n===== Assembly Metadata =====");
            Console.WriteLine($"File: {FilePath}");
            Console.WriteLine($"Parts: {Parts.Count}");
            for (int i = 0; i < Parts.Count; i++)
            {
                var part = Parts[i];
                Console.WriteLine($"  [{i + 1}] Name: {part.Name}");
                Console.WriteLine($"      DocumentType: {part.DocumentType}");
                Console.WriteLine($"      Children: {part.Children.Count}");
            }

            Console.WriteLine($"\nConstraints: {Constraints.Count}");
            for (int i = 0; i < Constraints.Count; i++)
            {
                var c = Constraints[i];
                Console.WriteLine($"  [{i + 1}] Name: {c.Name}");
                Console.WriteLine($"      Type: {c.Type}");
                Console.WriteLine($"      EntityOne: {c.EntityOne}");
                Console.WriteLine($"      EntityTwo: {c.EntityTwo}");
            }

            Console.WriteLine($"\nJoints: {Joints.Count}");
            for (int i = 0; i < Joints.Count; i++)
            {
                var j = Joints[i];
                Console.WriteLine($"  [{i + 1}] Name: {j.Name}");
                Console.WriteLine($"      Type: {j.Type}");
                Console.WriteLine($"      OccurrenceOne: {j.OccurrenceOne}");
                Console.WriteLine($"      OccurrenceTwo: {j.OccurrenceTwo}");
            }
            Console.WriteLine($"============================\n");
        }

        public string ExportAsSTL(Inventor.Application inventorApp, string outputFolder)
        {
            try
            {
                Inventor.AssemblyDocument assemblyDoc = assemblyDoc = (Inventor.AssemblyDocument)inventorApp.Documents.Open(FilePath, false);
                if (!System.IO.Directory.Exists(outputFolder))
                    System.IO.Directory.CreateDirectory(outputFolder);

                string stlPath = System.IO.Path.Combine(
                    outputFolder,
                    System.IO.Path.GetFileNameWithoutExtension(this.FilePath) + ".stl"
                );

                // Get the STL translator add-in and cast to TranslatorAddIn
                var stlAddInObj = inventorApp.ApplicationAddIns.ItemById["{89162634-02B6-11D5-8E80-0010B541CAA8}"];
                if (stlAddInObj != null && stlAddInObj.Activated == false)
                    stlAddInObj.Activate();

                var stlAddIn = stlAddInObj as Inventor.TranslatorAddIn;
                if (stlAddIn == null)
                    throw new System.Exception("STL TranslatorAddIn not found or not available.");

                var context = inventorApp.TransientObjects.CreateTranslationContext();
                context.Type = Inventor.IOMechanismEnum.kFileBrowseIOMechanism;

                var options = inventorApp.TransientObjects.CreateNameValueMap();
                if (stlAddIn.HasSaveCopyAsOptions[assemblyDoc, context, options])
                {
                    // You can set STL options here if needed, e.g.:
                    // options.Value["ExportUnits"] = 1; // 1 = cm, 2 = mm, etc.
                }

                var dataMedium = inventorApp.TransientObjects.CreateDataMedium();
                dataMedium.FileName = stlPath;

                stlAddIn.SaveCopyAs(assemblyDoc, context, options, dataMedium);
                return stlPath;
            }
            catch (System.Exception ex)
            {
                System.Console.WriteLine($"Error exporting STL: {ex.Message}");
                return null;
            }
        }
    }
}
