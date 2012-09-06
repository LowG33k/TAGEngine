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

inline StringBuilder::StringBuilder()
{
}

template< typename T >
inline StringBuilder::StringBuilder( const T& value )
{
    m_out << value;
}

template< typename T >
inline StringBuilder& StringBuilder::operator()( const T& value )
{
    m_out << value;

    return *this;
}

inline StringBuilder::operator std::string()
{
    return m_out.str();
}


inline StringExctractor::StringExctractor(const std::string &text) : m_in( text )
{

}

template< typename T >
inline StringExctractor& StringExctractor::operator()( T& value )
{
    if( !(m_in >> value) )
    {
        // gestion erreurs
    }

    return *this;
}

inline void StringExctractor::ThrowIfEOF()
{
    //std::string text;

    //if( std::getline( m_in, text ) )
        //gestion error;
}

