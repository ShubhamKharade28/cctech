#include "threed-utils.h"
#include "shape.h"

class FileUtils {
public:
    // Read methods
    static StlShape readSTL(string& filename);
    static StlShape readDAT(string& filename);
    static StlShape readOBJ(string& filename);

    // Write methods
    static void writeSTL(string& filename, StlShape& triangles);
    static void writeDAT(string& filename, StlShape& triangles);
    static void writeOBJ(string& filename, StlShape& triangles);

    // Conversion methods
    static void stlToDat(string& stlFile, string& datFile);
    static void datToStl(string& datFile, string& stlFile);
    static void stlToObj(string& stlFile, string& objFile);
    static void objToStl(string& objFile, string& stlFile);
    static void datToObj(string& datFile, string& objFile);
    static void objToDat(string& objFile, string& datFile);

    static void exportSTL(Shape* shape, string filename);
    static void exportOBJ(Shape* shape, string filename);
};