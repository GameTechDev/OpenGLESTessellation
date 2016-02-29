/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>


#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "CPUTScene.h"
#include "CPUTRenderStateBlockOGL.h"
#include "CPUT_OGL.h"
#include "CPUTGuiControllerOGL.h"
#include "CPUTWindowAndroid.h"
#include "CPUTSpriteOGL.h"
#include "CPUTRenderTargetOGL.h"
#include "CPUTTextureOGL.h"
#include "CPUTFont.h"

// define some controls
const CPUTControlID ID_MAIN_PANEL = 10;
const CPUTControlID ID_SECONDARY_PANEL = 20;
const CPUTControlID ID_TESSELLATION_BUTTON = 100;
const CPUTControlID ID_WIREFRAME_BUTTON = 101;
const CPUTControlID ID_INCREASE_TESSELLATION = 102;
const CPUTControlID ID_DECREASE_TESSELLATION = 103;
const CPUTControlID ID_TOGGLE_DEMOMODE = 104;
const CPUTControlID ID_TEST_CONTROL = 1000;
const CPUTControlID ID_IGNORE_CONTROL_ID = -1;

const cString MEDIA_DIR = _L("../../../Media/");
#define GUI_LOCATION     "gui_assets/"
#define SYSTEM_LOCATION  "System/"
#define SCENE_FILE       "androidscene.scene"
#define ASSET_LOCATION   "Teapot/"
#define ASSET_SET_FILE   "teapot"

// Unsure about these globals. Seem a bit hacky atm
const UINT SHADOW_WIDTH_HEIGHT = 2048;
static bool TessellationEnabled = true;
static float MaxTessellation = 16.0f;
static bool DemoMode = true;

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

    CPUTMaterial*       mpSkyBoxMaterial;
    CPUTSpriteOGL*      mpSkyBoxSprite;
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
        // Note: these two are defined in the base.  We release them because we addref them.
        SAFE_RELEASE(mpCamera);
        SAFE_RELEASE(mpShadowCamera);

        SAFE_RELEASE(mpAssetSet);
        SAFE_DELETE( mpCameraController );
        SAFE_DELETE( mpDebugSprite);
        SAFE_RELEASE(mpShadowCameraSet);
        SAFE_DELETE( mpShadowRenderTarget );
        SAFE_DELETE( mpScene );
    }

    virtual CPUTEventHandledCode HandleKeyboardEvent(CPUTKey key, CPUTKeyState state)
    {
        if (mpCameraController)
        {
            return mpCameraController->HandleKeyboardEvent(key, state);
        }
        return CPUT_EVENT_UNHANDLED;
    }

    virtual CPUTEventHandledCode HandleMouseEvent(int x, int y, int wheel, CPUTMouseState state)
    {
        if (mpCameraController)
        {
            return mpCameraController->HandleMouseEvent(x, y, wheel, state);
        }
        return CPUT_EVENT_UNHANDLED;
    }

    virtual void HandleCallbackEvent( CPUTEventID Event, CPUTControlID ControlID, CPUTControl *pControl )
    {
        if(Event == CPUT_EVENT_DOWN && ControlID == ID_TESSELLATION_BUTTON)
            TessellationEnabled = !TessellationEnabled;
        else if(Event == CPUT_EVENT_DOWN && ControlID == ID_WIREFRAME_BUTTON)
        {            
            CPUTMaterial* material = CPUTAssetLibrary::GetAssetLibrary()->GetMaterialByName("terrainLow_03/Material/terrain.mtl");
            DEBUG_PRINT("%p\n", material);
            static int wireframe = 1;
            material->SetCurrentEffect(wireframe);
            wireframe = !wireframe;
        }
        else if(Event == CPUT_EVENT_DOWN && ControlID == ID_INCREASE_TESSELLATION)
        {            
            MaxTessellation *= 2.0f;
            if(MaxTessellation > 64.0f)
                MaxTessellation = 64.0f;
        }
        else if(Event == CPUT_EVENT_DOWN && ControlID == ID_DECREASE_TESSELLATION)
        {            
            MaxTessellation /= 2.0f;
            if(MaxTessellation <= 1.0f)
                MaxTessellation = 1.0f;
        }
        else if(Event == CPUT_EVENT_DOWN && ControlID == ID_TOGGLE_DEMOMODE)
        {            
            DemoMode = !DemoMode;
            if(DemoMode)
                mpCamera->SetPosition( 17000.0f, 6000.0f, 0.0f );
        }

        return;
    }

    virtual void Create();
    virtual void Render(double deltaSeconds);
    virtual void Update(double deltaSeconds);
    virtual void ResizeWindow(UINT width, UINT height);

