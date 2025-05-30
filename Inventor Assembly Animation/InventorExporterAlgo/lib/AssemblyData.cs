using System.Text.Json;
using Inventor;

namespace AssemblyModel
{
    public class AssemblyDataExporter
    {
        public static void ExportAssemblyToJson(string dataDir = "data", string inputFile = "assembly.iml", string outputFile = "assembly_data.json", Inventor.Application inventorApp = null)
        {
            if (inventorApp == null)
            {
                Console.WriteLine("Inventor application instance is required.");
                return;
            }

            // if input file path and output file path are absolute paths, use them directly
            string inputFilePath = inputFile;
            if (!System.IO.Path.IsPathRooted(inputFile))
                inputFilePath = System.IO.Path.Combine(dataDir, inputFile);

            string outputFilePath = System.IO.Path.Combine(dataDir, outputFile);

            if (!System.IO.Directory.Exists(dataDir)) System.IO.Directory.CreateDirectory(dataDir);

            if (!System.IO.File.Exists(inputFilePath))
            {
                Console.WriteLine($"Input file not found: {inputFilePath}");
                return;
            }

            AssemblyDocument assemblyDoc = inventorApp.Documents.Open(inputFilePath, false) as AssemblyDocument;
            AssemblyComponentDefinition asmCompDef = assemblyDoc.ComponentDefinition;
            using (var writer = new System.IO.StreamWriter(outputFilePath))
            {
                var options = new JsonSerializerOptions
                {
                    WriteIndented = true,
                    PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
                };
                string json = JsonSerializer.Serialize(asmCompDef, options);
                writer.WriteLine(json);
            }
            Console.WriteLine($"Assembly data exported to: {outputFilePath}");
            if (assemblyDoc != null)
            {
                assemblyDoc.Close(false);
            }
        }
    }
}