#ifdef VERTEX_SHADER

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uView;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

void main()
{
  gl_Position =  uProjection * uView * uModel * vec4(aPos, 1.0);
  texCoord = aTexCoord;
  normal = mat3(transpose(inverse(uModel))) * aNormal;
  fragPos = vec3(uModel * vec4(aPos, 1.0));
}

#else

uniform sampler2D uTexture;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

void main()
{
  float ambientStrength = 0.2;

  vec3 lightColor = vec3(1.0);
  vec3 lightDirection = vec3(-0.2, -1.0, -0.3);
  //vec3 lightDir = normalize(lightPos - fragPos);
  //vec3 lightPos = vec3(1.2, 1.0, 2.0);

  vec3 ambient = ambientStrength * lightColor;

  vec3 lightDir = -normalize(lightDirection);
  vec3 norm = normalize(normal);
  float diff = max(dot(norm, lightDir), 0.0);

  vec3 diffuse = diff * lightColor;

  fragColor = vec4(ambient + diffuse, 1.0) * texture(uTexture, texCoord);
}

#endif