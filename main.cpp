#include "Blink.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /// INIT APPLICATION

    QCoreApplication::setApplicationName("Blink");
    QCoreApplication::setApplicationVersion(QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH));
    QCoreApplication::setOrganizationName("Faun-a-Fox");
    QCoreApplication::setOrganizationDomain("https://github.com/Faun-a-Fox/blink");

    QGuiApplication::setQuitOnLastWindowClosed(false);

    auto mainObject = new Blink();
    mainObject->connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), mainObject, SLOT(deleteLater()) );

    return a.exec();
}
