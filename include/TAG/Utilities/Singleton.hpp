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

#ifndef __Singleton_HPP__
#define __Singleton_HPP__

#include <cstdlib>
#include <iostream>
#include <Debug/MemoryDebug.hpp>

namespace TAG
{

    namespace Tools
    {

        template< typename T >
        class Singleton
        {
            public:
                static T& GetInstance( void )
                {
                    //std::cout << "Singleton: " << s_instance << std::endl;
                    if( s_instance == NULL )
                        s_instance = new T();

                    return *s_instance;
                }
                static void Kill( void )
                {
                    delete s_instance;
                    s_instance = NULL;
                }

            protected:
                Singleton( void ){}
                ~Singleton( void ){}

            private:
                static T* s_instance;

                Singleton( Singleton& );
                void operator=( Singleton& );
        };

        #define MAKE_SINGLETON( Class )\
            public: \
                friend class TAG::Tools::Singleton< Class >; \
                static Class& GetInstance(); \
            private: \

        #define IMPL_SINGLETON( Class ) \
            template <> Class* TAG::Tools::Singleton< Class >::s_instance = NULL; \
            Class& Class::GetInstance() \
            { \
                return TAG::Tools::Singleton< Class >::GetInstance(); \
            } \

    } // end namespace Tools

} // end namespace TAG

#include <Debug/MemoryDebugOff.hpp>

#endif // __Singleton_HPP__
