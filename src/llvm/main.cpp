// This imports the functions we defined in JS, in the "env" block
extern "C" void __wasm_import_console_log_add_to_buffer(char);
extern "C" void __wasm_import_console_log_flush_buffer();

// A custom implementation of console_log
void console_log(const char* _str) {
	for(int i = 0; _str[i] != 0; i++) {
		__wasm_import_console_log_add_to_buffer(_str[i]);
	}
	__wasm_import_console_log_flush_buffer();
}

char HELLO_WORLD_STR[] = "LLVM Compiled and run succsessfully!";

// as opposed to C, in C++ the compiler will do weird things to the function names in the binary
// (because namespaces etc)
// so we have to use this special keyword, `extern "C"`
// to preserver our function's name in the resulting wasm binary
extern "C" void hello() {
	console_log(HELLO_WORLD_STR);
}