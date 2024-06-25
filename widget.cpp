#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList comboxData = {"car1", "car2", "car3", "car4", "car5", "car6"};
    ui->comboBox->addItems(comboxData);
    QStringList serialPortList = {"/dev/ttyS0", "/dev/ttyS1"};
    ui->serial_port->addItems(serialPortList);

    ods = new Ods(this);
    QByteArray data = QByteArray::fromHex("f2 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 f6");
    ods->setData(data);
}

Widget::~Widget()
{
    delete ods;
    delete ui;
}

void Widget::on_door1_clicked()
{
    ods->setDataByte(4, 2);
    //data[4] = data[4] | (1 << 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        ods->setDataByte(5, 0);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        ods->setDataByte(6, 0);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        ods->setDataByte(7, 0);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        ods->setDataByte(8, 0);
    }
    else {
        ;
    }
}

void Widget::on_door2_clicked()
{
    ods->setDataByte(4, 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        ods->setDataByte(5, 1);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        ods->setDataByte(6, 1);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        ods->setDataByte(7, 1);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        ods->setDataByte(8, 1);
    }
    else {
        ;
    }
}

void Widget::on_recoveryData_clicked()
{
    ods->onRecoverydataClicked();
}


void Widget::on_door3_clicked()
{
    ods->setDataByte(4, 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        ods->setDataByte(5, 2);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        ods->setDataByte(6, 2);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        ods->setDataByte(7, 2);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        ods->setDataByte(8, 2);
    }
    else {
        ;
    }
}

void Widget::on_door4_clicked()
{
    ods->setDataByte(4, 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        ods->setDataByte(5, 3);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        ods->setDataByte(6, 3);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        ods->setDataByte(7, 3);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        ods->setDataByte(8, 3);
    }
    else {
        ;
    }
}

void Widget::on_door5_clicked()
{
    ods->setDataByte(4, 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        ods->setDataByte(5, 4);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        ods->setDataByte(6, 4);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        ods->setDataByte(7, 4);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        ods->setDataByte(8, 4);
    }
    else {
        ;
    }
}

void Widget::on_door6_clicked()
{
    ods->setDataByte(4, 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        ods->setDataByte(5, 5);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        ods->setDataByte(6, 5);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        ods->setDataByte(7, 5);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        ods->setDataByte(8, 5);
    }
    else {
        ;
    }
}

void Widget::on_door7_clicked()
{
    ods->setDataByte(4, 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        ods->setDataByte(5, 6);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        ods->setDataByte(6, 6);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        ods->setDataByte(7, 6);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        ods->setDataByte(8, 6);
    }
    else {
        ;
    }
}

void Widget::on_door8_clicked()
{
    ods->setDataByte(4, 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        ods->setDataByte(5, 7);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        ods->setDataByte(6, 7);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        ods->setDataByte(7, 7);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        ods->setDataByte(8, 7);
    }
    else {
        ;
    }
}

void Widget::on_car1_front_fault_clicked()
{
    ods->setDataByte(4, 0);
    qDebug() << "报文修改为" << ods->getData() << endl;
}

void Widget::on_car2_door2_fault_clicked()
{
    ods->setDataByte(4, 1);
    qDebug() << "报文修改为" << ods->getData() << endl;
}

void Widget::on_control_button_clicked()
{
    if(ui->control_button->text() == "开始")
    {
        ods->serialPort.setPortName(ui->serial_port->currentText()); // 串口号，请根据实际情况修改
        ods->serialPort.setBaudRate(QSerialPort::Baud19200);
        ods->serialPort.setDataBits(QSerialPort::Data8);
        ods->serialPort.setParity(QSerialPort::EvenParity);
        ods->serialPort.setStopBits(QSerialPort::OneStop);
        ods->serialPort.setFlowControl(QSerialPort::NoFlowControl);
        ods->serialPort.open(QIODevice::ReadWrite);
        connect(&(ods->serialPort), &QSerialPort::readyRead, ods, &Ods::handleReadyRead);
        ui->control_button->setText("关闭");
        qDebug() << ui->serial_port->currentText() << endl << ods->getData() << endl;
    }
    else {
        disconnect(&(ods->serialPort), &QSerialPort::readyRead, ods, &Ods::handleReadyRead);
        ods->serialPort.close();
        //disconnect(&serialPort, &QSerialPort::readyRead, ods, &Widget::handleReadyRead);
        ui->control_button->setText("开始");
        qDebug() << "关闭"  << endl;
    }
}
