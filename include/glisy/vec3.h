#ifndef GLISY_VEC3_H
#define GLISY_VEC3_H

#include <time.h>
#include <math.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * vec3 struct type.
 */

typedef struct vec3 vec3;
struct vec3 { float x; float y; float z; };

/**
 * vec3 initializer.
 */

#define vec3(...)  ((vec3){ __VA_ARGS__ })
#define vec3_create() vec3(0, 0, 0)

/**
 * Clones and returns vec3.
 */

#define vec3_clone(vec) ((vec3) {(vec).x, (vec).y, (vec).z})

/**
 * Subtracts vec3 b from vec3 a.
 */

#define vec3_sub vec3_subtract
#define vec3_subtract(a, b) ((vec3) {((a).x - (b).x), \
                                     ((a).y - (b).y), \
                                     ((a).z - (b).z)})

/**
 * Multiply two vec3.
 */

#define vec3_mul vec3_multiply
#define vec3_multiply(a, b) ((vec3) {((a).x * (b).x), \
                                     ((a).y * (b).y), \
                                     ((a).z * (b).z)})

/**
 * Divide two vec3 a by vec3 b
 */

#define vec3_div vec3_divide
#define vec3_divide(a, b) ((vec3) {((a).x / (b).x), \
                                   ((a).y / (b).y), \
                                   ((a).z / (b).z)})

/**
 * Copy vec3 b into vec3 a
 */

#define vec3_copy(a, b)  ({       \
  vec3 *tmp = (vec3 *) &(a);      \
  (tmp->x = b.x);                 \
  (tmp->y = b.y);                 \
  (tmp->z = b.z);                 \
  (*tmp);                         \
})

/**
 * Sets x and y component of vec3.
 */

#define vec3_set(v, a, b, c)  ({       \
  vec3 *tmp = (vec3 *) &(v);           \
  tmp->x = ((float) a);                \
  tmp->y = ((float) b);                \
  tmp->z = ((float) c);                \
  (*tmp);                              \
})

/**
 * Add two vectors together.
 */

#define vec3_add(a, b) ((vec3) {((a).x + (b).x), \
                                ((a).y + (b).y), \
                                ((a).z + (b).z)})

/**
 * Returns the maximum of two vec3 inputs.
 */

#define vec3_max(a, b) ((vec3) {fmaxf((a).x, (b).x), \
                                fmaxf((a).y, (b).y), \
                                fmaxf((a).z, (b).z)})

/**
 * Returns the minimum of two vec3 inputs.
 */

#define vec3_min(a, b) ((vec3) {fminf((a).x, (b).x), \
                                fminf((a).y, (b).y), \
                                fminf((a).z, (b).z)})

/**
 * Scale a vec3 by a scalar number.
 */

#define vec3_scale(a, s) ((vec3) {((a).x * s), \
                                  ((a).y * s), \
                                  ((a).z * s)})

/**
 * Calculates the Euclidean distance for a vec3.
 */

#define vec3_distance(a, b) (float) sqrt(pow((b).x - (a).x, 2) + \
                                         pow((b).y - (a).y, 2) + \
                                         pow((b).z - (a).z, 2))

/**
 * Calculates the squared distance for a vec3.
 */

#define vec3_distance_squared(a, b) (float) (powf((b).x - (a).x, 2) + \
                                             powf((b).y - (a).y, 2) + \
                                             powf((b).z - (a).z, 2))

/**
 * Calculates the length of a vec3.
 */

#define vec3_length(a) (float) sqrt(powf((a).x, 2) + \
                                    powf((a).y, 2) + \
                                    powf((a).z, 2))

/**
 * Calculates the squard length of a vec3.
 */

#define vec3_length_squared(a) (float) (powf((a).x, 2) + \
                                        powf((a).y, 2) + \
                                        powf((a).z, 2))

/**
 * Returns the negation of a vec3.
 */

#define vec3_negate(a) ( vec3_scale((a), -1))

/**
 * Calculates the inverse of a vec3.
 */

#define vec3_inverse(a) ((vec3) {(1.0f/(a).x), \
                                 (1.0f/(a).y), \
                                 (1.0f/(a).z)})

/**
 * Returns a normalized vec3.
 */

#define vec3_normalize(a)  ({                                      \
  float len = ((a).x * (a).x) + ((a).y * (a).y) + ((a).z * (a).z); \
  vec3 vec = {0, 0, 0};                                            \
  if (len > 0) {                                                   \
    len = (1/sqrt(len));                                           \
    vec.x = ((a).x * len);                                         \
    vec.y = ((a).y * len);                                         \
    vec.z = ((a).z * len);                                         \
  }                                                                \
  (vec);                                                           \
})

/**
 * Calculates the dot product of vec3 a
 * and vec3 b.
 */

#define vec3_dot(a, b) (float) (((a).x * (b).x) + \
                                ((a).y * (b).y) + \
                                ((a).z * (b).z))

/**
 * Calculates the cross product of vec3 a
 * and vec3 b.
 */

