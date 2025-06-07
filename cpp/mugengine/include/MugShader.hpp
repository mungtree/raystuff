//
// Created by meet on 5/31/25.
//

#ifndef MUGSHADER_H
#define MUGSHADER_H
#include <string>
#include <memory>

#include "glad/glad.h"


class MugShader {
private:
    static std::string read_file(std::string path);
    GLuint shaderProgram = 0;
public:
    static std::shared_ptr<MugShader> loadShader(const std::string& vpath, const std::string &fpath);
    static std::shared_ptr<MugShader> loadShaderNamed(std::string path, std::string name);
    static bool logShaderCompileStatus(GLuint shaderId, GLenum pname, const std::string &msg = "{}");

    MugShader(GLuint shaderProgram);
    GLuint getShaderProgram() const { return shaderProgram; }
    void bind();
    void unbind();
    ~MugShader();
};



#endif //MUGSHADER_H
