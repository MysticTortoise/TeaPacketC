import sys

from cwriter import write_enum_file_interface
from cppconverter import write_enum_file_cpp
from parser import parse_enum_file

def generate_c(input_file, output_file):
    write_enum_file_interface(parse_enum_file(input_file), output_file)

def generate_cpp(input_file, output_file, og_file, namespace_removal):
    write_enum_file_cpp(parse_enum_file(input_file), output_file, og_file, namespace_removal)

if __name__ == "__main__":
    if sys.argv[1] == "cgen":
        generate_c(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == "cppgen":
        namespace_removal = int(sys.argv[5]) if len(sys.argv) > 5 else 0
        generate_cpp(sys.argv[2], sys.argv[3], sys.argv[4], namespace_removal)