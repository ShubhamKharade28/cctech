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

        public void ExportAsOBJ(string directory = "data", string fileName = "assembly.obj")
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

            Console.WriteLine($"Exporting assembly to OBJ format...");
            Console.WriteLine($"Number of parts: {Parts.Count}");

            foreach (var part in Parts)
            {
                Console.WriteLine($"Processing part: {part.Name} ({part.DocumentType})");
                foreach (var body in part.SurfaceBodies)
                {
                    Console.WriteLine($"  Surface body with {body.Faces.Count} faces");
                    foreach (var face in body.Faces)
                    {
                        Console.WriteLine($"    Face with {face.Vertices.Count} vertices and {face.Edges.Count} edges");
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
    }
}
