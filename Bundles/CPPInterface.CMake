TP_add_interface_cpp_subdirectory(Assets)
TP_add_interface_cpp_subdirectory(Bundled)
TP_add_interface_cpp_subdirectory(Endianness)
TP_add_interface_cpp_subdirectory(Graphics)
TP_add_interface_cpp_subdirectory(Input)
TP_add_interface_cpp_subdirectory(Logging)
TP_add_interface_cpp_subdirectory(Random)
TP_add_interface_cpp_subdirectory(System)
TP_add_interface_cpp_subdirectory(Time)
TP_add_interface_cpp_subdirectory(Types)
TP_add_interface_cpp_subdirectory(Window)

add_library(TeaPacket_Bundle_CPP INTERFACE)
target_link_libraries(TeaPacket_Bundle_CPP INTERFACE
        TeaPacket_Assets_CPP
        TeaPacket_Bundled_CPP
        TeaPacket_Endianness_CPP
        TeaPacket_Graphics_CPP
        TeaPacket_Input_CPP
        TeaPacket_Logging_CPP
        TeaPacket_Random_CPP
        TeaPacket_System_CPP
        TeaPacket_Time_CPP
        TeaPacket_Types_CPP
        TeaPacket_Window_CPP
)