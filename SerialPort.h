#ifndef SERIALPORT_SERIALPORT_H
#define SERIALPORT_SERIALPORT_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

class SerialPort : public QWidget {
Q_OBJECT
public:
    explicit SerialPort(QWidget *parent = 0);

    ~SerialPort();

    void initUI();

    void openPort();

    QStringList getPortNames();

    void sendMessage();

public slots:

    void receiveInfo();

private:
    QSerialPort *serialPort_;
    QStringList portNamesList_;
    QComboBox *portNamesBox_;
    QPushButton *openPortButton_;
    QLineEdit *messageLine_;
    QPushButton *sendMessageButton_;
    QTextEdit *messageText_;
    QPushButton *receiveMessageButton_;
};


#endif //SERIALPORT_SERIALPORT_H
