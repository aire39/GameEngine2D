#ifndef NEWPROJECTPAGE1_H
#define NEWPROJECTPAGE1_H

#include <wx/wizard.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>

class newprojectpage1 : public wxWizardPageSimple
{
    private:
        wxBitmap pish_bitmap;
        wxStaticBitmap * pish_bitmap_display;
        wxStaticText * mtext;
                        ///Setup Page
        void SetPage();

    public:
                            ///Constructor
        newprojectpage1(wxWizard * parent, wxWizardPage * prev = NULL, wxWizardPage * next = NULL, const wxBitmap & bitmap = wxNullBitmap);
                            ///Destructor
        ~newprojectpage1();
};

#endif // NEWPROJECTPAGE1_H
