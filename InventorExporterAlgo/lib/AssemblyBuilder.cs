using System.Collections.Generic;
using Inventor;
using AssemblyModel;

using InvFace = Inventor.Face;
using InvEdge = Inventor.Edge;
using InvVertex = Inventor.Vertex;
using InvSurfaceBody = Inventor.SurfaceBody;

namespace AssemblyModel
{
    public static class AssemblyBuilder
    {
        public static Assembly BuildAssembly(string iamFilePath, Inventor.Application inventorApp)
        {
            var assembly = new Assembly { FilePath = iamFilePath };

            Console.WriteLine($"Opening assembly file: {iamFilePath}");
            var assemblyDoc = (AssemblyDocument)inventorApp.Documents.Open(iamFilePath, false);
            var asmCompDef = assemblyDoc.ComponentDefinition;

            Console.WriteLine($"Getting parts from assembly: {assemblyDoc.DisplayName}");
            assembly.Parts = GetParts(asmCompDef.Occurrences);

            Console.WriteLine($"Getting constraints and joints from assembly: {assemblyDoc.DisplayName}");
            assembly.Constraints = GetConstraints(asmCompDef);
            assembly.Joints = GetJoints(asmCompDef);

            assemblyDoc.Close(false);
            return assembly;
        }

        private static List<ConstraintData> GetConstraints(AssemblyComponentDefinition asmCompDef)
        {
            var constraints = new List<ConstraintData>();
            foreach (AssemblyConstraint constraint in asmCompDef.Constraints)
            {
                string constraintName = constraint.Name;
                string constraintType = constraint.Type.ToString();
                string entityOne = constraint.OccurrenceOne._DisplayName;
                string entityTwo = constraint.OccurrenceTwo._DisplayName;

                var data = new ConstraintData
                {
                    Name = constraintName,
                    Type = constraintType,
                    EntityOne = entityOne,
                    EntityTwo = entityTwo
                };
                constraints.Add(data);
            }
            return constraints;
        }

        private static List<JointData> GetJoints(AssemblyComponentDefinition asmCompDef)
        {
            var joints = new List<JointData>();
            foreach (object jointObj in asmCompDef.Joints)
            {
                // Use reflection to get properties if possible
                var type = jointObj.GetType();
                string name = type.GetProperty("Name")?.GetValue(jointObj)?.ToString() ?? string.Empty;
                string jointType = type.GetProperty("JointType")?.GetValue(jointObj)?.ToString() ?? string.Empty;
                string occurrenceOne = type.GetProperty("OccurrenceOne")?.GetValue(jointObj)?.ToString() ?? string.Empty;
                string occurrenceTwo = type.GetProperty("OccurrenceTwo")?.GetValue(jointObj)?.ToString() ?? string.Empty;
                var data = new JointData
                {
                    Name = name,
                    Type = jointType,
                    OccurrenceOne = occurrenceOne,
                    OccurrenceTwo = occurrenceTwo
                };
                joints.Add(data);
            }
            return joints;
        }

        private static List<AssemblyPart> GetParts(ComponentOccurrences occurrences)
        {
            var parts = new List<AssemblyPart>();

            foreach (ComponentOccurrence occurrence in occurrences)
            {
                var part = new AssemblyPart
                {
                    Name = occurrence.Name,
                    DocumentType = occurrence.DefinitionDocumentType.ToString(),
                    TransformMatrix = GetTransformMatrix(occurrence.Transformation),
                    SurfaceBodies = GetSurfaceBodies(occurrence.Definition),
                    Children = occurrence.DefinitionDocumentType == DocumentTypeEnum.kAssemblyDocumentObject
                        ? GetParts(((AssemblyComponentDefinition)occurrence.Definition).Occurrences)
                        : new List<AssemblyPart>()
                };

                parts.Add(part);
            }

            return parts;
        }

        private static double[] GetTransformMatrix(Matrix transform)
        {
            var matrixArray = new double[12];
            for (int row = 1; row <= 3; row++)
            {
                for (int col = 1; col <= 4; col++)
                {
                    matrixArray[(row - 1) * 4 + (col - 1)] = transform.get_Cell(row, col);
                }
            }
            return matrixArray;
        }

        private static List<SurfaceBodyData> GetSurfaceBodies(ComponentDefinition compDef)
        {
            var bodies = new List<SurfaceBodyData>();

            if (compDef is PartComponentDefinition partDef)
            {
                foreach (InvSurfaceBody body in partDef.SurfaceBodies)
                {
                    bodies.Add(BuildSurfaceBody(body));
                }
            }
            else if (compDef is AssemblyComponentDefinition asmDef)
            {
                foreach (InvSurfaceBody body in asmDef.SurfaceBodies)
                {
                    bodies.Add(BuildSurfaceBody(body));
                }
            }

            return bodies;
        }

        private static SurfaceBodyData BuildSurfaceBody(InvSurfaceBody invBody)
        {
            var surfaceBody = new SurfaceBodyData
            {
                Name = invBody.Name,
                Faces = new List<FaceData>()
            };

            foreach (InvFace invFace in invBody.Faces)
            {
                var faceObj = new FaceData
                {
                    SurfaceType = invFace.SurfaceType.ToString(),
                    Edges = new List<EdgeData>(),
                    Vertices = new List<VertexData>()
                };

                foreach (InvVertex v in invFace.Vertices)
                {
                    faceObj.Vertices.Add(new VertexData(v.Point.X, v.Point.Y, v.Point.Z));
                }

                foreach (InvEdge invEdge in invFace.Edges)
                {
                    var edgeObj = new EdgeData
                    {
                        GeometryType = invEdge.GeometryType.ToString(),
                        StartVertex = new VertexData(
                            invEdge.StartVertex.Point.X,
                            invEdge.StartVertex.Point.Y,
                            invEdge.StartVertex.Point.Z),
                        EndVertex = new VertexData(
                            invEdge.StopVertex.Point.X,
                            invEdge.StopVertex.Point.Y,
                            invEdge.StopVertex.Point.Z)
                    };

                    faceObj.Edges.Add(edgeObj);
                }
            }

            return surfaceBody;
        }
    }
}
