//--------------------------------------------------------------------------------------
// Copyright 2011 Intel Corporation
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
#ifndef __CPUT_SAMPLESTARTDX11_H__
#define __CPUT_SAMPLESTARTDX11_H__

#include <stdio.h>
#include <time.h>
#include "CPUTScene.h"
#include "CPUT_OGL.h"
#include "CPUTSpriteOGL.h"
#include "CPUTRenderTargetOGL.h"


// define some controls
const CPUTControlID ID_MAIN_PANEL = 10;
const CPUTControlID ID_SECONDARY_PANEL = 20;
const CPUTControlID ID_TESSELLATION_BUTTON = 100;
const CPUTControlID ID_WIREFRAME_BUTTON = 101;
const CPUTControlID ID_INCREASE_TESSELLATION = 102;
const CPUTControlID ID_DECREASE_TESSELLATION = 103;
const CPUTControlID ID_TOGGLE_DEMOMODE = 104;
//-----------------------------------------------------------------------------
class TessellationSample : public CPUT_OGL
{
private:
    float                  mfElapsedTime;
    CPUTAssetSet          *mpAssetSet;
    CPUTCameraController  *mpCameraController;
    CPUTSprite            *mpDebugSprite;

    CPUTAssetSet          *mpShadowCameraSet;
    CPUTFramebufferOGL    *mpShadowRenderTarget;

    CPUTScene             *mpScene;

    CPUTMaterial*          mpSkyBoxMaterial;
	CPUTSpriteOGL*         mpSkyBoxSprite;

public:
    TessellationSample() : 
        mpAssetSet(NULL),
        mpCameraController(NULL),
        mpDebugSprite(NULL),
        mpShadowCameraSet(NULL)
    {
    }
    virtual ~TessellationSample()
    {
    }
    virtual CPUTEventHandledCode HandleKeyboardEvent(CPUTKey key, CPUTKeyState state);
    virtual CPUTEventHandledCode HandleMouseEvent(int x, int y, int wheel, CPUTMouseState state);
    virtual void                 HandleCallbackEvent( CPUTEventID Event, CPUTControlID ControlID, CPUTControl *pControl );

    virtual void Create();
    virtual void Render(double deltaSeconds);
    virtual void Update(double deltaSeconds);
    virtual void ResizeWindow(UINT width, UINT height);
    void ReleaseResources();

    void LoadAssets();
};
#endif // __CPUT_SAMPLESTARTDX11_H__
