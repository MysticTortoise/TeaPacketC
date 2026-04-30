TP_add_interface_subdirectory(Assets)
TP_add_interface_subdirectory(Endianness)
TP_add_interface_subdirectory(Graphics)
TP_add_interface_subdirectory(Input)
TP_add_interface_subdirectory(Logging)
TP_add_interface_subdirectory(MacroUtils)
TP_add_interface_subdirectory(Memory)
TP_add_interface_subdirectory(Random)
TP_add_interface_subdirectory(System)
TP_add_interface_subdirectory(Time)
TP_add_interface_subdirectory(Types)
TP_add_interface_subdirectory(Window)

add_library(TeaPacket_Bundle_Interface INTERFACE)
target_link_libraries(TeaPacket_Bundle_Interface INTERFACE
        TeaPacket_Assets_Base
        TeaPacket_Endianness_Base
        TeaPacket_Graphics_Base
        TeaPacket_Input_Base
        TeaPacket_Logging_Base
        TeaPacket_MacroUtils_Base
        TeaPacket_Memory_Base
        TeaPacket_Random_Base
        TeaPacket_System_Base
        TeaPacket_Time_Base
        TeaPacket_Types_Base
        TeaPacket_Window_Base
)