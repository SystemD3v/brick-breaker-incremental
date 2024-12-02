#version 330 core

layout(location = 0) in vec3 position; // Vertex position

void main() {
    gl_Position = vec4(position, 1.0); // Pass position to the fragment shader
}
