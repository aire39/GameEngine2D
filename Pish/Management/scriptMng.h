#ifndef SCRIPTMNG_H
#define SCRIPTMNG_H

#include "../Common/amath.h"


#include "../Common/frameEvent.h"
#include "../Window/projectTreeView.h"
#include "../Management/entityManager.h"
//#include "../Core/GLFrame.h" //This has to be included somehow so that the script execution has data on glframe
#include "../PyFunc/pshEngine.h"
#include "../Core/pScript.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>



using namespace boost::python;
using namespace vector_math;

class Entity;
class entityManager;
class pScript;
class OGLWin;
class pshEngine;
class projectTreeView;
class Camera;
//class frameEvent;

typedef std::map<std::string, pScript *> scriptManager;
//typedef std::map<std::string, std::vector<pScript*> > scriptManager2;
typedef std::map<std::string, map<std::string, pScript*> > scriptManager2;
typedef std::vector<pScript*> ScriptManagerV;

class scriptMng
{
    private:
        Camera * camera;

        ScriptManagerV vscript_manager;
        scriptManager2 script_manager2; ///NEW
        scriptManager script_manager;
        object main_module;
        object main_namespace;
        pshEngine * py_pshengine;
        frameEvent * frame_event;

        std::vector<entityManager *> * scene_manager;
        projectTreeView * tree_view;

        ///Py functions to work with
        Vec3<float> getObjectPosition(std::string name = "");


    public:
        scriptMng();
        ~scriptMng();

        void initManager(pshEngine * py_pshengine=0);

        void initInterpreter();
        void endInterpreter();
        void reInitInterpreter();


        void setObjectManagerBind(std::vector<entityManager *> * scene_manager);
        void BindTreeView(projectTreeView * tree_view);
        void BindFrameEvent(frameEvent * frame_event);
        void BindCameraFromSceneView(Camera * camera);
        void setEntityPyData(Entity * e_object);
        void setInUseScript(pScript * c_script = NULL);

        pScript * addScript(std::string file_path);
        pScript * addNewScript(std::string script_name, std::string object_name);
        pScript * addNewScript(std::string script_name);
        void delScript(std::string script_name);

        bool searchScript(std::string script_name);
        bool searchScriptBound(std::string bound_name);

        void reLinkScriptsAll(bool linktype = true);
        void reLinkScript(std::string script_name, bool linktype = true);

        pScript * GetScriptByIndex(int index=-1);
        pScript * getScript(std::string script_name);
        int       get_number_of_scripts();
        void getAllScriptName(std::string * modify_str);

        void RemoveAll();

};

#endif // SCRIPTMNG_H
