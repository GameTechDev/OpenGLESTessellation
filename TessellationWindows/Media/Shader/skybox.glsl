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
precision highp float;

// -------------------------------------
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
// -------------------------------------
uniform samplerCube Texture0;
// -------------------------------------

#ifdef GLSL_VERTEX_SHADER

#define POSITION  0
#define NORMAL    1
#define BINORMAL  2
#define TANGENT   3
#define COLOR     4
#define TEXCOORD0 5
// -------------------------------------
layout (location = POSITION)  in vec3 Position; // Projected position
layout (location = TEXCOORD0) in vec2 UV;
// -------------------------------------
out vec3 vPosition;
out vec2 vUV;

void main()
{
    vPosition = Position;
    vUV = UV;
    gl_Position = vec4(vPosition,1);
}

#endif //GLSL_VERTEX_SHADER


#ifdef GLSL_GEOMETRY_SHADER

#ifdef OPENGL_ES
#extension GL_INTEL_geometry_shader:require
#endif

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 vPosition[1];
in vec2 vUV[1];

out vec4 outPosition;
out vec3 outUV;

void main()
{
	vec4 viewSpacePosition;
    vec2 proj_div = vec2(Projection[0][0], Projection[1][1]);

    outPosition = vec4( -1, -1, 0.5, 1);
    gl_Position = outPosition;
    viewSpacePosition = vec4(outPosition.xy, 1.0f, 0.0f);
    viewSpacePosition.xy /= proj_div;
    outUV = (viewSpacePosition * InverseView).xzy;
    EmitVertex();
    
    outPosition = vec4( -1, 1, 0.5, 1);
    gl_Position = outPosition;
    viewSpacePosition = vec4(outPosition.xy, 1.0f, 0.0f);
    viewSpacePosition.xy /= proj_div;
    outUV = (viewSpacePosition * InverseView).xzy;
    EmitVertex();
    
    outPosition = vec4( 1, -1, 0.5, 1);
    gl_Position = outPosition;
    viewSpacePosition = vec4(outPosition.xy, 1.0f, 0.0f);
    viewSpacePosition.xy /= proj_div;
    outUV = (viewSpacePosition * InverseView).xzy;
    EmitVertex();
    
    outPosition = vec4( 1, 1, 0.5, 1);
    gl_Position = outPosition;
    viewSpacePosition = vec4(outPosition.xy, 1.0f, 0.0f);
    viewSpacePosition.xy /= proj_div;
    outUV = (viewSpacePosition * InverseView).xzy;
    EmitVertex();

    EndPrimitive();
}
#endif // GLSL_GEOMETRY_SHADER

#ifdef GLSL_FRAGMENT_SHADER
in vec4 outPosition;
in vec3 outUV;

out vec4 FinalColor;

void main()
{
	 vec4 color = texture(Texture0, outUV);
    FinalColor = color;
}
#endif // GLSL_FRAGMENT_SHADER
