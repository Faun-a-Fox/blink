#include "Blink.h"
#include "settingsdef.h"

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
    , blinkColor(Qt::white)
    , blinkOpacity(100)

{
    /// INIT SETTINGS
    settings = new QSettings(SET_FILENAME, QSettings::IniFormat, this);
    settings->setValue(SET_BLINKENABLED_BOOL, settings->value(SET_BLINKENABLED_BOOL, true).toBool() );
    settings->setValue(SET_BLINKDURATION_INT, blinkDuration = settings->value(SET_BLINKDURATION_INT, blinkDuration).toInt() );
    settings->setValue(SET_BLINKINTERVAL_INT, blinkInterval = settings->value(SET_BLINKINTERVAL_INT, blinkInterval).toInt() );
    settings->setValue(SET_BLINKCOLOR_STR, (blinkColor = settings->value(SET_BLINKCOLOR_STR, blinkColor.name()).value<QColor>()).name() );
    settings->setValue(SET_BLINKOPACITY_INT, blinkOpacity = settings->value(SET_BLINKOPACITY_INT, blinkOpacity).toInt() );
    settings->sync();

    /// INIT TRAY ICON & MENU

    trayMenu = new QMenu("Blink");

    trayMenu->addAction("Settings", this, SLOT(openSettings()) );
    trayMenu->addSeparator();

    //trayMenu->addAction("Duration", this, SLOT(setBlinkDuration()) );
    //trayMenu->addAction("Interval", this, SLOT(setBlinkInterval()) );
    //trayMenu->addAction("Lightness", this, SLOT(setLightness()) );
    //trayMenu->addAction("Opacity", this, SLOT(setOpacity()) );
    //trayMenu->addSeparator();
    trayMenu->addAction("Quit", QApplication::instance(), SLOT(quit()) );

    trayIcon = new QSystemTrayIcon(QIcon("blink-32.png"), this);
    trayIcon->setToolTip("Blink");
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    /// INIT OVERLAY

    blinkOverlay = new OverlayWindow();
    blinkOverlay->setGeometry(QApplication::desktop()->rect());
    blinkOverlay->setColor(blinkColor);
    blinkOverlay->setOpacity(blinkOpacity);

    blinkTimerBar = new OverlayWindow();
    QRect r = QApplication::desktop()->screenGeometry(-1);
    r.setHeight(3);
    blinkTimerBar->setGeometry(r);
    blinkTimerBar->setColor(Qt::red);
    blinkTimerBar->show();

    blinkAnimation = new QPropertyAnimation(blinkTimerBar, "geometry", this);
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
    saveSettings();

    // delete all parent-less objects
    delete trayMenu;
    delete blinkOverlay;
    delete blinkTimerBar;
    delete settingsDialog;
}

void Blink::blink()
{
    if( (isBlinking = !isBlinking) )
    {
        /// BLINK

        // increase blink count
        ++blinkCounter;

        // set overlay properties and show it
        blinkOverlay->raise();
        blinkOverlay->setColor(blinkColor);
        blinkOverlay->setOpacity(blinkOpacity);
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

        // timer set to gap between blinks
        blinkTimer->start(t);
    }

}

void Blink::openSettings()
{
    auto dialog = new SettingsDialog(settings);
    connect(dialog, &SettingsDialog::accepted, this, &Blink::loadSettings);
    connect(dialog, &SettingsDialog::finished, dialog, &SettingsDialog::deleteLater);
    dialog->open();
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
    //blinkColor = QInputDialog::getInt(nullptr, "Set Lightness", "Lightness (0 - 100%)", blinkColor*100, 0, 100, 10) / 100.0;
}
void Blink::setOpacity()
{
    blinkOpacity = QInputDialog::getInt(nullptr, "Set Opacity", "Opacity (0 - 100%)", blinkOpacity, 0, 100, 10);
}

void Blink::saveSettings()
{
    settings->setValue(SET_BLINKDURATION_INT, blinkDuration);
    settings->setValue(SET_BLINKINTERVAL_INT, blinkInterval);
    settings->setValue(SET_BLINKCOLOR_STR, blinkColor.name());
    settings->setValue(SET_BLINKOPACITY_INT, blinkOpacity);
    settings->sync();
}

void Blink::loadSettings()
{
    //settings->value(SET_BLINKENABLED_BOOL, true).toBool();
    blinkDuration = settings->value(SET_BLINKDURATION_INT).toInt();
    blinkInterval = settings->value(SET_BLINKINTERVAL_INT).toInt();
    blinkColor = QColor(settings->value(SET_BLINKCOLOR_STR).toString());
    blinkOpacity = settings->value(SET_BLINKOPACITY_INT).toInt();
}
