#include "blinkwindow.h"

#include <QApplication>
#include <QDesktopWidget>

BlinkWindow::BlinkWindow(QWidget *parent)
    : QMainWindow(parent)
    , blinking(false)
    , counter(0)
    , blinkDuration(150)
    , blinkInterval(6000)
    , lightness(1.0)
    , opacity(1.0)

{
    setWindowFlags( windowFlags()
                    | Qt::Tool // Hides taskbar entry
                    | Qt::CustomizeWindowHint //hides title bar
                    | Qt::FramelessWindowHint //hides frame
                    | Qt::WindowStaysOnTopHint //makes window the top layer
                    | Qt::WindowTransparentForInput //enables click-through
                    | Qt::WindowDoesNotAcceptFocus //makes impossibe to focus
                    | Qt::X11BypassWindowManagerHint //all of the above on X11 systems (linux)
                    );

    //set geometry to cover all available screens
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

    //initialize the blink timer
    blinker.connect(&blinker, &QTimer::timeout, this, &BlinkWindow::blink);
    blinker.start(0);

    //call setters just in case they have some custom code to run
    setBlinkDuration(blinkDuration);
    setBlinkInterval(blinkInterval);
    setLightness(lightness);
    setOpacity(opacity);

}

BlinkWindow::~BlinkWindow()
{
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

void BlinkWindow::setBlinkDuration(int blinkDuration)
{
    this->blinkDuration = blinkDuration;
}
void BlinkWindow::setBlinkInterval(int blinkInterval)
{
    this->blinkInterval = blinkInterval;
}
void BlinkWindow::setLightness(qreal lightness)
{
    this->lightness = lightness;
    QColor color;
    color.setHslF(0.0,0.0,lightness);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    setPalette(pal);
}
void BlinkWindow::setOpacity(qreal opacity)
{
    this->opacity = opacity;
}








