#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "PlayerStats.h"
#include <stdlib.h>

#define MAX_STATS 5

static bool writeToFile(const std::string& path, const PlayerStats stats[MAX_STATS])
{
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs)
        return false;
    ofs.write((char*)stats, sizeof(PlayerStats) * MAX_STATS);
    ofs.close();
    return true;
}

static bool readFromFile(const std::string& path, PlayerStats stats[MAX_STATS])
{
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs)
        return false;
    ifs.read((char*)stats, sizeof(PlayerStats) * MAX_STATS);
    ifs.close();
    return true;
}
