// This imports the functions we defined in JS, in the "env" block
// extern "C" void __wasm_import_console_log_str(const char*);
extern "C" void __wasm_import_console_log_str(const char*);
// calls window.requestAnimationFrame, passing the __wasm_export_winreqanim_exec function as the one to play on the frame
extern "C" void __wasm_import_winreqanim_call();

void (*__wasm_winreqanim_callback)();
// simply calls our dynamic callback - done so that the callback can be changed and is not set to be a static function
extern "C" void __wasm_export_winreqanim_exec() {
	__wasm_winreqanim_callback();
}

// sets the callback to one we'd need and then calls the window.requestAnimationFrame function
extern "C" void __wasm_set_winreqanim_callback(void (*_cb)()) {
	__wasm_winreqanim_callback = _cb;
	__wasm_import_winreqanim_call();
}


const char* HELLO_WORLD_STR = "LLVM Compiled and run succsessfully!";

// as opposed to C, in C++ the compiler will do weird things to the function names in the binary
// (because namespaces etc)
// so we have to use this special keyword, `extern "C"`
// to preserver our function's name in the resulting wasm binary

// these functions will define what happens per frame
void (*pointer_to_animation_frame_first)();

void animation_frame_second() {
	__wasm_import_console_log_str("<h5 style=\"color: red; \">Animation Frame Second Callback!</h5>");
	__wasm_set_winreqanim_callback(pointer_to_animation_frame_first);
}

void animation_frame_first() {
	__wasm_import_console_log_str("<h5 style=\"color: green;\">Animation Frame First Callback!</h5>");
	__wasm_set_winreqanim_callback(animation_frame_second);
}

extern "C" void hello() {
	__wasm_import_console_log_str(HELLO_WORLD_STR);
	__wasm_import_console_log_str("If you wish to stop the Animation Frame cycle (the text that keeps on being printed), press Escape.");

	pointer_to_animation_frame_first = animation_frame_first;
	__wasm_set_winreqanim_callback(pointer_to_animation_frame_first);
}