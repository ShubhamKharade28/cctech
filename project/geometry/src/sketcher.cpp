#include "sketcher.h"

void Sketcher::addShape(std::shared_ptr<Shape> shape) {
    shapes.push_back(shape);
}

vvd Sketcher::getDrawable() {
    vvd combinedDrawable;

    for (size_t i = 0; i < shapes.size(); i++) {
        vvd shapeDrawable = shapes[i]->getDrawable();  // Use -> since shapes[i] is a shared_ptr
        combinedDrawable.insert(combinedDrawable.end(), shapeDrawable.begin(), shapeDrawable.end());

        if (i < shapes.size() - 1) {
            combinedDrawable.push_back({NAN, NAN, NAN});
        }
    }

    return combinedDrawable;
}

void Sketcher::draw(int seconds) {
    vvd dataPoints = getDrawable();
    GnuplotUtils gp;
    gp.draw3D(dataPoints, filename, title);

    if(seconds > 0){
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        system("pkill gnuplot");
    }
}

void Sketcher::setTitle(string title) {
    this->title = title;
}

void Sketcher::setFileName(string filename) {
    this->filename = filename;
}