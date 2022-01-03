@echo off

echo Compiling the emscripten code:
:: compiling with the emscripten toolchain is a lot easier
powershell em++ src/emscripten/main.cpp -o build/emscripten/main.js
echo Finished!
echo ---

echo Compiling the llvm code:
:: compiles the simpler, c file that simply exports 1 function
powershell clang --target=wasm32 -nostdlib '-Wl,--no-entry' '-Wl,--export-all' -o build/llvm/func.wasm src/llvm/func.c 
:: compiles the weirder c++ file that not only exports a function, but also imports a couple
:: ('-Wl,--allow-undefined' let's us define functions that our js code imports without needing to write any implementation for them in the c++ code)
powershell clang --target=wasm32 -nostdlib '-Wl,--no-entry' '-Wl,--export-all' '-Wl,--allow-undefined' -o build/llvm/main.wasm src/llvm/main.cpp
echo Finished!
echo ---

cd build
echo Running the Server on http://localhost:8080/
:: runs a python server to show the results
python -m http.server 8080