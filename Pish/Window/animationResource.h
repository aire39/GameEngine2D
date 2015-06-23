#ifndef ANIMATIONRESOURCE_H
#define ANIMATIONRESOURCE_H

#include "../Common/GLee.h"

#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/glcanvas.h>
#include <wx/treectrl.h>
#include <wx/listctrl.h>
#include <wx/bmpbuttn.h>

#include "../Management/texMng.h"
#include "../Management/animationManager.h"
#include "../Management/entityManager.h"
#include "../Window/textureResource.h"

typedef std::vector<entityManager *> SceneManager;

class animationResource : public wxPanel
{
    DECLARE_EVENT_TABLE()

    private:
        wxGLContext      * opengl_context;

        wxNotebook       * notebook;
        animationManager * anim_manager;
        SceneManager     * scene_manager;
        texMng           * texture_manager;
        projectTreeView  * tree_view;

        textureResource  * texture_resource;

        ///////////////////////////////////////////

        wxWindow * preview_window;
        wxWindow * edit_window;
        wxWindow * main_window;

        ///////////////////////////////////////////

        wxMenu * m_animlist;

        ///////////////////////////////////////////

        wxTreeCtrl * object_tree;
        wxListCtrl * animation_list;

        ///////////////////////////////////////////

        wxButton   * b_addframe;
        wxButton   * b_removeframe;
        wxButton   * b_nextframe;
        wxButton   * b_prevframe;
        wxButton   * b_update;

        wxButton   * b_attachanim;
        wxButton   * b_removeanim;
        wxButton   * b_deleteanim;

        ////////////////////////////////////////////

        wxTextCtrl * txt_setfps;
        wxTextCtrl * txt_animname;

        ///////////////////////////////////////////

        wxGLCanvas * frame_view;
        Sprite     * frame;

        ///////////////////////////////////////////

        wxBitmapButton * button_play;
        wxBitmapButton * button_next;
        wxBitmapButton * button_prev;
        wxBitmapButton * button_beg;
        wxBitmapButton * button_end;

        ///////////////////////////////////////////

        void update_object_tree();
        void update_anim_list();

        void Render_preview();
        void Render_CurrentPreview();

        bool context_render;

        int pickedAnimation;
        int scrolled_frame;

        int max_textures;


    public:

        animationResource(wxWindow * parent=NULL, wxWindowID id=-1);
        ~animationResource();

        void BindAnimationManager( animationManager * anim_manager );
        void BindSceneManager( SceneManager * scene_manager );
        void BindTextureManager( texMng * texture_manager );
        void BindTreeViewer( projectTreeView * tree_view );
        //void BindTextureResource( textureResource * texture_resource );

        void InitContext(wxGLContext * gl_context);
        void mUpdateResource();

        void OnSize(wxSizeEvent & event);
        void OnEnterWindow(wxMouseEvent & event);
        void OnLeaveWindow(wxMouseEvent & event);
        void NotebookPageChange( wxNotebookEvent & event );

        void OnPaint(wxPaintEvent & event);
        void OnIdle(wxIdleEvent & event);

        void PickedListItem(wxListEvent & event);
        void DblClickListItem(wxListEvent & event);
        void ClickedButton(wxCommandEvent &event);
        void TxtChange( wxCommandEvent & event);
        void ListClick( wxMouseEvent & event );
        void MenuCommand(wxCommandEvent & event);

};

#endif // ANIMATIONRESOURCE_H
