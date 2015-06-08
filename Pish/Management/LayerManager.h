#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

//#include "../Window/projectTreeView.h"
//#include "../Management/scriptMng.h"
//#include "../Core/pScript.h"
//#include "../Core/Entity.h"

#include <vector>
#include <map>
#include <string>

class scriptMng;
class pScript;
class Entity;
class entityManager;

struct LayerData
{
    std::vector<pScript*> scripts;
    pScript * script;
    Entity  * entity;
};

typedef std::vector< std::vector<LayerData*> > LAYER;
typedef std::map< std::string, LayerData*> MLAYER;

class LayerManager
{
    private:
    scriptMng * script_manager;

    LAYER  LayerControl;
    MLAYER LayerControlM;
                    ///Checks to see what layer the entity is on
    void Update();

    public:
                        ///Constructor
        LayerManager();
                        ///Destructor
        ~LayerManager();
                                                                ///Bind Script Manager
        void BindScriptManager( scriptMng * script_manager );
                                                                ///Insert Data For Layer Management
        void Insert(LayerData * layer_data);
                                                                ///
        LayerData * GetObjectLayerData(Entity * entity);
                                                                     ///
        void InitLayerScript( Entity * _entity, pScript * _script );
                                                                     ///Remove Deleted Object
        void RemoveObject(Entity * entity);
                                                                     ///Render According to Layers
        void Render();
                                                                     ///Render Object Color ID According to Layers
        void RenderID();
                                                                     ///Render Object With No Texture Or Color Modification
        void RenderRaw();


};

#endif // LAYERMANAGER_H
