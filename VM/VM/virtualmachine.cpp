#include "virtualmachine.h"

#include <iostream>

VirtualMachine::VirtualMachine()
{
    memory = std::make_unique<std::vector<int>>();
}

bool VirtualMachine::execute(const Dict &code) {
    for(const auto &item : code) {
        switch(item.first) {
            case PUSH:
                push(item.second);  break;
            case POP:
                pop(item.second);   break;
            case ADD:
                add();              break;
            case MUL:
                mul();              break;
            case SUB:
                sub();              break;
            case DIV:
                div();              break;

                // jmp
                // jmpif

            case EQUAL:
                equal();            break;
            case LARGER:
                larger();           break;
            case AND:
                andOp();            break;
            case OR:
                orOp();             break;
            case NOT:
                notOp();            break;
            case REG:
                reg();              break;
            case PUSHN:
                pushN(item.second); break;
            case GET:
                get();              break;
            case PUT:
                put();              break;

            default:
                return false;
        }

    }

    return false;
}

void VirtualMachine::push(int var) {
    stack.push((*memory)[var]);
}

void VirtualMachine::pop(int var) {
    auto top = stack.top();
    memory->at(var) = top;
    stack.pop();
}

void VirtualMachine::add() {
    stackOperation([](int first, int second) { return first + second; });
}

void VirtualMachine::mul() {
    stackOperation([](int first, int second) { return first * second; });
}

void VirtualMachine::sub() {
    stackOperation([](int first, int second) { return first - second; });
}

void VirtualMachine::div() {
    stackOperation([](int first, int second) { return first / second; });
}

// jmp
//jmpif


void VirtualMachine::equal() {
    stackOperation([](int first, int second) { return first == second; });
}

void VirtualMachine::larger() {
    stackOperation([](int first, int second) { return first > second; });
}

void VirtualMachine::andOp() {
    stackOperation([](int first, int second) { return first && second; });
}

void VirtualMachine::orOp() {
    stackOperation([](int first, int second) { return first || second; });
}

void VirtualMachine::notOp() {
    auto top = stack.top();
    stack.push(!top);
    stack.pop();
}

void VirtualMachine::reg() {
    memory->push_back(0);
}

void VirtualMachine::pushN(int number) {
    stack.push(number);
}

void VirtualMachine::get() {
    auto value = int();
    std::cin >> value;
    stack.push(value);
}

void VirtualMachine::put() {
    int top = stack.top();
    std::cout << top;
    stack.pop();
}

void VirtualMachine::stackOperation(std::function<int (int, int)> operation) {
    auto first = stack.top();
    stack.pop();
    auto second =stack.top();
    stack.pop();

    stack.push(operation(first, second));
}
