#ifndef OBSERVER_H
#define OBSERVER_H
#include "numbervector.h"
#include "scene.h"

class Camera
{    


public:    
    NumberVector camera_xyz_position;
    NumberVector look_at_xyz_position;
    NumberVector up_xyz;

    NumberVector camera_look_direction_k;
    NumberVector camera_right_direction_i;
    NumberVector camera_down_direction_j;

    Camera();
    Camera(NumberVector pos, NumberVector look_at, NumberVector up);
    double coordinatesWorldToCamera[4][4];

    void transformVertexFromCoordinatesWorldToCamera(Scene scene);


};

#endif // CAMERA_H
