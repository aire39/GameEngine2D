#include "../Management/LayerManager.h"
#include "../Core/pScript.h"
#include "../Core/Entity.h"

LayerManager::LayerManager()
{
    script_manager = NULL;
}

LayerManager::~LayerManager()
{
    for(int i=0; i<(int)LayerControl.size(); i++)
        for(int j=0; j<(int)LayerControl[i].size(); j++)
        {
            delete LayerControl[i][j];
            LayerControl[i].clear();
        }
    LayerControl.clear();
    LayerControlM.clear();
}

void LayerManager::Update()
{
    int clayer = 0;

    for(int i=0; i<(int)LayerControl.size(); i++)
    {
        for(int j=0; j<(int)LayerControl[i].size(); j++)
        {
            //Create layer that's not made automatically when checking object layer
            if(LayerControl[i][j]->entity != NULL)
                while( LayerControl[i][j]->entity->getLayer() >= (int)LayerControl.size() )
                {
                    std::vector<LayerData*> add_layer;
                    LayerControl.push_back( add_layer );
                }

            //Switch object layer when changed
            if(LayerControl[i][j]->entity->getLayer() != i)
            {
                LayerData * _LD;
                _LD = LayerControl[i][j];

                clayer = LayerControl[i][j]->entity->getLayer();

                LayerControl[i].erase( LayerControl[i].begin()+j );
                LayerControl[ clayer ].push_back( _LD );
            }

        }
    }
}

void LayerManager::Insert(LayerData * layer_data)
{
    while( layer_data->entity->getLayer() >= (int)LayerControl.size() )
    {
        std::vector<LayerData*> add_layer;
        LayerControl.push_back( add_layer );
    }

    LayerControl[ layer_data->entity->getLayer() ].push_back( layer_data );

    //LayerData * _LD = NULL;
    //_LD = LayerControl[ layer_data->entity->getLayer() ][ LayerControl[layer_data->entity->getLayer()].size()-1 ];
    //LayerControlM.insert( MLAYER::value_type( layer_data->entity->getName() , _LD) );
    LayerControlM.insert( MLAYER::value_type( layer_data->entity->getName() , layer_data) );

}

LayerData * LayerManager::GetObjectLayerData(Entity * entity)
{
    LayerData * layer_data = NULL;

    MLAYER::iterator it = LayerControlM.find(entity->getName());
    if(it != LayerControlM.end())
        layer_data = it->second;

    return layer_data;
}

void LayerManager::InitLayerScript( Entity * _entity, pScript * _script)
{
    /// script ptr doesn't pooint to correct address. It points to some address but it's definitely not the right mem address [FIXED:cause was with relink -> it would delete the mem and then reallocate a new area of mem which was dumb of me]
    /// entity is okay
    Entity * LM_entity = NULL;
    pScript * LM_script = NULL;

    LM_entity = _entity;
    LM_script = _script;

    if( (script_manager != NULL) && (_entity != NULL) && (_script != NULL) && (LayerControlM[ LM_entity->getName().c_str() ]!= NULL) )
    {
        if( LM_script != NULL )
        {
            LM_script->BindScriptManager(this->script_manager);

            MLAYER::iterator it;
            it = LayerControlM.find(LM_entity->getName());

            if(it != LayerControlM.end())
            {
                LayerData * mld = it->second;
                bool already_exists = false;

                for(int i=0; i<mld->scripts.size(); i++)
                    if( mld->scripts[i]->getName().compare( LM_script->getName() ) == 0 )
                    {
                        already_exists = true;
                        break;
                    }

                if( !already_exists )
                    mld->scripts.push_back(LM_script);

                mld->script = LM_script;
            }

        }
        else
            std::cout << "LayerManager::InitLayerScript -> Unable to attach script!" << std::endl;
    }

}

void LayerManager::RemoveObject(Entity * entity)
{
    /**
    In Testing...
    */

    MLAYER::iterator it;
    it = LayerControlM.find(entity->getName());

    if(it != LayerControlM.end())
        LayerControlM.erase(it);

    LAYER::iterator Lit;
    std::vector<LayerData*>::iterator LDit;

    Lit = LayerControl.begin();

    for(; Lit!=LayerControl.end(); Lit++)
    {
        LDit = Lit->begin();

        for(; LDit != Lit->end(); LDit++)
        {
            LayerData * LD = NULL;
            LD = *LDit;
            if( LD->entity->getName().compare(entity->getName()) == 0 )
            {
                LD->scripts.clear();
                delete LD;
                LD = NULL;
                Lit->erase(LDit);
                break;
            }
        }

        //if(LDit->size() <= 0)
        //    LayerControl.erase(Lit);
    }


}

void LayerManager::Render()
{
    Update();
/* //The old way to access and run a script on a specific object
   pScript * _script = NULL;
   _script = script_manager->getScript(LayerControl[i][j]->entity->getName());

    if( _script != NULL )
    {
        script_manager->setEntityPyData(LayerControl[i][j]->entity);
        _script->execute();
    }
*/

    //Render in reverse because I'm technically looking at the objects from behind (accidental)
    for( int i=(int)LayerControl.size()-1; i>=0; i-- )
        for(int j=(int)LayerControl[i].size()-1; j>=0; j--)
        {
            if( script_manager != NULL )
            if( LayerControl[i][j]->script != NULL )
            {
                script_manager->setEntityPyData(LayerControl[i][j]->entity);
                for(int k=0; k<LayerControl[i][j]->scripts.size(); k++)
                {
                    script_manager->setInUseScript( LayerControl[i][j]->scripts[k] );
                    LayerControl[i][j]->scripts[k]->execute();
                }

            }

            LayerControl[i][j]->entity->draw();
        }
}

void LayerManager::RenderID()
{
    for( int i=0; i<(int)LayerControl.size(); i++ )
        for(int j=(int)LayerControl[i].size()-1; j>=0; j--)
            LayerControl[i][j]->entity->picking();

}

void LayerManager::RenderRaw()
{
    Update();

    //Render in reverse because I'm technically looking at the objects from behind
    for( int i=(int)LayerControl.size()-1; i>=0; i-- )
        for(int j=(int)LayerControl[i].size()-1; j>=0; j--)
        {
            if( script_manager != NULL )
            if( LayerControl[i][j]->script != NULL )
            {
                script_manager->setEntityPyData(LayerControl[i][j]->entity);
                for(int k=0; k<LayerControl[i][j]->scripts.size(); k++)
                    LayerControl[i][j]->scripts[k]->execute();

            }

            LayerControl[i][j]->entity->draw_raw();
        }
}

void LayerManager::BindScriptManager(scriptMng * script_manager)
{
    this->script_manager = script_manager;
}
