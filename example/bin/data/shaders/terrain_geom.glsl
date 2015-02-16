#version 150

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 tePosition[3];
in vec3 tePatchDistance[3];
in vec2 teTexCoord[3];

out vec3 gFacetNormal;
out vec3 gPatchDistance;
out vec3 gTriDistance;
out vec2 texcoord;

void main()
{
    vec3 A = tePosition[2] - tePosition[0];
    vec3 B = tePosition[1] - tePosition[0];
    gFacetNormal = normalize(cross(A, B));
    
    gPatchDistance = tePatchDistance[0];
    gTriDistance = vec3(1, 0, 0);
    texcoord = teTexCoord[0];
    gl_Position = gl_in[0].gl_Position; EmitVertex();
    
    gPatchDistance = tePatchDistance[1];
    gTriDistance = vec3(0, 1, 0);
    texcoord = teTexCoord[1];
    gl_Position = gl_in[1].gl_Position; EmitVertex();
    
    gPatchDistance = tePatchDistance[2];
    gTriDistance = vec3(0, 0, 1);
    texcoord = teTexCoord[2];
    gl_Position = gl_in[2].gl_Position; EmitVertex();
    
    
    EndPrimitive();
}