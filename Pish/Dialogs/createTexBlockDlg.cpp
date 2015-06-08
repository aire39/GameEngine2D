#include "../Dialogs/createTexBlockDlg.h"
#include <wx/dc.h>
#include <wx/dcclient.h>

createTexBlockDlg::createTexBlockDlg(wxWindow * parent, wxWindowID id)  : wxDialog(parent, id, "Create Sub Textures")
{
    this->SetSize( wxSize(400, 400) );

    position_x = position_y = 0;
    width = height = 40;
    offset_x = offset_y = 0;

    spin_x_position = spin_y_position = NULL;

    img = NULL;
    texture = NULL;
    texture_sub = NULL;

    panel_size_x = 180;
    panel_size_y = 180;
    panel_pos_x  = 210;
    panel_pos_y  = 25;

    text_point_size = 15;

    image_panel = new wxPanel(this);

    wxColourData color_data;
    color_data.SetChooseFull(true);
    colour_dialog = new wxColourDialog(this, &color_data);


    spin_x_position = new wxSpinCtrl(this);
    spin_y_position = new wxSpinCtrl(this);

    spin_x_size = new wxSpinCtrl(this);
    spin_y_size = new wxSpinCtrl(this);

    spin_x_offset = new wxSpinCtrl(this);
    spin_y_offset = new wxSpinCtrl(this);

    mask_color_button = new wxButton(this, 7006);
    button_okay = new wxButton(this, wxID_OK, "OK");
    button_cancel = new wxButton(this, wxID_CANCEL, "CANCEL");

    text_position   = new wxStaticText(this, -1, "");
    text_size       = new wxStaticText(this, -1, "");
    text_offset     = new wxStaticText(this, -1, "");
    text_mask_color = new wxStaticText(this, -1, "");

    //mask_color_button->Connect(7006, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(createTexBlockDlg::on_button_clicked));
    SetWindowStyle(wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP);



    SetAffirmativeId( wxID_OK );
    SetEscapeId( wxID_CANCEL );

}

createTexBlockDlg::~createTexBlockDlg()
{
    delete image_panel;

    delete bitmap;
    delete img;
    img = NULL;

    texture = NULL;

    delete button_okay;
    delete button_cancel;

    delete text_offset;
    delete text_size;
    delete text_position;

    delete spin_x_position;
    delete spin_y_position;
    delete spin_x_size;
    delete spin_y_size;

    delete mask_color_button;
    delete colour_dialog;
}

TextureSub * createTexBlockDlg::UsingTexture(Texture * texture)
{
    ///Ptr to texture address
    this->texture = texture;

    if( texture != NULL )
    {
        image_panel->SetBackgroundColour(wxColour(0, 255, 0));
        image_panel->SetSize( (GetClientSize().GetWidth()/2)+21, 0,  (GetClientSize().GetWidth()/2)-21, (GetClientSize().GetWidth()/2)-21);

        std::cout << texture->GetTextureName() << " : Texture Exist Continuing To Process..." << std::endl;

        img = new wxImage;
        img->SetData(Texture::ConvertFromNewToAlloc(texture) , texture->GetTextureWidth(), texture->GetTextureHeight());

        bitmap = new wxBitmap(*img);

        if( texture->GetTextureSub() == NULL )
        {
            texture_sub = new TextureSub();
            texture_sub->AttachMasterTexture(texture);
        }
        this->Show();
        ///

        spin_x_position->SetRange(0, texture->GetTextureWidth());
        spin_y_position->SetRange(0, texture->GetTextureHeight());

        spin_x_size->SetRange(0, texture->GetTextureWidth());
        spin_y_size->SetRange(0, texture->GetTextureHeight());


        spin_x_offset->SetRange(0, texture->GetTextureWidth());
        spin_y_offset->SetRange(0, texture->GetTextureHeight());


        ///Set spin box attributes
        spin_x_position->SetSize(0, text_point_size+10, 100, 20);
        spin_y_position->SetSize(105, text_point_size+10, 100, 20);

        spin_x_size->SetSize(0, text_point_size+10+55, 100, 20);
        spin_y_size->SetSize(105, text_point_size+10+55, 100, 20);

        spin_x_offset->SetSize(0, text_point_size+10+110, 100, 20);
        spin_y_offset->SetSize(105, text_point_size+10+110, 100, 20);

        spin_x_size->SetValue(40);
        spin_y_size->SetValue(40);

        mask_color_button->SetSize(0, 165+25, 50, 25);
        button_okay->SetSize(0, 250, 100, 25);
        button_cancel->SetSize(110, 250, 100, 25);

        text_font.SetPointSize( text_point_size );

        text_position->SetFont( text_font );
        text_size->SetFont( text_font );
        text_offset->SetFont( text_font );
        text_mask_color->SetFont( text_font );

        text_position->Move(0, 0);
        text_size->Move(0, 55);
        text_offset->Move(0, 110);
        text_mask_color->Move(0, 165);

        text_position->SetLabel("cuts");
        text_size->SetLabel("Size");
        text_offset->SetLabel("Offset");
        text_mask_color->SetLabel("Mask");

        mask_color_button->SetBackgroundColour( wxColour(0, 0, 0) );

        Update();

        return texture_sub;
    }

    return NULL;

}


bool createTexBlockDlg::showDialog()
{
    SetFocus();
    bool is_success = false;

    if(texture != NULL)
    switch( ShowModal() )
    {
        case wxID_OK:
            ///Complete the block mode

            if( !texture_sub->ChopTexture(spin_x_position->GetValue(), spin_y_position->GetValue()) )
                std::cout << "Chop Measures Not Acceptable!" << std::endl;

            is_success = true;

        break;

        case wxID_CANCEL:
            Update();
            Show(false);
        break;

        default:
        break;
    }

    return is_success;
}


void createTexBlockDlg::on_paint(wxPaintEvent & event)
{
    wxPaintDC paintdc(image_panel);
    wxDC &dc = paintdc;

    if(texture != NULL)
    {
        dc.DrawBitmap(*bitmap,0, 0);
    }
}


void createTexBlockDlg::call_color_picker(wxCommandEvent & event)
{
    std::cout << "COLOR PICK CLICKED!" << std::endl;

    switch( event.GetId() )
    {
        case 7006:
            colour_dialog->SetFocus();
            if( colour_dialog->ShowModal() == wxID_OK)
            {
                wxColourData data = colour_dialog->GetColourData();
                wxColour color = data.GetColour();
            }
        break;

        default:
            event.Skip();
        break;
    }

    SetFocus();
}

BEGIN_EVENT_TABLE(createTexBlockDlg, wxDialog)

    EVT_PAINT(createTexBlockDlg::on_paint)
    EVT_BUTTON(7006, createTexBlockDlg::call_color_picker)

END_EVENT_TABLE()
