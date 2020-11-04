#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <memory>
#include <stack>
#include <vector>
#include <map>
#include <functional>



class VirtualMachine {

public:
    enum Instructions { PUSH, POP, ADD, MUL, SUB, DIV, JMP, JMPIF, EQUAL, LARGER, AND, OR, NOT, REG, PUSHN, GET, PUT };

    typedef std::vector<std::pair<VirtualMachine::Instructions, int>> Dict;

public:

    VirtualMachine();

    bool execute(const Dict &code);

    void push(int var);
    void pop(int var);
    void add();
    void mul();
    void sub();
    void div();
// jmp
// jmpif

    void equal();
    void larger();
    void andOp();
    void orOp();
    void notOp();
    void reg();
    void pushN(int number);
    void get();
    void put();

private:

    void stackOperation(std::function<int (int, int)> operation);

private:

    std::stack<int> stack;
    std::unique_ptr<std::vector<int>> memory;

};

#endif // VIRTUALMACHINE_H