//    void LoadAssets();

};



void TessellationSample::Render(double deltaSeconds)
{
    CPUTRenderParameters renderParams;
    
    renderParams.mpCamera = mpCamera;
    renderParams.mpShadowCamera = mpShadowCamera;
    renderParams.mpPerFrameConstants = mpPerFrameConstantBuffer;
    renderParams.mpPerModelConstants = mpPerModelConstantBuffer;
    if(TessellationEnabled)
        UpdatePerFrameConstantBuffer(renderParams, MaxTessellation);
    else
        UpdatePerFrameConstantBuffer(renderParams, 1);

    int width,height;
    mpWindow->GetClientDimensions(&width, &height);

    // Set default viewport
    glViewport( 0, 0, width, height );
    GL_CHECK(glClearColor ( 0.0, 0.5, 1, 1 ));
    GL_CHECK(glClearDepthf(0.0f));
    GL_CHECK(glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ));

    mpSkyBoxSprite->DrawSprite(renderParams,*mpSkyBoxMaterial);

    mpScene->Render( renderParams);
#ifdef ENABLE_GUI
	CPUTDrawGUI();
#endif
}

void TessellationSample::Update(double deltaSeconds)
{
    static float time = 0.0f;
    static int frame_count = 0;
    mpCameraController->Update((float)deltaSeconds);
    if(frame_count == 60) {
        LOGI("FPS: %.2f", frame_count/time);
        frame_count = 0;
        time = 0.0f;
    }
    time += (float)deltaSeconds;
    frame_count++;

    if(DemoMode) {
        float3 vec = mpCamera->GetPosition();
        float3x3 m = float3x3RotationY(deltaSeconds/5.0f);
        vec = m * vec;
        mpCamera->SetPosition(vec);
        mpCamera->LookAt(float3(-16000,4000,17000));
    }

}

