#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QByteArray>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtDebug>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    quint16 calculateCRC(const QByteArray &data);
    ~Widget();

private slots:
    void handleReadyRead();

    void sendData();

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
    QByteArray data;
    QSerialPort serialPort;
    quint16 count = 0;
    const QByteArray emptyData = QByteArray::fromHex("f2 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 f6");
};
#endif // WIDGET_H
