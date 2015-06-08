#include "../Management/entityManager.h"
//#include "../Window/projectTreeView.h"

tileEntityManager::tileEntityManager()
{
    p_name = "";
}

tileEntityManager::~tileEntityManager()
{
    ///Fix: Causes Crash

    #ifdef __WXDEBUG__
        std::cout << "Deleting tileEntityManager!" << std::endl;
    #endif

    for( objectManager::iterator it = object_manager.begin(); it != object_manager.end(); ++it)
    {
        if( script_manager->get_number_of_scripts() != 0)
            if( script_manager->searchScript(it->first) )
                unbindObjectToScript(it->first);

        //If I Destroy Th Root Folder Then The Subs Go With It.
        //tree_view->delItem( p_name, it->first);
        //std::cout << it->first << std::endl;
        //tree_view->delItem(it->first);
        delete it->second;
    }
    object_manager.clear();
    pick_manager.clear();
}

void tileEntityManager::addEntity(std::string type, std::string parent_name, std::string object_name)
{
    convert_string_tolower(type); //Use boost later for this
    std::string name_check = "object_0";
    int i=0;
    char buf[12];

    if(p_name.length() == 0)
        p_name = parent_name;//;tree_view->GetItemText(tree_view->GetSelection());

    if(type.compare("empty") == 0 )
    {

        Entity * empty = new Entity();
        empty->init();

            if( object_name.empty())
            {
                while(object_manager.find(name_check) != object_manager.end())
                {
                    name_check.clear();
                    name_check = "object_";
                    i++;
                    itoa(i, buf, 10);
                    name_check.append(buf);
                }

                empty->setName(name_check);
            }
            else
                empty->setName(object_name);

        wxTreeItemId tile_name = tree_view->searchTreeConfine(tree_view->GetSelection(), (std::string)parent_name);

        if( tile_name.IsOk())
        {
            tree_view->addSubItem(tile_name, empty->getName(), "entity", 1);
            object_manager.insert( objectManager::value_type(empty->getName(), empty) );
            pick_manager.insert(objectColorIDManager::value_type(empty->getColorID(), empty->getName()));
        }
        else
            std::cout << "tileEntityManager -> addEntity: Failed! (Adding Empty)\n" << std::endl;


    }
    else if(type.compare("sprite") == 0)
    {

        Sprite * sprite = new Sprite();
        sprite->init();


        if( object_name.empty())
        {
            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = "tileset_";
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            sprite->setName(name_check);
        }
        else
            sprite->setName(object_name);

        wxTreeItemId tile_name = tree_view->searchTreeConfine(tree_view->GetSelection(), (std::string)parent_name);

        if( tile_name.IsOk())
        {
            tree_view->addSubItem(tile_name, sprite->getName(), "entity", 1);
            object_manager.insert( objectManager::value_type(sprite->getName(), sprite) );
            pick_manager.insert(objectColorIDManager::value_type(sprite->getColorID(), sprite->getName()));
        }
        else
            std::cout << "tileEntityManager -> addEntity: Failed! (Adding Sprite)\n" << std::endl;

    }
    else if(type.compare("tile") == 0)
    {

        Tile * tile = new Tile();
        tile->BindTileToTreeView(tree_view);
        tile->init(this->script_manager);

        if( object_name.empty())
        {
            while(object_manager.find(name_check) != object_manager.end())
            {
                name_check.clear();
                name_check = "object_";
                i++;
                itoa(i, buf, 10);
                name_check.append(buf);
            }

            tile->setName(name_check);
        }
        else
            tile->setName(object_name);

        ///Needs access to script manager also or it crashes.
        wxTreeItemId tile_name = tree_view->searchTreeConfine(tree_view->GetSelection(), (std::string)parent_name);

        if( tile_name.IsOk())
        {
            tree_view->addSubItem(tile_name, tile->getName(), "entity", 1);
            object_manager.insert( objectManager::value_type(tile->getName(), tile) );
            pick_manager.insert(objectColorIDManager::value_type(tile->getColorID(), tile->getName()));
        }
        else
            std::cout << "tileEntityManager -> addEntity: Failed! (Adding Tile)\n" << std::endl;

    }
    else
        std::cout << "\ntileEntityManager -> addEntity: Type Not Found!\n" << std::endl;

}


void tileEntityManager::delEntity(std::string object_name) ///Not Setup Yet : Deletes at the subtile lvl
{
    objectManager::iterator it = object_manager.find(object_name);

    if(it != object_manager.end())
    {
        if( script_manager->get_number_of_scripts() != 0)
            if( script_manager->searchScript(it->first) )
                unbindObjectToScript(it->first);

        //Deletes objects ColorID that way the name is released.
        //Doone by iterating straigtht throughe look for a better method later.
        objectColorIDManager::iterator it_colID = pick_manager.begin();
        for(; it_colID!=pick_manager.end(); ++it_colID)
            if( it_colID->second == object_name)
            {
                pick_manager.erase(it_colID);
                break;
            }

        ///Can't find proper item to remove
        tree_view->delItem((std::string)tree_view->GetItemText(tree_view->GetSelection()), object_name);

        delete it->second;
        it->second = NULL;
        object_manager.erase(it);
    }
    else
        std::cout << "\nentityManager -> delEntity: Object Not Found!\n" << std::endl;
}



Entity * tileEntityManager::getEntitySub(unsigned char * colorID)
{
    Entity * e_tmp = NULL;


    ///Wasn't trying to do it this way but map::find won't do what I need it to. Need to look for workaround.
    objectColorIDManager::const_iterator it_colID = pick_manager.begin();
    for(; it_colID!=pick_manager.end(); ++it_colID)
        if(it_colID->first[0] == colorID[0] && it_colID->first[1] == colorID[1] && it_colID->first[2] == colorID[2])
            break;


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
    else
        std::cout << "\nentityManager -> getEntity: ColorID Was Not Found!\n" << std::endl;

    return e_tmp;
}


void tileEntityManager::setTextureAll(unsigned int textureID)
{
    for(objectManager::iterator it = object_manager.begin(); it != object_manager.end(); ++it)
        it->second->setTexture(textureID);

}
