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

#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <sstream>

namespace TAG
{

    class StringBuilder
    {
        public:
            StringBuilder();
            template< typename T > StringBuilder( const T& value );
            template< typename T > StringBuilder& operator()( const T& value );
            operator std::string();

        private:
            std::ostringstream m_out;
    };

    class StringExctractor
    {
        public:
            StringExctractor( const std::string& text );
            template< typename T > StringExctractor& operator()( T& value );
            void ThrowIfEOF();

        private:
            std::istringstream m_in;
    };

    #include <Utilities/String.inl>

}

#endif // STRING_HPP
