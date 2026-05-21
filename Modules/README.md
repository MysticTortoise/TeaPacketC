# Modules
Modules are the core of TeaPacket. Each Module serves some sort of purpose in the engine.

Each Module at least has an Interface. This is the cross-platform, cross-language representation of what this module is capable of.
It should be header-only, with no source files. Inline functions are allowed but are typically discouraged.

Most Modules will also have many Implementations. Each one contains an implementation of everything the Interface declares.

## Interface-Only Modules
Not all modules will have implementations. Some of them are header-only Modules, with everything being inline in the header.
This is discouraged but is useful for anything that should be consistent across all implementations, such as types or general functionality.