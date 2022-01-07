(module
	;; it imports a function from the js env called console_log_number as $log_num
	(import "env" "console_log_number" (func $log_num (param i32))) ;; in this case i32 will be interpreted as a number
	(import "env" "console_log_string" (func $log_str (param i32))) ;; in this case i32 will be interpreted as a pointer to the beggining of a string
	
	;; define our programmes memory
	(memory (;0;) 2)
	;; we create a string (an array of bytes) starting at the address of 1024
	(data (;0;) (i32.const 1024) "This is a string defined in WAT!\00")
	;; exports the memory
	(export "memory" (memory 0))

	;; we create a function
	(func $testn (param i32) (param i32) (result i32)
		;; pushes both params onto the stack
		local.get 0
		local.get 1
		;; [param0, param1]

		;; pops 2 values off the stack, adds them and pushes the result onto the stack
		i32.add
		;; [param0+param1]

		;; pushes the second param onto the stack
		local.get 1
		;; [param0+param1, param1]

		;; multiplies the 2 values off the stack and pushes the result
		i32.mul
		;; [(param0+param1)*param1]

		;; takes a value off the stack and passes it into a function
		call $log_num 
		;; []

		;; pushes a value onto the stack
		i32.const 1024
		;; [1024]
		;; pop 1024 off the stack, use it as a parameter for the log_str function
		call $log_str
		;; []


		;; pushes a value onto the stack (equal to 23)
		i32.const 23
		;; [23]

		;; the last value on the stack will be returned by this function
	)
	;; we export the function, we make it's name different than in here
	(export "testing_attention_please" (func $testn))
)