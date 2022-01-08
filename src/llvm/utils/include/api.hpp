#pragma once

// As this is a c++ file, and we're not exporting or importing any of these functions to or from js
// - we can do inlines and define multiple functions with the same name. :D

// CONSOLE LOGGING //

inline void console_log(const char* _str) {
	__wasm_import_console_log_str(_str);
}
inline void console_log(char _c) {
	char buffer[2] = {_c, '\0'};
	__wasm_import_console_log_str(buffer);
}
inline void console_log(int _a) {
	__wasm_import_console_log_num((double)_a);
}
inline void console_log(float _a) {
	__wasm_import_console_log_num((double)_a);
}	