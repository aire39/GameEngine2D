#ifndef NEWPROJECTPAGE0_H
#define NEWPROJECTPAGE0_H

#include <wx/wizard.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>

class newprojectpage0 : public wxWizardPageSimple
{
    private:
        wxBitmap pish_bitmap;
        wxStaticBitmap * pish_bitmap_display;
        wxStaticText * mtext;
                        ///Setup Page
        void SetPage();

    public:
                            ///Constructor
        newprojectpage0(wxWizard * parent, wxWizardPage * prev = NULL, wxWizardPage * next = NULL, const wxBitmap & bitmap = wxNullBitmap);
                            ///Destructor
        ~newprojectpage0();
};

#endif // NEWPROJECTPAGE0_H
