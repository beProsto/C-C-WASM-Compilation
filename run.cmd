@echo off

echo Compiling the emscripten code:
:: compiling with the emscripten toolchain is a lot easier
powershell em++ src/emscripten/main.cpp -o build/emscripten/main.js
echo Finished!
echo ---

echo Compiling the llvm code:
:: the llvm toolchain's compilation split up into two seperate parts for no actual reason;
powershell clang --target=wasm32 -c src/llvm/main.cpp -o build/llvm/main.o
powershell wasm-ld --no-entry --export-all -o build/llvm/main.wasm build/llvm/main.o
:: this is how it looks like in one command
powershell clang --target=wasm32 -nostdlib '-Wl,--no-entry' '-Wl,--export-all' -o build/llvm/func.wasm src/llvm/func.c 

echo Finished!
echo ---

cd build
echo Running the Server on http://localhost:8080/
:: runs a python server to show the results
python -m http.server 8080