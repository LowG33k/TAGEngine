/*
 * Copyright (c) 2012 Loïc Marchand - loic.marchand73@gmail.com
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will
 * the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial applications,
 * and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original
 * software. If you use this software in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original
 * software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <Config/Config.hpp>
#include <map>
#include <string>
#include <Tools/Singleton.hpp>
#include <Tools/Functor.hpp>

namespace TAG
{

    namespace Core
    {

        /// \brief Console is a command interpreter
        /// ////////////////////////////////////////////////
        class TAG_API Console : public TAG::Tools::Singleton< Console >
        {
            MAKE_SINGLETON( Console )
            public:
                /// \brief Default constructor.
                /// ////////////////////////////////////////////////
                Console( void );

                /// \brief Register new command
                ///
                /// \param command Command identifiant.
                /// \brief function The function, used Bind for add function.
                /// ////////////////////////////////////////////////
                void RegisterCommand( const std::string& command, const Tools::Functor& function );

                /// \brief Use for send a character to the console.
                ///
                /// You can send a character by network, by a shell, or a graphical console
                ///
                /// \param character The new character
                /// ////////////////////////////////////////////////
                void SendChar( char character );

                /// \brief Activate/Deactivate the console.
                ///
                /// \param enable True for activate the console, false also.
                /// ////////////////////////////////////////////////
                void Enable( bool enable = true );

                /// \brief Get if console is enabled.
                ///
                /// \return If console is enabled.
                /// ////////////////////////////////////////////////
                bool IsEnabled( void ) const;

            private:
                /// \brief Used for display console help.
                ///
                /// \return Return all command
                /// ////////////////////////////////////////////////
                std::string GetHelp( void ) const;

                /// \brief Treat current command
                /// ////////////////////////////////////////////////
                void ProcessCurrentCommand( void );

                /// \brief Shortcut for a functor table
                /// ////////////////////////////////////////////////
                typedef std::map< std::string, Tools::Functor > TCommandsTable;

                TCommandsTable m_commands; ///< Conserve all commands
                std::string m_currentCommand; ///< The current line
                bool m_enable; ///< Conserve if console is enable.

        };

    } // end namespace Core

} // end namespace TAG

#endif // CONSOLE_HPP
