//
// Created by meet on 5/31/25.
//

#ifndef SIMPLETRIANGLE_H
#define SIMPLETRIANGLE_H
#include <memory>

#include "SimplePoint.h"
#include "glad/glad.h"

/**
 * Draws triangle using simple points.
 * Expects shader to be set up to properly handle it.
 */
class SimpleTriangle {
private:
    GLuint vao;
    GLuint vbo;
public:
    SimpleTriangle(SimplePoint bl, SimplePoint top, SimplePoint br);
    ~SimpleTriangle();
    void draw();
    void update(SimplePoint bl, SimplePoint top, SimplePoint br);

    [[nodiscard]] int glInternalGetVAO() const;
    [[nodiscard]] int glInternalGetVBO() const;
};



#endif //SIMPLETRIANGLE_H
