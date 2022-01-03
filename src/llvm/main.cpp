const char* HELLO_WORLD_STR = "LLVM Compiled and run succsessfully!";

// as opposed to C, in C++ the compiler will do weird things to the function names in the binary
// (because namespaces etc)
// so we have to use this special keyword, `extern "C"`
// to preserver our function's name in the resulting wasm binary
extern "C" const char* hello_str() {
	return HELLO_WORLD_STR;
}
