//
// Created by meet on 6/15/25.
//

#ifndef INSTANCEDCIRCLES_H
#define INSTANCEDCIRCLES_H

#include <glm/ext/matrix_transform.hpp>

#include "InstancedTriangles.h"
#include "MugEngine.hpp"

class InstancedCircles;

class CircleInstance {
private:
    std::vector<TriangleTransformation>* srcTriangles;
    std::vector<TriangleColoredData>* srcColoredTriangles;
public:
    CircleInstance(InstancedTriangles& parent);
};

class InstancedCircles : public InstancedTriangles {
private:
    float circleRadius = 0.1;
public:
    InstancedCircles(unsigned int numCircles, unsigned int slices);


    float getCircleRadius() const { return circleRadius; }
    float setCircleRadius(float radius);
};



#endif //INSTANCEDCIRCLES_H
