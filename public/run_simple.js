(async () => {
	const { instance } = await WebAssembly.instantiateStreaming(
		fetch("./llvm/simple.wasm")
	);
	console.log("result of func(3,2): " + instance.exports.function_name(3, 2));
})();