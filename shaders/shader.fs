#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 TextureCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

vec2 horizontallyFlippedTextureCoord = vec2(-TextureCoord.x, TextureCoord.y);
void main() {
  FragColor = mix(texture(texture0, TextureCoord) * vec4(vertexColor, 1.0), texture(texture1, horizontallyFlippedTextureCoord) * vec4(vertexColor, 1.0), 0.2);
}
