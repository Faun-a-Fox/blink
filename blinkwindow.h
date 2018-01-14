#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>

class BlinkWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BlinkWindow(QWidget *parent = 0);
    ~BlinkWindow();

private slots:
    void blink();

    void setBlinkDuration();
    void setBlinkInterval();
    void setLightness();
    void setOpacity();

private:
    void updateColor();

    QSettings* settings;
    QSystemTrayIcon* trayIcon;
    QMenu* menu;

    QTimer blinker;
    bool blinking;

    int counter;

    int blinkDuration;
    int blinkInterval;
    qreal lightness;
    qreal opacity;

};

#endif // MAINWINDOW_H
