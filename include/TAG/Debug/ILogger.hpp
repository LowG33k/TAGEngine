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

#ifndef __ILogger_HPP__
#define __ILogger_HPP__

#include <Config/Config.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

namespace TAG
{

    namespace Debug
    {

        /// \brief Interface to create a logger
        /// ////////////////////////////////////////////////
        class TAG_API ILogger
        {
            public:
                enum LogTags
                {
                    DEBUG = 0,
                    INFO = 1,
                    WARNING = 2,
                    CRITICAL = 3
                };
                /// \brief Change the current logger
                ///
                /// \param newLogger Pointer to the new logger.
                /// ////////////////////////////////////////////////
                static void SetLogger( ILogger* newLogger );

                /// \brief Use for add a log message
                ///
                /// Use this like printf function.
                ///
                /// \param format The string format.
                /// ////////////////////////////////////////////////
                static void Log( LogTags tag, const char* format, ... );

                /// \brief Use for add a log message
                ///
                /// Use this like printf function.
                ///
                /// \param format The string format.
                /// ////////////////////////////////////////////////
                static void Log( const char* format, ... );

                /// \brief Use for get this logger.
                ///
                /// Use like a std::cout flow.
                ///
                /// \return A reference to the current logger.
                /// ////////////////////////////////////////////////
                static ILogger& Log( void );

                /// \brief Use this like a std::cout flow.
                ///
                /// \tparam T The type of the log message ( like integer, string, ... )
                /// \param toLog The message would you added to logger.
                ///
                /// \return A reference to the current logger.
                /// ////////////////////////////////////////////////
                template< typename T > ILogger& operator << ( const T& toLog );

                /// \brief Delete current logger instance.
                /// ////////////////////////////////////////////////
                static void Destroy( void );

                /// \brief Use to begin a log group
                ///
                /// \param title Group title
                /// ////////////////////////////////////////////////
                static void BeginGroup( const std::string& title );

                /// \brief Use to end a log group
                ///
                /// \param message End group message
                /// ////////////////////////////////////////////////
                static void EndGroup( const std::string& message );

            protected:
                /// \brief Default destructor.
                /// ////////////////////////////////////////////////
                virtual ~ILogger( void );

            private:
                /// \brief Abstract method you must rewrite.
                ///
                /// Add the message to the logger.
                ///
                /// \param message The log message.
                /// ////////////////////////////////////////////////
                virtual void Write( const std::string& message ) = 0;

                static std::string TagToStr( LogTags tag );

                static ILogger* m_instance; ///< A pointer to the current logger instance.
        };

        template< typename T > ILogger& ILogger::operator <<( const T& toLog )
        {
            std::ostringstream bufferStream;
            bufferStream << "             [   DEBUG   ] " << toLog;
            Write( bufferStream.str() );

            return Log();
        }

    } // end namespace Debug

} // end namespace TAG

#endif // __ILogger_HPP__
