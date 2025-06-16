//
// Created by meet on 6/14/25.
//

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <memory>
#include <string>
#include <unordered_map>

#include "MugShader.hpp"


class ShaderManager {
private:
    std::unordered_map<std::string, std::shared_ptr<MugShader>> shaders;
    std::string shaderDirectory = "res/shaders/";
public:
    std::shared_ptr<MugShader> loadNamedShader(std::string shaderName);
    std::shared_ptr<MugShader> loadNamedShader(std::string directory,  std::string shaderName);
    std::shared_ptr<MugShader> loadShader(const std::string& vpath, const std::string& fpath);
    void clearShaders();
    void setShaderDirectory(const std::string& directory) { shaderDirectory = directory; }
    std::string getShaderDirectory() { return shaderDirectory; }
};



#endif //SHADERMANAGER_H
