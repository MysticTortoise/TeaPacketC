# Bundles
Bundles are a way to automatically add Module Implementations for different targets. 
Useful for if you want to easily port your app with little setup for each platform.

To use a Bundle, use the `TP_add_bundle` function in `CMakeCommons/CommonFunctions.CMake`. 
Then, link the `TeaPacket_Bundle` INTERFACE target to your app. This should give you all of the implentations any given platform supports.

The `Interface.CMake` and `CPPInterface.CMake` files expose their own interface libraries exposing all of the Module Interfaces and C++ Interface Wrappers respectively.
Use those if you need that, for whatever reason.