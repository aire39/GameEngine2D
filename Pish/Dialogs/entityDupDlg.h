#ifndef ENTITYDUPDLG_H_INCLUDED
#define ENTITYDUPDLG_H_INCLUDED

#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/button.h>

class entityDupDlg : public wxDialog
{
    private:

        wxCheckBox ck_position;
        wxCheckBox ck_scale;
        wxCheckBox ck_color;

        wxCheckBox ck_animation;
        wxCheckBox ck_textures;

        wxButton bt_okay;
        wxButton bt_cancel;

    public:

        entityDupDlg();
        ~entityDupDlg();

        bool IsPosition();
        bool IsScale();
        bool IsColor();

        bool IsAnimation();
        bool IsTextures();
};

#endif // ENTITYDUPDLG_H_INCLUDED
