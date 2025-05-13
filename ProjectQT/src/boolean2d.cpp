#include "boolean2d.h"
using namespace std;

#include "sketcher.h"

bool Boolean2D::edgesIntersect(pdd& a1, pdd& a2,
                    pdd& b1, pdd& b2) {
    auto cross = [](double x1, double y1, double x2, double y2) {
        return x1 * y2 - y1 * x2;
    };

    double dx1 = a2.first - a1.first, dy1 = a2.second - a1.second;
    double dx2 = b2.first - b1.first, dy2 = b2.second - b1.second;

    double delta = cross(dx1, dy1, dx2, dy2);
    if (abs(delta) < 1e-8) return false; // Parallel lines

    double s = cross(b1.first - a1.first, b1.second - a1.second, dx2, dy2) / delta;
    double t = cross(b1.first - a1.first, b1.second - a1.second, dx1, dy1) / delta;

    return (s >= 0 && s <= 1 && t >= 0 && t <= 1);
}

vector<pdd> Boolean2D::getIntersectingPoints(vector<pdd>& polyA,
                                                    vector<pdd>& polyB) {
    vector<pdd> intersections;
    for (size_t i = 0; i < polyA.size(); ++i) {
        auto a1 = polyA[i];
        auto a2 = polyA[(i + 1) % polyA.size()];

        for (size_t j = 0; j < polyB.size(); ++j) {
            auto b1 = polyB[j];
            auto b2 = polyB[(j + 1) % polyB.size()];

            if (edgesIntersect(a1, a2, b1, b2)) {
                // Use line-line intersection formula
                double A1 = a2.second - a1.second;
                double B1 = a1.first - a2.first;
                double C1 = A1 * a1.first + B1 * a1.second;

                double A2 = b2.second - b1.second;
                double B2 = b1.first - b2.first;
                double C2 = A2 * b1.first + B2 * b1.second;

                double det = A1 * B2 - A2 * B1;
                if (abs(det) < 1e-8) continue; // Lines are parallel

                double x = (B2 * C1 - B1 * C2) / det;
                double y = (A1 * C2 - A2 * C1) / det;

                intersections.emplace_back(x, y);
            }
        }
    }
    return intersections;
}

/*
vector<pdd> findPath(
    vector<pdd>& polygon,
    pdd& start,
    pdd& end)
{
    vector<pdd> path;
    int startIndex = -1, endIndex = -1;

    // Include the start and end in the polygon temporarily
    vector<pdd> extended = polygon;

    // Append start and end if not present
    auto isClose = [](const pdd& a, const pdd& b) {
        return abs(a.first - b.first) < 1e-6 && abs(a.second - b.second) < 1e-6;
    };

    // Find start and end indices (insert them if they lie on an edge)
    for (size_t i = 0; i < extended.size(); ++i) {
        if (isClose(extended[i], start)) startIndex = i;
        if (isClose(extended[i], end)) endIndex = i;
    }

    if (startIndex == -1 || endIndex == -1) {
        // This implies start or end is not a vertex but lies on an edge
        // You should insert them by splitting the edge they belong to
        throw runtime_error("Start or end point not found in polygon — edge splitting not implemented yet.");
    }

    // Walk from startIndex to endIndex (wrap-around)
    int i = startIndex;
    while (true) {
        path.push_back(extended[i]);
        if (i == endIndex)
            break;
        i = (i + 1) % extended.size();
    }

    return path;
}
*/

map<string, vector<pdd>> Boolean2D::getBooleanPaths(
    vector<pdd>& polyA,
    vector<pdd>& polyB,
    vector<pdd>& intersectPoints) {

    pdd ip1 = intersectPoints[0];
    pdd ip2 = intersectPoints[1];

    auto insertPointOnEdge = [](vector<pdd>& poly, const pdd& pt) {
        auto isClose = [](const pdd& a, const pdd& b) {
            return std::abs(a.first - b.first) < 1e-8 && std::abs(a.second - b.second) < 1e-8;
        };
        // If already present, do nothing
        for (const auto& v : poly) if (isClose(v, pt)) return;
        // Try to insert between the correct edge
        for (size_t i = 0; i < poly.size(); ++i) {
            pdd a = poly[i];
            pdd b = poly[(i + 1) % poly.size()];
            // Check if pt is on segment ab
            double cross = (b.first - a.first) * (pt.second - a.second) - (b.second - a.second) * (pt.first - a.first);
            double dot = (pt.first - a.first) * (b.first - a.first) + (pt.second - a.second) * (b.second - a.second);
            double len_sq = (b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second);
            if (std::abs(cross) < 1e-8 && dot >= 0 && dot <= len_sq) {
                poly.insert(poly.begin() + i + 1, pt);
                return;
            }
        }
    };

    insertPointOnEdge(polyA, ip1);
    insertPointOnEdge(polyA, ip2);
    insertPointOnEdge(polyB, ip1);
    insertPointOnEdge(polyB, ip2);

    auto findPath = [](vector<pdd>& poly, pdd from, pdd to) {
        vector<pdd> result;
        auto it = find(poly.begin(), poly.end(), from);
        if (it == poly.end()) return result;

        size_t idx = distance(poly.begin(), it);
        result.push_back(from);
        while (true) {
            idx = (idx + 1) % poly.size();
            result.push_back(poly[idx]);
            if (poly[idx] == to) break;
        }
        return result;
    };

    vector<pdd> A = findPath(polyA, ip2, ip1);
    vector<pdd> B = findPath(polyB, ip1, ip2);
    vector<pdd> C = findPath(polyB, ip2, ip1);
    vector<pdd> D = findPath(polyA, ip1, ip2);

    return { {"A", A}, {"B", B}, {"C", C}, {"D", D} };
}

