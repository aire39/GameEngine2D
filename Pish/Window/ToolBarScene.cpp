#include "../Window/ToolBarScene.h"
#include "../Window/projectTreeView.h"
#include "../Core/GLFrame.h"
#include <iostream>

ToolBarScene::ToolBarScene(wxWindow * parent, wxWindowID id) : wxToolBar(parent, id)
{
    wxInitAllImageHandlers();
    SetToolBitmapSize(wxSize(16, 16));
//cursor-arrow.png
    wxImage img;
    img.LoadFile("./UI_Images/cursor-arrow.png");
    img.Rescale(16, 16);
    wxBitmap bitmap(img);

    img.LoadFile("./UI_Images/scene_icon64x64.gif");
    img.Rescale(16, 16);
    wxBitmap bitmap1(img);

    img.LoadFile("./UI_Images/duplicate.png");
    img.Rescale(16, 16);
    wxBitmap bitmap2(img);

    img.LoadFile("./UI_Images/Paintbrush-128x128.png");
    img.Rescale(16, 16);
    wxBitmap bitmap3(img);

    AddTool(0, "info"     , bitmap);
    AddTool(1, "objects"  , bitmap1, "Add Objects", wxITEM_NORMAL);
    AddTool(2, "duplicate", bitmap2, "Duplicate Objects", wxITEM_NORMAL);
    AddTool(3, "paint"    , bitmap3, "Texture Objects", wxITEM_NORMAL);

    objectsmenu   = new wxMenu();
    duplicatemenu = new wxMenu();
    paintmenu     = new wxMenu();

    objectsmenu->Append(100, "empty");
    objectsmenu->Append(101, "sprite");
    objectsmenu->Append(102, "text");
    objectsmenu->Append(103, "tile");
    objectsmenu->Append(104, "mesh");

    duplicatemenu->Append(105, "duplicate");
    duplicatemenu->Append(106, "duplicate extended");

    paintmenu->AppendCheckItem(107, "paint single");
    paintmenu->AppendCheckItem(108, "paint area");

    tree_view = NULL;
    glFrame   = NULL;

    Realize();

    //SetDropdownMenu(1, objectsmenu);
    //SetDropdownMenu(2, duplicatemenu);
    //SetDropdownMenu(3, paintmenu);

    Connect(100, 108, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ToolBarScene::ToolMenuEvent));

}

ToolBarScene::~ToolBarScene()
{
    delete objectsmenu;
    objectsmenu = NULL;
    delete duplicatemenu;
    duplicatemenu = NULL;
    delete paintmenu;
    paintmenu = NULL;

    for(int i=3; i>=0; i--)
        RemoveTool(i);
}

void ToolBarScene::BindTreeView(projectTreeView * tree_view)
{
    this->tree_view = tree_view;
}

void ToolBarScene::BindGLFrame(GLFrame * glFrame)
{
    this->glFrame = glFrame;
}

void ToolBarScene::ToolEvent(wxCommandEvent & event)
{
    event.Skip();

    switch(event.GetId())
    {
        case 0:
            std::cout << "Info Tool" << std::endl;
        break;

        case 1:
            std::cout << "Objects Tool" << std::endl;
            PopupMenu(objectsmenu);
        break;

        case 2:
            std::cout << "Duplicate Tool" << std::endl;
            PopupMenu(duplicatemenu);
        break;

        case 3:
            std::cout << "Paint Tool" << std::endl;
            PopupMenu(paintmenu);
        break;

        default:
        break;
    }
}

