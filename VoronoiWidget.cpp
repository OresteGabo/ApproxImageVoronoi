#include "VoronoiWidget.h"
#include <random>
#include <QFileInfo>
#include <QDebug>

VoronoiWidget::VoronoiWidget(QWidget *parent) : QWidget(parent) {}

void VoronoiWidget::setImage(const QImage &image) {
    originalImage = image;
    voronoiImage = QImage(image.size(), QImage::Format_Grayscale8);
}

void VoronoiWidget::calculateVoronoi(const QString &inputFileName) {
    int width = originalImage.width();
    int height = originalImage.height();

    auto points = generateRandomPoints(10000, width, height); // Plus de points pour éviter les zones noires
    std::vector<int> sums(points.size(), 0);
    std::vector<int> counts(points.size(), 0);
    std::vector<int> regionMap(width * height, -1);

    // Étape 1: Calculer les régions Voronoï et accumuler les niveaux de gris
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int closest = 0;
            int minDist = euclideanDistanceSquared(QPoint(x, y), points[0]);

            for (size_t i = 1; i < points.size(); ++i) {
                int dist = euclideanDistanceSquared(QPoint(x, y), points[i]);
                if (dist < minDist) {
                    closest = i;
                    minDist = dist;
                }
            }

            regionMap[y * width + x] = closest;
            int gray = qGray(originalImage.pixel(x, y));
            sums[closest] += gray;
            counts[closest]++;
        }
    }

    // Étape 2: Appliquer les niveaux de gris moyens pour chaque région
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int region = regionMap[y * width + x];
            if (region != -1 && counts[region] > 0) {
                int avgGray = sums[region] / counts[region];
                voronoiImage.setPixel(x, y, qRgb(avgGray, avgGray, avgGray));
            }
        }
    }

    // Étape 3: Sauvegarder le fichier avec un préfixe "out_"
    QFileInfo fileInfo(inputFileName);
    QString outputFileName = fileInfo.absolutePath() + "/out_" + fileInfo.fileName();
    voronoiImage.save(outputFileName, "PNG");

    qDebug() << "Image Voronoï sauvegardée sous:" << outputFileName;
    update();
}

void VoronoiWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!voronoiImage.isNull()) {
        painter.drawImage(0, 0, voronoiImage);
    }
}

std::vector<QPoint> VoronoiWidget::generateRandomPoints(int n, int width, int height) {
    std::vector<QPoint> points;
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> distX(0, width - 1), distY(0, height - 1);

    for (int i = 0; i < n; ++i) {
        points.emplace_back(distX(gen), distY(gen));
    }
    return points;
}

int VoronoiWidget::euclideanDistanceSquared(const QPoint &a, const QPoint &b) {
    int dx = a.x() - b.x();
    int dy = a.y() - b.y();
    return dx * dx + dy * dy;
}
