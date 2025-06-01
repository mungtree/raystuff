//
// Created by meet on 5/31/25.
//

#include "SimpleTriangle.h"

#include "glad/glad.h"

SimpleTriangle::SimpleTriangle(SimplePoint bl, SimplePoint top, SimplePoint br) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    update(bl, top, br);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

SimpleTriangle::~SimpleTriangle() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void SimpleTriangle::update(SimplePoint bl, SimplePoint top, SimplePoint br) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    float vertices[] = {
        bl.x, bl.y, bl.z,
        top.x, top.y, top.z,
        br.x, br.y, br.z
    };
    glBufferData(GL_ARRAY_BUFFER, SimplePoint::size * 3, vertices, GL_STATIC_DRAW);
}

void SimpleTriangle::draw() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

int SimpleTriangle::glInternalGetVAO() const {
    return vao;
}

int SimpleTriangle::glInternalGetVBO() const {
    return vbo;
}
