#ifndef PSHENGINE_H
#define PSHENGINE_H

#include "../Management/entityManager.h"
#include <boost/python.hpp>
#include <boost/python/call.hpp>
#include <boost/python/ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

using namespace boost;
using namespace std;
using namespace boost::python;

class entityManager;
typedef std::vector<entityManager *> SceneManager;


class pshEngine
{
    private:

        SceneManager * scene_manager;


    public:

        pshEngine();
        pshEngine(const pshEngine & en){}
        virtual ~pshEngine();

        void BindSceneManager(SceneManager * scene_manager);

        entityManager * getObjectManager(int n);
        entityManager getObjectManagerPy(int n) const;



};

#endif // PSHENGINE_H
