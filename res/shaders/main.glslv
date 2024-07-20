#include <commons>

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texCoord;
layout (location = 2) in float v_light;

out vec4 a_color;
out vec2 a_texCoord;
out float a_distance;
out vec3 a_dir;

uniform mat4 u_model;
uniform mat4 u_proj;
uniform mat4 u_view;
uniform vec3 u_skyLightColor;
uniform vec3 u_cameraPos;
uniform float u_gamma;
uniform samplerCube u_cubemap;

uniform vec3 u_torchlightColor;
uniform float u_torchlightDistance;

void main(){
    vec4 modelpos = u_model * vec4(v_position, 1.0);
    vec3 pos3d = modelpos.xyz-u_cameraPos.xyz;
    modelpos.y -= pow(length(pos3d.xz)*CURVATURE_FACTOR, 3.0);
    vec4 viewmodelpos = u_view * modelpos;
    vec4 decomp_light = decompress_light(v_light);
    
    vec3 light = decomp_light.rgb;
    float torchlight = max(0.0, 1.0-distance(u_cameraPos, modelpos.xyz)/u_torchlightDistance);
    light += torchlight * u_torchlightColor;
    a_color = vec4(pow(light, vec3(u_gamma)),1.0f);
    a_texCoord = v_texCoord;

    a_dir = modelpos.xyz - u_cameraPos;
    vec3 skyLightColor = pick_sky_color(u_cubemap);
    a_color.rgb = max(a_color.rgb, skyLightColor.rgb*decomp_light.a);
    a_distance = length(u_view * u_model * vec4(pos3d * FOG_POS_SCALE, 0.0));
    gl_Position = u_proj * viewmodelpos;
}
