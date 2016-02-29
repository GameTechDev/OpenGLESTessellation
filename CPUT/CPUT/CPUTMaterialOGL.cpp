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

#include "CPUTMaterialOGL.h"
#include "CPUT_OGL.h"
#include "CPUTRenderStateBlockOGL.h"
//#include "CPUTBufferOGL.h"
#include "CPUTShaderOGL.h"
#include "CPUTTextureOGL.h"

CPUTConfigBlock CPUTMaterialEffect::mGlobalProperties;
void *CPUTMaterialOGL::mpLastRenderStateBlock  = (void*)-1;

//-----------------------------------------------------------------------------
CPUTShaderParameters::~CPUTShaderParameters()
{
    for(int ii=0; ii<CPUT_MATERIAL_MAX_TEXTURE_SLOTS; ii++)
    {
        SAFE_RELEASE(mpTexture[ii]);
    }
    for(int ii=0; ii<CPUT_MATERIAL_MAX_BUFFER_SLOTS; ii++)
    {
        SAFE_RELEASE(mpBuffer[ii]);
    }
    for(int ii=0; ii<CPUT_MATERIAL_MAX_UAV_SLOTS; ii++)
    {
        SAFE_RELEASE(mpUAV[ii]);
    }
    for(int ii=0; ii<CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS; ii++)
    {
        SAFE_RELEASE(mpConstantBuffer[ii]);
    }
    SAFE_DELETE_ARRAY(mpSamplerParameterName);
    SAFE_DELETE_ARRAY(mpSamplerParameterBindPoint);
    SAFE_DELETE_ARRAY(mpBufferParameterName);
    SAFE_DELETE_ARRAY(mpBufferParameterBindPoint);
    //SAFE_DELETE_ARRAY(mpUAVParameterName);
    //SAFE_DELETE_ARRAY(mpUAVParameterBindPoint);
}

CPUTMaterialOGL::CPUTMaterialOGL() :
    mpVertexShader(NULL),
    mpFragmentShader(NULL),
    mpControlShader(NULL),
    mpEvaluationShader(NULL),
    mpGeometryShader(NULL), 
    mShaderProgram(0xFFFFFFFF),    // this value should always error when this shader is used
    mRequiresPerModelPayload(-1)
{
    memset(mSamplerIDs, 0, sizeof(mSamplerIDs));
    
    // TODO: Is there a better/safer way to initialize this list?
    mpShaderParametersList[0] =  &mPixelShaderParameters,
    mpShaderParametersList[1] =  &mComputeShaderParameters,
    mpShaderParametersList[2] =  &mVertexShaderParameters,
    mpShaderParametersList[3] =  &mGeometryShaderParameters,
    mpShaderParametersList[4] =  &mControlShaderParameters,
    mpShaderParametersList[5] =  &mEvaluationShaderParameters,
    mpShaderParametersList[6] =  NULL;
}

// Destructor
//-----------------------------------------------------------------------------
CPUTMaterialOGL::~CPUTMaterialOGL()
{
    // release any shaders
    SAFE_RELEASE(mpFragmentShader);
    //SAFE_RELEASE(mpComputeShader);
    SAFE_RELEASE(mpVertexShader);
    SAFE_RELEASE(mpGeometryShader);
    SAFE_RELEASE(mpControlShader);
    SAFE_RELEASE(mpEvaluationShader);
    SAFE_RELEASE(mpRenderStateBlock);

}

//-----------------------------------------------------------------------------
void CPUTMaterialOGL::SetRenderStates(CPUTRenderParameters &renderParams)
{
//    ID3D11DeviceContext *pContext = ((CPUTRenderParametersDX*)&renderParams)->mpContext;

    GL_CHECK(glUseProgram(mShaderProgram));

    if( mVertexShaderParameters.mTextureCount ) {
        for( unsigned int ii=0; ii < mVertexShaderParameters.mTextureCount; ii++ )
        {
            GLint bindPoint = mVertexShaderParameters.mpTextureParameterBindPoints[ii];
            GLint location = mVertexShaderParameters.mpTextureParameterLocations[ii];
            CPUTTextureOGL *pTex = (CPUTTextureOGL *)mVertexShaderParameters.mpTexture[ii];
            GL_CHECK(glActiveTexture(GL_TEXTURE0 + bindPoint));
            GL_CHECK(glBindTexture(GL_TEXTURE_2D, pTex->mTextureID));
            glUniform1i(location, bindPoint); // set the image unit to the bindpoint I think those are unique
            
#ifndef CPUT_FOR_OGLES2 
            //
            // Samplers are given in the renderstate but we need to always specify one as they can be different for each texture.
            // The renderstate won't necessarily change since it is the same material.
            // 
            GL_CHECK(ES3_COMPAT(glBindSampler(bindPoint, mSamplerIDs[ii]))); 
            // why is the texture unit here not GL_TEXTURE0 + bindpoint?
            // because uint v. enum in function signatures. more discussion in OpenGL red book Chapter 6 in Sampler Objects
            // glBindSampler(GLuint unit, GLuint sampler)
            // glBindTexture(GLActiveTexture(GLenum texture)
#else
#warning "Need to do something with samplers here"
#endif
        }
    }
    
#ifndef CPUT_FOR_OGLES2
    if ( mVertexShaderParameters.mConstantBufferCount ) {
        for (unsigned int ii=0; ii < mVertexShaderParameters.mConstantBufferCount; ii++ )
        {
            GLint bindPoint = mVertexShaderParameters.mConstantBufferBindPoints[ii];
	        GL_CHECK(ES3_COMPAT(glBindBufferBase(GL_UNIFORM_BUFFER, bindPoint, ((CPUTBufferOGL*)mVertexShaderParameters.mpConstantBuffer[ii])->GetBufferID())));
        }
    }
#else
#warning "Need to do something with uniform blocks here"
#endif
#ifdef CPUT_SUPPORT_IMAGE_STORE
    if( mVertexShaderParameters.mUAVCount)
        for(unsigned int ii=0; ii < mVertexShaderParameters.mUAVCount; ii++)
        {
            CPUTTextureOGL *pTex = (CPUTTextureOGL *)mVertexShaderParameters.mpUAV[ii];
            GLint mode = mVertexShaderParameters.mpUAVMode[ii];
            GL_CHECK(glBindImageTexture(0, pTex->GetTexture(), 0, GL_FALSE, 0, mode, GL_RGBA8));
        }
#endif

    // Set the render state block if it changed
    if( mpLastRenderStateBlock != mpRenderStateBlock )
    {
        mpLastRenderStateBlock = mpRenderStateBlock;
        if( mpRenderStateBlock )
        {
            // We know we have a OGL class.  Does this correctly bypass the virtual?
            // Should we move it to the OGL class.
            ((CPUTRenderStateBlockOGL*)mpRenderStateBlock)->SetRenderStates(renderParams);
        }
        else
        {
            CPUTRenderStateBlock::GetDefaultRenderStateBlock()->SetRenderStates(renderParams);
        }
    }
}

