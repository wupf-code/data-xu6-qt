#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QByteArray>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtDebug>
#include "ods.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_door1_clicked();

    void on_door2_clicked();

    void on_recoveryData_clicked();

    void on_door3_clicked();

    void on_door4_clicked();

    void on_door5_clicked();

    void on_door6_clicked();

    void on_door7_clicked();

    void on_door8_clicked();

    void on_car1_front_fault_clicked();

    void on_car2_door2_fault_clicked();

    void on_control_button_clicked();

private:
    Ui::Widget *ui;
    Ods *ods;
};
#endif // WIDGET_H
