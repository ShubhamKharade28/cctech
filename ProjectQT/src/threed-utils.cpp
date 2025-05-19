#include "threed-utils.h"
#include <QDebug>

Vector substract(Vector a, Vector b){
    return {a[0]-b[0], a[1]-b[1], a[2]-b[2]};
}

Vector cross(Vector a, Vector b){
    return {
        a[1]*b[2] - a[2]*b[1],
        a[2]*b[0] - a[0]*b[2],
        a[0]*b[1] - a[1]*b[0]
    };
}

double magnitude(Vector v) {
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

Vector normalize(Vector v) {
    double mag = magnitude(v);
    if (mag == 0) return {0, 0, 0}; // avoid division by zero
    return {v[0]/mag, v[1]/mag, v[2]/mag};
}

Vector Triangle::getNormal() {
    return computeNormal(vertex1, vertex2, vertex3);
}

Triangle::Triangle(Vector n, Vector v1, Vector v2, Vector v3): 
    normal(n), vertex1(v1), vertex2(v2), vertex3(v3) {}

Triangle::Triangle(Vector v1, Vector v2, Vector v3): vertex1(v1), vertex2(v2), vertex3(v3) {
    this->normal = getNormal();
}

double dot(Vector a, Vector b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

bool computePlaneIntersectionPoint(
    const Vector& n1, double d1,
    const Vector& n2, double d2,
    const Vector& dir,
    Vector& p0
) {
    // Create a matrix with rows: n1, n2, dir
    // Solve: [n1^T; n2^T; dir^T] * p = [-d1, -d2, 0]

    double A[3][3] = {
        {n1[0], n1[1], n1[2]},
        {n2[0], n2[1], n2[2]},
        {dir[0], dir[1], dir[2]}
    };

    double b[3] = {-d1, -d2, 0};

    // Use Cramer's Rule to solve A * p = b
    auto det = [](double m[3][3]) {
        return m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1]) -
               m[0][1]*(m[1][0]*m[2][2] - m[1][2]*m[2][0]) +
               m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
    };

    double detA = det(A);
    if (fabs(detA) < 1e-8) return false;  // Degenerate system

    // Replace column 0 with b to get detX
    double Ax[3][3] = {
        {b[0], A[0][1], A[0][2]},
        {b[1], A[1][1], A[1][2]},
        {b[2], A[2][1], A[2][2]}
    };

    double Ay[3][3] = {
        {A[0][0], b[0], A[0][2]},
        {A[1][0], b[1], A[1][2]},
        {A[2][0], b[2], A[2][2]}
    };

    double Az[3][3] = {
        {A[0][0], A[0][1], b[0]},
        {A[1][0], A[1][1], b[1]},
        {A[2][0], A[2][1], b[2]}
    };

    double x = det(Ax) / detA;
    double y = det(Ay) / detA;
    double z = det(Az) / detA;

    p0 = {x, y, z};
    return true;
}

optional<Line> clipTriangleToLine(const Triangle& tri, const Vector& p0, const Vector& dir) {
    std::vector<Vector> points;

    auto intersectEdge = [&](const Vector& a, const Vector& b) -> std::optional<Vector> {
        Vector ab = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };
        Vector ap0 = { p0[0] - a[0], p0[1] - a[1], p0[2] - a[2] };

        Vector cross_ab_dir = cross(ab, dir);
        if (magnitude(cross_ab_dir) < 1e-8) return std::nullopt; // Parallel

        // Solve a + t*(b - a) = p0 + s*dir
        // Reduce to 2D system by projecting to dominant plane

        int i = 0;
        if (std::abs(dir[1]) > std::abs(dir[i])) i = 1;
        if (std::abs(dir[2]) > std::abs(dir[i])) i = 2;
        int i1 = (i + 1) % 3, i2 = (i + 2) % 3;

        double dx1 = ab[i1], dy1 = ab[i2];
        double dx2 = -dir[i1], dy2 = -dir[i2];
        double dx = p0[i1] - a[i1], dy = p0[i2] - a[i2];

        double det = dx1 * dy2 - dx2 * dy1;
        if (std::fabs(det) < 1e-8) return std::nullopt;

        double t = (dx * dy2 - dy * dx2) / det;

        if (t < 0.0 || t > 1.0) return std::nullopt; // Not on edge

        Vector pt = {
            a[0] + t * ab[0],
            a[1] + t * ab[1],
            a[2] + t * ab[2]
        };
        return pt;
    };

    // Check each edge
    optional<Vector> i1 = intersectEdge(tri.vertex1, tri.vertex2);
    optional<Vector> i2 = intersectEdge(tri.vertex2, tri.vertex3);
    optional<Vector> i3 = intersectEdge(tri.vertex3, tri.vertex1);

    if (i1) points.push_back(*i1);
    if (i2) points.push_back(*i2);
    if (i3) points.push_back(*i3);

    // Remove duplicates if any
    auto isClose = [](const Vector& a, const Vector& b) {
        return std::sqrt(
            (a[0]-b[0])*(a[0]-b[0]) +
            (a[1]-b[1])*(a[1]-b[1]) +
            (a[2]-b[2])*(a[2]-b[2])
        ) < 1e-6;
    };

    if (points.size() >= 2) {
        if (isClose(points[0], points[1])) return std::nullopt;
        return Line{ points[0], points[1] };
    }

    return std::nullopt;
}

