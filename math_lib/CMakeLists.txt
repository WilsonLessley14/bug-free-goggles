# TODO 14: Remove mysqrt.cxx from the list of sources

# TODO 1: Add a library called MathFunctions sources MathFunctions.cxx
# and mysqrt.cxx -- read source files, see how your existing math_lib files fit into this pattern
# Hint: You will need the add_library command

# TODO 7: Create a variable USE_MYMATH using option and set default to ON

# TODO 8: If USE_MYMATH is ON, use target_compile_definitions to pass
# USE_MYMATH as a precompiled definition to our source files

# TODO 12: When USE_MYMATH is ON, add a library for SqrtLibrary with
# source mysqrt.cxx

# TODO 13: When USE_MYMATH is ON, link SqrtLibrary to the MathFunctions Library
