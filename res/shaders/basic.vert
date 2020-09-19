#version 460
        
layout( location = 0 ) in vec3 pos;        
layout( location = 1 ) in vec3 col;

out vec3 aCol;

void main( void )
{
    aCol = col;
    gl_Position = vec4( pos, 1.f );
}