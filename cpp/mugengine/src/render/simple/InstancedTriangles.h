//
// Created by meet on 6/1/25.
//

#ifndef INSTANCEDTRIANGLE_H
#define INSTANCEDTRIANGLE_H

#include <vector>
#include <glm/glm.hpp>

#include "SimplePoint.h"
#include "glad/glad.h"
#include "shaders/MugShader.hpp"
#include "util/RGBAColor.h"

struct TriangleColoredData {
    SimplePointStruct triangleData[3];
    void setColor(ColorRGB color);
};

struct TriangleTransformation {
    glm::mat4x4 transform = glm::mat4x4(1.0f);
};

class InstancedTriangles {
private:
    std::vector<TriangleTransformation> transforms;
    std::vector<TriangleColoredData> triangleData;

    GLuint vao;
    GLuint vbo;
    GLuint transformVBO;
    std::shared_ptr<MugShader> shader;

public:
    InstancedTriangles(unsigned int numTriangles);
    ~InstancedTriangles();

    void updateColorPositionBuffer();
    void updateTransformationBuffer();
    void draw();

    void setShader(std::shared_ptr<MugShader> shader) { this->shader = shader; }

    std::vector<TriangleColoredData>* getAllTriangleData() { return &triangleData; }
    std::vector<TriangleTransformation>* getAllTransformationData() { return &transforms; }
    [[nodiscard]] TriangleTransformation* getTransformation(const int index) { return &transforms[index]; }
    [[nodiscard]] TriangleColoredData* getTriangleData(const int index) { return &triangleData[index]; }
};

#endif //INSTANCEDTRIANGLE_H
