#include "utils/include/utils.hpp"

const char* HELLO_WORLD_STR = "LLVM Compiled and run succsessfully! 1234";

// import simple js functions
extern "C" void change_text_in_dom_element(const char*, const char*);
extern "C" void console_timer_start(unsigned int);
extern "C" void console_timer_end(unsigned int);

// create the array
const int WIDTH = 800, HEIGHT = 600, BPP=4; 
unsigned char display[WIDTH*HEIGHT*BPP];

// export a pointer to the first element of the array
extern "C" unsigned char* display_ptr = display;

// enum for rgba colour
struct color_t {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

// sets a specific value of the given pixel
inline void set_color(unsigned int _x, unsigned int _y, color_t _c) {
	if(_x < WIDTH && _y < HEIGHT) {
		((color_t*)display)[_y*WIDTH+_x] = _c;
	}
}

inline void draw_rect(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h, color_t _c) {
	// if(_x >= WIDTH) {
	// 	return;
	// }
	// if(_y >= HEIGHT) {
	// 	return;
	// }
	

	// if(_x+_w > WIDTH) {
	// 	_w = _w - (WIDTH - (_x + _w));
	// }
	// if(_x+_h > HEIGHT) {
	// 	_h = _h - (HEIGHT - (_y + _h));
	// }
	
	// for(uint32_t i = 0; i <_w*_h; i++) {
	// 	uint32_t x = i%_w;
	// 	uint32_t y = i/_h;
	// 	((color_t*)display)[(_y+y)*WIDTH+(_x+x)] = _c;
	// }

	for(uint32_t i = _x; i < _x + _w; i++) {
		for(uint32_t j = _y; j < _y + _h; j++) {
			set_color(i, j, _c);
		}
		
	}
	

}

// mouse position
extern "C" {
	int mouse_position_x_get();
	int mouse_position_y_get();
	int mouse_wheel_get();
}

// this function will define what happens per frame
void animation_frame() {
	uint32_t mpx = mouse_position_x_get();
	uint32_t mpy = mouse_position_y_get();
	uint8_t mw = (mouse_wheel_get() > 0? 255 : 0);
	draw_rect(mpx, mpy, 100, 100, color_t{mw, 255, 255, 255});
	// cout << "Mouse wheel value: " << mw << "\n";
}

// as opposed to C, in C++ the compiler will do weird things to the function names in the binary
// (because namespaces etc)
// so we have to use this special keyword, `extern "C"`
// to preserver our function's name in the resulting wasm binary
extern "C" void hello() {
	console_log(HELLO_WORLD_STR);
	cout << "HELLO_WORLD_STR constains " << strlen_4bytes(HELLO_WORLD_STR) << " characters according to 4 bytes at a time check!" << endl;
	cout << "HELLO_WORLD_STR constains " << strlen_1byte(HELLO_WORLD_STR) << " characters according to 1 byte at a time check!" << endl;

	// console_timer_start(1);
	// for(int i = 0; i < 9999; i++) {
	// 	strlen_1byte(HELLO_WORLD_STR);
	// }
	// console_timer_end(1);

	// console_timer_start(4);
	// for(int j = 0; j < 9999; j++) {
	// 	strlen_4bytes(HELLO_WORLD_STR);
	// }
	// console_timer_end(4);

	for(unsigned int i = 0; i < WIDTH*HEIGHT; i++) {
		((color_t*)display)[i] = {255, 0, 255, 255};
	}

	draw_rect(200, 200, 300, 300, {255, 255, 0, 255});

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
		cout << "Index " << i << ", Value " << a[i] << '\n';
	}


	// deallocation
	free(a);
	console_log("Testing malloc ended!");

	
	// allocation
	a = (int*)malloc(5*sizeof(int));
	a[0] = 4;
	a[2] = 3;
	a[1] = 2;
	a[3] = 1;

	// deallocation
	free(a);

	cout << reinterpret_cast<int>(b) << " points to " << *b << '\n';

	__wasm_set_winreqanim_callback(animation_frame);
	__wasm_import_winreqanim_call();
}