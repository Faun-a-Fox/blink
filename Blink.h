#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OverlayWindow.h"

#include <QMenu>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>

class Blink : public QObject
{
    Q_OBJECT

public:
    explicit Blink(QWidget *parent = 0);
    ~Blink();

private slots:
    void blink();

    void setBlinkDuration();
    void setBlinkInterval();
    void setLightness();
    void setOpacity();

private:
    /// COMPONENTS

    OverlayWindow* blinkOverlay; // The blink overlay itself

    QTimer   blinkTimer;        // Timer used to keep track when to blink or unblink
    QWidget* blinkTimerBar;     // Visaul display of the timer

    QSettings*       settings;  // Stored settings
    QSystemTrayIcon* trayIcon;  // Tray icon
    QMenu*           trayMenu;  // Menu of tray icon

    /// STATUS VARIABLES

    bool isBlinking;   // is currently the blink overlay is being displayed?

    int blinkCounter;  // Number of times blinked since start

    int blinkDuration; // Duration of the blinks in ms
    int blinkInterval; // Interval between the beginning of consequtive blinks
    qreal lightness;   // Lightness value of the blink overlay
    qreal opacity;     // Opacity value of the blink overlay

};

#endif // MAINWINDOW_H
