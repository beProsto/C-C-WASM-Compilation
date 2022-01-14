@echo off

echo Compiling the simple llvm code:
:: compiles the simpler, c file that simply exports 1 function
powershell clang --target=wasm32 -nostdlib '-Wl,--no-entry' '-Wl,--export-all' -o build/llvm/simple.wasm src/llvm/simple.c
echo Finished!
echo ---

echo Compiling the advanced llvm code:
:: compiles the weirder c++ file that not only exports a function, but also imports a couple
:: ('-Wl,--allow-undefined' let's us define functions that our js code imports without needing to write any implementation for them in the c++ code)
powershell clang++ --target=wasm32 -std=c++17 -nostdlib '-Wl,--no-entry' '-Wl,--export-all' '-Wl,--allow-undefined' -o build/llvm/main.wasm src/llvm/main.cpp src/llvm/utils/src/malloc.c src/llvm/utils/src/winreqanim.cpp
echo Finished!
echo ---

echo Compiling the WAT code:
:: uses wat2wasm tool from wabt toolkit
powershell wat2wasm src/wat/testin_it.wat -o build/wat/testin_it.wasm
echo Finished!
echo ---

cd build
echo Running the Server on http://localhost:8080/
:: runs a python server to show the results
python -m http.server 8080