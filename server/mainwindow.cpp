#include "mainwindow.h"
#include <QPushButton>
#include <QColorDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *turnOnButton = new QPushButton("Turn On");
    QPushButton *turnOffButton = new QPushButton("Turn Off");
    QPushButton *changeColorButton = new QPushButton("Change Color");

    connect(turnOnButton, SIGNAL(released()), this, SLOT(turnOn()));
    connect(turnOffButton, SIGNAL(released()), this, SLOT(turnOff()));
    connect(changeColorButton, SIGNAL(released()), this, SLOT(changeColor()));

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(turnOnButton);
    vbox->addWidget(turnOffButton);
    vbox->addWidget(changeColorButton);

    this->setLayout(vbox);

    this->setMinimumWidth(200);
}

MainWindow::~MainWindow()
{

}

void MainWindow::turnOn()
{
    dispatcher.sendData(Command::ON);
}

void MainWindow::turnOff()
{
    dispatcher.sendData(Command::OFF);
}

void MainWindow::changeColor()
{
    const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color");

    if (color.isValid()) {

        RGB rgb;
        rgb.red = color.red();
        rgb.green = color.green();
        rgb.blue = color.blue();

        QByteArray buffer;
        buffer.append(reinterpret_cast<char*>(&rgb), sizeof(RGB));

        dispatcher.sendData(Command::COLOR, buffer);
    }
}
