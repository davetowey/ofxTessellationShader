#version 410

layout(triangles, equal_spacing, ccw) in;

uniform mat4 modelViewProjectionMatrix;
uniform sampler2DRect heightmap;

uniform float offset;
out vec2 teTexCoord;

out vec3 tePosition;
out vec3 tePatchDistance;

uniform float ve;

void main(){
    
    vec4 position = (gl_TessCoord.x * gl_in[0].gl_Position
                     + gl_TessCoord.y * gl_in[1].gl_Position
                     + gl_TessCoord.z * gl_in[2].gl_Position);
    
    vec2 tc = vec2(position.x + 512 + offset, position.z + 512);
    
    if(offset > 0.0){
        tc = mod(vec2(position.x + 512 + offset, position.z + 512), vec2(1024,1024));
    }

    float height =  texture(heightmap,tc).r * ve;

    position.y = height;
    
    gl_Position = modelViewProjectionMatrix * position;

    teTexCoord = vec2(position.x + 512, position.z + 512);
    tePatchDistance = gl_TessCoord;
    tePosition = position.xyz;
    
}