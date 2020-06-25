#include "mysql/service_compression_lzma.h"

SERVICE_lzma_ret SERVICE_lzma_stream_buffer_decode(
		uint64_t *, uint32_t,
		const SERVICE_lzma_allocator *,
		const uint8_t *, size_t *, size_t,
		uint8_t *, size_t *, size_t) lzma_nothrow{
			return SERVICE_LZMA_OK;
		}


SERVICE_lzma_ret SERVICE_lzma_easy_buffer_encode(
		uint32_t, SERVICE_lzma_check,
		const SERVICE_lzma_allocator *,
		const uint8_t *, size_t,
		uint8_t *, size_t *, size_t) lzma_nothrow{
			return SERVICE_LZMA_OK;
		}