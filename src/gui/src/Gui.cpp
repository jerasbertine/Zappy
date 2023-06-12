/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Gui
*/

#include "Gui.hpp"

Zappy::Gui::Gui(int port, std::string machine) : _graphic(SCREEN_WIDTH, SCREEN_HEIGHT, "Zappy")
{
    _data = std::make_shared<Data>(machine, port);
    _graphic.setData(_data);
    std::cout << "Port = " << port << std::endl;
    std::cout << "Machine = " << machine << std::endl;
    _isRunning = true;
}

Zappy::Gui::~Gui()
{
    if (_dataReceiver.joinable())
        _dataReceiver.join();
}

void Zappy::Gui::run()
{
    _dataReceiver = std::thread(&Zappy::Gui::receiveServerData, std::ref(*this));
    _graphic.run(_isRunning);
}

void Zappy::Gui::receiveServerData()
{
    while (_isRunning)
    {
        _data->updateGame();
        // std::cout << &_data << std::endl;
    }
}