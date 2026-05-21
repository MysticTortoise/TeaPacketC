# Endianness Module
This Module is an Interface-Only module that handles endianness and endian-swapping.

It contains functions for endian-swapping different types. These should work on most typical C90 compliant platforms.
If possible, it will also try and use platform-specific extensions to speed up this swapping.