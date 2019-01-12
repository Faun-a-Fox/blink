#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

#include <QLineEdit>

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

    void querryColor(QLineEdit *);
    void updatePalette(QLineEdit *);
};

#endif // SETTINGSDIALOG_H
