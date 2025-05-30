using System.Collections.Generic;

namespace AssemblyModel
{
    public class AssemblyComponent
    {
        public string Parent { get; set; } // Name of the parent component
        public string Name { get; set; }
        public string DocumentType { get; set; } // e.g., PartDocument or AssemblyDocument
        public double[] TransformMatrix { get; set; } // 12-element array (3x4 matrix)
        public List<SurfaceBodyData> SurfaceBodies { get; set; } = new();
        public List<AssemblyComponent> Children { get; set; } = new();
        public List<AttributeSetData> Attributes { get; set; } = new();
        // public List<ConstraintData> Constraints { get; set; } = new();
        // public List<JointData> Joints { get; set; } = new();

        /* Attributes to add:
            2. AttributeSets
            3. RangeBox
            4. AssemblyConstraints
            5. WorkPoints, WorkAxes, WorkPlanes
            6. IMateResults, IMateDefinitions
        */
    }

    public class SurfaceBodyData
    {
        public string Name { get; set; }
        public List<FaceData> Faces { get; set; } = new();
    }

    public class FaceData
    {
        public string Name { get; set; } // Optional, can be used for identification
        public string SurfaceType { get; set; } // e.g., kPlaneSurface, kCylinderSurface
        public List<EdgeData> Edges { get; set; } = new();
        public List<VertexData> Vertices { get; set; } = new();
    }

    public class EdgeData
    {
        public string GeometryType { get; set; } // e.g., kLineSegmentCurve, kCircleCurve
        public VertexData StartVertex { get; set; }
        public VertexData EndVertex { get; set; }
    }


    public class VertexData
    {
        public double X { get; set; }
        public double Y { get; set; }
        public double Z { get; set; }

        public VertexData() { }

        public VertexData(double x, double y, double z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    }
}
