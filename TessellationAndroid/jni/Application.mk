APP_ABI        := armeabi-v7a x86
APP_STL        := stlport_static

#APP_PLATFORM - defines the API lvel of support needed
#by the App. The Platform specified in the manifest *should*
#match, but will stop the app running on older versions of 
#Android if too high.

#18 needed to pull in ES3 headers and libs
#APP_PLATFORM   := android-19
APP_PLATFORM   := android-18
#APP_PLATFORM   := android-14


#APP_GL_VERSION - Local define to specify the level of
#support required from CPUT.
#Options :
# GLES3
# GLES2
APP_GL_VERSION := GLES3
#APP_GL_VERSION := GLES2

#To run with ES3 functions but without an ES3 library
#ie. Intel platform Android 4.2 or earlier, set this to 1.
#All ES3 functions used in this mode should be wrapped with the
#ES3_COMPAT macro and defined in CPUT/CPUOGLES3Compat.h
APP_GL_COMPAT  := 0

#There might be a proper define for DEBUG builds
#But this enables debug prints etc in CPUT
CPUT_DEBUG      := 1


