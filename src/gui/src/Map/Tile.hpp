/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-vincent.shao
** File description:
** Tile
*/

#ifndef TILE_HPP_
#define TILE_HPP_
    #include <memory>
    #include <vector>
    #include <string>
    #include <sstream>
    #include <iostream>

    #include "IRessource.hpp"
    #include "RessourceFactory.hpp"

namespace Zappy {
    class Tile {
        public:
            Tile();
            Tile(int x, int y) { printf("X = %d, Y = %d\n", x, y); };
            Tile(std::string &content);
            ~Tile();

        protected:
        private:
            std::vector<std::shared_ptr<IRessource>> _ressources;
    };
};

#endif /* !TILE_HPP_ */
