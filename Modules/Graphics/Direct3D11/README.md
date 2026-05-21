This implementation of the Graphics Module uses Direct3D11 as a backend. 
It assumes compilation with MSVC and the existence of d3d11.lib and D3DCompiler.lib as built-in libraries.

An AssetMixer pass is provided to convert GLSL shaders to HLSL shaders. Conversion is NOT done manually by the Module itself.
This pass is appended to the TP_ASSET_MIXER_PASSES CMake variable.