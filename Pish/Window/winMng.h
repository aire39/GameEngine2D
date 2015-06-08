#ifndef WINMNG_H
#define WINMNG_H

#include "../Common/GLee.h"

#include <wx/menu.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/dockart.h>
#include <wx/filedlg.h>
#include <wx/notebook.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/log.h>
#include <wx/glcanvas.h>


#include "../Common/pshsignals.h"
#include "../Common/wx_windiw_ids.h"
#include "../IO/ProjectFile.h"
#include "../IO/UIFile.h"
#include "../Window/textEditor.h"
#include "../Window/OGLWin.h"
#include "../Window/textureResource.h"
#include "../Window/resourceWindow.h"
#include "../Window/projectTreeView.h"
#include "../Window/toolBar.h"
#include "../Management/texMng.h"
#include "../Management/scriptMng.h"
#include "../Management/entityManager.h"
#include "../Management/animationManager.h"
#include "../Window/animationResource.h"
#include "../PyFunc/pshEngine.h"
#include "../Window/propertyWindow.h"
#include "../Wizards/NewProjectWiz.h"
#include "../Dialogs/prefdialog.h"


#include <boost/python.hpp>
using namespace boost::python;
typedef std::vector<entityManager *> SceneManager;

class winMng : public wxFrame
{
    DECLARE_EVENT_TABLE()

    private:
        //bool AppMod;
        bool AppMod;
        wxGLContext * opengl_context;

        string projectPath;
        pshEngine * py_pshengine;

        //UI UIname;    this will be the main thing controlling inputs of contexts UI(OGLWin *, TWin *) TWin is supposed to be text based
        //windows.

        wxAuiManager   window_manager;
        wxAuiDockArt * dockArt;

        //----------------------------------------
        //Systems/Managers

        texMng           * texture_manager;
        animationManager * anim_manager;
        wxFileDialog     * fileDialog;

        //----------------------------------------
        //Window Types

        OGLWin   * win;
        toolBar  * toolbar;
        ToolBarScene * toolbar_scene;


        animationResource * anim_resource_window;
        textureResource   * texture_resource_window;
        resourceWindow    * resource_window;
        propertyWindow    * property_window;
        projectTreeView   * tree_view;
        textEditor        * text_editor;
        scriptMng         * scriptMan;

        SceneManager  * scene_manager;
        ProjectFile   * project_document;
        NewProjectWiz * npwiz;
        prefDialog      pref_dialog;

        void ClearData();

    public:

        winMng(wxFrame *frame, const wxString& title);
        ~winMng();

        void InitPSH();

        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        void viewScene(wxCommandEvent& event);
        void viewImageExp(wxCommandEvent& event);
        void viewProjTree(wxCommandEvent& event);
        void viewProp(wxCommandEvent& event);
        void viewAnim(wxCommandEvent& event);
        void viewText(wxCommandEvent& event);

        void fileOpen(wxCommandEvent& event);

        //void OnSize(wxSizeEvent& event);    //To Make Manager Update while resizing so that Pane stays consistent
        //void OnIdle(wxIdleEvent& event);    //Might Need It.
        void OnEnterWindow(wxMouseEvent & event);
        void OnLeaveWindow(wxMouseEvent & event);

};



#endif
