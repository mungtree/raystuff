#version 430 core
in vec2 uv;
in vec3 color;
out vec4 FragColor;
uniform float time;

float rand(float x) {
    return fract(sin(x) * 43758.5453123);
}

void main()
{
    // FragColor = vec4(uv.x, uv.y, 1.0 - uv.x, 1.0);
    FragColor = vec4(color, 1.0);
    // FragColor = vec4(r, g, b, 1.0);
} 
