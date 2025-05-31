#version 430 core
layout (location = 0) in vec3 aPos;
out vec2 uv;
out vec3 mcol;

layout(binding = 2, std430) readonly buffer ssbo1 {
    vec3 colors;
};

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = aPos.xy * 0.5 + 0.5; // map [-1, 1] to [0, 1]
    mcol = colors;
}
