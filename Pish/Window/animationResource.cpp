#include "../Window/animationResource.h"

animationResource::animationResource(wxWindow * parent, wxWindowID id) : wxPanel(parent, id)
{

    texture_manager  = NULL;
    anim_manager     = NULL;
    scene_manager    = NULL;
    tree_view        = NULL;

    notebook = new wxNotebook(this, 1000);

    main_window    = new wxPanel(notebook, -1);
    edit_window    = new wxPanel(notebook, -1);
    preview_window = new wxPanel(notebook, -1);

    preview_window->SetBackgroundColour( wxColour(0, 255, 0, 255) );
    edit_window->SetBackgroundColour( wxColour(0, 0, 255, 255) );

    notebook->AddPage(main_window, "main");
    notebook->AddPage(edit_window, "edit");
    notebook->AddPage(preview_window, "preview");

    scene_manager   = NULL;
    texture_manager = NULL;
    context_render  = true;

    /// ///////////////////////////////////////////

    m_animlist = new wxMenu();
    m_animlist->Append(100, "Attach Animation");
    m_animlist->Append(200, "Remove Animation");
    m_animlist->Append(300, "Delete Animation");

    /// ///////////////////////////////////////////

    object_tree    = new wxTreeCtrl(main_window);
    animation_list = new wxListCtrl(main_window, 2000);
    texture_resource = new textureResource(edit_window);


    /// ///////////////////////////////////////////

    scrolled_frame = 0;

    b_nextframe   = new wxButton( preview_window, 100, ">>" );
    b_prevframe   = new wxButton( preview_window, 200, "<<" );
    b_addframe    = new wxButton( preview_window, 1000, "+");
    b_removeframe = new wxButton( preview_window, 2000, "-" );
    b_update      = new wxButton( preview_window, 3000, "update" );

    b_attachanim  = new wxButton( main_window, 4000, "Attach" );
    b_removeanim  = new wxButton( main_window, 4001, "Remove" );
    b_deleteanim  = new wxButton( main_window, 4002, "Delete" );

    txt_setfps    = new wxTextCtrl( main_window , 200);
    txt_animname  = new wxTextCtrl( main_window , 100);

    txt_setfps->Move( int(GetClientSize().GetWidth()*0.68), 20);
    txt_animname->Move( int(GetClientSize().GetWidth()*0.68), 0);

    txt_animname->SetWindowStyle(wxTE_PROCESS_ENTER | wxTE_LEFT);

    Connect(100,  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(animationResource::ClickedButton));
    Connect(200,  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(animationResource::ClickedButton));
    Connect(1000, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(animationResource::ClickedButton));
    Connect(2000, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(animationResource::ClickedButton));
    Connect(3000, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(animationResource::ClickedButton));
    Connect(4000, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(animationResource::ClickedButton));
    Connect(4001, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(animationResource::ClickedButton));
    Connect(4002, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(animationResource::ClickedButton));


    txt_animname->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(animationResource::TxtChange), NULL, this);
    animation_list->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(animationResource::ListClick), NULL, this);
    m_animlist->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(animationResource::MenuCommand), NULL, this);

    pickedAnimation = 0;

}

animationResource::~animationResource()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting animationResource!" << std::endl;
    #endif

    delete b_addframe;
    delete b_attachanim;
    delete b_deleteanim;
    delete b_nextframe;
    delete b_prevframe;
    delete b_removeanim;
    delete b_removeframe;
    delete b_update;

    delete txt_animname;
    delete txt_setfps;

    delete frame;
    delete frame_view;
    delete texture_resource;

    delete object_tree;
    delete animation_list;

    delete main_window;
    delete edit_window;
    delete preview_window;
    delete notebook;


}

void animationResource::InitContext(wxGLContext * gl_context)
{
    this->opengl_context = gl_context;
    frame = new Sprite();
    frame->init();

    frame->setPosition(0, 0, 0);
    frame_view   = new wxGLCanvas( preview_window, wxID_ANY, (const int *)0);
}

void animationResource::mUpdateResource()
{
    texture_resource->mUpdateResource();
}

