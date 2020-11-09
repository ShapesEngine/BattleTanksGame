#version 460
        
layout( location = 0 ) in vec2 pos;
layout( location = 1 ) in vec2 tex;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;

void main( void )
{
    texCoord = tex;
    gl_Position = projection * model * vec4( pos, 0.f, 1.f );
}