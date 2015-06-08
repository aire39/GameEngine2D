#include "../Common/frameEvent.h"
#include "../Core/GLFrame.h"

frameEvent::frameEvent()
{
    gl_frame = NULL;
    pressedKey = 0;
}

frameEvent::~frameEvent()
{
}



void frameEvent::setKeyCode(int keyevent)
{
    pressedKey = keyevent;
}

int frameEvent::isKeyPressed(wxKeyEvent &event)
{
    int isPressed = 0;

    pressedKey = event.GetKeyCode();
    modkey     = event.GetModifiers();

    //std::cout << modkey << " " <<pressedKey << std::endl;

    return isPressed;
}

int frameEvent::returnkeypress()
{
    return pressedKey;
}

int frameEvent::returnkeymod()
{
    return modkey;
}

void frameEvent::BindGLView(GLFrame * gl_frame)
{
    this->gl_frame = gl_frame;
}

bool frameEvent::iskeydown(int key)
{
    if( gl_frame == NULL )
        return 0;

    if( !gl_frame->HasFocus() )
        return 0;

    return wxGetKeyState( wxKeyCode(key));
}