//-----------------------------------------------------------------------------
void ReadMacrosFromConfigBlock(
    CPUTConfigBlock    *pMacrosBlock,
    CPUT_SHADER_MACRO  *pShaderMacros,
    CPUT_SHADER_MACRO **pFinalShaderMacros
){
    int numUserSpecifiedMacros = pMacrosBlock->ValueCount();

    // Count the number of macros passed in
    CPUT_SHADER_MACRO *pMacro = (CPUT_SHADER_MACRO*)pShaderMacros;
    int numPassedInMacros = 0;
    if( pMacro )
    {
        while( pMacro->Name )
        {
            ++numPassedInMacros;
            ++pMacro;
        }
    }

    // Allocate an array of macros large enough to contain the passed-in macros plus those specified in the .mtl file.
    *pFinalShaderMacros = new CPUT_SHADER_MACRO[numUserSpecifiedMacros + numPassedInMacros + 1];

    // Copy the passed-in macro pointers to the final array
    int jj;
    for( jj=0; jj<numPassedInMacros; jj++ )
    {
        (*pFinalShaderMacros)[jj] = *(CPUT_SHADER_MACRO*)&pShaderMacros[jj];
    }

    // Create a D3D_SHADER_MACRO for each of the macros specified in the .mtl file.
    // And, add their pointers to the final array.
    for( int kk=0; kk<numUserSpecifiedMacros; kk++, jj++ )
    {
        CPUTConfigEntry *pValue = pMacrosBlock->GetValue(kk);
        (*pFinalShaderMacros)[jj].Name       = ws2s(pValue->NameAsString());
        (*pFinalShaderMacros)[jj].Definition = ws2s(pValue->ValueAsString());
    }
    (*pFinalShaderMacros)[jj].Name = NULL;
    (*pFinalShaderMacros)[jj].Definition = NULL;
}


