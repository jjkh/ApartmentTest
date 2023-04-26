#include <cstdarg>
#include <stdio.h>
#include <objidlbase.h>

const char* APTTYPE_STRING[] = { "STA", "MTA", "NA", "MAINSTA" };
const char* APTTYPEQUALIFIER_STRING[] = {
    "NONE",
    "IMPLICIT_MTA",
    "NA_ON_MTA",
    "NA_ON_STA",
    "NA_ON_IMPLICIT_MTA",
    "NA_ON_MAINSTA",
    "APPLICATION_STA",
    "RESERVED_1",
};

void Log(const char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);

	printf("\n");
}

void LogApartmentType(const char* prefix)
{
    printf("%s: ", prefix);

    APTTYPE aptType;
    APTTYPEQUALIFIER aptTypeQualifier;
    auto hr = CoGetApartmentType(&aptType, &aptTypeQualifier);
    switch (hr) {
    case S_OK:
        break;
    case E_FAIL:
        printf("E_FAIL - The call could not successfully query the current apartment type and type qualifier\n");
        return;
    case CO_E_NOTINITIALIZED:
        printf("CO_E_NOTINITIALIZED - CoInitialize or CoInitializeEx was not called on this thread\n");
        return;
    default:
        printf("%08X - Unexpected error", hr);
        return;
    }

    // table from https://devblogs.microsoft.com/oldnewthing/20180208-00/?p=97986
    switch (aptType) {
    case APTTYPE_STA:
        if (aptTypeQualifier == APTTYPEQUALIFIER_NONE)
            printf("Single-threaded apartment");
        else if (aptTypeQualifier == APTTYPEQUALIFIER_APPLICATION_STA)
            printf("Non-reentrant single-threaded apartment");
        else
            printf("Unknown");
        break;
    case APTTYPE_MAINSTA:
        if (aptTypeQualifier == APTTYPEQUALIFIER_NONE)
            printf("Main single-threaded apartment");
        else
            printf("Unknown");
        break;
    case APTTYPE_MTA:
        if (aptTypeQualifier == APTTYPEQUALIFIER_NONE)
            printf("Multithreaded apartment, explicitly initialized");
        else if (aptTypeQualifier == APTTYPEQUALIFIER_IMPLICIT_MTA)
            printf("Multithreaded apartment, implicitly initialized");
        else
            printf("Unknown");
        break;
    case APTTYPE_NA:
        printf("Neutral apartment");
        break;
    default:
        printf("Unknown");
    }

    printf(" (%s, %s)\n", APTTYPE_STRING[aptType], APTTYPEQUALIFIER_STRING[aptTypeQualifier]);
}