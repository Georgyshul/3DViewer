#ifndef SRC_BACK_IO_OBJ_H_
#define SRC_BACK_IO_OBJ_H_

#include <stdbool.h>

#include "../obj/obj.h"

#define BUFFERSIZE 1024

obj_t *read_obj(const char *filename);
bool write_obj(const char *filename, obj_t *obj, const trans_setup_t *setup);

#endif  // SRC_BACK_IO_OBJ_H_
