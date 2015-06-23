#include <wx/app.h>
#include "./Window/winMng.h"
#include "./Dialogs/Splash.h"

//////////////////////////
//Application Main Class//
//////////////////////////

////////////////
//Mac Specific//
////////////////

#ifdef __MACOSX__

class MyApp: public wxApp
{
    private:
        winMng * m_wmgr;
        Splash * splashscreen;
        wxBitmap splash_bitmap;
        virtual bool OnInit();
};



bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    splash_bitmap.LoadFile("./UI_Images/splash.png", wxBITMAP_TYPE_PNG);
    splashscreen = new Splash(NULL, splash_bitmap, 2000);

    m_wmgr = new winMng(0L, wxT(PROJECTVERSIONLABEL));
    m_wmgr->Show(true);
    m_wmgr->InitPSH();

  return true;
}

#endif

//////////////////
//Linux Specific//
//////////////////

#ifdef __LINUX__

class MyApp: public wxApp
{
    private:
        winMng * m_wmgr;
        Splash * splashscreen;
        wxBitmap splash_bitmap;
        virtual bool OnInit();
};



bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    //splash_bitmap.LoadFile("./UI_Images/splash.png", wxBITMAP_TYPE_PNG);
    //splashscreen = new Splash(NULL, splash_bitmap, 2000);

    m_wmgr = new winMng(0L, wxT(PROJECTVERSIONLABEL));
    m_wmgr->Show(true);
    m_wmgr->InitPSH();

  return true;
}

#endif

//////////////////
//Win32 Specific//
//////////////////

#ifdef __WIN32__

class MyApp: public wxApp
{
    private:
        winMng * m_wmgr;
        Splash * splashscreen;
        wxBitmap splash_bitmap;
        virtual bool OnInit();
};



bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    splash_bitmap.LoadFile("./UI_Images/splash.png", wxBITMAP_TYPE_PNG);
    splashscreen = new Splash(NULL, splash_bitmap, 2000);

    m_wmgr = new winMng(0L, wxT(PROJECTVERSIONLABEL));
    m_wmgr->Show(true);
    m_wmgr->InitPSH();

    return true;
}

#endif

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////


//DECLARE_APP(MyApp)
//IMPLEMENT_APP(MyApp) //Starts Main/Application
IMPLEMENT_APP_CONSOLE(MyApp) //Starts Main/Application
