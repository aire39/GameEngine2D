#include "../Management/entityManager.h"

entityManager::entityManager()
{
    renderable = true;
    scene_name = "Scene";
    global_camera = NULL;
}

entityManager::entityManager(const entityManager & entity_manager)
{
}

entityManager::~entityManager()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting entityManager!" << std::endl;
    #endif

    //delete layer_manager;
    //layer_manager = NULL;

    tree_view = NULL;

    if( object_manager.size() != 0)
    for(objectManager::iterator it = object_manager.begin(); it != object_manager.end(); ++it)
    {
        if( script_manager->get_number_of_scripts() != 0)
            if( script_manager->searchScript(it->first) )
                unbindObjectToScript(it->first);
        //tree_view->SelectItem(search)
        //tree_view->delItem(it->first);
        delete it->second;
    }
    object_manager.clear();
    pick_manager.clear();

    script_manager = NULL;
}

void entityManager::BindTreeView(projectTreeView * tree_view)
{
    this->tree_view = tree_view;
}

void entityManager::BindTextureManager( texMng * texture_manager )
{
    this->texture_manager = texture_manager;
}

void entityManager::BindScriptManager(scriptMng * script_manager)
{
    this->script_manager = script_manager;
    this->layer_manager.BindScriptManager( this->script_manager );
}

void entityManager::BindCamera(Camera * camera)
{
    this->global_camera = camera;
}

void entityManager::bindObjectToScript(std::string object_name, std::string script_name)
{

    if( searchEntity(object_name) )
    {
        if( script_manager->searchScript(script_name) )
        {
            script_manager->getScript(script_name)->setBoundName(object_name);
            script_manager->reLinkScript(script_name);
        }
        else
            std::cout << "\nEntityManager -> bindObjectToScript: Script Not Found!\n--Binding Failed!\n" << std::endl;
    }
    else
        std::cout << "\nEntityManager -> bindObjectToScript: Object Not Found!\n--Binding Failed!\n" << std::endl;
}

void entityManager::unbindObjectToScript(std::string object_name)
{

    if( searchEntity(object_name) )
    {
        //std::cout << "\nT1:" << script_manager->getScript(object_name)->getName() << " " << script_manager->getScript(object_name)->getBoundName() << "\n" << std::endl;
        script_manager->reLinkScript(script_manager->getScript(object_name)->getBoundName(), false);
    }
    else
        std::cout << "\nEntityManager -> bindObjectToScript: Object Not Found!\n--UnBinding Failed!\n" << std::endl;
}

void entityManager::SetSceneName(std::string scene_name)
{
    this->scene_name = scene_name;
}

std::string entityManager::SceneName()
{
    return scene_name;
}

void entityManager::renderActive()
{
    renderable = true;
}

void entityManager::renderDeactive()
{
    renderable = false;
}

void entityManager::renderEnabled(bool renderable)
{
    this->renderable = renderable;
}

bool entityManager::IsRendering()
{
    return renderable;
}

void entityManager::new_setscript(Entity * object, pScript * _script)
{
    if( _script != NULL )
        layer_manager.InitLayerScript( object, _script);
}

LayerData * entityManager::GetObjectLayerData(Entity * entity)
{
    return layer_manager.GetObjectLayerData(entity);
}

void entityManager::Render()
{
    if( renderable )
        layer_manager.Render();
}

void entityManager::Render_Raw()
{
    if(renderable)
        layer_manager.RenderRaw();
}

void entityManager::pickRender()
{
    if(renderable)
        layer_manager.RenderID();
}

