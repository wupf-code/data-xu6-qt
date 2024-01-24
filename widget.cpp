#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList comboxData = {"car1", "car2", "car3", "car4", "car5", "car6"};
    ui->comboBox->addItems(comboxData);
    data = QByteArray::fromHex("f2 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 f6");
    //qDebug() << "data.length:" << data.length();
    serialPort.setPortName("/dev/ttyS0"); // 串口号，请根据实际情况修改
    serialPort.setBaudRate(QSerialPort::Baud19200);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::EvenParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);
    serialPort.open(QIODevice::ReadWrite);
    connect(&serialPort, &QSerialPort::readyRead, this, &Widget::handleReadyRead);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::sendData);
    timer->start(200);
}

Widget::~Widget()
{
    serialPort.close();
    delete ui;
}

quint16 Widget::calculateCRC(const QByteArray &data)
{
    quint16 checksum = 0xFFFF;
    for (int i = 1; i < data.size() - 3; ++i)
    {
        checksum ^= quint8(data.at(i)) << 8;
        for (int j = 0; j < 8; ++j)
        {
            checksum = (checksum & 0x8000) ? ((checksum << 1) ^ 0x1021) : (checksum << 1);
        }
    }
    return checksum;
}

void Widget::on_recoveryData_clicked()
{
    data = emptyData;
}

void  Widget::handleReadyRead()
{
    QByteArray receiveData = serialPort.readAll();
    // 处理收到的数据，这里简单地打印出来
    qDebug() << "Received data: " << data.toHex();
}

void Widget::sendData()
{
    count++;
    qDebug() << count << endl;
    data[2] = quint8((count >> 8) & 0xFF);
    data[3] = quint8(count & 0xFF);
    quint16 checksum = calculateCRC(data);

    // 更新校验位
    data[data.size() - 3] = quint8((checksum >> 8) & 0xFF);
    data[data.size() - 2] = quint8(checksum & 0xFF);
    // 发送数据
    serialPort.write(data);
    qDebug() << "Sent data: " << data.toHex();
}

void Widget::on_door1_clicked()
{
    data[4] = data[4] | (1 << 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        data[5] = data[5] | 1;
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        data[6] = data[6] | 1;
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        data[7] = data[7] | 1;
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        data[8] = data[8] | 1;
    }
    else {
        ;
    }
    //data[5] = data[1] | 1;
    //qDebug() << data.toHex() ;
}

void Widget::on_door2_clicked()
{
    data[4] = data[4] | (1 << 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        data[5] = data[5] | (1 << 1);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        data[6] = data[6] | (1 << 1);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        data[7] = data[7] | (1 << 1);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        data[8] = data[8] | (1 << 1);
    }
    else {
        ;
    }
}


void Widget::on_door3_clicked()
{
    data[4] = data[4] | (1 << 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        data[5] = data[5] | (1 << 2);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        data[6] = data[6] | (1 << 2);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        data[7] = data[7] | (1 << 2);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        data[8] = data[8] | (1 << 2);
    }
    else {
        ;
    }
}

void Widget::on_door4_clicked()
{
    data[4] = data[4] | (1 << 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        data[5] = data[5] | (1 << 3);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        data[6] = data[6] | (1 << 3);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        data[7] = data[7] | (1 << 3);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        data[8] = data[8] | (1 << 3);
    }
    else {
        ;
    }
}

void Widget::on_door5_clicked()
{
    data[4] = data[4] | (1 << 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        data[5] = data[5] | (1 << 4);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        data[6] = data[6] | (1 << 4);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        data[7] = data[7] | (1 << 4);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        data[8] = data[8] | (1 << 4);
    }
    else {
        ;
    }
}

void Widget::on_door6_clicked()
{
    data[4] = data[4] | (1 << 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        data[5] = data[5] | (1 << 5);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        data[6] = data[6] | (1 << 5);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        data[7] = data[7] | (1 << 5);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        data[8] = data[8] | (1 << 5);
    }
    else {
        ;
    }
}

void Widget::on_door7_clicked()
{
    data[4] = data[4] | (1 << 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        data[5] = data[5] | (1 << 6);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        data[6] = data[6] | (1 << 6);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        data[7] = data[7] | (1 << 6);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        data[8] = data[8] | (1 << 6);
    }
    else {
        ;
    }
}

void Widget::on_door8_clicked()
{
    data[4] = data[4] | (1 << 2);
    if(ui->comboBox->currentIndex() == 0)
    {
        data[5] = data[5] | (1 << 7);
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        data[6] = data[6] | (1 << 7);
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        data[7] = data[7] | (1 << 7);
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        data[8] = data[8] | (1 << 7);
    }
    else {
        ;
    }
}

void Widget::on_car1_front_fault_clicked()
{
    data[4] = data[4] | (1 << 0);
}

void Widget::on_car2_door2_fault_clicked()
{
    data[4] = data[4] | (1 << 1);
}
