//
// Created by meet on 6/7/25.
//

#ifndef BOIDSIMULATIONSETTINGS_H
#define BOIDSIMULATIONSETTINGS_H

struct BoidSimulationSettings {
    unsigned int frameDurationMs = 10;

    float avoidStrength = 0.005f;
    float centeringStrength = 0.001f;
    float followStrength = 0.01f;
    float avoidWallStrength = 0.0001f;

    float centeringRange = 0.01f;
    float avoidRange = 0.0007f;
    float wallRange = 0.98f;

    float maxSpeed = 0.005f;
};

#endif //BOIDSIMULATIONSETTINGS_H
