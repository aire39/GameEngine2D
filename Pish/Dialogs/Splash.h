#ifndef SPLASH_H
#define SPLASH_H

#include <wx/splash.h>

class Splash : public wxSplashScreen
{
    DECLARE_EVENT_TABLE();

    public:

        Splash(wxWindow * parent, const wxBitmap bitmap, int milliseconds);
        ~Splash();

        void OnCloseWindow(wxCloseEvent & event);

};

#endif // SPLASH_H
