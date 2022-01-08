#include "utils/utils.hpp"

const char* HELLO_WORLD_STR = "LLVM Compiled and run succsessfully!";

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

// as opposed to C, in C++ the compiler will do weird things to the function names in the binary
// (because namespaces etc)
// so we have to use this special keyword, `extern "C"`
// to preserver our function's name in the resulting wasm binary
extern "C" void hello() {
	__wasm_import_console_log_str(HELLO_WORLD_STR);
	__wasm_import_console_log_str("If you wish to stop the Animation Frame cycle (the text that keeps on being printed), press Escape.");

	__wasm_import_console_log_str("Testing malloc:");

	// // allocation
	// int* a = make<int>(5);
	// int* b = a;

	// *b = 5;
	// b++;
	// *b = 10;
	// b++;
	// *b = 63;
	

	// for(int i = 0; i < 5; i++) {
	// 	__wasm_import_console_log_num(a[i]);
	// }
	// // deallocation
	// free(a);
	
	__wasm_import_console_log_str("Testing malloc ended!");
	


	pointer_to_animation_frame_first = animation_frame_first;
	__wasm_set_winreqanim_callback(pointer_to_animation_frame_first);
}