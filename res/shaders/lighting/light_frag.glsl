#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 viewPos;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 objectColor;

void main()
{
    vec3 norm = normalize(Normal);

    // ---- Ambient ----- //
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // ---- Diffuse ----- //
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diffuseFactor * lightColor;

    // ---- Specular----- //
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float shininess = 32;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    color = vec4(result, 1.0f);

}