void TessellationSample::Create()
{
	LOGI("Start Create");

    CPUTAssetLibrary *pAssetLibrary = CPUTAssetLibrary::GetAssetLibrary();
    cString ExecutableDirectory;
    CPUTFileSystem::GetExecutableDirectory(&ExecutableDirectory);
    //ExecutableDirectory.append(_L(ASSET_LOCATION));
    pAssetLibrary->SetMediaDirectoryName(ExecutableDirectory);

#ifdef ENABLE_GUI
    CPUTGuiControllerOGL *pGUI = (CPUTGuiControllerOGL*)CPUTGetGuiController();
    auto str = pAssetLibrary->GetMediaDirectoryName();
    std::string fontDirectory("Font/");
    CPUTFont *pFont = CPUTFont::CreateFont(SYSTEM_LOCATION + fontDirectory, "arial_64.fnt");

    pGUI->SetFont(pFont);
    //
    // Create some controls
    //   
	// CPUTDropdown *pDropdownMethod;

     pGUI->CreateButton(_L("Demo Mode    "), ID_TOGGLE_DEMOMODE, ID_MAIN_PANEL, NULL);
     pGUI->CreateButton(_L("Tessellation    "), ID_TESSELLATION_BUTTON, ID_MAIN_PANEL, NULL);
     pGUI->CreateButton(_L("Wireframe       "), ID_WIREFRAME_BUTTON, ID_MAIN_PANEL, NULL);
     pGUI->CreateButton(_L("+ Tessellation "), ID_INCREASE_TESSELLATION, ID_MAIN_PANEL, NULL);
     pGUI->CreateButton(_L("- Tessellation  "), ID_DECREASE_TESSELLATION, ID_MAIN_PANEL, NULL);
 //    pGUI->CreateText(_L("Test Font"), ID_IGNORE_CONTROL_ID, ID_MAIN_PANEL);
 //    pGUI->CreateDropdown(_L("Disabled"), ID_IGNORE_CONTROL_ID, ID_MAIN_PANEL, &pDropdownMethod);
 //    pDropdownMethod->AddSelectionItem(_L("Test Method"), true);
#endif
    pAssetLibrary->SetMediaDirectoryName(ExecutableDirectory);

    CPUTMaterial::mGlobalProperties.AddValue( _L("_Shadow"), _L("$shadow_depth") );

    int width, height;
    mpWindow->GetClientDimensions(&width, &height);
    DEBUG_PRINT(_L("Resize Window"));

    CPUTTextureOGL*  pDepthTexture = (CPUTTextureOGL*)CPUTTextureOGL::CreateTexture(_L("$shadow_depth"), GL_DEPTH_COMPONENT, SHADOW_WIDTH_HEIGHT, SHADOW_WIDTH_HEIGHT, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
    mpShadowRenderTarget = new CPUTFramebufferOGL(NULL, pDepthTexture);
    SAFE_RELEASE(pDepthTexture);

    mpDebugSprite = CPUTSprite::CreateSprite( -1.0f, -1.0f, 0.5f, 0.5f, _L("%sprite") );

    ResizeWindow(width, height);


    //CPUTRenderStateBlockOGL *pBlock = new CPUTRenderStateBlockOGL();
    //CPUTRenderStateOGL *pStates = pBlock->GetState();

    // Override default sampler desc for our default shadowing sampler
    //pStates->SamplerDesc[1].MinFilter      = GL_NEAREST_MIPMAP_NEAREST;
    //pStates->SamplerDesc[1].AddressU       = GL_CLAMP_TO_EDGE;
    //pStates->SamplerDesc[1].AddressV       = GL_CLAMP_TO_EDGE;
    //pStates->SamplerDesc[1].ComparisonFunc = GL_GREATER;
 	//pBlock->CreateNativeResources();
    //CPUTAssetLibrary::GetAssetLibrary()->AddRenderStateBlock( _L("$DefaultRenderStates"), pBlock );
    //pBlock->Release(); // We're done with it.  The library owns it now.

    mpScene = new CPUTScene();
    DEBUG_PRINT(_L("Load Scene"));
    // Load the scene
    if (CPUTFAILED(mpScene->LoadScene(SCENE_FILE)))
    {
        LOGI("Failed to Load Scene, try loading asset set individually");
        CPUTAssetSet *pAssetSet = NULL;
        pAssetSet = pAssetLibrary->GetAssetSet( ASSET_SET_FILE );
        mpScene->AddAssetSet(pAssetSet);
        pAssetSet->Release();
    }


    LOGI("Loaded the scene");

    // Get the camera. Get the first camera encountered in the scene or
    // if there are none, create a new one.
    unsigned int numAssets = mpScene->GetNumAssetSets();
    for (unsigned int i = 0; i < numAssets; ++i) {
        CPUTAssetSet *pAssetSet = mpScene->GetAssetSet(i);
        if (pAssetSet->GetCameraCount() > 0) {
            mpCamera = pAssetSet->GetFirstCamera();
            break;
        }
    }
    // Create the camera
    if (mpCamera == NULL)
    {
        LOGI("Creating the camera");
        mpCamera = new CPUTCamera();
        pAssetLibrary->AddCamera( _L(""), _L("SampleStart Camera"), _L(""), mpCamera );

        mpCamera->SetPosition( 17000.0f, 6000.0f, 0.0f );
        // Set the projection matrix for all of the cameras to match our window.
        // TODO: this should really be a viewport matrix.  Otherwise, all cameras will have the same FOV and aspect ratio, etc instead of just viewport dimensions.
        mpCamera->SetAspectRatio(((float)width)/((float)height));
    }
    mpCamera->SetFov(DegToRad(90.0)); // TODO: Fix converter's FOV bug (Maya generates cameras for which fbx reports garbage for fov)
    mpCamera->SetFarPlaneDistance(10000.0f);
    mpCamera->SetNearPlaneDistance(100.0f);
    mpCamera->Update();

    // Position and orient the shadow camera so that it sees the whole scene.
    // Set the near and far planes so that the frustum contains the whole scene.
    // Note that if we are allowed to move the shadow camera or the scene, this may no longer be true.
    // Consider updating the shadow camera when it (or the scene) moves.
    // Treat bounding box half as radius for an approximate bounding sphere.
    // The tightest-fitting sphere might be smaller, but this is close enough for placing our shadow camera.
    float3 sceneCenterPoint, halfVector;
    mpScene->GetBoundingBox(&sceneCenterPoint, &halfVector);
    float  length = halfVector.length();
    mpShadowCamera = new CPUTCamera( CPUT_CAMERA_TYPE_ORTHOGRAPHIC );
    mpShadowCamera->SetAspectRatio(1.0f);
    mpShadowCamera->SetNearPlaneDistance(1.0f);
    mpShadowCamera->SetFarPlaneDistance(2.0f*length + 1.0f);
    mpShadowCamera->SetPosition( sceneCenterPoint - float3(0,-1,1)* length );
    mpShadowCamera->LookAt( sceneCenterPoint );
    mpShadowCamera->SetWidth( length*2);
    mpShadowCamera->SetHeight(length*2);
    mpShadowCamera->Update();

    pAssetLibrary->AddCamera( _L(""), _L("ShadowCamera"), _L(""), mpShadowCamera );

    mpCameraController = new CPUTCameraControllerFPS();
    mpCameraController->SetCamera(mpCamera);
    mpCameraController->SetLookSpeed(0.004f);
    mpCameraController->SetMoveSpeed(20000.0f);

    // Skybox
    //pAssetLibrary->SetMediaDirectoryName(  ExecutableDirectory + MEDIA_DIR);
    pAssetLibrary->SetMediaDirectoryName(ExecutableDirectory);
    mpSkyBoxMaterial = pAssetLibrary->GetMaterial( _L("skybox") );

    mpSkyBoxSprite = (CPUTSpriteOGL*)CPUTSprite::CreateSprite( -1.0f, -1.0f, 2.0f, 2.0f, _L("skybox") );
    mpSkyBoxSprite->GetMesh()->SetNumVertices(1);
    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

// Handle resize events
//-----------------------------------------------------------------------------
void TessellationSample::ResizeWindow(UINT width, UINT height)
{
}

CPUTKey ConvertToCPUTKey(int aKey)
{
    if ((aKey >= AKEYCODE_0) && (aKey <= AKEYCODE_9))
        return (CPUTKey)(KEY_0 + aKey - AKEYCODE_0);

    if ((aKey >= AKEYCODE_A) && (aKey <= AKEYCODE_Z))
        return (CPUTKey)(KEY_A + aKey - AKEYCODE_A);

    switch (aKey)
    {
    case AKEYCODE_HOME:
        return KEY_HOME;
    case AKEYCODE_STAR:
        return KEY_STAR;
    case AKEYCODE_POUND:
        return KEY_HASH;
    case AKEYCODE_COMMA:
        return KEY_COMMA;
    case AKEYCODE_PERIOD:
        return KEY_PERIOD;
    case AKEYCODE_ALT_LEFT:
        return KEY_LEFT_ALT;
    case AKEYCODE_ALT_RIGHT:
        return KEY_RIGHT_ALT;
    case AKEYCODE_SHIFT_LEFT:
        return KEY_LEFT_SHIFT;
    case AKEYCODE_SHIFT_RIGHT:
        return KEY_RIGHT_SHIFT;
    case AKEYCODE_TAB:
        return KEY_TAB;
    case AKEYCODE_SPACE:
        return KEY_SPACE;
    case AKEYCODE_ENTER:
        return KEY_ENTER;
    case AKEYCODE_DEL:
        return KEY_DELETE;
    case AKEYCODE_MINUS:
        return KEY_MINUS;
    case AKEYCODE_LEFT_BRACKET:
        return KEY_OPENBRACKET;
    case AKEYCODE_RIGHT_BRACKET:
        return KEY_CLOSEBRACKET;
    case AKEYCODE_BACKSLASH:
        return KEY_BACKSLASH;
    case AKEYCODE_SEMICOLON:
        return KEY_SEMICOLON;
    case AKEYCODE_APOSTROPHE:
        return KEY_SINGLEQUOTE;
    case AKEYCODE_SLASH:
        return KEY_SLASH;
    case AKEYCODE_AT:
        return KEY_AT;
    case AKEYCODE_PLUS:
        return KEY_PLUS;
    case AKEYCODE_PAGE_UP:
        return KEY_PAGEUP;
    case AKEYCODE_PAGE_DOWN:
        return KEY_PAGEDOWN;
    default:
    case AKEYCODE_SOFT_LEFT:
    case AKEYCODE_SOFT_RIGHT:
    case AKEYCODE_BACK:
    case AKEYCODE_CALL:
    case AKEYCODE_ENDCALL:
    case AKEYCODE_DPAD_UP:
    case AKEYCODE_DPAD_DOWN:
    case AKEYCODE_DPAD_LEFT:
    case AKEYCODE_DPAD_RIGHT:
    case AKEYCODE_DPAD_CENTER:
    case AKEYCODE_VOLUME_UP:
    case AKEYCODE_VOLUME_DOWN:
    case AKEYCODE_POWER:
    case AKEYCODE_CAMERA:
    case AKEYCODE_CLEAR:
    case AKEYCODE_SYM:
    case AKEYCODE_EXPLORER:
    case AKEYCODE_ENVELOPE:
    case AKEYCODE_GRAVE:
    case AKEYCODE_EQUALS:
    case AKEYCODE_NUM:
    case AKEYCODE_HEADSETHOOK:
    case AKEYCODE_FOCUS:
    case AKEYCODE_MENU:
    case AKEYCODE_NOTIFICATION:
    case AKEYCODE_SEARCH:
    case AKEYCODE_MEDIA_PLAY_PAUSE:
    case AKEYCODE_MEDIA_STOP:
    case AKEYCODE_MEDIA_NEXT:
    case AKEYCODE_MEDIA_PREVIOUS:
    case AKEYCODE_MEDIA_REWIND:
    case AKEYCODE_MEDIA_FAST_FORWARD:
    case AKEYCODE_MUTE:
    case AKEYCODE_PICTSYMBOLS:
    case AKEYCODE_SWITCH_CHARSET:
    case AKEYCODE_BUTTON_L1:
    case AKEYCODE_BUTTON_R1:
    case AKEYCODE_BUTTON_L2:
    case AKEYCODE_BUTTON_R2:
    case AKEYCODE_BUTTON_THUMBL:
    case AKEYCODE_BUTTON_THUMBR:
    case AKEYCODE_BUTTON_START:
    case AKEYCODE_BUTTON_SELECT:
    case AKEYCODE_BUTTON_MODE:
    case AKEYCODE_UNKNOWN:
        return KEY_NONE;
    }

}

CPUTKeyState ConvertToCPUTKeyState(int aAction)
{
    switch (aAction)
    {
    case AKEY_EVENT_ACTION_UP:
        return CPUT_KEY_UP;
    case AKEY_EVENT_ACTION_DOWN:
    default:
        return CPUT_KEY_DOWN;
    }
}

int32_t CPUT_OGL::cput_handle_input(struct android_app* app, AInputEvent* event)
{    
	int n;
    TessellationSample *pSample = (TessellationSample *)app->userData;
	int lEventType = AInputEvent_getType(event);
    static float drag_center_x = 0.0f, drag_center_y = 0.0f;
    static float dist_squared = 0.0f;
    static bool isPanning = false;
    
    switch (lEventType) 
	{
        case AINPUT_EVENT_TYPE_MOTION:
			{
                ndk_helper::GESTURE_STATE doubleTapState = pSample->mDoubletapDetector.Detect(event);
                ndk_helper::GESTURE_STATE dragState      = pSample->mDragDetector.Detect(event);
                ndk_helper::GESTURE_STATE pinchState     = pSample->mPinchDetector.Detect(event);

                if( doubleTapState == ndk_helper::GESTURE_STATE_ACTION )
                {
                    LOGI("DOUBLE TAP RECEIVED");
                }
                else
                {
                    //Handle drag state
                    if( dragState & ndk_helper::GESTURE_STATE_START )
                    {
                        if (isPanning == false) {
                            LOGI("GESTURE_STATE_START - drag");
                            ndk_helper::Vec2 v;
                            float x, y;
                            pSample->mDragDetector.GetPointer( v );

                            v.Value(x, y);
                            LOGI("     TOUCH POINT: %f, %f", x, y);
                            pSample->CPUTHandleMouseEvent(x, y, 0.0f, CPUT_MOUSE_LEFT_DOWN);
                        }
                    }
                    else if( dragState & ndk_helper::GESTURE_STATE_MOVE )
                    {
                        if (isPanning == false) {
                            LOGI("GESTURE_STATE_MOVE - drag");
                            ndk_helper::Vec2 v;
                            float x, y;
                            pSample->mDragDetector.GetPointer( v );
                            v.Value(x, y);
                            pSample->CPUTHandleMouseEvent(x, y, 0.0f, CPUT_MOUSE_LEFT_DOWN);
                        }
                    }
                    else if( dragState & ndk_helper::GESTURE_STATE_END )
                    {
                        pSample->CPUTHandleMouseEvent(0.0f, 0.0f, 0.0f, CPUT_MOUSE_NONE);
                        pSample->HandleKeyboardEvent(KEY_A, CPUT_KEY_UP);
                        pSample->HandleKeyboardEvent(KEY_D, CPUT_KEY_UP);
                        pSample->HandleKeyboardEvent(KEY_E, CPUT_KEY_UP);
                        pSample->HandleKeyboardEvent(KEY_W, CPUT_KEY_UP);
                        pSample->HandleKeyboardEvent(KEY_S, CPUT_KEY_UP);
                        pSample->HandleKeyboardEvent(KEY_Q, CPUT_KEY_UP);
                        isPanning = false;
                        LOGI("GESTURE_STATE_END - drag");
                    }

                    //Handle pinch state
                    if( pinchState & ndk_helper::GESTURE_STATE_START )
                    {
                        if (isPanning == false) {
                            LOGI("GESTURE_STATE_START - pinch");
                            //Start new pinch
                            ndk_helper::Vec2 v1;
                            ndk_helper::Vec2 v2;
                            float x1, y1, x2, y2;
                            pSample->mPinchDetector.GetPointers( v1, v2 );
                            v1.Value(x1, y1);
                            v2.Value(x2, y2);
                            drag_center_x = (x1 + x2) / 2.0f;
                            drag_center_y = (y1 + y2) / 2.0f;
                            dist_squared = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));
                        }
                   }
                    else if( pinchState & ndk_helper::GESTURE_STATE_MOVE )
                    {
                        isPanning = true;

                        CPUTKey key = (CPUTKey)0;
                        CPUTKeyState state = (CPUTKeyState)0;

                        LOGI("GESTURE_STATE_MOVE - pinch");
                        
                        ndk_helper::Vec2 v1;
                        ndk_helper::Vec2 v2;
                        float x1, y1, x2, y2;
                        float new_center_x, new_center_y;
                        float new_dist_squared;
                        float delta_x, delta_y;
                        pSample->mPinchDetector.GetPointers( v1, v2 );
                        v1.Value(x1, y1);
                        v2.Value(x2, y2);
                            
                        new_center_x = (x1 + x2) / 2.0f;
                        new_center_y = (y1 + y2) / 2.0f;

                        new_dist_squared = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));

                        delta_x = drag_center_x - new_center_x;
                        delta_y = drag_center_y - new_center_y;

                        //
                        // For each direction of movement, the opposite direction is cancelled (KEY_UP)
                        //

                        // Handle pinch and zoom actions
                        if (abs(new_dist_squared - dist_squared) > 1000.0f) {
                            if (new_dist_squared < dist_squared) {
                                pSample->HandleKeyboardEvent(KEY_W, CPUT_KEY_UP);
                                pSample->HandleKeyboardEvent(KEY_S, CPUT_KEY_DOWN);
                            } else {
                                pSample->HandleKeyboardEvent(KEY_S, CPUT_KEY_UP);
                                pSample->HandleKeyboardEvent(KEY_W, CPUT_KEY_DOWN);
                            } 
                        } else {
                            pSample->HandleKeyboardEvent(KEY_W, CPUT_KEY_UP);
                            pSample->HandleKeyboardEvent(KEY_S, CPUT_KEY_UP);
                        }

                        // handle left and right drag
                        if (delta_x >= 2.0f) {
                            pSample->HandleKeyboardEvent(KEY_A, CPUT_KEY_DOWN);
                            pSample->HandleKeyboardEvent(KEY_D, CPUT_KEY_UP);
                        } else if (delta_x <= -2.0f) {
                            pSample->HandleKeyboardEvent(KEY_D, CPUT_KEY_DOWN);
                            pSample->HandleKeyboardEvent(KEY_A, CPUT_KEY_UP);
                        } else if (delta_x < 2.0 && delta_x > -2.0) {
                            pSample->HandleKeyboardEvent(KEY_A, CPUT_KEY_UP);
                            pSample->HandleKeyboardEvent(KEY_D, CPUT_KEY_UP);
                        }

                        // handle up and down drag
                        if (delta_y >= 2.0f) {
                            pSample->HandleKeyboardEvent(KEY_Q, CPUT_KEY_UP);
                            pSample->HandleKeyboardEvent(KEY_E, CPUT_KEY_DOWN);
                        } else if (delta_y <= -2.0f) {
                            pSample->HandleKeyboardEvent(KEY_E, CPUT_KEY_UP);
                            pSample->HandleKeyboardEvent(KEY_Q, CPUT_KEY_DOWN);
                        } else if (delta_y < 2.0 && delta_y > -2.0) {
                            pSample->HandleKeyboardEvent(KEY_E, CPUT_KEY_UP);
                            pSample->HandleKeyboardEvent(KEY_Q, CPUT_KEY_UP);
                        }


                        // current values become old values for next frame
                        dist_squared = new_dist_squared;
                        drag_center_x = new_center_x;
                        drag_center_y = new_center_y;
                    }
                }
                
			}
		case AINPUT_EVENT_TYPE_KEY:
			{
				int aKey = AKeyEvent_getKeyCode(event);
				CPUTKey cputKey = ConvertToCPUTKey(aKey);
				int aAction = AKeyEvent_getAction(event);
				CPUTKeyState cputKeyState = ConvertToCPUTKeyState(aAction);
				pSample->CPUTHandleKeyboardEvent(cputKey, cputKeyState);
				return 1;
			}
		default:
			return 0;
    }
    
    return 0;
}

