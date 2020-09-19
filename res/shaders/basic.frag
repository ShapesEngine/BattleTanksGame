#version 460
        
in vec3 aCol;

out vec4 fragCol;

void main( void )
{
    fragCol = vec4( aCol, 1.f );
}