#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H


#include <functional>

#include "keyword.h"


class VirtualMachine {

public:

    VirtualMachine();

    bool execute(const CodeDict &code);

    void push(int var);
    void pop(int var);
    void add();
    void mul();
    void sub();
    void div();
    void jmp(const CodeDict &code, ulong &current);
    void jmpif(const CodeDict &code, ulong &current);
    void equal();
    void larger();
    void andOp();
    void orOp();
    void notOp();
    void reg(Type type);
    void pushN(int number);
    void get();
    void put();

private:

    void stackOperation(std::function<int (int, int)> operation);

private:

    StackDict stack;
    std::unique_ptr<MemoryDict> memory;

};

#endif // VIRTUALMACHINE_H
