// #include "geometry.h"
// namespace fs = filesystem;

// void drawDiagram() {
//     cout << "In what dimensions do you want to draw?" << endl 
//         << "\t 1. 2D" << endl
//         << "\t 2. 3D" << endl;

//     int c = 1; cin >> c;

//     if(c==1) { // 2D diagrams
//         cout <<"What do you want to draw?" << endl
//             << "\t 1. Line" << endl
//             << "\t 2. Rectangle" << endl
//             << "\t 3. Square" << endl
//             << "\t 4. Circle" << endl
//             << "\t 5. Triangle" << endl;

//         cin >> c;
//         switch (c)
//         {
//             case 1:
//                 cout <<"Drawing a line..." << endl;
//                 break;
//             case 2: {
//                 Rectangle rg;
//                 rg.input();
//                 rg.draw();
//                 cout <<"Drawing a rectangle..." << endl;
//                 break;
//             }
//             case 4: {
//                 Circle cir;
//                 cir.input();
//                 cir.draw();
//                 cout << "Drawing a circle..." << endl;
//                 break;
//             }
//             default:
//                 break;
//         }
//     } 
//     else { // 3D diagrams
//         cout <<"What do you want to draw?" << endl
//             << "\t 1. Cuboid" << endl 
//             << "\t 2. Cube" << endl 
//             << "\t 3. Sphere" << endl
//             << "\t 4. Cylinder" << endl
//             << "\t 5. Circle" << endl;
        
//         cin >> c;
//         switch (c)
//         {
//         case 1:
//             cout << "Drawing a cuboid...";
//             break;
//         case 2:
//             cout << "Drawing a cube...";
//             break;
//         case 5: {
//             Circle cir;
//             cir.is3D = true;
//             cir.input();
//             cir.draw();
//             cout << "Drawing a circle...";
//         }
//         default:
//             break;
//         }
//     }
// }

// void listAndDrawSavedFiles(){
//     string dataFolder = "data/";
//     vector<string> datFiles;

//     if (!fs::exists(dataFolder) || !fs::is_directory(dataFolder)) {
//         cout << "No data folder found. No saved .dat files available.\n";
//         return;
//     }

//     cout << "Available .dat files:\n";
//     int index = 1;
//     for (auto& entry : fs::directory_iterator(dataFolder)) {
//         if (entry.path().extension() == ".dat") {
//             datFiles.push_back(entry.path().filename());
//             cout << index++ << ". " << entry.path().filename() << "\n";
//         }
//     }

//     if (datFiles.empty()) {
//         cout << "No .dat files found in the data folder.\n";
//         return;
//     }

//     cout << "Enter the number of the file you want to draw (or 0 to exit): ";
//     int choice;
//     cin >> choice;

//     if (choice > 0 && choice <= datFiles.size()) {
//         string selectedFile = datFiles[choice - 1];
//         cout << "Drawing " << selectedFile << "...\n";

//         // Assuming the file is 3D
//         GnuplotUtils gp;
//         gp.open3D(dataFolder + selectedFile, "Generated Plot");
//     } else {
//         cout << "Invalid selection or exit chosen.\n";
//     }
// }