#include "../Dialogs/prefDialog.h"


prefDialog::prefDialog() : wxDialog(NULL, -1, wxString("Preferences"))
{
    SetSize(wxSize(500, 500));

    notebook = new wxNotebook(this, wxID_ANY);
    panel.Create(notebook);
    notebook->SetSize(0, 50, GetClientSize().GetWidth(), GetClientSize().GetHeight()-50);

    notebook->AddPage(&panel, "scene");
    notebook->AddPage(&panel, "text editor");
    notebook->AddPage(&panel, "image editor");
    notebook->AddPage(&panel, "system");
}

prefDialog::~prefDialog()
{
    panel.Destroy();
    delete notebook;
}
