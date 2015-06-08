#include "../Dialogs/chooseScriptBox.h"

chooseScriptBox::chooseScriptBox(scriptMng * script_manager) : wxDialog(NULL, -1, wxString("Choose Script"))
{
    selection.clear();

    this->script_manager = script_manager;

    int box_width  = GetSize().GetWidth();
    int box_height = GetSize().GetHeight();

    SetSize( wxSize( box_width, box_height*2 ) );

    layout = new wxFlexGridSizer(2, 1, 0, 0);
    button_layout = new wxFlexGridSizer(1, 2, 0, 0);

    panel_top    = new wxPanel(this);
    panel_bottom = new wxPanel(this);
    script_list = new wxListbook(panel_top, 5000);
    text_preview = new wxRichTextCtrl(script_list, -1, _(""), wxDefaultPosition, wxDefaultSize,  wxTE_READONLY);

    button_add = new wxButton(panel_bottom, wxID_OK, _("Add"));
    button_cancel = new wxButton(panel_bottom, wxID_CANCEL, _("Cancel"));

    layout->Add(panel_top, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    layout->Add(panel_bottom, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);

    button_layout->Add(button_add, 1, wxALL|wxALIGN_CENTRE_HORIZONTAL, 5);
    button_layout->Add(button_cancel, 1, wxALL|wxALIGN_CENTRE_HORIZONTAL, 5);

    SetSizer(layout, true);
    panel_bottom->SetSizer(button_layout, true);

    SetWindowStyle(wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP);

    panel_top->SetInitialSize( wxSize( GetSize().GetWidth()-20, (GetSize().GetHeight()/2)+GetSize().GetHeight()/5 ) );
    script_list->SetInitialSize( wxSize( GetSize().GetWidth()-20, (GetSize().GetHeight()/2)+GetSize().GetHeight()/5 ) );

    //panel_top->SetBackgroundColour( wxColour("#00FF00"));
    //panel_bottom->SetBackgroundColour( wxColour("#0000FF"));

    SetAffirmativeId( wxID_OK );
    SetEscapeId( wxID_CANCEL );

}

chooseScriptBox::~chooseScriptBox()
{
    delete text_preview;
    delete script_list;
    delete panel_top;

    delete button_add;
    delete button_cancel;
    delete panel_bottom;
}


void chooseScriptBox::showDialog()
{
    switch( ShowModal() )
    {
        case wxID_OK:
        std::cout << "Add Clicked!" << std::endl;
        selection.clear();
        selection = (std::string)script_list->GetPageText( script_list->GetSelection() );
        Show(false);
        break;

        case wxID_CANCEL:
                std::cout << "Cancel Clicked!" << std::endl;
                selection.clear();
                Show(false);
        break;

        default:
            break;
    }

}

void chooseScriptBox::OnPageChange(wxListbookEvent & event)
{
    text_preview->Clear();
    pScript * script;

    script = script_manager->getScript( (std::string)script_list->GetPageText( script_list->GetSelection() ) );

    if( script != NULL)
        text_preview->SetValue( script->getData().c_str() );
}

void chooseScriptBox::updateDialogInfo()
{
	std::string * script_names = new std::string[script_manager->get_number_of_scripts()];

    for(int i=script_list->GetPageCount()-1; i>=0; i--)
        script_list->RemovePage(i);


    if( script_manager->get_number_of_scripts() != 0)
    {
        script_manager->getAllScriptName(script_names);

        for(int i=0; i<script_manager->get_number_of_scripts(); i++)
            script_list->AddPage( text_preview, script_names[i], true);
    }
    else
        script_list->AddPage(text_preview, "<No Scripts>", true);

    if(script_list->GetPageCount() > 0)
        script_list->SetSelection(0);

}

std::string chooseScriptBox::getSelection()
{
    return selection;
}

BEGIN_EVENT_TABLE(chooseScriptBox, wxDialog)

    EVT_LISTBOOK_PAGE_CHANGED(5000, chooseScriptBox::OnPageChange)

END_EVENT_TABLE()
