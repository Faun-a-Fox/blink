#include "blinkwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QInputDialog>

BlinkWindow::BlinkWindow(QWidget *parent)
    : QMainWindow(parent)
    , blinking(false)
    , counter(0)
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

    /// INIT WINDOW PROPERTIES

    // set flags
    setWindowFlags( windowFlags()
                    | Qt::Tool // Hides taskbar entry
                    | Qt::CustomizeWindowHint //hides title bar
                    | Qt::FramelessWindowHint //hides frame
                    | Qt::WindowStaysOnTopHint //makes window the top layer
                    | Qt::WindowTransparentForInput //enables click-through
                    | Qt::WindowDoesNotAcceptFocus //makes impossibe to focus
                    | Qt::X11BypassWindowManagerHint //all of the above on X11 systems (linux)
                    );

    // set geometry to cover all available screen space on all screens
    QRect geometry;
    int screen_amount = QApplication::desktop()->numScreens();
    for(int i=0; i<screen_amount; ++i)
    {
        QRect screen(QApplication::desktop()->screenGeometry(i));
        if(screen.top() < geometry.top())
            geometry.setTop(screen.top());
        if(screen.bottom() > geometry.bottom())
            geometry.setBottom(screen.bottom());
        if(screen.left() < geometry.left())
            geometry.setLeft(screen.left());
        if(screen.right() > geometry.right())
            geometry.setRight(screen.right());
    }
    setGeometry(geometry);

    // set correct color
    updateColor();

    /// INIT TRAY ICON & MENU

    menu = new QMenu("Blink", this);
    menu->addAction("Duration", this, SLOT(setBlinkDuration()) );
    menu->addAction("Interval", this, SLOT(setBlinkInterval()) );
    menu->addAction("Lightness", this, SLOT(setLightness()) );
    menu->addAction("Opacity", this, SLOT(setOpacity()) );
    menu->addSeparator();
    menu->addAction("Quit", QApplication::instance(), SLOT(quit()) );

    trayIcon = new QSystemTrayIcon(QIcon("blink-32.png") ,this);
    trayIcon->setToolTip("Blink");
    trayIcon->setContextMenu(menu);
    trayIcon->show();

    /// START BLINKING

    // initialize the blink timer to start the blinking
    blinker.connect(&blinker, &QTimer::timeout, this, &BlinkWindow::blink);
    blinker.start(0);

}

BlinkWindow::~BlinkWindow()
{
    settings->setValue("blinkDuration", blinkDuration);
    settings->setValue("blinkInterval", blinkInterval);
    settings->setValue("lightness", lightness);
    settings->setValue("opacity", opacity);
    settings->sync();
}

void BlinkWindow::blink()
{
    if((blinking = !blinking))
    {
        ///blink

        ++counter;
        // raise above anything displayed since last blink
        raise();
        // make visible
        setWindowOpacity(opacity);
        // start blink timer
        blinker.start(blinkDuration);
    }
    else
    {
        ///unblink

        // make transparent
        setWindowOpacity(0);
        // timer set to gap betwwen blinks
        blinker.start(blinkInterval - blinkDuration);
    }

}

void BlinkWindow::setBlinkDuration()
{
    blinkDuration = QInputDialog::getInt(this, "Set Duration", "Blink Duartion (0 - 500 ms)", blinkDuration, 0, 500, 25);
}
void BlinkWindow::setBlinkInterval()
{
    blinkInterval = QInputDialog::getInt(this, "Set Interval", "Blink Interval (1000 - 30000 ms)", blinkInterval, 1000, 30000, 500);
}
void BlinkWindow::setLightness()
{
    lightness = QInputDialog::getInt(this, "Set Lightness", "Lightness (0 - 100%)", lightness*100, 0, 100, 10) / 100.0;

    updateColor();
}
void BlinkWindow::setOpacity()
{
    opacity = QInputDialog::getInt(this, "Set Opacity", "Opacity (0 - 100%)", opacity*100, 0, 100, 10) / 100.0;
}

void BlinkWindow::updateColor()
{
    QColor color;
    color.setHslF(0.0,0.0,lightness);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    setPalette(pal);
}
