#ifndef PROJECTTREEVIEW_H
#define PROJECTTREEVIEW_H

#include "../Common/wx_windiw_ids.h"
#include "../Common/pshdefs.h"

#include <wx/textdlg.h>
#include <wx/menu.h>
#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include <wx/image.h>
#include "../Management/entityManager.h"
#include "../Window/propertyWindow.h"
#include "../Window/textEditor.h"
#include "../Dialogs/chooseScriptBox.h"
#include "../Dialogs/chooseAnimBox.h"
#include "../Management/animationManager.h"
#include "../Management/texMng.h"

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <utility>

typedef std::map<std::string, short> treeIDManager;
typedef std::map<std::string, wxTreeItemId> treeIDManagerItems;
typedef std::map<std::string, int> SceneIDManager;
enum{ MENU_ROOT=0,
      MENU_LVL,
      MENU_SCRIPT,
      MENU_SCRIPT_ITEM,
      MENU_ENTITY,
      MENU_FLDR,
      MENU_PROP,
      MENU_SCRIPT_VAR,
      MENU_SCRIPT_CHANGEVAR};

enum{ MENU_ENTITY_SCPT=0,
      MENU_LVL_ADDOBJ,
      MENU_ENTITY_ANIM,
      MENU_SCPT_VARS
        };

class entityManager;
class chooseScriptBox;
class textEditor;
class propertyWindow;

class projectTreeView : public wxTreeCtrl
{

    DECLARE_EVENT_TABLE()

    private:

    Entity * current_entity;
    Camera * global_camera;

    int active_project;
    int active_scene;

    wxMenu  * popup_menu;
    wxMenu  * popup_menu_sub;

    wxTreeItemId root;
    wxTreeItemId current;
    wxTreeItemId newly_created;

    treeIDManager      treeid_manager;      ///These 2 work side-by-side until I feel like using a struct
    treeIDManagerItems treeiditem_manager;  ///
    SceneIDManager     sceneID;


    std::vector<entityManager *> * scene_manager;
    wxImageList      * treeImages;
    propertyWindow   * property_window;
    scriptMng        * script_manager;
    textEditor       * text_editor;
    animationManager * animation_manager;
    texMng           * texture_manager;


    chooseScriptBox * scriptBox;

    public:

    projectTreeView(wxWindow * parent, wxWindowID id = wxID_ANY);
    ~projectTreeView();

    void LoadImgFrmPrjFile(char * fileLoc = NULL);
    void BindPropertyWindow( propertyWindow * property_window );
    void BindScriptManager(scriptMng * script_manager);
    void BindTextEditor(textEditor * text_editor);
    void BindAnimationManager( animationManager * animation_manager );
    void BindEntityManager(std::vector<entityManager*> * scene_manager);
    void BindTextureManager(texMng * texture_manager);
    void BindCamera(Camera * camera);


    void addItem_e(wxCommandEvent & event);
    wxTreeItemId addSubItem(std::string item_name_parent, std::string item_name_child, std::string tree_type = "", int icon_image=0);
    wxTreeItemId addSubItem(wxTreeItemId parent_item, std::string item_name, std::string tree_type = "", int icon_image=0);

    void delItem_e(wxCommandEvent & event);
    void delItem(std::string item_name);
    void delItem(std::string parent_item_name, std::string item_name);

    void changeName(std::string change_name_to);

    wxTreeItemId searchTree(std::string item_name);///Marked For Deprec
    wxTreeItemId searchTree(wxTreeItemId parent_item_name, std::string item_name);
    wxTreeItemId searchTreeConfine(wxTreeItemId parent_item_name, std::string item_name);
    wxTreeItemId retieveTreeItem(std::string item_name);


    Entity        * selectedEntity();
    entityManager * activeEntityManager();

                        ///Deletes All Scene Management and Tree Nodes
    void DeleteAll();

    void selection_change(wxTreeEvent &event);
    void key_command(wxTreeEvent &event);
    void on_right_click(wxTreeEvent & event);
    void otherEvents(wxCommandEvent & event);

    void activeScene(wxCommandEvent & event);
    void activeProject(wxCommandEvent & event); //Not in use yet

    void OnEnterWindow(wxMouseEvent& event);
    void OnLeaveWindow(wxMouseEvent& event);
    void OnIdle(wxIdleEvent & event);


    void printAllItemID();

    ////////////////
    ////////////////
    ////////////////
    std::vector<std::string> scenes_InTree;
    std::vector< std::vector< pair<std::string, std::string> > > entity_InScenesTree;

    entityManager * AddScene(std::string scene_name);
    Entity        * AddEntity(int sceneIndex, std::string entity_name, std::string type);
    Entity        * AddEntity(int sceneIndex, std::string type);

    bool AddScriptFromResource(std::string script_name);
    pScript *  AddScriptFromResource(std::string object_name, std::string script_name, int sceneindex);
    pScript *  AddScriptFromResource(Entity * object, std::string script_name, int sceneindex);

    void AddVarToScript(std::string type, std::string var_name="");
    void AddVarToScript2(std::string script_name0, std::string script_name1, std::string type, std::string var_name="");

    void SetRootName(wxString root_name = "New Project");


    int GetActiveScene();
};


#endif // PROJECTTREEVIEW_H
