#ifndef GLISY_QUAT_H
#define GLISY_QUAT_H

#include <glisy/mat3.h>
#include <glisy/vec4.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VAR_PTR_ACCESS(m, x) (*((float *) (&(m) + (x)))
#define VAR_PTR_SET(m, x, v) ({         \
  float *ptr = ((float *) (&(m) + (x)); \
  *ptr = v;                             \
})

/**
 * quat struct type.
 */

typedef struct quat quat;
struct quat { float x; float y; float z; float w; };

/**
 * quat initializers.
 */

#define quat(...)  { __VA_ARGS__ }
#define quat_create() quat(0, 0, 0, 1)
#define quat_identity(q) quat_set(q, 0, 0, 0, 1)

/**
 * Inherit vec4 routines.
 */

#define quat_length_squared(...) vec4_length_squared(__VA_ARGS__)
#define quat_normalize(...) vec4_normalize(__VA_ARGS__)
#define quat_length(...) vec4_length(__VA_ARGS__)
#define quat_clone(...) vec4_clone(__VA_ARGS__)
#define quat_scale(...) vec4_scale(__VA_ARGS__)
#define quat_copy(...) vec4_copy(__VA_ARGS__)
#define quat_lerp(...) vec4_lerp(__VA_ARGS__)
#define quat_set(...) vec4_set(__VA_ARGS__)
#define quat_add(...) vec4_add(__VA_ARGS__)
#define quat_dot(...) vec4_dot(__VA_ARGS__)

/**
 * Sets the specified quaternion with values corresponding to the given
 * axes with the view, right, and up vec3 vectors.
 */

#define quat_set_axes(q, view, right, up)  ({       \
  mat3 a = mat3(0);                                 \
  a.m11 = (right).x;                                \
  a.m21 = (right).y;                                \
  a.m31 = (right).z;                                \
  a.m12 = (up).x;                                   \
  a.m22 = (up).y;                                   \
  a.m32 = (up).z;                                   \
  a.m13 = -(view).x;                                \
  a.m23 = -(view).y;                                \
  a.m33 = -(view).z;                                \
  (quat_normalize((q), quat_from_mat3((a)));        \
})

/**
 * Sets a quat from the given angle and rotation axis,
 * then returns it.
 */

#define quat_set_axis_angle(q, axis, rad)  ({       \
  float r = rad * 0.5;                              \
  float s = sinf(r);                                \
  float c = cosf(r);                                \
  (q).x = s * (axis).x;                             \
  (q).y = s * (axis).y;                             \
  (q).z = s * (axis).z;                             \
  (q).w = c;                                        \
  (q);                                              \
})

/**
 * Multiply two quats
 */

#define quat_multiply(a, b) ({                          \
  float ax = (a).x, ay = (a).y, az = (a).z, aw = (a).w; \
  float bx = (b).x, by = (b).y, bz = (b).z, bw = (b).w; \
  (quat(ax * bw + aw * bx + ay * bz - az * by,          \
        ay * bw + aw * by + az * bx - ax * bz,          \
        az * bw + aw * bz + ax * by - ay * bx,          \
        aw * bw - ax * bx - ay * by - az * bz));        \
})

/**
 * Rotates a quaternion by the given angle around the X axis
 */

#define quat_rotateX(q, rad) ({                         \
  float r = rad * 0.5;                                  \
  float ax = (q).x, ay = (q).y, az = (q).z, aw = (q).w; \
  float bx = sinf(r), bw = cosf(r);                     \
  (q).x = ax * bw + aw * bx;                            \
  (q).y = ay * bw + az * bx;                            \
  (q).z = az * bw - ay * bx;                            \
  (q).w = aw * bw - ax * bx;                            \
  (q);                                                  \
})

/**
 * Rotates a quaternion by the given angle around the Y axis
 */

#define quat_rotateY(q, rad) ({                         \
  float r = rad * 0.5;                                  \
  float r = rad * 0.5;                                  \
  float ax = (q).x, ay = (q).y, az = (q).z, aw = (q).w; \
  float bx = sinf(r), bw = cosf(r);                     \
  (q).x = ax * bw - az * bx;                            \
  (q).y = ay * bw + aw * bx;                            \
  (q).z = az * bw + ax * bx;                            \
  (q).w = aw * bw - ay * bx;                            \
  (q);                                                  \
})

/**
 * Rotates a quaternion by the given angle around the Z axis
 */

#define quat_rotateZ(q, rad) ({                         \
  float r = rad * 0.5;                                  \
  float ax = (q).x, ay = (q).y, az = (q).z, aw = (q).w; \
  float bx = sinf(r), bw = cosf(r);                     \
  (q).x = ax * bw + ay * bx;                            \
  (q).y = ay * bw - ax * bx;                            \
  (q).z = az * bw + aw * bx;                            \
  (q).w = aw * bw - az * bx;                            \
  (q);                                                  \
})

