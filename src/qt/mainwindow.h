#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

#include "QtGifImage-master/src/gifimage/qgifimage.h"
#include "defines.h"
#include "glview.h"
#include "settingsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_spinBox_xRotObj_valueChanged(int arg1);
  void on_spinBox_yRotObj_valueChanged(int arg1);
  void on_spinBox_zRotObj_valueChanged(int arg1);

  void on_spinBox_xTranslation_valueChanged(int arg1);
  void on_spinBox_yTranslation_valueChanged(int arg1);
  void on_spinBox_zTranslation_valueChanged(int arg1);

  void on_spinBox_xScaling_valueChanged(int arg1);
  void on_spinBox_yScaling_valueChanged(int arg1);
  void on_spinBox_zScaling_valueChanged(int arg1);

  void on_pushButton_back_clicked();

  void on_actionOpen_File_triggered();
  void on_actionSave_As_triggered();
  void on_actionSettings_triggered();
  void on_actionImport_to_JPEG_triggered();
  void on_actionImport_to_BMP_triggered();
  void on_actionImport_to_GIF_triggered();

  void oneGif();

 private:
  Ui::MainWindow *ui;

  QSettings settings;

  QString getDir(const QString &filePath);

  void updateFile(const QString fileName);
  void updateCurrentDir(const QString &dir);
  void initSettings();
  void resetSetup();

  int startTime, tmpTime;
  float timePrint;
  const int gifFps = 10, gifLength = 5;
  QTimer *timer;
  QGifImage *gif;
  QString GIFfileName;
};
#endif  // MAINWINDOW_H
