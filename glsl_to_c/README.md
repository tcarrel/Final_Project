#GLSL To C

Utility used in the compilation process of the main program.

Processes all OpenGL shader language files in the current directory and
combines them into a single c-header file.  This is to simplify sending the
shaders to the GPU and compiling them on the gpu.

##Usage

glsl_to_c [output filename]

