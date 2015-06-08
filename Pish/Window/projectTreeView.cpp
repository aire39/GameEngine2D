#include <wx/msgdlg.h>
#include "../window/projectTreeView.h"

projectTreeView::projectTreeView(wxWindow * parent, wxWindowID id) : wxTreeCtrl(parent, id)
{
    ////////////////
    //Window Style//
    ////////////////

    SetWindowStyle( wxTR_HAS_BUTTONS | wxTR_NO_LINES | wxTR_EDIT_LABELS );

    ///////////////////////
    //Initilize Variables//
    ///////////////////////
    property_window = NULL;
    animation_manager = NULL;
    script_manager = NULL;
    text_editor = NULL;
    treeImages = NULL;

    active_scene = 0;
    active_project = 0;

    wxInitAllImageHandlers();
    treeImages = new wxImageList(16, 16);
    AssignImageList(treeImages);


    /////////////////////
    //Set Default Nodes//
    /////////////////////

    root = AddRoot(wxT("PSH Project"), 2, 2);
    current = root;
    SetItemBold(root);
    treeid_manager.insert(treeIDManager::value_type("PSH Project", MENU_ROOT));
    treeiditem_manager.insert(treeIDManagerItems::value_type("PSH Project", root));

    ///////////////////////
    //Setup Menu Contexts//
    ///////////////////////
    popup_menu = new wxMenu[9];
    popup_menu_sub = new wxMenu[6];

    popup_menu[MENU_ROOT].Append(PSH_TREE_ADDLVL, "Add Level");
    popup_menu[MENU_ROOT].Append(PSH_TREE_CLOSEPRJT, "Close Project");
    //popup_menu[MENU_ROOT].AppendSeparator();


    popup_menu_sub[MENU_LVL_ADDOBJ].Append(PSH_TREE_ADDEMPTY, "Add Empty");
    popup_menu_sub[MENU_LVL_ADDOBJ].Append(PSH_TREE_ADDSPRT , "Add Sprite");
    popup_menu_sub[MENU_LVL_ADDOBJ].Append(PSH_TREE_ADDTILE , "Add Tile");
    popup_menu_sub[MENU_LVL_ADDOBJ].Append(PSH_TREE_ADDTXT  , "Add Text");
    popup_menu_sub[MENU_LVL_ADDOBJ].Append(PSH_TREE_ADDMESH , "Add Mesh");
    popup_menu[MENU_LVL].AppendSubMenu(&popup_menu_sub[MENU_LVL_ADDOBJ], "Add Object");
    popup_menu[MENU_LVL].Append(PSH_TREE_ADDLVLSCPT, "Add Level Script"); //nothing yet
    popup_menu[MENU_LVL].Append(PSH_TREE_DELLVL, "Delete Lvl");
    popup_menu[MENU_LVL].AppendSeparator();
    popup_menu[MENU_LVL].Append(PSH_TREE_ADDFLDR, "Add Folder");
    popup_menu[MENU_LVL].Append(PSH_TREE_SCNACTIVE, "Activate Scene");
    popup_menu[MENU_LVL].Append(PSH_TREE_SCNSHOW, "Scene Show");
    popup_menu[MENU_LVL].Append(PSH_TREE_SCNHIDE, "Scene Hide");


    popup_menu_sub[MENU_ENTITY_SCPT].Append(PSH_TREE_NEWSCPT , "New Script");
    popup_menu_sub[MENU_ENTITY_SCPT].Append(PSH_TREE_RESCSCPT, "Script From Resource");
    popup_menu[MENU_ENTITY].AppendSubMenu(&popup_menu_sub[MENU_ENTITY_SCPT], "Add Script");
    popup_menu_sub[MENU_ENTITY_ANIM].Append(PSH_TREE_ADDANIM, "Add Animation"); //nothing yet
    popup_menu_sub[MENU_ENTITY_ANIM].Append(PSH_TREE_REMANIM, "Remove Animation"); //nothing yet
    popup_menu[MENU_ENTITY].AppendSubMenu(&popup_menu_sub[MENU_ENTITY_ANIM], "Animation");
    popup_menu[MENU_ENTITY].Append(PSH_TREE_PROENTITY, "Promote Entity"); //nothing yet
    popup_menu[MENU_ENTITY].Append(PSH_TREE_DELENTITY, "Delete  Entity");
    popup_menu[MENU_ENTITY].Append(PSH_TREE_DUPENTITY, "Duplicate  Entity");
    popup_menu[MENU_ENTITY].AppendSeparator();
    popup_menu[MENU_ENTITY].Append(PSH_TREE_ADDFLDR, "Add Folder");

    popup_menu[MENU_SCRIPT].Append(-1, "Run All Scripts"); //will be used to enable all scripts and stuff in one go
    popup_menu[MENU_SCRIPT].Append(-1, "Stop All Scripts"); //will be used to disable all scripts and stuff in one go

    popup_menu[MENU_SCRIPT_ITEM].Append(PSH_TREE_SCPT_VIEW, "View Script");
    popup_menu[MENU_SCRIPT_ITEM].Append(PSH_TREE_SCPT_STOP, "Stop Script");
    popup_menu[MENU_SCRIPT_ITEM].Append(PSH_TREE_SCPT_TRY, "Try Script");
    popup_menu[MENU_SCRIPT_ITEM].Append(PSH_TREE_SCPT_RUN, "Run Script");
    popup_menu[MENU_SCRIPT_ITEM].AppendSeparator();
    popup_menu_sub[MENU_SCPT_VARS].Append(PSH_TREE_SCPT_ADDVAR_TIMER , "Add Timer");
    popup_menu_sub[MENU_SCPT_VARS].Append(PSH_TREE_SCPT_ADDVAR_STRING , "Add String");
    popup_menu_sub[MENU_SCPT_VARS].Append(PSH_TREE_SCPT_ADDVAR_FLOAT , "Add Float");
    popup_menu_sub[MENU_SCPT_VARS].Append(PSH_TREE_SCPT_ADDVAR_BOOL , "Add Bool");
    popup_menu_sub[MENU_SCPT_VARS].Append(PSH_TREE_SCPT_ADDVAR_INT , "Add Int");
    popup_menu[MENU_SCRIPT_ITEM].AppendSubMenu(&popup_menu_sub[MENU_SCPT_VARS], "Add Variable");
    popup_menu[MENU_SCRIPT_ITEM].AppendSeparator();
    popup_menu[MENU_SCRIPT_ITEM].Append(PSH_TREE_SCPT_MOVEUP, "Move up");
    popup_menu[MENU_SCRIPT_ITEM].Append(PSH_TREE_SCPT_MOVEDOWN, "Move Down");
    popup_menu[MENU_SCRIPT_ITEM].AppendSeparator();
    popup_menu[MENU_SCRIPT_ITEM].Append(PSH_TREE_SCPT_REMOVE, "Remove Script");

    popup_menu[MENU_SCRIPT_CHANGEVAR].Append(PSH_TREE_SCPT_CHANGEVAR , "Change Variable");

    //popup_menu_sub[MENU_FLDR].Append(PSH_TREE_ADDEMPTY, "Add Entity");
    //popup_menu_sub[MENU_FLDR].Append(PSH_TREE_ADDSPRT, "Add Sprite");
    //popup_menu_sub[MENU_FLDR].Append(PSH_TREE_ADDTILE, "Add Tile");
    //popup_menu[MENU_FLDR].AppendSubMenu(&popup_menu_sub[MENU_LVL], "Add Object");

    /////////////////////////
    //Set Event Connections//
    /////////////////////////

    Connect(PSH_TREE_ADDLVL,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );


    Connect(PSH_TREE_DELENTITY,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::delItem_e) );

    Connect(PSH_TREE_ADDEMPTY,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );

    Connect(PSH_TREE_DUPENTITY,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );

    Connect(PSH_TREE_ADDSPRT,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );

    Connect(PSH_TREE_ADDTILE,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );

    Connect(PSH_TREE_ADDTXT,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );

    Connect(PSH_TREE_ADDMESH,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );

    Connect(PSH_TREE_NEWSCPT,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );

    Connect(PSH_TREE_RESCSCPT,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );

    Connect(PSH_TREE_SCPT_VIEW,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::otherEvents) );

    Connect(PSH_TREE_SCPT_CHANGEVAR,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::otherEvents) );

    Connect(PSH_TREE_SCPT_MOVEUP,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::otherEvents) );

    Connect(PSH_TREE_SCPT_MOVEDOWN,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::otherEvents) );

    Connect(PSH_TREE_SCPT_STOP,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::otherEvents) );

    Connect(PSH_TREE_SCPT_TRY,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::otherEvents) );

    Connect(PSH_TREE_SCPT_RUN,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::otherEvents) );

    Connect(PSH_TREE_SCPT_REMOVE,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::otherEvents) );

    Connect(PSH_TREE_SCPT_ADDVAR_TIMER, PSH_TREE_SCPT_ADDVAR_INT,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::otherEvents) );

    Connect(PSH_TREE_DELLVL,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::delItem_e) );

    Connect(PSH_TREE_ADDFLDR,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::addItem_e) );

    Connect(PSH_TREE_SCNACTIVE,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::activeScene) );
    Connect(PSH_TREE_SCNSHOW,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::activeScene) );

    Connect(PSH_TREE_SCNHIDE,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::activeScene) );

    Connect(PSH_TREE_ADDANIM,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::activeScene) );

    Connect(PSH_TREE_REMANIM,
            wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(projectTreeView::activeScene) );


    Refresh();

}


