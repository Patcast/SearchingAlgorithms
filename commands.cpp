#include "commands.h"

Commands::Commands()
{
    baseMap.push_back(std::make_pair(std::regex("^v.*"),vswitch));
    baseMap.push_back(std::make_pair(std::regex("^m.*"),pmove));
    baseMap.push_back(std::make_pair(std::regex("^h.*"),heuristic));
    baseMap.push_back(std::make_pair(std::regex("^s.*"),speed));

    directionMap.push_back(std::make_pair(std::regex("^u.*"),up));
    directionMap.push_back(std::make_pair(std::regex("^r.*"),right));
    directionMap.push_back(std::make_pair(std::regex("^l.*"),left));
    directionMap.push_back(std::make_pair(std::regex("^d.*"),down));
}

