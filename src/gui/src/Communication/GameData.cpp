/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-vincent.shao
** File description:
** GameData
*/

#include "GameData.hpp"

// Zappy::GameData::GameData()
// {
// }

Zappy::GameData::~GameData()
{
}

void Zappy::GameData::msz(std::vector<std::string> &content)
{
    if (content.size() != 2)
        throw Error("Error server response MSZ args", "Expected: 2, Got: " + std::to_string(content.size()));
    _mapSize = std::make_pair(std::stoi(content[0]), std::stoi(content[1]));
    for (std::size_t x = 0; x != _mapSize.first; x++) {
        std::vector<Tile> tmp;
        for (std::size_t y = 0; y != _mapSize.second; y++) {
            tmp.push_back(Tile(x, y));
        }
        _map.push_back(tmp);
    }
}

void Zappy::GameData::bct(std::vector<std::string> &content)
{
    std::cout << "bct" << std::endl;
}

void Zappy::GameData::tna(std::vector<std::string> &content)
{
    std::cout << "tna" << std::endl;
}

void Zappy::GameData::pnw(std::vector<std::string> &content)
{
    std::cout << "pnw" << std::endl;
}

void Zappy::GameData::ppo(std::vector<std::string> &content)
{
    std::cout << "ppo" << std::endl;
}

void Zappy::GameData::plv(std::vector<std::string> &content)
{
    std::cout << "plv" << std::endl;
}

void Zappy::GameData::pin(std::vector<std::string> &content)
{
    std::cout << "pin" << std::endl;
}

void Zappy::GameData::pex(std::vector<std::string> &content)
{
    std::cout << "pex" << std::endl;
}

void Zappy::GameData::pbc(std::vector<std::string> &content)
{
    std::cout << "pbc" << std::endl;
}

void Zappy::GameData::pic(std::vector<std::string> &content)
{
    std::cout << "pic" << std::endl;
}

void Zappy::GameData::pie(std::vector<std::string> &content)
{
    std::cout << "pie" << std::endl;
}

void Zappy::GameData::pfk(std::vector<std::string> &content)
{
    std::cout << "pfk" << std::endl;
}

void Zappy::GameData::pdr(std::vector<std::string> &content)
{
    std::cout << "pdr" << std::endl;
}

void Zappy::GameData::pgt(std::vector<std::string> &content)
{
    std::cout << "pgt" << std::endl;
}

void Zappy::GameData::pdi(std::vector<std::string> &content)
{
    std::cout << "pdi" << std::endl;
}

void Zappy::GameData::enw(std::vector<std::string> &content)
{
    std::cout << "enw" << std::endl;
}

void Zappy::GameData::ebo(std::vector<std::string> &content)
{
    std::cout << "ebo" << std::endl;
}

void Zappy::GameData::edi(std::vector<std::string> &content)
{
    std::cout << "edi" << std::endl;
}

void Zappy::GameData::sgt(std::vector<std::string> &content)
{
    std::cout << "sgt" << std::endl;
}

void Zappy::GameData::sst(std::vector<std::string> &content)
{
    std::cout << "sst" << std::endl;
}

void Zappy::GameData::seg(std::vector<std::string> &content)
{
    std::cout << "seg" << std::endl;
}

void Zappy::GameData::smg(std::vector<std::string> &content)
{
    std::cout << "smg" << std::endl;
}

void Zappy::GameData::suc(std::vector<std::string> &content)
{
    std::cout << "suc: unknow command" << std::endl;
}

void Zappy::GameData::sbp(std::vector<std::string> &content)
{
    std::cout << "sbp" << std::endl;
}
