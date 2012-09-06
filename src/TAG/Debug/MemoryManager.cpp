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

#include <Debug/MemoryManager.hpp>
#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace TAG
{

    namespace Debug
    {

        // See header file
        MemoryManager::MemoryBlockMap MemoryManager::m_blocks = MemoryManager::MemoryBlockMap();

        // See header file
        MemoryManager::MemoryBlock MemoryManager::m_nextDelete = MemoryManager::MemoryBlock();

        // See header file
        MemoryManager::MemoryManager( void ) : m_file( "MemoryLeaks.txt" )
        {
            m_file << "+++++++++++++++++++++++++++++++++++" << std::endl;
            m_file << "+      Create memory manager      +" << std::endl;
            m_file << "+++++++++++++++++++++++++++++++++++" << std::endl;
        }

        // See header file
        MemoryManager::~MemoryManager( void )
        {
            m_file << "+++++++++++++++++++++++++++++++++++" << std::endl;
            m_file << "+      Destroy memory manager     +" << std::endl;
            m_file << "+++++++++++++++++++++++++++++++++++" << std::endl;
            if( m_blocks.empty() )
            {
                m_file << " -- No memory leaks detected --" << std::endl;
            }
            else
                LeaksReport();
        }

        // See header file
        MemoryManager& MemoryManager::GetInstance( void )
        {
            static MemoryManager instance;

            return instance;
        }

        // See header file
        void MemoryManager::LeaksReport()
        {
            std::size_t totalSize = 0;

            for( MemoryBlockMap::iterator it = m_blocks.begin(); it != m_blocks.end(); ++it )
            {
                totalSize += it->second.size;

                m_file << "==> " << it->first
                       << " | " << std::setw( 7 ) << static_cast< int >( it->second.size ) << " bytes"
                       << " | " << it->second.filename << " ( l. " << it->second.line << " )" << std::endl;

                free( it->first ); // release the memory
            }

            m_file << std::endl << std::endl << " --- " << static_cast< int >( m_blocks.size() ) << " no-free blocks, "
                   << static_cast< int >( totalSize ) << " bytes ---" << std::endl;
        }

        // See header file
        void* MemoryManager::Allocate( std::size_t size, const char *filename, int line, bool array )
        {
            void* ptr = malloc( size );

            MemoryBlock mem;
            mem.size = size;
            mem.filename = filename;
            mem.line = line;
            mem.array = array;
            m_blocks[ ptr ] = mem;

            m_file << "++ Allocate " << ptr
                   << " | " << std::setw( 7 ) << static_cast< int >( size ) << " bytes"
                   << " | " << filename << " ( l. " << line << " )" << std::endl;

            return ptr;
        }

        // See header file
        void MemoryManager::Free( void *ptr, bool array )
        {
            MemoryBlockMap::iterator it = m_blocks.find( ptr );

            // if not found, freeing the memory even when
            if( it == m_blocks.end() )
            {
                free( ptr );
                return;
            }

            m_file << "-- Free     " << ptr
                   << " | " << std::setw( 7 ) << static_cast< int >( it->second.size ) << " bytes"
                   << " | " << m_nextDelete.filename << " ( l. " << m_nextDelete.line << " )" << std::endl;
            m_blocks.erase( it );

            if( ptr != NULL )
                free( ptr );
        }

        // See header file
        void MemoryManager::NextDelete(const char *filename, int line)
        {
            m_nextDelete.filename = filename;
            m_nextDelete.line = line;
        }

    } // end namespace Debug

} // end namespace TAG
