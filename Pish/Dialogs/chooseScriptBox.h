#ifndef CHOOSESCRIPTBOX_H
#define CHOOSESCRIPTBOX_H

#include <iostream>

#include <wx/richtext/richtextctrl.h>
#include <wx/dialog.h>
#include <wx/listbook.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sizer.h>

#include "../Management/scriptMng.h"

class chooseScriptBox : public wxDialog
{
    DECLARE_EVENT_TABLE()

    private:

        std::string selection;

        scriptMng       *   script_manager;

        wxFlexGridSizer *   layout;
        wxFlexGridSizer *   button_layout;

        wxRichTextCtrl  * text_preview;
        wxListbook      * script_list;
        wxPanel         * panel_top;
        wxPanel         * panel_bottom;

        wxButton    *   button_add;
        wxButton    *   button_cancel;

    public:

        chooseScriptBox(scriptMng * script_manager = NULL);
        ~chooseScriptBox();

        void OnSize(wxSizeEvent & event);
        void OnPageChange(wxListbookEvent & event);
        void updateDialogInfo();
        void showDialog();

        std::string getSelection();

};

#endif // CHOOSESCRIPTBOX_H
