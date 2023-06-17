/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-vincent.shao
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

    #include <map>
    #include <string>
    #include "raylib-cpp.hpp"
    #include "Cube.hpp"
    #include "Rectangle.hpp"
    #include <memory>

namespace Zappy {
    class Menu {
        public:
            Menu();
            ~Menu();

            void setData(std::shared_ptr<Data>);
            void setCamera();
            void setTexture();
            void setCube();
            void setRectangle();
            void setMusic();
            void run();

            void event();

            void draw();
            void drawText();
            void drawLogo();
            void drawButton();
            void drawBackground();

            void playSound();
            void playMusic();

            void mouseHovering();
            void mouseClicking();
        protected:
        private:
            raylib::Camera3D _cameraMenu;

            std::map<std::string, raylib::Texture2D> _texture;
            std::map<std::string, std::shared_ptr<Rect>> _rectangle;
            std::map<std::string, Cube> _cube;
            std::shared_ptr<Data> _data;

            raylib::Music _music;
            raylib::Sound _click;
    };
}

#endif /* !MENU_HPP_ */
