#version 440 core

struct Material
{
    vec3 Color;
    sampler2D Diffuse;
    sampler2D Specular;
    sampler2D Emission;
    float Shininess;
    bool Active;
};

layout(location = 0) out vec4 outColor;

in vec2 TexCoords;
in vec3 Normal;

uniform Material material;

void main()
{
    vec4 texel = texture(material.Diffuse, TexCoords);
    outColor = texel;
}