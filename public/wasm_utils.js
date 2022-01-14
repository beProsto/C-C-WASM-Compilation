let mouse_pos_x = 0;
let mouse_pos_y = 0;
let mouse_wheel = 0;

// mouse implementation
window.onmousemove = (e) => {
	mouse_pos_y = e.clientY;
	mouse_pos_x = e.clientX;
};
window.onwheel = (e) => {
	mouse_wheel = e.deltaY;
};
// touch implementation
window.ontouchmove = function(e) { 
	mouse_pos_x = e.touches[0].clientX;
	mouse_pos_y = e.touches[0].clientY;
};
window.ontouchstart = window.ontouchmove;


let frameId;
let animFrame = () => {};

// ends the animation loop
window.onkeydown = (e) => {
	if(e.which == 27) {
		window.cancelAnimationFrame(frameId);
		console.log("Stopped!");
	}
};


class ModuleUtils {
	constructor() {
		// this is our module
		this.moduleref = {};
		// reference to a context
		this.c2d = {};

		// buffer for the text 
		this.console_write_buffer = "";
	}

	// functions to import to our wasm code
	getImports() {
		return { env: {
			// logs a string
			__wasm_import_console_log_str: (_ptr) => {
				const memory_buffer = new Uint8Array(this.moduleref.instance.exports.memory.buffer);
				let text_buffer = "";
				
				for(; memory_buffer[_ptr] != 0; _ptr++) {
					text_buffer += String.fromCharCode(memory_buffer[_ptr]);
				}

				console.log(text_buffer);
			},
			// logs a number
			__wasm_import_console_log_num: (_num) => {
				console.log(_num);
			},
			// writes a string to a buffer that is logged upon detecting a new line character
			__wasm_import_console_write_str: (_ptr) => {
				const memory_buffer = new Uint8Array(this.moduleref.instance.exports.memory.buffer);
				
				for(; memory_buffer[_ptr] != 0; _ptr++) {
					if(memory_buffer[_ptr] == 10) {
						console.log(this.console_write_buffer);
						this.console_write_buffer = "";
					}
					else {
						this.console_write_buffer += String.fromCharCode(memory_buffer[_ptr]);
					}
				}
			},
			// writes a number to a buffer that is logged upon detecting a new line character
			__wasm_import_console_write_num: (_num) => {
				this.console_write_buffer += _num;
			},
			// starts a window.requireAnimationFrame loop called on a specific funtion exported by the module
			__wasm_import_winreqanim_call: () => {
				animFrame = () => {
					this.moduleref.instance.exports.__wasm_export_winreqanim_callback_execute();

					this.c2d.putImageData(img, 0, 0);

					frameId = window.requestAnimationFrame(animFrame);
				}
				frameId = window.requestAnimationFrame(animFrame);
			},
			// changes the inner html of a specific element chosen by id
			change_text_in_dom_element: (_id_str, _html_str) => {
				const memory_buffer = new Uint8Array(this.moduleref.instance.exports.memory.buffer);
				
				let id_text = "";
				for(; memory_buffer[_id_str] != 0; _id_str++) {
					id_text += String.fromCharCode(memory_buffer[_id_str]);
				}
				let html_text = "";
				for(; memory_buffer[_html_str] != 0; _html_str++) {
					html_text += String.fromCharCode(memory_buffer[_html_str]);
				}

				document.getElementById(id_text).innerHTML = html_text;
			},
			// starts a console timer
			console_timer_start: (_id) => {
				console.time("Console Timer <" + _id + ">");
			},
			// ends the console timer
			console_timer_end: (_id) => {
				console.timeEnd("Console Timer <" + _id + ">");
			},
			// imports the mouse's values
			mouse_position_x_get: () => {return mouse_pos_x;},
			mouse_position_y_get: () => {return mouse_pos_y;},
			mouse_wheel_get: () => {return mouse_wheel;}
		} };
	}
}