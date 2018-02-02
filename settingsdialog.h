#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QSettings* settings, QWidget *parent = 0);
    ~SettingsDialog();

private:
    QSettings *settings;
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
