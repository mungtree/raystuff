//
// Created by meet on 6/7/25.
//
#include "AbstractBoidSimulator.h"

#include "imgui.h"

void imguiAddSliderFloat(const char *title, float *data, float def, ImGuiSliderFlags flags,
                         float range = 50.0f, const char *format = "%.5f") {
    ImGui::SliderFloat(title, data,
                       def / range, def * range, "%.5f", flags);
}

void AbstractBoidSimulator::drawImGui() {
    static BoidSimulationSettings newSettings = BoidSimulationSettings();
    static BoidSimulationSettings defaultSettings = BoidSimulationSettings();
    ImGui::Begin("Boid Simulator");

    ImGuiSliderFlags flags = ImGuiSliderFlags_Logarithmic;

    imguiAddSliderFloat("Avoid Strength", &newSettings.avoidStrength,
        defaultSettings.avoidStrength, flags);
    imguiAddSliderFloat("Centering Strength", &newSettings.centeringStrength,
        defaultSettings.centeringStrength, flags);
    imguiAddSliderFloat("Follow Strength", &newSettings.followStrength,
        defaultSettings.followStrength, flags);

    imguiAddSliderFloat("Avoid Range", &newSettings.avoidRange,
        defaultSettings.avoidRange, flags);
    imguiAddSliderFloat("Centering Range", &newSettings.centeringRange,
        defaultSettings.centeringRange, flags);
    imguiAddSliderFloat("Wall Range", &newSettings.wallRange,
        defaultSettings.wallRange, flags);

    imguiAddSliderFloat("Max Speed", &newSettings.maxSpeed,
        defaultSettings.maxSpeed, flags);

    if (ImGui::Button("Reset")) {
        newSettings = defaultSettings;
        this->updateSettings(newSettings);
    }
    this->updateSettings(newSettings);
    ImGui::End();
}
