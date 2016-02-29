//--------------------------------------------------------------------------------------
// Copyright 2013 Intel Corporation
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
#ifndef __CPUTMATERIALDX11_H__
#define __CPUTMATERIALDX11_H__

#include <d3d11.h>
#include "d3d11shader.h"
#include "CPUTMaterial.h"
class CPUTPixelShaderDX11;
class CPUTComputeShaderDX11;
class CPUTVertexShaderDX11;
class CPUTGeometryShaderDX11;
class CPUTHullShaderDX11;
class CPUTDomainShaderDX11;
class CPUTModel;
class CPUTBufferDX11;

class CPUTShaderParameters
{
public:
    UINT                       mTextureCount;
    cString                   *mpTextureParameterName;
    UINT                      *mpTextureParameterBindPoint;
    UINT                       mTextureParameterCount;
    CPUTTexture               *mpTexture[CPUT_MATERIAL_MAX_TEXTURE_SLOTS];
    CPUTBuffer                *mpBuffer[CPUT_MATERIAL_MAX_BUFFER_SLOTS];
    CPUTBuffer                *mpUAV[CPUT_MATERIAL_MAX_UAV_SLOTS];
    CPUTBuffer                *mpConstantBuffer[CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS];

    cString                   *mpSamplerParameterName;
    UINT                      *mpSamplerParameterBindPoint;
    UINT                       mSamplerParameterCount;

    UINT                       mBufferCount;
    UINT                       mBufferParameterCount;
    cString                   *mpBufferParameterName;
    UINT                      *mpBufferParameterBindPoint;

    UINT                       mUAVCount;
    UINT                       mUAVParameterCount;
    cString                   *mpUAVParameterName;
    UINT                      *mpUAVParameterBindPoint;

    UINT                       mConstantBufferCount;
    UINT                       mConstantBufferParameterCount;
    cString                   *mpConstantBufferParameterName;
    UINT                      *mpConstantBufferParameterBindPoint;
    D3D11_SHADER_BUFFER_DESC  *mpConstantBufferDesc;
    ID3D11ShaderReflectionConstantBuffer **mpConstantBufferReflection;

    UINT                       mBindViewMin;
    UINT                       mBindViewMax;

    UINT                       mBindUAVMin;
    UINT                       mBindUAVMax;

    UINT                       mBindConstantBufferMin;
    UINT                       mBindConstantBufferMax;

    ID3D11ShaderResourceView  *mppBindViews[CPUT_MATERIAL_MAX_SRV_SLOTS];
    ID3D11UnorderedAccessView *mppBindUAVs[CPUT_MATERIAL_MAX_UAV_SLOTS];
    ID3D11Buffer              *mppBindConstantBuffers[CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS];

    CPUTShaderParameters() :
        mTextureCount(0),
        mTextureParameterCount(0),
        mpTextureParameterName(NULL),
        mpTextureParameterBindPoint(NULL),
        mSamplerParameterCount(0),
        mpSamplerParameterName(NULL),
        mpSamplerParameterBindPoint(NULL),
        mBufferCount(0),
        mBufferParameterCount(0),
        mpBufferParameterName(NULL),
        mpBufferParameterBindPoint(NULL),
        mUAVCount(0),
        mUAVParameterCount(0),
        mpUAVParameterName(NULL),
        mpUAVParameterBindPoint(NULL),
        mConstantBufferCount(0),
        mConstantBufferParameterCount(0),
        mpConstantBufferParameterName(NULL),
        mpConstantBufferParameterBindPoint(NULL),
        mpConstantBufferDesc(NULL),
        mpConstantBufferReflection(NULL),
        mBindViewMin(CPUT_MATERIAL_MAX_SRV_SLOTS),
        mBindViewMax(0),
        mBindUAVMin(CPUT_MATERIAL_MAX_UAV_SLOTS),
        mBindUAVMax(0),
        mBindConstantBufferMin(CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS),
        mBindConstantBufferMax(0)
    {
        memset( mppBindViews,           0, sizeof(mppBindViews) );
        memset( mpTexture,              0, sizeof(mpTexture) );
        memset( mpBuffer,               0, sizeof(mpBuffer) );
        memset( mppBindUAVs,            0, sizeof(mppBindUAVs) );
        memset( mpUAV,                  0, sizeof(mpUAV) );
        memset( mppBindConstantBuffers, 0, sizeof(mppBindConstantBuffers) );
        memset( mpConstantBuffer,       0, sizeof(mpConstantBuffer) );
    };
    ~CPUTShaderParameters();
    void CloneShaderParameters( CPUTShaderParameters *pShaderParameter );
};

