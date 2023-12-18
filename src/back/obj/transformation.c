#include "transformation.h"

#include <math.h>
#include <stdlib.h>

void translation(double *vertex, int size, double t_x, double t_y, double t_z);

void rotation_Ox(double *vertex, int size, double angle_Ox);
void rotation_Oy(double *vertex, int size, double angle_Oy);
void rotation_Oz(double *vertex, int size, double angle_Oz);

void scaling(double *vertex, int size, double s_x, double s_y, double s_z);

void transformation(double *vertex, int size, const trans_setup_t *setup) {
  if (setup == NULL) {
    return;
  }

  scaling(vertex, size, setup->s_x, setup->s_y, setup->s_z);
  rotation_Ox(vertex, size, setup->angle_Ox);
  rotation_Oy(vertex, size, setup->angle_Oy);
  rotation_Oz(vertex, size, setup->angle_Oz);
  translation(vertex, size, setup->t_x, setup->t_y, setup->t_z);
}

void init_trans_setup(trans_setup_t *setup, double t_x, double t_y, double t_z,
                      double s_x, double s_y, double s_z, double angle_Ox,
                      double angle_Oy, double angle_Oz) {
  setup->t_x = t_x;
  setup->t_y = t_y;
  setup->t_z = t_z;

  setup->s_x = s_x;
  setup->s_y = s_y;
  setup->s_z = s_z;

  setup->angle_Ox = angle_Ox;
  setup->angle_Oy = angle_Oy;
  setup->angle_Oz = angle_Oz;
}

void translation(double *vertex, int size, double t_x, double t_y, double t_z) {
  for (int i = 0; i < size; ++i) {
    vertex[i * 3] += t_x;
    vertex[i * 3 + 1] += t_y;
    vertex[i * 3 + 2] += t_z;
  }
}

void rotation_Ox(double *vertex, int size, double angle_Ox) {
  for (int i = 0; i < size; ++i) {
    double y = vertex[i * 3 + 1];
    double z = vertex[i * 3 + 2];

    vertex[i * 3 + 1] = y * cos(angle_Ox) - z * sin(angle_Ox);
    vertex[i * 3 + 2] = y * sin(angle_Ox) + z * cos(angle_Ox);
  }
}

void rotation_Oy(double *vertex, int size, double angle_Oy) {
  for (int i = 0; i < size; ++i) {
    double x = vertex[i * 3];
    double z = vertex[i * 3 + 2];

    vertex[i * 3] = x * cos(angle_Oy) + z * sin(angle_Oy);
    vertex[i * 3 + 2] = x * (-sin(angle_Oy)) + z * cos(angle_Oy);
  }
}

void rotation_Oz(double *vertex, int size, double angle_Oz) {
  for (int i = 0; i < size; ++i) {
    double x = vertex[i * 3];
    double y = vertex[i * 3 + 1];

    vertex[i * 3] = x * cos(angle_Oz) - y * sin(angle_Oz);
    vertex[i * 3 + 1] = x * sin(angle_Oz) + y * cos(angle_Oz);
  }
}

void scaling(double *vertex, int size, double s_x, double s_y, double s_z) {
  for (int i = 0; i < size; ++i) {
    vertex[i * 3] *= s_x;
    vertex[i * 3 + 1] *= s_y;
    vertex[i * 3 + 2] *= s_z;
  }
}
