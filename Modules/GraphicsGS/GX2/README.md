This implementation of the Graphics Module uses GX2 on Wii U as a backend.
It assumes compilation with the WUT devkitPro toolchain. 

Shader compilation requires CafeGLSL to be installed on the target Wii U. 

TODO: Remove that dependency?

## Remarks
This is one of the few platforms that requires endian swapping for Shader Buffer data!! 
Make sure you do so if you want things to run smoothly.