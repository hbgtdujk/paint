#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnColor, &QPushButton::clicked, this, [this]() {
        QColor color = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
        if (color.isValid())
            ui->canvas->setPenColor(color);
    });

    connect(ui->btnClear, &QPushButton::clicked, this, [this]() {
        ui->canvas->clear();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
