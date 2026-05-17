from pathlib import Path

class EnumDefinition:
    name: str
    base_type: str
    values: dict[str, int]

def parse_enum_file(input_file: Path):
    with open(input_file, 'r') as f:
        enum_def = EnumDefinition()

        # Parse Header
        line = f.readline()
        broken = line.split()

        enum_def.name = broken[0]
        if len(broken) == 1:
            enum_def.base_type = "int"
        if len(broken) == 2:
            enum_def.base_type = broken[1]
        else:
            raise Exception("Too many parameters in header!!")

        enum_def.values = dict()

        # Parse lines
        for line in f:
            broken = line.split()

            name = broken[0]
            if len(broken) == 1:
                if len(enum_def.values) <= 0:
                    val = 0
                else:
                    val = list(enum_def.values.values())[-1] + 1
            elif len(broken) == 3:
                if broken[1] != "=":
                    raise Exception(f"Invalid character at line: {line}")
                val = int(broken[2], 0)
            else:
                raise Exception(f"Too many parameters in line: {line}")

            if name in enum_def.values:
                raise Exception(f"Duplicate listing of: {name}")

            enum_def.values[name] = val
    return enum_def