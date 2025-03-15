#include <execinfo.h>   // Provides the backtrace() and backtrace_symbols() 
#include <dlfcn.h>      // Provides the dladdr() function,
#include <cxxabi.h>     // Provides __cxa_demangle(), which demangles symbols
#include <iostream>     
#include <cstdlib>     
#include <string>       

const int STACK_DUMP_DEPTH = 3;

void stack_dump(int depth, std::ostream &os){

    if(depth <=0) { return; }
    void* buffer[depth+1]; //+1 for this function
    int ptrs = backtrace(buffer, depth + 1);
    os << "Stack backtrace (" << ptrs - 1 << " frames):" << std::endl;
    for(int i = 1; i < ptrs; ++i) {
        Dl_info info;
        if(dladdr(buffer[i],&info) && info.dli_sname){
            int demangleStatus;
            char* demangledName = abi::__cxa_demangle(info.dli_sname, nullptr, nullptr, &demangleStatus);
            std::string funcName;
            if (demangleStatus == 0 && demangledName != nullptr) {
                funcName = demangledName;
                free(demangledName);  
                os << "Frame " << i << ": " << funcName 
                << " at " << buffer[i] << std::endl;
 
            } else {
                funcName = info.dli_sname;
            }

        } else {
            os << "Frame " << i << ": " << buffer[i] << std::endl;
        }

    }

}

void level3(std::ostream &os) {
    stack_dump(STACK_DUMP_DEPTH, os);
}
void level2(std::ostream &os) {
    level3(os);
}
void level1(std::ostream &os) {
    level2(os);
}
void test_stack_dump(std::ostream &os) {
    level1(os);
}
int main() {
    std::cout << "Running stack_dump test:" << std::endl;
    test_stack_dump(std::cout);
    return 0;
}
