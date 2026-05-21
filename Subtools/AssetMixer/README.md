# AssetMixer
AssetMixer is an asset-generation tool that ties into TeaPacket.

It's main use is changing assets based on platform-specific information. 
For example, Graphics Modules may use it to convert GLSL files into the target shader language.

## Usage
The main use of Asset Mixer is through the `TP_AM_BuildAssets` function provided in the Functions.CMake file.

An example usage of the function is as follows:
```cmake
TP_AM_BuildAssets(
        TARGET TeaPacket_TestPrograms_Graphics 
        SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/assets/" 
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/"
        PASSES ${TP_ASSET_MIXER_PASSES}
        REBUILD
        )
```
Arguments:
- TARGET defines the target that building these assets is connected to.
- SOURCE defines the source directory the assets should be drawn from.
- DESTINATION defines the destination directory the assets should be built into.
- PASSES is a list of Python scripts that modify the data. 
  - Use of the `TP_ASSET_MIXER_PASSES` CMake variable is reccomended as Modules may add to this variable.
- If REBUILD is specified, all assets will be rebuilt.

An example asset pass script is available in the `example_pass.py` file.
It will append "Hello, World!" to any `.txt` or `.text` file.