#version 460
        
layout( location = 0 ) in vec2 pos;
layout( location = 1 ) in vec2 tex;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;
uniform float depth_layer;

void main( void )
{
    texCoord = tex;
    gl_Position = projection * model * vec4( pos, depth_layer, 1.f );
}