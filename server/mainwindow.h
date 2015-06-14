#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dispatcher.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    Dispatcher dispatcher;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void turnOn();
    void turnOff();
    void changeColor();
};

#endif // MAINWINDOW_H
