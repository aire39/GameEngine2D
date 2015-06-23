#include "../Window/textureResource.h"

textureResource::textureResource(wxWindow * parent, wxWindowID id) : wxPanel(parent, id)
{
    showsubs = false;

    notebook = new wxNotebook(this, wxID_ANY);

    listview = new wxListView(notebook, 100);
    listview->SetWindowStyle(wxLC_ICON | wxLC_SINGLE_SEL);
    notebook->AddPage(listview, "Textures", true, 0);

    texture_image_list = new wxImageList(32, 32);
    texturesub_image_list = new wxImageList(32,32);
    listview->SetImageList(texture_image_list, 0);

    texture_menu = new wxMenu();
    texture_menu->Append(0, "Create Sub Textures");
    texture_menu->Append(1, "Look At Sub Textures");
    texture_menu->Append(3, "Delete Sub Textures");
    texture_menu->AppendSeparator();
    texture_menu->Append(2, "Texture Info");

    Connect(0, 3, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(textureResource::OnMenuItemSelected), 0, this);
    listview->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(textureResource::OnKey), 0, this);
}

textureResource::~textureResource()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting textureResource!" << std::endl;
    #endif

    texture_manager = NULL;

    delete texturesub_image_list;
    texturesub_image_list = NULL;
    delete texture_image_list;
    texture_image_list = NULL;
    delete listview;
    listview = NULL;
    if(notebook != NULL)
        delete notebook;
    notebook = NULL;
}

void textureResource::BindTextureManager( texMng * texture_manager )
{

    this->texture_manager = texture_manager;
    ntextures = (int)texture_manager->GetNumberOfTextures();

    wxInitAllImageHandlers();

    //Used for filling wxListCtrl
    if( texture_manager->GetNumberOfTextures() > 0 )
    {
        for(int i=0; i<(int)texture_manager->GetNumberOfTextures(); i++)
        {
            wxImage img(texture_manager->GetTexture(i)->GetTexturePath());
            img.Rescale(32,32);
            wxBitmap bitmap(img);
            texture_image_list->Add(bitmap);


            wxListItem listitem;
            listitem.SetImage(i);
            listitem.SetId(i);
            listitem.SetText(texture_manager->GetTexture(i)->GetTextureName());


            listview->InsertItem(listitem);

            ntextures++;
        }
    }

}

std::string textureResource::GetTexture()
{
    return selobjtxt;
}

std::string textureResource::GetTextureSub()
{
    return selobjtxt2;
}

void textureResource::OnSize(wxSizeEvent & event)
{
    notebook->SetSize( 0, 0, GetSize().GetWidth(), GetSize().GetHeight() );
    std::cout << "Texture Resource Window Changed Size!" << std::endl;
    listview->Arrange();
}

void textureResource::OnItemSelected(wxListEvent & event)
{
    std::cout << "Image Being Selected : " << event.GetLabel() << std::endl;

    if( !showsubs )
    {
        texture_manager->SetSelectedTexture( (std::string)event.GetLabel() );
        texture_manager->SetSelectedTexture2( selobjtxt2 );
        selobjtxt = (std::string)event.GetLabel();
    }
    else
    {
        texture_manager->SetSelectedTexture2( (std::string)event.GetLabel() );
        selobjtxt2 = (std::string)event.GetLabel();
    }


    mUpdateResource();
}

void textureResource::OnItemRightClicked(wxListEvent & event)
{
    if( listview->GetImageList(0) != texturesub_image_list )
        listview->PopupMenu(texture_menu, wxDefaultPosition);
}

void textureResource::OnMenuItemSelected(wxCommandEvent & event)
{
    switch( event.GetId() )
    {
        case 0:
        {
            TextureSub * texture_sub = NULL;
            createTexBlockDlg dialog(this);

            texture_sub = dialog.UsingTexture( texture_manager->GetTexture(selobjtxt.c_str()) );
            if( dialog.showDialog() )
                std::cout << "Sub Texture Creation A Success!\nNumber Of Subs: " << texture_sub->GetNumberOfSubs() << std::endl;
        }
        break;

        case 1:
        break;

        case 2:
        break;

        case 3:
        {
            Texture * texture = texture_manager->GetTexture(selobjtxt.c_str());

            if(texture != NULL)
            {
                TextureSub * texture_sub = texture->GetTextureSub();

                if(texture_sub != NULL)
                {
                    delete texture_sub;
                    texture->SetTextureSub(NULL);
                }
            }
        }
        break;

        default:
        break;
    }
}

