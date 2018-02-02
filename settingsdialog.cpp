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

    connect(ui->toolButton_Color, &QToolButton::clicked, [this]()
    {
        auto c = QColor(ui->lineEdit_Color->text());

        if( !c.isValid() )
            c = Qt::white;

        c = QColorDialog::getColor(c, this);

        if( c.isValid())
            ui->lineEdit_Color->setText(c.name(QColor::HexRgb).toUpper());
    });

    connect(ui->lineEdit_Color, &QLineEdit::textChanged, [this]()
    {
        auto p = ui->lineEdit_Color->palette();
        auto c = QColor(ui->lineEdit_Color->text());
        p.setColor(QPalette::Base, c);
        p.setColor(QPalette::Text, c.lightnessF() >= 0.5 ? Qt::black : Qt::white );
        ui->lineEdit_Color->setPalette(p);
    });

    /// Load values

    ui->spinBox_Duration->setValue(settings->value(SET_BLINKDURATION_INT).toInt());
    ui->spinBox_Interval->setValue(settings->value(SET_BLINKINTERVAL_INT).toInt());
    ui->lineEdit_Color->setText(settings->value(SET_BLINKCOLOR_STR).toString());
    ui->spinBox_Opacity->setValue(settings->value(SET_BLINKOPACITY_INT).toInt());

    /// Connect values

    connect(this, &SettingsDialog::accepted, [this, settings]()
    {
        settings->setValue(SET_BLINKDURATION_INT, ui->spinBox_Duration->value());
        settings->setValue(SET_BLINKINTERVAL_INT, ui->spinBox_Interval->value());
        settings->setValue(SET_BLINKCOLOR_STR, ui->lineEdit_Color->text());
        settings->setValue(SET_BLINKOPACITY_INT, ui->spinBox_Opacity->value());
    });

    /*
    connect(ui->spinBox_Duration, &QSpinBox::valueChanged, [this]()
    {
        this->settings->setValue(SET_BLINKDURATION_INT, ui->spinBox_Duration->value());
    });

    connect(ui->spinBox_Interval, &QSpinBox::valueChanged, [this]()
    {
        ;
    });

    connect(ui->lineEdit_Color, &QLineEdit::textChanged, [this]()
    {
        ;
    });
    */

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

