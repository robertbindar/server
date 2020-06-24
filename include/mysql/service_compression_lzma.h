/**
  @file include/mysql/service_compression_lzma.h
  This service provides dynamic access to LZMA.
*/

#ifndef SERVICE_COMPRESSION_LZMA_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef enum {
	SERIVCE_LZMA_OK                 = 0,
	SERIVCE_LZMA_STREAM_END         = 1,
	SERIVCE_LZMA_NO_CHECK           = 2,
	SERIVCE_LZMA_UNSUPPORTED_CHECK  = 3,
	SERIVCE_LZMA_GET_CHECK          = 4,
	SERIVCE_LZMA_MEM_ERROR          = 5,
	SERIVCE_LZMA_MEMLIMIT_ERROR     = 6,
	SERIVCE_LZMA_FORMAT_ERROR       = 7,
	SERIVCE_LZMA_OPTIONS_ERROR      = 8,
	SERIVCE_LZMA_DATA_ERROR         = 9,
	SERIVCE_LZMA_BUF_ERROR          = 10,
	SERIVCE_LZMA_PROG_ERROR         = 11,
} SERIVCE_lzma_ret;

typedef struct {
	void *(*alloc)(void *opaque, size_t nmemb, size_t size);
	void (*free)(void *opaque, void *ptr);
	void *opaque;
} SERIVCE_lzma_allocator;

typedef enum {
	SERIVCE_LZMA_CHECK_NONE     = 0,
	SERIVCE_LZMA_CHECK_CRC32    = 1,
	SERIVCE_LZMA_CHECK_CRC64    = 4,
	SERIVCE_LZMA_CHECK_SHA256   = 10
} SERIVCE_lzma_check;

extern struct compression_service_lzma_st {
  SERIVCE_lzma_ret (*SERIVCE_lzma_stream_buffer_decode_ptr)(uint64_t *, uint32_t, 
       const SERIVCE_lzma_allocator *, const uint8_t *, size_t *,
	   size_t, uint8_t *, size_t *, size_t);
  
  SERIVCE_lzma_ret (*SERIVCE_lzma_easy_buffer_encode_ptr)(uint32_t, SERIVCE_lzma_check,
		const SERIVCE_lzma_allocator *,
		const uint8_t *, size_t,
		uint8_t *, size_t *, size_t);
} *compression_service_lzma;


#ifdef MYSQL_DYNAMIC_PLUGIN

#define SERIVCE_lzma_stream_buffer_decode(a, b, c, d, e, f, g, h, i) compression_service_lzma->SERIVCE_lzma_stream_buffer_decode_ptr(a, b, c, d, e, f, g, h, i)
#define SERIVCE_lzma_easy_buffer_encode(a, b, c, d, e, f, g, h) compression_service_lzma->SERIVCE_lzma_easy_buffer_encode_ptr(a, b)

#else

#ifndef lzma_nothrow
#	if defined(__cplusplus)
#		if __cplusplus >= 201103L
#			define lzma_nothrow noexcept
#		else
#			define lzma_nothrow throw()
#		endif
#	elif __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
#		define lzma_nothrow __attribute__((__nothrow__))
#	else
#		define lzma_nothrow
#	endif
#endif

extern SERIVCE_lzma_ret SERIVCE_lzma_stream_buffer_decode(
		uint64_t *, uint32_t,
		const SERIVCE_lzma_allocator *,
		const uint8_t *, size_t *, size_t,
		uint8_t *, size_t *, size_t)
		lzma_nothrow;


extern SERIVCE_lzma_ret SERIVCE_lzma_easy_buffer_encode(
		uint32_t, SERIVCE_lzma_check,
		const SERIVCE_lzma_allocator *,
		const uint8_t *, size_t,
		uint8_t *, size_t *, size_t) lzma_nothrow;

#endif

#ifdef __cplusplus
}
#endif

#define SERVICE_COMPRESSION_LZMA_INCLUDED
#endif