#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OverlayWindow.h"
#include "settingsdialog.h"

#include <QMenu>
#include <QPropertyAnimation>
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

    void openSettings();

private:
    /// COMPONENTS

    /// CORE
    QSettings*       settings;  // Stored settings
    QSystemTrayIcon* trayIcon;  // Tray icon
    QMenu*           trayMenu;  // Menu of tray icon

    /// BLINKING
    QTimer*             blinkTimer;    // Timer used to keep track when to blink or unblink
    OverlayWindow*      blinkTimerBar; // Visaul display of the timer
    OverlayWindow*      blinkOverlay;  // The blink overlay itself

    /// FLOW-ER
    //QTimer*        flowTimer;    //
    //OverlayWindow* flowTimerBar; //
    //OverlayWindow* flowOverlay;  //

    /// STATUS VARIABLES

    int blinkCounter;  // Number of times blinked since start

};

#endif // MAINWINDOW_H
