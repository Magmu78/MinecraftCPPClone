#version 330 core

layout(location = 0) in vec3 aPos; // Vertex position
layout(location = 1) in vec3 aNormal; // Vertex normal
layout(location = 2) in vec2 aTexCoords; // Vertex texture coordinates

out vec3 FragPos; // Fragment position
out vec3 Normal; // Normal vector
out vec2 TexCoords; // Texture coordinates

uniform mat4 model; // Model matrix
uniform mat4 camMatrix;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    
    gl_Position = camMatrix * vec4(FragPos, 1.0);
}