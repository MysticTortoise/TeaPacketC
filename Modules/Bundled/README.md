# Bundled Module
This Module is an Interface-Only module that simplifies initialization when using different modules.

It should generate two inline functions, `tp_bool TP_Bundled_Init(void)` and `void TP_Bundled_DeInit(void)`.

Each one should (de)initialize all TeaPacket modules added, in the correct order.