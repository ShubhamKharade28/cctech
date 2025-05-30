using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text.Json;
using Inventor;


namespace InventorReader
{
    class Program
    {
        static void Main(string[] args)
        {
            string iamFilePath = args.Length > 0 ? args[0] : @"C:\Saurav Farkade Windows\AnimationProject\SampleProject27May\Data\Assembly1.iam";
            string jsonOutputPath = @"C:\Saurav Farkade Windows\AnimationProject\Data\assembly_metadata4.json";
 
            var metadata = new AssemblyMetadata { FilePath = iamFilePath };
 
            try
            {
                Inventor.Application inventorApp = null;
                bool startedInventor = false;
 
                try
                {
                    inventorApp = (Inventor.Application)Marshal.GetActiveObject("Inventor.Application");
                }
                catch
                {
                    Type inventorAppType = Type.GetTypeFromProgID("Inventor.Application");
                    inventorApp = (Inventor.Application)Activator.CreateInstance(inventorAppType);
                    inventorApp.Visible = false;
                    startedInventor = true;
                }
 
                AssemblyDocument assemblyDoc = (AssemblyDocument)inventorApp.Documents.Open(iamFilePath, false);
                AssemblyComponentDefinition asmCompDef = assemblyDoc.ComponentDefinition;
 
                metadata.Components = GetComponents(asmCompDef.Occurrences, 0);
                metadata.Constraints = GetConstraints(asmCompDef.Constraints);
                metadata.Joints = GetJoints(asmCompDef.Joints);
                metadata.Attributes = GetAttributes(asmCompDef.AttributeSets);
 
                assemblyDoc.Close(false);
                if (startedInventor)
                {
                    inventorApp.Quit();
                }
 
                string json = JsonSerializer.Serialize(metadata, new JsonSerializerOptions { WriteIndented = true });
                System.IO.File.WriteAllText(jsonOutputPath, json);
                Console.WriteLine($"Metadata saved to: {jsonOutputPath}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }
 
            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        }
 
        static List<Component> GetComponents(ComponentOccurrences occurrences, int level)
        {
            var list = new List<Component>();
            foreach (ComponentOccurrence occurrence in occurrences)
            {
                var comp = new Component
                {
                    Name = occurrence.Name,
                    Type = occurrence.DefinitionDocumentType.ToString(),
                    Children = occurrence.DefinitionDocumentType == DocumentTypeEnum.kAssemblyDocumentObject
                        ? GetComponents(((AssemblyComponentDefinition)occurrence.Definition).Occurrences, level + 1)
                        : null
                };
                list.Add(comp);
            }
            return list;
        }
 
        static List<Constraint> GetConstraints(AssemblyConstraints constraints)
        {
            var list = new List<Constraint>();
            foreach (AssemblyConstraint c in constraints)
            {
                list.Add(new Constraint
                {
                    Name = c.Name,
                    Type = c.Type.ToString(),
                    EntityOne = GetEntityName(c.EntityOne),
                    EntityTwo = GetEntityName(c.EntityTwo)
                });
            }
            return list;
        }
 
        static List<Joint> GetJoints(AssemblyJoints joints)
        {
            var list = new List<Joint>();
            foreach (AssemblyJoint j in joints)
            {
                list.Add(new Joint
                {
                    Name = j.Name,
                    Type = j.Type.ToString(),
                    OccurrenceOne = j.OccurrenceOne?.Name ?? "Unknown",
                    OccurrenceTwo = j.OccurrenceTwo?.Name ?? "Unknown"
                });
            }
            return list;
        }
 
        static List<AttributeSetData> GetAttributes(AttributeSets attrSets)
        {
            var list = new List<AttributeSetData>();
            foreach (AttributeSet set in attrSets)
            {
                var attrs = new List<AttributeData>();
                foreach (Inventor.Attribute a in set)
                {
                    attrs.Add(new AttributeData
                    {
                        Name = a.Name,
                        Value = a.Value?.ToString()
                    });
                }
 
                list.Add(new AttributeSetData
                {
                    SetName = set.Name,
                    Attributes = attrs
                });
            }
            return list;
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
    }
 
    // Metadata classes for serialization
    class AssemblyMetadata
    {
        public string FilePath { get; set; }
        public List<Component> Components { get; set; }
        public List<Constraint> Constraints { get; set; }
        public List<Joint> Joints { get; set; }
        public List<AttributeSetData> Attributes { get; set; }
    }
 
    class Component
    {
        public string Name { get; set; }
        public string Type { get; set; }
        public List<Component> Children { get; set; }
    }
 
    class Constraint
    {
        public string Name { get; set; }
        public string Type { get; set; }
        public string EntityOne { get; set; }
        public string EntityTwo { get; set; }
    }
 
    class Joint
    {
        public string Name { get; set; }
        public string Type { get; set; }
        public string OccurrenceOne { get; set; }
        public string OccurrenceTwo { get; set; }
    }
 
    class AttributeSetData
    {
        public string SetName { get; set; }
        public List<AttributeData> Attributes { get; set; }
    }
 
    class AttributeData
    {
        public string Name { get; set; }
        public string Value { get; set; }
    }
}