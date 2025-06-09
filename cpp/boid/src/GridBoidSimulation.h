//
// Created by meet on 6/7/25.
//

#ifndef GRIDBOIDSIMULATION_H
#define GRIDBOIDSIMULATION_H
#include <list>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#include "AbstractBoidSimulator.h"
#include "BoidSimulationSettings.h"
#include "render/simple/InstancedTriangles.h"
#include "util/PairHelpers.h"


class SimpleBoid;

struct GridBoidSettings {
    unsigned int gridSize = 16;
};

class GridBoidSimulation : public AbstractBoidSimulator {
private:
    std::mutex glMutex;
    std::thread updateThread;
    volatile bool isThreadRunning = false;
    volatile bool transformChanged = false;

    unsigned int boidCount;
    std::unordered_map<std::pair<int, int>, std::list<SimpleBoid*>, mug_int_pair_hash, mug_int_pair_equal> boidGrid;
    std::vector<SimpleBoid> mBoids;
    InstancedTriangles mTriangles;

    void initGrid();
    std::pair<int, int> getGridPositionForBoid(SimpleBoid& boid) const;
    void applyBoidUpdate(SimpleBoid *boid, const std::list<SimpleBoid*> &neighbors);
    void calculateGrid(int i, int j);
public:
    GridBoidSimulation(unsigned int boidCount);
    ~GridBoidSimulation() override;
    void startUpdateThread() override;
    void stopUpdateThread() override;
    void update() override;
    void resetBoids() override;
    void draw() override;
    unsigned int getBoidCount() const override { return boidCount; }
    void updateSettings(BoidSimulationSettings settings) override;
    GridBoidSettings gridSettings;

};



#endif //GRIDBOIDSIMULATION_H
