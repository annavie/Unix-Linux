**How It Works:**

- **Capturing the Stack:**  
  The program uses the `backtrace()` function to take a "snapshot" of the current call stack and save it in an array. It saves one extra frame so that the frame for `stack_dump()` is not printed.

- **Symbol Resolution:**  
  For each address in the call stack, the program uses `dladdr()` to find the function name from the program's dynamic symbol table.

- **Demangling:**  
  If a function name is "mangled" (which happens often in C++), the program calls `__cxa_demangle()` to convert it into a readable form.

- **Printing:**  
  The program prints the function names and their addresses. This shows the order of function calls that led to the call to `stack_dump()`.

- **Extra Memory (+1):**  
  We allocate an array of `depth + 1` pointers because `backtrace()` always includes the current function call. The extra slot holds the `stack_dump()` frame, which we then skip so that only the important function calls are printed.

- **Starting from Index 1:**  
  Since the first element (index 0) of the captured stack is the `stack_dump()` call, we start our loop at index 1 to ignore that frame. This ensures that the printed backtrace starts from the function that called `stack_dump()`.

---

**Why Run with -rdynamic:**

- **Exports Symbols:**  
  The `-rdynamic` flag tells the linker to export all function symbols in the executable. This is important because `dladdr()` needs these symbols to show function names. Without `-rdynamic`, some symbols might not be available, and you may only see memory addresses.

**How to Run with -rdynamic:**

Compile like this:

```bash
g++ -rdynamic -o stack_dump stack_dump.cpp 
```
