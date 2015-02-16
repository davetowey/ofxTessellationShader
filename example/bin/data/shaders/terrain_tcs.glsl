#version 410

layout(vertices = 3) out;

uniform int outerLevel;
uniform int innerLevel;
uniform int dynamic;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 eye_position;


float level (vec4 pos1, vec4 pos2){
    
    float lod = clamp(distance(pos2, pos1)/20, 0, 63);
    return 64 - lod;
    
}

bool offscreen(vec4 vertex){//vertex should be ndc
    
    return false;
    
    vec4 p = modelViewProjectionMatrix * vertex ;
    
    p = p / vec4(p.w);
    
    if(p.z < -0.5 || p.x < -1 || p.x > 1  ) return true;
    
    return false;
    
}

void main(){
    

    if (gl_InvocationID == 0){
        
        vec4 c1 = gl_in[0].gl_Position;
        vec4 c2 = gl_in[1].gl_Position;
        vec4 c3 = gl_in[2].gl_Position;

        vec3 d1=gl_in[1].gl_Position.xyz+(gl_in[2].gl_Position.xyz-gl_in[1].gl_Position.xyz)/2;
        vec3 d2=gl_in[0].gl_Position.xyz+(gl_in[2].gl_Position.xyz-gl_in[0].gl_Position.xyz)/2;
        vec3 d3=gl_in[0].gl_Position.xyz+(gl_in[1].gl_Position.xyz-gl_in[0].gl_Position.xyz)/2;
        
        float e0=level(vec4(d1,1.0),vec4(eye_position,1.0));
        float e1=level(vec4(d2,1.0),vec4(eye_position,1.0));
        float e2=level(vec4(d3,1.0),vec4(eye_position,1.0));
        
        float m=min(e0,min(e1,e2));
        
        if(all(bvec3(
                     offscreen(c1),
                     offscreen(c2),
                     offscreen(c3)
                     ))){
            
            gl_TessLevelInner[0] = 0;
            gl_TessLevelOuter[0] = 0;
            gl_TessLevelOuter[1] = 0;
            gl_TessLevelOuter[2] = 0;
            
        }else{
        
            if(dynamic == 1){
                
                gl_TessLevelInner[0] = floor((min(e0,min(e1,e2))+max(e0,max(e1,e2)))/2);
                gl_TessLevelOuter[0] = e0;
                gl_TessLevelOuter[1] = e1;
                gl_TessLevelOuter[2] = e2;
                
            }else{
             
                gl_TessLevelInner[0] = innerLevel;
                gl_TessLevelOuter[0] = outerLevel;
                gl_TessLevelOuter[1] = outerLevel;
                gl_TessLevelOuter[2] = outerLevel;
            
            }
        }
    
    }
    
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    
}