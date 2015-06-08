#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H

#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/image.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/dialog.h>

#include "../Management/texMng.h"
#include "../Dialogs/createTexBlockDlg.h"

class textureResource : public wxPanel
{
    DECLARE_EVENT_TABLE()

    private:

        wxMenu * texture_menu;

        wxFlexGridSizer * layout;

        bool showsubs;
        wxImageList * texturesub_image_list;
        wxImageList * texture_image_list; ///A list of images from loaded textures to display onto icon

        wxNotebook          * notebook;
        wxListView          * listview;
        texMng              * texture_manager;

        std::string         selobjtxt;
        std::string         selobjtxt2;
        int                 ntextures;

    public:
        textureResource(wxWindow * parent, wxWindowID id=wxID_ANY);
        ~textureResource();

        void BindTextureManager( texMng * texture_manager );

        std::string GetTexture();
        std::string GetTextureSub();

        void OnSize(wxSizeEvent & event);
        void OnItemSelected(wxListEvent & event);
        void OnItemRightClicked(wxListEvent & event);
        void OnItemActivated(wxListEvent & event);
        void OnMenuItemSelected(wxCommandEvent & event);
        void OnEnterWindow(wxMouseEvent & event);
        void OnKey(wxKeyEvent & event);


        void mUpdateResource();
};

#endif // TEXTURERESOURCE_H
