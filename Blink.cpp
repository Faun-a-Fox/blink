#include "Blink.h"
#include "settingsdef.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QInputDialog>

Blink::Blink(QWidget *parent)
    : QObject(parent)
    , blinkCounter(0)

{
    /// INIT SETTINGS
    settings = new QSettings(SET_FILENAME, QSettings::IniFormat, this);

    settings->setValue(SET_BLINKENABLED_BOOL, settings->value(SET_BLINKENABLED_BOOL, true).toBool() );
    settings->setValue(SET_BLINKDURATION_INT, settings->value(SET_BLINKDURATION_INT, 1000).toInt() );
    settings->setValue(SET_BLINKINTERVAL_INT, settings->value(SET_BLINKINTERVAL_INT, 6000).toInt() );
    settings->setValue(SET_BLINKCOLOR_STR, settings->value(SET_BLINKCOLOR_STR, "#ffffff").value<QColor>().name() );
    settings->setValue(SET_BLINKOPACITY_INT, settings->value(SET_BLINKOPACITY_INT, 100).toInt() );

    settings->setValue(SET_TIMERENABLED_BOOL, settings->value(SET_TIMERENABLED_BOOL, true).toBool() );
    settings->setValue(SET_TIMERHEIGHT_INT, settings->value(SET_TIMERHEIGHT_INT, 3).toInt() );
    settings->setValue(SET_TIMERCOLOR_STR, settings->value(SET_TIMERCOLOR_STR, "ff0000").value<QColor>().name() );
    settings->setValue(SET_TIMEROPACITY_INT, settings->value(SET_TIMEROPACITY_INT, 100). toInt() );

    settings->sync();

    /// INIT TRAY ICON & MENU

    trayMenu = new QMenu("Blink");
    trayMenu->addAction("Settings", this, SLOT(openSettings()) );
    trayMenu->addSeparator();
    trayMenu->addAction("Quit", QApplication::instance(), SLOT(quit()) );

    trayIcon = new QSystemTrayIcon(QIcon("blink-32.png"), this);
    trayIcon->setToolTip("Blink");
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    /// INIT OVERLAYS

    blinkOverlay = new OverlayWindow();
    blinkOverlay->show();

    blinkTimerBar = new OverlayWindow();
    blinkTimerBar->show();

    /// START BLINKING

    // initialize the blink timer to start the blinking
    blinkTimer = new QTimer(this);
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blink()) );
    blinkTimer->start(0);
}

Blink::~Blink()
{
    // delete all parent-less objects
    delete trayMenu;
    delete blinkOverlay;
    delete blinkTimerBar;
}

void Blink::blink()
{

    // increase blink count
    ++blinkCounter;

    if(settings->value(SET_BLINKENABLED_BOOL).toBool())
    {
        // set overlay properties and show it
        blinkOverlay->setGeometry(QApplication::desktop()->rect());
        blinkOverlay->setColor(settings->value(SET_BLINKCOLOR_STR).toString());
        blinkOverlay->setOpacity(settings->value(SET_BLINKOPACITY_INT).toInt());

        QTimer::singleShot(settings->value(SET_BLINKDURATION_INT).toInt(),[this](){blinkOverlay->setOpacity(0);});
    }

    if(settings->value(SET_TIMERENABLED_BOOL).toBool())
    {
        blinkTimerBar->setColor(settings->value(SET_TIMERCOLOR_STR).toString());
        blinkTimerBar->setOpacity(settings->value(SET_TIMEROPACITY_INT).toInt());

        QRect rect = QApplication::desktop()->screenGeometry(-1);
        rect.setHeight(settings->value(SET_TIMERHEIGHT_INT).toInt());

        auto anim = new QPropertyAnimation(blinkTimerBar, "geometry", this);
        anim->setEndValue(rect);
        rect.setWidth(1);
        anim->setStartValue(rect);
        anim->setDuration(settings->value(SET_BLINKINTERVAL_INT).toInt());
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }

    // start blink timer
    blinkTimer->start(settings->value(SET_BLINKINTERVAL_INT).toInt());
}

void Blink::openSettings()
{
    auto dialog = new SettingsDialog(settings);
    connect(dialog, &SettingsDialog::accepted, settings, &QSettings::sync);
    connect(dialog, &SettingsDialog::finished, dialog, &SettingsDialog::deleteLater);
    dialog->open();
}
