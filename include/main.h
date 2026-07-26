typedef struct{
  float x;
  float y;
  float z;
} position_t;

typedef struct{
  position_t position;
  float yaw;
  float pitch;
} camera_t;

position_t getDir(camera_t cam);