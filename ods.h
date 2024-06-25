#ifndef ODS_H
#define ODS_H
#include <QByteArray>
#include <QSerialPort>
#include <QtDebug>
#include <QObject>

class Ods : public QObject
{
    Q_OBJECT
public:
    explicit Ods(QObject *parent = nullptr);
    QByteArray getData() const;
    void setData(const QByteArray &value);
    void setDataByte(int index, int offset);

    void sendData();

    quint16 calculateCRC(const QByteArray &data);

    QString getSerialPortName() const;
    void setSerialPortName(const QString &value);
signals:

private:
    const QByteArray emptyData = QByteArray::fromHex("f2 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 f6");
    QString serialPortName;
    QByteArray data;
    quint16 count = 0;
public:
    QSerialPort serialPort;

public slots:
    void handleReadyRead();
    void onRecoverydataClicked();
};

#endif // ODS_H
