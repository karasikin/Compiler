#ifndef PARSER_H
#define PARSER_H

#include <map>
#include "keyword.h"

class Parser {

public:

    const std::map<std::string, Instructions> instructionMap;
    const std::map<std::string, Type> typeMap;

public:

    Parser();

    std::unique_ptr<CodeDict> parse(const std::string &filename);
    void readCodeFromFile(const std::string &filename);

private:

    std::vector<std::pair<std::string, std::string>> rowCode;
    std::map<std::string, int> variables;
    int varCount;

private:

    Type parseRegArgument(const std::string &arg);
    int parsePushArgument(const std::string &arg) const;
    int parsePopArgument(const std::string &arg) const;
    int parseJmpArgument(const std::string &arg) const;
    int parseJmpifArgument(const std::string &arg) const;
    int parsePushNArgument(const std::string &arg) const;

    void registerVariable(const std::string &name);
    int tryGetNumber(const std::string &arg) const;

    void clear();
};

#endif // PARSER_H
