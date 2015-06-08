#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "../Common/UtilityFunctions.h"
#include "../Common/pshdefs.h"
#include "../Common/GLee.h"

#include "../Camera/Camera.h"
#include "../Window/projectTreeView.h"

#include "../Core/CoreObjects.h"
#include "../Common/frameEvent.h"

#include <map>
#include <string>

#include "../Management/LayerManager.h"

typedef std::vector<Entity*> objectManagerV;
typedef std::map<std::string, Entity *> objectManager;
typedef std::map<unsigned char *, std::string> objectColorIDManager;

class projectTreeView;
class scriptMng;
class pshEngine;
class texMng;
class pScript;
class LayerManager;

/**
entityManager handles all work concerning the objects in the scene.
*/

class entityManager
{
    private:

        Camera * global_camera;      //global camera
        LayerManager  layer_manager; //layer management
        std::string   scene_name;    //scene name

    protected:
        texMng          * texture_manager; //texture manager
        scriptMng       * script_manager;  //script manager
        projectTreeView * tree_view;       //tree view

        objectManager        object_manager;    //objects contained by map
        objectManagerV       object_managerv;   //objects contained by vector
        objectColorIDManager pick_manager;      //objects color ids

        bool renderable;

    public:
                                                            ///Constructor
        entityManager();
                                                            ///Copy Constructor
        entityManager(const entityManager & entity_manager);
                                                            ///Destructor
        virtual ~entityManager();

        /////////////////
        //Bind Managers//
        /////////////////

        void BindTreeView(projectTreeView * tree_view);
        void BindTextureManager( texMng * texture_manager );
        void BindScriptManager(scriptMng * script_manager);
        void BindCamera(Camera * camera);

        void bindObjectToScript(std::string object_name, std::string script_name);  ///[may be deprecated]
        void unbindObjectToScript(std::string object_name);                         ///[may be deprecated]

        ///////////////
        //Scene Setup//
        ///////////////
                                                            ///Set Scene Name
        void SetSceneName(std::string scene_name="Scene");
                                                            ///Get Scene Name
        std::string SceneName();
                            ///Make Scene Rendering Active
        void renderActive();
                            ///Make Scene Rendering Deactive
        void renderDeactive();
                            ///Make Scene Rendering Active/Deactive
        void renderEnabled(bool renderable);
                            ///Chack To See If Scene Is Rendering
        bool IsRendering();

        /////////////////////////
        //Scene Layer Functions//
        /////////////////////////
                                                                ///Attach Script To Entity
        void new_setscript(Entity * object, pScript * _script);
                                                                ///Get Entities Layer Data
        LayerData * GetObjectLayerData(Entity * entity);

        ////////////////
        //Scene Render//
        ////////////////
                            ///Render All Entitys [Make Sure To Call When Opengl Context Is Running]
        void Render();
                            ///Render All Entities With No State Changes Other Than Draw
        void Render_Raw();
                            ///Render Entities With There ColorIDs
        void pickRender();

        /////////////////////////////////
        //Add/Delete Objects Into Scene//
        /////////////////////////////////
                                                                              ///Add Entity(By Object)
        void addEntity(Entity * obj);
                                                                              ///Add Entity(By String) -> Has Defs (look in pshdef.h)
        Entity * addEntity(std::string type, std::string object_name = "");
                                                                              ///Delete Entity(By Object)
        void delEntity(Entity * obj);
                                                                              ///Delete Entity(By String)
        void delEntity(std::string object_name);
                                                                                      ///Change Name Of Entity Na Make Parts Refelct The Change
        void changeEntityKey(std::string entity_name, std::string entity_key_change);
                                                                                      ///Check Total Number Of Entitys
        int  number_of_entitys();
                                                                                      ///Search To See If The Entity Exists
        bool searchEntity(std::string object_name);
        ///////////////////
        //Get Object Data//
        ///////////////////
                                                     ///Retrieve Entity
        Entity * getEntity(std::string object_name);
                                                     ///Retrieve Entity By ColorID (Used for picking with mouse)
        Entity * getEntity(unsigned char * colorID);
                                                     ///Retrieve Entity By Index
        Entity * getEntity(int index);

        //////////////////
        //Promote Object//
        //////////////////
                                                      ///Not yet implemented (Obviousely a demote but...)
        void promoteEntityToEmpty(Entity * object);
                                                      ///Not Sure If It Works
        void promoteEntityToSprite(Entity * object);
                                                      ///Not yet implemented
        void promoteEntityToText(Entity * object);
                                                      ///Most Likely Broken
        void promoteEntityToTile(Entity * object);
                                                      ///Not yet implemented
        void promoteEntityToMesh(Entity * object);


        /////////////////
        /////////////////
        /////////////////

        void operator= (const entityManager & right);

};



/**
This Class Will Be Deprecated. I Will Attempt To Just Write Everything In Tile And Not Hva e It Have An entityManager like usage.
*/
class tileEntityManager : public entityManager
{
    private:
        std::string p_name;
        objectColorIDManager pick_manager;

    public:
        tileEntityManager();
        ~tileEntityManager();

        virtual void addEntity(std::string type, std::string parent_name = "", std::string object_name = "");
        virtual void delEntity(std::string object_name);

        Entity * getEntitySub(unsigned char * colorID);

        ///Function(s) that allow to modify all tiles at the same time easier.
        void setTextureAll(unsigned int textureID);
};

#endif // ENTITYMANAGER_H
