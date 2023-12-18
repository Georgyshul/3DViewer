#include "mainwindow.h"

#include <QSettings>

#include "defines.h"
#include "ui_mainwindow.h"

extern "C" {
#include "../back/io_obj/io_obj.h"
#include "../back/obj/obj.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  initSettings();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateFile(QString fileName) {
  resetSetup();

  this->ui->openGLWidget->drawFile(fileName.toStdString());
  this->ui->lineFileName->setText(fileName);

  if (this->ui->openGLWidget->obj != nullptr) {
    this->ui->actionSave_As->setEnabled(true);
  } else {
    this->ui->actionSave_As->setEnabled(false);
  }

  this->ui->lineFacets->setText(
      QString::number(this->ui->openGLWidget->obj->num_facets));
  this->ui->lineVertexes->setText(
      QString::number(this->ui->openGLWidget->obj->num_vertexes));
}

void MainWindow::updateCurrentDir(const QString &dir) {
  this->settings.setValue(Settings::CURRENT_DIR, dir);
}

void MainWindow::initSettings() {
  if (!this->settings.contains(Settings::CURRENT_DIR)) {
    this->settings.setValue(Settings::CURRENT_DIR, qApp->applicationDirPath());
  }
  if (!this->settings.contains(Settings::PROJECTION)) {
    this->settings.setValue(Settings::PROJECTION,
                            Settings::Default::PROJECTION);
  }
  if (!this->settings.contains(Settings::BACKGROUND_COLOR)) {
    this->settings.setValue(Settings::BACKGROUND_COLOR,
                            Settings::Default::BACKGROUND_COLOR);
  }
  if (!this->settings.contains(Settings::DISPLAY_METHOD)) {
    this->settings.setValue(Settings::DISPLAY_METHOD,
                            Settings::Default::DISPLAY_METHOD);
  }
  if (!this->settings.contains(Settings::EDGES_COLOR)) {
    this->settings.setValue(Settings::EDGES_COLOR,
                            Settings::Default::EDGES_COLOR);
  }
  if (!this->settings.contains(Settings::EDGES_TYPE)) {
    this->settings.setValue(Settings::EDGES_TYPE,
                            Settings::Default::EDGES_TYPE);
  }
  if (!this->settings.contains(Settings::EDGES_THICKNESS)) {
    this->settings.setValue(Settings::EDGES_THICKNESS,
                            Settings::Default::EDGES_THICKNESS);
  }
  if (!this->settings.contains(Settings::VERTICES_COLOR)) {
    this->settings.setValue(Settings::VERTICES_COLOR,
                            Settings::Default::VERTICES_COLOR);
  }
  if (!this->settings.contains(Settings::VERTICES_SIZE)) {
    this->settings.setValue(Settings::VERTICES_SIZE,
                            Settings::Default::VERTICES_SIZE);
  }
}

QString MainWindow::getDir(const QString &filePath) {
  QDir dir = filePath;
  dir.cdUp();
  return dir.path();
}