projectTreeView::~projectTreeView()
{
    delete scriptBox;

    scene_manager = NULL;
    //data_propviewer = NULL;
    this->ExpandAll();
    treeid_manager.clear();
    treeiditem_manager.clear();

    //if( popup_menu_sub != NULL )
    //    delete [] popup_menu_sub;

    //if( popup_menu != NULL )
    //    delete [] popup_menu; //Check

}


void projectTreeView::LoadImgFrmPrjFile(char * fileLoc)
{
    fstream file;
    string tmp;

    file.open("./testPrj.pshProj"/*filLoc goes here*/, ios::in);
    if(!file)
    {
        cout << "project file not found!" << endl;
        cout << "Continuing..." << endl;
        file.close();

    }
    else
    {
        cout << "project file found!" << endl;
        cout << "loading imagelist..." << endl;

        while(!file.eof())
        {
            file >> tmp;
            if(tmp == "@IMAGELIST")
                break;
        }

        while(!file.eof() )
        {
            file >> tmp;

            if(tmp != "@IMAGELIST_END")
            {
                wxImage img;
                img.LoadFile(tmp);

                if(img.IsOk())
                {
                    cout << tmp << endl;
                    img.Rescale(16, 16);

                    wxBitmap bitmap(img);

                    treeImages->Add(bitmap);
                }

            }
            else
                break;
        }

        file.close();
    }

}


void projectTreeView::BindPropertyWindow( propertyWindow * property_window )
{
    this->property_window = property_window;
}

void projectTreeView::BindEntityManager(std::vector<entityManager*> * scene_manager)
{
    this->scene_manager = scene_manager;
}

void projectTreeView::BindScriptManager(scriptMng * script_manager)
{
    this->script_manager = script_manager;
    scriptBox = new chooseScriptBox( this->script_manager );
}

void projectTreeView::BindTextEditor(textEditor * text_editor)
{
    this->text_editor = text_editor;
}

void projectTreeView::BindAnimationManager( animationManager * animation_manager )
{
    this->animation_manager = animation_manager;
}

void projectTreeView::BindTextureManager(texMng * texture_manager)
{
    this->texture_manager = texture_manager;
}

void projectTreeView::BindCamera(Camera * camera)
{
    this->global_camera = camera;
}

///////////////////
///////////////////
///////////////////
entityManager * projectTreeView::AddScene(std::string scene_name)
{
    active_scene = 0;
    current = root;
    wxTreeItemId tmpId;

    entityManager * new_manager = new entityManager();
    new_manager->SetSceneName( scene_name );

    new_manager->BindTextureManager( texture_manager );
    new_manager->BindScriptManager( script_manager );
    new_manager->BindTreeView(this);
    new_manager->BindCamera(global_camera);

    sceneID.insert(SceneIDManager::value_type(scene_name, sceneID.size()));
    scene_manager->push_back(new_manager);
    treeid_manager.insert(treeIDManager::value_type(scene_name, MENU_LVL));

    scenes_InTree.push_back(scene_name);

    std::vector< pair<std::string, std::string> > temp;
    entity_InScenesTree.push_back( temp );

        if(current.IsOk())
        {
            tmpId = this->AppendItem(current, scene_name, 3, 3, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(scene_name, tmpId));
        }

    current = tmpId;
    this->SelectItem(current, true);


    std::cout << "Active Scene:" << active_scene << std::endl;
    return new_manager;
}

