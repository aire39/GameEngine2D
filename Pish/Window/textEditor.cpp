#include "../Window/textEditor.h"

textEditor::textEditor(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    wxString radiolist[] = {"export", "embeded"};
    LiveEdit = true;

    button_panel  = new wxPanel(this, wxID_ANY);
    text_panel    = new wxPanel(this, wxID_ANY);
    toolbar_panel = new wxPanel(this, wxID_ANY);

    text_editor  = new wxStyledTextCtrl(text_panel, 100);
    stop_button  = new wxButton(button_panel, 4100);
    try_button   = new wxButton(button_panel, 4101);
    run_button   = new wxButton(button_panel, 4102);

    stop_button->SetWindowStyle(wxBU_EXACTFIT );  stop_button->SetLabel("stop");
    try_button->SetWindowStyle( wxBU_EXACTFIT );  try_button->SetLabel("try");
    run_button->SetWindowStyle( wxBU_EXACTFIT );  run_button->SetLabel("run");

    tool_bar = new ToolBarTextEditor(toolbar_panel);
    script_io_option = new wxRadioBox(button_panel, 5000, "Embeded/Export Oprions", wxDefaultPosition, wxDefaultSize, 2, radiolist, 2, wxRA_SPECIFY_ROWS);
    script_live      = new wxCheckBox(button_panel, 5001, "Live");
    script_live->SetValue(LiveEdit);

    script_io_option->Move(0, 20);

    layout = new wxFlexGridSizer(1, 2, 0, 0);
    button_layout = new wxFlexGridSizer(3, 1, 0, 0);

    text_editor->SetTextRaw("An Editor Depending On The Type Of File:\n"
                            "Python Scripts: .py\n"
                            "Text Documents: .txt or .*\n"
                            "This is a Scintilla Text Editor\n");

    layout->Add(text_panel, 1, wxALL|wxALIGN_CENTRE_HORIZONTAL, 5);
    layout->Add(button_panel, 1, wxALL|wxALIGN_CENTRE_HORIZONTAL, 5);
    button_layout->Add(stop_button, 1, wxALL|wxALIGN_CENTRE_VERTICAL, 5);
    button_layout->Add(try_button, 1, wxALL|wxALIGN_CENTRE_VERTICAL, 5);
    button_layout->Add(run_button, 1, wxALL|wxALIGN_CENTRE_VERTICAL, 5);

    //this->SetBackgroundColour( wxColour("#0000FF") );
    //button_panel->SetBackgroundColour( wxColour("#00FF00") );
    //text_panel->SetBackgroundColour( wxColour("#FF0000") );

    SetSizer( layout, true );
    button_panel->SetSizer( button_layout, true );

    stop_button->Connect(4100, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(textEditor::OnButtonClicked), 0, 0);
    try_button->Connect(4101, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(textEditor::OnButtonClicked), 0, 0);
    run_button->Connect(4102, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(textEditor::OnButtonClicked), 0, 0);


    text_editor->Connect(wxEVT_STC_MODIFIED, wxStyledTextEventHandler(textEditor::OnTextTyped), 0, this);

    current_script = NULL;

    stop_button->Show(false);
    try_button->Show(false);
    run_button->Show(false);

    text_editor->SetEOLMode( wxSTC_EOL_LF );

    //text_editor->CmdKeyAssign('L', wxSTC_SCMOD_SHIFT, wxSTC_CMD_NEWLINE);
    tool_bar->Connect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(textEditor::ToolEvent), 0, this);

}

textEditor::~textEditor()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting textEditor!" << std::endl;
    #endif

    current_script = NULL;

    delete tool_bar;
    delete stop_button;
    delete try_button;
    delete run_button;
    delete button_panel;
    delete text_editor;
    delete text_panel;


}

void textEditor::BindResourceWindow(resourceWindow * resource_window)
{
    this->resource_window = resource_window;
}

void textEditor::BindScriptManager(scriptMng * script_manager)
{
    this->script_manager = script_manager;
}

void textEditor::setWorkingData(pScript * script)
{
    this->current_script = script;
    script_io_option->SetSelection( script->EmbedExportMode() );
}

void textEditor::unsetWorkingData()
{
    current_script = NULL;
}

void textEditor::ClearTextEditor()
{
    if( text_editor != NULL )
    {
        if( text_editor->GetLength() != 0 )
            text_editor->ClearAll();
    }
}

void textEditor::SetText(std::string text)
{
    text_editor->SetTextRaw(text.c_str());
}

void textEditor::OnTextTyped(wxStyledTextEvent & event)
{
    //std::cout << "Text in textEditor has been changed! " << event.GetEventType() << std::endl;
    if( (current_script != NULL) && (LiveEdit == true) )
        current_script->loadScript( (std::string)text_editor->GetTextRaw() );

    //std::cout << text_editor->GetTextRaw() << std::endl;
}



void textEditor::OnSize(wxSizeEvent & event)
{

    toolbar_panel->SetSize(0, 0, GetSize().GetWidth(), 25);
    text_panel->SetSize(0 , 25,(GetSize().GetWidth()/2) + (GetSize().GetWidth()/5), GetSize().GetHeight()-20 );
    text_editor->SetSize( text_panel->GetSize() );

    button_panel->SetSize( (GetSize().GetWidth()/2) + (GetSize().GetWidth()/5), 25, GetSize().GetWidth()/2, GetSize().GetHeight() );

    tool_bar->SetSize(wxSize(GetSize().GetWidth(), 25));
    stop_button->SetSize( wxSize(20, 20) );
    try_button->SetSize(  wxSize(20, 20) );
    run_button->SetSize(  wxSize(20, 20) );
}

void textEditor::OnButtonClicked(wxCommandEvent & event)
{
    switch( event.GetId() )
    {
        case 4100:
            std::cout << "Stop Clicked!" << std::endl;
            if( current_script != NULL )
                current_script->setMode(0);
        break;

        case 4101:
            std::cout << "Try Clicked!" << std::endl;
            if( current_script != NULL )
                current_script->setMode(1);
        break;

        case 4102:
            std::cout << "Run Clicked!" << std::endl;
            if( current_script != NULL )
                current_script->setMode(2);
        break;

        default:
            event.Skip();
        break;
    }
}

void textEditor::OnEnterWindow(wxMouseEvent & event)
{
    std::cout << "textEditor entered!" << std::endl;
    text_editor->SetFocus();
}

wxStyledTextCtrl * textEditor::GetTextEditor()
{
    return text_editor;
}

void textEditor::CheckOptions(wxCommandEvent & event)
{
    event.Skip();

    switch( event.GetId() )
    {
        case 5000:

            std::cout << script_io_option->GetSelection() << std::endl;
            if( current_script != NULL )
                current_script->SetSaveMode( script_io_option->GetSelection() );

        break;

        case 5001:
            LiveEdit = script_live->IsChecked();
        break;

        default:
        break;
    }
}

void textEditor::ToolEvent(wxCommandEvent & event)
{
    switch( event.GetId())
    {
        case 0:

            if( !LiveEdit )
                current_script->loadScript( (std::string)text_editor->GetTextRaw() );

        break;

        default:
        break;
    }
}

BEGIN_EVENT_TABLE(textEditor, wxPanel)

    EVT_SIZE(textEditor::OnSize)
    EVT_CHECKBOX(5001, textEditor::CheckOptions)
    EVT_RADIOBOX(5000, textEditor::CheckOptions)
    //EVT_STC_KEY(100, textEditor::OnTextKeyed)

END_EVENT_TABLE()
