//
// Created by meet on 6/1/25.
//

#ifndef SIMPLEBOIDSIM_H
#define SIMPLEBOIDSIM_H
#include <mutex>
#include <vector>
#include <random>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include "AbstractBoidSimulator.h"
#include "BoidSimulationSettings.h"
#include "render/simple/InstancedTriangles.h"


class SimpleBoid;

class SimpleBoidSimulation : public AbstractBoidSimulator {
private:
    std::mutex glMutex;
    std::thread updateThread;
    volatile bool isThreadRunning = false;
    volatile bool transformChanged = false;

    unsigned int boidCount;
    std::vector<SimpleBoid> mBoids;
    InstancedTriangles mTriangles;
public:
    SimpleBoidSimulation(unsigned int boidCount);
    ~SimpleBoidSimulation() override;
    void startUpdateThread() override;
    void stopUpdateThread() override;
    void update() override;
    void resetBoids() override;
    void draw() override;
    unsigned int getBoidCount() const override { return boidCount; }
    void updateSettings(BoidSimulationSettings settings) override;
};

class SimpleBoid {
private:
    static bool rand_init;
    static std::default_random_engine generator;
    static std::uniform_real_distribution<float> distribution;

public:
    unsigned int id = 0;
    float xPos;
    float yPos;
    float heading;
    float xVelocity;
    float yVelocity;
    SimpleBoid();

    /**
     * Update movement step
     */
    void stepMovementUpdate();


    void randomize();
    static SimpleBoid newRandomBoid();
};


#endif //SIMPLEBOIDSIM_H
