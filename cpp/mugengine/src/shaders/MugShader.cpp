//
// Created by meet on 5/31/25.
//

#include "MugShader.hpp"

#include <fstream>
#include <sstream>

#include "mugengine.hpp"
#include "util/MugLogger.hpp"

std::string MugShader::read_file(std::string path) {
    std::ifstream vif(path);
    if (!vif.is_open()) {
        return "";
    }

    std::stringstream vbuf;
    vbuf << vif.rdbuf();
    vif.close();

    std::string result = vbuf.str();
    return result;
}

MugShader::MugShader(GLuint shaderProgram) {
    this->shaderProgram = shaderProgram;
}



MugShader::~MugShader() {
    MugLogger::debug("Deallocating shader program " + std::to_string(this->shaderProgram));
    glDeleteProgram(this->shaderProgram);
}

void MugShader::bind() {
    glUseProgram(shaderProgram);
}

void MugShader::unbind() {
    glUseProgram(0);
}

std::shared_ptr<MugShader> MugShader::loadShader(const std::string& vpath, const std::string &fpath) {
    std::string vertexSrc = read_file(vpath);
    if (vertexSrc.length()  == 0) {
        MugLogger::error("Failed to read vertex shader: " + vpath);
        return nullptr;
    }
    std::string fragSrc = read_file(fpath);
    if (fragSrc.length()  == 0) {
        MugLogger::error("Failed to read fragment shader: " + vpath);
        return nullptr;
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderCStr = vertexSrc.c_str();
    glShaderSource(vertexShader, 1,
        &vertexShaderCStr, nullptr);
    glCompileShader(vertexShader);
    if (!logShaderCompileStatus(vertexShader, GL_COMPILE_STATUS, "Vertex")) return nullptr;

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragShaderCStr = fragSrc.c_str();
    glShaderSource(fragShader, 1,
        &fragShaderCStr, nullptr);

    glCompileShader(fragShader);
    if (!logShaderCompileStatus(fragShader, GL_COMPILE_STATUS, "Fragment")) return nullptr;

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    if (!logShaderCompileStatus(shaderProgram, GL_LINK_STATUS, "Shader")) return nullptr;

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    auto shader = std::make_shared<MugShader>(shaderProgram);
    return shader;
}

std::shared_ptr<MugShader> MugShader::loadShaderNamed(std::string path, std::string name) {
    std::string vPath = "";
    std::string fPath = "";
    if (path.back() == '/') {
        vPath = path + name + ".vs";
        fPath = path + name + ".frag";
    } else {
        vPath = path + "/" + name + ".vs";
        fPath = path + "/" + name + ".frag";
    }
    return loadShader(vPath, fPath);
}

bool MugShader::logShaderCompileStatus(GLuint shaderId, GLenum pname, const std::string &msg ) {
    int success;
    char infoLog[GL_INFO_LOG_LENGTH] = {};
    glGetShaderiv(shaderId, pname, &success);
    if (success) {
    } else {
        glGetProgramInfoLog(shaderId, GL_INFO_LOG_LENGTH, nullptr, infoLog);
        MugLogger::warn("Shader Error - " + msg + "" + std::string(infoLog));
    }
    return success;
}
