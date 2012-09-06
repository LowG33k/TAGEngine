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

#include <Core/Console.hpp>
#include <sstream>
#include <Debug/MemoryDebug.hpp>

namespace TAG
{
    namespace Core
    {

        IMPL_SINGLETON( Console )

        // See header file.
        Console::Console():
            m_currentCommand( ""),
            m_enable( true )
        {
            RegisterCommand( "?", Tools::Bind( &Console::GetHelp, *this ) );
        }

        // See header file.
        void Console::RegisterCommand( const std::string& command, const Tools::Functor& function )
        {
            m_commands[ command ] = function;
        }

        // See header file.
        void Console::SendChar( char character )
        {
            if( !m_enable )
                return;

            switch( character )
            {
                case '\n':
                case '\r':
                    if( !m_currentCommand.empty() )
                    {
                        ProcessCurrentCommand();
                        m_currentCommand.clear();
                    }
                    break;
                case '\b':
                    if( !m_currentCommand.empty() )
                        m_currentCommand.erase( m_currentCommand.size() - 1 );
                    break;
                default:
                    m_currentCommand += character;
                    break;
            }
        }

        // See header file.
        void Console::Enable( bool enable )
        {
            m_enable = enable;
        }

        // See header file.
        bool Console::IsEnabled( void ) const
        {
            return m_enable;
        }

        // See header file.
        void Console::ProcessCurrentCommand( void )
        {
            std::string command;
            std::istringstream iss( m_currentCommand );
            iss >> command;

            TCommandsTable::iterator it = m_commands.find( command );

            if( it != m_commands.end())
            {
                std::string args;
                std::getline( iss, args );

                std::cout << it->second( args ) << std::endl;
            }
            else
                std::cout << "\"" << command << "\" not found" << std::endl;
        }

        // See header file.
        std::string Console::GetHelp( void ) const
        {
            std::string list;

            for( TCommandsTable::const_iterator it = m_commands.begin(); it != m_commands.end(); ++it )
                list += it->first + "\n";//*/

            return list;
        }

    } // end namespace Core

} // end namespace TAG
