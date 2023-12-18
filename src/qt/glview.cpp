#include "glview.h"

#include <QPainter>
#include <cmath>

#include "defines.h"

glView::glView(QWidget *parent) : QOpenGLWidget(parent) {
  connect(&tmr, SIGNAL(timeout()), this, SLOT(update()));
  tmr.start(100);

  init_trans_setup(&this->setup, 0, 0, 0, 1, 1, 1, 0, 0, 0);
}

glView::~glView() {
  if (this->gl_obj != nullptr) free_gl_obj(this->gl_obj);
  if (this->obj != nullptr) free_obj(&this->obj);
}

void glView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void glView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void glView::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  loadSettings();

  glTranslatef(0, 0, this->distance);
  glRotatef(xRotCur + xRot, 1, 0, 0);
  glRotatef(yRotCur + yRot, 0, 1, 0);

  if (this->gl_obj != nullptr) {
    gl_obj_t *tmp = copy_gl_obj_transforation(this->gl_obj, &this->setup);

    this->drawFacets(tmp);
    this->drawVertexes(tmp);

    free_gl_obj(tmp);
  }
}

void glView::drawFacets(const gl_obj_t *tmp) {
  this->loadSettingsEdgesColor();
  for (int i = 0; i < tmp->num_facets; ++i) {
    glVertexPointer(3, GL_DOUBLE, 0, tmp->facets[i]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_LINE_LOOP, 0, tmp->line_sizes[i]);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void glView::drawVertexes(const gl_obj_t *tmp) {
  QSettings settings;
  this->loadSettingsVertexesColor();

  if (settings.value(Settings::DISPLAY_METHOD) !=
      Settings::DisplayMethod::none) {
    glVertexPointer(3, GL_DOUBLE, 0, tmp->vertexes);
    glEnableClientState(GL_VERTEX_ARRAY);
    if (settings.value(Settings::DISPLAY_METHOD) ==
        Settings::DisplayMethod::circle)
      glEnable(GL_POINT_SMOOTH);
    glPointSize(this->vertexesSize);
    glDrawArrays(GL_POINTS, 0, tmp->num_vertexes);
    if (settings.value(Settings::DISPLAY_METHOD) ==
        Settings::DisplayMethod::circle)
      glDisable(GL_POINT_SMOOTH);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void glView::loadSettings() {
  QSettings settings;

  switch (settings.value(Settings::BACKGROUND_COLOR).toInt()) {
    case Settings::Color::white:
      glClearColor(1, 1, 1, 0);
      break;
    case Settings::Color::black:
      glClearColor(0, 0, 0, 0);
      break;
    case Settings::Color::red:
      glClearColor(1, 0, 0, 0);
      break;
    case Settings::Color::blue:
      glClearColor(0, 0, 1, 0);
      break;
    case Settings::Color::green:
      glClearColor(0, 1, 0, 0);
      break;
  }

  if (this->gl_obj != nullptr) {
    switch (settings.value(Settings::PROJECTION).toInt()) {
      case Settings::Projection::central:
        glFrustum(-1, 1, -1, 1, 1, 100 - this->distance);
        break;
      case Settings::Projection::parallel:
        glOrtho(-1, 1, -1, 1, 1, 100 - this->distance);
        break;
    }
  }

  switch (settings.value(Settings::EDGES_TYPE).toInt()) {
    case Settings::EdgesType::solid:
      glDisable(GL_LINE_STIPPLE);
      break;
    case Settings::EdgesType::dashed:
      glLineStipple(1, 10);
      glEnable(GL_LINE_STIPPLE);
      break;
  }

  switch (settings.value(Settings::EDGES_THICKNESS).toInt()) {
    case Settings::EdgesThickness::thin:
      glLineWidth(1);
      break;
    case Settings::EdgesThickness::normal:
      glLineWidth(3);
      break;
    case Settings::EdgesThickness::thick:
      glLineWidth(10);
      break;
  }

  switch (settings.value(Settings::VERTICES_SIZE).toInt()) {
    case Settings::VerticesSize::little:
      this->vertexesSize = 5;
      break;
    case Settings::VerticesSize::pepe:
      this->vertexesSize = 10;
      break;
    case Settings::VerticesSize::big:
      this->vertexesSize = 25;
      break;
  }
}

void glView::loadSettingsEdgesColor() {
  QSettings settings;

  switch (settings.value(Settings::EDGES_COLOR).toInt()) {
    case Settings::Color::white:
      glColor3d(1, 1, 1);
      break;
    case Settings::Color::black:
      glColor3d(0, 0, 0);
      break;
    case Settings::Color::red:
      glColor3d(1, 0, 0);
      break;
    case Settings::Color::blue:
      glColor3d(0, 0, 1);
      break;
    case Settings::Color::green:
      glColor3d(0, 1, 0);
      break;
  }
}

void glView::loadSettingsVertexesColor() {
  QSettings settings;

  switch (settings.value(Settings::VERTICES_COLOR).toInt()) {
    case Settings::Color::white:
      glColor3d(1, 1, 1);
      break;
    case Settings::Color::black:
      glColor3d(0, 0, 0);
      break;
    case Settings::Color::red:
      glColor3d(1, 0, 0);
      break;
    case Settings::Color::blue:
      glColor3d(0, 0, 1);
      break;
    case Settings::Color::green:
      glColor3d(0, 1, 0);
      break;
  }
}

void glView::drawFile(const std::string &file) {
  if (this->obj != nullptr) free_obj(&this->obj);
  this->obj = read_obj(file.c_str());
  if (this->obj == nullptr) return;

  if (this->gl_obj != nullptr) free_gl_obj(this->gl_obj);
  this->gl_obj = gl_line_loop(obj);

  resetView();
}

void glView::mousePressEvent(QMouseEvent *mo) { this->mPos = mo->pos(); }

void glView::mouseReleaseEvent(QMouseEvent *) {
  this->xRotCur = std::fmod<float>(this->xRotCur + this->xRot, 360);
  this->yRotCur = std::fmod<float>(this->yRotCur + this->yRot, 360);
  this->xRot = 0;
  this->yRot = 0;

  this->updateFL();
}

void glView::mouseMoveEvent(QMouseEvent *mo) {
  this->xRot = 1 / M_PI * (mo->pos().y() - this->mPos.y());
  this->yRot = 1 / M_PI * (mo->pos().x() - this->mPos.x());

  this->updateFL();
}

void glView::wheelEvent(QWheelEvent *event) {
  this->distance = std::min<float>(
      this->distance + event->angleDelta().y() / 180.0, DISTANCE_MIN);

  this->updateFL();
}

void glView::updateFL() {
  if (this->gl_obj != nullptr) update();
}

void glView::resetView() {
  this->xRotCur = 0;
  this->yRotCur = 0;
  this->zRotCur = 0;
  this->distance = DISTANCE_DEFAULT;

  this->updateFL();
}
