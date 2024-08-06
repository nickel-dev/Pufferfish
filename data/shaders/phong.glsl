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
out vec3 lightPos;

void main()
{
	vec3 uLightPos = vec3(0.0, 5.0, 0.0);

  vec4 ffragPos = uModel * vec4(aPos, 1.0);
  gl_Position =  uProjection * uView * ffragPos;
  texCoord = aTexCoord;
  normal = mat3(transpose(inverse(uView * uModel))) * aNormal;
	lightPos = vec3(mat4(mat3(uView)) * vec4(uLightPos, 1.0));
  fragPos = ffragPos.xyz;
}

#else

uniform sampler2D uTexture;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec3 lightPos;

out vec4 fragColor;

void main()
{
  vec3 lightColor = vec3(0.9, 0.9, 0.8);

  float ambientStrength = 0.3;
  vec3 ambient = ambientStrength * lightColor;

  // diffuse
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  // specular
  float specularStrength = 0.5;
  vec3 viewDir = normalize(-fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  vec3 specular = specularStrength * spec * lightColor;

  fragColor = vec4(ambient + diffuse + specular, 1.0) * texture(uTexture, texCoord);
}

#endif