void animationResource::Render_CurrentPreview()
{
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    if( pickedAnimation < anim_manager->number_of_animations() )
    {

        static float dt=0.0f;
        dt+=0.01f;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();

            glOrtho(-1, 1, -1, 1, 0, 1);

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        if( anim_manager != NULL )
        if( anim_manager->getAnimation(pickedAnimation)->s_GetFrame(scrolled_frame).length() > 0 )
        {
            frame->setScale(0.5, -0.5);
            frame->setPosition(0, 0);

            if( anim_manager->getAnimation(pickedAnimation)->s_GetFrame2(scrolled_frame).empty() )
                frame->setTexture( anim_manager->getAnimation(pickedAnimation)->s_GetFrame(scrolled_frame) );
            else
            {
                frame->setTexture( anim_manager->getAnimation(pickedAnimation)->s_GetFrame(scrolled_frame) );
                frame->setTextureSub( anim_manager->getAnimation(pickedAnimation)->s_GetFrame2(scrolled_frame) );
            }


            frame->draw();
        }

    }

}

void animationResource::Render_preview()
{
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    if( pickedAnimation < anim_manager->number_of_animations() )
    {

        static float dt=0.0f;
        dt+=0.01f;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();

            glOrtho(-1, 1, -1, 1, 0, 1);

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        //if( this->anim_manager->getAnimation(pickedAnimation)->IsPlaying() == false )
        {
            //this->anim_manager->getAnimation(pickedAnimation)->setFPS(12);
            this->anim_manager->getAnimation(pickedAnimation)->Start();
            this->anim_manager->getAnimation(pickedAnimation)->Play();
        }

        frame->setScale(0.5, -0.5);
        frame->setPosition(0, 0);
        //frame->setTexture( this->anim_manager->getAnimation(pickedAnimation)->s_CurrentFrame() );

        if( anim_manager->getAnimation(pickedAnimation)->s_GetFrame2(this->anim_manager->getAnimation(pickedAnimation)->CurrentFrame()).empty() )
            frame->setTexture( this->anim_manager->getAnimation(pickedAnimation)->s_CurrentFrame() );
        else
        {
            frame->setTexture( anim_manager->getAnimation(pickedAnimation)->s_GetFrame(this->anim_manager->getAnimation(pickedAnimation)->CurrentFrame()) );
            frame->setTextureSub( anim_manager->getAnimation(pickedAnimation)->s_GetFrame2(this->anim_manager->getAnimation(pickedAnimation)->CurrentFrame()) );
        }

        //if( this->anim_manager->getAnimation(pickedAnimation)->s_CurrentFrame() != 0 )
            frame->draw();

    }

}

void animationResource::update_object_tree()
{
    static int t=0;
    int n=0;
    wxTreeItemId tree_id;

    for(int i=0; i<(int)scene_manager->size(); i++)
        n += scene_manager->at(i)->number_of_entitys();

    if( n != t)
    {
        object_tree->DeleteAllItems();
        object_tree->AddRoot("Root");

        for(int i=0; i<(int)scene_manager->size(); i++)
        {
            tree_id = object_tree->AppendItem( object_tree->GetRootItem(), scene_manager->at(i)->SceneName() );

            for(int j=0; j<scene_manager->at(i)->number_of_entitys(); j++)
            {
                //This is beating around the bush. There should be a function to easily get the entity with an index value.
                Entity * mobj = scene_manager->at(i)->getEntity( j );
                if( typeid(*mobj) == typeid(Sprite) )
                {
                    wxTreeItemId sub_id;

                    sub_id = object_tree->AppendItem( tree_id, mobj->getName() );
                    t++;

                    for(int k=0; k<((Sprite*)mobj)->GetNumberOfAnimation(); k++)
                        object_tree->AppendItem( sub_id, ((Sprite*)mobj)->GetAnimationName(k));

                }
            }
        }

    }
}

void animationResource::update_anim_list()
{
    animation_list->ClearAll();

    for(int i=0; i<anim_manager->number_of_animations(); i++)
        animation_list->InsertItem( animation_list->GetItemCount(), anim_manager->getAnimation(i)->AnimName());

    animation_list->InsertItem(animation_list->GetItemCount(), "<Add New Animation>");
}

void animationResource::BindAnimationManager(animationManager * anim_manager)
{
    this->anim_manager = anim_manager;

    if( anim_manager->number_of_animations() != 0 )
    {
        txt_setfps->WriteText("12");
        txt_animname->WriteText( anim_manager->getAnimation( pickedAnimation )->AnimName() );
    }
    else
    {
        txt_animname->WriteText( "<no animation selected>" );
        txt_setfps->WriteText("0");
    }

    update_anim_list();

}

void animationResource::BindSceneManager( SceneManager * scene_manager )
{
    this->scene_manager = scene_manager;

    update_object_tree();
}

