#version 460
out vec4 FragColor;
in vec3 oCol;

void main()
{
    FragColor = vec4(oCol, 1.0f);
}
