#include "../Dialogs/entityDupDlg.h"

entityDupDlg::entityDupDlg() : wxDialog(NULL, wxID_ANY, _T("Copy Object"))
{
    ck_position.Create(this, 0, "position");
    ck_scale.Create(this, 1, "scale");
    ck_color.Create(this, 2, "color");

    ck_animation.Create(this, 3, "animation");
    ck_textures.Create(this, 4, "textures");

    ck_position.Move(0, 0);
    ck_scale.Move(0, 20);
    ck_color.Move(0, 40);
    ck_animation.Move(0, 60);
    ck_textures.Move(0, 80);

    bt_okay.Create(this, wxID_OK, "OK");
    bt_cancel.Create(this, wxID_CANCEL, "CANCEL");

    bt_okay.Move(0, 110);
    bt_cancel.Move(0, 130);

    SetSize( wxSize(100, 200) );

    SetAffirmativeId( wxID_OK );
    SetEscapeId( wxID_CANCEL );
}

entityDupDlg::~entityDupDlg()
{
}

bool entityDupDlg::IsPosition()
{
    return ck_position.IsChecked();
}

bool entityDupDlg::IsScale()
{
    return ck_scale.IsChecked();
}

bool entityDupDlg::IsColor()
{
    return ck_color.IsChecked();
}

bool entityDupDlg::IsAnimation()
{
    return ck_animation.IsChecked();
}

bool entityDupDlg::IsTextures()
{
    return ck_textures.IsChecked();
}
