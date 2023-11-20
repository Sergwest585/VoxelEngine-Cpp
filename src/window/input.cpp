#include "input.h"
#include <GLFW/glfw3.h>

int keycode::ENTER = GLFW_KEY_ENTER;
int keycode::TAB = GLFW_KEY_TAB;
int keycode::SPACE = GLFW_KEY_SPACE;
int keycode::BACKSPACE = GLFW_KEY_BACKSPACE;
int keycode::LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT;
int keycode::LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL;
int keycode::LEFT_ALT = GLFW_KEY_LEFT_ALT;
int keycode::RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT;
int keycode::RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL;
int keycode::RIGHT_ALT = GLFW_KEY_RIGHT_ALT;
int keycode::ESCAPE = GLFW_KEY_ESCAPE;
int keycode::CAPS_LOCK = GLFW_KEY_CAPS_LOCK;
int keycode::LEFT = GLFW_KEY_LEFT;
int keycode::RIGHT = GLFW_KEY_RIGHT;
int keycode::DOWN = GLFW_KEY_DOWN;
int keycode::UP = GLFW_KEY_UP;
int keycode::F1 = GLFW_KEY_F1;
int keycode::F2 = GLFW_KEY_F2;
int keycode::F3 = GLFW_KEY_F3;
int keycode::F4 = GLFW_KEY_F4;
int keycode::F5 = GLFW_KEY_F5;
int keycode::F6 = GLFW_KEY_F6;
int keycode::F7 = GLFW_KEY_F7;
int keycode::F8 = GLFW_KEY_F8;
int keycode::F9 = GLFW_KEY_F9;
int keycode::F10 = GLFW_KEY_F10;
int keycode::F11 = GLFW_KEY_F11;
int keycode::F12 = GLFW_KEY_F12;
int keycode::A = GLFW_KEY_A;
int keycode::B = GLFW_KEY_B;
int keycode::C = GLFW_KEY_C;
int keycode::D = GLFW_KEY_D;
int keycode::E = GLFW_KEY_E;
int keycode::F = GLFW_KEY_F;
int keycode::G = GLFW_KEY_G;
int keycode::H = GLFW_KEY_H;
int keycode::I = GLFW_KEY_I;
int keycode::J = GLFW_KEY_J;
int keycode::K = GLFW_KEY_K;
int keycode::L = GLFW_KEY_L;
int keycode::M = GLFW_KEY_M;
int keycode::N = GLFW_KEY_N;
int keycode::O = GLFW_KEY_O;
int keycode::P = GLFW_KEY_P;
int keycode::Q = GLFW_KEY_Q;
int keycode::R = GLFW_KEY_R;
int keycode::S = GLFW_KEY_S;
int keycode::T = GLFW_KEY_T;
int keycode::U = GLFW_KEY_U;
int keycode::V = GLFW_KEY_V;
int keycode::W = GLFW_KEY_W;
int keycode::X = GLFW_KEY_X;
int keycode::Y = GLFW_KEY_Y;
int keycode::Z = GLFW_KEY_Z;
int keycode::NUM_0 = GLFW_KEY_0;
int keycode::NUM_1 = GLFW_KEY_1;
int keycode::NUM_2 = GLFW_KEY_2;
int keycode::NUM_3 = GLFW_KEY_3;
int keycode::NUM_4 = GLFW_KEY_4;
int keycode::NUM_5 = GLFW_KEY_5;
int keycode::NUM_6 = GLFW_KEY_6;
int keycode::NUM_7 = GLFW_KEY_7;
int keycode::NUM_8 = GLFW_KEY_8;
int keycode::NUM_9 = GLFW_KEY_9;

const char* keycode::name(int code) {
    const char* name = glfwGetKeyName(code, glfwGetKeyScancode(code));
    if (name == nullptr) {
        switch (code) {
            case GLFW_KEY_TAB: return "Tab";
            case GLFW_KEY_LEFT_CONTROL: return "Left Ctrl";
            case GLFW_KEY_RIGHT_CONTROL: return "Right Ctrl";
            case GLFW_KEY_LEFT_ALT: return "Left Alt";
            case GLFW_KEY_RIGHT_ALT: return "Right Alt";
            case GLFW_KEY_LEFT_SHIFT: return "Left Shift";
            case GLFW_KEY_RIGHT_SHIFT: return "Right Shift";
            case GLFW_KEY_CAPS_LOCK: return "Caps-Lock";
            case GLFW_KEY_SPACE: return "Space";
            case GLFW_KEY_ESCAPE: return "Esc";
            default:
                return "Unknown";
        }
    }
    return name;
}

int mousecode::BUTTON_1 = GLFW_MOUSE_BUTTON_1;
int mousecode::BUTTON_2 = GLFW_MOUSE_BUTTON_2;
int mousecode::BUTTON_3 = GLFW_MOUSE_BUTTON_3;

const char* mousecode::name(int code) {
    switch (code) {
        case GLFW_MOUSE_BUTTON_1: return "LMB";
        case GLFW_MOUSE_BUTTON_2: return "RMB";
        case GLFW_MOUSE_BUTTON_3: return "MMB";
    }
    return "unknown button";
}
