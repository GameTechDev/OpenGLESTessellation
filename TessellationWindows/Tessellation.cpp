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

#include "Tessellation.h"
#include "CPUTRenderStateBlockOGL.h"
#include "CPUTGuiControllerOGL.h"
#include "CPUTTextureOGL.h"
#include "CPUTFont.h"

#define BUTTON_UP 1000
#define BUTTON_FW 1001
#define BUTTON_DN 1002
#define BUTTON_LT 1003
#define BUTTON_RT 1004
#define BUTTON_BK 1005
#define CAMERA_BUTTON_SIZE 20


const UINT SHADOW_WIDTH_HEIGHT = 2048;

// set file to open
cString g_OpenFilePath;
cString g_OpenShaderPath;
cString g_OpenFileName;
std::string g_OpenSceneFileName;

static bool TessellationEnabled = true;
static float MaxTessellation = 16.0f;
static bool DemoMode = true;

const cString WINDOW_TITLE = _L("OpenGL Tessellation");

#ifdef CPUT_OS_LINUX
const cString GUI_DIR = _L("../Media/gui_assets/");
const cString SYSTEM_DIR = _L("../Media/System/");
const cString MEDIA_DIR = _L("../Media/Geartower/");
const std::string DEFAULT_SCENE = "../Media/defaultscene.scene";
#else
const cString GUI_DIR = _L("../../../Media/gui_assets/");
const cString SYSTEM_DIR = _L("../../../Media/System/");
const cString MEDIA_DIR = _L("../../../Media/");
const std::string DEFAULT_SCENE = "../../../Media/defaultscene.scene";
#endif

// Windows entry point. Calls standard main()
//-----------------------------------------------------------------------------

int main( int argc, char **argv );
#ifdef CPUT_OS_WINDOWS
#include <stdlib.h>
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    // Prevent unused parameter compiler warnings
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(nCmdShow);

    return main(__argc, __argv);
}
#endif
// Application entry point.  Execution begins here.
//-----------------------------------------------------------------------------
int main( int argc, char **argv )
{
#ifdef DEBUG
    // tell VS to report leaks at any exit of the program
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    //http://msdn.microsoft.com/en-us/library/x98tx3cf%28v=vs.100%29.aspx
	//Add a watch for “{,,msvcr100d.dll}_crtBreakAlloc” to the watch window
	//Set the value of the watch to the memory allocation number reported by your sample at exit.
	//Note that the “msvcr100d.dll” is for MSVC2010.  Other versions of MSVC use different versions of this dl; you’ll need to specify the appropriate version.

#endif
    CPUTResult result=CPUT_SUCCESS;
    int returnCode=0;

    // create an instance of my sample
    TessellationSample *pSample = new TessellationSample();
    
    // We make the assumption we are running from the executable's dir in
    // the CPUT SampleStart directory or it won't be able to use the relative paths to find the default
    // resources    
    cString ResourceDirectory;

    CPUTFileSystem::GetExecutableDirectory(&ResourceDirectory);

    // Different executable and assets locations on different OS'es.
    // Consistency should be maintained in all OS'es and API's.
    ResourceDirectory.append(GUI_DIR);

	// Initialize the system and give it the base CPUT resource directory (location of GUI images/etc)
    // For now, we assume it's a relative directory from the executable directory.  Might make that resource
    // directory location an env variable/hardcoded later
    pSample->CPUTInitialize(ResourceDirectory);

    CPUTFileSystem::GetExecutableDirectory(&ResourceDirectory);

    // Different executable and assets locations on different OS'es.
    // Consistency should be maintained in all OS'es and API's.
    ResourceDirectory.append(SYSTEM_DIR);
    CPUTAssetLibrary *pAssetLibrary = CPUTAssetLibrary::GetAssetLibrary();
    pAssetLibrary->SetSystemDirectoryName(ResourceDirectory);


    // window and device parameters
    CPUTWindowCreationParams params;
    params.samples = 1;
    params.windowWidth = 1280;
    params.windowHeight = 720;
    
    // parse out the parameter settings or reset them to defaults if not specified
    std::string AssetFilename;

    g_OpenSceneFileName = "../../../Media/defaultscene.scene";

    result = pSample->CPUTCreateWindowAndContext(WINDOW_TITLE, params);
    ASSERT( CPUTSUCCESS(result), _L("CPUT Error creating window and context.") );

    returnCode = pSample->CPUTMessageLoop();
    pSample->ReleaseResources();
    pSample->DeviceShutdown();

    // cleanup resources
    SAFE_DELETE(pSample);

    return returnCode;
}

void APIENTRY openglCallbackFunction(GLenum source,
                                           GLenum type,
                                           GLuint id,
                                           GLenum severity,
                                           GLsizei length,
                                           const GLchar* message,
                                           void* userParam){
 
    std::cout << "---------------------opengl-callback-start------------" << std::endl;
    std::cout << "message: "<< message << std::endl;
    std::cout << "type: ";
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "OTHER";
        break;
    }
    std::cout << std::endl;
 
    std::cout << "id: " << id << std::cout << "severity: ";
    switch (severity){
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "HIGH";
        break;
    }
    std::cout << std::endl;
    std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}

