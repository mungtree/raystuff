//
// Created by meet on 6/15/25.
//

#ifndef INSTANCEDCIRCLES_H
#define INSTANCEDCIRCLES_H

#include <glm/ext/matrix_transform.hpp>

#include "InstancedTriangles.h"
#include "MugEngine.hpp"

class MugInstanceTriangleFan;

class CircleInstance {
private:
    std::vector<TriangleTransformation>* srcTriangles;
    std::vector<TriangleColoredData>* srcColoredTriangles;
public:
    CircleInstance(InstancedTriangles& parent);
};

class MugInstanceTriangleFan : public InstancedTriangles {
private:
    float circleRadius = 0.1;
    unsigned int numCircles;
    unsigned int slices;
public:
    MugInstanceTriangleFan(unsigned int numCircles, unsigned int slices);


    void update();
    float getCircleRadius() const { return circleRadius; }
    void setCircleRadius(float radius);
};



#endif //INSTANCEDCIRCLES_H
