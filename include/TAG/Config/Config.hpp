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

#ifndef __Config_HPP__
#define __Config_HPP__

namespace TAG
{

    ////////////////////////////////////////////////////////////
    // Identify the operating system
    ////////////////////////////////////////////////////////////
    #if defined(_WIN32) || defined(__WIN32__)

        // Windows
        #define TAG_SYSTEM_WINDOWS

    #elif defined(linux) || defined(__linux)

        // Linux
        #define TAG_SYSTEM_LINUX

    #elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

        // MacOS
        #define TAG_SYSTEM_MACOS

    #elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

        // FreeBSD
        #define TAG_SYSTEM_FREEBSD

    #else

        // Unsupported system
        #error This operating system is not supported by TAG library

    #endif

    #if !defined( NDEBUG )

        #define TAG_DEBUG

    #endif

    #if !defined( TAG_STATIC )

        #if defined( TAG_SYSTEM_WINDOWS )

            #if defined( TAG_EXPORT )

                #define TAG_API __declspec( dllexport )

            #else

                #define TAG_API __declspec( dllimport )

            #endif

        #else

            #if __GNUC__ >= 4

                // GCC 4 has special keywords for showing/hidding symbols,
                // the same keyword is used for both importing and exporting
                #define TAG_API __attribute__ ((__visibility__ ("default")))

            #else

                // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
                #define TAG_API

            #endif

        #endif
    #else

        #define TAG_API

    #endif

}

#endif // __Config_HPP__
