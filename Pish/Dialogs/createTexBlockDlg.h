#ifndef CREATETEXBLOCKDLG_H
#define CREATETEXBLOCKDLG_H

#include "../Common/GLee.h"

#include <iostream>

#include <wx/richtext/richtextctrl.h>
#include <wx/dialog.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/clrpicker.h>
#include <wx/colordlg.h>


#include "../Core/Texture.h"
#include "../Core/TextureSub.h"

class createTexBlockDlg : public wxDialog
{
    DECLARE_EVENT_TABLE()

    private:

        wxPanel * image_panel;

        wxImage * img;
        wxBitmap * bitmap;

        Texture * texture;
        TextureSub * texture_sub;

        int position_x, position_y;
        int width, height;
        int offset_x, offset_y;

        wxSpinCtrl         *  spin_x_position, * spin_y_position;
        wxSpinCtrl         *  spin_x_size    , * spin_y_size;
        wxSpinCtrl         *  spin_x_offset  , * spin_y_offset;
        wxButton           *  mask_color_button;
        wxButton           *  button_okay;
        wxButton           *  button_cancel;

        wxColourDialog     *  colour_dialog;

        int panel_size_x, panel_size_y, panel_pos_x, panel_pos_y;

        wxStaticText * text_position, * text_size, * text_offset, * text_mask_color;
        int text_point_size;
        wxFont text_font;

        void call_color_picker(wxCommandEvent & event);

    public:

        createTexBlockDlg(wxWindow * parent, wxWindowID id = wxID_ANY);
        ~createTexBlockDlg();

        TextureSub * UsingTexture( Texture * texture );
        bool showDialog();

        void on_paint(wxPaintEvent & event);
};

#endif // CREATETEXBLOCKDLG_H
