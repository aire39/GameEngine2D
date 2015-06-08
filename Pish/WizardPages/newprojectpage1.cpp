#include "../WizardPages/newprojectpage1.h"

newprojectpage1::newprojectpage1(wxWizard * parent, wxWizardPage * prev, wxWizardPage * next, const wxBitmap & bitmap) : wxWizardPageSimple(parent, prev, next, bitmap)
{
    SetSize(600,400);
    SetPage();
}

newprojectpage1::~newprojectpage1()
{
    delete mtext;
    delete pish_bitmap_display;
}

void newprojectpage1::SetPage()
{
    mtext = new wxStaticText(this, wxID_ANY, "");
    mtext->SetSize( GetClientSize() );
    mtext->SetLabelText("Scene Setup!");


    pish_bitmap.LoadFile("./UI_Images/psh_banner_a0.gif", wxBITMAP_TYPE_GIF);

    pish_bitmap_display = new wxStaticBitmap(this, wxID_ANY, pish_bitmap);
    pish_bitmap_display->Move(380, 0);
}
