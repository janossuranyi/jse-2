#ifndef JSE_INPUTDRV_SDL_H
#define JSE_INPUTDRV_SDL_H

#include "input/InputService.hpp"
#include "input/InputTypes.hpp"
#include <list>
#include <vector>
#include <mutex>
#include <SDL.h>

namespace jse::input {

    using namespace core::math;

    class InputServiceSDL : public InputService
    {
    public:
        InputServiceSDL();
        ~InputServiceSDL();

        bool IsKeyDown(const Key aKey);
        bool IsButtonDown(const MouseButton aButton) const;
        KeyPress GetKeyPressed();
        KeyPress GetKeyReleased();
        bool IsKeyPressed();
        bool IsKeyReleased() ;
        ivec2 GetMousePosition() const;

        void SetRelativeMouseMode(const bool a0);
        ivec2 GetRelativeMousePosition() const;

        bool IsWheelUpMoved() const;
        bool IsWheelDownMoved() const;

        void Update();

        bool IsQuitMessagePosted();
    private:
        Key SDLToKey(const int aKey);
        MouseButton SDLToButton(const int aBtn);
        void UpdateKeyboard();
        void UpdateMouse();
        void AddKeyToList(int aSDLMod, Key aKey, int aUnicode, std::list<KeyPress>& aKeys);

        bool quitMessagePosted;
        bool wheelUpMoved;
        bool wheelDownMoved;

        ivec2 mousePos;
        std::list<SDL_Event> events;
        std::list<KeyPress> keysPressed;
        std::list<KeyPress> keysReleased;
        std::vector<bool> keyState;
        std::vector<bool> mouseState;
    };

}

#endif