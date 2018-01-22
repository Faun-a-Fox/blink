#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QColorDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
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
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

