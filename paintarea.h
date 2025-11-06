#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QPoint>

class PaintArea : public QWidget
{
    Q_OBJECT

public:
    enum Tool {
        Pencil,
        Line,
        Rectangle,
        Ellipse
    };

    explicit PaintArea(QWidget *parent = nullptr);
    
    void setTool(Tool newTool);
    void setPenColor(const QColor &color);
    void setPenWidth(int width);
    
    bool saveImage(const QString &fileName);
    void clearImage();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawShapeToImage();
    void resizeImage(QImage *image, const QSize &newSize);

    QImage image;
    QImage tempImage;
    
    Tool currentTool;
    QColor penColor;
    int penWidth;
    
    bool drawing;
    QPoint startPoint;
    QPoint endPoint;
    
    QPoint lastPoint;
};

#endif // PAINTAREA_H