void entityManager::addEntity(Entity * obj)
{
    std::string name_check = obj->getName();
    std::string object_name = obj->getName();
    int i=0;
    char buf[10];

    if( obj == NULL )
    {
        std::cout << "No Data In Object!" << std::endl;
    }
    else if( typeid(*obj) == typeid(Entity) )
    {
        ////////////////////////////////////////
        //Check to see if object already exist//
        ////////////////////////////////////////

        if( name_check.empty() )
        {
            name_check = "empty";

            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = "empty_";
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            obj->setName(name_check);
        }
        else
        {
            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = object_name;
                name_check.append("_");
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            obj->setName(name_check);
        }



        ////////////////////
        ////////////////////
        ////////////////////

        obj->setPosition( -global_camera->getPos2D()/10.0f );

        object_manager.insert( objectManager::value_type(obj->getName(), obj));
        object_managerv.push_back(obj);

        LayerData * layerdatainsert = new LayerData;
        layerdatainsert->entity = obj;
        layerdatainsert->script = NULL;
        layer_manager.Insert( layerdatainsert );
    }
    else if( typeid(*obj) == typeid(Sprite) )
    {
        ////////////////////////////////////////
        //Check to see if object already exist//
        ////////////////////////////////////////

        if( name_check.empty() )
        {
            name_check = "sprite";

            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = "sprite_";
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            obj->setName(name_check);
        }
        else
        {
            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = object_name;
                name_check.append("_");
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            obj->setName(name_check);
        }



        ////////////////////
        ////////////////////
        ////////////////////

        Sprite * sprite = NULL;

        sprite = (Sprite*)obj;

        sprite->setPosition( -global_camera->getPos2D()/10.0f );

        object_manager.insert( objectManager::value_type(sprite->getName(), sprite));
        object_managerv.push_back(sprite);

        LayerData * layerdatainsert = new LayerData;
        layerdatainsert->entity = sprite;
        layerdatainsert->script = NULL;
        layer_manager.Insert( layerdatainsert );
    }
    else if( typeid(*obj) == typeid(Text) )
    {
        ////////////////////////////////////////
        //Check to see if object already exist//
        ////////////////////////////////////////

        if( name_check.empty() )
        {
            name_check = "text";

            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = "text_";
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            obj->setName(name_check);
        }
        else
        {
            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = object_name;
                name_check.append("_");
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            obj->setName(name_check);
        }



        ////////////////////
        ////////////////////
        ////////////////////

        Text * text = NULL;

        text = (Text*)obj;

        text->setPosition( -global_camera->getPos2D()/10.0f );

        object_manager.insert( objectManager::value_type(text->getName(), text));
        object_managerv.push_back(text);

        LayerData * layerdatainsert = new LayerData;
        layerdatainsert->entity = text;
        layerdatainsert->script = NULL;
        layer_manager.Insert( layerdatainsert );
    }
    else if( typeid(*obj) == typeid(Tile) )
    {
        std::cout << "Needs To Go Under Reconstruction" << std::endl;
    }
    else if( typeid(*obj) == typeid(Mesh) )
    {
        std::cout << "Still Needs To Be Implemented Completely" << std::endl;
    }
    else
    {
        std::cout << "Can't Accept Object Type!" << std::endl;
    }

}

