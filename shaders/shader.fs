#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 TextureCoord;

uniform sampler2D ourTexture;

void main() {
  FragColor = texture(ourTexture, TextureCoord) * vec4(vertexColor, 1.0);
}
