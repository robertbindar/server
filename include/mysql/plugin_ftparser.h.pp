class THD;
class Item;
typedef char my_bool;
typedef void * MYSQL_PLUGIN;
extern "C" {
extern "C" {
extern struct base64_service_st {
  int (*base64_needed_encoded_length_ptr)(int length_of_data);
  int (*base64_encode_max_arg_length_ptr)(void);
  int (*base64_needed_decoded_length_ptr)(int length_of_encoded_data);
  int (*base64_decode_max_arg_length_ptr)();
  int (*base64_encode_ptr)(const void *src, size_t src_len, char *dst);
  int (*base64_decode_ptr)(const char *src, size_t src_len,
                           void *dst, const char **end_ptr, int flags);
} *base64_service;
int my_base64_needed_encoded_length(int length_of_data);
int my_base64_encode_max_arg_length(void);
int my_base64_needed_decoded_length(int length_of_encoded_data);
int my_base64_decode_max_arg_length();
int my_base64_encode(const void *src, size_t src_len, char *dst);
int my_base64_decode(const char *src, size_t src_len,
                  void *dst, const char **end_ptr, int flags);
}
extern "C" {
extern void (*debug_sync_C_callback_ptr)(THD*, const char *, size_t);
}
extern "C" {