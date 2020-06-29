#include "mysql/service_compression_lzma.h"
#include "compression_libs.h"
#include "mariadb.h"
#include <stdio.h>

SERVICE_lzma_ret Dummy_lzma_easy_buffer_encode(
		uint32_t, SERVICE_lzma_check,
		const SERVICE_lzma_allocator *,
		const uint8_t *, size_t,
		uint8_t *, size_t *, size_t)
{
	printf("#####function encode \n");
	return SERVICE_LZMA_OK;
}

void init_compression_libs(struct compression_service_lzma_st *handler)
{
	printf("#####init_compression_libs\n");
  
	// With this patch, for DYNAMIC plugins, compression_service_lzma
	// points to the right structure because the services fake dynamic linker does its job (function plugin_dl_add in sql_plugin.cc)
	// But for STATIC plugins, the fake dynamic linker doesn't work, so we need
	// to make this pointer point to the right handler.
	compression_service_lzma= handler;

	// TODO: this is where we'll dl_open the compression libraries as well
	compression_service_lzma->SERVICE_lzma_easy_buffer_encode_ptr= Dummy_lzma_easy_buffer_encode;
}

