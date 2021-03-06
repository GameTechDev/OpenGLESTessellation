////////////////////////////////////////////////////////////////////////////////
// Copyright 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License.  You may obtain a copy
// of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
// License for the specific language governing permissions and limitations
// under the License.
////////////////////////////////////////////////////////////////////////////////
// Generated by ShaderGenerator.exe version 0.13
//--------------------------------------------------------------------------------------

// Fog color in both shaders
// Skybox
precision highp float;

const float TessellationHeight = 5500.0; // Height of a 1.0 in the height map (height map * TessellationHeight)

const int NumLights = 2;
const vec3 LightDirections[NumLights] = vec3[]( vec3(-1.0, -1.0,  -1.0),
                                                vec3(0.5, -1.0,  1.0) );
const vec3 LightColors[NumLights] = vec3[]( vec3(0.362, 0.526, 0.575),
                                            vec3(0.630, 0.914, 1.0));

// -------------------------------------
layout (std140, row_major) uniform cbPerModelValues
{
   mat4 World;
   mat4 NormalMatrix;
   mat4 WorldViewProjection;
   mat4 InverseWorld;
   mat4 LightWorldViewProjection;
   vec4 BoundingBoxCenterWorldSpace;
   vec4 BoundingBoxHalfWorldSpace;
   vec4 BoundingBoxCenterObjectSpace;
   vec4 BoundingBoxHalfObjectSpace;
};

// -------------------------------------
layout (std140, row_major) uniform cbPerFrameValues
{
   mat4  View;
   mat4  InverseView;
   mat4  Projection;
   mat4  ViewProjection;
   vec4  AmbientColor;
   vec4  LightColor;
   vec4  LightDirection;
   vec4  EyePosition;
   vec4  MaxTessellation;
};
// -------------------------------------
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
// -------------------------------------
#ifdef GLSL_VERTEX_SHADER
precision highp float;

#define POSITION  0
#define NORMAL    1
#define BINORMAL  2
#define TANGENT   3
#define COLOR   4
#define TEXCOORD0 5
// -------------------------------------
layout (location = POSITION)  in vec3 Position; // Projected position
layout (location = NORMAL)    in vec3 Normal;
layout (location = TANGENT)   in vec3 Tangent;
layout (location = BINORMAL)  in vec3 Binormal;
layout (location = TEXCOORD0) in vec2 UV0;
// -------------------------------------
out vec4 outPosition;
out vec3 outNormal;
out vec3 outTangent;
out vec3 outBinormal;
out vec2 outUV0;
out vec3 outWorldPosition; // Object space position 
#endif //GLSL_VERTEX_SHADER
#ifdef GLSL_FRAGMENT_SHADER
precision highp float;
// -------------------------------------
in vec4 outPosition;
in vec3 outNormal;
in vec3 outTangent;
in vec3 outBinormal;
in vec2 outUV0;
in vec3 outWorldPosition; // Object space position 
in vec3 outTriDistance;
// -------------------------------------
vec4 DIFFUSETMP( )
{
    return texture(Texture0,(((outUV0)) *(20.0)) );
}

// -------------------------------------
vec4 NORMAL( )
{
    return texture(Texture1,(((outUV0)) *(1.0)) ) * 2.0 - 1.0;
}

// -------------------------------------
vec4 AOMAP( )
{
    return texture(Texture2,(((outUV0)) *(1.0)) );
}

// -------------------------------------
vec4 DIFFUSE( )
{
	vec4 diffuse = DIFFUSETMP() * AOMAP();
#ifdef OPENGL_ES
	diffuse.rgb = pow(diffuse.rgb, vec3(2.2));
#endif
    return diffuse*vec4(2.0);
}

// -------------------------------------
vec4 AMBIENT( )
{
    return DIFFUSE();
}

// -------------------------------------
#endif //GLSL_FRAGMENT_SHADER

#ifdef GLSL_VERTEX_SHADER
// -------------------------------------
void main( )
{
    outPosition = vec4( Position, 1.0);
    outWorldPosition = (outPosition * World).xyz;
    outNormal   = Normal   * mat3(World);
    outTangent  = Tangent  * mat3(World);
    outBinormal = Binormal * mat3(World);
    outUV0 = UV0;
}

#endif //GLSL_VERTEX_SHADER
#ifdef  GLSL_TESS_CONTROL_SHADER

precision highp float;

#ifdef OPENGL_ES
#extension GL_INTEL_tessellation:require
#endif

layout(vertices = 3) out;

in vec4 outPosition[];
in vec3 outNormal[];
in vec3 outTangent[];
in vec3 outBinormal[];
in vec2 outUV0[];
in vec3 outWorldPosition[];

out  vec4  tcPosition[3];
out  vec3  tcNormal[3];
out  vec3  tcTangent[3];
out  vec3  tcBinormal[3];
out  vec2  tcUV0[3];
out  vec3  tcWorldPosition[3];

