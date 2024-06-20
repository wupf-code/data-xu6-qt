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
    QStringList serialPortList = {"/dev/ttyS0", "/dev/ttyS1"};
    ui->serial_port->addItems(serialPortList);
//    connect(&serialPort, &QSerialPort::readyRead, this, &Widget::handleReadyRead);
//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &Widget::sendData);
//    timer->start(200);
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
    // 初始化起始位置以便在数据中搜索
        int startIndex = 0;

        while(startIndex <= receiveData.size() - 21) { // 确保剩余数据足够检查一个21字节的报文
            // 检查从startIndex开始的21字节数据是否符合条件
            if(receiveData.mid(startIndex, 1)[0] == '\xfc' && // 开头是fc
               receiveData.mid(startIndex, 21).endsWith('\xf6')) { // 结尾是f6且长度为21
                // 符合条件的报文发现，进行回复
                // 处理收到的数据，这里简单地打印出来
                qDebug() << "Received data: " << receiveData.toHex();
                // 更新startIndex以检查下一个可能的子报文，注意这里是加21，因为已经检查过了当前的21字节
                startIndex += 21;
                sendData();
            } else {
                // 如果当前起始位置不符合条件，移动到下一个可能的起始位置
                startIndex++;
            }
        }
    //sendData();
}

void Widget::sendData()
{
    count++;
    data[2] = quint8((count >> 8) & 0xFF);
    data[3] = quint8(count & 0xFF);
    quint16 checksum = calculateCRC(data);

    // 更新校验位
    data[data.size() - 3] = quint8((checksum >> 8) & 0xFF);
    data[data.size() - 2] = quint8(checksum & 0xFF);
    // 发送数据
    serialPort.write(data);
    qDebug() << "Sent data: " << data.toHex();
    qDebug() << count << endl;
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
    qDebug() << "报文修改为" << data << endl;
}

void Widget::on_car2_door2_fault_clicked()
{
    data[4] = data[4] | (1 << 1);
    qDebug() << "报文修改为" << data << endl;
}

void Widget::on_control_button_clicked()
{
    if(ui->control_button->text() == "开始")
    {
        serialPort.setPortName(ui->serial_port->currentText()); // 串口号，请根据实际情况修改
        serialPort.setBaudRate(QSerialPort::Baud19200);
        serialPort.setDataBits(QSerialPort::Data8);
        serialPort.setParity(QSerialPort::EvenParity);
        serialPort.setStopBits(QSerialPort::OneStop);
        serialPort.setFlowControl(QSerialPort::NoFlowControl);
        serialPort.open(QIODevice::ReadWrite);
        connect(&serialPort, &QSerialPort::readyRead, this, &Widget::handleReadyRead);
        ui->control_button->setText("关闭");
        qDebug() << ui->serial_port->currentText() << endl << data << endl;
    }
    else {
        disconnect(&serialPort, &QSerialPort::readyRead, this, &Widget::handleReadyRead);
        serialPort.close();
        disconnect(&serialPort, &QSerialPort::readyRead, this, &Widget::handleReadyRead);
        ui->control_button->setText("开始");
        qDebug() << "关闭"  << endl;
    }
}