vector<pdd> Boolean2D::combine(vector<pdd> path1, vector<pdd> path2)
{
    if (path1.empty()) return path2;
    if (path2.empty()) return path1;

    if (path1.back() == path2.front()) {}
    else if (path1.back() == path2.back()) reverse(path2.begin(), path2.end());
    else if (path1.front() == path2.front()) reverse(path1.begin(), path1.end());
    else if (path1.front() == path2.back()) {
        reverse(path1.begin(), path1.end());
        reverse(path2.begin(), path2.end());
    }

    path1.insert(path1.end(), path2.begin() + 1, path2.end());
    return path1;
}

Face* Boolean2D::perform(Face* faceA, Face* faceB, BooleanType op, Sketcher* sketcher = nullptr) {
    switch (op) {
        case BooleanType::Union:
            return unify(faceA, faceB, sketcher);
        case BooleanType::Intersection:
            return intersect(faceA, faceB, sketcher);
        case BooleanType::Difference:
            return difference(faceA, faceB, sketcher);
        default:
            return nullptr;
    }
}

Face* Boolean2D::intersect(Face* faceA, Face* faceB, Sketcher* sketcher) {
    auto polyA = to2DPolygon(faceA);
    auto polyB = to2DPolygon(faceB);

    vector<pdd> intersections = getIntersectingPoints(polyA, polyB);
    if(intersections.size() < 2) return nullptr;
    
    auto booleanPaths = getBooleanPaths(polyA, polyB, intersections);

    vector<pdd> intersectionPolygon = combine(booleanPaths["C"], booleanPaths["D"]);

    return from2DPolygon(intersectionPolygon, sketcher);
}

Face* Boolean2D::difference(Face* faceA, Face* faceB, Sketcher* sketcher) {
    auto polyA = to2DPolygon(faceA);
    auto polyB = to2DPolygon(faceB);

    vector<pdd> intersections = getIntersectingPoints(polyA, polyB);
    if(intersections.size() < 2) return nullptr;
    
    auto booleanPaths = getBooleanPaths(polyA, polyB, intersections);

    vector<pdd> differencePolygon = combine(booleanPaths["A"], booleanPaths["C"]);
    return from2DPolygon(differencePolygon, sketcher);
}

Face* Boolean2D::unify(Face* faceA, Face* faceB, Sketcher* sketcher) {
    auto polyA = to2DPolygon(faceA);
    auto polyB = to2DPolygon(faceB);

    vector<pdd> intersections = getIntersectingPoints(polyA, polyB);
    if(intersections.size() < 2) return nullptr;
    
    auto booleanPaths = getBooleanPaths(polyA, polyB, intersections);

    vector<pdd> unionPolygon = combine(booleanPaths["A"], booleanPaths["B"]);
    return from2DPolygon(unionPolygon, sketcher);
}

vector<pdd> Boolean2D::to2DPolygon(Face* face) {
    vector<pdd> polygon;
    for (Vertex* v : face->getVertices()) {
        polygon.emplace_back(v->getX(), v->getY());
    }
    return polygon;
}

Face* Boolean2D::from2DPolygon(vector<pdd>& polygon, Sketcher* sketcher) {
    if (polygon.size() < 3) return nullptr;

    vector<Vertex*> vertices;
    vector<Edge*> edges;

    for (auto& p : polygon) {
        Vertex* v = sketcher->addVertex(p.first, p.second, 0.0); // z = 0
        vertices.push_back(v);
    }

    for (size_t i = 0; i < vertices.size(); ++i) {
        Vertex* start = vertices[i];
        Vertex* end = vertices[(i + 1) % vertices.size()];
        Edge* e = sketcher->addEdge(start, end);
        edges.push_back(e);
    }

    Face* f = sketcher->addFace(edges);
    return f;
}