float level(float d)
{
    d = d/55000.0; // d = [0..1]
    float s = clamp(1.0*(d), 0.0, 1.0);
    return mix(MaxTessellation.x,1.0, s);
}
void main()
{
    tcPosition[gl_InvocationID] = outPosition[gl_InvocationID];
    tcWorldPosition[gl_InvocationID] = outWorldPosition[gl_InvocationID];

    tcNormal[gl_InvocationID] = outNormal[gl_InvocationID];
    tcBinormal[gl_InvocationID] = outBinormal[gl_InvocationID];
    tcTangent[gl_InvocationID] = outTangent[gl_InvocationID];
    tcUV0[gl_InvocationID] = outUV0[gl_InvocationID];

    if(gl_InvocationID == 0) {
        vec3 CamPos = EyePosition.xyz;
        
        float d0 = distance(CamPos, outWorldPosition[0]);
        float d1 = distance(CamPos, outWorldPosition[1]);
        float d2 = distance(CamPos, outWorldPosition[2]);
        
        gl_TessLevelOuter[2] = level(mix(d0,d1,0.5));
        gl_TessLevelOuter[0] = level(mix(d1,d2,0.5));
        gl_TessLevelOuter[1] = level(mix(d2,d0,0.5));
        
        float inner = max(max(gl_TessLevelOuter[0], gl_TessLevelOuter[1]),gl_TessLevelOuter[2]);
        gl_TessLevelInner[0] = inner;
    }
}

#endif  //GLSL_TESS_CONTROL_SHADER

#ifdef GLSL_TESS_EVALUATION_SHADER

precision highp float;

#ifdef OPENGL_ES
#extension GL_INTEL_tessellation:require
#endif // OPENGL_ES

layout(triangles,fractional_odd_spacing,ccw) in;

in  vec4  tcPosition[];
in  vec3  tcNormal[];
in  vec3  tcTangent[];
in  vec3  tcBinormal[];
in  vec2  tcUV0[];
in  vec3  tcWorldPosition[];

out vec4 outPosition;
out vec3 outNormal;
out vec3 outTangent;
out vec3 outBinormal;
out vec2 outUV0;
out vec3 outWorldPosition;

vec2 interpolate(vec2 a, vec2 b, vec2 c)
{
    vec2 p0 = vec2(gl_TessCoord.x) * a;
    vec2 p1 = vec2(gl_TessCoord.y) * b;
    vec2 p2 = vec2(gl_TessCoord.z) * c;
    return p0+p1+p2;
}
vec3 interpolate(vec3 a, vec3 b, vec3 c)
{
    vec3 p0 = vec3(gl_TessCoord.x) * a;
    vec3 p1 = vec3(gl_TessCoord.y) * b;
    vec3 p2 = vec3(gl_TessCoord.z) * c;
    return p0+p1+p2;
}
vec4 interpolate(vec4 a, vec4 b, vec4 c)
{
    vec4 p0 = vec4(gl_TessCoord.x) * a;
    vec4 p1 = vec4(gl_TessCoord.y) * b;
    vec4 p2 = vec4(gl_TessCoord.z) * c;
    return p0+p1+p2;
}

void main()
{
    outPosition = interpolate(tcPosition[0],tcPosition[1],tcPosition[2]);
    outUV0 = interpolate(tcUV0[0],tcUV0[1],tcUV0[2]);
    outWorldPosition = interpolate(tcWorldPosition[0],tcWorldPosition[1],tcWorldPosition[2]);
    outNormal = interpolate(tcNormal[0],tcNormal[1],tcNormal[2]);
    outTangent = interpolate(tcTangent[0],tcTangent[1],tcTangent[2]);
    outBinormal = interpolate(tcBinormal[0],tcBinormal[1],tcBinormal[2]);

    float y = texture(Texture1,(outUV0)).a * TessellationHeight;
    outPosition.y = y;

    outPosition   = outPosition * WorldViewProjection;

    gl_Position = outPosition;
}
#endif  //GLSL_TESS_EVALUATION_SHADER

#ifdef GLSL_FRAGMENT_SHADER
out vec4 fragColor;// -------------------------------------

void main( )
{
    vec4 result = vec4(0.0,0.0,0.0,1.0);

    vec3 normal   = outNormal;
    vec3 tangent  = outTangent;
    vec3 binormal = outBinormal;
    mat3 tangentToWorld = mat3(tangent, binormal, normal);
    normal = normalize( tangentToWorld * NORMAL().bgr );
    float  shadowAmount = 1.0;

    // Ambient-related computation
    vec3 ambient = AmbientColor.rgb * AMBIENT().rgb;
    result.xyz +=  ambient;
    vec3 lightDirection = -LightDirection.xyz;

    // Diffuse-related computation
    vec3 albedo = DIFFUSE().rgb;
    
    for(int ii=0; ii<NumLights; ++ii) {
        lightDirection = -LightDirections[ii];
        float  nDotL = max( 0.0,dot( normal, lightDirection ) );
        vec3 diffuse = LightColors[ii] * nDotL * shadowAmount  * albedo;
        result.xyz += diffuse * (1.0/float(NumLights));
    }

    fragColor =  result;
    
    const vec4 FogColor = vec4(0.211,0.223,0.226,1.0);
    const float MinFogDistance = 5000.0;
    const float MaxFogDistance = 75000.0;
    float dist = distance(outWorldPosition, EyePosition.xyz);
    float fog_factor = clamp((MaxFogDistance - dist)/(MaxFogDistance - MinFogDistance),0.0,1.0);
    fragColor =  mix(fragColor,FogColor,1.0-fog_factor);

    #ifdef OPENGL_ES
    fragColor.rgb = pow(fragColor.rgb, vec3(0.454545454545));
    #endif
}

#endif //GLSL_FRAGMENT_SHADER