#define vec3_cross(a, b) ((vec3) {((a).y * (b).z - (a).z * (b).y), \
                                  ((a).z * (b).x - (a).x * (b).z), \
                                  ((a).x * (b).y - (a).y * (b).x)})
/**
 * Calculates a linear interpolation between
 * vec3 a and vec3 b with interpolation factor t.
 */

#define vec3_lerp(a, b, t) ((vec3) {(a).x + t * ((b).x - (a).x), \
                                    (a).y + t * ((b).y - (a).y), \
                                    (a).z + t * ((b).z - (a).z)})

/**
 * Generates a random vec3 with scale.
 */

#define vec3_random(scale)  ({                   \
  srand((unsigned int) time(NULL));              \
  float rad = 2.0 * M_PI * rand();               \
  float z = (rand() * 2.0) - 1.0;                \
  float zs = sqrt(1.0 - z * z) * scale;          \
  (vec3(cosf(rad)*zs, sinf(rad)*zs, z*scale));   \
})

/**
 * Returns the angle between two vec3 vectors.
 */

#define vec3_angle(a, b) ({      \
  vec3 x = vec3_normalize((a));  \
  vec3 y = vec3_normalize((b));  \
  float angle = 0;               \
  float cosine = vec3_dot(x, y); \
  if (cosine > 1.0) cosine = 0;  \
  else cosine = acosf(cosine);   \
  (cosine);                      \
})

/**
 * Applies a mat4 to a vec3.
 */

#define vec3_transform_mat3(vec, mat) ({     \
  vec3 out;                                  \
  vec3 v = *(vec3* ) &(vec);                 \
  mat3 a = (mat3) (mat);                     \
  float x = v.x, y = v.y, z = v.z;           \
  out.x = x * a.m11 + y * a.m21 + z * a.m31; \
  out.y = x * a.m12 + y * a.m22 + z * a.m32; \
  out.z = x * a.m13 + y * a.m23 + z * a.m33; \
  (out);                                     \
})

  // @TODO(werle) - hermite
  // @TODO(werle) - bezier
  // @TODO(werle) - transform
  // @TODO(werle) - transformQuat

/**
 */

#define vec3_transform_mat4(vec, mat)  ({                              \
  vec3 out;                                                            \
  double x = (vec).x, y = (vec).y, z = (vec).z;                         \
  double w = (mat).m14 * x + (mat).m24 * y + (mat).m34 * z + (mat).m44; \
  w = w ? w : 1.0;                                                     \
  out.x = (mat.m11 * x + mat.m21 * y + mat.m31 * z + mat.m41) / w;     \
  out.y = (mat.m12 * x + mat.m22 * y + mat.m32 * z + mat.m42) / w;     \
  out.z = (mat.m13 * x + mat.m23 * y + mat.m33 * z + mat.m43) / w;     \
  (out);                                                               \
})

/**
 */

#define vec3_rotateX(vec, axis, origin, angle) ({ \
  vec3 p, r;                                      \
  p.x = (axis).x - (origin).x;                    \
  p.y = (axis).y - (origin).y;                    \
  p.z = (axis).z - (origin).z;                    \
  r.x = p.x;                                      \
  r.y = p.y * cosf(angle) - p.z * sinf(angle);    \
  r.z = p.y * sinf(angle) + p.z * cosf(angle);    \
  (vec).x = r.x + (origin).x;                     \
  (vec).y = r.y + (origin).y;                     \
  (vec).z = r.z + (origin).z;                     \
})

/**
 */

#define vec3_rotateY(vec, axis, origin, angle) ({ \
  vec3 p, r;                                      \
  p.x = (axis).x - (origin).x;                    \
  p.y = (axis).y - (origin).y;                    \
  p.z = (axis).z - (origin).z;                    \
  r.x = p.z * sinf(angle) + p.x * cosf(angle);    \
  r.y = p.y;                                      \
  r.z = p.z * cosf(angle) - p.x * sinf(angle);    \
  (vec).x = r.x + (origin).x;                     \
  (vec).y = r.y + (origin).y;                     \
  (vec).z = r.z + (origin).z;                     \
})

/**
 */

#define vec3_rotateZ(vec, axis, origin, angle) ({ \
  vec3 p, r;                                      \
  p.x = (axis).x - (origin).x;                    \
  p.y = (axis).y - (origin).y;                    \
  p.z = (axis).z - (origin).z;                    \
  r.x = p.x * cosf(angle) - p.y * sinf(angle);    \
  r.y = p.x * sinf(angle) + p.y * cosf(angle);    \
  r.z = p.z;                                      \
  (vec).x = r.x + (origin).x;                     \
  (vec).y = r.y + (origin).y;                     \
  (vec).z = r.z + (origin).z;                     \
})

/**
 * Returns a string representation of vec3 a.
 */

#define vec3_string(a) (const char *) ({                 \
  char str[BUFSIZ];                                      \
  memset(str, 0, BUFSIZ);                                \
  sprintf(str, "vec3(%g, %g, %g)", (a).x, (a).y, (a).z); \
  (strdup(str));                                         \
})

#ifdef __cplusplus
}
#endif
#endif
