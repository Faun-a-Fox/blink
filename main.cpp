#include "blinkwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /// INIT APPLICATION

    QCoreApplication::setApplicationVersion(QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH));
    QCoreApplication::setApplicationName("Blink");
    QCoreApplication::setOrganizationName("Faun-a-Fox");
    QCoreApplication::setOrganizationDomain("https://github.com/Faun-a-Fox/blink");

    BlinkWindow w;
    w.show();

    return a.exec();
}
