#version 440 core

layout(location = 0) out vec4 outColor;

in vec2 texCoords;

uniform sampler2D textura;
uniform vec4 color;

void main()
{
    vec4 texel = texture(textura, texCoords);
    if(texel.a == 0.0f)
    {
        discard;
    }
    outColor = texel * color;
}