Entity * entityManager::addEntity(std::string type, std::string object_name)
{
    convert_string_tolower(type); //Use boost later for this
    std::string name_check = object_name;
    int i=0;
    char buf[10];
    Entity * _addedentity = NULL;

    if(type.compare(PSHEMPTY) == 0 )
    {

        ////////////////////////////////////////
        //Check to see if object already exist//
        ////////////////////////////////////////



        ////////////////////
        ////////////////////
        ////////////////////

        Entity * empty = new Entity();
        empty->init();

            if( object_name.empty())
            {
                object_name = "empty";
                name_check = object_name;

                while(object_manager.find(name_check) != object_manager.end())
                {
                    name_check.clear();
                    name_check = "empty_";
                    i++;
                    itoa(i, buf, 10);
                    name_check.append(buf);
                }

                empty->setName(name_check);
            }
            else
            {
                while(object_manager.find(name_check) != object_manager.end())
                {
                    name_check.clear();
                    name_check = object_name;
                    name_check.append("_");
                    i++;
                    itoa(i, buf, 10);
                    name_check.append(buf);
                }

                empty->setName(object_name);
            }

        empty->setPosition( -global_camera->getPos2D()/10.0f );

        tree_view->addSubItem(tree_view->GetSelection(), empty->getName(), "entity", 1);
        object_manager.insert( objectManager::value_type(empty->getName(), empty) );
        pick_manager.insert(objectColorIDManager::value_type(empty->getColorID(), empty->getName()));

        object_managerv.push_back( empty );

        LayerData * layerdatainsert = new LayerData;
        layerdatainsert->entity = empty;
        layerdatainsert->script = NULL;
        layer_manager.Insert( layerdatainsert );

        _addedentity = empty;

    }
    else if(type.compare(PSHSPRITE) == 0)
    {

        Sprite * sprite = new Sprite();
        sprite->init();
        sprite->initTextureManage( texture_manager );

        if( object_name.empty())
        {
            object_name = "sprite";
            name_check = object_name;

            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = "sprite_";
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            sprite->setName(name_check);
        }
        else
        {

            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = object_name;
                name_check.append("_");
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            sprite->setName(name_check);
        }

        sprite->setPosition( -global_camera->getPos2D()/10.0f );

        tree_view->addSubItem(tree_view->GetSelection(), sprite->getName(), "entity", 1);
        object_manager.insert( objectManager::value_type(sprite->getName(), sprite) );
        pick_manager.insert(objectColorIDManager::value_type(sprite->getColorID(), sprite->getName()));


        object_managerv.push_back( sprite );


        LayerData * layerdatainsert = new LayerData;
        layerdatainsert->entity = sprite;
        layerdatainsert->script = NULL;
        layer_manager.Insert( layerdatainsert );

        _addedentity = sprite;

    }
    else if(type.compare(PSHTILE) == 0)
    {

        Tile * tile = new Tile();
        tile->BindTileToTreeView(tree_view);


        if( object_name.empty())
        {
            object_name = "tile";
            name_check = object_name;

            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = "tile_";
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            tile->setName(name_check);
        }
        else
        {
            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = object_name;
                name_check.append("_");
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            tile->setName(object_name);
        }

        tile->setPosition( -global_camera->getPos2D()/10.0f );

        ///Needs access to script manager also or it crashes.
        //tree_view->addSubItem((std::string)tree_view->GetItemText(tree_view->GetSelection()), tile->getName(), "entity");
        tree_view->addSubItem(tree_view->GetSelection(), tile->getName(), "entity", 1);
        //tree_view->addItem(tile->getName());
        object_manager.insert( objectManager::value_type(tile->getName(), tile) );
        tile->init(this->script_manager);
        //std::cout << (int)tile->getColorID()[0] << " " << (int)tile->getColorID()[1] << " " << (int)tile->getColorID()[2] << std::endl;
        pick_manager.insert(objectColorIDManager::value_type(tile->getColorID(), tile->getName()));

        object_managerv.push_back( tile );

        LayerData * layerdatainsert = new LayerData;
        layerdatainsert->entity = tile;
        layerdatainsert->script = NULL;
        layer_manager.Insert( layerdatainsert );

        _addedentity = tile;

    }
    else if(type.compare(PSHTEXT) == 0)
    {
        Text * text = new Text("Text");

        if( object_name.empty())
        {
            object_name = "text";
            name_check = object_name;

            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = "text_";
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            text->setName(name_check);
        }
        else
        {
            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = object_name;
                name_check.append("_");
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            text->setName(object_name);
        }

        text->setPosition( -global_camera->getPos2D()/10.0f );

        tree_view->addSubItem(tree_view->GetSelection(), text->getName(), "entity", 1);
        //tree_view->addItem(sprite->getName());
        object_manager.insert( objectManager::value_type(text->getName(), text) );

        //std::cout << (int)sprite->getColorID()[0] << std::endl;
        pick_manager.insert(objectColorIDManager::value_type(text->getColorID(), text->getName()));

        object_managerv.push_back( text );

        LayerData * layerdatainsert = new LayerData;
        layerdatainsert->entity = text;
        layerdatainsert->script = NULL;
        layer_manager.Insert( layerdatainsert );

        _addedentity = text;
    }
    else if(type.compare(PSHMESH) == 0)
    {
        std::cout << "Not Implemented Yet!" << std::endl;
    }
    else
        std::cout << "\nentityManager -> addEntity: Type Not Found!\n" << std::endl;

    return _addedentity;
}

void entityManager::delEntity(Entity * obj)
{
    if(obj != NULL)
    {
        objectManager::iterator it = object_manager.begin();
        it = object_manager.find(obj->getName());

        if( script_manager->searchScript(it->first) )
            unbindObjectToScript(it->first);

        //tree_view->delItem(it->first);

        layer_manager.RemoveObject(obj);
        delete it->second;
        it->second = NULL;
        object_manager.erase(it);
    }
    else
        std::cout << "\nentityManager -> delEntity: Object Not Found!\n" << std::endl;
}

