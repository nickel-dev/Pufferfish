#ifdef VERTEX_SHADER

layout (location = 0) in vec4 aVert;
out vec2 texCoords;

uniform mat4 uProjection;

void main()
{
  gl_Position = uProjection * vec4(aVert.x, aVert.y, -0.6, 1.0);
  texCoords = aVert.zw;
}

#else

in vec2 texCoords;
out vec4 fragColor;

uniform sampler2D uText;
uniform vec3 uTextColor;

void main()
{
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uText, texCoords).r);
  fragColor = vec4(uTextColor, 1.0) * sampled;
}

#endif