std::optional<Line> segmentOverlap(Line seg1, Line seg2) {
    const Vector& p1 = seg1.first;
    const Vector& p2 = seg1.second;
    const Vector& q1 = seg2.first;
    const Vector& q2 = seg2.second;

    // Compute direction of the shared line
    Vector dir = {
        p2[0] - p1[0],
        p2[1] - p1[1],
        p2[2] - p1[2]
    };

    double len = magnitude(dir);
    if (len < 1e-8) return std::nullopt; // degenerate segment

    for (int i = 0; i < 3; ++i) dir[i] /= len; // normalize

    // Project onto the line using dot products
    auto project = [&](const Vector& pt) {
        Vector diff = { pt[0] - p1[0], pt[1] - p1[1], pt[2] - p1[2] };
        return dot(diff, dir); // scalar t
    };

    double t1 = 0.0;
    double t2 = len;
    double s1 = project(q1);
    double s2 = project(q2);

    // Sort scalar ranges
    if (t1 > t2) std::swap(t1, t2);
    if (s1 > s2) std::swap(s1, s2);

    double overlap_min = std::max(t1, s1);
    double overlap_max = std::min(t2, s2);

    if (overlap_min >= overlap_max) return std::nullopt; // no overlap

    // Compute actual points on the line
    Vector p0 = p1;
    Vector start = {
        p0[0] + overlap_min * dir[0],
        p0[1] + overlap_min * dir[1],
        p0[2] + overlap_min * dir[2]
    };
    Vector end = {
        p0[0] + overlap_max * dir[0],
        p0[1] + overlap_max * dir[1],
        p0[2] + overlap_max * dir[2]
    };

    return Line{start, end};
}

optional<Line> getIntersection(Triangle& t1, Triangle& t2) {
    Vector n1 = t1.getNormal();
    Vector n2 = t2.getNormal();

    Vector dir = cross(n1, n2);

    qDebug() << "Magnitude of dir: " << magnitude(dir);
    // Check if the planes are parallel
    if (magnitude(dir) < 1e-6) {
        qDebug() << "Planes are parallel";
        return std::nullopt;  // Planes are parallel
    } 

    // Plane equations
    double d1 = -dot(n1, t1.vertex1);
    double d2 = -dot(n2, t2.vertex1);

    // Find a point on the line of intersection between the two planes
    Vector p0;
    if (!computePlaneIntersectionPoint(n1, d1, n2, d2, dir, p0)){
        qDebug() << "No reliable intersection point between planes.";
        return std::nullopt;  // No reliable intersection point
    }

    // Define line: L(t) = p0 + t * dir
    optional<Line> seg1 = clipTriangleToLine(t1, p0, dir);
    optional<Line> seg2 = clipTriangleToLine(t2, p0, dir);
    if (!seg1.has_value() || !seg2.has_value()) return std::nullopt;

    auto overlap = segmentOverlap(seg1.value(), seg2.value());
    if(overlap.has_value()) {
        qDebug() << "Overlap found!";
    }
    qDebug() << "No overlap found.";
    return overlap;
}

