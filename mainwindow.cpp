#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include <QColorDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 🎨 Выбор цвета
    connect(ui->btnColor, &QPushButton::clicked, this, [this]() {
        QColor color = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
        if (color.isValid()) {
            ui->canvas->setPenColor(color);
            ui->canvas->setTool(Canvas::Pen);
        }
    });

    // 🧽 Очистка
    connect(ui->btnClear, &QPushButton::clicked, this, [this]() {
        ui->canvas->clear();
    });

    // ✏️ Карандаш
    connect(ui->btnPen, &QPushButton::clicked, this, [this]() {
        ui->canvas->setTool(Canvas::Pen);
    });

    // 🩹 Ластик
    connect(ui->btnEraser, &QPushButton::clicked, this, [this]() {
        ui->canvas->setTool(Canvas::Eraser);
    });

    // ➖ Линия
    connect(ui->btnLine, &QPushButton::clicked, this, [this]() {
        ui->canvas->setTool(Canvas::Line);
    });

    // ⬜ Прямоугольник
    connect(ui->btnRec, &QPushButton::clicked, this, [this]() {
        ui->canvas->setTool(Canvas::Rectangle);
    });

    // ⚪ Эллипс
    connect(ui->btnEll, &QPushButton::clicked, this, [this]() {
        ui->canvas->setTool(Canvas::Ellipse);
    });

    // 💾 Сохранить в PNG
    connect(ui->btnSave, &QPushButton::clicked, this, [this]() {
        QString filePath = QFileDialog::getSaveFileName(this, "Сохранить изображение", "", "PNG файлы (*.png)");
        if (!filePath.isEmpty()) {
            if (!filePath.endsWith(".png"))
                filePath += ".png";
            ui->canvas->saveToFile(filePath);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
