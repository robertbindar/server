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
	LZMA_OK                 = 0,
	LZMA_STREAM_END         = 1,
	LZMA_NO_CHECK           = 2,
	LZMA_UNSUPPORTED_CHECK  = 3,
	LZMA_GET_CHECK          = 4,
	LZMA_MEM_ERROR          = 5,
	LZMA_MEMLIMIT_ERROR     = 6,
	LZMA_FORMAT_ERROR       = 7,
	LZMA_OPTIONS_ERROR      = 8,
	LZMA_DATA_ERROR         = 9,
	LZMA_BUF_ERROR          = 10,
	LZMA_PROG_ERROR         = 11,
} lzma_ret;

typedef struct {
	void *(*alloc)(void *opaque, size_t nmemb, size_t size);
	void (*free)(void *opaque, void *ptr);
	void *opaque;
} lzma_allocator;

typedef enum {
	LZMA_CHECK_NONE     = 0,
	LZMA_CHECK_CRC32    = 1,
	LZMA_CHECK_CRC64    = 4,
	LZMA_CHECK_SHA256   = 10
} lzma_check;

extern struct compression_service_lzma_st {
  lzma_ret (*lzma_stream_buffer_decode_ptr)(uint64_t *, uint32_t, 
       const lzma_allocator *, const uint8_t *, size_t *,
	   size_t, uint8_t *, size_t *, size_t);
  
  lzma_ret (*lzma_easy_buffer_encode_ptr)(uint32_t, lzma_check,
		const lzma_allocator *,
		const uint8_t *, size_t,
		uint8_t *, size_t *, size_t);
} *compression_service_lzma;


#ifdef MYSQL_DYNAMIC_PLUGIN

#define deflateInit2(a, b, c, d, e, f, g) compression_service_lzma->lzma_stream_buffer_decode_ptr(a, b, c, d, e, f, g)
#define inflateInit2(a, b) compression_service_lzma->lzma_easy_buffer_encode_ptr(a, b)

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

extern lzma_ret lzma_stream_buffer_decode(
		uint64_t *, uint32_t,
		const lzma_allocator *,
		const uint8_t *, size_t *, size_t,
		uint8_t *, size_t *, size_t)
		lzma_nothrow;


extern lzma_ret lzma_easy_buffer_encode(
		uint32_t, lzma_check,
		const lzma_allocator *,
		const uint8_t *, size_t,
		uint8_t *, size_t *, size_t) lzma_nothrow;

#endif

#ifdef __cplusplus
}
#endif

#define SERVICE_COMPRESSION_LZMA_INCLUDED
#endif