static const int CPUT_NUM_SHADER_PARAMETER_LISTS = 7;
class CPUTMaterialDX11 : public CPUTMaterial
{
protected:
    static void *mpLastVertexShader;
    static void *mpLastPixelShader;
    static void *mpLastComputeShader;
    static void *mpLastGeometryShader;
    static void *mpLastHullShader;
    static void *mpLastDomainShader;

    static void *mpLastVertexShaderViews[CPUT_MATERIAL_MAX_TEXTURE_SLOTS];
    static void *mpLastPixelShaderViews[CPUT_MATERIAL_MAX_TEXTURE_SLOTS];
    static void *mpLastComputeShaderViews[CPUT_MATERIAL_MAX_TEXTURE_SLOTS];
    static void *mpLastGeometryShaderViews[CPUT_MATERIAL_MAX_TEXTURE_SLOTS];
    static void *mpLastHullShaderViews[CPUT_MATERIAL_MAX_TEXTURE_SLOTS];
    static void *mpLastDomainShaderViews[CPUT_MATERIAL_MAX_TEXTURE_SLOTS];

    static void *mpLastVertexShaderConstantBuffers[CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS];
    static void *mpLastPixelShaderConstantBuffers[CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS];
    static void *mpLastComputeShaderConstantBuffers[CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS];
    static void *mpLastGeometryShaderConstantBuffers[CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS];
    static void *mpLastHullShaderConstantBuffers[CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS];
    static void *mpLastDomainShaderConstantBuffers[CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS];

    static void *mpLastComputeShaderUAVs[CPUT_MATERIAL_MAX_UAV_SLOTS];

    static void *mpLastRenderStateBlock;

    CPUTPixelShaderDX11      *mpPixelShader;
    CPUTComputeShaderDX11    *mpComputeShader;
    CPUTVertexShaderDX11     *mpVertexShader;
    CPUTGeometryShaderDX11   *mpGeometryShader;
    CPUTHullShaderDX11       *mpHullShader;
    CPUTDomainShaderDX11     *mpDomainShader;
    int                       mRequiresPerModelPayload;

    cString                 **mpExternalName;
    float4                  **mpExternalValue;  // External value.  Allow multiple externals per submaterial
    int                     **mpExternalOffset; // External offset (i.e., byte-offset in constant buffer)
    int                     **mpExternalSize;   // External size
    int                      *mpExternalCount;

public:
    CPUTShaderParameters      mPixelShaderParameters;
    CPUTShaderParameters      mComputeShaderParameters;
    CPUTShaderParameters      mVertexShaderParameters;
    CPUTShaderParameters      mGeometryShaderParameters;
    CPUTShaderParameters      mHullShaderParameters;
    CPUTShaderParameters      mDomainShaderParameters;
    CPUTShaderParameters     *mpShaderParametersList[CPUT_NUM_SHADER_PARAMETER_LISTS]; // Constructor initializes this as a list of pointers to the above shader parameters.

    // Notes:  We support the idea of material externals.  "Externals" are variables that can be changed externally to the material.
    // We implement them in DX11 using constant buffers.  In contrast, we also support material-defines (#defines that affect the shaders at compile time)
    // Our material supports shaders from different files.  However, for simplicity, we support only one set of externals per material.
    // If your sample/application requires per-shader externals, then these members would likely move to CPUTShaderParameters
    // and, their usage mechanics would also need to be more complex.
    CPUTBufferDX11                       *mpExternalsConstantBuffer;
    bool                                  mExternalsConstantBufferDirty;
    D3D11_SHADER_BUFFER_DESC              mExternalsConstantBufferDesc;
    ID3D11ShaderReflectionConstantBuffer *mpExternalsConstantBufferReflection;

protected:
    ~CPUTMaterialDX11();  // Destructor is not public.  Must release instead of delete.

    void ReadShaderSamplersAndTextures(   ID3DBlob *pBlob, CPUTShaderParameters *pShaderParameter );
    void ReadExternalsFromConfigBlock(
        CPUTConfigBlock *pExternalsBlock,
        int              externalCount,
        cString         *pExternalName,
        float4          *pExternals, // Original list
        int             *pExternalOffset,
        int             *pExternalSize,
        int             *pFinaleExternalCount,
        cString        **pFinalExternalName,
        float4         **pFinalExternalValue, // List after combining originals and values from file
        int            **pFinalExternalOffset,
        int            **pFinalExternalSize
    );
    void ReadExternalsFromMasterConfigBlock(
        CPUTConfigBlock *pExternalsBlock,
        int             *pExternalCount,
        cString        **pExternalName,
        float4         **pExternalValue, // List after combining originals and values from file
        int            **pExternalOffset,
        int            **pFinalExternalSize
    );

