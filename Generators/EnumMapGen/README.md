# EnumMapGen
This Generator is used for mapping one enum to another.

# Usage
## Definition Files
Enum mappings are defined via .gmap files.
.gmap files are command-like, with each line beginning with a keyword to denote a command.

### Destination
Format: `Destination [Path]`

Sets the output path of this file.
- Path - The output path that this file will generate to. This will be placed in the project's `include` directory.

### Namespaces
Format: `Namespaces [Namespace...]`

DEPRECATED DO NOT USE(?)

### Enum
Format: `Enum [Name] (Alias [EnumAlias])?`

Defines an enum to convert between.
- Name - The name of the enum.
- EnumAlias - The alias of the enum. Used for shortening the function names.

### Headers
Format: `Headers [Header...]`

Defines headers to be included in the generated file.
- Header - Each space-separated token is the exact string to place after an `#include` directive at the top of the generated file.
  - Include all quotes and angle brackets.

### Data / End
Format: 
```
Data
First_Enum_A Second_Enum_A
First_Enum_B Second_Enum_B
...
End
```

Defines how the enums map to one another. 
The Data command marks the beginning of this block,
while the End command marks the end of it.

Each line is a sequence of space-separated tokens defining how each enum maps to one another.
The order of the tokens should match the order the enums are defined in (via the `Enum` command)

### Default
Format: `Default [DefaultValues...]`

Defines a default value if no conversion is possible.
- DefaultValues - A list of space-separated tokens defining the default value for each enum.
Like the Data segment, the order of these tokens must match the order the enums are defined in.

This command should not be used if the Error command is used.

### Error
Format: `Error [Message...]`

Defines the error message to be set if no conversion is possible.
- Message - The message to print if no conversion is possible. Can be as long as you want. 
  - The message will automatically be wrapped in quotes so make sure it has no characters that interfere with that.

This command should not be used if the Default command is used. 

## Functions
As with all Generators, use of the Functions.CMake file is the preferred way to use it.

### TP_EnumMapGen
usage: `TP_EnumMapGen(SourceFilePath, Target)`

Generates an enum conversion file for usage in C++.
- SourceFilePath - The path to the .gmap file to use when generating.
- Target - The name of the CMake target to bind the creation of this file to.

# TODO
This should probably also have a way to generate C90 compatible headers.
This hasn't been needed so far so it hasn't been made, but when the time comes it should be.

Preferably don't remove the C++ support as `constexpr` is nice. Just have a way to do either C or C++