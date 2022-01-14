let img;
let c2d;

(async () => {
	const modutils = new ModuleUtils();
	const module = await WebAssembly.instantiateStreaming(
		fetch("./llvm/main.wasm"), modutils.getImports()
	);
	// pass the reference of the module to the utils importer
	modutils.moduleref = module;

	// start executing the main function
	module.instance.exports.hello();

	// canvas drawing setup
	c2d = document.getElementById("vancas").getContext("2d");
	const data = new Uint8ClampedArray(module.instance.exports.memory.buffer, module.instance.exports.display_ptr, 800 * 600 * 4);
	img = new ImageData(data, 800, 600);
	c2d.putImageData(img, 0, 0);

	// pass a reference to the context
	modutils.c2d = c2d;

	// make the fs button work!
	document.getElementById("flscrn").onclick = () => {
		document.getElementById("vancas").requestFullscreen();
	};
})();

