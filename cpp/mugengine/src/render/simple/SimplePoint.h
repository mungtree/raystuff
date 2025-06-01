//
// Created by meet on 5/31/25.
//

#ifndef SIMPLEPOINT_H
#define SIMPLEPOINT_H
#include "glad/glad.h"


class SimplePoint {
private:
public:
    inline static GLuint size = 3 * sizeof(float);
    float x;
    float y;
    float z;
    SimplePoint() : x(0), y(0), z(0) {}
    SimplePoint(float x, float y) : x(x), y(y), z(0) {}
    SimplePoint(float x, float y, float z) : x(x), y(y), z(z) {}
};


#endif //SIMPLEPOINT_H
