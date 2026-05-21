# EnumGenerator
This Generator is used for generating enums.
Specifically, it is used for generating enums with a specific size that is not int.

# Usage
## Definition Files
Enums are defined via .enum files. 
A file begins with the name of the enum and the name of its base type, separated with a space.\
Every line after that can take two forms. \
If it is a single token with no spaces, it defines an enum and assigns it a default value.\
If it is a token, followed by an Equals sign (`=`) and a number value, it defines this to be the number's value.
This is assumed to be in decimal form, but other forms can be denoted using typical notation 
(only hex, via the `0x` prefix, is tested)

## Functions
As with all Generators, use of the Functions.CMake file is the preferred way to use it.

### TP_EnumGenerator
usage: `TP_EnumGenerator(SourceFilePath, DestFilePath, Target)`

Generates an enum file for usage in C.
- SourceFilePath - The path to the .enum file to use when generating.
- DestFilePath - The path to output the .h header defining the enum.
- Target - The name of the CMake target to bind the creation of this header to.

### TP_EnumGenerator_CPPWrap
usage: `TP_EnumGenerator_CPPWrap(SourceFilePath, DestFilePath, CPath, Target, NamespaceRemoval?)`

Generates an enum file for usage in C++.
- SourceFilePath - The path to the .enum file to use when generating.
- DestFilePath - The path to output the .hpp header defining the enum.
- CPath - The include path of the original header that this C++ enum maps to.
- Target - The name of the CMake target to bind the creation of this header to.
- NamespaceRemoval - OPTIONAL - If set, the namespace of the original will be collapsed
  - Example: NamespaceRemoval = 1 means 
    `TP_Graphics_Texture_Format` will become 
    `TeaPacket::Graphics::TextureFormat` instead of
    `TeaPacket::Graphics::Texture::Format`
  - This is used to avoid namespace-class collisions. It's a hack, but it works.