vector<Line> getIntersections(StlShape& shape1, StlShape& shape2) {
    vector<Line> intersections;
    qDebug() << "Finding intersections...";
    qDebug() << "Shape 1 size: " << shape1.size();
    qDebug() << "Shape 2 size: " << shape2.size();

    for(Triangle& t1 : shape1) {
        for(Triangle& t2 : shape2) {
            optional<Line> intersection = getIntersection(t1, t2);
            if(intersection.has_value()) {
                qDebug() << "Intersection found!";
                intersections.push_back(intersection.value());
            }
        }
    }

    return intersections;
}

/*
// Sakshi's code:
bool trianglesCoplanar(Triangle& t1, Triangle& t2) {
    // Plane normal for t1
    Vector n1 = cross(substract(t1.vertex2, t1.vertex1), substract(t1.vertex3, t1.vertex1));
    double d1 = -dot(n1, t1.vertex1);
    // Check all points of t2 in t1's plane
    double dist1 = dot(n1, t2.vertex1) + d1;
    double dist2 = dot(n1, t2.vertex2) + d1;
    double dist3 = dot(n1, t2.vertex3) + d1;
    double eps = 1e-5f;
    return (fabs(dist1) < eps && fabs(dist2) < eps && fabs(dist3) < eps);
}

// Compute intersection segment of two triangles in 3D (returns true if intersect, and sets segA, segB)
bool triangleTriangleIntersectionSegment(const Triangle& t1, const Triangle& t2, Vector& segA, Vector& segB) {
    // Möller–Trumbore style: test all edges of t1 against t2 and vice versa
    // Collect intersection points
    std::vector<Vector> isects;
    auto segmentIntersectTriangle = [](const Vector& p0, const Vector& p1, const Triangle& tri, Vector& isect) -> bool {
        // Plane of triangle
        Vector u = substract(tri.vertex2, tri.vertex1);
        Vector v = substract(tri.vertex3, tri.vertex1);
        Vector n = cross(u, v);
        if (n.x == 0 && n.y == 0 && n.z == 0) return false; // degenerate

        Vector dir = substract(p1, p0);
        double denom = dot(n, dir);
        if (fabs(denom) < 1e-6f) return false; // parallel

        double t = (dot(n, substract(tri.vertex1, p0))) / denom;
        if (t < 0.0f || t > 1.0f) return false; // not within segment

        Vector P = Vector{p0.x + t*dir.x, p0.y + t*dir.y, p0.z + t*dir.z};

        // Inside-triangle test (barycentric)
        Vector w = substract(P, tri.p1);
        double uu = dot(u, u), uv = dot(u, v), vv = dot(v, v);
        double wu = dot(w, u), wv = dot(w, v);
        double D = uv * uv - uu * vv;
        double s = (uv * wv - vv * wu) / D;
        double t2 = (uv * wu - uu * wv) / D;
        if (s >= -1e-5f && t2 >= -1e-5f && (s + t2) <= 1.0f + 1e-5f) {
            isect = P;
            return true;
        }
        return false;
    };

    // t1 edges vs t2
    const Vector* t1_pts[3] = { &t1.p1, &t1.p2, &t1.p3 };
    for (int i = 0; i < 3; ++i) {
        Vector isect;
        if (segmentIntersectTriangle(*t1_pts[i], *t1_pts[(i+1)%3], t2, isect))
            isects.push_back(isect);
    }

    // t2 edges vs t1
    const Vector* t2_pts[3] = { &t2.p1, &t2.p2, &t2.p3 };
    for (int i = 0; i < 3; ++i) {
        Vector isect;
        if (segmentIntersectTriangle(*t2_pts[i], *t2_pts[(i+1)%3], t1, isect))
            isects.push_back(isect);
    }

    // Remove duplicates (within epsilon)
    double eps = 1e-5f;
    auto same = [eps](const Vector& a, const Vector& b) {
        return fabs(a[0]-b[0])<eps && fabs(a[1]-b[1])<eps && fabs(a[2]-b[2])<eps;
    };

    vector<Vector> unique;
    for (const auto& p : isects) {
        bool found = false;
        for (const auto& q : unique) if (same(p, q)) { found = true; break; }
        if (!found) unique.push_back(p);
    }

    if (unique.size() == 2) {
        segA = unique[0];
        segB = unique[1];
        return true;
    }
    return false;
}
    */

    