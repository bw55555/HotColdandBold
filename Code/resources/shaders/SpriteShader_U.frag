#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform bool shouldBlend;

void main()
{    
    vec4 texColor = texture(texture1, TexCoords);
    if(!shouldBlend && texColor.a < 0.1)
        discard;
    FragColor = texColor;
}