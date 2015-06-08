#include "OGLWin.h"



OGLWin::OGLWin(wxWindow * parent, texMng * tMng, entityManager * entity_manager, std::vector<entityManager*> * scene_manager) : wxSplitterWindow(parent, wxID_ANY)
{
    SetWindowStyle(wxBORDER_SUNKEN | wxSP_3DBORDER);

    this->scene_manager = scene_manager;
    texture_manager = tMng;
    m_glContext = NULL;

    toolbar = new ToolBarScene(this);

    Connect(wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGING, wxSplitterEventHandler(OGLWin::SashChange), 0, this);

}

OGLWin::~OGLWin()
{
    delete toolbar;
    delete m_glContext;
}

void OGLWin::InitContext()
{
    Show(true);
    m_glContext = new GLFrame(this, opengl_context);
    m_glContext->LoadSceneManager(scene_manager);
    m_glContext->LoadTexMng(texture_manager);
    m_glContext->Init();
    m_glContext->Render();

    SplitHorizontally(toolbar, m_glContext);
    SetSashPosition(21, true);
    UpdateSize();

    toolbar->BindGLFrame( m_glContext );

}

void OGLWin::BindToolBar(ToolBarScene * toolbar)
{
    this->toolbar = toolbar;
}

void OGLWin::BindTreeView(projectTreeView * tree_view)
{
    this->tree_view = tree_view;
    toolbar->BindTreeView(tree_view);
}

void OGLWin::BindPropertyWindow(propertyWindow * property_window)
{
    m_glContext->BindPropertyWindow(property_window);
}

frameEvent * OGLWin::getFrameEvent()
{
    return m_glContext->getFrameEvent();
}

void OGLWin::OnSize(wxSizeEvent& WXUNUSED(event))
{
    int h, w;
    GetSize(&w, &h);

    if( m_glContext != NULL )
    {
        m_glContext->SetSize(0, GetSashPosition()+10, w, h-GetSashPosition()-10);
        toolbar->SetSize(0, GetSashPosition()-21, GetClientSize().GetWidth(), 16);
    }
}

wxGLContext * OGLWin::GetContext()
{
    return m_glContext->GetContext();
}

Camera * OGLWin::GetCamera()
{
    return m_glContext->GetCamera();
}

void OGLWin::SashChange(wxSplitterEvent & event)
{
    std::cout << event.GetSashPosition() << std::endl;

    int h, w;
    GetSize(&w, &h);

    if( m_glContext != NULL )
    {
        m_glContext->SetSize(0, event.GetSashPosition()+10, w, h-event.GetSashPosition()-10);
        toolbar->SetSize(0, event.GetSashPosition()-21, GetClientSize().GetWidth(), 16 );
    }
}

void OGLWin::OnEnterWindow(wxMouseEvent& WXUNUSED(event))
{
    //SplitVertically(toolbar, m_glContext);

    if( toolbar != NULL )
        toolbar->SetSize(0, GetSashPosition()-21, GetClientSize().GetWidth(), 16 );
    std::cout << "OGLWin Entered!" << std::endl;
    //m_glContext->SetCurrent(*opengl_context);
    m_glContext->SetFocus();

}

void OGLWin::ResetGL()
{
    m_glContext->Reset();
}

BEGIN_EVENT_TABLE(OGLWin, wxSplitterWindow)
    EVT_SIZE(OGLWin::OnSize)
    EVT_ENTER_WINDOW(OGLWin::OnEnterWindow)
END_EVENT_TABLE()
