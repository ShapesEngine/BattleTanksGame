#version 460
        
in vec3 aCol;
in vec2 texCoord;

uniform sampler2D tex;

out vec4 fragCol;

void main( void )
{
    fragCol = texture( tex, texCoord );
}