// Handle OnCreation events
//-----------------------------------------------------------------------------
void TessellationSample::Create()
{    
    glDebugMessageCallback(openglCallbackFunction, NULL);

    CPUTAssetLibrary *pAssetLibrary = CPUTAssetLibrary::GetAssetLibrary();

#ifdef ENABLE_GUI
    cString ExecutableDirectory;
    CPUTFileSystem::GetExecutableDirectory(&ExecutableDirectory);
    // Different executable and assets locations on different OS'es.
    // Consistency should be maintained in all OS'es and API's.
    pAssetLibrary->SetMediaDirectoryName(  ExecutableDirectory + MEDIA_DIR);

    CPUTGuiControllerOGL *pGUI = (CPUTGuiControllerOGL*)CPUTGetGuiController();
    cString mediaDirectory = pAssetLibrary->GetMediaDirectoryName();
    CPUTFont *pFont = CPUTFont::CreateFont(mediaDirectory + _L("System/Font/"), _L("arial_64.fnt"));

    pGUI->SetFont(pFont);


    //
    // Create some controls
    //   
     pGUI->CreateButton(_L("Demo Mode    "), ID_TOGGLE_DEMOMODE, ID_MAIN_PANEL, NULL);
     pGUI->CreateButton(_L("Tessellation    "), ID_TESSELLATION_BUTTON, ID_MAIN_PANEL, NULL);
     pGUI->CreateButton(_L("Wireframe       "), ID_WIREFRAME_BUTTON, ID_MAIN_PANEL, NULL);
     pGUI->CreateButton(_L("+ Tessellation "), ID_INCREASE_TESSELLATION, ID_MAIN_PANEL, NULL);
     pGUI->CreateButton(_L("- Tessellation  "), ID_DECREASE_TESSELLATION, ID_MAIN_PANEL, NULL);
#endif
    // load shadow casting material+sprite object
    CPUTMaterial::mGlobalProperties.AddValue( _L("_Shadow"), _L("$shadow_depth") );

    
    int width, height;
    mpWindow->GetClientDimensions(&width, &height);

    CPUTTextureOGL*  pDepthTexture = (CPUTTextureOGL*)CPUTTextureOGL::CreateTexture(_L("$shadow_depth"), GL_DEPTH_COMPONENT, SHADOW_WIDTH_HEIGHT, SHADOW_WIDTH_HEIGHT, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
    mpShadowRenderTarget = new CPUTFramebufferOGL(NULL, pDepthTexture);
    SAFE_RELEASE(pDepthTexture);


    // Call ResizeWindow() because it creates some resources that our blur material needs (e.g., the back buffer)	
    ResizeWindow(width, height);

	mpScene = new CPUTScene();
    
    if (!g_OpenFilePath.empty())
    {
        CPUTAssetSet *pAssetSet = NULL;
        pAssetLibrary->SetMediaDirectoryName( g_OpenFilePath );
        pAssetSet        = pAssetLibrary->GetAssetSet( g_OpenFileName );
        mpScene->AddAssetSet(pAssetSet);
        pAssetSet->Release();
    } else {
        if (CPUTFAILED(mpScene->LoadScene(g_OpenSceneFileName))) {
            CPUTAssetSet *pAssetSet = NULL;
            g_OpenFilePath = _L("../../../Media/Teapot/");
            g_OpenFileName = _L("Teapot");
            cString wd;
            CPUTFileSystem::GetWorkingDirectory(&wd);

            pAssetLibrary->SetMediaDirectoryName( g_OpenFilePath );
            pAssetSet        = pAssetLibrary->GetAssetSet( g_OpenFileName );
            mpScene->AddAssetSet(pAssetSet);
            pAssetSet->Release();
        }
    }

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
    
    if (mpCamera == NULL) {
        mpCamera = new CPUTCamera();
        pAssetLibrary->AddCamera( _L(""), _L("SampleStart Camera"),_L(""),  mpCamera );

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
    mpShadowCamera->SetPosition( sceneCenterPoint - float3(0, -1, 0) * length );
    mpShadowCamera->LookAt( sceneCenterPoint );
    mpShadowCamera->SetWidth( length*2);
    mpShadowCamera->SetHeight(length*2);
    mpShadowCamera->Update();

    pAssetLibrary->AddCamera( _L("ShadowCamera"), _L(""), _L(""), mpShadowCamera );
    mpCameraController = new CPUTCameraControllerFPS();
    mpCameraController->SetCamera(mpCamera);
    mpCameraController->SetLookSpeed(0.004f);
    mpCameraController->SetMoveSpeed(7500.0f);

    mpDebugSprite = CPUTSprite::CreateSprite( -1.0f, -1.0f, 0.5f, 0.5f, _L("%Sprite") );

    // Skybox
    pAssetLibrary->SetMediaDirectoryName(  ExecutableDirectory + MEDIA_DIR);
    //mpSkyBoxMaterial = pAssetLibrary->GetMaterial( _L("skybox") );

	mpSkyBoxSprite = (CPUTSpriteOGL*)CPUTSprite::CreateSprite( -1.0f, -1.0f, 2.0f, 2.0f, _L("skybox") );
    //mpSkyBoxMaterial->Release();
    mpSkyBoxSprite->GetMesh()->SetNumVertices(1);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}


//-----------------------------------------------------------------------------
void TessellationSample::Update(double deltaSeconds)
{
    mpCameraController->Update((float)deltaSeconds);
    
    if(DemoMode) {
        float3 vec = mpCamera->GetPosition();
        float3x3 m = float3x3RotationY((float)deltaSeconds/5.0f);
        vec = m * vec;
        mpCamera->SetPosition(vec);
        mpCamera->LookAt(float3(-16000,4000,17000));
    }
}

// Handle keyboard events
//-----------------------------------------------------------------------------
CPUTEventHandledCode TessellationSample::HandleKeyboardEvent(CPUTKey key, CPUTKeyState state)
{
    static bool panelToggle = false;
    CPUTEventHandledCode    handled = CPUT_EVENT_UNHANDLED;
    cString fileName;

    switch(key)
    {
    case KEY_ESCAPE:
        handled = CPUT_EVENT_HANDLED;
        DestroyWindow(mpWindow->GetHWnd());
        break;
    }

    // pass it to the camera controller
    if(handled == CPUT_EVENT_UNHANDLED)
    {
        if (mpCameraController) {
            handled = mpCameraController->HandleKeyboardEvent(key, state);
        }
    }
    return handled;
}


// Handle mouse events
//-----------------------------------------------------------------------------
CPUTEventHandledCode TessellationSample::HandleMouseEvent(int x, int y, int wheel, CPUTMouseState state)
{
    if( mpCameraController )
    {
        return mpCameraController->HandleMouseEvent(x, y, wheel, state);
    }
    return CPUT_EVENT_UNHANDLED;
}

// Handle any control callback events
//-----------------------------------------------------------------------------
void TessellationSample::HandleCallbackEvent( CPUTEventID Event, CPUTControlID ControlID, CPUTControl *pControl )
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(pControl);
    if(Event == CPUT_EVENT_DOWN && ControlID == ID_TESSELLATION_BUTTON)
        TessellationEnabled = !TessellationEnabled;
    else if(Event == CPUT_EVENT_DOWN && ControlID == ID_WIREFRAME_BUTTON)
    {            
        CPUTMaterial* material = CPUTAssetLibrary::GetAssetLibrary()->GetMaterialByName(_L("terrain.mtl"));
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
}

// Handle resize events
//-----------------------------------------------------------------------------
void TessellationSample::ResizeWindow(UINT width, UINT height)
{
    CPUTGuiControllerOGL *pGUI = (CPUTGuiControllerOGL*)CPUTGetGuiController();
    pGUI->Resize();
}

//-----------------------------------------------------------------------------
void TessellationSample::Render(double deltaSeconds)
{
    CPUTRenderParameters renderParams;
    
    renderParams.mpCamera = mpShadowCamera;
    renderParams.mpShadowCamera = mpShadowCamera;
    renderParams.mpPerFrameConstants = mpPerFrameConstantBuffer;
    renderParams.mpPerModelConstants = mpPerModelConstantBuffer;
    renderParams.mpCamera = mpCamera;

    if(TessellationEnabled)
        UpdatePerFrameConstantBuffer(renderParams, MaxTessellation);
    else
        UpdatePerFrameConstantBuffer(renderParams, 1);

    int width, height;
    mpWindow->GetClientDimensions(&width, &height);
    GL_CHECK(glViewport(0, 0, width, height ));
    GL_CHECK(glClearColor ( 0.0, 0.5, 1, 1 ));
    GL_CHECK(glClearDepthf(0.0f));
    GL_CHECK(glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ));

    mpSkyBoxSprite->DrawSprite(renderParams);
    mpScene->Render( renderParams);	
    
    if(mpCameraController->GetCamera() == mpShadowCamera)
    {
        mpDebugSprite->DrawSprite(renderParams);
    }
    
#ifdef ENABLE_GUI
    CPUTDrawGUI();
#endif
}

void TessellationSample::ReleaseResources()
{
    // Note: these two are defined in the base.  We release them because we addref them.
    SAFE_RELEASE(mpCamera);

    SAFE_RELEASE(mpAssetSet);
    SAFE_RELEASE(mpShadowCamera);
    SAFE_DELETE( mpCameraController );
    SAFE_DELETE( mpDebugSprite);
    SAFE_RELEASE(mpShadowCameraSet);
    SAFE_DELETE( mpShadowRenderTarget );
    SAFE_DELETE( mpScene );
    SAFE_DELETE( mpSkyBoxSprite );
}
