//
// Created by meet on 6/15/25.
//

#include "MugInstanceTriangleFan.h"

#include "InstancedCircles.h"

CircleInstance::CircleInstance(InstancedTriangles &parent) {
    srcTriangles = parent.getAllTransformationData();
    srcColoredTriangles = parent.getAllTriangleData();
}

MugInstanceTriangleFan::MugInstanceTriangleFan(unsigned int numCircles, unsigned int slices) : InstancedTriangles(
    numCircles * slices) {
    this->numCircles = numCircles;
    this->slices = slices;
    float circumference = 2.0f * M_PI * 1.0f + 0.4;
    float triangleBaseW = (circumference / slices) / 2.0f;
    // Need to resize triangles to proper size.
    TriangleColoredData triangleSlice = {
        SimplePointStruct{
            0.0, 0.0, 0.0,
            0.2, 0.0, 0.4
        },
        SimplePointStruct{
            -triangleBaseW, -1.0f, 0.0,
            0.2, 0.0, 0.4
        },
        SimplePointStruct{
            triangleBaseW, -1.0f, 0.0,
            0.2, 0.0, 0.4
        },
    };

    for (unsigned int i = 0; i < numCircles; i++) {
        triangleData[i] = triangleSlice;
    }

    update();
    shader = MugEngine::getInstance().getShaderManager().loadNamedShader("simple/instancedtri");
}

void MugInstanceTriangleFan::update() {
    updateColorPositionBuffer();
    // Rotate & Scale Circles
    for (unsigned int i = 0; i < numCircles; i++) {
        float angleDiff = 360.0f / slices;
        for (int j = 0; j < slices; j++) {
            glm::mat4x4 trans = glm::mat4x4(1.0f);
            trans = glm::scale(trans, glm::vec3(circleRadius, circleRadius, 1.0));
            trans = glm::rotate(trans, j * angleDiff, glm::vec3(0, 0, 1.0));
            transforms[i * slices + j].transform = trans;
        }
    }
    updateTransformationBuffer();
}

void MugInstanceTriangleFan::setCircleRadius(float radius) {
    if (this->circleRadius == radius) { return; }
    this->circleRadius = radius;
    updateColorPositionBuffer();
}
