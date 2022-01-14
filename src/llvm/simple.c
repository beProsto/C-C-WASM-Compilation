// in C the final function's name (in the binary) is the same as in the code,
// thus we don't have to do anything special to export it
int function_name(int a, int b) {
	return a * b + a * b;
}