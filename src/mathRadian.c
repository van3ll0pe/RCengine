#include <math.h>

float degree_to_radian(float i) {
    return (i * (M_PI/180));
}

float distance_points(float x1, float y1, float x2, float y2) {
    return ( sqrt( (pow((x1 - x2), 2) + pow((y1 - y2), 2))) );
}