#ifndef RESOURCEWINDOW_H
#define RESOURCEWINDOW_H

#include <iostream>

#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/choice.h>
#include <wx/listbox.h>
#include <wx/sizer.h>

#include "../Window/projectTreeView.h"
#include "../Management/scriptMng.h"
#include "../Window/textEditor.h"
#include "../Management/animationManager.h"

class textEditor;

class resourceWindow : public wxPanel
{
    DECLARE_EVENT_TABLE()

    private:

        wxFlexGridSizer * layout;

        wxNotebook * notebook;
        wxListBox  * listbox;

        wxChoice   * choice_resource;
        wxTextCtrl * search_treeView;

        projectTreeView * tree_view;
        scriptMng  * script_manager;
        textEditor * text_editor;
        animationManager * animation_manager;

    public:

    resourceWindow(wxWindow * parent = NULL, wxWindowID id = wxID_ANY);
    ~resourceWindow();

    void BindTreeView(projectTreeView * tree_view);
    void BindScriptManager(scriptMng * script_manager);
    void BindTextEditor(textEditor * text_editor);
    void BindAnimationManager( animationManager * animation_manager );

    wxNotebook * notebookwindow();

    void OnSize(wxSizeEvent & event);
    void OnNoteBookSwitch(wxNotebookEvent & event);
    void OnChoiceChange(wxCommandEvent & event);
    void OnListBoxItemDClicked(wxCommandEvent & event);

};

#endif // RESOURCEWINDOW_H