static void cput_handle_cmd(struct android_app* app, int32_t cmd)
{
    TessellationSample *pSample = (TessellationSample *)app->userData;

	switch (cmd)
    {
    case APP_CMD_SAVE_STATE:
        LOGI("APP_CMD_SAVE_STATE");
        break;
    case APP_CMD_INIT_WINDOW:
        LOGI("APP_CMD_INIT_WINDOW");
        if (!pSample->HasWindow())
        {
            LOGI("Creating window");
            CPUTResult result;

            // window and device parameters
            CPUTWindowCreationParams params;
            params.samples = 1;

            // create the window and device context
            result = pSample->CPUTCreateWindowAndContext(_L("CPUTWindow OpenGLES"), params);
            if (result != CPUT_SUCCESS)
                LOGI("Unable to create window");
        }
        else
        {
            LOGI("Window already created");
        }
        break;
    case APP_CMD_TERM_WINDOW:
        LOGI("APP_CMD_TERM_WINDOW");
        // Need clear window create and destroy calls
        // The window is being hidden or closed, clean it up.
        if (pSample->HasWindow())
        {
            pSample->DeviceShutdown();
        }
        break;
    case APP_CMD_GAINED_FOCUS:
        LOGI("APP_CMD_GAINED_FOCUS");
        break;
    case APP_CMD_LOST_FOCUS:
        LOGI("APP_CMD_LOST_FOCUS");
        break;
	case APP_CMD_WINDOW_RESIZED:
        LOGI("APP_CMD_WINDOW_RESIZED");
        break;
    }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state)
{
    // Make sure glue isn't stripped.
    app_dummy();

    // create an instance of my sample
    TessellationSample *pSample = new TessellationSample();
    if (!pSample)
    {
        LOGI("Failed to allocate TessellationSample");
        return;
    }

     // Assign the sample back into the app state
    state->userData = pSample;
    state->onAppCmd = cput_handle_cmd;
    state->onInputEvent = CPUT_OGL::cput_handle_input;


    // We make the assumption we are running from the executable's dir in
    // the CPUT SampleStart directory or it won't be able to use the relative paths to find the default
    // resources    
    cString ResourceDirectory;

    CPUTFileSystem::GetExecutableDirectory(&ResourceDirectory);

    // Different executable and assets locations on different OS'es.
    // Consistency should be maintained in all OS'es and API's.
    ResourceDirectory.append(GUI_LOCATION);

	// Initialize the system and give it the base CPUT resource directory (location of GUI images/etc)
    // For now, we assume it's a relative directory from the executable directory.  Might make that resource
    // directory location an env variable/hardcoded later
    CPUTWindowAndroid::SetAppState(state);
	pSample->CPUTInitialize(ResourceDirectory);

    CPUTFileSystem::GetExecutableDirectory(&ResourceDirectory);

    // Different executable and assets locations on different OS'es.
    // Consistency should be maintained in all OS'es and API's.
    ResourceDirectory.append(SYSTEM_LOCATION);
    CPUTAssetLibrary *pAssetLibrary = CPUTAssetLibrary::GetAssetLibrary();
    pAssetLibrary->SetSystemDirectoryName(ResourceDirectory);

    // start the main message loop
    pSample->CPUTMessageLoop();

    // cleanup resources
    SAFE_DELETE(pSample);
    pSample = NULL;

    state->userData = NULL;
}
//END_INCLUDE(all)
