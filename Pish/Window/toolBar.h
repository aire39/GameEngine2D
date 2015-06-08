#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "wx/image.h"
#include "wx/toolbar.h"
#include "wx/msgdlg.h"


class toolBar : public wxToolBar
{
    DECLARE_EVENT_TABLE()

    private:


    public:

        toolBar(wxWindow *parent = NULL);
        ~toolBar();

        void ToolEvent(wxCommandEvent &event);
};


#endif // TOOLBAR_H
