Contained within this folder is a bunch of useful .CMake files used throughout TeaPacket.

## CommonEnd.CMake
Should be `include()`ed at the end of most CMake files. Used for ensuring proper settings required for TeaPacket (i.e. warnings on)

## CommonFunctions.CMake
Can be `include()`ed anywhere in a CMake project. Includes many functions useful throughout this repo.

### add_subdirectory_no_overwrite()
Usage: `add_subdirectory_no_overwrite(Target, Subdirectory, InternalDir)`

Adds a subdirectory project to the current CMake build, but only if it has yet to be added.
- Target - The name of the target this subdirectory creates.
- Subdirectory - The path to the subdirectory to add if that target doesn't exist.
- InternalDir - The name of the internal directory used when this is an out-of-tree subdirectory.

### TP_get_interface_subdirectory()
Usage: `TP_get_interface_subdirectory(OutVariable, InterfaceName)`

Outputs the path of an Interface to a variable.
- OutVariable - The name of the variable to ouptut the Interface's path to.
- InterfaceName - The name of the interface whose subdirectory will be retrieved.

### TP_add_interface_subdirectory()
Usage: `TP_add_interface_subdirectory(ModuleName)`

Adds the given Module Interface as a CMake subdirectory.
- ModuleName - The name of the interface to add. This will result in `Modules/[InterfaceName]/Interface` being added.

### TP_add_interface_cpp_subdirectory()
Usage: `TP_add_interface_cpp_subdirectory(ModuleName)`

Adds the given Module Interface's C++ Wrapper as a CMake subdirectory.
- ModuleName - The name of the Interface to add the wrapper of.

### TP_add_impl_subdirectory()
Usage: `TP_add_impl_subdirectory(ModuleName, ImplementationName)`

Adds the given Module Implementation as a CMake subdirectory.
- ModuleName - The name of the Module whose implementation should be added.
- ImplementationName - The name of the implementation to add.

### TP_add_extension_subdirectory()
Usage: `TP_add_extension_subdirectory(ExtensionName)`

Adds the given Extension as a CMake subdirectory.
- ExtensionName - The name of the Extension whose implementation should be added.

### TP_add_bundle()
Usage: `TP_add_bundle(BundleName, Target)`

Adds a Bundle as a CMake subdirectory. See the Bundles folder for more info.
- BundleName - The name of the Bundle to add.
- Target - The target that this bundle should attach to.
  - Note that the bundle will not automatically link to the target. The Target parameter is used for other automatic actions (such as building in the correct format)

### TP_run_python_script()
Usage: `TP_run_python_script(Target, ScriptPath)`

Runs the Python script whenever a Target is built.
- Target - The name of the target to attach this script to.
- ScriptPath - The Python script to run.
#### TODO: Arguments?

## CommonTest.CMake
Was used for automated tests. Until those are re-implemented this has no purpose.

## CPPWrapperCommon.CMake
Should be `include()`ed at the end of every C++ wrapper CMakeLists.txt file. Contains everything those wrappers should all do.

## InterfaceCommon.CMake
Should be `include()`ed at the end of every Module Interface CMakeLists.txt file. Contains everything that Module Interfaces should do.