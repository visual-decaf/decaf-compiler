#ifdef __cplusplus
extern "C" {
#endif

int get_id();
void compile(const char* code, int id);
const char* get_token_stream(int id);
const char* get_ast(int id);
const char* get_program(int id);

#ifdef __cplusplus
}
#endif