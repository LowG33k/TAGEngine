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

#ifndef __Functor_HPP__
#define __Functor_HPP__

#include <string>
#include <Config/Config.hpp>
#include <Utilities/String.hpp>

#include <Debug/MemoryDebug.hpp>

namespace TAG
{

    namespace Tools
    {

        /// \brief Interface for functions
        /// ////////////////////////////////////////////////
        class IFunction
        {

            public:
                /// \brief Default destructor.
                /// ////////////////////////////////////////////////
                virtual ~IFunction( void ){}

                /// \brief Use for execute the current function with params.
                ///
                /// \param params Parameters send to the current function.
                ///
                /// \return Function result in a string.
                /// ////////////////////////////////////////////////
                virtual std::string Execute( const std::string& params ) = 0;

        };

        /// \brief A functor.
        /// ////////////////////////////////////////////////
        class TAG_API Functor
        {

            public:
                /// \brief Default constructor.
                ///
                /// \param function Pointer to the function use in this functor.
                /// ////////////////////////////////////////////////
                Functor( IFunction* function = NULL );

                /// \brief Overload parenthesis operator for call function in the functor.
                ///
                /// \param params Parameters send to call function.
                ///
                /// \return The result of the function in a string.
                /// ////////////////////////////////////////////////
                std::string operator()( const std::string& params = "" ) const;

            private:
                IFunction* m_function; ///< Pointer to the current function.
        };

        #include <Utilities/Functor.inl>

    } // end namespace Tools

} // end namespace TAG

#include <Debug/MemoryDebugOff.hpp>

#endif // __Functor_HPP__
