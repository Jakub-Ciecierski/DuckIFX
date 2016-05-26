#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 objectColor;

void main()
{
    // ---- Ambient ----- //
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // ---- Diffuse ----- //
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);

    vec3 diffuse = diffuseFactor * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

    color = vec4(result, 1.0f);
}