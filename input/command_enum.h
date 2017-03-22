/**
 *
 * \file command_enum.h
 * \author Thomas R. Carrel
 *
 * \brief Adds an enumerated type to distinguish commands.
 *
 */




#ifndef  _COMMAND_ENUM_H_
# define _COMMAND_ENUM_H_


namespace Input
{

    /** An enumeration representing all possible commands.
     */
    enum Commands_Enum{
        WINDOW_SHOW_COMMAND, ///< Window given focus.
        EXIT_COMMAND, ///< Exit 
        SCREENSHOT_COMMAND, ///< Screenshot
        NULL_COMMAND, ///< Null Object
        ALL_COMMANDS   ///< Qty
    };

} //Input namespace.

#endif
