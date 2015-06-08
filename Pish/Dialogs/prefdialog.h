#ifndef PREFDIALOG_H_INCLUDED
#define PREFDIALOG_H_INCLUDED

#include <wx/dialog.h>
#include <wx/notebook.h>

class prefDialog : public wxDialog
{
    private:

        wxNotebook * notebook;
        wxPanel panel;

    public:

        prefDialog();
        ~prefDialog();
};

#endif // PREFDIALOG_H_INCLUDED
