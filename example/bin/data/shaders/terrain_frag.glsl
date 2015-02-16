#version 410

out vec4 fragment;

in vec3 gFacetNormal;
in vec3 gTriDistance;
in vec3 gPatchDistance;

uniform sampler2DRect heightmap;
uniform sampler2DRect colourmap;

uniform float alpha;

uniform int wireframe;

in vec2 texcoord;

float amplify(float d, float scale, float offset)
{
    d = scale * d + offset;
    d = clamp(d, 0, 1);
    d = 1 - exp2(-2*d*d);
    return d;
}

void main(){
    
    vec4 diffuse = texture(colourmap, texcoord) * vec4(1.0,1.0,1.0,alpha);
    
    vec4 ambient = vec4(1.0,1.0,1.0,alpha);
    vec3 N = normalize(gFacetNormal);
    vec3 L = vec3(0,1000,1000);
    float df = abs(dot(N, L));
    //vec3 color = normalize(ambient.xyz + df * diffuse.xyz);
    vec3 color = diffuse.xyz;
    
    float d1 = min(min(gTriDistance.x, gTriDistance.y), gTriDistance.z);
    
    //float d2 = min(min(gPatchDistance.x, gPatchDistance.y), gPatchDistance.z);
    //color = amplify(d1, 100, 0.1) * amplify(d2, 150, 0.1) * color;
    
    //color = amplify(d1, 30, -0.5) * amplify(d2, 70, -0.5) * color;
    
    color = amplify(d1, 30, -0.5) * color;
    
    if(wireframe == 1){
        fragment = vec4(color, alpha);
    }else{
        fragment = diffuse;
    }
	
}
