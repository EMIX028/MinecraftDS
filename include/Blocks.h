block_t air = {.id = 0,
                .drawAll = NULL};

block_t pierre = {.id = 1,
                      .position.x = 3.0, .position.y = 2.0, .position.z = -2.0,
                      .color.r = 10, .color.g = 10, .color.b = 10,
                      .drawTop = drawCubeTop, .drawBottom = drawCubeBottom,
                      .drawFront = drawCubeFront, .drawBack = drawCubeBack,
                      .drawLeft = drawCubeLeft, .drawRight = drawCubeRight,
                      .drawAll = drawCube
};