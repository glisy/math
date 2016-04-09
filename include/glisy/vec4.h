#ifndef GLISY_VEC4_H
#define GLISY_VEC4_H

#include <time.h>
#include <math.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * vec4 struct type.
 */

typedef struct vec4 vec4;
struct vec4 { float x; float y; float z; float w; };

/**
 * vec4 initializer.
 */

#define vec4(...) (vec4) { __VA_ARGS__ }
#define vec4_create() vec4(0, 0, 0, 0)

/**
 * Clones and returns vec4.
 */

#define vec4_clone(vec) ((vec4) {(ve)c.x, (vec).y, (vec).z, (vec).w})

/**
 * Subtracts vec4 b from vec4 a.
 */

#define vec4_sub vec4_subtract
#define vec4_subtract(a, b) ((vec4) {((a).x - (b).x), \
                                     ((a).y - (b).y), \
                                     ((a).z - (b).z), \
                                     ((a).w - (b).w)})

/**
 * Multiply two vec4.
 */

#define vec4_mul vec4_multiply
#define vec4_multiply(a, b) ((vec4) {((a).x * (b).x), \
                                     ((a).y * (b).y), \
                                     ((a).z * (b).z), \
                                     ((a).w * (b).w)})

/**
 * Divide two vec4 a by vec4 b
 */

#define vec4_div vec4_divide
#define vec4_divide(a, b) ((vec4) {((a).x / (b).x), \
                                   ((a).y / (b).y), \
                                   ((a).z / (b).z), \
                                   ((a).w / (b).w)})

/**
 * Copy vec4 b into vec4 a
 */

#define vec4_copy(a, b) (vec4) ({ \
  vec4 *tmp = &(a);               \
  (tmp->x = b.x);                 \
  (tmp->y = b.y);                 \
  (tmp->z = b.z);                 \
  (tmp->w = b.w);                 \
  (*tmp);                         \
})

/**
 * Sets x and y component of vec4.
 */

#define vec4_set(v, a, b, c, d) (vec4) ({ \
  vec4 *tmp = &(v);                       \
  tmp->x = ((float) a);                   \
  tmp->y = ((float) b);                   \
  tmp->z = ((float) c);                   \
  tmp->w = ((float) d);                   \
  (*tmp);                                 \
})

/**
 * Add two vectors together.
 */

#define vec4_add(a, b) ((vec4) {((a).x + (b).x), \
                                ((a).y + (b).y), \
                                ((a).z + (b).z), \
                                ((a).w + (b).w)})

/**
 * Returns the maximum of two vec4 inputs.
 */

#define vec4_max(a, b) ((vec4) {fmaxf((a).x, (b).x), \
                                fmaxf((a).y, (b).y), \
                                fmaxf((a).z, (b).z), \
                                fmaxf((a).w, (b).w)})

/**
 * Returns the minimum of two vec4 inputs.
 */

#define vec4_min(a, b) ((vec4) {fminf((a).x, (b).x), \
                                fminf((a).y, (b).y), \
                                fminf((a).z, (b).z), \
                                fminf((a).w, (b).w)})

/**
 * Scale a vec4 by a scalar number.
 */

#define vec4_scale(a, s) ((vec4) {((a).x * s), \
                                  ((a).y * s), \
                                  ((a).z * s), \
                                  ((a).w * s)})

/**
 * Calculates the Euclidean distance for a vec4.
 */

#define vec4_distance(a, b) (float) sqrt(pow((b).x - (a).x, 2) + \
                                         pow((b).y - (a).y, 2) + \
                                         pow((b).z - (a).z, 2) + \
                                         pow((b).w - (a).w, 2))

/**
 * Calculates the squared distance for a vec4.
 */

#define vec4_distance_squared(a, b) (float) (powf((b).x - (a).x, 2) + \
                                             powf((b).y - (a).y, 2) + \
                                             powf((b).z - (a).z, 2) + \
                                             powf((b).w - (a).w, 2))

/**
 * Calculates the length of a vec4.
 */

#define vec4_length(a) (float) sqrt(powf((a).x, 2) + \
                                    powf((a).y, 2) + \
                                    powf((a).z, 2) + \
                                    powf((a).w, 2))

/**
 * Calculates the squard length of a vec4.
 */

#define vec4_length_squared(a) (float) (powf((a).x, 2) + \
                                        powf((a).y, 2) + \
                                        powf((a).z, 2) + \
                                        powf((a).w, 2))

/**
 * Returns the negation of a vec4.
 */

#define vec4_negate(a) ((vec4) vec4_scale((a), -1)

/**
 * Calculates the inverse of a vec4.
 */

#define vec4_inverse(a) ((vec4) {(1.0f/(a).x), \
                                 (1.0f/(a).y), \
                                 (1.0f/(a).z), \
                                 (1.0f/(a).w)})

/**
 * Returns a normalized vec4.
 */

#define vec4_normalize(a) (vec4) ({    \
  float len = ((a).x * (a).x) +        \
              ((a).y * (a).y) +        \
              ((a).z * (a).z) +        \
              ((a).w * (a).w);         \
  vec4 vec = vec4(0);                  \
  if (len > 0) {                       \
    len = (1/sqrt(len));               \
    vec.x = ((a).x * len);             \
    vec.y = ((a).y * len);             \
    vec.z = ((a).z * len);             \
    vec.w = ((a).w * len);             \
  }                                    \
  (vec);                               \
})

/**
 * Calculates the dot product of vec4 a
 * and vec4 b.
 */

#define vec4_dot(a, b) (float) (((a).x * (b).x) + \
                                ((a).y * (b).y) + \
                                ((a).z * (b).z) + \
                                ((a).w * (b).w))
/**
 * Calculates a linear interpolation between
 * vec4 a and vec4 b with interpolation factor t.
 */

#define vec4_lerp(a, b, t) ((vec4) {(a).x + t * ((b).x - (a).x), \
                                    (a).y + t * ((b).y - (a).y), \
                                    (a).z + t * ((b).z - (a).z), \
                                    (a).w + t * ((b).w - (a).w)})
/**
 * Returns a string representation of vec4 a.
 */

#define vec4_string(a) (const char *) ({                            \
  char str[BUFSIZ];                                                 \
  memset(str, 0, BUFSIZ);                                           \
  sprintf(str, "vec4(%g, %g, %g, %g)", (a).x, (a).y, (a).z, (a).w); \
  (strdup(str));                                                    \
})

#ifdef __cplusplus
}
#endif
#endif
