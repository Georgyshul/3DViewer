#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

#include "glview.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
  Q_OBJECT

 public:
  explicit SettingsDialog(QWidget *parent = nullptr);
  ~SettingsDialog();

 private slots:
  void on_buttonBox_accepted();

  void on_comboBox_displayMethod_currentIndexChanged(int index);

 private:
  Ui::SettingsDialog *ui;

  QSettings settings;
};

#endif  // SETTINGSDIALOG_H
