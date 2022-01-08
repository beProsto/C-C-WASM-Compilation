#include "utils/include/utils.hpp"

const char* HELLO_WORLD_STR = "LLVM Compiled and run succsessfully!";

// these functions will define what happens per frame
void (*pointer_to_animation_frame_first)();

void animation_frame_second() {
	console_log("<h5 style=\"color: red; \">Animation Frame Second Callback!</h5>");
	__wasm_set_winreqanim_callback(pointer_to_animation_frame_first);
}

void animation_frame_first() {
	console_log("<h5 style=\"color: green;\">Animation Frame First Callback!</h5>");
	__wasm_set_winreqanim_callback(animation_frame_second);
}

// as opposed to C, in C++ the compiler will do weird things to the function names in the binary
// (because namespaces etc)
// so we have to use this special keyword, `extern "C"`
// to preserver our function's name in the resulting wasm binary
extern "C" void hello() {
	console_log(HELLO_WORLD_STR);
	console_log("If you wish to stop the Animation Frame cycle (the text that keeps on being printed), press Escape.");

	console_log("Testing malloc:");
	// allocation
	int* a = (int*)malloc(5*sizeof(int));
	int* b = a;

	*b = 5;
	b++;
	*b = 10;
	b++;
	*b = 63;
	

	for(int i = 0; i < 5; i++) {
		__wasm_import_console_log_num(a[i]);
	}
	// deallocation
	free(a);
	console_log("Testing malloc ended!");

	pointer_to_animation_frame_first = animation_frame_first;
	__wasm_set_winreqanim_callback(pointer_to_animation_frame_first);
}