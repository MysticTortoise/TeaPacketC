# Bundles
Bundles are a way to automatically add Module Implementations for different targets. 
Useful for if you want to easily port your app with little setup for each platform.

To use a Bundle, use the `TP_add_bundle` function in `CMakeCommons/CommonFunctions.CMake` to add a bundle. 
You may override the modules you want to use by then setting `TP_Bundle_[NAME OF YOUR BUNDLE]_[NAME OF YOUR MODULE]Lib` 
to the name of the Module you want to use.

Then, you can call `TP_build_bundle` to create an `INTERFACE` library named `TeaPacket_[NAME OF YOUR BUNDLE]_Bundle`
to package all your modules into one linkable library.

You may optionally then call `TP_link_bundle` to link your bundle. This will also bind any bundle-specific functionality
to your target (such as creating the right format for your app when cross compiling).

The `Interface.CMake` and `CPPInterface.CMake` files expose their own interface libraries exposing all of the Module Interfaces and C++ Interface Wrappers respectively.
Use those if you need that, for whatever reason.