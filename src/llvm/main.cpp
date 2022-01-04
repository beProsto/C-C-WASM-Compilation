// This imports the functions we defined in JS, in the "env" block
// extern "C" void __wasm_import_console_log_str(const char*);
extern "C" void __wasm_import_console_log_str(char*);
extern "C" void __wasm_import_winreqanim_call();

extern "C" void (*__wasm_winreqanim_callback)();

extern "C" void __wasm_export_winreqanim_exec() {
	__wasm_winreqanim_callback();
}

extern "C" void __wasm_set_winreqanim_callback(void (*_cb)()) {
	__wasm_winreqanim_callback = _cb;
	__wasm_import_winreqanim_call();
}


const char* HELLO_WORLD_STR = "LLVM Compiled and run succsessfully!";

// as opposed to C, in C++ the compiler will do weird things to the function names in the binary
// (because namespaces etc)
// so we have to use this special keyword, `extern "C"`
// to preserver our function's name in the resulting wasm binary

void animation_frame() {
	__wasm_import_console_log_str((char*)"Animation Frame Update!");
	__wasm_set_winreqanim_callback(animation_frame);
}

extern "C" void hello() {
	__wasm_import_console_log_str((char*)HELLO_WORLD_STR);
	__wasm_set_winreqanim_callback(animation_frame);
}