#version 330 core

// in vec3 fColor;
out vec4 fColor;

void main() {
	float fragd = gl_FragCoord.z;
	fColor = vec4(vec3(1.0f), fragd*2);

}
