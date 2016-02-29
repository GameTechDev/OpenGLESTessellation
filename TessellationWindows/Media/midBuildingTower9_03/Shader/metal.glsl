//--------------------------------------------------------------------------------------
// Copyright 2014 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
//--------------------------------------------------------------------------------------
// Generated by ShaderGenerator.exe version 0.13
//--------------------------------------------------------------------------------------
precision highp float;

const int NumLights = 2;
const vec3 LightDirections[NumLights] = vec3[]( vec3(0.0, -1.0,  -1.0),
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
   vec4  TotalTimeInSeconds;
};

#ifdef GLSL_VERTEX_SHADER

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
// -------------------------------------
in vec4 outPosition;
in vec3 outNormal;
in vec3 outTangent;
in vec3 outBinormal;
in vec2 outUV0;
in vec3 outWorldPosition; // Object space position 
// -------------------------------------
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
// -------------------------------------
vec4 DIFFUSE( )
{
    vec4 tex = texture(Texture0,(((outUV0)) *(vec2(1, 1).xy)) );
    #ifdef OPENGL_ES
    return vec4(pow(tex.rgb,vec3(2.2)), tex.a);
    #endif
    return tex;
}

// -------------------------------------
vec4 NORMAL( )
{
    return texture(Texture1,(((outUV0)) *(vec2(1, 1).xy)) ) * 2.0 - 1.0;
}

// -------------------------------------
vec4 SPECULARTMP( )
{
    vec4 tex = texture(Texture2,(((outUV0)) *(vec2(1, 1).xy)) );
    #ifdef OPENGL_ES
    return vec4(pow(tex.rgb,vec3(2.2)), tex.a);
    #endif
    return tex;
}

// -------------------------------------
float SPECULARITYTMP( )
{
    return texture(Texture3,(((outUV0)) *(vec2(1, 1).xy)) );
}

// -------------------------------------
vec4 SPECULAR( )
{
    return ((SPECULARTMP()) *(SPECULARITYTMP())) *(1.5);
}

// -------------------------------------
float SPECULARITY( )
{
    return 10.0;
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

    outPosition      = vec4( Position, 1.0) * WorldViewProjection;
    outWorldPosition = (vec4( Position, 1.0) * World ).xyz;

    // TODO: transform the light into object space instead of the normal into world space
    outNormal   = Normal   * mat3(World);
    outTangent  = Tangent  * mat3(World);
    outBinormal = Binormal * mat3(World);
	outUV0 = UV0;

    gl_Position = outPosition;
}

#endif //GLSL_VERTEX_SHADER

#ifdef GLSL_FRAGMENT_SHADER

out vec4 fragColor;

// -------------------------------------
void main( )
{
    vec4 result = vec4(0,0,0,1);

    vec3 normal   = outNormal;
    vec3 tangent  = outTangent;
    vec3 binormal = outBinormal;
    mat3 tangentToWorld = mat3(tangent, binormal, normal);
    normal = normalize(  tangentToWorld * NORMAL().xyz );

    // Specular-related computation
    vec3 eyeDirection  = normalize(outWorldPosition - EyePosition.xyz);
    vec3 Reflection    = reflect( eyeDirection, normal );
    float  shadowAmount = 1.0;

    // Ambient-related computation
    vec3 ambient = AmbientColor.rgb * AMBIENT().rgb;
    result.xyz +=  ambient;
   vec3 lightDirection = -LightDirection.xyz;

    // Diffuse-related computation
    for(int ii=0; ii<NumLights; ++ii) {
        lightDirection = -LightDirections[ii];
        float  nDotL = max( 0.0,dot( normal, lightDirection ) );
        vec3 diffuse = LightColors[ii].rgb * nDotL * shadowAmount  * DIFFUSE().rgb;
        result.xyz += diffuse * (1.0/float(NumLights));
        float  rDotL = max(0.0,dot( Reflection, lightDirection ));
        vec3 specular = pow(rDotL,  SPECULARITY() ) * SPECULAR().rgb * LightColor.rgb;
        result.xyz += specular * (1.0/float(NumLights));
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