    void BindTextures(        CPUTShaderParameters &params, const CPUTModel *pModel=NULL, int meshIndex=-1 );
    void BindBuffers(         CPUTShaderParameters &params, const CPUTModel *pModel=NULL, int meshIndex=-1 );
    void BindUAVs(            CPUTShaderParameters &params, const CPUTModel *pModel=NULL, int meshIndex=-1 );
    void BindConstantBuffers( CPUTShaderParameters &params, const CPUTModel *pModel=NULL, int meshIndex=-1 );

public:
    CPUTMaterialDX11();

    CPUTResult    LoadMaterial(
        const cString   &fileName,
        const CPUTModel *pModel=NULL,
              int        meshIndex=-1,
        const char     **pShaderMacros=NULL,
              int        systemMaterialCount=0,
              cString   *pSystemMaterialNames=NULL,
              int        externalCount=0,
              cString   *pExternalName=NULL,
              float4    *pExternals=NULL,
              int       *pExternalOffset=NULL,
              int       *pExternalSize=NULL
    );
    void          ReleaseTexturesAndBuffers();
    void          RebindTexturesAndBuffers();
    CPUTVertexShaderDX11   *GetVertexShader()   { return mpVertexShader; }
    CPUTPixelShaderDX11    *GetPixelShader()    { return mpPixelShader; }
    CPUTGeometryShaderDX11 *GetGeometryShader() { return mpGeometryShader; }
    CPUTComputeShaderDX11  *GetComputeShader()  { return mpComputeShader; }
    CPUTDomainShaderDX11   *GetDomainShader()   { return mpDomainShader; }
    CPUTHullShaderDX11     *GetHullShader()     { return mpHullShader; }

    void SetRenderStates( CPUTRenderParameters &renderParams );
    bool MaterialRequiresPerModelPayload();
    CPUTMaterial *CloneMaterial( const cString &absolutePathAndFilename, const CPUTModel *pModel=NULL, int meshIndex=-1 );
    static void ResetStateTracking()
    {
        mpLastVertexShader     = (void*)-1;
        mpLastPixelShader      = (void*)-1;
        mpLastComputeShader    = (void*)-1;
        mpLastGeometryShader   = (void*)-1;
        mpLastHullShader       = (void*)-1;
        mpLastDomainShader     = (void*)-1;
        mpLastRenderStateBlock = (void*)-1;
        memset( mpLastVertexShaderViews,             -1, sizeof(mpLastVertexShaderViews) );
        memset( mpLastPixelShaderViews,              -1, sizeof(mpLastPixelShaderViews) );
        memset( mpLastComputeShaderViews,            -1, sizeof(mpLastComputeShaderViews) );
        memset( mpLastGeometryShaderViews,           -1, sizeof(mpLastGeometryShaderViews) );
        memset( mpLastHullShaderViews,               -1, sizeof(mpLastHullShaderViews) );
        memset( mpLastDomainShaderViews,             -1, sizeof(mpLastDomainShaderViews) );
        memset( mpLastVertexShaderConstantBuffers,   -1, sizeof(mpLastVertexShaderConstantBuffers) );
        memset( mpLastPixelShaderConstantBuffers,    -1, sizeof(mpLastPixelShaderConstantBuffers) );
        memset( mpLastComputeShaderConstantBuffers,  -1, sizeof(mpLastComputeShaderConstantBuffers) );
        memset( mpLastGeometryShaderConstantBuffers, -1, sizeof(mpLastGeometryShaderConstantBuffers) );
        memset( mpLastHullShaderConstantBuffers,     -1, sizeof(mpLastHullShaderConstantBuffers) );
        memset( mpLastDomainShaderConstantBuffers,   -1, sizeof(mpLastDomainShaderConstantBuffers) );
        memset( mpLastComputeShaderUAVs,             -1, sizeof(mpLastComputeShaderUAVs) );
    }
    int GetExternalOffset( cString name );
    int GetExternalSize( cString name );
};

#endif // #ifndef __CPUTMATERIALDX11_H__
