`task \[build/run\]` to run main files
`task \[build/run\]:example` to run example files

if `gl.o` does not exist or is corrupted, be sure to run `task build:glad` to generate GLAD library object files prior to running `task \[build/run\]`

`/glad` sub directory comes from https://github.com/Dav1dde/glad/wiki/C
this specific GLAD library was generated for OpenGL version 3.3 with --debug capabilities