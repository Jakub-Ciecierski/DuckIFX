#version 330 core

/*
 * Phong illumination: Global Light with Attenuation.
 * Use with com
 */

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

struct Material {
    sampler2D diffuse; // ambient == diffuse
    sampler2D specular;

    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    vec3 norm = normalize(Normal);

    // ---- Ambient ----- //
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

    // ---- Diffuse ----- //
    vec3 lightDir = normalize(light.position - FragPos);
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse =
    diffuseFactor * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;

    // ---- Specular ----- //
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =
    vec3(texture(material.specular, TexCoords)) * spec * light.specular;

    // ---- Attenuation ----- //
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0f /
    ((light.constant) +
    (light.linear * distance) +
    (light.quadratic * (distance* distance)));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular);
    color = vec4(result, 1.0f);
}