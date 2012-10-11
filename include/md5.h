#pragma once
#pragma warning(disable:4251)

#ifdef LIBOSS_EXPORTS
#define OSSDLL_API __declspec(dllexport)
#else
#define OSSDLL_API __declspec(dllimport)
#endif

#ifndef _MD5_H
#define _MD5_H

#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

typedef struct md5_contextStru
{
    uint32 total[2];
    uint32 state[4];
    uint8 buffer[64];
}md5_context;
#ifdef __cplusplus
extern "C"
{
#endif
OSSDLL_API void  md5_starts( md5_context *ctx );
OSSDLL_API void  md5_update( md5_context *ctx, uint8 *input, uint32 length );
OSSDLL_API void  md5_finish( md5_context *ctx, uint8 digest[16] );
#ifdef __cplusplus
}
#endif
#endif /* md5.h */
