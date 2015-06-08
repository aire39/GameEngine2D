#include "../Dialogs/Splash.h"
#include <wx/msgdlg.h>

Splash::Splash(wxWindow * parent, const wxBitmap bitmap, int milliseconds) : wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT, milliseconds, parent, wxID_ANY)
{

}

Splash::~Splash()
{

}

void Splash::OnCloseWindow(wxCloseEvent & event)
{
    #ifdef __WXDEBUG__
        wxMessageBox(_T("Switched to wxwidgets 2.9!"), _T("PSH Engine Notes"));
    #endif

    Destroy();
}

BEGIN_EVENT_TABLE(Splash, wxSplashScreen)
    EVT_CLOSE(Splash::OnCloseWindow)
END_EVENT_TABLE()
