#ifdef VERTEX_SHADER

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uView;

out vec2 texCoord;

void main()
{
    gl_Position =  /*uProjection * uView * uModel */ vec4(aPos, 1.0);
    texCoord = aTexCoord;
}

#else

uniform sampler2D uTexture;

in vec2 texCoord;
in float normal;

out vec4 fragColor;

void main()
{
    fragColor = vec4(1.0);//texture(uTexture, texCoord);
}

#endif