void animationResource::BindTextureManager( texMng * texture_manager )
{
    this->texture_manager = texture_manager;
    max_textures = texture_manager->GetNumberOfTextures();
    frame->initTextureManage(texture_manager);

    texture_resource->BindTextureManager( texture_manager );
}

void animationResource::BindTreeViewer(projectTreeView * tree_view)
{
    this->tree_view = tree_view;
}
/*
void animationResource::BindTextureResource(textureResource * texture_resource)
{
    this->texture_resource = texture_resource;
}
*/
void animationResource::OnSize(wxSizeEvent & event)
{
    notebook->SetSize( event.GetSize() );

    int nw, nh;
    nw = notebook->GetClientSize().GetWidth();
    nh = notebook->GetClientSize().GetHeight();

    if(txt_animname != NULL)
    {
        //txt_animname->Move( (int)(nw*0.68), 0); // causes problems
        //txt_setfps->Move( (int)(nw*0.68), 20);
    }

    object_tree->SetSize( event.GetSize().GetWidth()/3, event.GetSize().GetHeight()-20 );
    animation_list->SetSize(event.GetSize().GetWidth()/3, 0, event.GetSize().GetWidth()/3, event.GetSize().GetHeight()-20);

    if( notebook->GetPageText( notebook->GetSelection() ).compare("preview") == 0 )
    {
        frame_view->SetSize(0, 0, nw, nh-21 );
    }
    else if( notebook->GetPageText( notebook->GetSelection() ).compare("edit") == 0 )
    {
        preview_window->SetSize(nw/2, 21, nw/2, nh-21 );

        frame_view->SetSize(0, 0, nw/2, nh-70 );
        texture_resource->SetSize(0, 0, nw/2, nh-21);

        b_nextframe->SetSize((nw/4)+40, nh-70, 40, 20);
        b_prevframe->SetSize((nw/4)-40, nh-70, 40, 20);

        b_addframe->SetSize((nw/4)+100, nh-70, 30, 20);
        b_removeframe->SetSize((nw/4)+100, nh-50, 30, 20);

        b_update->SetSize((nw/4)+130, nh-70, 50, 20);

    }


}

void animationResource::OnEnterWindow(wxMouseEvent & event)
{
    SetFocus();

    int w, h;
    GetClientSize(&w, &h);
    glViewport(0, 0, w, h);

    update_object_tree();
    update_anim_list();

    context_render = false;

}

void animationResource::OnLeaveWindow(wxMouseEvent & event)
{
    context_render = true;
}

void animationResource::NotebookPageChange(wxNotebookEvent & event)
{

    if( notebook->GetPageText( event.GetSelection() ).compare("preview") == 0 && opengl_context != NULL )
    {
        main_window->Show(false);
        edit_window->Show(false);


        frame_view->Reparent( preview_window );

        preview_window->Update();

        preview_window->SetSize(0, 21, GetClientSize().GetWidth(), GetClientSize().GetHeight()-21 );
        frame_view->SetSize(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight()-21 );

        frame_view->SetCurrent(*opengl_context);
        frame_view->Show(true);
        glEnable( GL_TEXTURE_2D );

        b_nextframe->Show(false);
        b_prevframe->Show(false);
        b_addframe->Show(false);
        b_removeframe->Show(false);
        b_update->Show(false);


    }
    else if( notebook->GetPageText( event.GetSelection() ).compare("edit") == 0 && opengl_context != NULL )
    {
        max_textures = texture_manager->GetNumberOfTextures();

        main_window->Show(false);

        frame_view->Reparent( preview_window );

        preview_window->Update();
        edit_window->Update();

        int nw, nh;
        nw = notebook->GetClientSize().GetWidth();
        nh = notebook->GetClientSize().GetHeight();

        edit_window->SetSize(0, 21, nw/2, nh-21);
        edit_window->Show(true);

        preview_window->SetSize(nw/2, 21, nw/2, nh-21 );
        preview_window->Show(true);


        frame_view->SetSize(0, 0, nw/2, nh-70 );
        texture_resource->SetSize(0, 0, nw/2, nh-21);

        frame_view->SetCurrent(*opengl_context);
        frame_view->Show(true);
        glEnable( GL_TEXTURE_2D );

        texture_resource->Show(true);
        glEnable( GL_TEXTURE_2D );

        /////////////////////////////

        b_nextframe->SetSize((nw/4)+40, nh-70, 40, 20);
        b_nextframe->Show(true);

        b_prevframe->SetSize((nw/4)-40, nh-70, 40, 20);
        b_prevframe->Show(true);

        b_addframe->SetSize((nw/4)+100, nh-70, 30, 20);
        b_addframe->Show(true);

        b_removeframe->SetSize((nw/4)+100, nh-50, 30, 20);
        b_removeframe->Show(true);

        b_update->SetSize((nw/4)+130, nh-70, 50, 20);
        b_update->Show(true);

    }
    else if( notebook->GetPageText( event.GetSelection() ).compare("main") == 0 )
    {
        int nw, nh;
        nw = notebook->GetClientSize().GetWidth();
        nh = notebook->GetClientSize().GetHeight();

        main_window->Show(true);
        edit_window->Show(false);
        preview_window->Show(false);

        //b_attachanim->SetSize(0, 0, 20, 20);
        //b_attachanim->Show(true);
        //b_removeanim->SetSize(0, 0, 20, 20);
        //b_removeanim->Show(true);
        //b_deleteanim->SetSize(0, 0, 20, 20);
        //b_deleteanim->Show(true);


        //txt_animname->Show(true);
        //txt_setfps->SetSize(0, 0, 20, 20);
        //txt_setfps->Show(true);

    }

}

