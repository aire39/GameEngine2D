#include "../Window/toolBar.h"

toolBar::toolBar(wxWindow * parent) : wxToolBar(parent, -1)
{
    //Test
    wxInitAllImageHandlers();
    wxImage img;
    img.LoadFile("./UI_Images/filenew.png");
    img.Rescale(16, 16);
    wxBitmap bitmap(img);

    wxImage img2;
    img2.LoadFile("./UI_Images/file_open2.png");
    img2.Rescale(16, 16);
    wxBitmap bitmap2(img2);

    wxImage img3;
    img3.LoadFile("./UI_Images/scene_icon32x32.gif");
    img3.Rescale(16, 16);
    wxBitmap bitmap3(img3);

    wxImage img4;
    img4.LoadFile("./UI_Images/filesave.png");
    img4.Rescale(16, 16);
    wxBitmap bitmap4(img4);

    AddTool(0, "New Project", bitmap);
    AddTool(1, "Open File", bitmap2);
    AddTool(2, "Save File", bitmap4);
    AddTool(3, "Run Game", bitmap3);


    Realize();
}


toolBar::~toolBar()
{
    RemoveTool(0);
}


void toolBar::ToolEvent(wxCommandEvent &event)
{
    switch( event.GetId() )
    {
        case 0:
            wxMessageBox("Not Yet Implemented!","New Project");
        break;

        case 1:
        break;

        case 2:
        break;

        case 3:
        break;

        default:
        break;
    }

}


BEGIN_EVENT_TABLE(toolBar, wxToolBar)

EVT_TOOL_RANGE(0, 3, toolBar::ToolEvent)

END_EVENT_TABLE()
