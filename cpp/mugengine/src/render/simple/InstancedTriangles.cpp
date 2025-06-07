//
// Created by meet on 6/1/25.
//

#include "InstancedTriangles.h"

#include <glm/ext/matrix_transform.hpp>

void TriangleColoredData::setColor(ColorRGB color) {
    for (int i = 0; i < 3; i++) {
        triangleData[i].rgb[0] = color.r;
        triangleData[i].rgb[1] = color.g;
        triangleData[i].rgb[2] = color.b;
    }
}

InstancedTriangles::InstancedTriangles(unsigned int numTriangles) {
    transforms = std::vector(numTriangles, TriangleTransformation());
    TriangleColoredData data = {
        SimplePointStruct{-0.1, -0.1, 0.0, 1.0, 0.0, 0.0},
        SimplePointStruct{0.1, -0.1, 0.0, 0.0, 1.0, 0.0},
        SimplePointStruct{0.0, 0.25, 0.0, 0.0, 0.0, 1.0},
    };
    triangleData = std::vector(numTriangles, data);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    updateColorPositionBuffer();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // XYZ
    glVertexAttribPointer(0, 3, GL_FLOAT,
                          GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT,
                          GL_FALSE, 6 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Transform VBO
    glGenBuffers(1, &transformVBO);
    updateTransformationBuffer();
    glBindBuffer(GL_ARRAY_BUFFER, transformVBO);
    // Mat4 takes 4 attributes, so we need to enable one at a time.
    for (int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer(2 + i, 4,
            GL_FLOAT, GL_FALSE,
            sizeof(glm::mat4), (void*)(i * sizeof(glm::vec4)));
        glVertexAttribDivisor(2 + i, 1);
    }

}

InstancedTriangles::~InstancedTriangles() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &transformVBO);
}

void InstancedTriangles::updateColorPositionBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    TriangleColoredData *triBuf = triangleData.data();
    GLuint bufSz = sizeof(TriangleColoredData) * triangleData.size();
    glBufferData(GL_ARRAY_BUFFER, bufSz, triBuf, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstancedTriangles::updateTransformationBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, transformVBO);

    TriangleTransformation *transBuf = transforms.data();
    GLuint bufSz = triangleData.size() * sizeof(glm::mat4);
    glBufferData(GL_ARRAY_BUFFER, bufSz,
                 transBuf, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void InstancedTriangles::draw() {
    if (shader != nullptr) {
        shader->bind();
    }

    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, triangleData.size());
    glBindVertexArray(0);

    if (shader != nullptr) {
        shader->unbind();
    }
}
