#include <QApplication>
#include "SerialPort.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    SerialPort sender;
    sender.show();
    return a.exec();
}
