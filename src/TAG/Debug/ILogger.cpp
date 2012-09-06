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

#include <Debug/ILogger.hpp>
#include <cstdarg>
#include <cstdio>
#include <Utilities/Date.hpp>
#include <Utilities/Time.hpp>

#include <Debug/MemoryDebug.hpp>

namespace TAG
{

    namespace Debug
    {

        ILogger* ILogger::m_instance = NULL;

        // See header file.
        ILogger::~ILogger( void )
        {

        }

        // See header file.
        void ILogger::SetLogger( ILogger* newLogger )
        {
            Destroy();
            m_instance = newLogger;
        }

        // See header file.
        void ILogger::Destroy( void )
        {
            delete m_instance;
            m_instance = NULL;
        }

        // See header file.
        void ILogger::Log( LogTags tag, const char* format, ... )
        {
            char buffer[ 256 ];
            va_list args;
            va_start( args, format );
            vsprintf( buffer, format, args );
            va_end( args );

            std::ostringstream bufferStream;
            bufferStream << "             [" << TagToStr( tag ) << "] " << buffer;

            m_instance->Write( bufferStream.str() );
        }

        // See header file.
        void ILogger::Log( const char* format, ... )
        {
            char buffer[ 256 ];
            va_list args;
            va_start( args, format );
            vsprintf( buffer, format, args );
            va_end( args );

            std::ostringstream bufferStream;
            bufferStream << "             [   DEBUG   ] " << buffer;

            m_instance->Write( bufferStream.str() );
        }

        // See header file.
        ILogger& ILogger::Log( void )
        {
            return *m_instance;
        }

        // See header file.
        void ILogger::BeginGroup( const std::string &title )
        {
            std::string groupMessage = "[ ";
            groupMessage += Time::CurrentTime();
            groupMessage += " ] [   BEGIN   ] -- " + title + " --\n";
            m_instance->Write( groupMessage );
        }

        // See header file.
        void ILogger::EndGroup( const std::string &message )
        {
            std::string groupMessage = "[ ";
            groupMessage += Time::CurrentTime();
            groupMessage += " ] [    END    ] ++ " + message + "\n";
            m_instance->Write( groupMessage );
            m_instance->Write( "---------------------------------------------\n" );
        }

        std::string ILogger::TagToStr( LogTags tag )
        {
            switch( tag )
            {
                case DEBUG:
                    return "   DEBUG   ";
                case INFO:
                    return "    INFO   ";
                case WARNING:
                    return "  WARNING  ";
                case CRITICAL:
                    return " CRITICALS ";
            }
            return "  ?????  ";
        }

    } // end namespace Debug

} // end namespace TAG
