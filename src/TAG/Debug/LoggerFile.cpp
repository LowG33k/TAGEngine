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

#include <Debug/LoggerFile.hpp>
#include <iostream>
#include <Tools/Date.hpp>
#include <Tools/Time.hpp>

namespace TAG
{

    namespace Debug
    {

        // See header file.
        LoggerFile::LoggerFile( const std::string& filename ) :  m_file( filename.c_str() )
        {
            m_file << "--------------------------------" << std::endl;
            m_file << "+          Events log          +" << std::endl;
            m_file << "+          " << Tools::Date::CurrentDate() << "          +" << std::endl;
            m_file << "+           " << Time::CurrentTime() << "           +" << std::endl;
            m_file << "--------------------------------" << std::endl;
        }

        // See header file.
        LoggerFile::~LoggerFile( void )
        {

        }

        // See header file.
        void LoggerFile::Write( const std::string& message )
        {
            m_file << message << std::flush;
        }

    } // end namespace Debug

} // end namespace TAG