void entityManager::delEntity(std::string object_name)
{
    objectManager::iterator it = object_manager.find(object_name);

    if(it != object_manager.end())
    {
        if( script_manager->get_number_of_scripts() != 0)
            if( script_manager->searchScript(it->first) )
                unbindObjectToScript(it->first);

        //std::cout << "Currently Selected: " << (std::string)tree_view->GetItemText(tree_view->GetSelection()) << "  " << object_name << std::endl;
        //Deletes objects ColorID that way the name is released.
        //Doone by iterating straigtht throughe look for a better method later.
        objectColorIDManager::iterator it_colID = pick_manager.begin();
        for(; it_colID!=pick_manager.end(); ++it_colID)
            if( it_colID->second == object_name)
            {
                pick_manager.erase(it_colID);
                break;
            }

        layer_manager.RemoveObject(it->second);
        delete it->second;
        tree_view->delItem((std::string)tree_view->GetItemText(tree_view->GetSelection()), object_name);
        //std::cout << "PROPOROORO 3" << std::endl;

        it->second = NULL;
        object_manager.erase(it);
    }
    else
        std::cout << "\nentityManager -> delEntity: Object Not Found!\n" << std::endl;
}

void entityManager::changeEntityKey(std::string entity_name, std::string entity_key_change)
{
    Entity * entity;

    entity = object_manager[entity_name];
    entity->setName(entity_key_change);
    object_manager.insert(objectManager::value_type(entity->getName(), entity));
    object_manager.erase(entity_name);
}

int entityManager::number_of_entitys()
{
    return object_manager.size();
}

bool entityManager::searchEntity(std::string object_name)
{
    bool found = false;

    if( object_manager.find(object_name) != object_manager.end() )
        found = true;

    return found;

}

Entity * entityManager::getEntity(std::string object_name)
{
    Entity * e_tmp = NULL;

    objectManager::iterator it = object_manager.find(object_name);

    if(it != object_manager.end())
    {
        e_tmp = it->second;
    }
    else
    {
        e_tmp = NULL;
        std::cout << "\nentityManager -> getEntity: Entity Was Not Found!\n" << std::endl;
    }

    return e_tmp;
}

Entity * entityManager::getEntity(unsigned char * colorID)
{
    Entity * e_tmp = NULL;

    ///Wasn't trying to do it this way buy map::find won't do what I need it to. Need to look for workaround.
    objectColorIDManager::iterator it_colID = pick_manager.begin();
    for(; it_colID!=pick_manager.end(); ++it_colID)
        if(it_colID->first[0] == colorID[0] && it_colID->first[1] == colorID[1] && it_colID->first[2] == colorID[2])
            break;


    //if( it_colID != pick_manager.end())
    //    std::cout << it_colID->second << std::endl;

    if(it_colID != pick_manager.end())
    {

        objectManager::iterator it = object_manager.find(it_colID->second);

        if(it != object_manager.end())
        {
            tree_view->SelectItem( tree_view->retieveTreeItem(it->first), true );
            e_tmp = it->second;
        }
        else
        {
            e_tmp = NULL;
            std::cout << "\nentityManager -> getEntity: Entity Was Not Found!\n" << std::endl;
        }
    }

    return e_tmp;
}

Entity * entityManager::getEntity(int e)
{
    return object_managerv[e];
}

void entityManager::promoteEntityToEmpty(Entity * object)
{
}

void entityManager::promoteEntityToSprite(Entity * object)
{
    if( typeid(object).name() == typeid(Entity).name())
    {
        objectManager::iterator it = object_manager.find(object->getName());
        //Grab Data Before Delete And Promote ie call new.
        //Entity Doesn't have any real type of data atm.

        if(it != object_manager.end())
        {
            delete it->second;
            it->second = new Sprite();
            it->second->setName(it->first);
        }
        else
            std::cout << "\nEntityManager -> promoteEntityToSprite: No Object To Promote!\n" << std::endl;
    }
    else
        std::cout << "\nEntityManager -> promoteEntityToSprite:Can Not Promote Object To Sprite.\n--Object Is Not Of Base Entity!\n" << std::endl;
}

void entityManager::promoteEntityToText(Entity * object)
{
}

void entityManager::promoteEntityToTile(Entity * object)
{
    if( typeid(object).name() == typeid(Entity).name())
    {
        objectManager::iterator it = object_manager.find(object->getName());
        //Grab Data Before Delete And Promote ie call new.
        //Entity Doesn't have any real type of data atm.

        if(it != object_manager.end())
        {
            delete it->second;
            it->second = new Tile();
            it->second->setName(it->first);
        }
        else
            std::cout << "\nEntityManager -> promoteEntityToSprite: No Object To Promote!\n" << std::endl;
    }
    else
        std::cout << "\nEntityManager -> promoteEntityToSprite:Can Not Promote Object To Sprite.\n--Object Is Not Of Base Entity!\n" << std::endl;
}

void entityManager::promoteEntityToMesh(Entity * object)
{
}

void entityManager::operator= (const entityManager & right)
{
}