CPUTResult CPUTMaterialOGL::LoadMaterial(
    const cString   &fileName,
    const CPUTModel *pModel,
          int        meshIndex,
    const char     **pShaderMacros,
          int        systemMaterialCount,
          cString   *pSystemMaterialNames,
          int        externalCount,
          cString   *pExternalName,
          float4    *pExternals,
          int       *pExternalOffset,
          int       *pExternalSize
){
    CPUTResult result = CPUT_SUCCESS;

    mMaterialName = fileName;
    mMaterialNameHash = CPUTComputeHash( mMaterialName );

    // Open/parse the file
    CPUTConfigFile file;
    result = file.LoadFile(fileName);
    if(CPUTFAILED(result))
    {
        return result;
    }

    // Make a local copy of all the parameters
    CPUTConfigBlock *pBlock = file.GetBlock(0);
    ASSERT( pBlock, _L("Error getting parameter block") );
    if( !pBlock )
    {
        return CPUT_ERROR_PARAMETER_BLOCK_NOT_FOUND;
    }
    mConfigBlock = *pBlock;

    // get necessary device and AssetLibrary pointers
    //ID3D11Device *pD3dDevice = CPUT_DX11::GetDevice();
    CPUTAssetLibraryOGL *pAssetLibrary = (CPUTAssetLibraryOGL*)CPUTAssetLibrary::GetAssetLibrary();

    // TODO:  The following code is very repetitive.  Consider generalizing so we can call a function instead.
    // see if there are any pixel/vertex/geo shaders to load
    CPUTConfigEntry *pValue;
    CPUT_SHADER_MACRO *pFinalShaderMacros = NULL;

    mSubMaterialCount = 0;
    if( mConfigBlock.GetValueByName( _L("MultiMaterial") )->ValueAsBool() )
    {
        // Count materials;
        for(;;)
        {
            CPUTConfigEntry * pValue = mConfigBlock.GetValueByName( _L("Material") + itoc(mSubMaterialCount) );
            if( pValue->IsValid() )
            {
                ++mSubMaterialCount;
            } else
            {
                break;
            }
        }
        ASSERT(mSubMaterialCount != 0, _L("MultiMaterial specified, but no sub materials given.") );

        // Reserve space for "authored" materials plus system materials
        mpSubMaterialNames = new cString[mSubMaterialCount+systemMaterialCount];
        int ii;
        for( ii=0; ii<mSubMaterialCount; ii++ )
        {
            CPUTConfigEntry * pValue = mConfigBlock.GetValueByName( _L("Material") + itoc(ii) );
            mpSubMaterialNames[ii] = pValue->ValueAsString();
        }
        // The real material count includes the system material count
        mSubMaterialCount += systemMaterialCount;
        for( ii=0; ii<systemMaterialCount; ii++ )
        {
            // System materials "grow" from the end; the 1st system material is at the end of the list.
            mpSubMaterialNames[mSubMaterialCount-systemMaterialCount+ii] = pSystemMaterialNames[ii];
        }
        mpSubMaterials = new CPUTMaterial*[mSubMaterialCount+1];
        for( int ii=0; ii<mSubMaterialCount; ii++ )
        {
            // Read additional macros from .mtl file
            cString macroBlockName = _L("defines") + itoc(ii);
            CPUTConfigBlock *pMacrosBlock = file.GetBlockByName(macroBlockName);
            int numUserSpecifiedMacros = 0;
            if( pMacrosBlock )
            {
                // This material specifies macros/defines.  Allocate a list big enough to hold the "master" macros + those specified by the material.
                // Copy the master macros to the new list, and also read the material's macros into the list.
                ReadMacrosFromConfigBlock( pMacrosBlock, (CPUT_SHADER_MACRO*)pShaderMacros, &pFinalShaderMacros );
            } else
            {
                // The material doesn't specify any additional macros.  Just use the "master" list.
                pFinalShaderMacros = (CPUT_SHADER_MACRO*)pShaderMacros;
            }
            mpSubMaterials[ii] = pAssetLibrary->GetMaterial( mpSubMaterialNames[ii], false, pModel, meshIndex, pShaderMacros );
            ASSERT( !mpSubMaterials[ii]->IsMultiMaterial(), L"Multi-material cannot have a sub material that is also a multi-material (hierarchy not supported at the moment)" );
            // If we allocated pFinalShaderMacros, then delete them
            if( pFinalShaderMacros != (CPUT_SHADER_MACRO*)pShaderMacros )
            {
                for( CPUT_SHADER_MACRO *pCur = pFinalShaderMacros; NULL != pCur->Name; pCur++ )
                {
                    SAFE_DELETE(pCur->Name);
                    SAFE_DELETE(pCur->Definition);
                }
                SAFE_DELETE_ARRAY( pFinalShaderMacros );
            }
        }
        mpSubMaterials[mSubMaterialCount] = NULL;
    }
    else
    {
        mSubMaterialCount     = 1 + systemMaterialCount;
        mpSubMaterialNames    = new cString[mSubMaterialCount+1]; // +1 for NULL terminator
        mpSubMaterials        = new CPUTMaterial*[mSubMaterialCount+1];
        mpSubMaterialNames[0] = mMaterialName;
        mpSubMaterials[0]     = this;
        int ii;
        //fixme no system materials for OpenGL
        for( ii=0; ii<systemMaterialCount; ii++ )
        {
            mpSubMaterialNames[ii+1] = pSystemMaterialNames[ii];
            mpSubMaterials[ii+1]     = pAssetLibrary->GetMaterial( mpSubMaterialNames[ii+1], false, pModel, meshIndex, pShaderMacros );
        }
        mpSubMaterials[ii+1] = NULL;
        // Read additional macros from .mtl file
        cString macroBlockName = _L("defines");
        CPUTConfigBlock *pMacrosBlock = file.GetBlockByName(macroBlockName);
        int numUserSpecifiedMacros = 0;
        if( pMacrosBlock )
        {
            // This material specifies macros/defines.  Allocate a list big enough to hold the "master" macros + those specified by the material.
            // Copy the master macros to the new list, and also read the material's macros into the list.
            ReadMacrosFromConfigBlock( pMacrosBlock, (CPUT_SHADER_MACRO*)pShaderMacros, &pFinalShaderMacros );
        } else
        {
            // The material doesn't specify any additional macros.  Just use the "master" list.
            pFinalShaderMacros = (CPUT_SHADER_MACRO*)pShaderMacros;
        }
    }

    {
        CPUTConfigEntry *pEntryPointName, *pProfileName;
        int numFiles = 0;
        cString pBase = _L("VertexShaderFileOGL_");
        cString pName = pBase + to_cString(numFiles+1);
        std::vector<cString> filenames;
        while (mConfigBlock.GetValueByName(pName)->IsValid())
        {
            filenames.push_back(mConfigBlock.GetValueByName(pName)->ValueAsString());
            numFiles++;
            pName = pBase + to_cString(numFiles+1);
        }
        if(numFiles > 0)
        {
            pEntryPointName = mConfigBlock.GetValueByName(_L("VertexShaderMain"));
            pProfileName    = mConfigBlock.GetValueByName(_L("VertexShaderProfile"));
            pAssetLibrary->GetVertexShader(
                filenames,
                /*pD3dDevice,*/
                _L("VertexShaderMain"),
                pProfileName->ValueAsString(),
                &mpVertexShader,
                false,
                pFinalShaderMacros
            );
        }
		else
		{
			ASSERT( 0, _L("No vertex shader in material") );
		}
    }

    // load and store the pixel shader if it was specified
    {
        int numFiles = 0;
        cString pBase = _L("FragmentShaderFileOGL_");
        cString pName = pBase + to_cString(numFiles+1);
        std::vector<cString> filenames;
        while (mConfigBlock.GetValueByName(pName)->IsValid())
        {
            filenames.push_back(mConfigBlock.GetValueByName(pName)->ValueAsString());
            numFiles++;
            pName = pBase + to_cString(numFiles+1);
        }
        if(numFiles > 0) 
        {
            pAssetLibrary->GetPixelShader(
                filenames,
                /* pD3dDevice,*/
                _L("FragmentShaderMain"), //mConfigBlock.GetValueByName(_L("FragmentShaderMain"))->ValueAsString(),
                mConfigBlock.GetValueByName(_L("FragmentShaderProfile"))->ValueAsString(),
                &mpFragmentShader,
                false,
                pFinalShaderMacros
            );
        }
    }

/*
    // load and store the compute shader if it was specified
    pValue = mConfigBlock.GetValueByName(_L("ComputeShaderFile"));
    if( pValue->IsValid() )
    {
        pEntryPointName = mConfigBlock.GetValueByName(_L("ComputeShaderMain"));
        pProfileName = mConfigBlock.GetValueByName(_L("ComputeShaderProfile"));
        pAssetLibrary->GetComputeShader(pValue->ValueAsString(), pD3dDevice, pEntryPointName->ValueAsString(), pProfileName->ValueAsString(), &mpComputeShader);
        ReadShaderSamplersAndTextures( mpComputeShader->GetBlob(), &mComputeShaderParameters );
    }

    // load and store the geometry shader if it was specified
    pValue = mConfigBlock.GetValueByName(_L("GeometryShaderFile"));
    if( pValue->IsValid() )
    {
        pEntryPointName = mConfigBlock.GetValueByName(_L("GeometryShaderMain"));
        pProfileName = mConfigBlock.GetValueByName(_L("GeometryShaderProfile"));
        pAssetLibrary->GetGeometryShader(pValue->ValueAsString(), pD3dDevice, pEntryPointName->ValueAsString(), pProfileName->ValueAsString(), &mpGeometryShader);
        ReadShaderSamplersAndTextures( mpGeometryShader->GetBlob(), &mGeometryShaderParameters );
    }
	*/
#ifdef CPUT_SUPPORT_TESSELLATION
    {
        int numFiles = 0;
        cString pBase = _L("ControlShaderFileOGL_");
        cString pName = pBase + to_cString(numFiles+1);
        std::vector<cString> filenames;
        while (mConfigBlock.GetValueByName(pName)->IsValid())
        {
            filenames.push_back(mConfigBlock.GetValueByName(pName)->ValueAsString());
            numFiles++;
            pName = pBase + to_cString(numFiles+1);
        }
        if(numFiles > 0) 
        {
			pAssetLibrary->GetHullShader(
                filenames,
                /* pD3dDevice,*/
                _L("ControlShaderMain"), 
                _L(""),
                &mpControlShader,
                false,
                pFinalShaderMacros
            );
        }
    }
    {
        int numFiles = 0;
        cString pBase = _L("EvaluationShaderFileOGL_");
        cString pName = pBase + to_cString(numFiles+1);
        std::vector<cString> filenames;
        while (mConfigBlock.GetValueByName(pName)->IsValid())
        {
            filenames.push_back(mConfigBlock.GetValueByName(pName)->ValueAsString());
            numFiles++;
            pName = pBase + to_cString(numFiles+1);
        }
        if(numFiles > 0) 
        {
			pAssetLibrary->GetDomainShader(
                filenames,
                /* pD3dDevice,*/
                _L("EvaluationShaderMain"), 
                _L(""),
                &mpEvaluationShader,
                false,
                pFinalShaderMacros
            );
        }
    }
#endif
    {
        int numFiles = 0;
        cString pBase = _L("GeometryShaderFileOGL_");
        cString pName = pBase + to_cString(numFiles+1);
        std::vector<cString> filenames;
        while (mConfigBlock.GetValueByName(pName)->IsValid())
        {
            filenames.push_back(mConfigBlock.GetValueByName(pName)->ValueAsString());
            numFiles++;
            pName = pBase + to_cString(numFiles+1);
        }
        if(numFiles > 0) 
        {
			pAssetLibrary->GetGeometryShader(
                filenames,
                /* pD3dDevice,*/
                _L("GeometryShaderMain"), 
                _L(""),
                &mpGeometryShader,
                false,
                pFinalShaderMacros
            );
        }
    }
	/*
	// load and store the hull shader if it was specified
    pValue = mConfigBlock.GetValueByName(_L("HullShaderFile"));
    if( pValue->IsValid() )
    {
        pEntryPointName = mConfigBlock.GetValueByName(_L("HullShaderMain"));
        pProfileName = mConfigBlock.GetValueByName(_L("HullShaderProfile"));
        pAssetLibrary->GetHullShader(pValue->ValueAsString(), pD3dDevice, pEntryPointName->ValueAsString(), pProfileName->ValueAsString(), &mpHullShader);
        ReadShaderSamplersAndTextures( mpHullShader->GetBlob(), &mHullShaderParameters );
    }

    // load and store the domain shader if it was specified
    pValue = mConfigBlock.GetValueByName(_L("DomainShaderFile"));
    if( pValue->IsValid() )
    {
        pEntryPointName = mConfigBlock.GetValueByName(_L("DomainShaderMain"));
        pProfileName = mConfigBlock.GetValueByName(_L("DomainShaderProfile"));
        pAssetLibrary->GetDomainShader(pValue->ValueAsString(), pD3dDevice, pEntryPointName->ValueAsString(), pProfileName->ValueAsString(), &mpDomainShader);
        ReadShaderSamplersAndTextures( mpDomainShader->GetBlob(), &mDomainShaderParameters );
    }
	*/
    // load and store the render state file if it was specified
    pValue = mConfigBlock.GetValueByName(_L("RenderStateFile"));
    if( pValue->IsValid() )
    {
        mpRenderStateBlock = pAssetLibrary->GetRenderStateBlock(pValue->ValueAsString());
    }


    int IsLinked;
    char *shaderProgramInfoLog;
    int maxLength;
    
     mShaderProgram = glCreateProgram();
	DEBUG_PRINT(_L("Created Program: %d"), mShaderProgram);
    // Attach our shaders to our program
    if (mpVertexShader) {
        GL_CHECK(glAttachShader(mShaderProgram, mpVertexShader->GetShaderID()));
    }
    if (mpFragmentShader) {
        GL_CHECK(glAttachShader(mShaderProgram, mpFragmentShader->GetShaderID()));
    }
    if (mpControlShader) {
        GL_CHECK(glAttachShader(mShaderProgram, mpControlShader->GetShaderID()));
    }
    if (mpEvaluationShader) {
        GL_CHECK(glAttachShader(mShaderProgram, mpEvaluationShader->GetShaderID()));
    }
	if (mpGeometryShader) {
		GL_CHECK(glAttachShader(mShaderProgram, mpGeometryShader->GetShaderID()));
	}
    /*
    GL_CHECK(glBindAttribLocation(mShaderProgram, 0, "in_Position"));
    GL_CHECK(glBindAttribLocation(mShaderProgram, 1, "inNormal"));
    GL_CHECK(glBindAttribLocation(mShaderProgram, 2, "inBinormal"));
    GL_CHECK(glBindAttribLocation(mShaderProgram, 3, "inTangent"));
    GL_CHECK(glBindAttribLocation(mShaderProgram, 4, "inTex"));
      */          
    
    // Link our program
    // At this stage, the vertex and fragment programs are inspected, optimized and a binary code is generated for the shader.
    // The binary code is uploaded to the GPU, if there is no error.
    GL_CHECK(glLinkProgram(mShaderProgram));
 
    // Again, we must check and make sure that it linked. If it fails, it would mean either there is a mismatch between the vertex
    // and fragment shaders. It might be that you have surpassed your GPU's abilities. Perhaps too many ALU operations or
    // too many texel fetch instructions or too many interpolators or dynamic loops.
 
    GL_CHECK(glGetProgramiv(mShaderProgram, GL_LINK_STATUS, (int *)&IsLinked));
    if(IsLinked == false)
    {
        // Noticed that glGetProgramiv is used to get the length for a shader program, not glGetShaderiv.
        glGetProgramiv(mShaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
 
        // The maxLength includes the NULL character
        shaderProgramInfoLog = (char *)malloc(maxLength);
 
        // Notice that glGetProgramInfoLog, not glGetShaderInfoLog.
        glGetProgramInfoLog(mShaderProgram, maxLength, &maxLength, shaderProgramInfoLog);
 
       // Handle the error in an appropriate way such as displaying a message or writing to a log file.
       // In this simple program, we'll just leave
       DEBUG_PRINT("Failed to link shader program:\n%s\n", shaderProgramInfoLog);
	   ASSERT(false, _L("glLinkProgramFailed"));
        free(shaderProgramInfoLog);
    }
    DEBUG_PRINT(_L("Linked Program %d"), mShaderProgram);
    // Shader must be successfully linked before we can query uniform locations
    ReadShaderSamplersAndTextures( mShaderProgram, &mVertexShaderParameters );
    glUseProgram(0);
// For each of the shader stages, bind shaders and buffers
//    for( CPUTShaderParameters **pCur = mpShaderParametersList; *pCur; pCur++ ) // Bind textures and buffersfor each shader stage
    {
        BindTextures(        mVertexShaderParameters, pModel, meshIndex );
        //BindTextures(        **pCur, pModel, meshIndex );
        //BindBuffers(         **pCur, pModel, meshIndex );
        BindUAVs(            mVertexShaderParameters, pModel, meshIndex );
        BindConstantBuffers( mVertexShaderParameters, pModel, meshIndex );
    }
    DEBUG_PRINT(_L("Exit LoadMaterial"));
    return result;
}

// https://sites.google.com/site/opengltutorialsbyaks/introduction-to-opengl-4-1---tutorial-05
void DebugOutputToFile2(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, const char* message)
{
#ifndef CPUT_FOR_OGLES
       {
             char debSource[16], debType[20], debSev[5];
             
             if(source == GL_DEBUG_SOURCE_API_ARB)
                    strcpy(debSource, "OpenGL");
             else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
                    strcpy(debSource, "Windows");
             else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
                    strcpy(debSource, "Shader Compiler");
             else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
                    strcpy(debSource, "Third Party");
             else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)
                    strcpy(debSource, "Application");
             else if(source == GL_DEBUG_SOURCE_OTHER_ARB)
                    strcpy(debSource, "Other");
             if(type == GL_DEBUG_TYPE_ERROR_ARB)
                    strcpy(debType, "Error");
             else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)
                    strcpy(debType, "Deprecated behavior");
             else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)
                    strcpy(debType, "Undefined behavior");
             else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)
                    strcpy(debType, "Portability");
             else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
                    strcpy(debType, "Performance");
             else if(type == GL_DEBUG_TYPE_OTHER_ARB)
                    strcpy(debType, "Other");
             if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)
                    strcpy(debSev, "High");
             else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
                    strcpy(debSev, "Medium");
             else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
                    strcpy(debSev, "Low");

             printf("Source:%s\tType:%s\tID:%d\tSeverity:%s\tMessage:%s\n", debSource, debType, id, debSev, message);
       }
