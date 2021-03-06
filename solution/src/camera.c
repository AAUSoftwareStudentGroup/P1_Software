#include "camera.h"

/* Positions camera on a sphere with radius 'distance', orientet to look at 
   point with horizontal and vertical angles given in radians */
void camera_look_at_point(Camera *camera, Vector point, double distance, double vertical_angle, double horizontal_angle) {
  /* Resetting camera position to prepare rotation */
  camera->position = (Vector){0, -distance, 0};

  /* Rotate camera around itself */
  camera_set_angle(camera, -vertical_angle, horizontal_angle);
  
  /* Rotate camera around x and z axis and add to point we wanna look at */
  camera->position = vector_rotate_around_xz(camera->position, -vertical_angle, horizontal_angle);
  camera->position = vector_add(camera->position, point);
}

/* Orients camera to look in direction given by horizontal and vertical angle in radians */
int camera_set_angle(Camera *camera, double vertical_angle, double horizontal_angle){
  /* Reset camera angles before rotating*/
  camera->right   = (Vector){1,0,0};
  camera->forward = (Vector){0,1,0};
  camera->up      = (Vector){0,0,1};

  /* Rotating up and forward vector */
  camera->up      = vector_rotate_around_xz(camera->up,      vertical_angle, horizontal_angle);
  camera->forward = vector_rotate_around_xz(camera->forward, vertical_angle, horizontal_angle);
  camera->right   = vector_rotate_around_z(camera->right,   horizontal_angle);
  
  return 1;
}

Camera *new_camera(unsigned int width, unsigned int height) {
  Camera *camera;
  camera = (Camera*)malloc(sizeof(Camera));
  camera->width    = width;
  camera->height   = height;
  camera->position = (Vector){0,0,0};
  camera->right    = (Vector){1,0,0};
  camera->forward  = (Vector){0,1,0};
  camera->up       = (Vector){0,0,1};
  camera->distance = MAX(width, height);
  return camera; 
}

int free_camera(Camera *camera) {
  free(camera);
  return 1;
}