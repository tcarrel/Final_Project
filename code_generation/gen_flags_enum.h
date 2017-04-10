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

/** Underlying type for Computer shader options enum.
 */
typedef unsigned long long int Com_gen_enum;
/** Flags for generating Computed shaders.
 */
# define Com_gen_enum_SIZE          (sizeof(Com_gen_enum))
# define COM_EMPTY_SHADER           ((Com_gen_enum) 0)

/** Underlying type for Vertex shader options enum.
 */
typedef unsigned long long int Ver_gen_enum;
/** Flags for generating Vertex shaders.
 */
# define Ver_gen_enum_SIZE          (sizeof(Vert_gen_enum))
# define VER_EMPTY_SHADER           ((Ver_gen_enum) 0)
# define VER_POSITION               ((Ver_gen_enum) 1)
# define VER_VERTEX_COLORING        ((Ver_gen_enum) 1<<1)
# define VER_VIEW_POSITION_UNI      ((Ver_gen_enum) 1<<2)
# define VER_UNIFORM_SCALE          ((Ver_gen_enum) 1<<3)

/** Underlying type for Tesselation Control shader options enum.
 */
typedef unsigned long long int TCS_gen_enum;
/** Flags for generating Tesselation Control shaders.
 */
# define TCS_gen_enum_SIZE          (sizeof(TCS_gen_enum))
# define TCS_EMPTY_SHADER           ((TCS_gen_enum) 0)

/** Underlying type for Tesselation Evaluation shader options enum.
 */
typedef unsigned long long int TEV_gen_enum;
/** Flags for generating Tesselation Evaluation shaders.
 */
# define TEV_gen_enum_SIZE          (sizeof(TEV_gen_enum))
# define TEV_EMPTY_SHADER           ((TEV_gen_enum) 0)

/** Underlying type for Geometry shader options enum.
 */
typedef unsigned long long int Geo_gen_enum;
/** Flags for generating Geometry shaders.
 */
# define Geo_gen_enum_SIZE          (sizeof(Geo_gen_enum))
# define GEO_EMPTY_SHADER           ((Geo_gen_enum) 0)

/** Underlying type for Fragment shader options enum.
 */
typedef unsigned long long int Fra_gen_enum;
/** Flags for generating Fragment shaders.
 */
# define Fra_gen_enum_SIZE          (sizeof(Fra_gen_enum))
# define FRA_EMPTY_SHADER           ((Fra_gen_enum) 0)

#endif