#endif
}

void CheckDebugLog2()
{
#ifndef CPUT_FOR_OGLES
       unsigned int count = 10; // max. num. of messages that will be read from the log
       int bufsize = 2048;

       unsigned int* sources      = new unsigned int[count];
       unsigned int* types        = new unsigned int[count];
       unsigned int* ids   = new unsigned int[count];
       unsigned int* severities = new unsigned int[count];
       int* lengths = new int[count];
       char* messageLog = new char[bufsize];

       unsigned int retVal = glGetDebugMessageLogARB(count, bufsize, sources, types, ids, severities, lengths, messageLog);
       if(retVal > 0)
       {
             unsigned int pos = 0;
             for(unsigned int i=0; i<retVal; i++)
             {
                    DebugOutputToFile2(sources[i], types[i], ids[i], severities[i], &messageLog[pos]);
                    pos += lengths[i];
              }
       }
       delete [] sources;
       delete [] types;
       delete [] ids;
       delete [] severities;
       delete [] lengths;
       delete [] messageLog;
#endif
}

//-----------------------------------------------------------------------------
void CPUTMaterialOGL::ReadShaderSamplersAndTextures( GLuint shaderProgram, CPUTShaderParameters *pShaderParameter )
{
    GLint numActiveUniforms;
    GLint activeUniformMaxLength;
    GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &numActiveUniforms));
    GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &activeUniformMaxLength));
    
#ifndef CPUT_FOR_OGLES2
    GLint numActiveUniformBlocks;
    GLint activeUniformBlockMaxLength = 50;
    GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_BLOCKS, &numActiveUniformBlocks));
#else
#warning "Need to do something with uniform blocks here"
#endif
	//
	// #### This parameter is currently unsupported by Intel OGL drivers.
	//
  //  GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &activeUniformBlockMaxLength));
    
    GLchar* uniformVariableName = new GLchar[activeUniformMaxLength];
    GLenum  dataType;
    GLint   size;
    for (int i = 0; i < numActiveUniforms; i++) {
        GL_CHECK(glGetActiveUniform(shaderProgram, i, activeUniformMaxLength, NULL, &size, &dataType, uniformVariableName));
        switch(dataType) {
#ifndef CPUT_FOR_OGLES
            case GL_SAMPLER_1D:
#endif
        case GL_SAMPLER_2D:
#ifndef CPUT_FOR_OGLES2
        case GL_SAMPLER_3D:
#endif
        case GL_SAMPLER_2D_SHADOW:
                pShaderParameter->mpTextureParameterNames.push_back(uniformVariableName);
                pShaderParameter->mpTextureParameterLocations.push_back(glGetUniformLocation(shaderProgram, uniformVariableName));
                pShaderParameter->mTextureParameterCount++;
                break;
#ifdef CPUT_SUPPORT_IMAGE_STORE
        case GL_IMAGE_2D:
            pShaderParameter->mpUAVParameterNames.push_back(uniformVariableName);
            pShaderParameter->mpUAVParameterLocations.push_back(glGetUniformLocation(shaderProgram, uniformVariableName));
            pShaderParameter->mUAVParameterCount++;
            break;
#endif
            default:
                // unsupported uniform type
            break;
        }
    }
	delete uniformVariableName;

