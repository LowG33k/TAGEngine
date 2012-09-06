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

#ifndef __MemoryManager_HPP__
#define __MemoryManager_HPP__

#include <Config/Config.hpp>
#include <cstdlib>
#include <string>
#include <map>
#include <fstream>

namespace TAG
{

    namespace Debug
    {

        /// \brief This class use to allocate / deallocate memory, and create a report.
        /// ////////////////////////////////////////////////
        class TAG_API MemoryManager
        {
            public:
                /// \brief Return unique instance of MemoryManager.
                ///
                /// Do not use a pointer, otherwise the new operator is used.
                /// ////////////////////////////////////////////////
                static MemoryManager& GetInstance( void );

                /// \brief Allocate a memory, and add a message in a file.
                ///
                /// \param size The pointer size in memory.
                /// \param filename The filename when the allocation used.
                /// \param line The line when the allocation used.
                /// \param array True if allocate an array, false also.
                ///
                /// \return A void pointer.
                /// ////////////////////////////////////////////////
                void* Allocate( std::size_t size, const char* filename, int line, bool array );

                /// \brief Release the memory.
                ///
                /// \param ptr The pointer would you release.
                /// \param array True if you would release an array, false also.
                /// ////////////////////////////////////////////////
                void Free( void* ptr, bool array );

                /// \brief Add information for release, because delete operator no accept parameters.
                ///
                /// \param filename The filename when the next release used.
                /// \param line The line when the next release used.
                /// ////////////////////////////////////////////////
                static void NextDelete( const char* filename, int line );

            protected:
                /// \brief Default constructor.
                /// ////////////////////////////////////////////////
                MemoryManager( void );

                /// \brief Default destructor.
                /// ////////////////////////////////////////////////
                virtual ~MemoryManager( void );

            private:
                /// \brief Represent a memory block
                /// ////////////////////////////////////////////////
                struct MemoryBlock
                {
                    std::size_t size; ///< Size of the pointer.
                    std::string filename; ///< Filename when allocation/release used.
                    int line; ///< Line in the file when allocation/release used.
                    bool array; ///< True if allocation/release is an array, false also.
                };

                /// \brief A shortcut for a MemoryBlock map
                /// ////////////////////////////////////////////////
                typedef std::map< void*, MemoryBlock > MemoryBlockMap;

                /// \brief Create a report at the end of execution.
                /// ////////////////////////////////////////////////
                void LeaksReport( void );

                std::ofstream m_file; ///< Stream to the memory leaks report.

                static MemoryBlockMap m_blocks; ///< Kept all memory block which are been allocated.

                static MemoryBlock m_nextDelete; ///< Kept the next memory block which will be released.
        };

    } // end namespace Debug

} // end namespace TAG

#endif // __MemoryManager_HPP__

