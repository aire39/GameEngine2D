#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <iostream>
#include <wx/richtext/richtextctrl.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stc/stc.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>

#include "../Window/resourceWindow.h"
#include "../Management/scriptMng.h"
#include "../Window/ToolBarTextEditor.h"

class resourceWindow;
class pScript;


class textEditor : public wxPanel
{
    DECLARE_EVENT_TABLE()

    private:

        bool LiveEdit;

        ToolBarTextEditor * tool_bar;

        wxFlexGridSizer * layout;
        wxFlexGridSizer * button_layout;
        wxPanel         * button_panel;
        wxPanel         * text_panel;
        wxPanel         * toolbar_panel;
        wxStyledTextCtrl* text_editor;
        wxButton        * stop_button;
        wxButton        * try_button;
        wxButton        * run_button;
        wxButton        * reInitShader;
        wxButton        * compileShader;

        wxRadioBox  *  script_io_option;
        wxCheckBox  *  script_live;

        resourceWindow * resource_window;
        scriptMng      * script_manager;

        pScript        * current_script;
        //text
        //shader_vert
        //shader_frag
        //All above need the same base class

    public:
        textEditor(wxWindow* parent);
        ~textEditor();

        void BindResourceWindow(resourceWindow * resource_window);
        void BindScriptManager(scriptMng * script_manager);

        void setWorkingData( pScript * script ); ///Is supposed to work with any type of text
                                                 ///But just this for now.
        void unsetWorkingData();
        void ClearTextEditor();
        void SetText(std::string text);

        void OnTextTyped(wxStyledTextEvent & event);

        void OnSize(wxSizeEvent & event);
        void OnButtonClicked(wxCommandEvent & event);
        void CheckOptions(wxCommandEvent & event);
        void OnEnterWindow(wxMouseEvent & event);

        wxStyledTextCtrl * GetTextEditor();
        void ToolEvent(wxCommandEvent & event);
};

#endif // TEXTEDITOR_H
