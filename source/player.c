#include "player.h"

vec3_t getDir(camera_t cam){
  vec3_t dir;
  dir.x = sinf(cam.yaw)*cosf(cam.pitch);
  dir.y = sinf(cam.pitch);
  dir.z = -cosf(cam.yaw)*cosf(cam.pitch);
  return dir;
}