#include "parser.h"

#include <iostream>
#include <fstream>

#include "exceptions.h"

Parser::Parser()
    : instructionMap({
        { "PUSH", Instructions::PUSH },
        { "POP", Instructions::POP },
        { "ADD", Instructions::ADD },
        { "MUL", Instructions::MUL },
        { "SUB", Instructions::SUB },
        { "DIV", Instructions::DIV },
        { "JMP", Instructions::JMP },
        { "JMPIF", Instructions::JMPIF },
        { "EQUAL", Instructions::EQUAL },
        { "LARGER", Instructions::LARGER },
        { "AND", Instructions::AND },
        { "OR", Instructions::OR },
        { "NOT", Instructions::NOT },
        { "REG", Instructions::REG },
        { "PUSHN", Instructions::PUSHN },
        { "GET", Instructions::GET },
        { "PUT", Instructions::PUT }
      }),
      typeMap({
        { "BYTE", Type::BYTE },
        { "CHAR", Type::CHAR },
        { "INT", Type::INT }
              }),
      variables(),
      varCount(int())
{

}

std::unique_ptr<CodeDict> Parser::parse(const std::string &filename) {
    readCodeFromFile(filename);

    auto code = std::make_unique<CodeDict>();

    for(const auto &item : rowCode) {

        auto it_instructionMap = instructionMap.find(item.first);
        if(it_instructionMap == instructionMap.end()) {
            throw InvalidOperatorException(item.first);
        }

        auto currentInstruction = it_instructionMap->second;
        auto currentArg = int();

        switch (currentInstruction) {
            case Instructions::REG:
                currentArg = int(parseRegArgument(item.second));  break;
            case Instructions::PUSH:
                currentArg = parsePushArgument(item.second);      break;
            case Instructions::POP:
                currentArg = parsePopArgument(item.second);       break;
            case Instructions::JMP:
                currentArg = parseJmpArgument(item.second);       break;
            case Instructions::JMPIF:
                currentArg = parseJmpifArgument(item.second);     break;
            case Instructions::PUSHN:
                currentArg = parsePushNArgument(item.second);     break;

            default:
                currentArg = 0;
        }

        code->push_back({ currentInstruction, currentArg });
    }

    clear();

    return code;
}

void Parser::readCodeFromFile(const std::string &filename) {
    auto input = std::ifstream(filename, std::ios::in);

    if(!input) {
        throw std::ios_base::failure("Error opening file:" + filename);
    }

    rowCode.clear();

    while(!input.eof()) {
        auto instruction = std::string();
        auto arg = std::string();

        input >> instruction;

        if(instruction.front() == '#') {
            std::getline(input, instruction);
            continue;
        }

        if(instruction.empty()) {
            continue;
        }

        input >> arg;

        if(input.eof()) {            /// Зачекать
            break;
        }

        rowCode.push_back({ instruction, arg });
    }

    input.close();
}

Type Parser::parseRegArgument(const std::string &arg) {
    auto name = arg.substr(0, arg.find(':'));
    auto type = arg.substr(arg.find(':') + 1);

    registerVariable(name);

    auto it = typeMap.find(type);

    if(it == typeMap.end()) {
        throw InvalidTypeException(arg);
    }

    return it->second;
}

void Parser::registerVariable(const std::string &name) {
    auto it = variables.find(name);

    if(it != variables.end()) {
        throw RedeclarationVariableException(name);
    }

    variables[name] = varCount++;
}

int Parser::parsePushArgument(const std::string &arg) const {
    auto it_variables = variables.find(arg);

    if(it_variables == variables.end()) {
        throw NotDeclaredVariableException(arg);
    }

    return it_variables->second;
}

int Parser::parsePopArgument(const std::string &arg) const {
    return parsePushArgument(arg);
}

int Parser::parseJmpArgument(const std::string &arg) const {
    return tryGetNumber(arg);
}


int Parser::parseJmpifArgument(const std::string &arg) const {
    return tryGetNumber(arg);
}

int Parser::parsePushNArgument(const std::string &arg) const {
    return tryGetNumber(arg);
}

int Parser::tryGetNumber(const std::string &arg) const {
    return std::stoi(arg);
}

void Parser::clear() {
    rowCode.clear();
    variables.clear();
    varCount = 0;
}
