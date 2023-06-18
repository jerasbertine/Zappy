/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-vincent.shao
** File description:
** Gameplay
*/

#include "Gameplay.hpp"

Zappy::Gameplay::Gameplay()
{
    setCamera();
    setTexture();
    setCube();
}

Zappy::Gameplay::~Gameplay()
{
    std::cout << "Gameplay Destroyed" << std::endl;
}

void Zappy::Gameplay::setData(std::shared_ptr<Data> data)
{
    std::shared_ptr<Data> tmp(data, data.get());
    _data = tmp;
}

void Zappy::Gameplay::setCamera()
{
    _camera.position = (Vector3){0.0f, 40.0f, 10.0f};    // Camera position
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    _camera.up = (Vector3){ 0.0f, 10.0f, 0.0f };          // Camera up vector (rotation towards target)
    _camera.fovy = 45.0f;                                // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;
    _cameraMove = false;
    _cameraMode = CAMERA_ORBITAL;
}

void Zappy::Gameplay::setTexture()
{
    _shader.insert({"waterWave", LoadShader(0, TextFormat("src/gui/assets/shaders/wave.fs"))});

    _texture.insert({"grassSide", raylib::Texture("src/gui/assets/grass_block_side.png")});
    _texture.insert({"grassTop", raylib::Texture("src/gui/assets/grass_block_top.png")});
    _texture.insert({"water", raylib::Texture("src/gui/assets/water_flow.png")});
    _texture.insert({"dirt", raylib::Texture("src/gui/assets/dirt.png")});
    _texture.insert({"clearbackground", raylib::Texture("src/gui/assets/clearbackground.png")});

    _texture.insert({"beef", raylib::Texture("src/gui/assets/beef_cooked.png")});
    _texture.insert({"carrot", raylib::Texture("src/gui/assets/carrot_golden.png")});
    _texture.insert({"coal", raylib::Texture("src/gui/assets/coal.png")});
    _texture.insert({"diamond", raylib::Texture("src/gui/assets/diamond.png")});
    _texture.insert({"emerald", raylib::Texture("src/gui/assets/emerald.png")});
    _texture.insert({"gold", raylib::Texture("src/gui/assets/gold_ingot.png")});
    _texture.insert({"iron", raylib::Texture("src/gui/assets/iron_ingot.png")});
    _texture.insert({"netherStar", raylib::Texture("src/gui/assets/nether_star.png")});
    _texture.insert({"quartz", raylib::Texture("src/gui/assets/quartz.png")});
}

void Zappy::Gameplay::setCube()
{
    _cube.insert({"water", Cube(_texture["water"].GetId(), _texture["clearbackground"].GetId(), _texture["water"].GetId(), _shader["waterWave"])});
    _cube.insert({"grass", Cube(_texture["grassTop"].GetId(), _texture["grassSide"].GetId(), _texture["dirt"].GetId())});
    _cube.insert({"beef", Cube(_texture["beef"].GetId())});
    _cube.insert({"Thystame", Cube(_texture["netherStar"].GetId())});
    _cube.insert({"Phiras", Cube(_texture["emerald"].GetId())});
    _cube.insert({"Mendiane", Cube(_texture["diamond"].GetId())});
    _cube.insert({"Sibur", Cube(_texture["gold"].GetId())});
    _cube.insert({"Deraumere", Cube(_texture["iron"].GetId())});
    _cube.insert({"Linemate", Cube(_texture["coal"].GetId())});
    _cube.insert({"Food", Cube(_texture["carrot"].GetId())});

}

void Zappy::Gameplay::run()
{
    event();
    draw();
}

void Zappy::Gameplay::event()
{
    cameraEvent();
}

void Zappy::Gameplay::cameraEvent()
{
    if (IsKeyPressed(KEY_SPACE))
        _cameraMove = !_cameraMove;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)) {
        _cameraMode = CAMERA_THIRD_PERSON;
        return;
    }
    if (_cameraMove == true)
        _cameraMode = CAMERA_ORBITAL;
    else 
        _cameraMode = CAMERA_THIRD_PERSON;
}

void Zappy::Gameplay::draw()
{
    _camera.Update(_cameraMode);
    _camera.BeginMode();
    drawMap();
     _camera.EndMode();
}

void Zappy::Gameplay::drawMap()
{
    auto mapSize = _data->_gameData._mapSize;
    for (std::size_t x = 0; x != mapSize.first; x++)
        for (std::size_t y = 0; y != mapSize.second; y++) {
            drawTile(x, y, mapSize);
        }

    _cube["water"].drawWaterTexture((Vector3){0, 0.9, 0}, (Vector3){200, 0.9, 200}, GRAY);
}

void Zappy::Gameplay::drawTile(std::size_t x, std::size_t y, std::pair<std::size_t, std::size_t> map)
{
    float size = 3.0f;
    int midX = map.first / 2;
    int midY = map.second / 2;
    float posX = size * x - (midX * size);
    float posY = size * y - (midY * size);
    float posZ = size / 2;
    DrawCubeWiresV((Vector3){posX, posZ +5.0, posY}, (Vector3){size, size, size}, BLACK);
    _cube["grass"].drawBlockTexture((Vector3){posX, posZ, posY}, (Vector3){size, size, size}, WHITE);
    drawItem((Vector3){posX, posY, posZ}, size, _data->_gameData._map[x][y].getRessources());
}

void Zappy::Gameplay::drawItem(Vector3 pos, std::size_t size, std::vector<std::shared_ptr<IRessource>> rss)
{
    bool floor = true;
    std::vector<std::string> ressource = {"Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame"};
    for (std::size_t i = 0; i != rss.size(); i++) {
        auto qty = rss[i]->getQuantity();
        if (qty > 0)
            drawSpacedItem(qty, pos, ressource[i]);
    }
}

void Zappy::Gameplay::drawSpacedItem(std::size_t qty, Vector3 pos, std::string ressource)
{
    // bool floor = true;
    // for (std::size_t a = 0; a != qty; a++)
    // {
    //     if (floor)
    //         _cube[ressource[i]].drawItemTextureFloor((Vector3){pos.x - (size / 2) + i * 0.5, pos.z + size - 0.2, pos.y - (size / 2)}, (Vector3){1.2, 1.2, 1.2}, LIGHTGRAY);
    //     else 
    //         _cube[ressource[i]].drawItemTextureAnimated((Vector3){pos.x, pos.z + size - 0.2, pos.y}, (Vector3){1.2, 1.2, 1.2}, LIGHTGRAY);
    // }
    // _cube[ressource[i]].AnimateItem((Vector3){1.2, 1.2, 1.2});

}