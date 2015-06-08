#ifndef TOOLBARTEXTEDITOR_H
#define TOOLBARTEXTEDITOR_H

#include <wx/image.h>
#include <wx/toolbar.h>

#include <iostream>

class ToolBarTextEditor : public wxToolBar
{
    DECLARE_EVENT_TABLE()

    private:

    public:

        ToolBarTextEditor(wxWindow * parent, wxWindowID id=wxID_ANY);
        ~ToolBarTextEditor();

        void ToolEvent(wxCommandEvent & event);
        void ToolMenuEvent(wxCommandEvent & event);
};

#endif // TOOLBARTEXTEDITOR_H
