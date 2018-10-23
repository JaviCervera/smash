#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#define MOUSE_LEFT       0
#define MOUSE_RIGHT      1
#define MOUSE_MIDDLE     2

class Input {
public:
    // Mouse
    static void ShowMouse(bool show);
    static void MoveMouse(int x, int y);
    static int MouseX();
    static int MouseY();
    static bool MouseButtonPressed(int button);

    // Keyboard
    static bool KeyPressed(int key);
protected:
    Input() {}
    ~Input() {}
};

#endif // GAME_INPUT_H
