#include "canvas.h"
#include <QFileDialog>
#include <QMessageBox>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    image(800, 600, QImage::Format_ARGB32_Premultiplied),
    penColor(Qt::black),
    lastPenColor(Qt::black),
    drawing(false)
{
    image.fill(Qt::white);
    setMouseTracking(true);
}

void Canvas::setPenColor(const QColor &color)
{
    penColor = color;
    lastPenColor = color;
}

void Canvas::clear()
{
    image.fill(Qt::white);
    update();
}

void Canvas::setEraserMode(bool enabled)
{
    eraserMode = enabled;
    if (enabled)
        penColor = Qt::white;
}

void Canvas::setDrawMode()
{
    eraserMode = false;
    penColor = lastPenColor;
}

void Canvas::setBrushSize(int size)
{
    brushSize = size;
}

void Canvas::setTool(ToolType tool)
{
    currentTool = tool;
    if (tool == Eraser) {
        setEraserMode(true);
    } else {
        setDrawMode();
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        lastPoint = startPoint;
        drawing = true;
        tempImage = image;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    cursorPos = event->pos();

    if ((event->buttons() & Qt::LeftButton) && drawing) {
        if (currentTool == Pen || currentTool == Eraser) {
            QPainter painter(&image);
            if (currentTool == Eraser) {
                painter.setCompositionMode(QPainter::CompositionMode_Clear); // 🔹 Реальное стирание
            }
            QPen pen(penColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
            painter.setPen(pen);
            painter.drawLine(lastPoint, event->pos());
            lastPoint = event->pos();
        } else {
            image = tempImage;
            QPainter painter(&image);
            QPen pen(penColor, brushSize);
            painter.setPen(pen);
            QRect rect(startPoint, event->pos());

            switch (currentTool) {
            case Line:
                painter.drawLine(startPoint, event->pos());
                break;
            case Rectangle:
                painter.drawRect(rect);
                break;
            case Ellipse:
                painter.drawEllipse(rect);
                break;
            default:
                break;
            }
        }
    }
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        drawing = false;
}

void Canvas::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);
    showBrush = true;
    update();
}

void Canvas::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    showBrush = false;
    update();
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);

    if (showBrush) {
        QPen brushOutline(Qt::gray);
        brushOutline.setWidth(1);
        painter.setPen(brushOutline);
        QColor fill = eraserMode ? QColor(255, 255, 255, 120)
                                 : QColor(penColor.red(), penColor.green(), penColor.blue(), 60);
        painter.setBrush(fill);
        painter.drawEllipse(cursorPos, brushSize / 2, brushSize / 2);
    }
}

// 🖼 Сохранение холста в PNG
void Canvas::saveToFile(const QString &filePath)
{
    if (!image.save(filePath, "PNG")) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить изображение!");
    }
}
