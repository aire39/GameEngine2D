#include "../Window/ToolBarTextEditor.h"

ToolBarTextEditor::ToolBarTextEditor(wxWindow * parent, wxWindowID id) : wxToolBar(parent, id)
{
    wxInitAllImageHandlers();
    SetToolBitmapSize(wxSize(16, 16));

    wxImage img;
    img.LoadFile("./UI_Images/filesave.png");
    img.Rescale(16, 16);
    wxBitmap bitmap(img);


    AddTool(0, "Save" , bitmap);

    Realize();
}

ToolBarTextEditor::~ToolBarTextEditor()
{
}

void ToolBarTextEditor::ToolEvent(wxCommandEvent & event)
{
    event.Skip();

    switch(event.GetId())
    {
        case 0:
            std::cout << "Save Item" << std::endl;
        break;

        default:
        break;
    }
}

void ToolBarTextEditor::ToolMenuEvent(wxCommandEvent & event)
{
}

BEGIN_EVENT_TABLE(ToolBarTextEditor, wxToolBar)

EVT_TOOL(0, ToolBarTextEditor::ToolEvent)

END_EVENT_TABLE()
