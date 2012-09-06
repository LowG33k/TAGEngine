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

#include <Core/TAGApplication.hpp>
#include <iostream>
#include <Debug/LoggerFile.hpp>

#include <Debug/MemoryDebug.hpp>

namespace TAG
{

    namespace Core
    {

        IMPL_SINGLETON( TAGApplication )

        TAGApplication::TAGApplication( void ) :
            m_console( Console::GetInstance() ),
            m_running( true )
        {
            Debug::ILogger::SetLogger( new Debug::LoggerFile() );

            m_console.RegisterCommand( "min", Tools::Bind( std::min<int> ) );
            m_console.RegisterCommand( "max", Tools::Bind( std::max<int> ) );
            m_console.RegisterCommand( "exit", Tools::Bind( &TAGApplication::Exit, *this ) );
        }

        TAGApplication::~TAGApplication( void )
        {
            Console::Kill();
            Debug::ILogger::Destroy();
        }

        int TAGApplication::Run( void )
        {
            Debug::ILogger::BeginGroup( "Init application" );

            Debug::ILogger::Log( Debug::ILogger::DEBUG, "Test debug\n" );
            Debug::ILogger::Log( Debug::ILogger::INFO, "Test info\n" );
            Debug::ILogger::Log( Debug::ILogger::WARNING, "Test warning\n" );
            Debug::ILogger::Log( Debug::ILogger::CRITICAL, "Test critical\n" );
            Debug::ILogger::Log() << "Load\n";

            Debug::ILogger::EndGroup( "Application initialized" );

            return 0;
        }

        void TAGApplication::Exit()
        {
            m_running = false;
        }

    } // end namespace Core

} // end namespace TAG