void MainWindow::on_spinBox_xRotObj_valueChanged(int arg1) {
  this->ui->openGLWidget->setup.angle_Ox = arg1 * M_PI / 180;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_spinBox_yRotObj_valueChanged(int arg1) {
  this->ui->openGLWidget->setup.angle_Oy = arg1 * M_PI / 180;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_spinBox_zRotObj_valueChanged(int arg1) {
  this->ui->openGLWidget->setup.angle_Oz = arg1 * M_PI / 180;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_spinBox_xTranslation_valueChanged(int arg1) {
  this->ui->openGLWidget->setup.t_x = arg1;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_spinBox_yTranslation_valueChanged(int arg1) {
  this->ui->openGLWidget->setup.t_y = arg1;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_spinBox_zTranslation_valueChanged(int arg1) {
  this->ui->openGLWidget->setup.t_z = arg1;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_spinBox_xScaling_valueChanged(int arg1) {
  this->ui->openGLWidget->setup.s_x = arg1 / 100.0;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_spinBox_yScaling_valueChanged(int arg1) {
  this->ui->openGLWidget->setup.s_y = arg1 / 100.0;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_spinBox_zScaling_valueChanged(int arg1) {
  this->ui->openGLWidget->setup.s_z = arg1 / 100.0;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_pushButton_back_clicked() {
  this->ui->openGLWidget->resetView();
  this->ui->openGLWidget->updateFL();
}

void MainWindow::resetSetup() {
  init_trans_setup(&this->ui->openGLWidget->setup, 0, 0, 0, 1, 1, 1, 0, 0, 0);

  this->ui->spinBox_xTranslation->setValue(0);
  this->ui->spinBox_yTranslation->setValue(0);
  this->ui->spinBox_zTranslation->setValue(0);

  this->ui->spinBox_xRotObj->setValue(0);
  this->ui->spinBox_yRotObj->setValue(0);
  this->ui->spinBox_zRotObj->setValue(0);

  this->ui->spinBox_xScaling->setValue(100);
  this->ui->spinBox_yScaling->setValue(100);
  this->ui->spinBox_zScaling->setValue(100);

  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_actionOpen_File_triggered() {
  QString filePath = QFileDialog::getOpenFileName(
      this, "Open a file",
      this->settings.value(Settings::CURRENT_DIR).toString(), "Obj(*.obj)");
  if (filePath == "") return;

  updateCurrentDir(getDir(filePath));
  updateFile(filePath);
}

void MainWindow::on_actionSave_As_triggered() {
  QString fileName =
      QFileDialog::getSaveFileName(this, "Save file", nullptr, "Obj(*.obj)");
  if (fileName.isNull()) return;
  write_obj(fileName.toStdString().c_str(), this->ui->openGLWidget->obj,
            &this->ui->openGLWidget->setup);
}

void MainWindow::on_actionSettings_triggered() {
  SettingsDialog *settings = new SettingsDialog(this);
  settings->exec();
  delete settings;
  this->ui->openGLWidget->updateFL();
}

void MainWindow::on_actionImport_to_JPEG_triggered() {
  QString fileName =
      QFileDialog::getSaveFileName(this, "Save file", nullptr, "Image(*.jpeg)");
  if (fileName.isNull()) return;
  this->ui->openGLWidget->grabFramebuffer().save(fileName, "jpeg");
}

void MainWindow::on_actionImport_to_BMP_triggered() {
  QString fileName =
      QFileDialog::getSaveFileName(this, "Save file", nullptr, "Image(*.bmp)");
  if (fileName.isNull()) return;
  this->ui->openGLWidget->grabFramebuffer().save(fileName, "bmp");
}

void MainWindow::on_actionImport_to_GIF_triggered() {
  GIFfileName =
      QFileDialog::getSaveFileName(this, "Save file", nullptr, "Image(*.gif)");
  if (GIFfileName.isNull()) return;

  gif = new QGifImage;
  gif->setDefaultDelay(1000 / gifFps);
  startTime = 0, tmpTime = 1000 / gifFps;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(oneGif()));
  timer->start(1000 / gifFps);

  this->ui->actionImport_to_GIF->setEnabled(false);
  this->ui->label_recordingGIF->setText("Recording GIF...");
}

void MainWindow::oneGif() {
  if (startTime == tmpTime) {
    QPixmap screenGIF(this->ui->openGLWidget->size());
    this->ui->openGLWidget->render(&screenGIF);
    QImage image = screenGIF.toImage();
    gif->addFrame(image, 1000 / gifFps);
    timePrint = (float)startTime / 1e3;  // GIF time in seconds
    tmpTime += 1000 / gifFps;
  }
  if (startTime == 1000 * gifLength) {
    gif->save(GIFfileName);
    timer->stop();

    disconnect(timer, SIGNAL(timeout()), this, SLOT(oneGif()));

    delete gif;
    delete timer;

    this->ui->actionImport_to_GIF->setEnabled(true);
    this->ui->label_recordingGIF->setText("");
  }
  startTime += 1000 / gifFps;
}
