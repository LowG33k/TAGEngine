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
#include <Utilities/Singleton.hpp>
#include <Utilities/Functor.hpp>

namespace TAG
{

    class TAG_API Console : public TAG::Tools::Singleton< Console >
    {
        MAKE_SINGLETON( Console )
        public:
            Console();
            void RegisterCommand( const std::string& command, const Tools::Functor& function );
            void SendChar( char character );
            void Enable( bool enable = true );
            bool IsEnabled( void ) const;

        private:
            std::string GetHelp() const;
            void ProcessCurrentCommand();
            typedef std::map< std::string, Tools::Functor > TCommandsTable;

            TCommandsTable m_commands;
            std::string m_currentCommand;
            bool m_enable;

    };

}

#endif // CONSOLE_HPP
