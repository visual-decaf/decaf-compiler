#ifdef __cplusplus
extern "C" {
#endif

int get_id();
char* upload_code(const char* code, int id);
char* get_token_stream(int id);
char* get_ast(int id);
char* get_program(int id);
char* get_debug_info(int id);
void end_use(int id);

#ifdef __cplusplus
}
#endif