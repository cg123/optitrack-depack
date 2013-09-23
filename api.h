#ifndef OPTITRACK_API_H_
#define OPTITRACK_API_H_

#if defined(_MSC_VER)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__) || defined(__clang__)
// GCC or clang
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
// I have no idea what compiler this is. Hope for the best.
#define EXPORT
#define IMPORT
#endif

#define EXPORT_FUNC(type) extern EXPORT "C" type __cdecl

#endif//OPTITRACK_API_H_
