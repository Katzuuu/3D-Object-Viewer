#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;

out vec4 vCol;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
    texCoord = tex;
}