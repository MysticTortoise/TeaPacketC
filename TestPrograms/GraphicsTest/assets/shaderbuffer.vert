#version 450

layout(location = 0) in vec2 i_position;

layout(binding = 0, std140) uniform u_block1
{
    vec2 u_pos;
};

void main()
{
    gl_Position = vec4(i_position + u_pos, 0.5f, 1.0f);
}