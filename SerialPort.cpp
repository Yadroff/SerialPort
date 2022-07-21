#include "SerialPort.h"
#include <QLayout>

SerialPort::SerialPort(QWidget *parent) : QWidget(parent) {
    serialPort_ = new QSerialPort();
    initUI();
    portNamesList_ = getPortNames();
    portNamesBox_->addItems(portNamesList_);
    this->setWindowTitle("Serial Port Test");
    connect(openPortButton_, &QPushButton::clicked, this, &SerialPort::openPort);
    connect(sendMessageButton_, &QPushButton::clicked, this, &SerialPort::sendMessage);
    connect(receiveMessageButton_, &QPushButton::clicked, this, &SerialPort::receiveInfo);
}

SerialPort::~SerialPort() {
    if (serialPort_->isOpen()) {
        serialPort_->close();
        qDebug() << serialPort_->portName() << "Порт закрыт";
    }
    delete serialPort_;
    delete portNamesBox_;
    delete messageLine_;
    delete openPortButton_;
    delete sendMessageButton_;
}

void SerialPort::initUI() {
    openPortButton_ = new QPushButton();
    openPortButton_->setText("Открыть Serial Port");
    portNamesBox_ = new QComboBox;
    sendMessageButton_ = new QPushButton();
    sendMessageButton_->setText("Отправить сообщение по порту");
    messageLine_ = new QLineEdit;
    messageText_ = new QTextEdit;
    messageText_->setReadOnly(true);
    receiveMessageButton_ = new QPushButton();
    receiveMessageButton_->setText("Получить сообщение");
    auto *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    auto *choosePortLayout = new QHBoxLayout();
    choosePortLayout->addWidget(portNamesBox_);
    choosePortLayout->addWidget(openPortButton_);
    auto *sendMessageLayout = new QHBoxLayout();
    sendMessageLayout->addWidget(messageLine_);
    sendMessageLayout->addWidget(sendMessageButton_);
    auto *receiveMessageLayout = new QHBoxLayout();
    receiveMessageLayout->addWidget(messageText_);
    receiveMessageLayout->addWidget(receiveMessageButton_);
    layout->addLayout(choosePortLayout);
    layout->addLayout(sendMessageLayout);
    layout->addLayout(receiveMessageLayout);
    this->setLayout(layout);
}

QStringList SerialPort::getPortNames() {
    QStringList serialPortNames;
            foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            serialPortNames << info.portName();
            qDebug() << "serialPortName:" << info.portName();
        }
    return serialPortNames;
}

void SerialPort::openPort() {
    if (serialPort_->isOpen()) {
        serialPort_->clear();
        serialPort_->close();
        qDebug() << serialPort_->portName() << "Порт закрыт";
    }
    serialPort_->setPortName(portNamesBox_->currentText());
    if (!serialPort_->open(QIODevice::ReadWrite)) {
        qDebug() << serialPort_->portName() << "Не удалось открыть Serial Port";
        return;
    }
    qDebug() << serialPort_->portName() << "Порт открыт";

    serialPort_->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    serialPort_->setDataBits(QSerialPort::Data8);
    serialPort_->setFlowControl(QSerialPort::NoFlowControl);
    serialPort_->setParity(QSerialPort::NoParity);
    serialPort_->setStopBits(QSerialPort::OneStop);
}

void SerialPort::sendMessage() {
    if (!serialPort_->isOpen()) {
        qDebug() << "Ошибка долбаеба: открой Serial Port";
        return;
    }
    QString string = messageLine_->text().append('\n');
    QByteArray data(string.toUtf8());
    serialPort_->write(data);
    qDebug() << serialPort_->portName() << "Отправлено сообщение по Serial Port:" << string;
    messageLine_->clear();
}

void SerialPort::receiveInfo() {
    if (!serialPort_->isOpen()){
        qDebug() << "Ошибка долбаеба: открой Serial Port";
        return;
    }
    QByteArray info = serialPort_->readAll();
    QString string(info);
    messageText_->append(string);
    qDebug() << serialPort_->portName() << "Получено сообщение:" << string;
}
