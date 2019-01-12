#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include "settingsdef.h"

#include <QColorDialog>

SettingsDialog::SettingsDialog(QSettings *settings, QWidget *parent) :
    QDialog(parent),
    settings(settings),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    settings->

    /// Connect color settings

    connect(ui->toolButton_Color, &QToolButton::clicked, [this](){querryColor(ui->lineEdit_Color);});
    connect(ui->toolButton_TimerColor, &QToolButton::clicked, [this](){querryColor(ui->lineEdit_TimerColor);});

    connect(ui->lineEdit_Color, &QLineEdit::textChanged, [this](){updatePalette(ui->lineEdit_Color);});
    connect(ui->lineEdit_TimerColor, &QLineEdit::textChanged, [this](){updatePalette(ui->lineEdit_TimerColor);});

    /// Load values

    ui->groupBox_BlinkOverlay->setChecked(settings->value(SET_BLINKENABLED_BOOL).toBool());
    ui->spinBox_Duration->setValue(settings->value(SET_BLINKDURATION_INT).toInt());
    ui->spinBox_Interval->setValue(settings->value(SET_BLINKINTERVAL_INT).toInt());
    ui->lineEdit_Color->setText(settings->value(SET_BLINKCOLOR_STR).toString());
    ui->spinBox_Opacity->setValue(settings->value(SET_BLINKOPACITY_INT).toInt());

    ui->groupBox_TimerBar->setChecked(settings->value(SET_TIMERENABLED_BOOL).toBool());
    ui->spinBox_TimerHeight->setValue(settings->value(SET_TIMERHEIGHT_INT).toInt());
    ui->lineEdit_TimerColor->setText(settings->value(SET_TIMERCOLOR_STR).toString());
    ui->spinBox_TimerOpacity->setValue(settings->value(SET_TIMEROPACITY_INT).toInt());

    /// Connect values

    connect(this, &SettingsDialog::accepted, [this, settings]()
    {
        settings->setValue(SET_BLINKENABLED_BOOL, ui->groupBox_BlinkOverlay->isChecked());
        settings->setValue(SET_BLINKDURATION_INT, ui->spinBox_Duration->value());
        settings->setValue(SET_BLINKINTERVAL_INT, ui->spinBox_Interval->value());
        settings->setValue(SET_BLINKCOLOR_STR, ui->lineEdit_Color->text());
        settings->setValue(SET_BLINKOPACITY_INT, ui->spinBox_Opacity->value());

        settings->setValue(SET_TIMERENABLED_BOOL, ui->groupBox_TimerBar->isChecked());
        settings->setValue(SET_TIMERHEIGHT_INT, ui->spinBox_TimerHeight->value());
        settings->setValue(SET_TIMERCOLOR_STR, ui->lineEdit_TimerColor->text());
        settings->setValue(SET_TIMEROPACITY_INT, ui->spinBox_TimerOpacity->value());
    });

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::querryColor(QLineEdit *lineEdit)
{
    auto c = QColor(lineEdit->text());

    if( !c.isValid() )
        c = Qt::white;

    c = QColorDialog::getColor(c, this);

    if( c.isValid())
        lineEdit->setText(c.name(QColor::HexRgb).toUpper());
}

void SettingsDialog::updatePalette(QLineEdit *lineEdit)
{
    auto p = lineEdit->palette();
    auto c = QColor(lineEdit->text());
    p.setColor(QPalette::Base, c);
    p.setColor(QPalette::Text, c.lightnessF() >= 0.5 ? Qt::black : Qt::white );
    lineEdit->setPalette(p);
}

