#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
//#include <QSystemTrayIcon>

class BlinkWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BlinkWindow(QWidget *parent = 0);
    ~BlinkWindow();

public slots:
    void blink();

    void setBlinkDuration(int blinkDuration);
    void setBlinkInterval(int blinkInterval);
    void setLightness(qreal lightness);
    void setOpacity(qreal opacity);

private:
    //QSystemTrayIcon trayIcon;
    QTimer blinker;
    bool blinking;

    int counter;

    int blinkDuration;
    int blinkInterval;
    qreal lightness;
    qreal opacity;

};

#endif // MAINWINDOW_H
