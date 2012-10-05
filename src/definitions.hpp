#ifndef XXON_DEFINITIONS_HPP
#define XXON_DEFINITIONS_HPP

/*! CMake will define XXON_EXPORTS on Windows when it configures to build a library.
    If you are going to use another build system on windows or create the visual studio
    projects by hand you need to define XXON_EXPORTS when building the library on windows.
*/

#if defined (_WIN32) 
    /*! \def XXON_EXPORTS_STATIC
        It comes from CMakeFile, and it's defined when building a STATIC libary.
     */
    #if defined(XXON_EXPORTS_STATIC) 
        #define XXON_SPEC
    #elif defined(XXON_EXPORTS)
        #define XXON_SPEC __declspec(dllexport)
    #else
        #define XXON_SPEC __declspec(dllimport)
    #endif
#else
    #define XXON_SPEC
#endif

#endif



























