#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <regex>

enum baseCommand {
    vswitch = 1,
    pmove = 2,
};

enum moveDirection {
    up = 1,
    right = 2,
    down = 3,
    left = 4,
};

struct regexCommand {

};

class Commands
{
public:
    Commands();
    std::vector<std::pair<std::regex,baseCommand>> baseMap;
    std::vector<std::pair<std::regex,moveDirection>> directionMap;

    template <typename EnumType>
    EnumType resolve(std::string query, std::vector<std::pair<std::regex, EnumType>> mapping) {
        for (auto& t : mapping) {
            if (std::regex_search(query,t.first))
                return t.second;
        }
        throw(query);
    }
};

#endif // COMMANDS_H
