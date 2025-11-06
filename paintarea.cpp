#include "paintarea.h"
#include <QPainter>

PaintArea::PaintArea(QWidget *parent)
    : QWidget(parent), currentTool(Pencil), penColor(Qt::black), penWidth(2), drawing(false)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    
    image = QImage(size(), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);
    
    tempImage = image;
}

void PaintArea::setTool(Tool newTool)
{
    currentTool = newTool;
}

void PaintArea::setPenColor(const QColor &color)
{
    penColor = color;
}

void PaintArea::setPenWidth(int width)
{
    penWidth = width;
}

bool PaintArea::saveImage(const QString &fileName)
{
    return image.save(fileName);
}

void PaintArea::clearImage()
{
    image.fill(Qt::white);
    tempImage.fill(Qt::white);
    update();
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.drawImage(0, 0, image);

    if (drawing) {
        painter.drawImage(0, 0, tempImage);
    }
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        startPoint = event->pos();
        lastPoint = startPoint;
        endPoint = startPoint;
        
        tempImage = image; 
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        endPoint = event->pos();
        
        if (currentTool == Pencil) {
            QPainter painter(&image);
            painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, endPoint);
            lastPoint = endPoint;
            update();
        } else {
            tempImage = image; 
            QPainter painter(&tempImage);
            painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            
            switch (currentTool) {
            case Line:
                painter.drawLine(startPoint, endPoint);
                break;
            case Rectangle:
                painter.drawRect(QRect(startPoint, endPoint));
                break;
            case Ellipse:
                painter.drawEllipse(QRect(startPoint, endPoint));
                break;
            default:
                break;
            }
            update();
        }
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        
        if (currentTool != Pencil) {
            QPainter painter(&image);
            painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            
            switch (currentTool) {
            case Line:
                painter.drawLine(startPoint, endPoint);
                break;
            case Rectangle:
                painter.drawRect(QRect(startPoint, endPoint));
                break;
            case Ellipse:
                painter.drawEllipse(QRect(startPoint, endPoint));
                break;
            default:
                break;
            }
            
            tempImage = image;
            update();
        }
    }
}

void PaintArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        resizeImage(&tempImage, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void PaintArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;
    
    QImage newImage(newSize, QImage::Format_ARGB32_Premultiplied);
    newImage.fill(Qt::white);
    
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
