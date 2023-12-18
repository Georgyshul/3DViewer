#ifndef GLVIEW_H
#define GLVIEW_H

#define GL_SILENCE_DEPRECATION
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QWidget>

extern "C" {
#include "../back/gl_obj/gl_obj.h"
#include "../back/io_obj/io_obj.h"
#include "../back/obj/obj.h"
}

#define DISTANCE_MIN -1
#define DISTANCE_DEFAULT -3

class glView : public QOpenGLWidget {
  Q_OBJECT

 private:
  gl_obj_t *gl_obj = nullptr;
  QTimer tmr;

  float xRot, yRot, zRot;
  float xRotCur = 0, yRotCur = 0, zRotCur = 0;
  QPoint mPos;

  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

  float distance = DISTANCE_DEFAULT;
  void wheelEvent(QWheelEvent *event) override;

  void drawFacets(const gl_obj_t *gl_obj);
  void drawVertexes(const gl_obj_t *gl_obj);

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 public:
  glView(QWidget *parent);
  ~glView();

  trans_setup_t setup;
  obj_t *obj = nullptr;

  void updateFL();
  void resetView();
  void drawFile(const std::string &filename);

  void loadSettings();
  void loadSettingsVertexesColor();
  void loadSettingsEdgesColor();

  double vertexesSize;

 public slots:
};

#endif  // GLVIEW_H