#ifndef CPUT_FOR_OGLES2
    GLchar* uniformBlockName = new GLchar[activeUniformBlockMaxLength];
    for (int i = 0; i < numActiveUniformBlocks; i++) 
    {
        GL_CHECK(ES3_COMPAT(glGetActiveUniformBlockName(shaderProgram, i, activeUniformBlockMaxLength, NULL, uniformBlockName)));
        pShaderParameter->mConstantBufferParameterNames.push_back(uniformBlockName);
        pShaderParameter->mConstantBufferBindPoints.push_back(ES3_COMPAT(glGetUniformBlockIndex(shaderProgram, uniformBlockName)));
        pShaderParameter->mConstantBufferParameterCount++;
    }
    delete uniformBlockName;
#else
#warning "Need to do something with uniform blocks here"
#endif
/*    
    glUseProgram(0);
    
    GLchar activeUniformNames[10][100];
    GLchar activeUniformBlockNames[10][100];
    GLchar activeAttributeNames[10][100];
    GLint numActiveAttributes, activeAttributeMaxLength;
    GLint numActiveUniformBlocks, activeUniformBlockMaxLength;
    GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &numActiveUniforms));
    GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &activeUniformMaxLength));
    GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &numActiveAttributes));
    GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &activeAttributeMaxLength));
    GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_BLOCKS, &numActiveUniformBlocks));
    GL_CHECK(glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &activeUniformBlockMaxLength));
    
    GLsizei numBytesWritten;
    
    
     for (int i = 0; i < numActiveUniforms; i++) {
        GL_CHECK(glGetActiveUniform(shaderProgram, i, 100, &numBytesWritten, &size, &dataType, activeUniformNames[i]));
    }
    
    for (int i = 0; i < numActiveAttributes; i++) {
        GL_CHECK(glGetActiveAttrib(shaderProgram, i, 100, &numBytesWritten, &size, &dataType, activeAttributeNames[i]));
    }
    
    for (int i = 0; i < numActiveUniformBlocks; i++) {
 //       GL_CHECK(glGetActiveUniformBlock(shaderProgram, i, ));
    }

    CheckDebugLog2();
    
    GLuint g_gaussSampler;
    glGenSamplers(1, &g_gaussSampler);
    glSamplerParameteri(g_gaussSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glSamplerParameteri(g_gaussSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(g_gaussSampler, GL_TEXTURE_WRAP_S, GL_REPEAT);

    GLuint TextureName = gli::createTexture2D("/home/q-dawg/Develop/projects/Framework/CPUT_Linux/SampleStartCPUT/Media/Teapot/Texture/checker_20x.dds");

    
    glBindTexture(GL_TEXTURE_2D, TextureName);
    GL_CHECK(glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ));
    GL_CHECK(glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ));
    GL_CHECK(glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ));
    GL_CHECK(glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ));
    GL_CHECK(glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT ));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    
    GLint diffuseTextureLocation = glGetUniformLocation(shaderProgram, "diffuseTex");
    CheckDebugLog2();
    glUseProgram(mShaderProgram);
    glUniform1i(diffuseTextureLocation, 0);
    CheckDebugLog2();
    GL_CHECK(glActiveTexture(GL_TEXTURE0 + 0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, TextureName));
    glUseProgram(0);
*/    
/*
    ID3D11ShaderReflection *pReflector = NULL; 
    D3D11_SHADER_INPUT_BIND_DESC desc;

    D3DReflect( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);
    // Walk through the shader input bind descriptors.  Find the samplers and textures.
    int ii=0;
    HRESULT hr = pReflector->GetResourceBindingDesc( ii++, &desc );
    while( SUCCEEDED(hr) )
    {
        switch( desc.Type )
        {
        case D3D_SIT_TEXTURE:
            pShaderParameter->mTextureParameterCount++;
            break;
        case D3D_SIT_SAMPLER:
            pShaderParameter->mSamplerParameterCount++;
            break;
        case D3D_SIT_CBUFFER:
            pShaderParameter->mConstantBufferParameterCount++;
            break;

        case D3D_SIT_TBUFFER:
        case D3D_SIT_STRUCTURED:
        case D3D_SIT_BYTEADDRESS:
            pShaderParameter->mBufferParameterCount++;
            break;

        case D3D_SIT_UAV_RWTYPED:
        case D3D_SIT_UAV_RWSTRUCTURED:
        case D3D_SIT_UAV_RWBYTEADDRESS:
        case D3D_SIT_UAV_APPEND_STRUCTURED:
        case D3D_SIT_UAV_CONSUME_STRUCTURED:
        case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
            pShaderParameter->mUAVParameterCount++;
            break;
        }
        hr = pReflector->GetResourceBindingDesc( ii++, &desc );
    }

    pShaderParameter->mpTextureParameterName              = new cString[pShaderParameter->mTextureParameterCount];
    pShaderParameter->mpTextureParameterBindPoint         = new UINT[   pShaderParameter->mTextureParameterCount];
    pShaderParameter->mpSamplerParameterName              = new cString[pShaderParameter->mSamplerParameterCount];
    pShaderParameter->mpSamplerParameterBindPoint         = new UINT[   pShaderParameter->mSamplerParameterCount];
    pShaderParameter->mpBufferParameterName               = new cString[pShaderParameter->mBufferParameterCount];
    pShaderParameter->mpBufferParameterBindPoint          = new UINT[   pShaderParameter->mBufferParameterCount];
    pShaderParameter->mpUAVParameterName                  = new cString[pShaderParameter->mUAVParameterCount];
    pShaderParameter->mpUAVParameterBindPoint             = new UINT[   pShaderParameter->mUAVParameterCount];
    pShaderParameter->mpConstantBufferParameterName       = new cString[pShaderParameter->mConstantBufferParameterCount];
    pShaderParameter->mpConstantBufferParameterBindPoint  = new UINT[   pShaderParameter->mConstantBufferParameterCount];
        
    // Start over.  This time, copy the names.
    ii=0;
    UINT textureIndex = 0;
    UINT samplerIndex = 0;
    UINT bufferIndex = 0;
    UINT uavIndex = 0;
    UINT constantBufferIndex = 0;
    hr = pReflector->GetResourceBindingDesc( ii++, &desc );

    while( SUCCEEDED(hr) )
    {
        switch( desc.Type )
        {
        case D3D_SIT_TEXTURE:
            pShaderParameter->mpTextureParameterName[textureIndex] = s2ws(desc.Name);
            pShaderParameter->mpTextureParameterBindPoint[textureIndex] = desc.BindPoint;
            textureIndex++;
            break;
        case D3D_SIT_SAMPLER:
            pShaderParameter->mpSamplerParameterName[samplerIndex] = s2ws(desc.Name);
            pShaderParameter->mpSamplerParameterBindPoint[samplerIndex] = desc.BindPoint;
            samplerIndex++;
            break;
        case D3D_SIT_CBUFFER:
            pShaderParameter->mpConstantBufferParameterName[constantBufferIndex] = s2ws(desc.Name);
            pShaderParameter->mpConstantBufferParameterBindPoint[constantBufferIndex] = desc.BindPoint;
            constantBufferIndex++;
            break;
        case D3D_SIT_TBUFFER:
        case D3D_SIT_STRUCTURED:
        case D3D_SIT_BYTEADDRESS:
            pShaderParameter->mpBufferParameterName[bufferIndex] = s2ws(desc.Name);
            pShaderParameter->mpBufferParameterBindPoint[bufferIndex] = desc.BindPoint;
            bufferIndex++;
            break;
        case D3D_SIT_UAV_RWTYPED:
        case D3D_SIT_UAV_RWSTRUCTURED:
        case D3D_SIT_UAV_RWBYTEADDRESS:
        case D3D_SIT_UAV_APPEND_STRUCTURED:
        case D3D_SIT_UAV_CONSUME_STRUCTURED:
        case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
            pShaderParameter->mpUAVParameterName[uavIndex] = s2ws(desc.Name);
            pShaderParameter->mpUAVParameterBindPoint[uavIndex] = desc.BindPoint;
            uavIndex++;
            break;
        }
        hr = pReflector->GetResourceBindingDesc( ii++, &desc );
    }
     */
}

