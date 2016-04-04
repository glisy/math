math
====

Math functions for Glisy

## Installation

```sh
$ clib install glisy/math --save
```

## Usage

```c
#include <glisy/math.h>

int
main (void) {

  mat4 projection;
  mat4 model;
  mat4 view;
  mat4 mat;

  vec3 position = {0, 0, -1};
  vec3 eye = {0, 0, 0}
  vec3 up = {0, 1, 0};

  mat4_identity(model);
  projection = mat4_perspetive(45, 1.0, 1, 1000);
  view = mat4_lookAt(eye, position, up);

  mat = mat4_multiply(projection, view);
  mat = mat4_multiply(mat, model);

  return 0;
}
```

## License

MIT