void animationResource::OnPaint(wxPaintEvent & event)
{
    event.Skip(context_render);

    if( notebook->GetPageText( notebook->GetSelection() ).compare("preview") == 0 )
    {
        texture_resource->Show(false);

        frame_view->SetCurrent(*opengl_context);
        glViewport(0, 0, frame_view->GetClientSize().GetWidth(), frame_view->GetClientSize().GetHeight());
        Render_preview();
        //glFlush();
        frame_view->SwapBuffers();

        //std::cout << "Rendering Preview!" << std::endl;
    }
    else if( notebook->GetPageText( notebook->GetSelection() ).compare("edit") == 0 )
    {
        texture_resource->Show(true);

        frame_view->SetCurrent(*opengl_context);
        glViewport(0, 0, frame_view->GetClientSize().GetWidth(), frame_view->GetClientSize().GetHeight());
        Render_CurrentPreview();
        glFinish();
        frame_view->SwapBuffers();


        //std::cout << "Rendering Edit!" << std::endl;
    }
}

void animationResource::OnIdle(wxIdleEvent & event)
{
    wxPaintEvent pevent(wxEVT_PAINT);
    AddPendingEvent(pevent);

    event.RequestMore();
    event.Skip();
}

void animationResource::PickedListItem(wxListEvent & event)
{
    pickedAnimation = event.GetItem().GetId();
    txt_animname->Clear();

    if( pickedAnimation < anim_manager->number_of_animations() )
        txt_animname->WriteText( anim_manager->getAnimation( pickedAnimation )->AnimName() );
}

void animationResource::DblClickListItem(wxListEvent & event)
{
    if( pickedAnimation == anim_manager->number_of_animations() )
    {
        std::string name = "NewAnimation";
        char n[3];

        for(int i=0; i<anim_manager->number_of_animations(); i++)
			if (anim_manager->getAnimation(i)->AnimName().compare(name) == 0){
				#ifdef __WIN32__
				name.append(_itoa(i, n, 10));
				#else
				sprintf(n, "%d", i);
				name.append(n);
				#endif
			}

        Animation * n_animation;
        n_animation = new Animation();
        n_animation->SetAnimationName(name);
        n_animation->AddFrame(0);

        anim_manager->InsertAnimation( name, n_animation );

        update_anim_list();
    }
}

void animationResource::ClickedButton(wxCommandEvent & event)
{
    switch( event.GetId() )
    {
        case 100:
            scrolled_frame++;

            if( scrolled_frame > anim_manager->getAnimation(pickedAnimation)->GetNumberOfFrames()-1 )
                scrolled_frame = anim_manager->getAnimation(pickedAnimation)->GetNumberOfFrames()-1;

            std::cout << "NFrames: " << anim_manager->getAnimation(pickedAnimation)->GetNumberOfFrames() << " | CurrentFrame: " << scrolled_frame << std::endl;

        break;

        case 200:
            scrolled_frame--;

            if( scrolled_frame < 0 )
                scrolled_frame = 0;

            std::cout << "NFrames: " << anim_manager->getAnimation(pickedAnimation)->GetNumberOfFrames() << " | CurrentFrame: " << scrolled_frame << std::endl;

        break;

        case 1000:
            anim_manager->getAnimation(pickedAnimation)->s_AddFrame("");
        break;

        case 2000:
            anim_manager->getAnimation(pickedAnimation)->s_RemoveFrame(scrolled_frame);

            if( scrolled_frame > anim_manager->getAnimation(pickedAnimation)->GetNumberOfFrames()-1)
                scrolled_frame = anim_manager->getAnimation(pickedAnimation)->GetNumberOfFrames()-1;

        break;

        case 3000:

            anim_manager->getAnimation(pickedAnimation)->s_SetFrame( scrolled_frame,
                                                                     texture_resource->GetTexture(), texture_resource->GetTextureSub() );
        break;

        default:
            event.Skip();
        break;
    };
}