void CPUTMaterialOGL::BindTextures( CPUTShaderParameters &params, const CPUTModel *pModel, int meshIndex )
{
    CPUTAssetLibraryOGL *pAssetLibrary = (CPUTAssetLibraryOGL*)CPUTAssetLibrary::GetAssetLibrary();

    for(params.mTextureCount=0; params.mTextureCount < params.mTextureParameterCount; params.mTextureCount++)
    {
        cString textureName;
        unsigned int textureCount = params.mTextureCount;

// Dirty fix
#ifndef CPUT_OS_WINDOWS
        cString tagName = params.mpTextureParameterNames[textureCount];
#else
        cString tagName = s2ws(params.mpTextureParameterNames[textureCount].c_str());
#endif

        CPUTConfigEntry *pValue = mConfigBlock.GetValueByName(tagName);
        if( !pValue->IsValid() )
        {
            // We didn't find our property in the file.  Is it in the global config block?
            pValue = mGlobalProperties.GetValueByName(tagName);
        }
        ASSERT( pValue->IsValid(), L"Can't find texture '" + tagName + L"'." ); //  TODO: fix message
        textureName = pValue->ValueAsString();
        // If the texture name not specified.  Load default.dds instead
        if( 0 == textureName.length() ) 
        { 
            textureName = _L("default.dds"); 
        }

        UINT bindPoint = params.mTextureCount;//params.mpTextureParameterBindPoints[textureCount];
        params.mpTextureParameterBindPoints.push_back(bindPoint);
//        UINT bindPoint = params.mpTextureParameterBindPoint[textureCount]; mpTextureParameterBindPoints
        ASSERT( bindPoint < CPUT_MATERIAL_MAX_TEXTURE_SLOTS, _L("Texture bind point out of range.") );

        params.mBindViewMin = std::min( params.mBindViewMin, bindPoint );
        params.mBindViewMax = std::max( params.mBindViewMax, bindPoint );

        if( textureName[0] == '@' )
        {
            // This is a per-mesh value.  Add to per-mesh list.
            textureName += ptoc(pModel) + itoc(meshIndex);
        } else if( textureName[0] == '#' )
        {
            // This is a per-mesh value.  Add to per-mesh list.
            textureName += ptoc(pModel);
        }

        // Get the sRGB flag (default to true)
//#ifndef CPUT_OS_WINDOWS
        cString SRGBName = tagName + _L("sRGB");
//#else
//        cString SRGBName = tagName + L"sRGB";
//#endif

        CPUTConfigEntry *pSRGBValue = mConfigBlock.GetValueByName(SRGBName);
        bool loadAsSRGB = pSRGBValue->IsValid() ?  loadAsSRGB = pSRGBValue->ValueAsBool() : true;

        if( !params.mpTexture[textureCount] )
        {
            params.mpTexture[textureCount] = pAssetLibrary->GetTexture( textureName, false, loadAsSRGB );
            ASSERT( params.mpTexture[textureCount], _L("Failed getting texture ") + textureName);
        }

        // The shader file (e.g. .fx) can specify the texture bind point (e.g., t0).  Those specifications 
        // might not be contiguous, and there might be gaps (bind points without assigned textures)
        // TODO: Warn about missing bind points?
//        params.mppBindViews[bindPoint] = ((CPUTTextureOGL*)mpTexture[textureCount])->GetShaderResourceView();
//        params.mppBindViews[bindPoint]->AddRef();

        //
        // Match up the texture name in any texture samplers given in the renderstate file. If there wasn't
        // one specified for a particular texture then it just uses the default sampler.
        //
        CPUTRenderStateOGL *pRenderState;
        pRenderState = ((CPUTRenderStateBlockOGL*)mpRenderStateBlock)->GetState();
        
        mSamplerIDs[textureCount] = pRenderState->DefaultSamplerID;

		if(textureCount<((CPUTRenderStateBlockOGL*)mpRenderStateBlock)->GetNumSamplers())
        {
            mSamplerIDs[textureCount] = pRenderState->SamplerIDs[textureCount];
        }

  
    }
}

