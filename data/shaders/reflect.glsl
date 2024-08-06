#ifdef VERTEX_SHADER

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uView;

out vec3 normal;
out vec3 position;

void main()
{
  normal = mat3(transpose(inverse(uModel))) * aNormal;
  position = vec3(uModel * vec4(aPos, 1.0));
  gl_Position = uProjection * uView * vec4(position, 1.0);
}

#else

uniform vec3 uCameraPos;
uniform samplerCube uSkybox;

in vec3 normal;
in vec3 position;

out vec4 fragColor;

void main()
{
  vec3 I = normalize(position - uCameraPos);
  vec3 R = reflect(I, normalize(normal));
  fragColor = vec4(texture(uSkybox, R).rgb, 1.0);
}

#endif