using System.Collections.Generic;
using System.Text.Json;

namespace AssemblyModel
{
    public class ConstraintData
    {
        public string Name { get; set; }
        public string Type { get; set; }
        public string EntityOne { get; set; }
        public string EntityTwo { get; set; }
        public string OccurrenceOne { get; set; }
        public string OccurrenceTwo { get; set; }
    }

    public class JointData
    {
        public string Name { get; set; }
        public string Type { get; set; }
        public string OccurrenceOne { get; set; }
        public string OccurrenceTwo { get; set; }
    }
 
    public class AttributeData
    {
        public string Name { get; set; }
        public string Value { get; set; }
    }

    public class AttributeSetData
    {
        public string SetName { get; set; }
        public List<AttributeData> Attributes { get; set; }
    }


    public class Assembly
    {
        public string FilePath { get; set; }
        public string DisplayName;
        public string DocumentType;

        public List<AssemblyComponent> Components { get; set; } = new();
        public List<ConstraintData> Constraints { get; set; } = new();
        public List<JointData> Joints { get; set; } = new();
        public List<AttributeSetData> Attributes { get; set; } = new();

        /* Attributes to add:
            1. DisplayName (Name);
            2. ModelingSettings
            3. SketchSettings
            4. Materials
            5. DocumentType
        */


        public void PrintMetadata()
        {
            Console.WriteLine($"\n===== Assembly Metadata =====");
            Console.WriteLine($"File: {FilePath}");
            Console.WriteLine($"DisplayName: {DisplayName}");
            Console.WriteLine($"DocumentType: {DocumentType}");
            Console.WriteLine($"Components: {Components.Count}");
            for (int i = 0; i < Components.Count; i++)
            {
                var component = Components[i];
                Console.WriteLine($"  [{i + 1}] Name: {component.Name}");
                Console.WriteLine($"      DocumentType: {component.DocumentType}");
                Console.WriteLine($"      Children: {component.Children.Count}");
            }

            Console.WriteLine($"\nConstraints: {Constraints.Count}");
            for (int i = 0; i < Constraints.Count; i++)
            {
                var c = Constraints[i];
                Console.WriteLine($"  [{i + 1}] Name: {c.Name}");
                Console.WriteLine($"      Type: {c.Type}");
                Console.WriteLine($"      EntityOne: {c.EntityOne}");
                Console.WriteLine($"      EntityTwo: {c.EntityTwo}");
                Console.WriteLine($"      EntityOne: {c.OccurrenceOne}");
                Console.WriteLine($"      EntityTwo: {c.OccurrenceTwo}");
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

            Console.WriteLine($"\nAttributes: {Attributes.Count}");
            for (int i = 0; i < Attributes.Count; i++)
            {
                var attrSet = Attributes[i];
                Console.WriteLine($"  [{i + 1}] SetName: {attrSet.SetName}");
                foreach (var attr in attrSet.Attributes)
                {
                    Console.WriteLine($"      Attribute: {attr.Name} = {attr.Value}");
                }
            }
            Console.WriteLine($"============================\n");
        }

        private static double[] MultiplyMatrix(double[] a, double[] b)
        {
            var r = new double[12];
            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 4; col++)
                {
                    r[row * 4 + col] =
                        a[row * 4 + 0] * b[0 + col] +
                        a[row * 4 + 1] * b[4 + col] +
                        a[row * 4 + 2] * b[8 + col] +
                        (col == 3 ? a[row * 4 + 3] : 0);
                }
            }
            return r;
        }

        private static (double X, double Y, double Z) TransformVertex(VertexData v, double[] matrix)
        {
            double x = v.X, y = v.Y, z = v.Z;
            return (
                matrix[0] * x + matrix[1] * y + matrix[2] * z + matrix[3],
                matrix[4] * x + matrix[5] * y + matrix[6] * z + matrix[7],
                matrix[8] * x + matrix[9] * y + matrix[10] * z + matrix[11]
            );
        }

        public void ExportToOBJ(string directory = "data", string fileName = "assembly.obj")
        {
            var vertices = new List<(double X, double Y, double Z)>();
            var faces = new List<List<int>>();

            int AddVertex(double x, double y, double z)
            {
                // check if vertex already exists
                for (int i = 0; i < vertices.Count; i++)
                {
                    var v = vertices[i];
                    if (v.X == x && v.Y == y && v.Z == z)
                    {
                        return i + 1; // OBJ indices are 1-based
                    }
                }
                vertices.Add((x, y, z));
                return vertices.Count;
            }

            // Todo: Apply transformations before writing data


            Console.WriteLine($"Exporting assembly to OBJ format...");
            Console.WriteLine($"Number of Components: {Components.Count}");

            foreach (var component in Components)
            {
                foreach (var body in component.SurfaceBodies)
                {
                    foreach (var face in body.Faces)
                    {
                        List<int> faceVerticesIndices = new List<int>();
                        foreach (var vertex in face.Vertices)
                        {
                            int index = AddVertex(vertex.X, vertex.Y, vertex.Z);
                            faceVerticesIndices.Add(index);
                        }
                        faces.Add(faceVerticesIndices);
                    }
                }
            }

            // create empty output directory if it doesn't exist
            System.IO.Directory.CreateDirectory(directory);

            string outputPath = System.IO.Path.Combine(directory, fileName);

            using (var writer = new System.IO.StreamWriter(outputPath))
            {
                Console.WriteLine($"Exporting {vertices.Count} vertices and {faces.Count} faces to {outputPath}");
                foreach (var v in vertices)
                {
                    writer.WriteLine($"v {v.X} {v.Y} {v.Z}");
                }
                writer.WriteLine();

                foreach (var face in faces)
                {
                    writer.WriteLine("f " + string.Join(" ", face));
                }
            }
        }

        public void ExportToJson(string outputPath)
        {
            // Ensure output directory exists
        string outputDir = System.IO.Path.GetDirectoryName(outputPath);
        if (!string.IsNullOrEmpty(outputDir) && !System.IO.Directory.Exists(outputDir))
            System.IO.Directory.CreateDirectory(outputDir);

            // Serialize the assembly metadata to JSON
        var options = new JsonSerializerOptions
            {
                WriteIndented = true,
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
            };

            string json = JsonSerializer.Serialize(this, options);

            // Write the JSON to a file
            using (var writer = new System.IO.StreamWriter(outputPath))
            {
                writer.WriteLine(json);
            }

            Console.WriteLine($"Assembly data saved to: {outputPath}");
        }
    }
}
