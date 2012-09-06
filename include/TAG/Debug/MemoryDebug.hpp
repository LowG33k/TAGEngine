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

#ifndef __MemoryDebug_HPP__
#define __MemoryDebug_HPP__

#include <iostream>
#include <Config/Config.hpp>
#include <Debug/MemoryManager.hpp>

#ifdef TAG_DEBUG

/// \brief Replace the new opertaor.
///
/// \param size The new pointer size required.
/// \param filename The filename when the allocation used.
/// \param line The line when the allocation used.
///
/// \return A void pointer.
/// ////////////////////////////////////////////////
inline void* operator new( std::size_t size, const char* filename, int line ) throw( std::bad_alloc )
{
    return TAG::Debug::MemoryManager::GetInstance().Allocate( size, filename, line, false );
}

/// \brief Replace the new opertaor for array.
///
/// \param size The new pointer size required.
/// \param filename The filename when the allocation used.
/// \param line The line when the allocation used.
///
/// \return A void pointer.
/// ////////////////////////////////////////////////
inline void* operator new[]( std::size_t size, const char* filename, int line ) throw( std::bad_alloc )
{
    return TAG::Debug::MemoryManager::GetInstance().Allocate( size, filename, line, true );
}

/// \brief Replace the delete opertaor.
///
/// \param ptr The pointer would you delete.
/// ////////////////////////////////////////////////
inline void operator delete( void* ptr ) throw()
{
    TAG::Debug::MemoryManager::GetInstance().Free( ptr, false );
}

/// \brief Replace the delete opertaor, used when an exception risen.
///
/// \param ptr The pointer would you delete.
/// \param filename The filename when the allocation used.
/// \param line The line when the allocation used.
/// ////////////////////////////////////////////////
inline void operator delete( void* ptr, const char* filename, int line ) throw()
{
    TAG::Debug::MemoryManager::GetInstance().NextDelete( filename, line );
    TAG::Debug::MemoryManager::GetInstance().Free( ptr, false );
}

/// \brief Replace the delete opertaor for array.
///
/// \param ptr The pointer would you delete.
/// ////////////////////////////////////////////////
inline void operator delete[]( void* ptr ) throw()
{
    TAG::Debug::MemoryManager::GetInstance().Free( ptr, true );
}

/// \brief Replace the delete opertaor for array, used when an exception risen.
///
/// \param ptr The pointer would you delete.
/// \param filename The filename when the allocation used.
/// \param line The line when the allocation used.
/// ////////////////////////////////////////////////
inline void operator delete[]( void* ptr, const char* filename, int line ) throw()
{
    TAG::Debug::MemoryManager::GetInstance().NextDelete( filename, line );
    TAG::Debug::MemoryManager::GetInstance().Free( ptr, true );
}

#ifndef new
    #define new new( __FILE__, __LINE__ )
    #define delete TAG::Debug::MemoryManager::GetInstance().NextDelete( __FILE__, __LINE__ ), delete
#endif

#endif // TAG_DEBUG

#endif // __MemoryDebug_HPP__

