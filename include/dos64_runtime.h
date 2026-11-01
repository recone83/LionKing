#ifndef DOS64_RUNTIME_H
#define DOS64_RUNTIME_H

#include "dos64_api.h"

#ifndef DOS64_RUNTIME_MAJOR
#define DOS64_RUNTIME_MAJOR 1
#endif
#ifndef DOS64_RUNTIME_MINOR
#define DOS64_RUNTIME_MINOR 0
#endif
#define DOS64_SERVICE_TEXT 1ULL
#define DOS64_SERVICE_GFX 2ULL
#define DOS64_SERVICE_INPUT 4ULL
#define DOS64_SERVICE_TIME 8ULL
#define DOS64_SERVICE_AUDIO 16ULL
#define DOS64_SERVICE_FS 32ULL
#define DOS64_SERVICE_SYSTEM 64ULL
#define DOS64_REQUIRED_SERVICES (DOS64_SERVICE_TEXT | DOS64_SERVICE_GFX | \
                                 DOS64_SERVICE_INPUT | DOS64_SERVICE_TIME | \
                                 DOS64_SERVICE_FS | DOS64_SERVICE_SYSTEM)

typedef int (__attribute__((ms_abi)) *DOS64_APPLICATION)(const DOS64_API *Api);

/* This negotiation layout and export signature remain stable across releases. */
typedef struct DOS64_REQUIREMENTS {
    unsigned int Size;
    unsigned short Major, Minor;
    unsigned long long ApiSize, ApiVersion, RequiredServices;
} DOS64_REQUIREMENTS;

static inline int dos64_runtime_compatible(const DOS64_REQUIREMENTS *Required,
                                           unsigned short Major, unsigned short Minor,
                                           unsigned long long Services)
{
    return Required != 0 && Required->Size == sizeof(*Required) &&
           Required->Major == Major && Required->Minor <= Minor &&
           Required->ApiSize <= sizeof(DOS64_API) &&
           Required->ApiVersion <= DOS64_API_VERSION &&
           (Required->RequiredServices & Services) == Required->RequiredServices;
}

#ifdef DOS64_RUNTIME_DLL
#define DOS64_RUNTIME_IMPORT __declspec(dllexport)
#elif defined(_WIN32)
#define DOS64_RUNTIME_IMPORT __declspec(dllimport)
#else
#define DOS64_RUNTIME_IMPORT
#endif

DOS64_RUNTIME_IMPORT int __attribute__((ms_abi))
Dos64Run(DOS64_APPLICATION Application, const DOS64_REQUIREMENTS *Required);

#endif
