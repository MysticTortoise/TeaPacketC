TP_add_impl_subdirectory(Assets CPPSTDFile)
TP_add_interface_subdirectory(Endianness)
TP_add_impl_subdirectory(Graphics Direct3D11)
TP_add_impl_subdirectory(Input GameInput)
TP_add_impl_subdirectory(Logging STDIO)
TP_add_interface_subdirectory(MacroUtils)
TP_add_impl_subdirectory(Memory CMem)
TP_add_impl_subdirectory(Random STDRandom)
TP_add_impl_subdirectory(System Windows)
TP_add_impl_subdirectory(Time STDChrono)
TP_add_interface_subdirectory(Types)
TP_add_impl_subdirectory(Window Windows)

add_library(TeaPacket_Bundle INTERFACE)
target_link_libraries(TeaPacket_Bundle INTERFACE
        TeaPacket_Assets_CPPSTDFile
        TeaPacket_Endianness_Base
        TeaPacket_Graphics_Direct3D11
        TeaPacket_Input_GameInput
        TeaPacket_Logging_STDIO
        TeaPacket_MacroUtils_Base
        TeaPacket_Memory_CMem
        TeaPacket_Random_STDRandom
        TeaPacket_System_Windows
        TeaPacket_Time_STDChrono
        TeaPacket_Types_Base
        TeaPacket_Window_Windows
)