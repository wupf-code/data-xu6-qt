#include "ods.h"

Ods::Ods(QObject *parent) : QObject(parent)
{

}

QByteArray Ods::getData() const
{
    return data;
}

void Ods::setData(const QByteArray &value)
{
    data = value;
}

void Ods::setDataByte(int index, int offset)
{
    data[index] = data[index] | (1 << offset);
}




void Ods::sendData()
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

quint16 Ods::calculateCRC(const QByteArray &data)
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

QString Ods::getSerialPortName() const
{
    return serialPortName;
}

void Ods::setSerialPortName(const QString &value)
{
    serialPortName = value;
}

void Ods::handleReadyRead()
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

void Ods::onRecoverydataClicked()
{
    data = emptyData;
}
