//
// Created by meet on 6/7/25.
//

#ifndef ABSTRACTBOIDSIMULATOR_H
#define ABSTRACTBOIDSIMULATOR_H
#include "BoidSimulationSettings.h"
#include "util/MugLogger.hpp"

class AbstractBoidSimulator {
protected:
public:
    virtual ~AbstractBoidSimulator() = default;
    virtual void startUpdateThread() {}
    virtual void stopUpdateThread() {};
    virtual void update() {};
    virtual void resetBoids() {};
    virtual void draw() {};
    virtual unsigned int getBoidCount() const { return 0; };
};



#endif //ABSTRACTBOIDSIMULATOR_H
