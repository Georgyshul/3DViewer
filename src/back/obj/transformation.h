#ifndef SRC_BACK_OBJ_TRANSFORMATION_H_
#define SRC_BACK_OBJ_TRANSFORMATION_H_

typedef struct transformation_setup {
  double t_x;
  double t_y;
  double t_z;

  double s_x;
  double s_y;
  double s_z;

  double angle_Ox;
  double angle_Oy;
  double angle_Oz;
} trans_setup_t;

void transformation(double *vertex, int size, const trans_setup_t *setup);
void init_trans_setup(trans_setup_t *setup, double t_x, double t_y, double t_z,
                      double s_x, double s_y, double s_z, double angle_Ox,
                      double angle_Oy, double angle_Oz);

#endif  // SRC_BACK_OBJ_TRANSFORMATION_H_