/**
 * Calculates the W component of a quat from the X, Y,
 * and Z components. Assumes that quaternion is 1 unit
 * in length. Any existing W component will be ignored.
 */

#define quat_calculateW(a)  ({                     \
  float x = (a).x, y = (a).y, z = (a).z;           \
  (a).w = sqrt(abs(1.0 - x * x - y * y - z * z));  \
})

/**
 * Performs a linear interpolation between two quat.
 */

#define quat_slerp(q, a, b, t)  ({                      \
  float ax = (a).x, ay = (a).y, az = (a).z, aw = (a).w; \
  float bx = (b).x, by = (b).y, bz = (b).z, bw = (b).w; \
  float omega, sinom, scale0, scale1;                   \
  float cosom = ax * bx + ay * by + az * bz + aw * bw;  \
  if ( cosom < 0.0 ) {                                  \
    cosom = -cosom;                                     \
    bx = - bx;                                          \
    by = - by;                                          \
    bz = - bz;                                          \
    bw = - bw;                                          \
  }                                                     \
  if ((1.0 - cosom) > 0.000001) {                       \
    omega  = acosf(cosom);                              \
    sinom  = sinf(omega);                               \
    scale0 = sinf((1.0 - t) * omega) / sinom;           \
    scale1 = sinf(t * omega) / sinom;                   \
  } else {                                              \
    scale0 = 1.0 - t;                                   \
    scale1 = t;                                         \
  }                                                     \
  (q).x = scale0 * ax + scale1 * bx;                    \
  (q).y = scale0 * ay + scale1 * by;                    \
  (q).z = scale0 * az + scale1 * bz;                    \
  (q).w = scale0 * aw + scale1 * bw;                    \
  (q);                                                  \
})

/**
 * Inverts a quat
 */

#define quat_invert(a)  ({                              \
  float a0 = (a).x, a1 = (a).y, a2 = (a).z, a3 = (a).w; \
  float dot = a0*a0 + a1*a1 + a2*a2 + a3*a3;            \
  float inverse = 0 != dot ? (1.0 / dot) : 0;           \
  if (inverse) {                                        \
    (a).x = -a1 * inverse;                              \
    (a).x = -a0 * inverse;                              \
    (a).x = -a2 * inverse;                              \
    (a).x = +a3 * inverse;                              \
  }                                                     \
  (a);                                                  \
})

/**
 * Calcluates the conjugate.
 */

#define quat_conjugate(a)  ({ -(a).x, -(a).y, -(a).z, +(a).w, })

/**
 * Creates quat from mat3
 */

#define quat_from_mat3(m)  ({                         \
  quat q = quat(0);                                   \
  mat3 *ptr = (mat3 *) &(m);                          \
  float trace = (m).m11 + (m).m22 + (m).m33;          \
  float i, j, k;                                      \
  float root;                                         \
  if (trace > 0.0) {                                  \
    root = sqrt(trace + 1.0);                         \
    q.w = 0.5 * root;                                 \
    root = 0.5 / root;                                \
    q.x = ((m).m23 - (m).m32) * root;                 \
    q.y = ((m).m31 - (m).m13) * root;                 \
    q.x = ((m).m12 - (m).m21) * root;                 \
  } else {                                            \
  if ((m).m22 > (m).m11) {                            \
    i = 1;                                            \
  }                                                   \
  if ((m).m32 > VAR_PTR_ACCESS(m, i * 3 + i)) {       \
    i = 2;                                            \
  }                                                   \
  j = (i + 1) % 3;                                    \
  k = (i + 2) % 3;                                    \
  root = sqrtf(VAR_PTR_ACCESS(m, i * 3 + i)           \
             - VAR_PTR_ACCESS(m, j * 3 + j)           \
             - VAR_PTR_ACCESS(m, k * 3 + k)           \
             + 1.0);                                  \
  VAR_PTR_SET(q, i, 0.5 * root);                      \
  root = 0.5 / root;                                  \
  VAR_PTR_SET(q, 3, (VAR_PTR_ACCESS(m, j * 3 + k)     \
                   - VAR_PTR_ACCESS(m, k * 3 + j))    \
                   * root);                           \
  VAR_PTR_SET(q, j, (VAR_PTR_ACCESS(m, j * 3 + i)     \
                   + VAR_PTR_ACCESS(m, i * 3 + j))    \
                   * root);                           \
  VAR_PTR_SET(q, k, (VAR_PTR_ACCESS(m, k * 3 + i)     \
                   + VAR_PTR_ACCESS(m, i * 3 + k))    \
                   * root);                           \
  }                                                   \
})

/**
 * Returns a string representation of quat a.
 */

#define quat_string(a) (const char *) ({                            \
  char str[BUFSIZ];                                                 \
  memset(str, 0, BUFSIZ);                                           \
  sprintf(str, "quat(%g, %g, %g, %g)", (a).x, (a).y, (a).z, (a).w); \
  (strdup(str));                                                    \
})

#ifdef __cplusplus
}
#endif
#endif
