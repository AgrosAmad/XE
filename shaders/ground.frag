#version 440 core

layout(location = 0) out vec4 outColor;

in vec2 texCoords;

uniform sampler2D snowTex;
uniform sampler2D pathTex;
uniform sampler2D pavementTex;

void main()
{
    vec4 snowTexel = texture(snowTex, texCoords);
	vec4 pathTexel = texture(pathTex, texCoords / 20.0f);
	vec4 pavementTexel = texture(pavementTex, texCoords);
	float pathWeight = 0.6*pathTexel.r;
	float snowWeight = 1.0f - pathWeight;
	outColor = pavementTexel * pathWeight + snowTexel * snowWeight;
}