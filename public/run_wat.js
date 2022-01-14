(async () => {
	// Instantiates a WASM module
	const module = await WebAssembly.instantiateStreaming(
		// Loads the binary from a file
		fetch("./wat/testin_it.wasm"),
		// Things to import into the module
		{
			env: {
				// This function logs a number
				console_log_number: (_num) => {console.log("This log has been imported into the wasm module: " + _num)},
				// This function logs a string
				console_log_string: (_ptr) => {
					const memory_buffer = new Uint8Array(module.instance.exports.memory.buffer);
					let text_buffer = "";
					
					for(; memory_buffer[_ptr] != 0; _ptr++) {
						text_buffer += String.fromCharCode(memory_buffer[_ptr]);
					}

					console.log(text_buffer);
				}
			}
		}
	);
	
	// Runs a function exported by the WASM module and logs it's result
	console.log("Testing the wat to wasm compilation: " + module.instance.exports.testing_attention_please(2, 3));
})();