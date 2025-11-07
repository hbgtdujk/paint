#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QImage>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);

    void setPenColor(const QColor &color);
    void clear();
    void setEraserMode(bool enabled);
    void setDrawMode();
    void setBrushSize(int size);
    void saveToFile(const QString &filePath); // 🔹 новый метод сохранения
    enum ToolType { Pen, Line, Rectangle, Ellipse, Eraser };
    void setTool(ToolType tool);
    ToolType tool() const { return currentTool; }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QImage image;
    QImage tempImage;
    QPoint lastPoint;
    QPoint startPoint;
    QColor penColor;
    QColor lastPenColor;
    bool drawing;
    bool eraserMode = false;
    ToolType currentTool = Pen;

    // 🔹 Для визуализации кисти
    QPoint cursorPos;
    bool showBrush = false;
    int brushSize = 3;
};

#endif // CANVAS_H
