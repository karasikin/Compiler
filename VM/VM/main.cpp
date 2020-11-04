#include <iostream>

#include "virtualmachine.h"

void vm_sum_test();
void vm_var_sum_test();
void vm_get_test();

int main()
{
    //vm_sum_test();
    //vm_var_sum_test();
    vm_get_test();

    return 0;
}


/////////////////////////  TESTS  /////////////////////////////////

void vm_sum_test() {
    auto vm = VirtualMachine();

    vm.execute({
                   {VirtualMachine::PUSHN, 10},
                   {VirtualMachine::PUSHN, 20},
                   {VirtualMachine::ADD, 0},
                   {VirtualMachine::PUT, 0},
                   {VirtualMachine::PUSHN, int('\n')},
                   {VirtualMachine::PUT, 0}
               });
}

void vm_var_sum_test() {
    auto vm = VirtualMachine();

    vm.execute({
                   {VirtualMachine::REG, 0},
                   {VirtualMachine::REG, 0},
                   {VirtualMachine::PUSHN, 100},
                   {VirtualMachine::PUSHN, 500},
                   {VirtualMachine::POP, 0},
                   {VirtualMachine::POP, 1},
                   {VirtualMachine::PUSH, 0},
                   {VirtualMachine::PUSH, 1},
                   {VirtualMachine::ADD, 0},
                   {VirtualMachine::REG, 0},
                   {VirtualMachine::POP, 2},
                   {VirtualMachine::PUSH, 2},
                   {VirtualMachine::PUT, 0},
                   {VirtualMachine::PUSHN, int('\n')},
                   {VirtualMachine::PUT, 0}
               });
}

void vm_get_test(){
    auto vm = VirtualMachine();

    vm.execute({
                   {VirtualMachine::GET, 0},
                   {VirtualMachine::GET, 0},
                   {VirtualMachine::ADD, 0},
                   {VirtualMachine::PUT, 0},
                   {VirtualMachine::PUSHN, int('\n')},
                   {VirtualMachine::PUT, 0}
               });
}
