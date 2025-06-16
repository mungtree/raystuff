//
// Created by meet on 6/14/25.
//

#include "ShaderManager.h"

#include "util/MugLogger.hpp"

std::shared_ptr<MugShader> ShaderManager::loadNamedShader(std::string shaderName) {
    return loadNamedShader(shaderDirectory, shaderName);
}

std::shared_ptr<MugShader> ShaderManager::loadNamedShader(std::string directory, std::string shaderName) {
    std::string shaderPath = directory + shaderName;
    MugLogger::debug("Loading Shader: "  + shaderPath);
    if (shaders.find(shaderPath) == shaders.end()) {
        auto nShader = MugShader::loadShaderNamed(directory, shaderName);
        shaders[shaderPath] = nShader;
        return nShader;
    } else {
        std::weak_ptr<MugShader> weakShader = shaders[shaderPath];

        // If shader not valid, load a new one, otherwise just return that.
        auto pShader = weakShader.lock();
        if (pShader == nullptr) {
            auto nShader = MugShader::loadShaderNamed(directory, shaderName);
            shaders[shaderPath] = nShader;
            return nShader;
        } else {
            return pShader;
        }
    }
}

std::shared_ptr<MugShader> ShaderManager::loadShader(const std::string &vpath, const std::string &fpath) {
    std::string shaderKey = vpath + fpath;
    if (shaders.find(shaderKey) == shaders.end()) {
        auto nShader = MugShader::loadShader(vpath, fpath);
        shaders[shaderKey] = nShader;
        return nShader;
    } else {
        std::weak_ptr<MugShader> weakShader = shaders[shaderKey];

        // If shader not valid, load a new one, otherwise just return that.
        auto pShader = weakShader.lock();
        if (pShader == nullptr) {
            auto nShader = MugShader::loadShader(vpath, fpath);
            shaders[shaderKey] = nShader;
            return nShader;
        } else {
            return pShader;
        }
    }
}

void ShaderManager::clearShaders() {
    for (const auto & [key, shader] : shaders) {
        shader->deallocate();
    }
    shaders.clear();
}
