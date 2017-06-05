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
