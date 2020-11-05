#include <iostream>

#include "virtualmachine.h"
#include "parser.h"

void vm_sum_test();
void vm_var_sum_test();
void vm_get_test();
void vm_print_char_test();

int main()
{
    auto parser = Parser();
    auto instructions = parser.parse("../files/program.code");

    for(const auto &item : *instructions) {
        std::cout << int(item.first) << " " << item.second << std::endl;
    }

    auto vm = VirtualMachine();
    vm.execute(*instructions);

    //vm_sum_test();
//    vm_var_sum_test();
    //vm_get_test();
//    vm_print_char_test();

    return 0;
}


/////////////////////////  TESTS  /////////////////////////////////

void vm_sum_test() {
    auto vm = VirtualMachine();

    vm.execute({
                   {Instructions::PUSHN, 10},
                   {Instructions::PUSHN, 20},
                   {Instructions::ADD, 0},
                   {Instructions::PUT, 0},
                   {Instructions::PUSHN, int('\n')},
                   {Instructions::PUT, 0}
               });
}

void vm_var_sum_test() {
    auto vm = VirtualMachine();

    vm.execute({
                   {Instructions::REG, 40},
                   {Instructions::REG, 40},
                   {Instructions::PUSHN, 100},
                   {Instructions::PUSHN, 500},
                   {Instructions::POP, 0},
                   {Instructions::POP, 1},
                   {Instructions::PUSH, 0},
                   {Instructions::PUSH, 1},
                   {Instructions::ADD, 0},
                   {Instructions::REG, 40},
                   {Instructions::POP, 2},
                   {Instructions::PUSH, 2},
                   {Instructions::PUT, 0},
                   {Instructions::REG, 11},
                   {Instructions::PUSHN, int('\n')},
                   {Instructions::POP, 3},
                   {Instructions::PUSH, 3},
                   {Instructions::PUT, 0}
               });
}

void vm_get_test(){
    auto vm = VirtualMachine();

    vm.execute({
                   {Instructions::GET, 0},
                   {Instructions::GET, 0},
                   {Instructions::ADD, 0},
                   {Instructions::PUT, 0},
                   {Instructions::PUSHN, int('\n')},
                   {Instructions::PUT, 0}
               });
}

void vm_print_char_test() {
    auto vm = VirtualMachine();

    vm.execute({
                   {Instructions::REG, 11},
                   {Instructions::PUSHN, 67},
                   {Instructions::POP, 0},
                   {Instructions::PUSH, 0},
                   {Instructions::PUT, 0}
                   //{Instructions::PUSHN, int('\n')},
                   //{Instructions::PUT, 0}
               });
}
