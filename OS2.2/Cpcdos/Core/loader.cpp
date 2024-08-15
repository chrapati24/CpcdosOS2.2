#include <iostream>

void __CPCDOS_INIT_1(char* argcpc){

    std::cout << "Heya" << std::endl;
}

namespace cpc_init {
    
    int cpcdos_loader(char *s){

        __CPCDOS_INIT_1(s);

        //CpcdosCP_Shell("exe/ KRNL/KRNL.CPC");

        //cmdloop();
       
        return 0;
    }
}