/*
 *
 * @file gen_flags_enum.h
 * @author Thomas R. Carrel
 *
 *
 */

# ifndef GEN_FLAGS_ENUM
# define GEN_FLAGS_ENUM
/** Macros are used for the 'enums' instead of proper C++ enums so that they
 * can be easily combined when passed into functions.
 */

/** Flags for generating Computed shaders.
 */
typedef unsigned long long int Com_gen_enum;

/** Flags for generating Vertex shaders.
 */
typedef unsigned long long int Ver_gen_enum;
#  define Vert_gen_enum_SIZE (sizeof(Vert_gen_enum))
#  define EMPTY_SHADER           ((Vert_gen_enum) 0)
#  define VERT_POSITION          ((Vert_gen_enum) 1)
#  define VERT_VERTEX_COLORING   ((Vert_gen_enum) 1<<1)
#  define VERT_VIEW_POSITION_UNI ((Vert_gen_enum) 1<<2)
#  define VERT_UNIFORM_SCALE     ((Vert_gen_enum) 1<<3)


/** Flags for generating Tesselation Control shaders.
 */
typedef unsigned long long int TCS_gen_enum;

/** Flags for generating Tesselation Evaluation shaders.
 */
typedef unsigned long long int TEV_gen_enum;

/** Flags for generating Geometry shaders.
 */
typedef unsigned long long int Geo_gen_enum;

/** Flags for generating Fragment shaders.
 */
typedef unsigned long long int Fra_gen_enum;
#endif
