//
// Created by meet on 6/1/25.
//

#ifndef SIMPLEBOIDSIM_H
#define SIMPLEBOIDSIM_H
#include <vector>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "render/simple/InstancedTriangles.h"


class SimpleBoid;

class SimpleBoidSimulation {
private:
    unsigned int boidCount;
    std::vector<SimpleBoid> mBoids;
    InstancedTriangles mTriangles;

public:
    SimpleBoidSimulation(unsigned int boidCount);
    void update();
    void draw();
};

class SimpleBoid {
private:
    static bool rand_init;
    static std::default_random_engine generator;
    static std::uniform_real_distribution<float> distribution;

public:
    float xPos;
    float yPos;
    float heading;
    float xVelocity;
    float yVelocity;

    SimpleBoid();
    void randomize();

    static SimpleBoid newRandomBoid();
};


#endif //SIMPLEBOIDSIM_H
