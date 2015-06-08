#include "winMng.h"
#include "../Common/GApp.h"


winMng::winMng(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    Center();
    Move(200, 200);
    SetSize(800, 600);
    extern bool AppMod;
}

void winMng::ClearData()
{
    win->ResetGL();
    tree_view->DeleteAll();
    anim_manager->RemoveAll();
    texture_manager->removeAllTextures();
    tree_view->SetRootName();
    win->GetCamera()->cam2DPan(0.0f, 0.0f);
}

void winMng::InitPSH()
{
    window_manager.SetManagedWindow(this);
    dockArt = window_manager.GetArtProvider();
    window_manager.SetFlags(wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_DEFAULT);

    fileDialog = new wxFileDialog(NULL);

    wxMenuBar* mbar = new wxMenuBar();

    wxMenu * fileMenu_openSub = new wxMenu();
    fileMenu_openSub->Append(PSH_MENUFILE_OPEN_PRJ, _T("Project"));
    fileMenu_openSub->AppendSeparator();
    fileMenu_openSub->Append(PSH_MENUFILE_OPEN_IMG, _T("image"));
    fileMenu_openSub->Append(PSH_MENUFILE_OPEN_SCPT, _T("script"));
    fileMenu_openSub->Append(PSH_MENUFILE_OPEN_SHDR, _T("shader"));

    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(PSH_MENUFILE_NEW, _("&New") );
    fileMenu->AppendSubMenu( fileMenu_openSub, "Open");
    fileMenu->Append(PSH_MENUFILE_SAVE, _("&Save"), _("Save Project") );
    fileMenu->Append(PSH_MENUFILE_SAVEAS, _("Save As"), _("Save Project As...") );
    fileMenu->Append(PSH_MENUFILE_PREF, _("Preferences"), _("Preferences") );
    fileMenu->Append(PSH_MENUFILE_QUIT, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* viewMenu = new wxMenu(_T(""));
    viewMenu->Append(PSH_MENUVIEW_SCENE, _("&Scene Explorer\tF2"), _("View Scene Explorer"));
    viewMenu->Append(PSH_MENUVIEW_IMAGE, _("&Image Explorer\tF3"), _("View Image Explorer"));
    viewMenu->Append(PSH_MENUVIEW_TREE, _("&Project Tree\tF4")  , _("Project Tree"));
    viewMenu->Append(PSH_MENUVIEW_PROP, _("&Property\tF5")  , _("Property"));
    viewMenu->Append(PSH_MENUVIEW_ANIM, _("&Animation\tF6")  , _("Animation"));
    viewMenu->Append(PSH_MENUVIEW_TEXT, _("&Text/Script\tF7")  , _("Text/Script"));
    mbar->Append(viewMenu, _("&View"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(-1, _("&Help"), _("Open html help doc"));
    helpMenu->Append(-1, _("&Website"), _("Open Website From Browser"));
    helpMenu->Append(PSH_MENUHELP_ABOUT, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);



    CreateStatusBar(2);
    SetStatusText(_("PSH Game Engine Application"),0);
    SetStatusText("", 1);


    wxColour color;
    color.Set(50, 50, 50);
    dockArt->SetColor(8, color);

    //Object Instatiation
    toolbar = new toolBar(this);
    window_manager.AddPane(toolbar, wxTOP);
    window_manager.GetPane(toolbar).Gripper();
    window_manager.GetPane(toolbar).Floatable();
    window_manager.GetPane(toolbar).CaptionVisible(false);
    window_manager.Update();

    toolbar->SetBackgroundColour(color);

    ///////////////////
    ///////////////////
    ///////////////////
    scene_manager    = new SceneManager();
    texture_manager  = new texMng();
    py_pshengine     = new pshEngine();
    scriptMan        = new scriptMng();
    anim_manager     = new animationManager();
    project_document = new ProjectFile();

    /////////////////////
    /////////////////////
    /////////////////////

    resource_window = new resourceWindow(this, PSH_RESOURCE_WINDOW); //TAKE A LOOK AT THIS :: NOTEBOOK CAUSES WARNING
    window_manager.AddPane(resource_window, wxLEFT, wxT("Management"));
    window_manager.Update();

    property_window = new propertyWindow(this, PSH_PROPERTY_WINDOW);
    window_manager.AddPane(property_window, wxLEFT, wxT("New Prop"));
    window_manager.Update();

    text_editor = new textEditor(this);
    window_manager.AddPane(text_editor, wxRIGHT, wxT("text editor"));
    window_manager.Update();

    win = new OGLWin(this, texture_manager, NULL, scene_manager);
    window_manager.AddPane(win, wxCENTRE, wxT("Scene Explorer"));
    window_manager.Update();

    anim_resource_window = new animationResource(this, -1);
    window_manager.AddPane(anim_resource_window, wxBOTTOM, wxT("Animation Explorer"));
    window_manager.Update();

    //Under Testing

    texture_resource_window = new textureResource(this);
    window_manager.AddPane(texture_resource_window, wxRIGHT, wxT("Texture Explorer"));
    window_manager.Update();

    /////////////////////
    /////////////////////
    /////////////////////

    /* Create instance */

    tree_view  = new projectTreeView(resource_window->notebookwindow(), 1006);

/*
    toolbar_scene = new ToolBarScene(this);
    window_manager.AddPane(toolbar_scene, wxTOP);
    window_manager.GetPane(toolbar_scene).Gripper();
    window_manager.GetPane(toolbar_scene).Floatable();
    window_manager.GetPane(toolbar_scene).CaptionVisible(false);
    window_manager.GetPane(toolbar_scene).Centre();
    window_manager.GetPane(toolbar_scene).DockFixed(false);
    window_manager.GetPane(toolbar_scene).MaxSize(win->GetClientSize().GetWidth(), 20);
    window_manager.Update();

    win->BindToolBar(toolbar_scene);
*/
    /////////////////////
    /////////////////////
    /////////////////////

    py_pshengine->BindSceneManager(scene_manager);

    win->InitContext();
    opengl_context = win->GetContext();

    anim_resource_window->InitContext(opengl_context);
    anim_resource_window->BindAnimationManager( anim_manager );
    anim_resource_window->BindTextureManager( texture_manager );
    anim_resource_window->BindTreeViewer( tree_view );
    //anim_resource_window->BindTextureResource( texture_resource_window );

    win->BindTreeView(tree_view);
    win->BindPropertyWindow(property_window);

    //Object Communication

    scriptMan->setObjectManagerBind(scene_manager);
    scriptMan->BindTreeView(tree_view);

    anim_resource_window->BindSceneManager( scene_manager );

    tree_view->BindScriptManager(scriptMan);
    tree_view->BindTextEditor( text_editor );
    tree_view->BindAnimationManager( anim_manager );
    tree_view->BindTextureManager(texture_manager);
    tree_view->BindCamera(win->GetCamera());

    texture_resource_window->BindTextureManager( texture_manager );

    tree_view->BindEntityManager(scene_manager);
    project_document->BindSceneManager(scene_manager);
    project_document->BindTextureManager(texture_manager);
    project_document->BindScriptManager(scriptMan);
    project_document->BindAnimationManager(anim_manager);
    project_document->BindTextureResource(texture_resource_window);
    project_document->BindAnimationResource(anim_resource_window);
    project_document->BindProjectTree( tree_view );

    resource_window->BindTreeView(tree_view);
    resource_window->BindScriptManager(scriptMan);
    resource_window->BindTextEditor( text_editor );
    resource_window->BindAnimationManager( anim_manager );

    property_window->BindProjectTree( tree_view );
    tree_view->BindPropertyWindow( property_window );

    text_editor->BindResourceWindow( resource_window );


    //Setup Windows
    win->SetSize(400, 600);
    tree_view->SetSize(200, 600);



    tree_view->LoadImgFrmPrjFile();

    scriptMan->initManager(py_pshengine);
    scriptMan->BindFrameEvent( win->getFrameEvent() );
    scriptMan->BindCameraFromSceneView( win->GetCamera() );
    anim_resource_window->BindSceneManager( scene_manager );

    property_window->HideDataProperty();
}

winMng::~winMng()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting Program..." << std::endl;
    #endif

    delete anim_manager;
    delete anim_resource_window;

    delete win;
    delete texture_manager;
    delete tree_view; //has a problem deleteing the menus

    for(int i=0; i<(int)scene_manager->size(); i++)
        delete scene_manager->at(i);
    scene_manager->clear();
    delete scene_manager;

    delete fileDialog;
    delete scriptMan;
    delete text_editor;

    delete resource_window;


    delete texture_resource_window;

    delete py_pshengine;
    delete project_document;

    delete property_window;

    window_manager.UnInit();
}


void winMng::OnClose(wxCloseEvent& event)
{
    Destroy();
}


void winMng::OnQuit(wxCommandEvent& event)
{
    Destroy();
}


void winMng::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This app is a 2D Game Engine.\nCreated by Sean Butler", "About");
}


void winMng::viewScene(wxCommandEvent& event)
{
    static bool s = true;

    if(s)
    {
        window_manager.GetPane(win).Show(false);
        s = false;
    }
    else
    {
        window_manager.GetPane(win).Show(true);
        s = true;
    }



    window_manager.Update();
}


void winMng::viewImageExp(wxCommandEvent& event)
{
    static bool s = true;

    if(s)
    {
        window_manager.GetPane(texture_resource_window).Show(false);
        s = false;
    }
    else
    {
        window_manager.GetPane(texture_resource_window).Show(true);
        s = true;
    }


    window_manager.Update();
}


void winMng::viewProjTree(wxCommandEvent& event)
{
    static bool s = true;

    if(s)
    {
        window_manager.GetPane(resource_window).Show(false);
        s = false;
    }
    else
    {
        window_manager.GetPane(resource_window).Show(true);
        s = true;
    }

    window_manager.Update();

}


void winMng::viewProp(wxCommandEvent& event)
{

    static bool s = true;

    if(s)
    {
        window_manager.GetPane(property_window).Show(false);
        s = false;
    }
    else
    {
        window_manager.GetPane(property_window).Show(true);
        s = true;
    }

    window_manager.Update();

}


void winMng::viewAnim(wxCommandEvent& event)
{
    static bool s = true;

    if(s)
    {
        window_manager.GetPane(anim_resource_window).Show(false);
        s = false;
    }
    else
    {
        window_manager.GetPane(anim_resource_window).Show(true);
        s = true;
    }

    window_manager.Update();

}


void winMng::viewText(wxCommandEvent& event)
{
    static bool s = true;

    if(s)
    {
        window_manager.GetPane(text_editor).Show(false);
        s = false;
    }
    else
    {
        window_manager.GetPane(text_editor).Show(true);
        s = true;
    }

    window_manager.Update();

}


void winMng::fileOpen(wxCommandEvent& event)
{
    static bool *ex_AppMod = &AppMod;

    switch( event.GetId() )
    {
        case PSH_MENUFILE_NEW:
        {
            std::cout << "ex_AppMod:" << *ex_AppMod << std::endl;
            if( *ex_AppMod == true )
            {
                int choice = wxMessageBox("Would You Like To Save?", "Save");

                if( choice == wxID_OK )
                {
                    std::cout << "Wanted To Save!" << std::endl;
                }
            }

            NewProjectWiz wiz(this, wxID_ANY);
            wiz.ShowWizard();

            ClearData();
			project_document->ClearDirectoryBaseFile();

            *ex_AppMod = false;
        }

        break;
        case PSH_MENUFILE_OPEN_PRJ:
        {
            int choice;
            fileDialog->SetWindowStyle(wxFD_OPEN);
            fileDialog->SetWildcard("PSH Project *.pshj|*.pshj");
            choice = fileDialog->ShowModal();
            if(((((std::string)fileDialog->GetPath()).length() != 0)) && (choice == wxID_OK) )
            {
                ClearData();

                std::cout << "Project File Found! This Still In Works!" << std::endl;
                project_document->Load( (std::string)fileDialog->GetPath() );

                wxString project_label = PROJECTVERSIONLABEL;
                project_label.append( " : " );
                project_label.append( fileDialog->GetFilename().Before('.') );

                SetLabel( project_label );

                wxString str = fileDialog->GetFilename().Before('.');
                tree_view->SetRootName( str );

                *ex_AppMod = false;
            }
            else
                std::cout << "No File Was Chosen!" << std::endl;
        }
        break;

        case PSH_MENUFILE_OPEN_SCPT:
        {
            int choice;
            fileDialog->SetWildcard("Python *.py|*.py|Any *.*|*.*");
            choice = fileDialog->ShowModal();
            if((((std::string)fileDialog->GetPath()).length() != 0) && (choice == wxID_OK) )
            {
                scriptMan->addScript((std::string)fileDialog->GetPath());
                *ex_AppMod = true;
            }
            else
                std::cout << "No File Was Chosen!" << std::endl;
        }

        break;

        case PSH_MENUFILE_OPEN_IMG:
        {
            int choice;
            fileDialog->SetWildcard("PNG (.png)|*.png|Bitmap (.bmp)|*.bmp|Targa (.tga)|*.tga|JPEG (.jpg)|*.jpg|Any (*.*)|*.*");
            choice = fileDialog->ShowModal();
            if((((std::string)fileDialog->GetPath()).length() != 0) && (choice == wxID_OK) )
            {
                //std::cout << "Working on implementation!" << std::endl;
                std::string path = (std::string)fileDialog->GetPath();
                //std::cout << path << std::endl;
                texture_manager->addTexture( path.c_str(), 0 );
                texture_resource_window->mUpdateResource();
                anim_resource_window->mUpdateResource();
                *ex_AppMod = true;
            }
            else
                std::cout << "No Image Selected Or Format Not Supported!" << std::endl;
        }

        break;

        case PSH_MENUFILE_OPEN_SHDR:
            fileDialog->SetWildcard("Shader *.vert|*.vert|Any *.*|*.*");
            fileDialog->ShowModal();
            if(((std::string)fileDialog->GetPath()).length() != 0)
                std::cout << "Shader File Found! This Still In Works!" << std::endl;
            else
                std::cout << "No File Was Chosen!" << std::endl;
        break;

        case PSH_MENUFILE_SAVE:
		{
			if( !project_document->GetDirectoryBaseFile().empty() )
				project_document->SaveOutput( project_document->GetDirectoryBaseFile() );
			else
			{
				fileDialog->SetWindowStyle(wxFD_SAVE);
				fileDialog->SetWildcard("PSH Project *.pshj|*.pshj|Any *.*|*.*");
				int choice = fileDialog->ShowModal();
				if((((std::string)fileDialog->GetPath()).length() != 0) && (choice == wxID_OK) )
				{
					std::string str;
					str = fileDialog->GetPath();
					if( !is_forard_slash_dir(str) )
						foward_slash_dir(str);

					std::cout << "Project File Found! This Still In Works!" << std::endl;
					std::cout << str << std::endl;

					project_document->SaveOutput(str);

					wxString project_label = PROJECTVERSIONLABEL;
					project_label.append( " : " );
					project_label.append( fileDialog->GetFilename() );

					SetLabel( project_label );
					*ex_AppMod = false;

				}
				else
				{
					std::cout << "No File Was Chosen!" << std::endl;
					project_document->ClearDirectoryBaseFile();
				}
			}

            *ex_AppMod = false;
		}
        break;

        case PSH_MENUFILE_SAVEAS:
		{
            fileDialog->SetWindowStyle(wxFD_SAVE);
            fileDialog->SetWildcard("PSH Project *.pshj|*.pshj|Any *.*|*.*");
            int choice = fileDialog->ShowModal();
            if((((std::string)fileDialog->GetPath()).length() != 0) && (choice == wxID_OK) )
            {
				std::string str;
				str = fileDialog->GetPath();
				if( !is_forard_slash_dir(str) )
					foward_slash_dir(str);

                std::cout << "Project File Found! This Still In Works!" << std::endl;
                std::cout << str << std::endl;

                project_document->SaveOutput(str);

                wxString project_label = PROJECTVERSIONLABEL;
                project_label.append( " : " );
                project_label.append( fileDialog->GetFilename() );

                SetLabel( project_label );
                *ex_AppMod = false;

            }
            else
                std::cout << "No File Was Chosen!" << std::endl;
		}
        break;

        case PSH_MENUFILE_PREF:
        {
            pref_dialog.ShowModal();
        }
        break;

        default:
            std::cout << "Menu Not Supported!" << std::endl;
            event.Skip();
            break;
    }

    //wxMessageBox("Working On It! Doesn't do\nanything at the moment.", "IN PROGRESS");
}


/*void winMng::OnIdle(wxIdleEvent& event)
{

}
*/


/*void winMng::OnSize(wxSizeEvent& event)
{
}*/

void winMng::OnEnterWindow(wxMouseEvent & event)
{
    std::cout << "ENTERED APP WINDOW" << std::endl;
}

void winMng::OnLeaveWindow(wxMouseEvent & event)
{
}


BEGIN_EVENT_TABLE(winMng, wxFrame)
    EVT_CLOSE(winMng::OnClose)
    EVT_MENU(PSH_MENUFILE_QUIT, winMng::OnQuit)
    EVT_MENU(PSH_MENUHELP_ABOUT, winMng::OnAbout)
    EVT_MENU(PSH_MENUVIEW_SCENE, winMng::viewScene)
    EVT_MENU(PSH_MENUVIEW_IMAGE, winMng::viewImageExp)
    EVT_MENU(PSH_MENUVIEW_TREE, winMng::viewProjTree)
    EVT_MENU(PSH_MENUVIEW_PROP, winMng::viewProp)
    EVT_MENU(PSH_MENUVIEW_ANIM, winMng::viewAnim)
    EVT_MENU(PSH_MENUVIEW_TEXT, winMng::viewText)
    EVT_MENU(PSH_MENUFILE_OPEN_SCPT, winMng::fileOpen)
    EVT_MENU(PSH_MENUFILE_OPEN_IMG, winMng::fileOpen)
    EVT_MENU(PSH_MENUFILE_OPEN_PRJ, winMng::fileOpen)
    EVT_MENU(PSH_MENUFILE_OPEN_SHDR, winMng::fileOpen)
    EVT_MENU(PSH_MENUFILE_SAVE, winMng::fileOpen)
    EVT_MENU(PSH_MENUFILE_SAVEAS, winMng::fileOpen)
    EVT_MENU(PSH_MENUFILE_NEW, winMng::fileOpen)
    EVT_MENU(PSH_MENUFILE_PREF, winMng::fileOpen)
    EVT_ENTER_WINDOW(winMng::OnEnterWindow)
    EVT_LEAVE_WINDOW(winMng::OnLeaveWindow)
    //EVT_TREE_SEL_CHANGED(1006, winMng::OnTreeSelect)
    //EVT_SIZE(winMng::OnSize)
    //EVT_IDLE(winMng::OnIdle)
END_EVENT_TABLE()


