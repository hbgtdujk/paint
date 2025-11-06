#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    image(800, 600, QImage::Format_ARGB32_Premultiplied),
    penColor(Qt::black),
    drawing(false)
{
    image.fill(Qt::white);
}

void Canvas::setPenColor(const QColor &color)
{
    penColor = color;
}

void Canvas::clear()
{
    image.fill(Qt::white);
    update();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPainter painter(&image);
        QPen pen(penColor, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}
