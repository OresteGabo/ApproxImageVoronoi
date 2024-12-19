//
// Created by oreste on 18/12/24.
//

#ifndef APPROXIMAGEVORONOI_VORONOIWIDGET_H
#define APPROXIMAGEVORONOI_VORONOIWIDGET_H


#include <QWidget>
#include <QImage>
#include <QPainter>
#include <vector>
#include <QString>
#include <QDebug>
class VoronoiWidget : public QWidget {
Q_OBJECT

public:
    explicit VoronoiWidget(QWidget *parent = nullptr);
    void setImage(const QImage &image);
    void calculateVoronoi(const QString &inputFileName);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage originalImage;
    QImage voronoiImage;

    std::vector<QPoint> generateRandomPoints(int n, int width, int height);
    int euclideanDistanceSquared(const QPoint &a, const QPoint &b);
};





#endif //APPROXIMAGEVORONOI_VORONOIWIDGET_H
