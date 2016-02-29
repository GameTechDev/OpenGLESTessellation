Android port of CPUT
====================
Initial port done by Jon Kennedy, Oct 2013, 
    based on the CPUT_Linux port.

Current Status (10/09/2013)
==============
This port expects ES3 support on the target,  either  natively (ie. >= Android
4.3) or via  function  pointers  and an ES2 library (< Android  4.3). Pure ES2
support will need further work, but look in the Application.mk file to set the
appropriate defines.

Enough of the port was done to get the basic CPUT Sample up and running on
Android. It is based on the Android Native Activity so has no Java
implementation.

All art assets should be in the /assets folder. This will ensure that they are
built into the APK and installed on the device.

The port only  supports DDS  compressed  textures at present, but it should be
trivial to add further support.

The following is not currently implemented :
    GUI
    Text
    Sprites
    RenderTargets
    PostProcessing
    
Much could be done to tidy up the port, but this should be  considered as part
of a CPUT re-factor in general.

The input handling in the jni could could be made common and moved into CPUT?

The file reading code could be  consolidated  further - currently  there are 2
implementations (istream style implementation and ReadFileContents()).

The full android life cycle is not fully supported at the moment. CPUT needs
modifying to support the android requests to start/stop the app and to
open/close a window. There is also the possibility to save data when the app
is backgrounded - we could save the per frame constants here?

The event processing loop needs modifying so that CPUT knows when it no longer
has focus and it will block on receiving an event, rather than polling.


Build Requirements
==================
Install the latest Android SDK and NDK.
    http://developer.android.com/sdk/index.html
    http://developer.android.com/tools/sdk/ndk/index.html

I used the adt bundle - adt-bundle-linux-x86_64-20130917 and version r9 of the
ndk.

Add the NDK and SDK to your path :
    export PATH=$ANDROID_NDK/:$ANDROID_SDK/tools/:$PATH

To Build - cd to your sample folder
========
1. First time only, you may need to initialise your project :
    android update project -p . -s -t android-18 -n SampleCPUTActivity

2. Build the NDK component :
    ndk-build
    
3. Build the APK
    ant debug
    
4. Install the APK
    adb install -r ./bin/SampleCPUTActivity-debug.apk

5. Run it.

To Interact with the Sample
===========================
1. Use the mouse or touch to rotate the camera. No support has been added to
move the position of the camera.

2. Use a keyboard :
    a/d - strafe left/right
    w/s - move forwards/back
    q/e - move up/down

    <space> + a/d/w/s - rotate the camera
    

