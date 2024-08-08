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
  fragPos = vec3(uModel * uView * vec4(aPos, 1.0));
}

#else

struct Light
{
  vec3 pos;
  vec3 dir;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Light light;
uniform sampler2D uTexture;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

void main()
{
  int shininess = 64;

  // ---- DIFFUSE ---- //
  //vec3 lightDir = normalize(light.pos - fragPos);
  vec3 lightDir = -normalize(light.dir);
  vec3 norm = normalize(normal);
  float diff = max(dot(norm, lightDir), 0.0);

  // ---- SPECULAR ---- //
  vec3 viewDir = normalize(-fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

  vec3 color = light.ambient + (diff * light.diffuse) + (spec * light.specular);
  fragColor = vec4(color, 1.0) * texture(uTexture, texCoord);
}

#endif