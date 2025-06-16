//
// Created by meet on 6/7/25.
//

#include "GridBoidSimulation.h"

#include <cmath>

#include "SimpleBoidSimulation.h"
#include "util/MugLogger.hpp"

void GridBoidSimulation::initGrid() {
    glMutex.lock();
    mBoids.clear();
    boidGrid.clear();
    // Initialize Grid
    for (int i = 0; i < gridSettings.gridSize; i++) {
        for (int j = 0; j < gridSettings.gridSize; j++) {
            boidGrid[std::make_pair(i, j)] = std::list<SimpleBoid *>();
        }
    }

    mBoids.reserve(boidCount);
    for (int i = 0; i < boidCount; i++) {
        mBoids.push_back(SimpleBoid::newRandomBoid());
        SimpleBoid *b = &mBoids.back();
        boidGrid[getGridPositionForBoid(*b)].push_back(b);
        b->id = i;
    }
    glMutex.unlock();
}

std::pair<int, int> GridBoidSimulation::getGridPositionForBoid(SimpleBoid &boid) const {
    float gridStep = 2.0f / gridSettings.gridSize;
    int xCell = std::min(static_cast<int>((boid.xPos + 1) / gridStep), static_cast<int>(gridSettings.gridSize));
    int yCell = std::min(static_cast<int>((boid.yPos + 1) / gridStep), static_cast<int>(gridSettings.gridSize));
    return std::make_pair(xCell, yCell);
}


GridBoidSimulation::GridBoidSimulation(unsigned int boidCount): mTriangles(boidCount) {
    this->boidCount = boidCount;
    initGrid();
    // Shader
    auto instShader = MugShader::loadShaderNamed("res/shaders/simple", "instancedtri");
    if (instShader != nullptr) {
        mTriangles.setShader(instShader);
    }
}

GridBoidSimulation::~GridBoidSimulation() {
    GridBoidSimulation::stopUpdateThread();
}

void GridBoidSimulation::startUpdateThread() {
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
                if (elapsedMs > 5) {
                    MugLogger::debug("Frame Time: " + std::to_string(elapsedMs));
                }
                if (sleepTime > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
                }
            }
        } catch (std::exception &e) {
            MugLogger::error(e.what());
        }
    });
}

void GridBoidSimulation::stopUpdateThread() {
    if (!isThreadRunning) return;
    isThreadRunning = false;
    MugLogger::info("GridBoidSimulation::Stopping update thread");
    updateThread.join();
}


void GridBoidSimulation::update() {
    for (int i = 0; i < gridSettings.gridSize; i++) {
        for (int j = 0; j < gridSettings.gridSize; j++) {
            calculateGrid(i, j);
        }
    }
}

void GridBoidSimulation::calculateGrid(int i, int j) {
    std::vector<TriangleTransformation>* tData = mTriangles.getAllTransformationData();
    std::pair<int, int> gridPos = std::make_pair(i, j);
    std::list<SimpleBoid *> *cellBoids = &boidGrid[gridPos];
    for (auto it = cellBoids->begin(); it != cellBoids->end(); ++it) {
        SimpleBoid *boid = *it;
        applyBoidUpdate(boid, *cellBoids);

        // Update Boid Position
        boid->stepMovementUpdate();
        if (std::fabs(boid->xPos) >= 1.1f || std::fabs(boid->yPos) >= 1.1f) {
            boid->randomize();
        }
        std::pair<int, int> newPos = getGridPositionForBoid(*boid);
        if (newPos != gridPos) {
            it = cellBoids->erase(it);
            --it;   // Used to delete while iterating
            boidGrid[newPos].push_back(boid);
        }

        auto trans = glm::mat4x4(1.0f);
        trans = glm::translate(trans, glm::vec3(boid->xPos, boid->yPos, 0.0));
        trans = glm::rotate(trans, boid->heading,  glm::vec3(0, 0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.05, 0.05, 1));
        (*tData)[boid->id].transform = trans;
    }
    transformChanged = true;
}

void GridBoidSimulation::applyBoidUpdate(SimpleBoid *boid, const std::list<SimpleBoid *> &neighbors) {
    unsigned int avoidCount = 0;
    float avgAvoidX = 0.0f;
    float avgAvoidY = 0.0f;

    unsigned int centerCount = 0;
    float avgCenterX = 0.0f;
    float avgCenterY = 0.0f;
    float avgHeadingX = 0.0f;
    float avgHeadingY = 0.0f;

    for (const SimpleBoid *other: neighbors) {
        if (other == boid) continue;
        float xd = other->xPos - boid->xPos;
        float yd = other->yPos - boid->yPos;
        float distance = xd * xd + yd * yd;
        if (distance > settings.centeringRange) continue;
        if (distance <= settings.avoidRange) {
            avoidCount++;
            avgAvoidX += boid->xPos - other->xPos;
            avgAvoidY += boid->yPos - other->yPos;
        }

        centerCount++;
        avgCenterX += other->xPos;
        avgCenterY += other->yPos;
        avgHeadingX += other->xVelocity;
        avgHeadingY += other->yVelocity;
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
    if (speed >= settings.maxSpeed) {
        boid->xVelocity = (sX / speed) * settings.maxSpeed;
        boid->yVelocity = (sY / speed) * settings.maxSpeed;
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
}

void GridBoidSimulation::resetBoids() {
    initGrid();
}

void GridBoidSimulation::draw() {
    glMutex.lock();
    if (transformChanged) {
    mTriangles.updateTransformationBuffer();
    }
    glMutex.unlock();

    mTriangles.draw();
}

void GridBoidSimulation::updateSettings(BoidSimulationSettings settings) {
    this->settings = settings;
}
