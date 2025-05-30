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

            // if path is relative, resolve it to absolute path
            if (!System.IO.Path.IsPathRooted(iamFilePath))
            {
                iamFilePath = System.IO.Path.GetFullPath(iamFilePath);
            }

            Console.WriteLine($"Opening assembly file: {iamFilePath}");
            var assemblyDoc = (AssemblyDocument)inventorApp.Documents.Open(iamFilePath, false);
            var asmCompDef = assemblyDoc.ComponentDefinition;

            Console.WriteLine($"Getting components from assembly...");
            assembly.Components = GetComponents(asmCompDef.Occurrences);

            Console.WriteLine($"Getting constraints from assembly...");
            assembly.Constraints = GetConstraints(asmCompDef.Constraints);

            Console.WriteLine($"Getting Joints from assembly...");
            assembly.Joints = GetJoints(asmCompDef.Joints);

            Console.WriteLine($"Getting attributes from assembly: {assemblyDoc.DisplayName}");
            assembly.Attributes = GetAttributes(assemblyDoc.AttributeSets);

            assemblyDoc.Close(false);

            Console.WriteLine("Assembly loaded successfully.");
            return assembly;
        }

        private static List<ConstraintData> GetConstraints(AssemblyConstraints asmConstraints)
        {
            var constraints = new List<ConstraintData>();
            foreach (AssemblyConstraint constraint in asmConstraints)
            {
                // string constraintName = constraint.Name;
                // string constraintType = constraint.Type.ToString();
                string occurrenceOne = constraint.OccurrenceOne._DisplayName;
                string occurrenceTwo = constraint.OccurrenceTwo._DisplayName;
                string entityOne = GetEntityName(constraint.EntityOne);
                string entityTwo = GetEntityName(constraint.EntityTwo);

                var data = new ConstraintData
                {
                    Name = constraint.Name,
                    Type = constraint.Type.ToString(),
                    EntityOne = GetEntityName(constraint.EntityOne),
                    EntityTwo = GetEntityName(constraint.EntityTwo),
                    OccurrenceOne = constraint.OccurrenceOne._DisplayName,
                    OccurrenceTwo = constraint.OccurrenceTwo._DisplayName
                };
                constraints.Add(data);
            }
            return constraints;
        }

        private static List<JointData> GetJoints(AssemblyJoints asmJoints)
        {
            var joints = new List<JointData>();
            foreach (object jointObj in asmJoints)
            {
                // Use reflection to get properties if possible
                var type = jointObj.GetType();
                var data = new JointData
                {
                    Type = type.ToString(),
                    Name = type.GetProperty("Name")?.GetValue(jointObj)?.ToString() ?? string.Empty,
                    OccurrenceOne = type.GetProperty("OccurrenceOne")?.GetValue(jointObj)?.ToString() ?? string.Empty,
                    OccurrenceTwo = type.GetProperty("OccurrenceTwo")?.GetValue(jointObj)?.ToString() ?? string.Empty
                };
                joints.Add(data);
            }
            return joints;
        }

        private static List<AssemblyComponent> GetComponents(ComponentOccurrences occurrences)
        {
            var components = new List<AssemblyComponent>();

            foreach (ComponentOccurrence occurrence in occurrences)
            {
                var component = new AssemblyComponent
                {
                    Name = occurrence.Name,
                    Parent = occurrence.ParentOccurrence?._DisplayName ?? "Root",
                    DocumentType = occurrence.DefinitionDocumentType.ToString(),
                    TransformMatrix = GetTransformMatrix(occurrence.Transformation),
                    SurfaceBodies = GetSurfaceBodies(occurrence.Definition),
                    // Constraints = GetConstraints(occurrence.Constraints),
                    // Joints = GetJoints(occurrence.Joints),
                    Attributes = GetAttributes(occurrence.AttributeSets),
                    Children = occurrence.DefinitionDocumentType == DocumentTypeEnum.kAssemblyDocumentObject
                        ? GetComponents(((AssemblyComponentDefinition)occurrence.Definition).Occurrences)
                        : new List<AssemblyComponent>()
                };

                components.Add(component);
            }

            return components;
        }

        private static List<AttributeSetData> GetAttributes(AttributeSets attributeSets)
        {
            var attributes = new List<AttributeSetData>();
            foreach (AttributeSet attributeSet in attributeSets)
            {
                var attrSetData = new AttributeSetData
                {
                    SetName = attributeSet.Name,
                    Attributes = new List<AttributeData>()
                };

                foreach (AttributeData attribute in attributeSet)
                {
                    attrSetData.Attributes.Add(new AttributeData
                    {
                        Name = attribute.Name,
                        Value = attribute.Value.ToString()
                    });
                }

                attributes.Add(attrSetData);
            }
            return attributes;
        }

        static string GetEntityName(object entity)
        {
            if (entity is Face face) return $"Face (SurfaceType: {face.SurfaceType})";
            if (entity is Edge edge) return $"Edge (CurveType: {edge.GeometryType})";
            if (entity is WorkPlane wp) return $"WorkPlane: {wp.Name}";
            if (entity is WorkAxis wa) return $"WorkAxis: {wa.Name}";
            if (entity is WorkPoint wpnt) return $"WorkPoint: {wpnt.Name}";
            if (entity is ComponentOccurrence occ) return $"Component: {occ.Name}";
            return "Unknown Entity";
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
                surfaceBody.Faces.Add(faceObj);
            }

            return surfaceBody;
        }
    }
}
