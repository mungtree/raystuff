//
// Created by meet on 6/1/25.
//

#include "SimpleBoidSimulation.h"

#include <functional>

SimpleBoidSimulation::SimpleBoidSimulation(unsigned int boidCount): mTriangles(boidCount) {
    this->boidCount = boidCount;
    mBoids.reserve(boidCount);
    for (int i = 0; i < boidCount; i++) {
        mBoids.push_back(SimpleBoid::newRandomBoid());
    }

    // Shader
    auto instShader = MugShader::loadShaderNamed("res/shaders/simple", "instancedtri");
    if (instShader != nullptr) {
        mTriangles.setShader(instShader);
    }
}

void SimpleBoidSimulation::update() {
    std::vector<TriangleTransformation>* tData = mTriangles.getAllTransformationData();
    for (int i = 0; i < boidCount; i++) {
        SimpleBoid boid = mBoids[i];
        boid.randomize();

        glm::mat4x4 trans = glm::mat4x4(1.0f);
        trans = glm::rotate(trans, glm::radians(boid.heading), glm::vec3(0, 0, 1.0));
        trans = glm::translate(trans, glm::vec3(boid.xPos, boid.yPos, 0.0));
        trans = glm::scale(trans, glm::vec3(0.1, 0.1, 1));
        (*tData)[i].transform = trans;
    }
    mTriangles.updateTransformationBuffer();
}

void SimpleBoidSimulation::draw() {
    mTriangles.draw();
}


#pragma region Simple Boid

SimpleBoid::SimpleBoid() {
    xPos = yPos = 0;
    heading = 0;
    xVelocity = 0;
    yVelocity = 0;
}

void SimpleBoid::randomize() {
    xPos = distribution(generator);
    yPos = distribution(generator);
    heading = distribution(generator) * 360.0f;
    xVelocity = distribution(generator);
    yVelocity = distribution(generator);
}

std::default_random_engine SimpleBoid::generator = std::default_random_engine();
std::uniform_real_distribution<float> SimpleBoid::distribution(-1, 1);

SimpleBoid SimpleBoid::newRandomBoid() {
    SimpleBoid newBoid = SimpleBoid();
    newBoid.xPos = distribution(generator);
    newBoid.yPos = distribution(generator);
    newBoid.xVelocity = distribution(generator) / 4.0f;
    newBoid.yVelocity = distribution(generator) / 4.0f;
    return newBoid;
}

#pragma endregion
