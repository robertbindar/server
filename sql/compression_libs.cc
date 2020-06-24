#include "service_compression_lzma.h"

lzma_ret SERVICE_lzma_stream_buffer_decode(
		uint64_t *, uint32_t,
		const lzma_allocator *,
		const uint8_t *, size_t *, size_t,
		uint8_t *, size_t *, size_t) lzma_nothrow{
			return LZMA_OK;
		}


lzma_ret SERVICE_lzma_easy_buffer_encode(
		uint32_t, lzma_check,
		const lzma_allocator *,
		const uint8_t *, size_t,
		uint8_t *, size_t *, size_t) lzma_nothrow{
			return LZMA_OK;
		}