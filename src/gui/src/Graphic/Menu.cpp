/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-vincent.shao
** File description:
** Menu
*/

#include "Menu.hpp"

Zappy::Menu::Menu()
{
    setCamera();
    setTexture();
    setCube();
    setRectangle();
    setMusic();
}

Zappy::Menu::~Menu()
{
    std::cout << "Menu Destroyed" << std::endl;
    UnloadMusicStream(_music);
    UnloadSound(_click);
}

void Zappy::Menu::setCamera()
{
    _cameraMenu.position = (Vector3){1.0f, 1.0f, 1.0f };  // Camera position
    _cameraMenu.target = (Vector3){1.0f, 1.0f, 1.0f + 2};      // Camera looking at point
    _cameraMenu.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    _cameraMenu.fovy = 70.0f;                                // Camera field-of-view Y
    _cameraMenu.projection = CAMERA_PERSPECTIVE;
}

void Zappy::Menu::setData(std::shared_ptr<Data> data)
{
    std::shared_ptr<Data> tmp(data, data.get());
    _data = tmp;
}

void Zappy::Menu::setMusic()
{
    _music = LoadMusicStream("src/gui/assets/Minecraft-Theme Song {Extended for 30 Minutes}.mp3");
    _click = LoadSound("src/gui/assets/click.ogg");
    PlayMusicStream(_music);
    SetMusicVolume(_music, _volume);
    SetSoundVolume(_click, 0.2);
}

void Zappy::Menu::setTexture()
{
    _texture.insert({"Pano0", raylib::Texture("src/gui/assets/panorama_0.png")});
    _texture.insert({"Pano1", raylib::Texture("src/gui/assets/panorama_1.png")});
    _texture.insert({"Pano2", raylib::Texture("src/gui/assets/panorama_2.png")});
    _texture.insert({"Pano3", raylib::Texture("src/gui/assets/panorama_3.png")});
    _texture.insert({"Pano4", raylib::Texture("src/gui/assets/panorama_4.png")});
    _texture.insert({"Pano5", raylib::Texture("src/gui/assets/panorama_5.png")});
    _texture.insert({"Logo", raylib::Texture("src/gui/assets/ZAPPy.png")});
    _texture.insert({"basicButton", raylib::Texture("src/gui/assets/basic_button.png")});
    _texture.insert({"hoverButton", raylib::Texture("src/gui/assets/hover_button.png")});
}

void Zappy::Menu::setRectangle()
{
    _rectangle.insert({"menuLogo", std::make_shared<Rect>(_texture["Logo"])});
    _rectangle.insert({"menuPlayButton", std::make_shared<Rect>(_texture["basicButton"])});
    _rectangle.insert({"menuSettingsButton", std::make_shared<Rect>(_texture["basicButton"])});
    _rectangle.insert({"menuQuitButton", std::make_shared<Rect>(_texture["basicButton"])});
    _rectangle.insert({"menuHoverButton", std::make_shared<Rect>(_texture["hoverButton"])});
    _rectangle.insert({"volumeUp", std::make_shared<Rect>(_texture["basicButton"])});
    _rectangle.insert({"volumeDown", std::make_shared<Rect>(_texture["basicButton"])});
    _rectangle.insert({"30_fps", std::make_shared<Rect>(_texture["basicButton"])});
    _rectangle.insert({"60_fps", std::make_shared<Rect>(_texture["basicButton"])});
    _rectangle.insert({"90_fps", std::make_shared<Rect>(_texture["basicButton"])});
}

void Zappy::Menu::setCube()
{
    _cube.insert({"menuTop", Cube(_texture["Pano4"].GetId(), _texture["Pano4"].GetId(), _texture["Pano4"].GetId())});
    _cube.insert({"menuBot", Cube(_texture["Pano5"].GetId(), _texture["Pano5"].GetId(), _texture["Pano5"].GetId())});
    _cube.insert({"menuFront", Cube(_texture["Pano0"].GetId(), _texture["Pano0"].GetId(), _texture["Pano0"].GetId())});
    _cube.insert({"menuRight", Cube(_texture["Pano1"].GetId(), _texture["Pano1"].GetId(), _texture["Pano1"].GetId())});
    _cube.insert({"menuBack", Cube(_texture["Pano2"].GetId(), _texture["Pano2"].GetId(), _texture["Pano2"].GetId())});
    _cube.insert({"menuLeft", Cube(_texture["Pano3"].GetId(), _texture["Pano3"].GetId(), _texture["Pano3"].GetId())});
}

void Zappy::Menu::run()
{
    UpdateMusicStream(_music);
    if (_settings == true)
        settingsEvent();
    else
        event();
    draw();
}

void Zappy::Menu::event()
{
    mouseHovering();
    mouseClicking();
}

void Zappy::Menu::settingsEvent()
{
    if (IsKeyPressed(KEY_ENTER)) {
        _settings = false;
    }
    settingsButtonEvent();
}

void Zappy::Menu::volumeEvent(std::string volume)
{
    if (volume == "volumeUp") {
        if (_volume < 1.0f)
            _volume -= 0.1f;
    } else if (volume == "volumeDown") {
        if (_volume > 0.0f)
            _volume += 0.1f;
    }
    SetMusicVolume(_music, _volume);
}

void Zappy::Menu::framerateEvent(std::string framerate)
{
    if (framerate == "30_fps") {
        SetTargetFPS(30);
    } else if (framerate == "60_fps") {
        SetTargetFPS(60);
    } else if (framerate == "90_fps") {
        SetTargetFPS(90);
    }
}

