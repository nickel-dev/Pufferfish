#ifdef VERTEX_SHADER

layout (location = 0) in vec3 aPos;

uniform mat4 uProjection;
uniform mat4 uView;

out vec3 texCoord;

void main()
{
  texCoord = aPos;
  gl_Position = uProjection * uView * vec4(aPos, 1.0);
}

#else

uniform samplerCube uSkybox;

out vec4 fragColor;
in vec3 texCoord;

void main()
{
  fragColor = texture(uSkybox, texCoord);
}

#endif