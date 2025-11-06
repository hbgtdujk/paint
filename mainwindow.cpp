#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentColor(Qt::black)
{
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    
    paintArea = new PaintArea(this);
    mainLayout->addWidget(paintArea);
    
    toolLayout = new QHBoxLayout();
    
    toolGroup = new QButtonGroup(this);
    toolGroup->setExclusive(true);
    
    pencilButton = new QPushButton("Карандаш", this);
    lineButton = new QPushButton("Линия", this);
    rectangleButton = new QPushButton("Прямоугольник", this);
    ellipseButton = new QPushButton("Эллипс", this);
    
    pencilButton->setCheckable(true);
    lineButton->setCheckable(true);
    rectangleButton->setCheckable(true);
    ellipseButton->setCheckable(true);
    
    pencilButton->setChecked(true); 
    
    toolGroup->addButton(pencilButton, PaintArea::Pencil);
    toolGroup->addButton(lineButton, PaintArea::Line);
    toolGroup->addButton(rectangleButton, PaintArea::Rectangle);
    toolGroup->addButton(ellipseButton, PaintArea::Ellipse);
    
    toolLayout->addWidget(pencilButton);
    toolLayout->addWidget(lineButton);
    toolLayout->addWidget(rectangleButton);
    toolLayout->addWidget(ellipseButton);
    
    mainLayout->addLayout(toolLayout);
    
    controlLayout = new QHBoxLayout();
    
    colorButton = new QPushButton("Выбрать цвет", this);
    saveButton = new QPushButton("Сохранить", this);
    clearButton = new QPushButton("Очистить", this);
    
    colorLabel = new QLabel(this);
    colorLabel->setFixedSize(30, 30);
    colorLabel->setStyleSheet("background-color: black; border: 1px solid gray;");
    
    penWidthSpinBox = new QSpinBox(this);
    penWidthSpinBox->setRange(1, 20);
    penWidthSpinBox->setValue(2);
    penWidthSpinBox->setPrefix("Толщина: ");
    penWidthSpinBox->setSuffix(" px");
    
    controlLayout->addWidget(colorButton);
    controlLayout->addWidget(colorLabel);
    controlLayout->addWidget(penWidthSpinBox);
    controlLayout->addWidget(saveButton);
    controlLayout->addWidget(clearButton);
    controlLayout->addStretch();
    
    mainLayout->addLayout(controlLayout);
    
    connect(toolGroup, SIGNAL(buttonClicked(int)), this, SLOT(onToolChanged(int)));
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(penWidthSpinBox, SIGNAL(valueChanged(int)), paintArea, SLOT(setPenWidth(int)));
    
    paintArea->setTool(PaintArea::Pencil);
    paintArea->setPenColor(currentColor);
    paintArea->setPenWidth(penWidthSpinBox->value());
    
    setWindowTitle("Painter Qt");
    resize(800, 600);
}

void MainWindow::onColorButtonClicked()
{
    QColor newColor = QColorDialog::getColor(currentColor, this, "Выберите цвет");
    if (newColor.isValid()) {
        currentColor = newColor;
        colorLabel->setStyleSheet(QString("background-color: %1; border: 1px solid gray;").arg(currentColor.name()));
        paintArea->setPenColor(currentColor);
    }
}

void MainWindow::onSaveButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить рисунок", "", "PNG Files (*.png);;JPEG Files (*.jpg *.jpeg);;All Files (*)");
    if (!fileName.isEmpty()) {
        if (paintArea->saveImage(fileName)) {
            QMessageBox::information(this, "Успех", "Рисунок успешно сохранен!");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить рисунок!");
        }
    }
}

void MainWindow::onClearButtonClicked()
{
    paintArea->clearImage();
}

void MainWindow::onToolChanged(int tool)
{
    paintArea->setTool(static_cast<PaintArea::Tool>(tool));
}
