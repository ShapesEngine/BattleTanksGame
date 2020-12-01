#version 460
        
in vec2 texCoord;

out vec4 fragCol;

uniform sampler2D tex;

void main( void )
{
    fragCol = texture( tex, texCoord );

    if( fragCol.rgb == 0.f )
        discard;
}