Entity * projectTreeView::AddEntity(int sceneIndex, std::string type)
{
    Entity * entity = NULL;

    if( scene_manager != NULL )
    if( scene_manager->size() > 0 )
    {
        std::string entity_name = (std::string)wxGetTextFromUser("Enter Name:", "Adding Object");

        wxTreeItemId tmpId;
        wxTreeItemId csave_position = current;

        if(current.IsOk())
        {
            if( GetItemText(current).compare( (wxString)scenes_InTree[sceneIndex] ) == 0 );
            else
            {

                //current = searchTree(root, scenes_InTree[sceneIndex]); //search will cause a crash
                current = retieveTreeItem(scenes_InTree[sceneIndex]);
                SelectItem(current, true);
            }

            entity = scene_manager->at(sceneIndex)->addEntity(type, entity_name);

            tmpId = AppendItem(searchTreeConfine(current, entity->getName()), "Properties", 4, 4, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Properties", tmpId));
            treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Color", 9, 9, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Color", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Position", 5, 5, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Position", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Rotation", 6, 6, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Rotation", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Scale", 7, 7, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Scale", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Layer", 8, 8, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Layer", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            pair<std::string, std::string> _p(entity->getName(), type);
            entity_InScenesTree[sceneIndex].push_back( _p );

        }

        current = csave_position;
        SelectItem(csave_position);

    }


    return entity;
}

Entity * projectTreeView::AddEntity(int sceneIndex, std::string entity_name, std::string type)
{
    Entity * entity = NULL;

    if( scene_manager != NULL )
    if( scene_manager->size() > 0 )
    {
        wxTreeItemId tmpId;
        wxTreeItemId csave_position = current;

        if(current.IsOk())
        {
            if( GetItemText(current).compare( (wxString)scenes_InTree[sceneIndex] ) == 0 );
            else
            {
                //current = searchTree(root, scenes_InTree[sceneIndex]); //causes problems when trying to search
                current = retieveTreeItem(scenes_InTree[sceneIndex]);
                SelectItem(current, true);
            }

            entity = scene_manager->at(sceneIndex)->addEntity(type, entity_name);

            tmpId = AppendItem(searchTreeConfine(current, entity->getName()), "Properties", 4, 4, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Properties", tmpId));
            treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Color", 9, 9, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Color", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Position", 5, 5, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Position", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Rotation", 6, 6, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Rotation", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Scale", 7, 7, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Scale", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            tmpId = AppendItem(treeiditem_manager[entity->getName()+"Properties"], "Layer", 8, 8, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(entity->getName()+"Layer", tmpId));
            //treeid_manager.insert(treeIDManager::value_type(entity->getName()+"Properties", MENU_PROP));

            pair<std::string, std::string> _p(entity->getName(), type);
            entity_InScenesTree[sceneIndex].push_back( _p );

        }

        current = csave_position;
        SelectItem(csave_position);

    }


    return entity;
}

bool projectTreeView::AddScriptFromResource(std::string script_name)
{
    pScript * script = NULL;
    script = script_manager->getScript( script_name );

    if( script != NULL )
    {
        std::cout << "Found script!" << std::endl;
        //std::cout << script->getData() << std::endl;
        //scene_manager->at(0)->new_setscript(script);
        scene_manager->at(active_scene)->new_setscript( selectedEntity(), script );

        if( treeiditem_manager.find((std::string)GetItemText(GetSelection())+"Scripts") == treeiditem_manager.end() )
            addSubItem( GetSelection(), "Scripts", "scriptFldr", 0 );

        addSubItem( treeiditem_manager[(std::string)GetItemText(GetSelection())+"Scripts"], script->getName(), "script", 10 );

        if( treeid_manager[ (std::string)GetItemText( GetSelection() ) ] == MENU_ENTITY )
        {
            script->setBoundName( (std::string)GetItemText( GetSelection() ) );
            script_manager->reLinkScript( script->getName(), true ); ///true relinks while false delinks
        }

        return 1;
    }

    return 0;
}

pScript * projectTreeView::AddScriptFromResource(std::string object_name, std::string script_name, int sceneindex)
{
    pScript * script = NULL;
    script = script_manager->getScript( script_name );
    active_scene = sceneindex;

    if( script != NULL )
    {
        std::cout << "Found script!" << std::endl;
        //std::cout << script->getData() << std::endl;
        //scene_manager->at(0)->new_setscript(script);
        scene_manager->at(sceneindex)->new_setscript( selectedEntity(), script );

        SelectItem( retieveTreeItem(object_name), true );

        if( treeiditem_manager.find(object_name+"Scripts") == treeiditem_manager.end() )
            addSubItem( GetSelection(), "Scripts", "scriptFldr", 0 );

        addSubItem( treeiditem_manager[object_name+"Scripts"], script->getName(), "script", 10 );

        script->setBoundName( object_name );
        script_manager->reLinkScript( script->getName(), true ); ///true relinks while false delinks

        return script;
    }

    return 0;
}

pScript * projectTreeView::AddScriptFromResource(Entity * object, std::string script_name, int sceneindex)
{
    std::string object_name;
    pScript * script = NULL;
    script = script_manager->getScript( script_name );
    active_scene = sceneindex;

    if(object != NULL)
        object_name = object->getName();

    if( object != NULL )
    if( script != NULL )
    {
        std::cout << "Found script!" << std::endl;
        //std::cout << script->getData() << std::endl;
        //scene_manager->at(0)->new_setscript(script);
        scene_manager->at(sceneindex)->new_setscript( object, script );

        SelectItem( retieveTreeItem(object_name), true );

        if( treeiditem_manager.find(object_name+"Scripts") == treeiditem_manager.end() )
            addSubItem( GetSelection(), "Scripts", "scriptFldr", 0 );

        addSubItem( treeiditem_manager[object_name+"Scripts"], script->getName(), "script", 10 );

        script->setBoundName( object_name );
        script_manager->reLinkScript( script->getName(), true ); ///true relinks while false delinks

        return script;
    }

    return 0;
}

void projectTreeView::AddVarToScript(std::string type, std::string var_name)
{
    pScript * script = NULL;
    LayerData * layer_data = NULL;

    layer_data = scene_manager->at(active_scene)->GetObjectLayerData(current_entity);

    for(int i=0; i<(int)layer_data->scripts.size(); i++)
        if( GetItemText( current ).compare(layer_data->scripts[i]->getName() )==0 )
        {
            script = layer_data->scripts[i];
            break;
        }

    wxTreeItemId set_label_of_item;

    script->AddVar(type, var_name);
    set_label_of_item = addSubItem( current, type, "scriptvar",  0);

    SetItemText( set_label_of_item, script->GetNameOfVar(script->GetNumberOfVars(type)-1, type ) );
}

void projectTreeView::AddVarToScript2(std::string script_name0, std::string script_name1, std::string type, std::string var_name)
{
    pScript   * script = NULL;
    LayerData * layer_data = NULL;

    layer_data = scene_manager->at(active_scene)->GetObjectLayerData(current_entity);

    wxTreeItemId tmp_id = treeiditem_manager[script_name0];

    wxTreeItemIdValue cookie;
    tmp_id = GetFirstChild(tmp_id, cookie);

    for(int i=0; i<(int)layer_data->scripts.size(); i++)
    {
        if( GetItemText( tmp_id ).compare(script_name1)==0 )
        {
            script = layer_data->scripts[i];
            script->AddVar(type, var_name);
            wxTreeItemId set_label_of_item;
            set_label_of_item = addSubItem( tmp_id, type, "scriptvar",  0);

            SetItemText( set_label_of_item, var_name );
        }

        if( GetNextSibling(tmp_id).IsOk() )
            tmp_id = GetNextSibling(tmp_id);
    }



}

///////////////////
///////////////////

void projectTreeView::addItem_e(wxCommandEvent & event)
{
    wxTreeItemId tmpId;

    if( treeid_manager[(std::string)GetItemText(current)] == MENU_ROOT )
    {
        std::string item_name = (std::string)wxGetTextFromUser("Enter Level Name:", "Adding Level");
        if( !item_name.empty() )
            AddScene(item_name);
    }
    else if( treeid_manager[(std::string)GetItemText(current)] == MENU_LVL )
    {

        if(event.GetId() == PSH_TREE_ADDEMPTY)
        {
            AddEntity(active_scene, PSHEMPTY);
        }
        else if(event.GetId() == PSH_TREE_ADDSPRT)
        {
            AddEntity(active_scene, PSHSPRITE);
        }
        else if( event.GetId() == PSH_TREE_ADDTILE )
        {
            //std::cout << "*****TEST ADD TILE:PHASE I******" << std::endl;

            std::string item_name = (std::string)wxGetTextFromUser("Enter Tile Name:", "Adding Tile");
            //AddEntity(active_scene, item_name, PSHTILE); //Doesn't work for tile object

            if(current.IsOk())
            {
                scene_manager->at(active_scene)->addEntity(PSHTILE, item_name);
                //system("pause");
                //AppendItem(searchTreeConfine(current, item_name), "Properties", 0, 0, NULL);
                //AppendItem( GetSelection(), "Properties", 0, 0, NULL);
                //treeid_manager.insert(treeIDManager::value_type(item_name+"Properties", MENU_PROP));


                tmpId = AppendItem(GetSelection(), "Properties", 4, 4, NULL);
                treeiditem_manager.insert(treeIDManagerItems::value_type(item_name+"Properties", tmpId));
                treeid_manager.insert(treeIDManager::value_type(item_name+"Properties", MENU_PROP));

                tmpId = AppendItem(treeiditem_manager[item_name+"Properties"], "Color", 9, 9, NULL);
                treeiditem_manager.insert(treeIDManagerItems::value_type(item_name+"Color", tmpId));
                //treeid_manager.insert(treeIDManager::value_type(item_name+"Properties", MENU_PROP));

                tmpId = AppendItem(treeiditem_manager[item_name+"Properties"], "Position", 5, 5, NULL);
                treeiditem_manager.insert(treeIDManagerItems::value_type(item_name+"Position", tmpId));
                //treeid_manager.insert(treeIDManager::value_type(item_name+"Properties", MENU_PROP));

                tmpId = AppendItem(treeiditem_manager[item_name+"Properties"], "Rotation", 6, 6, NULL);
                treeiditem_manager.insert(treeIDManagerItems::value_type(item_name+"Rotation", tmpId));
                //treeid_manager.insert(treeIDManager::value_type(item_name+"Properties", MENU_PROP));

                tmpId = AppendItem(treeiditem_manager[item_name+"Properties"], "Scale", 7, 7, NULL);
                treeiditem_manager.insert(treeIDManagerItems::value_type(item_name+"Scale", tmpId));
                //treeid_manager.insert(treeIDManager::value_type(item_name+"Properties", MENU_PROP));

                tmpId = AppendItem(treeiditem_manager[item_name+"Properties"], "Layer", 8, 8, NULL);
                treeiditem_manager.insert(treeIDManagerItems::value_type(item_name+"Layer", tmpId));
                //treeid_manager.insert(treeIDManager::value_type(item_name+"Properties", MENU_PROP));

                pair<std::string, std::string> _p(item_name, PSHTILE);
                entity_InScenesTree[active_scene].push_back( _p );

            }

        }
        else if( event.GetId() == PSH_TREE_ADDTXT )
        {
            AddEntity(active_scene, PSHTEXT);
        }
        else if( event.GetId() == PSH_TREE_ADDMESH )
        {
            //wxMessageBox("Not Implemented Yet!", "Add Mesh");
            std::cout << "Add Mesh -> Not Implemented Yet!" << std::endl;
        }
        else if( event.GetId() == PSH_TREE_ADDFLDR )
        {

            std::string item_name = (std::string)wxGetTextFromUser("Enter Folder Name:", "Adding Folder");

            if(current.IsOk())
            {
                treeid_manager.insert(treeIDManager::value_type(item_name, MENU_LVL));
                AppendItem(current, item_name, 0, 0, NULL);
            }
        }

    }
    else if( treeid_manager[(std::string)GetItemText(current)] == MENU_ENTITY )
    {
        switch( event.GetId() )
        {
            case PSH_TREE_NEWSCPT:
            {
                std::cout << "Add New Script!" << std::endl;

                std::string script_name = (std::string)wxGetTextFromUser("Enter Script Name:", "Adding Script");
                pScript * script_hold = NULL;

                if( !script_name.empty() )
                {
                    script_hold = script_manager->addNewScript(script_name, (std::string)GetItemText(current));
                    scene_manager->at(active_scene)->new_setscript( selectedEntity(), script_hold );
                    //needs a condition to not add nother folder when there already is one
                    if( treeiditem_manager.find((std::string)GetItemText(GetSelection())+"Scripts") == treeiditem_manager.end() )
                        addSubItem( GetSelection(), "Scripts", "scriptFldr", 0 );

                    addSubItem( treeiditem_manager[(std::string)GetItemText(GetSelection())+"Scripts"], script_hold->getName(), "script", 10 );

                    //std::cout << "TTTSSSS: " << (std::string)GetItemText(GetSelection())+"Scripts" << std::endl;

                    if( selectedEntity() != NULL )
                    {
                        script_hold->setBoundName( selectedEntity()->getName() );
                        script_manager->reLinkScript( script_hold->getName(), true ); ///true relinks while false delinks
                    }

                    if( treeid_manager[ (std::string)GetItemText( GetSelection() ) ] == MENU_ENTITY )
                    {
                        script_hold->setBoundName( (std::string)GetItemText( GetSelection() ) );
                        script_manager->reLinkScript( script_hold->getName(), true ); ///true relinks while false delinks
                    }
                }




            }

            break;

            case PSH_TREE_RESCSCPT:
            {

                std::cout << "Load Script From Resource!" << std::endl;

                scriptBox->Centre();
                scriptBox->updateDialogInfo();
                scriptBox->showDialog();

                std::string script_name = scriptBox->getSelection();

                if( script_name.length() != 0)
                {
                    if( AddScriptFromResource(script_name) );
                    else
                        std::cout << "Can't find script!" << std::endl;
                }
                else
                    std::cout << "No selection was made!" << std::endl;

            }
            break;

            case PSH_TREE_DUPENTITY:
            {
                Entity * source_object = NULL;
                source_object = selectedEntity();

                if( typeid(*source_object) == typeid(Entity) )
                {
                    Entity * cpy_object = NULL;
                    cpy_object = AddEntity(active_scene, PSHEMPTY);
                    *cpy_object = *source_object;
                }
                else if( typeid(*source_object) == typeid(Sprite) )
                {
                    Sprite * cpy_object = NULL;
                    cpy_object = (Sprite*)AddEntity(active_scene, PSHSPRITE);
                    *cpy_object = *(Sprite*)source_object;
                }
                else if( typeid(*source_object) == typeid(Text) )
                {
                    Text * cpy_object = NULL;
                    cpy_object = (Text*)AddEntity(active_scene, PSHTEXT);
                    *cpy_object = *(Text*)source_object;
                }
            }

            break;

            default:
                event.Skip();
            break;
        }
    }
    else if( event.GetId() == PSH_TREE_ADDANIM )
    {
        std::cout << "Show Animation Resource" << std::endl;
    }

    Refresh();
    UpdateWindowUI();
}


wxTreeItemId projectTreeView::addSubItem(std::string item_name_parent, std::string item_name_child, std::string tree_type, int icon_image)
{
    wxTreeItemId dummy;

    if(tree_type.length() != 0)
    {
        if( tree_type.compare("entity") == 0)
            treeid_manager.insert(treeIDManager::value_type(item_name_child, MENU_ENTITY));
    }

    ///Has a limitation of finding the correct currently selected object [Needs to be fixed]
    if( searchTree(item_name_parent))
    {
        dummy = AppendItem(searchTree(item_name_parent), item_name_child, icon_image, icon_image, NULL);
        treeiditem_manager.insert(treeIDManagerItems::value_type(item_name_child, dummy));
        return dummy;
    }
    else
        std::cout << "\nprojectTreeView -> addSubItem: (Failed) Item Doesn't Exist!\n" << std::endl;

    return dummy;
}

wxTreeItemId projectTreeView::addSubItem(wxTreeItemId parent_item, std::string item_name_child, std::string tree_type, int icon_image)
{
    wxTreeItemId dummy;

    //std::cout << "\nADDING SUB: " << GetItemText(parent_item) << "\n" << std::endl;
    if(tree_type.length() != 0)
    {
        if( tree_type.compare("entity") == 0)
            treeid_manager.insert(treeIDManager::value_type(item_name_child, MENU_ENTITY));
        else if( tree_type.compare("scriptFldr") == 0)
            treeid_manager.insert(treeIDManager::value_type(item_name_child, MENU_SCRIPT));
        else if( tree_type.compare("script") == 0)
            treeid_manager.insert(treeIDManager::value_type(item_name_child, MENU_SCRIPT_ITEM));
        else if( tree_type.compare("scriptvar") == 0)
            treeid_manager.insert(treeIDManager::value_type(item_name_child, MENU_SCRIPT_VAR));

    }

    if( parent_item.IsOk() )
    {
        if( tree_type.compare("scriptFldr") == 0 )
        {
            dummy = AppendItem(parent_item, item_name_child, icon_image, icon_image, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type((std::string)GetItemText(parent_item)+item_name_child, dummy));
        }
        else if( tree_type.compare("script") == 0 )
        {
            dummy = AppendItem(parent_item, item_name_child, icon_image, icon_image, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type((std::string)GetItemText(parent_item)+item_name_child, dummy));
        }
        else if( tree_type.compare("scriptvar") == 0 )
        {
            dummy = AppendItem(parent_item, item_name_child, icon_image, icon_image, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type((std::string)GetItemText(parent_item)+item_name_child, dummy));
        }
        else
        {
            dummy = AppendItem(parent_item, item_name_child, icon_image, icon_image, NULL);
            treeiditem_manager.insert(treeIDManagerItems::value_type(item_name_child, dummy));
        }
        return dummy;
    }
    else
        std::cout << "\nprojectTreeView -> addSubItem: (Failed) Item Doesn't Exist!\n" << std::endl;

    return dummy;
}

void projectTreeView::delItem_e(wxCommandEvent& event)
{
    if( event.GetId() == PSH_TREE_DELLVL)
    {
        wxMessageDialog msgdlg(NULL,
                               "Are you sure you want to delete this scene?\n(No Undo Yet!)",
                               "Delete Scene",
                               wxYES_NO | wxICON_QUESTION);


        if( msgdlg.ShowModal() == wxID_YES )
        {

            if( GetItemParent(current) == root )
            {
                std::string scene_name = (std::string)GetItemText(current);
                this->Delete(current);
                current = root;

                std::vector<entityManager *>::iterator it;
                it =  scene_manager->begin()+active_scene;

                delete (*it);
                scene_manager->erase(it);

                std::vector<std::string>::iterator it2;
                it2 = scenes_InTree.begin();

                static int i=-1;
                for(; it2!=scenes_InTree.end(); it2++)
                {
                    i++;

                    if( it2->compare(scene_name) == 0 )
                    {
                        scenes_InTree.erase(it2);
                        entity_InScenesTree.erase( entity_InScenesTree.begin()+i );
                        break;
                    }

                }

            sceneID.erase( sceneID.find(scene_name) );

            if(scene_manager->size() > 0)
                active_scene = 0;
            else
                active_scene += -1;

            std::cout << "Active_Scene:" << active_scene << std::endl;


                /*
                if( HasChildren(current) )
                {
                    const int number_of_children = GetChildrenCount(current, false);
                    wxTreeItemIdValue cookie;

                    for(int i=0; i<number_of_children; i++)
                    {
                        wxTreeItemId child = this->GetFirstChild(current, cookie);
                        //std::cout << (std::string)GetItemText(child) << std::endl;
                        scene_manager->at(active_scene)->delEntity((std::string)GetItemText(child)); ///Cause of crash
                    }

                    delItem((std::string)GetItemText(current));
                    delete scene_manager->at(active_scene);
                    scene_manager->erase(scene_manager->begin()+active_scene);


                    current = GetFirstVisibleItem();
                    if( active_scene > 0)
                        active_scene -= 1;
                    else
                        active_scene = 0;

                    //printAllItemID();

                }
                else
                {
                    ///Somethin here crashes app.

                    wxTreeItemId obj_del;
                    obj_del = current;

                    delItem((std::string)GetItemText(current));
                    delete scene_manager->at(active_scene);

                    scene_manager->erase(scene_manager->begin()+active_scene);

                    Delete(obj_del);

                    current = this->GetFirstVisibleItem();

                    if( active_scene > 0)
                        active_scene -= 1;
                    else
                        active_scene = 0;

                    //printAllItemID();
                }
                */
            }
        }
        else if(event.GetId() == PSH_TREE_DELENTITY)
        {
            //std::cout << (std::string)GetItemText(current) << std::endl;
            scene_manager->at(active_scene)->delEntity((std::string)GetItemText(current));

        }
    }
}

void projectTreeView::delItem(std::string item_name)
{
    wxTreeItemId tmpID = treeiditem_manager[item_name];
/*
    if(current.IsOk())
    {
        //treeid_manager.erase(item_name);
        this->Delete(searchTree(GetItemParent(current), item_name));
    }
*/

    if(tmpID.IsOk())
    {
        treeid_manager.erase(item_name);
        treeiditem_manager.erase(item_name);
        this->Delete(tmpID);
    }
}

void projectTreeView::delItem(std::string parent_item_name, std::string item_name)
{

    printAllItemID();

    if( parent_item_name.compare(item_name) == 0 )
    {
        std::cout << parent_item_name << "  01 " << item_name << std::endl;

        treeiditem_manager.erase(item_name);

        std::cout << parent_item_name << "  02 " << item_name << std::endl;

        treeid_manager.erase(item_name);
        Delete(current);
    }
    else
    {

        if( treeid_manager[item_name] == MENU_ENTITY ) ///Think of a better way to do this automtically
        {
            treeiditem_manager.erase(item_name+"Properties");
            treeiditem_manager.erase(item_name+"Color");
            treeiditem_manager.erase(item_name+"Position");
            treeiditem_manager.erase(item_name+"Rotation");
            treeiditem_manager.erase(item_name+"Scale");
            treeiditem_manager.erase(item_name+"Layer");
        }

        //wxTreeItemId t_id = searchTree(parent_item_name);
        wxTreeItemId t_id = treeiditem_manager[parent_item_name];

        if(t_id.IsOk())
        {
            treeiditem_manager.erase(item_name);
            treeid_manager.erase(item_name);
            this->Delete(searchTree(t_id, item_name));
        }
        else
            std::cout << "\nprojectTreeView -> delItem: Failed - Tree item not found!\n" << std::endl;
    }

}

void projectTreeView::changeName(std::string change_name_to)
{
    Entity * entity;
    entity = this->selectedEntity();
    std::string prev_name;

    if( entity != NULL)
    {
        prev_name = entity->getName();
        //wxTreeItemId parent;

        //parent = GetItemParent( GetSelection() );
        //AppendItem(parent, change_name_to, 1, 1, NULL);

        this->SetItemText( GetSelection(), change_name_to);

        wxTreeItemId copy;

        copy = treeiditem_manager[prev_name+"Layer"];
        treeiditem_manager.insert( treeIDManagerItems::value_type(change_name_to+"Layer", copy));
        treeiditem_manager.erase(prev_name+"Layer");

        copy = treeiditem_manager[prev_name+"Scale"];
        treeiditem_manager.insert( treeIDManagerItems::value_type(change_name_to+"Scale", copy));
        treeiditem_manager.erase(prev_name+"Scale");

        copy = treeiditem_manager[prev_name+"Rotation"];
        treeiditem_manager.insert( treeIDManagerItems::value_type(change_name_to+"Rotation", copy));
        treeiditem_manager.erase(prev_name+"Rotation");

        copy = treeiditem_manager[prev_name+"Position"];
        treeiditem_manager.insert( treeIDManagerItems::value_type(change_name_to+"Position", copy));
        treeiditem_manager.erase(prev_name+"Position");

        copy = treeiditem_manager[prev_name+"Properties"];
        treeiditem_manager.insert( treeIDManagerItems::value_type(change_name_to+"Properties", copy));
        treeiditem_manager.erase(prev_name+"Properties");

        copy = treeiditem_manager[prev_name];
        treeiditem_manager.insert( treeIDManagerItems::value_type(change_name_to, copy));
        treeiditem_manager.erase(prev_name);

        scene_manager->at(active_scene)->changeEntityKey(prev_name, change_name_to);

    }
}

wxTreeItemId projectTreeView::searchTree(std::string item_name)
{
	wxTreeItemIdValue cookie;
	wxTreeItemId search;
	wxTreeItemId item = this->GetFirstChild( root, cookie );
	wxTreeItemId child;

	while( item.IsOk() )
	{
		wxString sData = this->GetItemText(item);
		if( item_name.compare(sData) == 0 )
		{
			return item;
		}
		if( this->ItemHasChildren( item ) )
		{
			wxTreeItemId search = searchTree( item_name );
			if( search.IsOk() )
			{
				return search;
			}
		}
		item = this->GetNextChild( root, cookie);
	}

	/* Not found */
	wxTreeItemId dummy;
	return dummy;

}

wxTreeItemId projectTreeView::searchTree(wxTreeItemId parent_item_name, std::string item_name)
{
	wxTreeItemIdValue cookie;
	wxTreeItemId search;
	wxTreeItemId item = this->GetFirstChild( parent_item_name, cookie );
	wxTreeItemId child;

	while( item.IsOk() )
	{
		wxString sData = this->GetItemText(item);
		if( item_name.compare(sData) == 0 )
		{
			return item;
		}
		if( this->ItemHasChildren( item ) )
		{
			wxTreeItemId search = searchTree( item_name );
			if( search.IsOk() )
			{
				return search;
			}
		}
		item = this->GetNextChild( parent_item_name, cookie);
	}

	/* Not found */
	wxTreeItemId dummy;
	return dummy;

}


wxTreeItemId projectTreeView::searchTreeConfine(wxTreeItemId parent_item_name, std::string item_name) ///special:new
{
	wxTreeItemIdValue cookie;
	wxTreeItemId search;
	wxTreeItemId item = this->GetFirstChild( parent_item_name, cookie );
	wxTreeItemId child;

	while( item.IsOk() )
	{
		wxString sData = this->GetItemText(item);
		if( item_name.compare(sData) == 0 )
		{
			return item;
		}

		item = this->GetNextChild( parent_item_name, cookie);
	}

	/* Not found */
	wxTreeItemId dummy;
	return dummy;

}

wxTreeItemId projectTreeView::retieveTreeItem(std::string item_name)
{
    wxTreeItemId retrieveID = 0;

    retrieveID = treeiditem_manager[item_name];
    if( retrieveID.IsOk() )
        return retrieveID;

    return retrieveID;
}


Entity * projectTreeView::selectedEntity()
{
    //std::cout << "Number of scenes: " << active_scene << std::endl;

    if( scene_manager->size() > 0 )
    {
        std::cout << "Number of scenes: " << scene_manager->size() << std::endl;
        const std::string selected = (std::string)GetItemText( GetSelection() );

        if(scene_manager->at(active_scene)->number_of_entitys() > 0)
        if( (scene_manager->at(active_scene)->searchEntity(selected) ) )
        {
            return scene_manager->at(active_scene)->getEntity(selected);
        }
    }

    return 0;
}

entityManager * projectTreeView::activeEntityManager()
{
    return scene_manager->at(active_scene);
}

void projectTreeView::DeleteAll()
{
    this->DeleteAllItems();
    for(int i=scene_manager->size()-1; i>=0; i--)
    {
            delete scene_manager->at(i);
            scene_manager->erase( scene_manager->begin()+i );
    }

    script_manager->RemoveAll();

    active_scene   = 0;
    active_project = 0;

    //current = root = AddRoot(wxT("New Project"), 2, 2);
    sceneID.clear();
    scenes_InTree.clear();
    entity_InScenesTree.clear();
    treeiditem_manager.clear();
    treeid_manager.clear();
    //addSubItem(root, "Scene", "", 3);
    Refresh();
}

void projectTreeView::SetRootName(wxString root_name)
{

    if(root == GetRootItem())
    {
        SetItemText(root, root_name);
        treeid_manager.insert(treeIDManager::value_type((std::string)root_name, MENU_ROOT));
        treeiditem_manager.insert(treeIDManagerItems::value_type((std::string)root_name, root));
    }

    else
    {
        current = root = AddRoot(root_name, 2, 2);
        treeid_manager.insert(treeIDManager::value_type((std::string)root_name, MENU_ROOT));
        treeiditem_manager.insert(treeIDManagerItems::value_type((std::string)root_name, root));
    }

}

/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////

void projectTreeView::selection_change(wxTreeEvent &event)
{
    std::string name;

    current = event.GetItem();

    if( sceneID.find((std::string)GetItemText(current)) != sceneID.end() )
        active_scene = sceneID[(std::string)GetItemText(current)];

    if( selectedEntity() != NULL )
    {
        property_window->EnterWindow((wxMouseEvent&)event);
        current_entity = selectedEntity();
    }

    std::cout << "Test For Selection! " << GetItemText(current) << "  " << active_scene << std::endl;

}

void projectTreeView::key_command(wxTreeEvent &event)
{
    switch(event.GetKeyCode())
    {
        case WXK_DELETE: //Delete Key Code
            std::cout << "Test For Deletion!" << std::endl;
            if(current.IsOk())
            {
                if( sceneID.find((std::string)GetItemText(current)) != sceneID.end() )
                {
                    entityManager * entity_manager = scene_manager->at(sceneID.find((std::string)GetItemText(current))->second);

                    scene_manager->erase( scene_manager->begin()+sceneID.find((std::string)GetItemText(current))->second);
                    delete entity_manager;
                    entity_manager = NULL;

                    Delete(current);
                    current = GetFirstVisibleItem();
                }

                if( scene_manager->at(active_scene)->searchEntity( (std::string)GetItemText(current) ) )
                    scene_manager->at(active_scene)->delEntity((std::string)GetItemText(current)); //delItem_e(event);//entity_manager->delEntity((std::string)GetItemText(current));

                if( GetItemText(GetItemParent(GetItemParent(current))) == "Scripts" )
                {
                    Entity * entity = NULL;
                    entity = scene_manager->at(active_scene)->getEntity( (std::string)GetItemText( GetItemParent(GetItemParent(GetItemParent(current)) )) );

                    LayerData * layer_data = scene_manager->at(active_scene)->GetObjectLayerData( entity );

                    if( layer_data != NULL )
                    {

                        //system("PAUSE");
                        pScript * script = NULL;

                        for(int i=0; i<(int)layer_data->scripts.size(); i++)
                            if( layer_data->scripts[i]->getName() ==  GetItemText(GetItemParent(current)))
                            {
                                script = layer_data->scripts[i];
                                break;
                            }

                        if( script != NULL )
                        {
                             wxString str = GetItemText( current );
                             //std::cout << "Current: " << str << std::endl;
                             //system("PAUSE");

                             if(str.Find("timer") != wxNOT_FOUND)
                             {
                                 //std::cout << "Timer Var Removed!" << std::endl;
                                 //system("PAUSE");

                                script->RemoveVar("timer", (std::string)str);
                                Delete(current);
                                current = GetFirstVisibleItem();
                             }
                             else if(str.Find("string") != wxNOT_FOUND)
                             {
                                script->RemoveVar("string", (std::string)str);
                                Delete(current);
                                current = GetFirstVisibleItem();
                             }
                             else if(str.Find("float") != wxNOT_FOUND)
                             {
                                script->RemoveVar("float", (std::string)str);
                                Delete(current);
                                current = GetFirstVisibleItem();
                             }
                             else if(str.Find("bool") != wxNOT_FOUND)
                             {
                                script->RemoveVar("bool", (std::string)str);
                                Delete(current);
                                current = GetFirstVisibleItem();
                             }
                             else if(str.Find("int") != wxNOT_FOUND)
                             {
                                script->RemoveVar("int", (std::string)str);
                                Delete(current);
                                current = GetFirstVisibleItem();
                             }
                        }



                    }

                }
            }

            break;

        default:
            break;
    }
}

void projectTreeView::on_right_click(wxTreeEvent & event)
{
    current = event.GetItem();
    this->SelectItem(current, true);

    int prev_active_scene = active_scene;

    ///Know which scene the object is actually in.
    wxTreeItemId tmpID;
    tmpID = GetItemParent( current );

    if( treeid_manager[ (std::string)GetItemText( GetSelection() ) ] == MENU_LVL )
    {
        tmpID = GetSelection(  );
        //if( GetItemText( tmpID ).compare( GetItemText( root ) ) == 0 )
        //    break;
    }
    //else

    if( treeid_manager[ (std::string)GetItemText( GetSelection() ) ] == MENU_ROOT )
    {
        tmpID = GetSelection(  );
        //if( GetItemText( tmpID ).compare( GetItemText( root ) ) == 0 )
        //    break;
    }


    if(treeid_manager[ (std::string)GetItemText( GetSelection() ) ] == MENU_LVL)
    active_scene = sceneID[ (std::string)GetItemText(tmpID) ];
    ///END

    if( sceneID.find((std::string)GetItemText(current)) != sceneID.end() )
        active_scene = sceneID[(std::string)GetItemText(current)];

    std::cout << "Test For Selection! " << GetItemText(current) << "  " << active_scene << std::endl;
    std::cout << "ROOT:" << GetItemText( tmpID ) << "  " << treeid_manager[ (std::string)GetItemText( GetSelection() ) ] << std::endl;

    //if( current.IsOk() )
    //    SelectItem(current, true);
    //Entity * type;


/*
    if(entity_manager->searchEntity( (std::string)GetItemText(current)))
    {
        type = entity_manager->getEntity( (std::string)GetItemText(current) );
        std::cout << typeid(*type).name() << std::endl;



        if( typeid(*type) == typeid(Entity))
        {
            this->PopupMenu(&popup_menu[MENU_ENTITY], event.GetPoint());
        }
        else if( typeid(*type) == typeid(Sprite))
        {
            this->PopupMenu(&popup_menu[MENU_ENTITY], event.GetPoint());
        }
        else if( typeid(*type) == typeid(Tile))
        {
            this->PopupMenu(&popup_menu[MENU_ENTITY], event.GetPoint());
        }

    }*/
    if( current.IsOk() )
    switch( treeid_manager[(std::string)GetItemText(current)] )
    {

        case MENU_ENTITY:
            this->PopupMenu(&popup_menu[MENU_ENTITY], event.GetPoint());
            break;

        case MENU_LVL:
            PopupMenu(&popup_menu[MENU_LVL], event.GetPoint());
            break;

        case MENU_FLDR:
            PopupMenu(&popup_menu[MENU_FLDR], event.GetPoint());
            break;

        case MENU_ROOT:
            this->PopupMenu(&popup_menu[MENU_ROOT], event.GetPoint());
            break;

        case MENU_PROP:
        {
            std::string p0;
            p0 = GetItemText( GetItemParent( GetSelection() ) );
            p0 += "Properties";
            break;
        }

        case MENU_SCRIPT:
        {
            std::string p0;
            p0 = GetItemText( GetItemParent( GetSelection() ) );
            p0 += GetItemText( GetSelection() );

            this->PopupMenu(&popup_menu[MENU_SCRIPT], event.GetPoint());

            break;
        }

        case MENU_SCRIPT_ITEM:
        {
            std::string p0;
            p0 = GetItemText( GetItemParent( GetSelection() ) );
            p0 += GetItemText( GetSelection() );

            this->PopupMenu(&popup_menu[MENU_SCRIPT_ITEM], event.GetPoint());
            break;
        }

        case MENU_SCRIPT_VAR:
        {
            std::string p0;
            p0 = GetItemText( GetItemParent( GetSelection() ) );
            p0 += GetItemText( GetSelection() );

            this->PopupMenu(&popup_menu[MENU_SCRIPT_CHANGEVAR], event.GetPoint());
            break;
        }

        default:
            event.Skip();
            break;
    }
    else
        std::cout << "\nRight-Click Unable To Find Connection!\n" << std::endl;

    std::cout << "Test For Right-Click! " << GetItemText(current) << std::endl;
    active_scene = prev_active_scene;
    std::cout << "Test For Selection! " << GetItemText(current) << "  " << active_scene << std::endl;
}

void projectTreeView::otherEvents(wxCommandEvent & event)
{
    switch( event.GetId() )
    {
        case PSH_TREE_SCPT_MOVEUP:
        {
            LayerData * layer_data = NULL;

            if( current_entity != NULL )
            {
                layer_data = scene_manager->at(active_scene)->GetObjectLayerData(current_entity);

                if( layer_data != NULL )
                    for(int i=0; i<(int)layer_data->scripts.size(); i++)
                    {
                        std::string str_cscript = "";
                        str_cscript = GetItemText( current );

                        if( str_cscript.compare(layer_data->scripts[i]->getName()) == 0 )
                            if( i > 0)
                            {

                                pScript * script = NULL;
                                script = layer_data->scripts[i];

                                layer_data->scripts[i]   = layer_data->scripts[i-1];
                                layer_data->scripts[i-1] = script;

                                std::string str_cid = (std::string)GetItemText(current);
                                std::string str_pid = (std::string)GetItemText(GetPrevSibling(current));

                                SetItemText(current, str_pid);
                                SetItemText(GetPrevSibling(current), str_cid);

                            }
                    }

            }
        }
        break;

        case PSH_TREE_SCPT_MOVEDOWN:
        {
            LayerData * layer_data = NULL;

            if( current_entity != NULL )
            {
                layer_data = scene_manager->at(active_scene)->GetObjectLayerData(current_entity);

                if( layer_data != NULL )
                    for(int i=0; i<(int)layer_data->scripts.size(); i++)
                    {
                        std::string str_cscript = "";
                        str_cscript = GetItemText( current );

                        if( str_cscript.compare(layer_data->scripts[i]->getName()) == 0 )
                            if( i < (int)layer_data->scripts.size()-1)
                            {

                                pScript * script = NULL;
                                script = layer_data->scripts[i];

                                layer_data->scripts[i]   = layer_data->scripts[i+1];
                                layer_data->scripts[i+1] = script;

                                std::string str_cid = (std::string)GetItemText(current);
                                std::string str_pid = (std::string)GetItemText(GetNextSibling(current));

                                SetItemText(current, str_pid);
                                SetItemText(GetNextSibling(current), str_cid);

                            }
                    }

            }
        }
        break;

        case PSH_TREE_SCPT_REMOVE:
        {
           LayerData * layer_data = NULL;

            if( current_entity != NULL )
            {
                layer_data = scene_manager->at(active_scene)->GetObjectLayerData(current_entity);
                std::cout << "1.Deleted Script/Item" << std::endl;

                if( layer_data != NULL )
                    for(int i=0; i<(int)layer_data->scripts.size(); i++)
                    {
                        std::string str_cscript = "";
                        str_cscript = GetItemText( current );
                        std::cout << "2.Deleted Script/Item" << std::endl;

                        if( str_cscript.compare(layer_data->scripts[i]->getName()) == 0 )
                        {
                            layer_data->scripts.erase( layer_data->scripts.begin()+i );
                            Delete(current);
                            current = GetFirstVisibleItem();
                            std::cout << "3.Deleted Script/Item" << std::endl;
                            break;
                        }
                    }

            }
        }
        break;
        case PSH_TREE_SCPT_VIEW:

            text_editor->unsetWorkingData();

            if( treeid_manager[ (std::string)GetItemText( GetSelection() ) ] == MENU_SCRIPT_ITEM )
            {
                pScript * script = NULL;

                std::string mstring = "";
                mstring = GetItemText( GetSelection() );

                text_editor->ClearTextEditor();
                //script = script_manager->getScript( mstring );
                for(int i=0; i<script_manager->get_number_of_scripts(); i++)
                    if(script_manager->GetScriptByIndex(i)->getName().compare(mstring) == 0)
                    {
                        script = script_manager->GetScriptByIndex(i);
                        break;
                    }

                if( script == NULL) //Object is most likely bounded so try again
                {
                    wxTreeItemId tmpID;
                    tmpID = GetItemParent( GetSelection() );

                    while( treeid_manager[ (std::string)GetItemText( tmpID ) ] != MENU_ENTITY )
                    {
                        tmpID = GetItemParent( tmpID );
                        if( GetItemText( tmpID ).compare( GetItemText( root ) ) == 0 )
                            break;
                    }


                    script = script_manager->getScript( (std::string)GetItemText( tmpID ) );
                }

                if( script != NULL )
                {
                    text_editor->ClearTextEditor();
                    text_editor->SetText(script->getData());
                    text_editor->setWorkingData(script);
                }
                else
                    std::cout << "Script has no data or wasn't found!" << std::endl;
            }
            else
                std::cout << "Script not found : Can't View!" << std::endl;

        break;

        case PSH_TREE_SCPT_STOP:
            if( treeid_manager[ (std::string)GetItemText( GetSelection() ) ] == MENU_SCRIPT_ITEM )
            {
                pScript * script = NULL;
                //script = script_manager->getScript( (std::string)GetItemText( GetSelection() ) );

                std::string mstring = "";
                mstring = GetItemText( GetSelection() );

                for(int i=0; i<script_manager->get_number_of_scripts(); i++)
                    if(script_manager->GetScriptByIndex(i)->getName().compare(mstring) == 0)
                    {
                        script = script_manager->GetScriptByIndex(i);
                        break;
                    }

                if( script == NULL) //Object is most likely bounded so try again
                {
                    wxTreeItemId tmpID;
                    tmpID = GetItemParent( GetSelection() );

                    while( treeid_manager[ (std::string)GetItemText( tmpID ) ] != MENU_ENTITY )
                    {
                        tmpID = GetItemParent( tmpID );
                        if( GetItemText( tmpID ).compare( GetItemText( root ) ) == 0 )
                            break;
                    }

                    script = script_manager->getScript( (std::string)GetItemText( tmpID ) );
                }

                if( script != NULL )
                    script->setMode(0);
                else
                    std::cout << "Script has no data or wasn't found!" << std::endl;
            }
            else
                std::cout << "Script not found : Can't Stop!" << std::endl;
        break;

        case PSH_TREE_SCPT_TRY:
            if( treeid_manager[ (std::string)GetItemText( GetSelection() ) ] == MENU_SCRIPT_ITEM )
            {
                pScript * script = NULL;
                //script = script_manager->getScript( (std::string)GetItemText( GetSelection() ) );

                std::string mstring = "";
                mstring = GetItemText( GetSelection() );

                for(int i=0; i<script_manager->get_number_of_scripts(); i++)
                    if(script_manager->GetScriptByIndex(i)->getName().compare(mstring) == 0)
                    {
                        script = script_manager->GetScriptByIndex(i);
                        break;
                    }

                if( script == NULL) //Object is most likely bounded so try again
                {
                    wxTreeItemId tmpID;
                    tmpID = GetItemParent( GetSelection() );

                    while( treeid_manager[ (std::string)GetItemText( tmpID ) ] != MENU_ENTITY )
                    {
                        tmpID = GetItemParent( tmpID );
                        if( GetItemText( tmpID ).compare( GetItemText( root ) ) == 0 )
                            break;
                    }

                    script = script_manager->getScript( (std::string)GetItemText( tmpID ) );
                }

                if( script != NULL )
                    script->setMode(1);
                else
                    std::cout << "Script has no data or wasn't found!" << std::endl;
            }
            else
                std::cout << "Script not found : Can't Try!" << std::endl;
        break;

        case PSH_TREE_SCPT_RUN:
            if( treeid_manager[ (std::string)GetItemText( GetSelection() ) ] == MENU_SCRIPT_ITEM )
            {
                pScript * script = NULL;
                script = script_manager->getScript( (std::string)GetItemText( GetSelection() ) );

                std::string mstring = "";
                mstring = GetItemText( GetSelection() );

                for(int i=0; i<script_manager->get_number_of_scripts(); i++)
                    if(script_manager->GetScriptByIndex(i)->getName().compare(mstring) == 0)
                    {
                        script = script_manager->GetScriptByIndex(i);
                        break;
                    }

                if( script == NULL) //Object is most likely bounded so try again
                {
                    wxTreeItemId tmpID;
                    tmpID = GetItemParent( GetSelection() );

                    while( treeid_manager[ (std::string)GetItemText( tmpID ) ] != MENU_ENTITY )
                    {
                        tmpID = GetItemParent( tmpID );
                        if( GetItemText( tmpID ).compare( GetItemText( root ) ) == 0 )
                            break;
                    }

                    script = script_manager->getScript( (std::string)GetItemText( tmpID ) );
                }

                if( script != NULL )
                    script->setMode(2);
                else
                    std::cout << "Script has no data or wasn't found!" << std::endl;
            }
            else
                std::cout << "Script not found : Can't Run!" << std::endl;
        break;

        case PSH_TREE_SCPT_ADDVAR_TIMER:
        {
            AddVarToScript("timer");
        }
        break;

        case PSH_TREE_SCPT_ADDVAR_STRING:
        {
            AddVarToScript("string");
        }
        break;

        case PSH_TREE_SCPT_ADDVAR_FLOAT:
        {
            AddVarToScript("float");
        }
        break;

        case PSH_TREE_SCPT_ADDVAR_BOOL:
        {
            AddVarToScript("bool");
        }
        break;

        case PSH_TREE_SCPT_ADDVAR_INT:
        {
            AddVarToScript("int");
        }
        break;

        case PSH_TREE_SCPT_CHANGEVAR:
        {
                Entity * entity = NULL;
                entity = scene_manager->at(active_scene)->getEntity( (std::string)GetItemText( GetItemParent(GetItemParent(GetItemParent(current)) )) );

                LayerData * layer_data = scene_manager->at(active_scene)->GetObjectLayerData( entity );

                if( layer_data != NULL )
                {

                    pScript * script = NULL;

                    for(int i=0; i<(int)layer_data->scripts.size(); i++)
                        if( layer_data->scripts[i]->getName() ==  GetItemText(GetItemParent(current)))
                        {
                            script = layer_data->scripts[i];
                            break;
                        }

                    if( script != NULL )
                    {
                        if ( GetItemText(current).Find("string") != wxNOT_FOUND )
                        {
                            wxString str = script->GetVarStr( GetItemText(current).c_str() );
                            wxString value = (std::string)wxGetTextFromUser("Enter Value:", "Changing String", str);

                            script->SetVarStr( (const char*) GetItemText(current).c_str(), (std::string)value);
                        }
                        else if ( GetItemText(current).Find("float") != wxNOT_FOUND )
                        {
                            float mfloat = script->GetVarFloat( GetItemText(current).c_str() );
                            wxString value = (std::string)wxGetTextFromUser("Enter Value:", "Changing Float", convertDouble(mfloat));

                            script->SetVarFloat( (const char*) GetItemText(current).c_str(), atof(value.c_str()));
                        }
                        else if ( GetItemText(current).Find("bool") != wxNOT_FOUND )
                        {
                            bool mbool = script->GetVarBool( GetItemText(current).c_str() );
                            wxString value = (std::string)wxGetTextFromUser("Enter Value:", "Changing Bool", convertDouble(mbool));

                            script->SetVarBool( (const char*) GetItemText(current).c_str(), atoi(value.c_str()));
                        }
                        else if ( GetItemText(current).Find("int") != wxNOT_FOUND )
                        {
                            int mint = script->GetVarInt( GetItemText(current).c_str() );
                            wxString value = (std::string)wxGetTextFromUser("Enter Value:", "Changing Integer", convertDouble(mint));

                            script->SetVarInt( (const char*) GetItemText(current).c_str(), atoi(value.c_str()));
                        }

                    }
                }

        }
        break;

        default:
            event.Skip();
        break;
    }
}

void projectTreeView::OnEnterWindow(wxMouseEvent& WXUNUSED(event))
{
    std::cout << "Entering project tree view!\n" << std::endl;
    Refresh();
    SetFocus();
    Update();
    //SetCurrent(); //I think this hands over controls for this context
}

void projectTreeView::OnLeaveWindow(wxMouseEvent& WXUNUSED(event))
{
    std::cout << "Leaving project tree view!\n" << std::endl;
}


void projectTreeView::activeScene(wxCommandEvent & event)
{
    switch(event.GetId())
    {
        case PSH_TREE_SCNACTIVE:
            active_scene = sceneID[ (std::string)GetItemText(current) ];
            std::cout << "Current Active Scene: " << active_scene << std::endl;
        break;

        case PSH_TREE_SCNSHOW:
            scene_manager->at(active_scene)->renderActive();
            std::cout << "Current Active Scene: " << active_scene << std::endl;
        break;

        case PSH_TREE_SCNHIDE:
            scene_manager->at(active_scene)->renderDeactive();
            std::cout << "Current Active Scene: " << active_scene << std::endl;
        break;

        default:
            std::cout << "No Matching Signal!" << std::endl;
            event.Skip();
        break;
    }
}


void projectTreeView::printAllItemID()
{
    treeIDManagerItems::iterator it = treeiditem_manager.begin();
    for(; it!=treeiditem_manager.end(); ++it)
    {
        std::cout << it->first << std::endl;
    }
}

int projectTreeView::GetActiveScene()
{
    return active_scene;
}

void projectTreeView::OnIdle(wxIdleEvent & event)
{
    wxMouseEvent pevent(wxEVT_MOTION);
    AddPendingEvent(pevent);

    event.RequestMore();
    event.Skip();
}

BEGIN_EVENT_TABLE(projectTreeView, wxTreeCtrl)
    EVT_TREE_SEL_CHANGED(PSH_TREEVIEW_ID, projectTreeView::selection_change)
    EVT_TREE_KEY_DOWN(PSH_TREEVIEW_ID, projectTreeView::key_command)
    EVT_TREE_ITEM_RIGHT_CLICK(PSH_TREEVIEW_ID, projectTreeView::on_right_click)
    EVT_ENTER_WINDOW( projectTreeView::OnEnterWindow )
    EVT_LEAVE_WINDOW( projectTreeView::OnLeaveWindow )
    //EVT_IDLE(projectTreeView::OnIdle)
END_EVENT_TABLE()