void Zappy::Menu::settingsButtonEvent()
{
    Vector2 mouse = GetMousePosition();

    auto it = _rectangle.begin();

    for (; it != _rectangle.end(); ++it) {
        if (CheckCollisionPointRec(mouse, it->second->getRect())) {
            it->second->setTexture(_texture["hoverButton"]);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (it->first == "volumeUp" || it->first == "volumeDown") {
                    PlaySound(_click);
                    volumeEvent(it->first);
                } 
                if (it->first == "30_fps" || it->first == "60_fps" || it->first == "90_fps") {
                    PlaySound(_click);
                    framerateEvent(it->first);
                }
            }
        } else if (it->first == "volumeUp" || it->first == "volumeDown" || it->first == "30_fps" || it->first == "60_fps" || it->first == "90_fps")
            it->second->setTexture(_texture["basicButton"]);
    }
}

void Zappy::Menu::drawBackground()
{
    float size = 2;

    _cameraMenu.Update(Vector3 {0.0f,0.0f,0.0f}, Vector3{0.005f, 0.0000f, 0.0f}, 0.0);
    _cameraMenu.BeginMode();
    _cube["menuBack"].drawBlockTexture(Vector3{1.0f, 1.0f, 1.0f - size}, Vector3{size, size, size}, WHITE);
    _cube["menuLeft"].drawBlockTexture(Vector3{1.0f - size, 1.0f, 1.0f}, Vector3 {size, size, size}, WHITE);
    _cube["menuFront"].drawBlockTexture(Vector3{1.0f, 1.0f, 1.0f + size}, Vector3{size, size, size}, WHITE);
    _cube["menuRight"].drawBlockTexture(Vector3{1.0f + size, 1.0f, 1.0f}, Vector3 {size, size, size}, WHITE);
    _cube["menuTop"].drawBlockTexture(Vector3{1.0f, 1.0f + size, 1.0f}, Vector3 {size, size, size}, WHITE);
    _cube["menuBot"].drawBlockTexture(Vector3{1.0f, 1.0f - size, 1.0f}, Vector3 {size, size, size}, WHITE);
    _cameraMenu.EndMode();
}

void Zappy::Menu::draw()
{
    drawBackground();
    if (!_settings && _data->_gameData._menu == true) {
        drawLogo();
        drawButton();
        drawText();
    } else
        drawSettings();
}

void Zappy::Menu::drawLogo()
{
    _rectangle["menuLogo"]->drawRect(744, 212, {600, 150});
}

void Zappy::Menu::drawButton()
{
    _rectangle["menuPlayButton"]->drawRect(1000, 100, {470, 450});
    _rectangle["menuSettingsButton"]->drawRect(1000, 100, {470, 650});
    _rectangle["menuQuitButton"]->drawRect(1000, 100, {470, 850});
}

void Zappy::Menu::drawText()
{
    DrawText("Play", 900, 470, 50, WHITE);
    DrawText("Settings", 850, 670, 50, WHITE);
    DrawText("Quit", 900, 870, 50, WHITE);
}

void Zappy::Menu::drawVolume()
{
    _rectangle["volumeUp"]->drawRect(200, 100, {670, 350});
    _rectangle["volumeDown"]->drawRect(200, 100, {1070, 350});
    DrawText("Volume", 860, 200, 70, WHITE);
    DrawText("-", 765, 370, 50, WHITE);
    DrawText("+", 1165, 370, 50, WHITE);
    DrawText("Press [Enter] to go back", 1200, 970, 50, WHITE);
}

void Zappy::Menu::drawFramerate()
{
    DrawText("FPS", 900, 500, 70, WHITE);
    _rectangle["30_fps"]->drawRect(200, 100, {470, 640});
    _rectangle["60_fps"]->drawRect(200, 100, {870, 640});
    _rectangle["90_fps"]->drawRect(200, 100, {1270, 640});
    DrawText("30", 550, 660, 50, WHITE);
    DrawText("60", 950, 660, 50, WHITE);
    DrawText("90", 1350, 660, 50, WHITE);
}

void Zappy::Menu::drawSettings()
{
    if (_settings == true) {
        drawVolume();
        drawFramerate();
    }
}

void Zappy::Menu::mouseClicking()
{
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        auto it = _rectangle.begin();
        std::advance(it, 2);
        for (; it != _rectangle.end(); ++it) {
            if (CheckCollisionPointRec(mousePos, it->second->getRect())) {
                PlaySound(_click);
                if (it->first == "menuPlayButton")
                    _data->_gameData._menu = false;
                else if (it->first == "menuSettingsButton")
                    _settings = true;
                else if (it->first == "menuQuitButton")
                    _data->_gameData._end = true;
            }
        }
    }
}

void Zappy::Menu::mouseHovering()
{
    Vector2 mousePos = GetMousePosition();

    auto it = _rectangle.begin();
    std::advance(it, 2);

    if (_settings != true) {
        for (; it != _rectangle.end(); ++it) {
            if (CheckCollisionPointRec(mousePos, it->second->getRect()) && it->first != "menuLogo")
                it->second->setTexture(_texture["hoverButton"]);
            else if (it->first == "menuPlayButton" || it->first == "menuSettingsButton" || it->first == "menuQuitButton")
                it->second->setTexture(_texture["basicButton"]);
        }
    }
}