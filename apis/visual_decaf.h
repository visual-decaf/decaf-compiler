#ifdef __cplusplus
extern "C" {
#endif

int get_id();
void compile(const char* code, int id);
char* get_token_stream(int id);
char* get_ast(int id);
char* get_program(int id);

#ifdef __cplusplus
}
#endif