void ToolBarScene::ToolMenuEvent(wxCommandEvent & event)
{
    event.Skip();

    switch(event.GetId())
    {
        case 100:

            if(tree_view != NULL)
            {
                tree_view->AddEntity( tree_view->GetActiveScene(), PSHEMPTY);
            }

        break;

        case 101:
            if(tree_view != NULL)
            {
                tree_view->AddEntity( tree_view->GetActiveScene(), PSHSPRITE);
            }
        break;

        case 102:
            if(tree_view != NULL)
            {
                tree_view->AddEntity( tree_view->GetActiveScene(), PSHTEXT);
            }
        break;

        case 103:
            if(tree_view != NULL)
            {
                std::cout << "Will cause a crash so it needs to be seriously reworked!" << std::endl;
                //tree_view->AddEntity( tree_view->GetActiveScene(), "tile");
            }
        break;

        case 104:
            if(tree_view != NULL)
            {
                std::cout << "Needs to be implemented : Need to move .obj code into source." << std::endl;
                //tree_view->AddEntity( tree_view->GetActiveScene(), "mesh");
            }
        break;

        case 105:
            if(tree_view != NULL)
            {
                Entity * source_object = NULL;
                source_object = tree_view->selectedEntity();

                if( source_object != NULL )
                {
                    if( typeid(*source_object) == typeid(Entity) )
                    {
                        Entity * cpy_object = NULL;
                        cpy_object = tree_view->AddEntity(tree_view->GetActiveScene(), PSHEMPTY);
                        *cpy_object = *source_object;
                    }
                    else if( typeid(*source_object) == typeid(Sprite) )
                    {
                        Sprite * cpy_object = NULL;
                        cpy_object = (Sprite*)tree_view->AddEntity(tree_view->GetActiveScene(), PSHSPRITE);
                        *cpy_object = *(Sprite*)source_object;
                    }
                    else if( typeid(*source_object) == typeid(Text) )
                    {
                        Text * cpy_object = NULL;
                        cpy_object = (Text*)tree_view->AddEntity(tree_view->GetActiveScene(), PSHTEXT);
                        *cpy_object = *(Text*)source_object;
                    }
                }

            }
        break;

        case 106:
            if(tree_view != NULL)
            {
                entityDupDlg cpydlg;

                Entity * source_object = NULL;
                source_object = tree_view->selectedEntity();

                if( source_object != NULL )
                {
                    int choice = cpydlg.ShowModal();

                    if( choice == wxID_OK )
                    {
                        if( typeid(*source_object) == typeid(Entity) )
                        {
                            Entity * cpy_object = NULL;
                            cpy_object = tree_view->AddEntity(tree_view->GetActiveScene(), PSHEMPTY);

                            if( cpydlg.IsPosition() )
                                cpy_object->setPosition( source_object->getPosition() );

                            if( cpydlg.IsScale() )
                                cpy_object->setScale( source_object->getScale() );

                            if( cpydlg.IsColor() )
                                cpy_object->setColor( source_object->getColor() );
                        }
                        else if( typeid(*source_object) == typeid(Sprite) )
                        {
                            Sprite * cpy_object = NULL;
                            cpy_object = (Sprite*)tree_view->AddEntity(tree_view->GetActiveScene(), PSHSPRITE);
                            //*cpy_object = *(Sprite*)source_object;

                            if( cpydlg.IsPosition() )
                                cpy_object->setPosition( source_object->getPosition() );

                            if( cpydlg.IsScale() )
                                cpy_object->setScale( source_object->getScale() );

                            if( cpydlg.IsColor() )
                                cpy_object->setColor( source_object->getColor() );

                            if( cpydlg.IsTextures() )
                            {
                                cpy_object->setTexture( ((Sprite*)source_object)->getTexture() );
                                cpy_object->setTextureSub( ((Sprite*)source_object)->getTextureSub() );
                            }
                        }
                        else if( typeid(*source_object) == typeid(Text) )
                        {
                            Text * cpy_object = NULL;
                            cpy_object = (Text*)tree_view->AddEntity(tree_view->GetActiveScene(), PSHTEXT);

                            cpy_object->setText( ((Text*)source_object)->getText() );

                            if( cpydlg.IsPosition() )
                                cpy_object->setPosition( source_object->getPosition() );

                            if( cpydlg.IsScale() )
                                cpy_object->setScale( source_object->getScale() );

                            if( cpydlg.IsColor() )
                                cpy_object->setColor( source_object->getColor() );
                        }

                    }

                }

            }

        break;

        case 107:
            if(glFrame != NULL)
            {
                static bool pmode = false;

                pmode ^= true;
                glFrame->SetPaintMode(pmode);

                if( pmode )
                    paintmenu->Check(108, false);
            }

        break;

        case 108:
            if(glFrame != NULL)
            {
                static bool pmode_area = false;

                pmode_area ^= true;
                //glFrame->SetPaintMode(pmode);
                if( pmode_area )
                    paintmenu->Check(107, false);
            }

        break;

        default:
        break;
    }
}

BEGIN_EVENT_TABLE(ToolBarScene, wxToolBar)

EVT_TOOL(0, ToolBarScene::ToolEvent)
EVT_TOOL(1, ToolBarScene::ToolEvent)
EVT_TOOL(2, ToolBarScene::ToolEvent)
EVT_TOOL(3, ToolBarScene::ToolEvent)

END_EVENT_TABLE()
