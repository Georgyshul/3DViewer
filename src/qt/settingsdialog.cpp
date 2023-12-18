#include "settingsdialog.h"

#include "defines.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsDialog) {
  ui->setupUi(this);

  ui->comboBox_projection->setCurrentIndex(
      settings.value(Settings::PROJECTION).toInt());
  ui->comboBox_displayMethod->setCurrentIndex(
      settings.value(Settings::DISPLAY_METHOD).toInt());
  ui->comboBox_backgroundColor->setCurrentIndex(
      settings.value(Settings::BACKGROUND_COLOR).toInt());
  ui->comboBox_edgesColor->setCurrentIndex(
      settings.value(Settings::EDGES_COLOR).toInt());
  ui->comboBox_edgesType->setCurrentIndex(
      settings.value(Settings::EDGES_TYPE).toInt());
  ui->comboBox_edgesThickness->setCurrentIndex(
      settings.value(Settings::EDGES_THICKNESS).toInt());
  ui->comboBox_verticesColor->setCurrentIndex(
      settings.value(Settings::VERTICES_COLOR).toInt());
  ui->comboBox_verticesSize->setCurrentIndex(
      settings.value(Settings::VERTICES_SIZE).toInt());

  if (settings.value(Settings::DISPLAY_METHOD).toInt() ==
      Settings::DisplayMethod::none) {
    ui->comboBox_verticesColor->setEnabled(false);
    ui->comboBox_verticesSize->setEnabled(false);
  }
}

SettingsDialog::~SettingsDialog() { delete ui; }

void SettingsDialog::on_buttonBox_accepted() {
  settings.setValue(Settings::PROJECTION,
                    ui->comboBox_projection->currentIndex());
  settings.setValue(Settings::DISPLAY_METHOD,
                    ui->comboBox_displayMethod->currentIndex());
  settings.setValue(Settings::BACKGROUND_COLOR,
                    ui->comboBox_backgroundColor->currentIndex());
  settings.setValue(Settings::EDGES_COLOR,
                    ui->comboBox_edgesColor->currentIndex());
  settings.setValue(Settings::EDGES_TYPE,
                    ui->comboBox_edgesType->currentIndex());
  settings.setValue(Settings::EDGES_THICKNESS,
                    ui->comboBox_edgesThickness->currentIndex());
  settings.setValue(Settings::VERTICES_COLOR,
                    ui->comboBox_verticesColor->currentIndex());
  settings.setValue(Settings::VERTICES_SIZE,
                    ui->comboBox_verticesSize->currentIndex());
}

void SettingsDialog::on_comboBox_displayMethod_currentIndexChanged(int index) {
  if (index == Settings::DisplayMethod::none) {
    ui->comboBox_verticesColor->setEnabled(false);
    ui->comboBox_verticesSize->setEnabled(false);
  } else {
    ui->comboBox_verticesColor->setEnabled(true);
    ui->comboBox_verticesSize->setEnabled(true);
  }
}
