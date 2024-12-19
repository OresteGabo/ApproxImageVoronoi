#include <QApplication>
#include <QPushButton>
#include "VoronoiWidget.h"
#include <QImage>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString inputFile = "kcc.png";
    QImage image(inputFile);

    VoronoiWidget widget;
    widget.setImage(image);
    widget.calculateVoronoi(inputFile); // Pass the input file name
    widget.resize(image.size());
    widget.show();

    return a.exec();
}