/**
 *
 * \file colors.cpp
 * \author Thomas R. Carrel
 *
 * \brief If it is desired/needed to be able to generate random colors and/or
 * to access them from an array, this file defines the necessary functions.
 *
 */

#include<cstdint>
#include<cstdlib>


#include "colors.h"
#include "random.h"


#ifdef COLOR_ARRAY

namespace Color
{
    /** An array of colors.
     */
    uint32_t Color_Array[] =
    {
        ABSOLUTE_ZERO,
        ACID_GREEN,
        AERO,
        AERO_BLUE,
        AFRICAN_VIOLET,
        AIR_FORCE_BLUE_RAF,
        AIR_FORCE_BLUE_USAF,
        AIR_SUPERIORITY_BLUE,
        ALABAMA_CRIMSON,
        ALABASTER,
        ALICE_BLUE,
        ALIEN_ARMPIT,
        ALIZARIN_CRIMSON,
        ALLOY_ORANGE,
        ALMOND,
        AMARANTH,
        AMARANTH_DEEP_PURPLE,
        AMARANTH_PINK,
        AMARANTH_PURPLE,
        AMARANTH_RED,
        AMAZON_STORE,
        AMAZONITE,
        AMBER,
        AMBER_SAE,
        AMERICAN_ROSE,
        AMETHYST,
        ANDROID_GREEN,
        ANTI_FLASH_WHITE,
        ANTIQUE_BRASS,
        ANTIQUE_BRONZE,
        ANTIQUE_FUCHSIA,
        ANTIQUE_RUBY,
        ANTIQUE_WHITE,
        AO_ENGLISH,
        APPLE_GREEN,
        APRICOT,
        AQUA,
        AQUAMARINE,
        ARCTIC_LIME,
        ARMY_GREEN,
        ARSENIC,
        ARTICHOKE,
        ARYLIDE_YELLOW,
        ASH_GRAY,
        ASPARAGUS,
        ATOMIC_TANGERINE,
        AUBURN,
        AUREOLIN,
        AUROMETALSAURUS,
        AVOCADO,
        AWESOME,
        AZTEC_GOLD,
        AZURE,
        AZURE_WEB,
        AZURE_MIST,
        AZUREISH_WHITE,
        BABY_BLUE,
        BABY_BLUE_EYES,
        BABY_PINK,
        BABY_POWDER,
        BAKER_MILLER_PINK,
        BALL_BLUE,
        BANANA_MANIA,
        BANANA_YELLOW,
        BANGLADESH_GREEN,
        BARBIE_PINK,
        BARN_RED,
        BATTERY_CHARGED_BLUE,
        BATTLESHIP_GRAY,
        BAZAAR,
        BEAU_BLUE,
        BEAVER,
        BEGONIA,
        BEIGE,
        B_DAZZLED_BLUE,
        BIG_DIP_O_RUBY,
        BIG_FOOT_FEET,
        BISQUE,
        BISTRE,
        BISTRE_BROWN,
        BITTER_LEMON,
        BITTER_LIME,
        BITTERSWEET,
        BITTERSWEET_SHIMMER,
        BLACK,
        BLACK_BEAN,
        BLACK_CORAL,
        BLACK_LEATHER_JACKET,
        BLACK_OLIVE,
        BLACK_SHADOWS,
        BLANCHED_ALMOND,
        BLAST_OFF_BRONZE,
        BLEU_DE_FRANCE,
        BLIZZARD_BLUE,
        BLOND,
        BLUE,
        BLUE_CRAYOLA,
        BLUE_MUNSELL,
        BLUE_NCS,
        BLUE_PANTONE,
        BLUE_PIGMENT,
        BLUE_RYB,
        BLUE_BELL,
        BLUE_BOLT,
        BLUE_GRAY,
        BLUE_GREEN,
        BLUE_JEANS,
        BLUE_LAGOON,
        BLUE_MAGENTA_VIOLET,
        BLUE_SAPPHIRE,
        BLUE_VIOLET,
        BLUE_YONDER,
        BLUEBERRY,
        BLUEBONNET,
        BLUSH,
        BOLE,
        BONDI_BLUE,
        BONE,
        BOOGER_BUSTER,
        BOSTON_UNIVERSITY_RED,
        BOTTLE_GREEN,
        BOYSENBERRY,
        BRANDEIS_BLUE,
        BRASS,
        BRICK_RED,
        BRIGHT_CERULEAN,
        BRIGHT_GREEN,
        BRIGHT_LAVENDER,
        BRIGHT_LILAC,
        BRIGHT_MAROON,
        BRIGHT_NAVY_BLUE,
        BRIGHT_PINK,
        BRIGHT_TURQUOISE,
        BRIGHT_UBE,
        BRIGHT_YELLOW_CRAYOLA,
        BRILLIANT_AZURE,
        BRILLIANT_LAVENDER,
        BRILLIANT_ROSE,
        BRINK_PINK,
        BRITISH_RACING_GREEN,
        BRONZE,
        BRONZE_YELLOW,
        BROWN_TRADITIONAL,
        BROWN_WEB,
        BROWN_NOSE,
        BROWN_SUGAR,
        BROWN_YELLOW,
        BRUNSWICK_GREEN,
        BUBBLE_GUM,
        BUBBLES,
        BUD_GREEN,
        BUFF,
        BULGARIAN_ROSE,
        BURGUNDY,
        BURLYWOOD,
        BURNISHED_BROWN,
        BURNT_ORANGE,
        BURNT_SIENNA,
        BURNT_UMBER,
        BUTTON_BLUE,
        BYZANTINE,
        BYZANTIUM,
        CADET,
        CADET_BLUE,
        CADET_GREY,
        CADMIUM_GREEN,
        CADMIUM_ORANGE,
        CADMIUM_RED,
        CADMIUM_YELLOW,
        CAFE_AU_LAIT,
        CAFE_NOIR,
        CAL_POLY_POMONA_GREEN,
        CAMBRIDGE_BLUE,
        CAMEL,
        CAMEO_PINK,
        CAMOUFLAGE_GREEN,
        CANARY,
        CANARY_YELLOW,
        CANDY_APPLE_RED,
        CANDY_PINK,
        CAPRI,
        CAPUT_MORTUUM,
        CARDINAL,
        CARIBBEAN_GREEN,
        CARMINE,
        CARMINE_M_P,
        CARMINE_PINK,
        CARMINE_RED,
        CARNATION_PINK,
        CARNELIAN,
        CAROLINA_BLUE,
        CARROT_ORANGE,
        CASTLETON_GREEN,
        CATALINA_BLUE,
        CATAWBA,
        CEDAR_CHEST,
        CEIL,
        CELADON,
        CELADON_BLUE,
        CELADON_GREEN,
        CELESTE,
        CELESTIAL_BLUE,
        CERISE,
        CERISE_PINK,
        CERULEAN,
        CERULEAN_BLUE,
        CERULEAN_FROST,
        CG_BLUE,
        CG_RED,
        CHAMOISEE,
        CHAMPAGNE,
        CHAMPAGNE_PINK,
        CHARCOAL,
        CHARLESTON_GREEN,
        CHARM_PINK,
        CHARTREUSE_TRADITIONAL,
        CHARTREUSE_WEB,
        CHERRY,
        CHERRY_BLOSSOM_PINK,
        CHESTNUT,
        CHINA_PINK,
        CHINA_ROSE,
        CHINESE_RED,
        CHINESE_VIOLET,
        CHLOROPHYLL_GREEN,
        CHOCOLATE_TRADITIONAL,
        CHOCOLATE_WEB,
        CHROME_YELLOW,
        CINEREOUS,
        CINNABAR,
        CINNAMON, //**
        CINNAMON_SATIN,
        CITRINE,
        CITRON,
        CLARET,
        CLASSIC_ROSE,
        COBALT_BLUE,
        COCOA_BROWN,
        COCONUT,
        COFFEE,
        COLUMBIA_BLUE,
        CONGO_PINK,
        COOL_BLACK,
        COOL_GREY,
        COPPER,
        COPPER_CRAYOLA,
        COPPER_PENNY,
        COPPER_RED,
        COPPER_ROSE,
        COQUELICOT,
        CORAL,
        CORAL_PINK,
        CORAL_RED,
        CORAL_REEF,
        CORDOVAN,
        CORN,
        CORNELL_RED,
        CORNFLOWER_BLUE,
        CORNSILK,
        COSMIC_COBALT,
        COSMIC_LATTE,
        COYOTE_BROWN,
        COTTON_CANDY,
        CREAM,
        CRIMSON,
        CRIMSON_GLORY,
        CRIMSON_RED,
        CULTURED,
        CYAN,
        CYAN_AZURE,
        CYAN_BLUE_AZURE,
        CYAN_COBALT_BLUE,
        CYAN_CORNFLOWER_BLUE,
        CYAN_PROCESS,
        CYBER_GRAPE,
        CYBER_YELLOW,
        CYCLAMEN,
        DAFFODIL,
        DANDELION,
        DARK_BLUE,
        DARK_BLUE_GRAY,
        DARK_BROWN,
        DARK_BROWN_TANGELO,
        DARK_BYZANTIUM,
        DARK_CANDY_APPLE_RED,
        DARK_CERULEAN,
        DARK_CHESTNUT,
        DARK_CORAL,
        DARK_CYAN,
        DARK_ELECTRIC_BLUE,
        DARK_GOLDENROD,
        DARK_GRAY_X11,
        DARK_GREEN,
        DARK_GREEN_X11,
        DARK_GUNMETAL,
        DARK_IMPERIAL_BLUE0,
        DARK_IMPERIAL_BLUE1,
        DARK_JUNGLE_GREEN,
        DARK_KHAKI,
        DARK_LAVA,
        DARK_LAVENDER,
        DARK_LIVER,
        DARK_LIVER_HORSES,
        DARK_MAGENTA,
        DARK_MEDIUM_GRAY,
        DARK_MIDNIGHT_BLUE,
        DARK_MOSS_GREEN,
        DARK_OLIVE_GREEN,
        DARK_ORANGE,
        DARK_ORCHID,
        DARK_PASTEL_BLUE,
        DARK_PASTEL_GREEN,
        DARK_PASTEL_PURPLE,
        DARK_PASTEL_RED,
        DARK_PINK,
        DARK_POWDER_BLUE,
        DARK_PUCE,
        DARK_PURPLE,
        DARK_RASPBERRY,
        DARK_RED,
        DARK_SALMON,
        DARK_SCARLET,
        DARK_SEA_GREEN,
        DARK_SIENNA,
        DARK_SKY_BLUE,
        DARK_SLATE_BLUE,
        DARK_SLATE_GRAY,
        DARK_SPRING_GREEN,
        DARK_TAN,
        DARK_TANGERINE,
        DARK_TAUPE,
        DARK_TERRA_COTTA,
        DARK_TURQUOISE,
        DARK_VANILLA,
        DARK_VIOLET,
        DARK_YELLOW,
        DARTMOUTH_GREEN,
        DAVYS_GRAY,
        DEBIAN_RED,
        DEEP_AQUAMARINE,
        DEEP_CARMINE,
        DEEP_CARMINE_PINK,
        DEEP_CARROT_ORANGE,
        DEEP_CERISE,
        DEEP_CHAMPAGNE,
        DEEP_CHESTNUT,
        DEEP_COFFEE,
        DEEP_FUCHSIA,
        DEEP_GREEN,
        DEEP_GREEN_CYAN_TURQUOISE,
        DEEP_JUNGLE_GREEN,
        DEEP_KOAMARU,
        DEEP_LEMON,
        DEEP_LILAC,
        DEEP_MAGENTA,
        DEEP_MAROON,
        DEEP_MAUVE,
        DEEP_MOSS_GREEN,
        DEEP_PEACH,
        DEEP_PINK,
        DEEP_PUCE,
        DEEP_RED,
        DEEP_RUBY,
        DEEP_SAFFRON,
        DEEP_SKY_BLUE,
        DEEP_SPACE_SPARKLE,
        DEEP_SPRING_BUD,
        DEEP_TAUPE,
        DEEP_TUSCAN_RED,
        DEEP_VIOLET,
        DEER,
        DENIM,
        DENIM_BLUE,
        DESATURATED_CYAN,
        DESERT,
        DESERT_SAND,
        DESIRE,
        DIAMOND,
        DIM_GRAY,
        DINGY_DUNGEON,
        DIRT,
        DODGER_BLUE,
        DODIE_YELLOW,
        DOGWOOD_ROSE,
        DOLLAR_BILL,
        DOLPHIN_GRAY,
        DONKEY_BROWN,
        DRAB,
        DUKE_BLUE,
        DUST_STORM,
        DUTCH_WHITE,
        EARTH_YELLOW,
        EBONY,
        ECRU,
        EERIE_BLACK,
        EGGPLANT,
        EGGSHELL,
        EGYPTIAN_BLUE,
        ELECTRIC_BLUE,
        ELECTRIC_CRIMSON,
        ELECTRIC_CYAN,
        ELECTRIC_GREEN,
        ELECTRIC_INDIGO,
        ELECTRIC_LAVENDER,
        ELECTRIC_LIME,
        ELECTRIC_PURPLE,
        ELECTRIC_ULTRAMARINE,
        ELECTRIC_VIOLET,
        ELECTRIC_YELLOW,
        EMERALD,
        EMINENCE,
        ENGLISH_GREEN,
        ENGLISH_LAVENDER,
        ENGLISH_RED,
        ENGLISH_VERMILLION,
        ENGLISH_VIOLET,
        ETON_BLUE,
        EUCALYPTUS,
        FALLOW,
        FALU_RED,
        FANDANGO,
        FANDANGO_PINK,
        FASHION_FUCHSIA,
        FAWN,
        FELDGRAU,
        FELDSPAR,
        FERN_GREEN,
        FERRARI_RED,
        FIELD_DRAB,
        FIERY_ROSE,
        FIREBRICK,
        FIRE_ENGINE_RED,
        FLAME,
        FLAMINGO_PINK,
        FLATTERY,
        FLAVESCENT,
        FLAX,
        FLIRT,
        FLORAL_WHITE,
        FLOURESCENT_ORANGE,
        FLOURESCENT_PINK,
        FLOURESCENT_YELLOW,
        FOLLY,
        FOREST_GREEN_TRADITIONAL,
        FOREST_GREEN_WEB,
        FRENCH_BEIGE,
        FRENCH_BISTRE,
        FRENCH_BLUE,
        FRENCH_FUCHSIA,
        FRENCH_LILAC,
        FRENCH_LIME,
        FRENCH_MAUVE,
        FRENCH_PINK,
        FRENCH_PLUM,
        FRENCH_PUCE,
        FRENCH_RASPBERRY,
        FRENCH_ROSE,
        FRENCH_SKY_BLUE,
        FRENCH_VIOLET,
        FRENCH_WINE,
        FRESH_AIR,
        FROGERT,
        FUCHSIA,
        FUCHSIA_CRAYOLA,
        FUCHSIA_PINK,
        FUCHSIA_PURPLE,
        FUCHSIA_ROSE,
        FULVOUS,
        FUZZY_WUZZY,
        GAINSBORO,
        GAMBOGE,
        GAMBOGE_ORANGE,
        GARGOYLE_GAS,
        GENERIC_VIRIDIAN,
        GHOST_WHITE,
        GIANTS_CLUB,
        GIANTS_ORANGE,
        GINGER,
        GLAUCOUS,
        GLITTER,
        GLOSSY_GRAPE,
        GO_GREEN,
        GOLD_METALLIC,
        GOLD_WEB,
        GOLD_FUSION,
        GOLDEN_BROWN,
        GOLDEN_POPPY,
        GOLDEN_YELLOW,
        GOLDENROD,
        GRANITE_GRAY,
        GRANNY_SMITH_APPLE,
        GRAPE,
        GRAY,
        GRAY_X11,
        GRAY_ASPARAGUS,
        GRAY_BLUE,
        GREEN,
        GREEN_CRAYOLA,
        GREEN_HTML,
        GREEN_MUNSELL,
        GREEN_NCS,
        GREEN_PANTONE,
        GREEN_PIGMENT,
        GREEN_RYB,
        GREEN_BLUE,
        GREEN_CYAN,
        GREEN_LIZARD,
        GREEN_SHEEN,
        GREEN_YELLOW,
        GRIZZLY,
        GRULLO,
        GUPPIE_GREEN,
        GUNMETAL,
        HALAYA_UBE,
        HAN_BLUE,
        HAN_PURPLE,
        HANSA_YELLOW,
        HARLEQUIN,
        HARLEQUIN_GREEN,
        HARVARD_CRIMSON,
        HARVEST_GOLD,
        HEART_GOLD,
        HEAT_WAVE,
        HEIDELBERG_RED,
        HELIOTROPE,
        HELIOTROPE_GRAY,
        HELIOTROPE_MAGENTA,
        HOLLYWOOD_CERISE,
        HONEYDEW,
        HONOLULU_BLUE,
        HOOKERS_GREEN,
        HOT_MAGENTA,
        HOT_PINK,
        HUNTER_GREEN,
        ICEBERG,
        ICTERINE,
        IGUANA_GREEN,
        ILLUMINATING_EMERALD,
        IMPERIAL,
        IMPERIAL_BLUE,
        IMPERIAL_PURPLE,
        IMPERIAL_RED,
        INCHWORM,
        INDEPENDENCE,
        INDIA_GREEN,
        INDIAN_RED,
        INDIAN_YELLOW,
        INDIGO,
        INDIGO_DYE,
        INDIGO_WEB,
        INFRA_RED,
        INTERDIMENSIONAL_BLUE,
        INTERNATIONAL_KLEIN_BLUE,
        INTERNATIONAL_ORANGE_AEROSPACE,
        INTERNATIONAL_ORANGE_ENGINEERING,
        INTERNATIONAL_ORANGE_GOLDEN_GATE_BRIDGE,
        IRIS,
        IRRESISTIBLE,
        ISABELLINE,
        ISLAMIC_GREEN,
        ITALIAN_SKY_BLUE,
        IVORY,
        JADE,
        JAPANESE_CARMINE,
        JAPANESE_INDIGO,
        JAPANESE_VIOLET,
        JASMINE,
        JASPER,
        JAZZBERRY_JAM,
        JELLY_BEAN,
        JET,
        JONQUIL,
        JORDY_BLUE,
        JUNE_BUD,
        JUNGLE_GREEN,
        KELLY_GREEN,
        KENYAN_COPPER,
        KEPPEL,
        KEY_LIME,
        KHAKI,
        KHAKI_X11,
        KIWI,
        KOBE,
        KOBI,
        KOBICHA,
        KOMBU_GREEN,
        KSU_PURPLE,
        KU_CRIMSON,
        LA_SALLE_GREEN,
        LANGUID_LAVENDER,
        LAPIS_LAZULI,
        LASER_LEMON,
        LAUREL_GREEN,
        LAVA,
        LAVENDER,
        LAVENDER_FLORAL,
        LAVENDER_BLUE,
        LAVENDER_BLUSH,
        LAVENDER_GRAY,
        LAVENDER_INDIGO,
        LAVENDER_MAGENTA,
        LAVENDER_PINK,
        LAVENDER_PURPLE,
        LAVENDER_ROSE,
        LAWN_GREEN,
        LEMON,
        LEMON_CHIFFON,
        LEMON_CURRY,
        LEMON_GLACIER,
        LEMON_LIME,
        LEMON_MERINGUE,
        LEMON_YELLOW,
        LICORICE,
        LIBERTY,
        LIGHT_APRICOT,
        LIGHT_BLUE,
        LIGHT_BROWN,
        LIGHT_CARMINE_PINK,
        LIGHT_COBALT_BLUE,
        LIGHT_CORAL,
        LIGHT_CORNFLOWER_BLUE,
        LIGHT_CRIMSON,
        LIGHT_CYAN,
        LIGHT_DEEP_PINK,
        LIGHT_FRENCH_BEIGE,
        LIGHT_FUCHSIA_PINK,
        LIGHT_GOLDENROD_YELLOW,
        LIGHT_GRAY,
        LIGHT_GRAYISH_MAGENTA,
        LIGHT_GREEN,
        LIGHT_HOT_PINK,
        LIGHT_MEDIUM_ORCHID,
        LIGHT_MOSS_GREEN,
        LIGHT_ORANGE,
        LIGHT_ORCHID,
        LIGHT_PASTEL_PURPLE,
        LIGHT_PINK,
        LIGHT_RED_OCHRE,
        LIGHT_SALMON,
        LIGHT_SALMON_PINK,
        LIGHT_SEA_GREEN,
        LIGHT_SKY_BLUE,
        LIGHT_SLATE_GRAY,
        LIGHT_STEEL_BLUE,
        LIGHT_TAUPE,
        LIGHT_THULIAN_PINK,
        LIGHT_YELLOW,
        LILAC,
        LILAC_LUSTER,
        LIME,
        LIME_GREEN,
        LIMERICK,
        LINCOLN_GREEN,
        LINEN,
        LOEEN,
        LISERAN_PURPLE,
        LITTLE_BOY_BLUE,
        LIVER,
        LIVER_DOGS,
        LIVER_ORGAN,
        LIVER_CHESTNUT,
        LIVID,
        LUMBER,
        LUST,
        MAASTRICHT_BLUE,
        MACARONI_AND_CHEESE,
        MADDER_LAKE,
        MAGENTA,
        MAGENTA_CRAYOLA,
        MAGENTA_DYE,
        MAGENTA_PANTONE,
        MAGENTA_PROCESS,
        MAGENTA_HAZE,
        MAGENTA_PINK,
        MAGIC_MINT,
        MAGIC_POTION,
        MAGNOLIA,
        MAHOGANY,
        MAJORELLE_BLUE,
        MALACHITE,
        MANATEE,
        MANDARIN,
        MANGO_TANGO,
        MANTIS,
        MARDI_GRAS,
        MARIGOLD,
        MAROON,
        MAROON_CRAYOLA,
        MAROON_X11,
        MAUVE,
        MAUVE_TAUPE,
        MAUVELOUS,
        MAXIMUM_BLUE,
        MAXIMUM_BLUE_GREEN,
        MAXIMUM_BLUE_PURPLE,
        MAXIMUM_GREEN,
        MAXIMUM_GREEN_YELLOW,
        MAXIMUM_PURPLE,
        MAXIMUM_RED,
        MAXIMUM_RED_PURPLE,
        MAXIMUM_YELLOW,
        MAXIMUM_YELLOW_RED,
        MAY_GREEN,
        MAYA_BLUE,
        MEAT_BROWN,
        MEDIUM_AQUAMARINE,
        MEDIUM_BLUE,
        MEDIUM_CANDY_APPLE_RED,
        MEDIUM_CARMINE,
        MEDIUM_CHAMPAGNE,
        MEDIUM_ELECTRIC_BLUE,
        MEDIUM_JUNGLE_GREEN,
        MEDIUM_LAVENDER_MAGENTA,
        MEDIUM_ORCHID,
        MEDIUM_PERSIAN_BLUE,
        MEDIUM_PURPLE,
        MEDIUM_RED_VIOLET,
        MEDIUM_RUBY,
        MEDIUM_SEA_GREEN,
        MEDIUM_SKY_BLUE,
        MEDIUM_SLATE_BLUE,
        MEDIUM_SPRING_BUD,
        MEDIUM_SPRING_GREEN,
        MEDIUM_TAUPE,
        MEDIUM_TURQUOISE,
        MEDIUM_TUSCAN_RED,
        MEDIUM_VERMILION,
        MEDIUM_VIOLET_RED,
        MELLOW_APRICOT,
        MELLOW_YELLOW,
        MELON,
        METALLIC_SEAWEED,
        METALLIC_SUNBURST,
        MEXICAN_PINK,
        MIDDLE_BLUE,
        MIDDLE_BLUE_GREEN,
        MIDDLE_BLUE_PURPLE,
        MIDDLE_RED_PURPLE,
        MIDDLE_GREEN,
        MIDDLE_GREEN_YELLOW,
        MIDDLE_PURPLE,
        MIDDLE_RED,
        MIDDLE_YELLOW,
        MIDDLE_YELLOW_RED,
        MIDNIGHT,
        MIDNIGHT_BLUE,
        MIDNIGHT_GREEN,
        MIKADO_YELLOW,
        MILK,
        MIMI_PINK,
        MINDARO,
        MING,
        MINION_YELLOW,
        MINT,
        MINT_CREAM,
        MINT_GREEN,
        MISTY_MOSS,
        MISTY_ROSE,
        MOCCASIN,
        MODE_BEIGE,
        MOONSTONE_BLUE,
        MORDANT_RED_19,
        MORNING_BLUE,
        MOSS_GREEN,
        MOUNTAIN_MEADOW,
        MOUNTBATTEN_PINK,
        MSU_GREEN,
        MUGHAL_GREEN,
        MULBERRY,
        MUMMYS_TOMB,
        MUSTARD,
        MYRTLE_GREEN,
        MYSTIC,
        MYSTIC_MAROON,
        NADESHIKO_PINK,
        NAPIER_GREEN,
        NAPLES_YELLOW,
        NAVAJO_WHITE,
        NAVY,
        NAVY_PURPLE,
        NEON_CARROT,
        NEON_FUCHSIA,
        NEON_GREEN,
        NEW_CAR,
        NEW_YORK_PINK,
        NICKEL,
        NON_PHOTO_BLUE,
        NORTH_TEXAS_GREEN,
        NYANZA,
        OCEAN_BLUE,
        OCEAN_BOAT_BLUE,
        OCEAN_GREEN,
        OCHRE,
        OFFICE_GREEN,
        OGRE_ODOR,
        OLD_BURGUNDY,
        OLD_GOLD,
        OLD_HELIOTROPE,
        OLD_LACE,
        OLD_LAVENDER,
        OLD_MAUVE,
        OLD_MOSS_GREEN,
        OLD_ROSE,
        OLD_SILVER,
        OLIVE,
        OLIVE_DRAB_NO3,
        OLIVE_DRAB_NO7,
        OLIVINE,
        ONYX,
        OPERA_MAUVE,
        ORANGE,
        ORANGE_CRAYOLA,
        ORANGE_PANTONE,
        ORANGE_RYB,
        ORANGE_WEB,
        ORANGE_PEEL,
        ORANGE_RED,
        ORANGE_SODA,
        ORANGE_YELLOW,
        ORCHID,
        ORCHID_PINK,
        ORIOLES_ORANGE,
        OUTER_SPACE,
        OUTRAGEOUS_ORANGE,
        OXFORD_BLUE,
        OU_CRIMSON_RED,
        PACIFIC_BLUE,
        PAKISTAN_GREEN,
        PALATINATE_BLUE,
        PALATINATE_PURPLE,
        PALE_AQUA,
        PALE_BLUE,
        PALE_BROWN,
        PALE_CARMINE,
        PALE_CERULEAN,
        PALE_CHESTNUT,
        PALE_COPPER,
        PALE_CORNFLOWER_BLUE,
        PALE_CYAN,
        PALE_GOLD,
        PALE_GOLDENROD,
        PALE_GREEN,
        PALE_LAVENDER,
        PALE_MAGENTA,
        PALE_MAGENTA_PINK,
        PALE_RED_VIOLET,
        PALE_ROBIN_EGG_BLUE,
        PALE_SILVER,
        PALE_SPRING_BUD,
        PALE_TAUPE,
        PALE_TURQUOISE,
        PALE_VIOLET,
        PALE_VIOLET_RED,
        PALM_LEAF,
        PANSY_PURPLE,
        PAOLO_VERONESE_GREEN,
        PAPAYA_WHIP,
        PARADISE_PINK,
        PARIS_GREEN,
        PARROT_PINK,
        PASTEL_BLUE,
        PASTEL_BROWN,
        PASTEL_GRAY,
        PASTEL_GREEN,
        PASTEL_MAGENTA,
        PASTEL_ORANGE,
        PASTEL_PINK,
        PASTEL_PURPLE,
        PASTEL_RED,
        PASTEL_VIOLET,
        PASTEL_YELLOW,
        PATRIARCH,
        PAYNES_GRAY,
        PEACH_1,
        PEACH_2,
        PEACH_ORANGE,
        PEACH_PUFF,
        PEACH_YELLOW,
        PEAR,
        PEARL,
        PEARL_AQUA,
        PEARLY_PURPLE,
        PERIDOT,
        PERIWINKLE,
        PERMANENT_GERANIUM_LAKE,
        PERSIAN_BLUE,
        PERSIAN_GREEN,
        PERSIAN_INDIGO,
        PERSIAN_ORANGE,
        PERSIAN_PINK,
        PERSIAN_PLUM,
        PERSIAN_RED,
        PERSIAN_ROSE,
        PERSIMMON,
        PERU,
        PEWTER_BLUE,
        PHLOX,
        PHTHALO_BLUE,
        PHTHALO_GREEN,
        PICTON_BLUE,
        PICTORIAL_CARMINE,
        PIGGY_PINK,
        PINE_GREEN,
        PINEAPPLE,
        PINK,
        PINK_PANTONE,
        PINK_FLAMINGO,
        PINK_LACE,
        PINK_LAVENDER,
        PINK_ORANGE,
        PINK_PEARL,
        PINK_RASPBERRY,
        PINK_SHERBET,
        PISTACHIO,
        PIXIE_POWDER,
        PLATINUM,
        PLUM,
        PLUMP_PURPLE,
        POLISHED_PINE,
        POMP_AND_POWER,
        POPSTAR,
        PORTLAND_ORANGE,
        POWDER_BLUE,
        PRINCESS_PERFUME,
        PRINCETON_ORANGE,
        PRUSSIAN_BLUE,
        PUCE,
        PUCE_RED,
        PULLMAN_BROWN,
        PULLMAN_GREEN,
        PUMPKIN,
        PURPLE_MUNSELL,
        PURPLE_X11,
        PURPLE_HEART,
        PURPLE_MOUNTAIN_MAJESTY,
        PURPLE_NAVY,
        PURPLE_PIZZAZZ,
        PURPLE_PLUM,
        PURPLE_TAUPE,
        PURPUREUS,
        QUARTZ,
        QUEEN_BLUE,
        QUEEN_PINK,
        QUICK_SILVER,
        QUINACRIDONE_MAGENTA,
        RACKLEY,
        RADICAL_RED,
        RAISIN_BLACK,
        RAJAH,
        RASPBERRY,
        RASPBERRY_GLACE,
        RASPBERRY_PINK,
        RASPBERRY_ROSE,
        RAW_SIENNA,
        RAW_UMBER,
        RAZZLE_DAZZLE_ROSE,
        RAZZMATAZZ,
        RAZZMIC_BERRY,
        REBECCA_PURPLE,
        RED,
        RED_CRAYOLA,
        RED_MUNSELL,
        RED_NCS,
        RED_PANTONE,
        RED_PIGMENT,
        RED_RYB,
        RED_BROWN,
        RED_DEVIL,
        RED_ORANGE,
        RED_PURPLE,
        RED_SALSA,
        RED_VIOLET,
        REDWOOD,
        REGALIA,
        RESOLUTION_BLUE,
        RHYTHM,
        RICH_BLACK,
        RICH_BLACK_FOGRA29,
        RICH_BLACK_FOGRA39,
        RICH_BRILLIANT_LAVENDER,
        RICH_CARMINE,
        RICH_ELECTRIC_BLUE,
        RICH_LAVENDER,
        RICH_LILAC,
        RICH_MAROON,
        RIFLE_GREEN,
        ROAST_COFFEE,
        ROBIN_EGG_BLUE,
        ROCKET_METALLIC,
        ROMAN_SILVER,
        ROSE,
        ROSE_BONBON,
        ROSE_DUST,
        ROSE_EBONY,
        ROSE_GOLD,
        ROSE_MADDER,
        ROSE_PINK,
        ROSE_QUARTZ,
        ROSE_RED,
        ROSE_TAUPE,
        ROSE_VALE,
        ROSEWOOD,
        ROSSO_CORSA,
        ROSY_BROWN,
        ROYAL_AZURE,
        ROYAL_BLUE_1,
        ROYAL_BLUE_2,
        ROYAL_FUCHSIA,
        ROYAL_PURPLE,
        ROYAL_YELLOW,
        RUBER,
        RUBINE_RED,
        RUBY,
        RUBY_RED,
        RUDDY,
        RUDDY_BROWN,
        RUDDY_PINK,
        RUFOUS,
        RUSSET,
        RUSSIAN_GREEN,
        RUSSIAN_VIOLET,
        RUST,
        RUSTY_RED,
        SACRAMENTO_STATE_GREEN,
        SADDLE_BROWN,
        SAFETY_ORANGE,
        BLAZE_ORANGE,
        SAFETY_YELLOW,
        SAFFRON,
        SAGE,
        ST_PATRICKS_BLUE,
        SALMON,
        SALMON_PINK,
        SAND,
        SAND_DUNE,
        SANDSTORM,
        SANDY_BROWN,
        SANDY_TAN,
        SANGRIA,
        SAP_GREEN,
        SAPPHIRE,
        SAPPHIRE_BLUE,
        SASQUATCH_SOCKS,
        SATIN_SHEEN_GOLD,
        SCARLET_1,
        SCARLET_2,
        SCHAUSS_PINK,
        SCHOOL_BUS_YELLOW,
        SCREAMIN_GREEN,
        SEA_BLUE,
        SEA_FOAM_GREEN,
        SEA_GREEN,
        SEA_SERPENT,
        SEAL_BROWN,
        SEASHELL,
        SELECTIVE_YELLOW,
        SEPIA,
        SHADOW,
        SHADOW_BLUE,
        SHAMPOO,
        SHAMROCK_GREEN,
        SHEEN_GREEN,
        SHIMMERING_BLUSH,
        SHINY_SHAMROCK,
        SHOCKING_PINK,
        SHOCKING_PINK_CRAYOLA,
        SIENNA,
        SILVER,
        SILVER_CHALICE,
        SILVER_LAKE_BLUE,
        SILVER_PINK,
        SILVER_SAND,
        SINOPIA,
        SIZZLING_RED,
        SIZZLING_SUNRISE,
        SKOBELOFF,
        SKY_BLUE,
        SKY_MAGENTA,
        SLATE_BLUE,
        SLATE_GRAY,
        SLIMY_GREEN,
        SMASHED_PUMPKIN,
        SMITTEN,
        SMOKE,
        SMOKEY_TOPAZ,
        SMOKY_BLACK,
        SMOKY_TOPAZ,
        SNOW,
        SOAP,
        SOLID_PINK,
        SONIC_SILVER,
        SPARTAN_CRIMSON,
        SPACE_CADET,
        SPANISH_BISTRE,
        SPANISH_BLUE,
        SPANISH_CARMINE,
        SPANISH_CRIMSON,
        SPANISH_GRAY,
        SPANISH_GREEN,
        SPANISH_ORANGE,
        SPANISH_PINK,
        SPANISH_RED,
        SPANISH_SKY_BLUE,
        SPANISH_VIOLET,
        SPANISH_VIRIDIAN,
        SPICY_MIX,
        SPIRO_DISCO_BALL,
        SPRING_BUD,
        SPRING_FROST,
        SPRING_GREEN,
        STAR_COMMAND_BLUE,
        STEEL_BLUE,
        STEEL_PINK,
        STEEL_TEAL,
        STIL_DE_GRAIN_YELLOW,
        STIZZA,
        STORMCLOUD,
        STRAW,
        STRAWBERRY,
        SUGAR_PLUM,
        SUNBURNT_CYCLOPS,
        SUNGLOW,
        SUNNY,
        SUNRAY,
        SUNSET,
        SUNSET_ORANGE,
        SUPER_PINK,
        SWEET_BROWN,
        TAN,
        TANGELO,
        TANGERINE,
        TANGERINE_YELLOW,
        TANGO_PINK,
        TART_ORANGE,
        TAUPE,
        TAUPE_GRAY,
        TEA_GREEN,
        TEA_ROSE_1,
        TEA_ROSE_2,
        TEAL,
        TEAL_BLUE,
        TEAL_DEER,
        TEAL_GREEN,
        TELEMAGENTA,
        TAWNY,
        TERRA_COTTA,
        THISTLE,
        THULIAN_PINK,
        TICKLE_ME_PINK,
        TIFFANY_BLUE,
        TIGERS_EYE,
        TIMBERWOLF,
        TITANIUM_YELLOW,
        TOMATO,
        TOOLBOX,
        TOPAZ,
        TRACTOR_RED,
        TROLLEY_GRAY,
        TROPICAL_RAIN_FOREST,
        TROPICAL_VIOLET,
        TRUE_BLUE,
        TUFTS_BLUE,
        TULIP,
        TUMBLEWEED,
        TURKISH_ROSE,
        TURQUOISE,
        TURQUOISE_BLUE,
        TURQUOISE_GREEN,
        TURQUOISE_SURF,
        TURTLE_GREEN,
        TUSCAN,
        TUSCAN_BROWN,
        TUSCAN_RED,
        TUSCAN_TAN,
        TUSCANY,
        TWILIGHT_LAVENDER,
        TYRIAN_PURPLE,
        UA_BLUE,
        UA_RED,
        UBE,
        UCLA_BLUE,
        UCLA_GOLD,
        UFO_GREEN,
        ULTRAMARINE,
        ULTRAMARINE_BLUE,
        ULTRA_PINK,
        ULTRA_RED,
        UMBER,
        UNBLEACHED_SILK,
        UN_BLUE,
        UNIVERSITY_OF_CALIFORNIA_GOLD,
        UNMELLOW_YELLOW,
        UP_FOREST_GREEN,
        UP_MAROON,
        UPSDELL_RED,
        UROBILIN,
        USAFA_BLUE,
        USC_CARDINAL,
        USC_GOLD,
        UTK_ORANGE,
        UTAH_CRIMSON,
        VAN_DYKE_BROWN,
        VANILLA,
        VANILLA_ICE,
        VEGAS_GOLD,
        VENETIAN_RED,
        VERDIGRIS,
        VERMILION_1,
        VERMILION_2,
        VERONICA,
        VERY_LIGHT_AZURE,
        VERY_LIGHT_BLUE,
        VERY_LIGHT_MALACHITE_GREEN,
        VERY_LIGHT_TANGELO,
        VERY_PALE_ORANGE,
        VERY_PALE_YELLOW,
        VIOLET,
        VIOLET_COLOR_WHEEL,
        VIOLET_RYB,
        VIOLET_WEB,
        VIOLET_BLUE,
        VIOLET_RED,
        VIRIDIAN,
        VIRIDIAN_GREEN,
        VISTA_BLUE,
        VIVID_AMBER,
        VIVID_AUBURN,
        VIVID_BURGUNDY,
        VIVID_CERISE, 
        VIVID_CERULEAN,
        VIVID_CRIMSON,
        VIVID_GAMBOGE,
        VIVID_LIME_GREEN,
        VIVID_MALACHITE,
        VIVID_MULBERRY,
        VIVID_ORANGE,
        VIVID_ORANGE_PEEL,
        VIVID_ORCHID,
        VIVID_RASPBERRY,
        VIVID_RED,
        VIVID_RED_TANGELO,
        VIVID_SKY_BLUE,
        VIVID_TANGELO,
        VIVID_TANGERINE,
        VIVID_VERMILION,
        VIVID_VIOLET,
        VIVID_YELLOW,
        VOLT,
        WAGENINGEN_GREEN,
        WARM_BLACK,
        WATERSPOUT,
        WELDON_BLUE,
        WENGE,
        WHEAT,
        WHITE,
        WHITE_SMOKE,
        WILD_BLUE_YONDER,
        WILD_ORCHID,
        WILD_STRAWBERRY,
        WILD_WATERMELON,
        WILLPOWER_ORANGE,
        WINDSOR_TAN,
        WINE,
        WINE_DREGS,
        WINTER_SKY,
        WINTER_WIZARD,
        WINTERGREEN_DREAM,
        WISTERIA,
        WOOD_BROWN,
        XANADU,
        YALE_BLUE,
        YANKEES_BLUE,
        YELLOW,
        YELLOW_CRAYOLA,
        YELLOW_MUNSELL,
        YELLOW_NCS,
        YELLOW_PANTONE,
        YELLOW_PROCESS,
        YELLOW_RYB,
        YELLOW_GREEN,
        YELLOW_ORANGE,
        YELLOW_ROSE,
        YELLOW_SUNSHINE,
        ZAFFRE,
        ZINNWALDITE_BROWN,
        ZOMP
    };

# define NUM_COLORS (1301 - 16)

    /** Returns and random color.
     * @return A random color.
     */
    uint32_t random_color()
    {
        return Color_Array[ get_rand( NUM_COLORS ) ];
    }

} //Color namespace.

#endif
