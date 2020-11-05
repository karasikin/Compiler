#ifndef KEYWORD_H
#define KEYWORD_H

#include <memory>
#include <stack>
#include <vector>

enum class Instructions { PUSH, POP, ADD, MUL, SUB, DIV, JMP, JMPIF, EQUAL, LARGER, AND, OR, NOT, REG, PUSHN, GET, PUT };
enum class Type { BYTE = 10, CHAR = 11, INT = 40 };

typedef std::vector<std::pair<Instructions, int>> CodeDict;
typedef std::vector<std::pair<Type, int>> MemoryDict;
typedef std::stack<std::pair<Type, int>> StackDict;

#endif // KEYWORD_H
