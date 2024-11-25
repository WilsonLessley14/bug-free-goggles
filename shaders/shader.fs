#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 TextureCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
  FragColor = mix(texture(texture0, TextureCoord) * vec4(vertexColor, 1.0), texture(texture1, TextureCoord) * vec4(vertexColor, 1.0), 0.2);
}
