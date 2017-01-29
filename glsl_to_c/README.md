#GLSL To C

Utility used in the compilation process of the main program.

Processes all OpenGL shader language files in the current directory and
combines them into a single c-header file.  This is to simplify sending the
shaders to the GPU and compiling them on the gpu.

##Usage

### glsl_to_c [output filename]  
 
##Output Filename
The [output filename] is parsed and converted to all caps with special
characters changed to underscores (_) and suffixed and prefixed with
underscores (_) for the precompiler definition.  For example, *shader.h* will
become _SHADER_H_ and be affixed to the #define and #ifndef precompiler
directives in the header file.

##Input filenames
The filenames for OpenGL shader files is important as well.  In order to follow
a convention, of sorts, filenames for glsl code should be as follows:  
### [name].[type].glsl 
