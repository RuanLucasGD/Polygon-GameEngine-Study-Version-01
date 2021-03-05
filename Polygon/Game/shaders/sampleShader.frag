#version 330 core

#define MAX_NUMBER_OF_POINT_LIGTHS	32
#define MAX_NUMBER_OF_SPOT_LIGHTS	32

in vec3 fragPos;
in vec3 normalWolrdDirection;
in vec2 textCoords;

out vec4 fragColor;

uniform vec3 cameraPos;

struct Ambient
{	
	vec3 color;
	float intensity;
	vec3 lightDir;
};

struct Material
{	
	vec3 color;
	float specular;
	bool textureIsNull;
	sampler2D diffuseTexture;
};

struct SunLight
{
	vec3 dir;
	vec3 color;
	float intensity;
};

struct PointLight
{	
	vec3 pos;
	vec3 color;
	float intensity;
	float maxDistance;
};

struct SpotLight
{
	vec3 pos;
	vec3 dir;
	vec3 color;
	float intensity;
	float maxDistance;
	float angle;
};

vec3 CalcAmbientLight(Ambient ambient, SunLight sun, Material material, vec3 normal)
{
	vec3 sunDir = sun.dir;

	vec3 sunColor = sun.color;
	vec3 ambientColor = ambient.color;

	float maxSpecular = material.specular;

	float diffuse = max(dot(sunDir, normal), 0);
	vec3 color = sunColor * diffuse;
	color += ambientColor;

	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectionDir = reflect(-sunDir, normal);

	float specularIntensity = pow(max(dot(viewDir, reflectionDir), 0), 32);
	vec3 specular = vec3(maxSpecular) * specularIntensity;

	return color + specular;
}

vec3 CalcLightPoint(PointLight light, Material material, vec3 normal)
{	
	float maxDistance = light.maxDistance;
	float maxSpecular = material.specular;
	vec3 lightColor = light.color;
	
	vec3 lightPos = light.pos;
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 lightDirNoramlized = normalize(lightPos - (fragPos + normalize(lightPos)));

	// diffuse
	float intensityPerDistance = 1 - (clamp(distance(lightPos, fragPos), 0, maxDistance) / maxDistance);
	float diffuseIntensity = (max(dot(lightDirNoramlized, normal), 0) * intensityPerDistance);
	vec3 diffuse = lightColor * diffuseIntensity;

	// specular
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularIntensity = pow(max(dot(viewDir, reflectionDir), 0), 32);
	vec3 specularColor = vec3(maxSpecular) * specularIntensity * lightColor; 

	vec3 color = diffuse + specularColor;

	return color;
}

vec3 CalcSpotLight(SpotLight light, Material material, vec3 normal)
{
	vec3 lightPos = light.pos;
	vec3 lightDir = light.dir;
	vec3 fragmentLightDir = normalize(lightPos - fragPos);

	float maxSpecular = material.specular;
	float spotAngle = light.angle;
	float maxDistance = light.maxDistance;
	vec3 lightColor = light.color;

	// create cone
	float theta = dot(fragmentLightDir, -lightDir);
	float angle = cos(radians(spotAngle));
	// smooth edges
	float externAngle = cos(radians(spotAngle + (spotAngle * 0.15f)));
	float epsilon = angle - externAngle;

	// diffuse
	float dist = clamp(distance(fragPos, lightPos), 0, maxDistance);
	float influenceAngle = max(dot(fragmentLightDir, normal), 0);
	float influenceDist = 1 - (dist / maxDistance);
	float intensity = clamp((theta - externAngle) / epsilon, 0, 1);

	vec3 color = light.color * influenceAngle * intensity * influenceDist;

	// specular
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-fragmentLightDir, normal);
	float specularIntensity = pow(max(dot(viewDir, reflectDir), 0), 32);

	color += vec3(maxSpecular) * specularIntensity * lightColor * intensity;

	return color;
}

uniform Material material;

uniform int pointLightsAmount;
uniform int spotLightsAmount;

uniform Ambient ambient;
uniform SunLight sunLight;
uniform PointLight pointLights[MAX_NUMBER_OF_POINT_LIGTHS];
uniform SpotLight spotLights[MAX_NUMBER_OF_SPOT_LIGHTS];

void main()
{
	vec3 normal = normalize(normalWolrdDirection);
	
	vec3 lightsColor = CalcAmbientLight(ambient, sunLight, material, normal);

	for (int i = 0; i < pointLightsAmount; i++)
	{	
		lightsColor += CalcLightPoint(pointLights[i], material, normal);
	}

	for (int i = 0; i < spotLightsAmount; i++)
	{	
		lightsColor += CalcSpotLight(spotLights[i], material, normal);
	}

	vec4 finalColor = vec4(material.color * lightsColor, 1);

	if (!material.textureIsNull)
	{
		finalColor *= texture(material.diffuseTexture, textCoords);
	}

	fragColor = finalColor;
}