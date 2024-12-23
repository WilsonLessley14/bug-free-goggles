#version 330 core

out vec4 FragColor;

in vec2 TextureCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform float opacity;

vec2 horizontallyFlippedTextureCoord = vec2(-TextureCoord.x, TextureCoord.y);

void main() {
  FragColor = mix(texture(texture0, TextureCoord), texture(texture1, horizontallyFlippedTextureCoord), opacity);
}
