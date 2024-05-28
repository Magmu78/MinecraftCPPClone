#version 330 core

struct Material {
    sampler2D diffuse; // Diffuse map
    vec3 specular; // Specular color
    float shininess; // Shininess factor
};

struct Light {
    vec3 position; // Light position

    vec3 ambient; // Ambient color
    vec3 diffuse; // Diffuse color
    vec3 specular; // Specular color
};

in vec3 FragPos; // Fragment position
in vec3 Normal; // Normal vector
in vec2 TexCoords; // Texture coordinates

out vec4 FragColor; // Output fragment color

uniform vec3 viewPos; // Camera position
uniform Light light; // Light struct
uniform Material material; // Material struct

void main()
{
    // Ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}