void CPUTMaterialOGL::BindUAVs( CPUTShaderParameters &params, const CPUTModel *pModel, int meshIndex )
{
#ifdef CPUT_SUPPORT_IMAGE_STORE

    CPUTAssetLibraryOGL *pAssetLibrary = (CPUTAssetLibraryOGL*)CPUTAssetLibrary::GetAssetLibrary();

    for(params.mUAVCount=0; params.mUAVCount < params.mUAVParameterCount; params.mUAVCount++)
    {
        cString UAVName;
        unsigned int UAVCount = params.mUAVCount;

// Dirty fix
#ifndef CPUT_OS_WINDOWS
        cString tagName = params.mpUAVParameterNames[UAVCount];
#else
        cString tagName = s2ws(params.mpUAVParameterNames[UAVCount].c_str());
#endif

        CPUTConfigEntry *pValue = mConfigBlock.GetValueByName(tagName);
        if( !pValue->IsValid() )
        {
            // We didn't find our property in the file.  Is it in the global config block?
            pValue = mGlobalProperties.GetValueByName(tagName);
        }
        ASSERT( pValue->IsValid(), L"Can't find UAV '" + tagName + L"'." ); //  TODO: fix message
        UAVName = pValue->ValueAsString();
        // If the UAV name not specified.  Load default.dds instead
        if( 0 == UAVName.length() ) 
        { 
            UAVName = _L("default.dds"); 
        }

        UINT bindPoint = params.mUAVCount;//params.mpUAVParameterBindPoints[UAVCount];
        params.mpUAVParameterBindPoints.push_back(bindPoint);
//        UINT bindPoint = params.mpUAVParameterBindPoint[UAVCount]; mpUAVParameterBindPoints
        ASSERT( bindPoint < CPUT_MATERIAL_MAX_UAV_SLOTS, _L("UAV bind point out of range.") );

        params.mBindViewMin = std::min( params.mBindViewMin, bindPoint );
        params.mBindViewMax = std::max( params.mBindViewMax, bindPoint );

        if( UAVName[0] == '@' )
        {
            // This is a per-mesh value.  Add to per-mesh list.
            UAVName += ptoc(pModel) + itoc(meshIndex);
        } else if( UAVName[0] == '#' )
        {
            // This is a per-mesh value.  Add to per-mesh list.
            UAVName += ptoc(pModel);
        }

        // Get the sRGB flag (default to true)
//#ifndef CPUT_OS_WINDOWS
        cString SRGBName = tagName + _L("sRGB");
//#else
//        cString SRGBName = tagName + L"sRGB";
//#endif
        CPUTConfigEntry *pSRGBValue = mConfigBlock.GetValueByName(SRGBName);
        bool loadAsSRGB = pSRGBValue->IsValid() ?  loadAsSRGB = pSRGBValue->ValueAsBool() : true;

        if( !params.mpUAV[UAVCount] )
        {
            params.mpUAV[UAVCount] = pAssetLibrary->GetTexture( UAVName, false, loadAsSRGB );
            ASSERT( params.mpUAV[UAVCount], _L("Failed getting UAV ") + UAVName);
        }

        cString ReadName = tagName + _L("READ");
        CPUTConfigEntry *pRead = mConfigBlock.GetValueByName(ReadName);
        bool read = pRead->IsValid() ? pRead->ValueAsBool() : true;
        cString WriteName = tagName + _L("WRITE");
        CPUTConfigEntry *pWrite = mConfigBlock.GetValueByName(WriteName);
        bool write = pWrite->IsValid() ? pWrite  ->ValueAsBool() : true;
        if(write && read)
            params.mpUAVMode[UAVCount] = GL_READ_WRITE;
        else if(read)
            params.mpUAVMode[UAVCount] = GL_READ_ONLY;
        else
            params.mpUAVMode[UAVCount] = GL_WRITE_ONLY;

        // The shader file (e.g. .fx) can specify the UAV bind point (e.g., t0).  Those specifications 
        // might not be contiguous, and there might be gaps (bind points without assigned UAVs)
        // TODO: Warn about missing bind points?
//        params.mppBindViews[bindPoint] = ((CPUTTextureOGL*)mpTexture[textureCount])->GetShaderResourceView();
//        params.mppBindViews[bindPoint]->AddRef();

        //
        // Match up the UAV name in any UAV samplers given in the renderstate file. If there wasn't
        // one specified for a particular UAV then it just uses the default sampler.
        //
        CPUTRenderStateOGL *pRenderState;
        pRenderState = ((CPUTRenderStateBlockOGL*)mpRenderStateBlock)->GetState();
        
        mSamplerIDs[UAVCount] = pRenderState->DefaultSamplerID;
        for (int renderStateIDX = 0; renderStateIDX < NUM_SAMPLERS_PER_RENDERSTATE; renderStateIDX++) {
			if(renderStateIDX<((CPUTRenderStateBlockOGL*)mpRenderStateBlock)->GetNumSamplers())
            {
                mSamplerIDs[UAVCount] = pRenderState->SamplerIDs[renderStateIDX];
            }
        }
    }
#endif

}

//-----------------------------------------------------------------------------
void CPUTMaterialOGL::BindConstantBuffers( CPUTShaderParameters &params, const CPUTModel *pModel, int meshIndex )
{
    CPUTAssetLibraryOGL *pAssetLibrary = (CPUTAssetLibraryOGL*)CPUTAssetLibrary::GetAssetLibrary();
    
    for(params.mConstantBufferCount=0; params.mConstantBufferCount < params.mConstantBufferParameterCount; params.mConstantBufferCount++)
    {
        cString constantBufferName;
        UINT constantBufferCount = params.mConstantBufferCount;

// Dirty fix - you should work on std::string in all OS'es ! Why WSTRING ? Whyyyyyyy
#ifndef CPUT_OS_WINDOWS
        cString tagName = params.mConstantBufferParameterNames[constantBufferCount];
#else
        cString tagName = s2ws(params.mConstantBufferParameterNames[constantBufferCount].c_str());
#endif


        CPUTConfigEntry *pValue = mConfigBlock.GetValueByName(tagName);
        if( !pValue->IsValid() )
        {
            // We didn't find our property in the file.  Is it in the global config block?
            pValue = mGlobalProperties.GetValueByName(tagName);
        }
		ASSERT( pValue->IsValid(), L"Can't find constant buffer '" + tagName + L"'." ); //  TODO: fix message
        
        constantBufferName = pValue->ValueAsString();
     
        UINT bindPoint = params.mConstantBufferBindPoints[constantBufferCount];
        ASSERT( bindPoint < CPUT_MATERIAL_MAX_CONSTANT_BUFFER_SLOTS, _L("Constant buffer bind point out of range.") );

        params.mBindConstantBufferMin = std::min( params.mBindConstantBufferMin, bindPoint );
        params.mBindConstantBufferMax = std::max( params.mBindConstantBufferMax, bindPoint );

        if( constantBufferName[0] == '@' )
        {
            constantBufferName += ptoc(pModel) + itoc(meshIndex);
        }
        else if( constantBufferName[0] == '#' )
        {
            constantBufferName += ptoc(pModel);
        }
        if( !params.mpConstantBuffer[constantBufferCount] )
        {
            params.mpConstantBuffer[constantBufferCount] = pAssetLibrary->GetConstantBuffer( constantBufferName );
            ASSERT( params.mpConstantBuffer[constantBufferCount], _L("Failed getting constant buffer ") + constantBufferName);
        }

#ifndef CPUT_FOR_OGLES2
        ES3_COMPAT(glUniformBlockBinding(mShaderProgram, bindPoint, bindPoint)); // just use the index as the binding point
#else
#warning "Need to do something with uniform buffers here"
#endif
        // If has constant buffer, then add to mppBindConstantBuffer
//        params.mppBindConstantBuffers[bindPoint]   = ((CPUTBufferOGL*)mpConstantBuffer[constantBufferCount])->GetNativeBuffer();
//        if( params.mppBindConstantBuffers[bindPoint] ) {
//            params.mppBindConstantBuffers[bindPoint]->AddRef();
//        }
    }
	  DEBUG_PRINT(_L("Exit BindConstantBuffers"));

}

//-----------------------------------------------------------------------------
void CPUTMaterialOGL::ReleaseTexturesAndBuffers()
{
    assert(false);
}

//-----------------------------------------------------------------------------
void CPUTMaterialOGL::RebindTexturesAndBuffers()
{
    assert(false);
}

//-----------------------------------------------------------------------------
bool CPUTMaterialOGL::MaterialRequiresPerModelPayload()
{
//    assert(false);
    if( mRequiresPerModelPayload == -1 )
    {
        mRequiresPerModelPayload = 
            (mpFragmentShader    && mpFragmentShader->ShaderRequiresPerModelPayload(mConfigBlock))  ||
//            (mpComputeShader  && mpComputeShader ->ShaderRequiresPerModelPayload(mConfigBlock))  ||
            (mpVertexShader   && mpVertexShader->ShaderRequiresPerModelPayload(mConfigBlock));//  ||
//            (mpGeometryShader && mpGeometryShader->ShaderRequiresPerModelPayload(mConfigBlock))  ||
//            (mpHullShader     && mpHullShader    ->ShaderRequiresPerModelPayload(mConfigBlock))  ||
//            (mpDomainShader   && mpDomainShader  ->ShaderRequiresPerModelPayload(mConfigBlock));
    }
    return mRequiresPerModelPayload != 0;
}

