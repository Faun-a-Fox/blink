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

    void setBlinkDuration();
    void setBlinkInterval();
    void setLightness();
    void setOpacity();

private:
    /// COMPONENTS

    /// CORE
    SettingsDialog*  settingsDialog;
    QSettings*       settings;  // Stored settings
    QSystemTrayIcon* trayIcon;  // Tray icon
    QMenu*           trayMenu;  // Menu of tray icon

    /// BLINKING
    QTimer*        blinkTimer;    // Timer used to keep track when to blink or unblink
    OverlayWindow* blinkTimerBar; // Visaul display of the timer
    OverlayWindow* blinkOverlay;  // The blink overlay itself
    QPropertyAnimation* blinkAnimation;

    /// FLOW-ER
    //QTimer*        flowTimer;    //
    //OverlayWindow* flowTimerBar; //
    //OverlayWindow* flowOverlay;  //

    /// STATUS VARIABLES

    bool isBlinking;   // is currently the blink overlay is being displayed?
    int blinkCounter;  // Number of times blinked since start

    int blinkDuration; // Duration of the blinks in ms
    int blinkInterval; // Interval between the beginning of consequtive blinks
    qreal lightness;   // Lightness value of the blink overlay
    qreal opacity;     // Opacity value of the blink overlay

};

#endif // MAINWINDOW_H
