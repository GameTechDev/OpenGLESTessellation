# OpenGLESTessellation

Tessellation is a hardware feature that allows a graphics processing unit (GPU) to dynamically subdivide primitives. This feature also allows you to control new vertex placements.

One common use of tessellation is to dynamically scale the level of detail of a terrain based on the distance from the camera. This scaling maintains the visual fidelity of a highly triangulated terrain with great performance.

To support this technique, tessellation shaders were recently added to DirectX 11 and OpenGL 4.0. OpenGL ES does not have tessellation shaders yet, but Intel’s Bay Trail platform now has an extension that would allow for the use of tessellation shaders in OpenGL ES 3.0.

View full accompanying article at: https://software.intel.com/en-us/articles/tessellation-for-opengl-es-31-on-android
