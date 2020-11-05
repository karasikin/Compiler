#include "virtualmachine.h"

#include <iostream>

VirtualMachine::VirtualMachine()
{
    memory = std::make_unique<MemoryDict>();
}

bool VirtualMachine::execute(const CodeDict &code) {
    for(auto i = 0ul; i < code.size(); ++i) {
        switch(code[i].first) {
            case Instructions::PUSH:
                push(code[i].second);  break;
            case Instructions::POP:
                pop(code[i].second);   break;
            case Instructions::ADD:
                add();              break;
            case Instructions::MUL:
                mul();              break;
            case Instructions::SUB:
                sub();              break;
            case Instructions::DIV:
                div();              break;
            case Instructions::JMP:
                jmp(code, i);       break;
            case Instructions::JMPIF:
                jmpif(code, i);     break;
            case Instructions::EQUAL:
                equal();            break;
            case Instructions::LARGER:
                larger();           break;
            case Instructions::AND:
                andOp();            break;
            case Instructions::OR:
                orOp();             break;
            case Instructions::NOT:
                notOp();            break;
            case Instructions::REG:
                reg(Type(code[i].second));  break;
            case Instructions::PUSHN:
                pushN(code[i].second); break;
            case Instructions::GET:
                get();              break;
            case Instructions::PUT:
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
    memory->at(var).second = top.second;
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

void VirtualMachine::jmp(const CodeDict &code, ulong &current) {
    current = code[current].second - 1;
}

void VirtualMachine::jmpif(const CodeDict &code, ulong &current) {
    if(stack.top().second) {
        current = code[current].second - 1;
    }

    stack.pop();
}

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
    stack.pop();
    stack.push({ top.first, !top.second });
}

void VirtualMachine::reg(Type type) {
    memory->push_back({type, 0});
}

void VirtualMachine::pushN(int number) {
    stack.push({ Type::INT, number });
}

void VirtualMachine::get() {
    auto value = int();
    std::cin >> value;
    stack.push({ Type::INT, value });
}

void VirtualMachine::put() {
    auto top = stack.top();

    if(top.first == Type::CHAR) {
        std::cout << char(top.second);
    } else {
        std::cout << top.second;
    }

    stack.pop();
}

void VirtualMachine::stackOperation(std::function<int (int, int)> operation) {
    auto left = stack.top();
    stack.pop();
    auto right = stack.top();
    stack.pop();

    stack.push({ left.first, operation(left.second, right.second) });
}
