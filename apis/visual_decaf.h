#ifdef __cplusplus
extern "C" {
#endif

int get_id();
char* upload_code(const char* code, int id);
char* get_token_stream(int id);
char* get_ast(int id);
char* get_program(int id);
void write_error_msg(const char* error_code, const char* error_msg, char* response);

#ifdef __cplusplus
}
#endif