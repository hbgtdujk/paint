#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QColorDialog>
#include <QSpinBox>
#include <QFileDialog>
#include <QMessageBox>

#include "paintarea.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onColorButtonClicked();
    void onSaveButtonClicked();
    void onClearButtonClicked();
    void onToolChanged(int tool);

private:
    void setupUI();

    PaintArea *paintArea;
    
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *toolLayout;
    QHBoxLayout *controlLayout;
    
    QButtonGroup *toolGroup;
    QPushButton *pencilButton;
    QPushButton *lineButton;
    QPushButton *rectangleButton;
    QPushButton *ellipseButton;
    
    QPushButton *colorButton;
    QPushButton *saveButton;
    QPushButton *clearButton;
    
    QSpinBox *penWidthSpinBox;
    QLabel *colorLabel;
    
    QColor currentColor;
};

#endif // MAINWINDOW_H
