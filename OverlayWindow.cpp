#include "OverlayWindow.h"

OverlayWindow::OverlayWindow(const QColor color, QWidget *parent)
    : QWidget(parent)
{
    setColor(color);
    setWindowFlags( windowFlags()
                    | Qt::Tool // Hides taskbar entry
                    | Qt::CustomizeWindowHint //hides title bar
                    | Qt::FramelessWindowHint //hides frame
                    | Qt::WindowStaysOnTopHint //makes window the top layer
                    | Qt::WindowTransparentForInput //enables click-through
                    | Qt::WindowDoesNotAcceptFocus //makes impossibe to focus
                    | Qt::X11BypassWindowManagerHint //all of the above on X11 systems (linux)
                    );
}
OverlayWindow::OverlayWindow(QWidget *parent)
    : OverlayWindow(Qt::white, parent)
{}


void OverlayWindow::setColor(const QColor color)
{
    if(color != palette().color(QPalette::Background) )
    {
        QPalette pal = palette();
        pal.setColor(QPalette::Background, color);
        setPalette(pal);
    }
}


void OverlayWindow::setOpacity(const qreal opacity)
{
    if(opacity != windowOpacity())
    {
        setWindowOpacity(opacity);
    }
}