//-----------------------------------------------------------------------------
CPUTMaterial *CPUTMaterialOGL::CloneMaterial(const cString &fileName, const CPUTModel *pModel, int meshIndex)
{
    CPUTMaterialOGL *pMaterial = new CPUTMaterialOGL();

    // TODO: move texture to base class.  All APIs have textures.
    pMaterial->mpFragmentShader    = mpFragmentShader;    if(mpFragmentShader)    mpFragmentShader->AddRef();   
    //pMaterial->mpComputeShader  = mpComputeShader;  if(mpComputeShader)  mpComputeShader->AddRef();
    pMaterial->mpVertexShader   = mpVertexShader;   if(mpVertexShader)   mpVertexShader->AddRef();
    //pMaterial->mpGeometryShader = mpGeometryShader; if(mpGeometryShader) mpGeometryShader->AddRef();
    //pMaterial->mpHullShader     = mpHullShader;     if(mpHullShader)     mpHullShader->AddRef();
    //pMaterial->mpDomainShader   = mpDomainShader;   if(mpDomainShader)   mpDomainShader->AddRef();
    pMaterial->mShaderProgram = mShaderProgram;

    mPixelShaderParameters.CloneShaderParameters(    &pMaterial->mPixelShaderParameters );
    //mComputeShaderParameters.CloneShaderParameters(  &pMaterial->mComputeShaderParameters );
    mVertexShaderParameters.CloneShaderParameters(   &pMaterial->mVertexShaderParameters );
    //mGeometryShaderParameters.CloneShaderParameters( &pMaterial->mGeometryShaderParameters );
    //mHullShaderParameters.CloneShaderParameters(     &pMaterial->mHullShaderParameters );
    //mDomainShaderParameters.CloneShaderParameters(   &pMaterial->mDomainShaderParameters );

    pMaterial->mpShaderParametersList[0] =  &pMaterial->mPixelShaderParameters,
    //pMaterial->mpShaderParametersList[1] =  &pMaterial->mComputeShaderParameters,
    pMaterial->mpShaderParametersList[2] =  &pMaterial->mVertexShaderParameters,
    //pMaterial->mpShaderParametersList[3] =  &pMaterial->mGeometryShaderParameters,
    //pMaterial->mpShaderParametersList[4] =  &pMaterial->mHullShaderParameters,
    //pMaterial->mpShaderParametersList[5] =  &pMaterial->mDomainShaderParameters,
    pMaterial->mpShaderParametersList[6] =  NULL;

    pMaterial->mpRenderStateBlock = mpRenderStateBlock;
    if( mpRenderStateBlock ) {
        mpRenderStateBlock->AddRef();
    }

    pMaterial->mMaterialName      = mMaterialName + ptoc(pModel) + itoc(meshIndex);
    pMaterial->mMaterialNameHash  = CPUTComputeHash(pMaterial->mMaterialName);
    pMaterial->mConfigBlock       = mConfigBlock;

    // For each of the shader stages, bind shaders and buffers
 //   for( CPUTShaderParameters **pCur = pMaterial->mpShaderParametersList; *pCur; pCur++ ) // Bind textures and buffersfor each shader stage
    {
        pMaterial->BindTextures(        pMaterial->mVertexShaderParameters, pModel, meshIndex );
//        pMaterial->BindBuffers(         **pCur, pModel, meshIndex );
        pMaterial->BindUAVs(            pMaterial->mVertexShaderParameters, pModel, meshIndex );
//        pMaterial->BindConstantBuffers( **pCur, pModel, meshIndex );
    }
    // Append this clone to our clone list
    if( mpMaterialNextClone )
    {
        // Already have a list, so add to the end of it.
        ((CPUTMaterialOGL*)mpMaterialLastClone)->mpMaterialNextClone = pMaterial;
    } else
    {
        // No list yet, so start it with this material.
        mpMaterialNextClone = pMaterial;
        mpMaterialLastClone = pMaterial;
    }
    pMaterial->mpModel    = pModel;
    pMaterial->mMeshIndex = meshIndex;
    
    return pMaterial;
}

//-----------------------------------------------------------------------------
void CPUTShaderParameters::CloneShaderParameters( CPUTShaderParameters *pShaderParameter )
{
//    pShaderParameter->mpTextureParameterName              = new cString[mTextureParameterCount];
//    pShaderParameter->mpTextureParameterBindPoint         = new UINT[   mTextureParameterCount];
    pShaderParameter->mpSamplerParameterName              = new cString[mSamplerParameterCount];
    pShaderParameter->mpSamplerParameterBindPoint         = new UINT[   mSamplerParameterCount];
    pShaderParameter->mpBufferParameterName               = new cString[mBufferParameterCount];
    pShaderParameter->mpBufferParameterBindPoint          = new UINT[   mBufferParameterCount];
    //pShaderParameter->mpUAVParameterName                  = new cString[mUAVParameterCount];
    //pShaderParameter->mpUAVParameterBindPoint             = new UINT[   mUAVParameterCount];
//    pShaderParameter->mpConstantBufferParameterName       = new cString[mConstantBufferParameterCount];
//    pShaderParameter->mpConstantBufferParameterBindPoint  = new UINT[   mConstantBufferParameterCount];

    pShaderParameter->mTextureCount                 = mTextureCount;
    
    pShaderParameter->mpTextureParameterNames       = mpTextureParameterNames;
    pShaderParameter->mpTextureParameterBindPoints  = mpTextureParameterBindPoints;
    pShaderParameter->mpTextureParameterLocations  = mpTextureParameterLocations;
    
    pShaderParameter->mpUAVParameterNames = mpUAVParameterNames;
    pShaderParameter->mpUAVParameterBindPoints  = mpUAVParameterBindPoints;
    pShaderParameter->mpUAVParameterLocations = mpUAVParameterLocations;

    pShaderParameter->mTextureParameterCount        = mTextureParameterCount;
    pShaderParameter->mBufferParameterCount         = mBufferParameterCount;
    pShaderParameter->mUAVParameterCount            = mUAVParameterCount;
    pShaderParameter->mConstantBufferParameterCount = mConstantBufferParameterCount;

    for(UINT ii=0; ii<mTextureParameterCount; ii++ )
    {
//        pShaderParameter->mpTextureParameterName[ii]      = mpTextureParameterName[ii];
//        pShaderParameter->mpTextureParameterBindPoint[ii] = mpTextureParameterBindPoint[ii];
    }
    for(UINT ii=0; ii<mSamplerParameterCount; ii++ )
    {
        pShaderParameter->mpSamplerParameterName[ii]      = mpSamplerParameterName[ii];
        pShaderParameter->mpSamplerParameterBindPoint[ii] = mpSamplerParameterBindPoint[ii];
    }
    
    pShaderParameter->mBufferCount = mBufferCount;
    for(UINT ii=0; ii<mBufferParameterCount; ii++ )
    {
        pShaderParameter->mpBufferParameterName[ii]      = mpBufferParameterName[ii];
        pShaderParameter->mpBufferParameterBindPoint[ii] = mpBufferParameterBindPoint[ii];
    }
    for(UINT ii=0; ii<mUAVParameterCount; ii++ )
    {
        //pShaderParameter->mpUAVParameterName[ii]      = mpUAVParameterName[ii];
        //pShaderParameter->mpUAVParameterBindPoint[ii] = mpUAVParameterBindPoint[ii];
    }
    for(UINT ii=0; ii<mConstantBufferParameterCount; ii++ )
    {
//        pShaderParameter->mpConstantBufferParameterName[ii]      = mpConstantBufferParameterName[ii];
//        pShaderParameter->mpConstantBufferParameterBindPoint[ii] = mpConstantBufferParameterBindPoint[ii];
    }
    pShaderParameter->mBindViewMin = mBindViewMin;
    pShaderParameter->mBindViewMax = mBindViewMax;

    pShaderParameter->mBindUAVMin = mBindUAVMin;
    pShaderParameter->mBindUAVMax = mBindUAVMax;

    pShaderParameter->mBindConstantBufferMin = mBindConstantBufferMin;
    pShaderParameter->mBindConstantBufferMax = mBindConstantBufferMax;
}