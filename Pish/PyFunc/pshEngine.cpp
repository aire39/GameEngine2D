#include "../PyFunc/pshEngine.h"

pshEngine::pshEngine()
{
    scene_manager = NULL;
}


pshEngine::~pshEngine()
{
}

void pshEngine::BindSceneManager(SceneManager * scene_manager)
{
    this->scene_manager = scene_manager;
}

entityManager * pshEngine::getObjectManager(int n)
{
    if( ( n >= 0 ) && ( n<scene_manager->size()) )
        return scene_manager->at(n);

    std::cout << "Not Found!" << std::endl;

    return NULL;
}

entityManager pshEngine::getObjectManagerPy(int n) const
{
    if( ( n >= 0 ) && ( n<scene_manager->size()) )
        return *scene_manager->at(n);

    std::cout << "Not Found!" << std::endl;
    entityManager tmp_manager;
    return tmp_manager;
}

