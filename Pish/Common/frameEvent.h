#ifndef FRAMEEVENT_H
#define FRAMEEVENT_H

#include "../Common/GLee.h"
#include <wx/event.h>
#include <iostream>
#include <vector>

class GLFrame;

class frameEvent
{
    private:

    int pressedKey;
    int modkey;
    std::vector<int> keys;

    GLFrame * gl_frame;

    public:

        frameEvent();
        ~frameEvent();

        void setKeyCode(int keyevent=0);
        int isKeyPressed(wxKeyEvent& event);

        int returnkeypress();
        int returnkeymod();

        void BindGLView(GLFrame * gl_frame);
        bool iskeydown(int key);
};

#endif // FRAMEEVENT_H
