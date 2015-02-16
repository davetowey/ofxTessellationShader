#version 410

in vec4 position;

uniform sampler2DRect heightmap;
uniform float offset;
uniform float ve;

void main(void){

    vec2 tc = vec2(position.x + 512 + offset, position.z + 512);
    
    if(offset > 0.0){
        tc = mod(vec2(position.x + 512 + offset, position.z + 512), vec2(1024,1024));
    }
    
    float height = texture(heightmap,tc).r * ve;
      
    gl_Position = vec4( position.x, height, position.z, 1.0);

}