void animationResource::TxtChange(wxCommandEvent & event)
{
    std::string prev_name = anim_manager->getAnimation(pickedAnimation)->AnimName();

    anim_manager->ChangeAnimationName( prev_name, (std::string)event.GetString() );
    update_anim_list();
}

void animationResource::ListClick(wxMouseEvent & event)
{
    event.Skip();

    switch( event.GetButton() )
    {
        case wxMOUSE_BTN_RIGHT:
            std::cout << "List Right Clicked!" << std::endl;

            if( pickedAnimation < anim_manager->number_of_animations())
                PopupMenu( m_animlist, event.GetPosition().x+(notebook->GetClientSize().GetWidth()/3), event.GetPosition().y+20 );

        break;

        default:
        break;
    }
}

void animationResource::MenuCommand(wxCommandEvent & event)
{
    switch( event.GetId() )
    {
        case 100:
        {
            if( (anim_manager->number_of_animations() > 0) && (pickedAnimation < anim_manager->number_of_animations()) && (pickedAnimation >= 0) )
            {
                Sprite * stemp = NULL;

                if( anim_manager->getAnimation(pickedAnimation) != NULL )
                {
                    Animation * _addanim = new Animation( *anim_manager->getAnimation(pickedAnimation) );
                    stemp = ((Sprite*)scene_manager->at(tree_view->GetActiveScene())->getEntity( (std::string)object_tree->GetItemText(object_tree->GetSelection()) ));
                    stemp->AddAnimation(_addanim);

                    std::cout << "Attaching Animation too: " << stemp->getName() << "\nNumber of Animations: " << stemp->GetNumberOfAnimation() << std::endl;
                }
                else
                    std::cout << "Animation Not Found!" << std::endl;
            }
        }
        break;

        case 200:

            for(int i=0; i<(int)scene_manager->size(); i++)
                for(int j=0; j<scene_manager->at(i)->number_of_entitys(); j++)
                {
                    Entity * _e = scene_manager->at(i)->getEntity(j);

                    if( typeid(*_e) == typeid(Sprite) )
                        for(int k=0; k<((Sprite*)_e)->GetNumberOfAnimation(); k++ )
                            if( ((Sprite*)_e)->GetAnimationName(k) == anim_manager->getAnimation( pickedAnimation )->AnimName() )
                            {
                                ((Sprite*)_e)->RemoveAnimation(k);
                                break;
                            }

                }

        break;

        case 300:

            for(int i=0; i<(int)scene_manager->size(); i++)
                for(int j=0; j<scene_manager->at(i)->number_of_entitys(); j++)
                {
                    Entity * _e = scene_manager->at(i)->getEntity(j);

                    if( typeid(*_e) == typeid(Sprite) )
                        for(int k=0; k<((Sprite*)_e)->GetNumberOfAnimation(); k++ )
                            if( ((Sprite*)_e)->GetAnimationName(k) == anim_manager->getAnimation( pickedAnimation )->AnimName() )
                                ((Sprite*)_e)->RemoveAnimation(k);

                }

                anim_manager->RemoveAnimation(pickedAnimation);


        break;

        default:
        break;
    }
}

BEGIN_EVENT_TABLE(animationResource, wxPanel)

    EVT_SIZE(animationResource::OnSize)
    EVT_ENTER_WINDOW(animationResource::OnEnterWindow)
    EVT_LEAVE_WINDOW(animationResource::OnLeaveWindow)
    EVT_NOTEBOOK_PAGE_CHANGED(1000, animationResource::NotebookPageChange)
    EVT_PAINT(animationResource::OnPaint)
    EVT_IDLE(animationResource::OnIdle)

    EVT_LIST_ITEM_SELECTED(2000, animationResource::PickedListItem)
    EVT_LIST_ITEM_ACTIVATED(2000, animationResource::DblClickListItem)

    //EVT_TEXT_ENTER(100, animationResource::TxtChange)

END_EVENT_TABLE()
