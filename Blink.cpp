#include "Blink.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QInputDialog>

Blink::Blink(QWidget *parent)
    : QObject(parent)
    // States
    , isBlinking(false)
    , blinkCounter(0)
    // Defaults
    , blinkDuration(100)
    , blinkInterval(6000)
    , lightness(1.0)
    , opacity(0.9)

{
    /// INIT SETTINGS

    settings = new QSettings("BlinkConfig.ini", QSettings::IniFormat, this);
    settings->setValue("blinkDuration", blinkDuration = settings->value("blinkDuration", blinkDuration).toInt() );
    settings->setValue("blinkInterval", blinkInterval = settings->value("blinkInterval", blinkInterval).toInt() );
    settings->setValue("lightness", lightness = settings->value("lightness", lightness).toDouble() );
    settings->setValue("opacity", opacity = settings->value("opacity", opacity).toDouble() );
    settings->sync();

    /// INIT TRAY ICON & MENU

    trayMenu = new QMenu("Blink");
    trayMenu->addAction("Duration", this, SLOT(setBlinkDuration()) );
    trayMenu->addAction("Interval", this, SLOT(setBlinkInterval()) );
    trayMenu->addAction("Lightness", this, SLOT(setLightness()) );
    trayMenu->addAction("Opacity", this, SLOT(setOpacity()) );
    trayMenu->addSeparator();
    trayMenu->addAction("Quit", QApplication::instance(), SLOT(quit()) );

    trayIcon = new QSystemTrayIcon(QIcon("blink-32.png"), this);
    trayIcon->setToolTip("Blink");
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    /// INIT OVERLAY

    blinkOverlay = new OverlayWindow();
    blinkOverlay->setGeometry(QApplication::desktop()->rect());
    blinkOverlay->setColor(QColor::fromHslF(0.0, 0.0, lightness) );
    blinkOverlay->setOpacity(opacity);

    blinkTimerBar = new OverlayWindow();
    QRect r = QApplication::desktop()->screen()->rect();
    r.setHeight(3);
    blinkTimerBar->setGeometry(r);
    blinkTimerBar->setColor(Qt::red);
    blinkTimerBar->show();

    blinkAnimation = new QPropertyAnimation(blinkTimerBar, "geometry", this);
    //blinkAnimation->setStartValue(blinkTimerBar->rect().adjusted(0,0,0,1-blinkTimerBar->rect().width()));
    blinkAnimation->setStartValue(QRect(blinkTimerBar->rect().topLeft(),QPoint(1,3)));
    blinkAnimation->setEndValue(blinkTimerBar->rect());

    /// START BLINKING

    // initialize the blink timer to start the blinking
    blinkTimer = new QTimer(this);
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blink()) );
    blinkTimer->start(0);
}

Blink::~Blink()
{
    //save settings
    settings->setValue("blinkDuration", blinkDuration);
    settings->setValue("blinkInterval", blinkInterval);
    settings->setValue("lightness", lightness);
    settings->setValue("opacity", opacity);
    settings->sync();

    // delete all parent-less objects
    delete trayMenu;
    delete blinkOverlay;
    delete blinkTimerBar;
}

void Blink::blink()
{
    if((isBlinking = !isBlinking))
    {
        /// BLINK

        // increase blink count
        ++blinkCounter;

        // set overlay properties and show it
        blinkOverlay->raise();
        blinkOverlay->setColor(QColor::fromHslF(0.0,0.0,lightness));
        blinkOverlay->setOpacity(opacity);
        blinkOverlay->show();

        blinkTimerBar->hide();

        // start blink timer
        blinkTimer->start(blinkDuration);

    }
    else
    {
        /// UNBLINK

        // hide overlay
        blinkOverlay->hide();

        int t = blinkInterval - blinkDuration;


        blinkAnimation->setDuration(t);
        blinkAnimation->start();
        blinkTimerBar->show();

        // timer set to gap betwwen blinks
        blinkTimer->start(t);
    }

}

void Blink::setBlinkDuration()
{
    blinkDuration = QInputDialog::getInt(nullptr, "Set Duration", "Blink Duartion (0 - 500 ms)", blinkDuration, 0, 500, 25);
}
void Blink::setBlinkInterval()
{
    blinkInterval = QInputDialog::getInt(nullptr, "Set Interval", "Blink Interval (1000 - 30000 ms)", blinkInterval, 1000, 30000, 500);
}
void Blink::setLightness()
{
    lightness = QInputDialog::getInt(nullptr, "Set Lightness", "Lightness (0 - 100%)", lightness*100, 0, 100, 10) / 100.0;
}
void Blink::setOpacity()
{
    opacity = QInputDialog::getInt(nullptr, "Set Opacity", "Opacity (0 - 100%)", opacity*100, 0, 100, 10) / 100.0;
}