void textureResource::OnItemActivated(wxListEvent & event)
{
    Texture * texture = texture_manager->GetTexture(selobjtxt.c_str());

    if( texture != NULL )
        if( texture->GetTextureSub() != NULL )
        {
            TextureSub * texture_sub = texture->GetTextureSub();
            std::cout << "Texture Has Sub Textures!" << std::endl;

            showsubs = true;
            listview->DeleteAllItems();
            texturesub_image_list->RemoveAll();

            if( texturesub_image_list->GetImageCount() <= 0 )
            {
                ntextures = 0;

                for(int i=0; i<texture_sub->GetNumberOfSubs(); i++ )
                {

                    unsigned char * ac_texture_data = Texture::ConvertFromNewToAlloc(texture_sub->GetTexture(i));
                    wxImage img;
                    img.SetData(ac_texture_data, texture_sub->GetTexture(i)->GetTextureWidth(), texture_sub->GetTexture(i)->GetTextureHeight());

                    img.Rescale(32,32);
                    wxBitmap bitmap(img);
                    texturesub_image_list->Add(bitmap);


                    wxListItem listitem;
                    listitem.SetImage(i);
                    listitem.SetId(i);
                    listitem.SetText(texture_sub->GetTexture(i)->GetTextureName());


                    listview->InsertItem(listitem);

                    ntextures++;
                    //delete img;
                }

            }

            listview->SetImageList(texturesub_image_list, 0);
        }
}

void textureResource::OnEnterWindow(wxMouseEvent & event)
{
    if((texture_manager->GetNumberOfTextures() <= 0) && (listview->GetItemCount() > 0) )
        listview->ClearAll();

    if( texture_manager->GetNumberOfTextures() > 0 )
    {
        mUpdateResource();
        listview->Arrange();
    }
}

void textureResource::mUpdateResource()
{
    if((ntextures == texture_manager->GetNumberOfTextures()) && (texture_manager->GetNumberOfTextures()>0) );
    else if( (texture_manager->GetNumberOfTextures() > ntextures) || (texture_manager->GetNumberOfTextures()==0) )
    {

        if( !showsubs )
        {
            listview->SetImageList(texture_image_list, 0);

             if(texture_manager->GetRecent()=="")
                return;

            wxImage img(texture_manager->GetTexture(texture_manager->GetRecent().c_str())->GetTexturePath());
            std::cout << "ImageList -> textureResource : " << texture_manager->GetTexture(texture_manager->GetRecent().c_str())->GetTexturePath() << std::endl;
            img.Rescale(32,32);
            wxBitmap bitmap(img);
            texture_image_list->Add(bitmap);

            wxListItem listitem;
            listitem.SetImage( texture_image_list->GetImageCount()-1 );
            listitem.SetText(texture_manager->GetRecent());

            listview->InsertItem(listitem);
            ntextures++;
        }
        else
        {
            std::cout << "Trying to access texture subs!" << std::endl;
        }

    }
    else if( texture_manager->GetNumberOfTextures() < ntextures )
    {
        if( !showsubs )
        {
            texture_image_list->Remove( listview->FindItem(0, texture_manager->GetRecent()) );
            listview->DeleteItem( listview->FindItem(0, texture_manager->GetRecent()) );

            ntextures--;
        }
    }

}

void textureResource::OnKey(wxKeyEvent & event)
{
    event.Skip();

    if( event.GetKeyCode() == 'R' )
    {
        selobjtxt2.clear();

        showsubs = false;
        listview->DeleteAllItems();
        ntextures = 0;
        std::cout << "Clearing Texture Items And Reseting... " << std::endl;


        listview->SetImageList(texture_image_list, 0);

         if(texture_manager->GetRecent()=="")
            return;

            //wxImage img(texture_manager->GetTexture(texture_manager->GetRecent().c_str())->GetTexturePath());
        for(int i=(int)texture_manager->GetNumberOfTextures()-1; i>=0; i--)
        {
            wxListItem listitem;
            listitem.SetImage(i);
            listitem.SetId(i);
            listitem.SetText(texture_manager->GetTexture(i)->GetTextureName());

            listview->InsertItem(listitem);
            ntextures++;
        }

        listview->SetImageList(texture_image_list, 0);

    }
}

BEGIN_EVENT_TABLE(textureResource, wxPanel)

    EVT_SIZE(textureResource::OnSize)
    EVT_LIST_ITEM_SELECTED(100, textureResource::OnItemSelected)
    EVT_LIST_ITEM_RIGHT_CLICK(100, textureResource::OnItemRightClicked)
    EVT_ENTER_WINDOW(textureResource::OnEnterWindow)
    EVT_LIST_ITEM_ACTIVATED(100, textureResource::OnItemActivated)
    EVT_KEY_DOWN(textureResource::OnKey)

END_EVENT_TABLE()
