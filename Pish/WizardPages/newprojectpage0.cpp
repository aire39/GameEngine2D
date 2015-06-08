#include "../WizardPages/newprojectpage0.h"


newprojectpage0::newprojectpage0(wxWizard * parent, wxWizardPage * prev, wxWizardPage * next, const wxBitmap & bitmap) : wxWizardPageSimple(parent, prev, next, bitmap)
{
    SetSize(600,400);
    SetPage();
}

newprojectpage0::~newprojectpage0()
{
    delete mtext;
    delete pish_bitmap_display;
}

void newprojectpage0::SetPage()
{
    mtext = new wxStaticText(this, wxID_ANY, "");
    mtext->SetSize( GetClientSize() );
    mtext->SetLabelText("Welcome to PiSH!\n\n"
                       "PiSH is a 2D Game Maker That Uses Opengl For The Base Graphics\n"
                       "It Can Take 3D Objects Also (Though Limited) And Has A Good Amount\n"
                       "Of Features For A First Version.\n"
                       "Object Creation, Animation, Image Loading And More Are All Included\n"
                       "In This Version Of PiSH. More Features That Will Make This More Complete\n"
                       "Will Soon Follow!"
                       "\n\n\n"
                       "Click Next To Setup Project Settings Or Finish To Just Deal With The Defaults.\n"
                       "");


    pish_bitmap.LoadFile("./UI_Images/psh_banner_a0.gif", wxBITMAP_TYPE_GIF);

    pish_bitmap_display = new wxStaticBitmap(this, wxID_ANY, pish_bitmap);
    pish_bitmap_display->Move(380, 0);
}
