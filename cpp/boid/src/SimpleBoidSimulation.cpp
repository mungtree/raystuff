//
// Created by meet on 6/1/25.
//

#include "SimpleBoidSimulation.h"

#include <unistd.h>

#include "util/MugLogger.hpp"



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

SimpleBoidSimulation::~SimpleBoidSimulation() {
    stopUpdateThread();
}

void SimpleBoidSimulation::startUpdateThread() {
    if (isThreadRunning) { return; }
    isThreadRunning = true;
    updateThread = std::thread([&]() {
        try {
            while (isThreadRunning) {
                auto start = std::chrono::steady_clock::now();

                glMutex.lock();
                update();
                glMutex.unlock();
                auto end = std::chrono::steady_clock::now();
                const auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                int sleepTime = settings.frameDurationMs - elapsedMs;
                if (elapsedMs > 50) {
                    MugLogger::debug("Frame Time: " + std::to_string(elapsedMs));
                }
                if (sleepTime > 0) {
                  std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
                }
            }
        } catch (std::exception& e) {
            MugLogger::error(e.what());
        }
    });
    // updateThread = std::thread(&SimpleBoidSimulation::updateTask, this);
}

void SimpleBoidSimulation::stopUpdateThread() {
    if (!isThreadRunning) return;
    isThreadRunning = false;
    MugLogger::info("SimpleBoidSimulation::Stopping update thread");
    updateThread.join();
}

void SimpleBoidSimulation::update() {
    std::vector<TriangleTransformation>* tData = mTriangles.getAllTransformationData();

    unsigned int tooFast = 0;
    for (int i = 0; i < boidCount; i++) {
        SimpleBoid* boid = &mBoids[i];

        unsigned int avoidCount = 0;
        float avgAvoidX = 0.0f;
        float avgAvoidY = 0.0f;

        unsigned int centerCount = 0;
        float avgCenterX = 0.0f;
        float avgCenterY = 0.0f;
        float avgHeadingX = 0.0f;
        float avgHeadingY = 0.0f;

        for (SimpleBoid& b : mBoids) {
            float xd = b.xPos - boid->xPos;
            float yd = b.yPos - boid->yPos;
            float distance = xd*xd + yd*yd;
            if (distance > settings.centeringRange) continue;
            if (distance <= settings.avoidRange) {
                avoidCount++;
                avgAvoidX += boid->xPos - b.xPos;
                avgAvoidY += boid->yPos - b.yPos;
            }

            centerCount++;
            avgCenterX += b.xPos;
            avgCenterY += b.yPos;
            avgHeadingX += b.xVelocity;
            avgHeadingY += b.yVelocity;
        }

        if (centerCount == 0) { centerCount++; }
        avgCenterX /= centerCount;
        avgCenterY /= centerCount;
        avgHeadingX /= centerCount;
        avgHeadingY /= centerCount;

        // Centering
        boid->xVelocity += (avgCenterX - boid->xPos) * settings.centeringStrength;
        boid->yVelocity += (avgCenterY - boid->yPos) * settings.centeringStrength;

        // Heading
        boid->xVelocity += (avgHeadingX - boid->xVelocity) * settings.followStrength;
        boid->yVelocity += (avgHeadingY - boid->yVelocity) * settings.followStrength;

        // Avoid
        boid->xVelocity += avgAvoidX * settings.avoidStrength;
        boid->yVelocity += avgAvoidY * settings.avoidStrength;




        // Limit Speed
        float sX = boid->xVelocity * boid->xVelocity;
        float sY = boid->yVelocity * boid->yVelocity;
        float speed = sqrtf(sX + sY);
        if  (speed >= settings.maxSpeed) {
            boid->xVelocity = (sX/speed) * settings.maxSpeed;
            boid->yVelocity = (sY/speed) * settings.maxSpeed;
            tooFast++;
        }

        // Avoid Wall
        if (boid->xPos >= settings.wallRange) {
            boid->xVelocity -= settings.avoidWallStrength;
        } else if (boid->xPos <= -settings.wallRange) {
            boid->xVelocity += settings.avoidWallStrength;
        }
        if (boid->yPos >= settings.wallRange) {
            boid->yVelocity -= settings.avoidWallStrength;
        } else if (boid->yPos <= -settings.wallRange) {
            boid->yVelocity += settings.avoidWallStrength;
        }


        boid->stepMovementUpdate();
        if (abs(boid->xPos) >= 1.2f || abs(boid->yPos) >= 1.2f) {
            boid->randomize();
        }
        glm::mat4x4 trans = glm::mat4x4(1.0f);
        trans = glm::translate(trans, glm::vec3(boid->xPos, boid->yPos, 0.0));
        trans = glm::rotate(trans, boid->heading,  glm::vec3(0, 0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.05, 0.05, 1));
        (*tData)[i].transform = trans;
    }
    float tooFastPercentage = 1.0f * tooFast / boidCount;
    if (tooFastPercentage > 0.01f) {
        MugLogger::debug("Too Fast Boids: " + std::to_string(100.0f * tooFastPercentage) + "%");
    }
    transformChanged = true;
}

void SimpleBoidSimulation::resetBoids() {
    std::vector<TriangleTransformation>* tData = mTriangles.getAllTransformationData();
    for (int i = 0; i < boidCount; i++) {
        SimpleBoid* boid = &mBoids[i];
        boid->randomize();
        glm::mat4x4 trans = glm::mat4x4(1.0f);
        trans = glm::translate(trans, glm::vec3(boid->xPos, boid->yPos, 0.0));
        trans = glm::rotate(trans, boid->heading,  glm::vec3(0, 0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.1, 0.1, 1));
        (*tData)[i].transform = trans;
    }
    mTriangles.updateTransformationBuffer();
}

void SimpleBoidSimulation::draw() {
    glMutex.lock();
    if (transformChanged) {
    mTriangles.updateTransformationBuffer();
    }
    glMutex.unlock();

    mTriangles.draw();
}

void SimpleBoidSimulation::updateSettings(BoidSimulationSettings settings) {
    this->settings = settings;
}


#pragma region Simple Boid

// Static

std::default_random_engine SimpleBoid::generator = std::default_random_engine();

std::uniform_real_distribution<float> SimpleBoid::distribution(-1, 1);

SimpleBoid SimpleBoid::newRandomBoid() {
    SimpleBoid newBoid = SimpleBoid();
    newBoid.xPos = distribution(generator) / 1.1f;
    newBoid.yPos = distribution(generator)  / 1.1f;
    newBoid.xVelocity = distribution(generator) / 1000.0f;
    newBoid.yVelocity = distribution(generator) / 1000.0f;
    return newBoid;
}
// End Static

SimpleBoid::SimpleBoid() {
    xPos = yPos = 0;
    heading = 0;
    xVelocity = 0;
    yVelocity = 0;
}


static float boidRotationCorrection = glm::radians(270.0f);
void SimpleBoid::stepMovementUpdate() {
    xPos += xVelocity;
    yPos += yVelocity;
    heading = boidRotationCorrection + atan2f(yVelocity, xVelocity);
    // MugLogger::debug("Degrees: " + std::to_string(glm::degrees(heading)) +
    //    "\nX/Y Velocity: " +  std::to_string(xVelocity) + "," + std::to_string(yVelocity));
}

void SimpleBoid::randomize() {
    xPos = distribution(generator) / 2.0f;
    yPos = distribution(generator) / 2.0f;
    heading = distribution(generator) * 360.0f;
    xVelocity = distribution(generator) / 1000.0f;
    yVelocity = distribution(generator) / 1000.0f;
}

#pragma endregion
