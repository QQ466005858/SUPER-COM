#include "SerialPort.h"
#include <QTime>


Q_LOGGING_CATEGORY(SerialPortLog, "ComPortLibrary.SerialPort.log")


SerialPort::SerialPort()
{
    serialPortPtr_ = Q_NULLPTR;
    buf_.clear();
    qCDebug(SerialPortLog())<<"构造";
}

SerialPort::~SerialPort()
{
//    close();
    qCDebug(SerialPortLog())<<"析构";
    if(serialPortPtr_ != Q_NULLPTR) {
        delete serialPortPtr_;
//        serialPortPtr_ = Q_NULLPTR;
//        serialPortPtr_->deleteLater();
    }
}


/**
 * @brief SerialPort::open
 * @param port "ttyUSBx", "ttySx", "COMx"
 * @param args ["9600","N","8","1"]
 * @return true-成功, false-失败
 */
bool SerialPort::open(QString port, QStringList args)
{
//    qCDebug(SerialPortLog())<<"open:"<<port<<args;
    if(port == "" || args.length() != 4)
    {
        qCDebug(SerialPortLog())<<"args:error"<<port<<args;
        return false;
    }
//    qCDebug(SerialPortLog())<<"open:"<<port<<args;

    QString szSerialPortName = port;

#ifdef Q_OS_LINUX
    serialPortPtr_ = new QSerialPort(szSerialPortName);
#elif defined (Q_OS_WIN)
    serialPortPtr_ = new QSerialPort(szSerialPortName);
#endif

    //设置波特率
    QString strBaud = args.at(0);
    serialPortPtr_->setBaudRate(strBaud.toInt());


    //设置校验
    QString strParity = args.at(1);
    if(strParity == "N" || strParity == "无校验") {
        serialPortPtr_->setParity(QSerialPort::Parity::NoParity);
    } else if(strParity == "O" || strParity == "奇校验") {
        serialPortPtr_->setParity(QSerialPort::Parity::OddParity);
    } else if(strParity == "E" || strParity == "偶校验") {
        serialPortPtr_->setParity(QSerialPort::Parity::EvenParity);
    } else {
        serialPortPtr_->setParity(QSerialPort::Parity::NoParity);
    }

    //设置数据位
    QString strDataBits = args.at(2);
    serialPortPtr_->setDataBits((QSerialPort::DataBits)strDataBits.toInt());

    //设置停止位
    QString strStopBits = args.at(3);
    int iStopBits = strStopBits.toFloat() * 10;
    switch(iStopBits) {
    case 10:
        serialPortPtr_->setStopBits(QSerialPort::OneStop);
        break;
    case 15:
 #ifdef Q_OS_WIN
        serialPortPtr_->setStopBits(QSerialPort::OneAndHalfStop);
 #endif
        break;
    case 20:
        serialPortPtr_->setStopBits(QSerialPort::TwoStop);
        break;
    default:
        serialPortPtr_->setStopBits(QSerialPort::OneStop);
        break;
    }

    //设置数据流控制
    serialPortPtr_->setFlowControl(QSerialPort::NoFlowControl);

    return serialPortPtr_->open(QIODevice::ReadWrite);
}


bool SerialPort::isOpen()
{
    return serialPortPtr_->isOpen();
}
/**
 * @brief SerialPort::reOpen
 * @return true-成功, false-失败
 */
bool SerialPort::reOpen()
{
    if(serialPortPtr_->isOpen()) {
        serialPortPtr_->close();
        return serialPortPtr_->open(QIODevice::ReadWrite);
    }
    return true;
}

int SerialPort::write(QByteArray buf, int)
{
    qCDebug(SerialPortLog())<<"write:"<<"data:"<<buf.toHex();
    int count = 0;
    count = serialPortPtr_->write(buf);
    serialPortPtr_->flush();
    return count;
}

//超过一定时间无数据则认为一包结束
int SerialPort::read(QByteArray & rec, int ms)
{
    rec.clear();//先清除BUF
    int tm_cnt = 0;
    while( tm_cnt < ms)
    {
        if(serialPortPtr_->bytesAvailable())
        {
            rec.append(serialPortPtr_->readAll());
            tm_cnt = 0;//清时间
        }
         else
        {
            serialPortPtr_->waitForReadyRead(10);
            tm_cnt += 10;
        }
    }
    return rec.length();
}
void SerialPort::readAll()
{
    if(serialPortPtr_->bytesAvailable())
    {
        serialPortPtr_->readAll();
    }
}

void SerialPort::clear_read()
{
    readAll();
}
int SerialPort::read(unsigned char *buf, int len, int ms)
{
    long start;
    QTime time;
    time.start();
    start = time.elapsed();
    while(buf_.size() < len) {
        if(serialPortPtr_->bytesAvailable()) {
            buf_.append(serialPortPtr_->readAll());
        }
        if((time.elapsed() - start) > ms) {
            if(len > buf_.size())
                len = buf_.size();
            break;
        } else {
//            QThread::msleep(20);
            serialPortPtr_->waitForReadyRead(10);
        }
    }

    for(int i=0; i<len; i++) buf[i] = buf_[i];
#if 0
    qDebug()<< "read: " << hexToString(buf_.data(), len);
#endif
    buf_.remove(0, len);

    return len;
}

int SerialPort::write(unsigned char *buf, int len, int /*ms*/)
{
    int count = 0;
#if 0
    qDebug()<< "write: " << hexToString((char *)buf, len);
#endif
    count = serialPortPtr_->write((char*)buf, len);
    serialPortPtr_->flush();
    return count;
}

bool SerialPort::close()
{
    buf_.clear();
    if(serialPortPtr_ != Q_NULLPTR) {
        if(serialPortPtr_->isOpen()) {
            serialPortPtr_->close();
            return true;
        }
    }
    return false;
}

TPortType SerialPort::getPortType()
{
    return PORT_SERIAL;
}
