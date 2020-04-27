#version 330 core

in vec3 position;
uniform mat4 proj, view, transf;

void main() {
	gl_Position = proj * view * transf * vec4(position, 1.0f);
}
