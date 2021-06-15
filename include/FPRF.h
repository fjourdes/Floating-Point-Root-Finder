#ifndef _FPRF_H_
#define _FPRF_H_


#ifndef WIN32
#   define FPRF_EXPORT_DYNAMIC_LIBRARY
#   define FPRF_IMPORT_DYNAMIC_LIBRARY
#else
#   define FPRF_EXPORT_DYNAMIC_LIBRARY __declspec( dllexport )
#   define FPRF_IMPORT_DYNAMIC_LIBRARY __declspec( dllimport )
#   ifdef _MSC_VER
#       pragma warning(disable : 4273)
#   endif
#endif

#ifdef FloatingPointRootFinder_EXPORTS
#define FPRF_API FPRF_EXPORT_DYNAMIC_LIBRARY
#else
#define FPRF_API FPRF_IMPORT_DYNAMIC_LIBRARY
#endif

#endif _FPRF_H_
