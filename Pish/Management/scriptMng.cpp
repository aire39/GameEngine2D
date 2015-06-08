#include "../Management/scriptMng.h"
#include "../PyFunc/pyFunc.h"

scriptMng::scriptMng()
{
    camera = NULL;
    Py_Initialize();
}

scriptMng::~scriptMng()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting scriptManager!\n..Ending Python Interpreter!" << std::endl;
    #endif

    if( script_manager.size() != 0 )
    {
        for(scriptManager::iterator it = script_manager.begin(); it != script_manager.end(); ++it)
            delete it->second;
        script_manager.clear();
    }

    camera = NULL;

    PyGC_Collect();
    Py_Finalize();
}

void scriptMng::initManager(pshEngine * py_pshengine)
{
    this->py_pshengine = py_pshengine;

    //Py_Initialize(); //already initialized in the constructor
        initpshVectorMath();
        initpshGameEngine();
        initpshScriptEngine();
        initpshObjectTests();
        initpshEvent();


        main_module = boost::python::import("__main__");
        main_namespace = main_module.attr("__dict__");

        #ifdef __WXDEBUG__
            PyRun_SimpleString("print('Starting python(v2.6)...')\n"
                               "print('Loading Modules...')\n"
                               "print('Set Path...')\n"
                               "print ''\n"
                               "print('For PSH ENGINE script manager and active python(v2.6) interpreter!')\n");
        #endif


        try
        {
            object pshLoadMathModule      = exec_file("./Modules/Common/psh_math_init.py", main_namespace, main_namespace);
            object pshLoadEngineModule    = exec_file("./Modules/Common/psh_engine_init.py", main_namespace, main_namespace);
            object pshLoadEventModule     = exec_file("./Modules/Common/psh_event_init.py", main_namespace, main_namespace);
            object pshLoadEventKeyModule  = exec_file("./Modules/Common/psh_keymacros.py", main_namespace, main_namespace);
            object skipline = exec("print ''", main_namespace, main_namespace);
            object setPyPath = exec("import sys\n"
                                    "sys.path.append('C:/Documents and Settings/Sean/Desktop/Program Development/C++ Projects/PSH Developement/pshOgl_gEngine_a5/bin/Debug/Scripts/')\n"
                                    ,main_namespace, main_namespace);

            object test_object_import = exec_file("./Scripts/test_0_imp.py", main_namespace, main_namespace);

            pointer_wrapper<pshEngine*> pGameEngine_ptr(py_pshengine);
            main_namespace["pshGE"] = pGameEngine_ptr;

            pointer_wrapper<scriptMng*> pScriptEngine_ptr(this);
            main_namespace["pshSE"] = pScriptEngine_ptr;

            std::cout << "pshGE SUCCESS!" << std::endl;

        }
        catch(error_already_set)
        {
            PyErr_Print();
        }
}

void scriptMng::initInterpreter()
{
    Py_Initialize();
        main_module = boost::python::import("__main__");
        main_namespace = main_module.attr("__dict__");

}

void scriptMng::reInitInterpreter()
{
    initpshVectorMath();
    initpshGameEngine();
    initpshObjectTests();
    initpshEvent();

    PyRun_SimpleString("__main__.__dict__.clear()\n");
    main_module = boost::python::import("__main__");
    main_namespace = main_module.attr("__dict__");
}

void scriptMng::endInterpreter()
{
    PyGC_Collect();
    Py_Finalize();
}

void scriptMng::setObjectManagerBind(std::vector<entityManager *> * scene_manager)
{
    this->scene_manager = scene_manager;
}

void scriptMng::BindTreeView(projectTreeView * tree_view)
{
    this->tree_view = tree_view;
}

void scriptMng::BindFrameEvent(frameEvent * frame_event)
{
    this->frame_event = frame_event;

    //Need to get access to frame event address first
    pointer_wrapper<frameEvent*> pFrameEvent_ptr(frame_event);
    main_namespace["FrameEvent"] = pFrameEvent_ptr;
}

void scriptMng::BindCameraFromSceneView(Camera * camera)
{
    this->camera = camera;
}

void scriptMng::setEntityPyData(Entity * e_object)
{
    ///Setting up keywords/variables for script...

    //Sets the keyword 'the objects name'
    //will replace with a 'this' keyword later
    pointer_wrapper<Entity*> current_object(e_object);
    main_namespace[e_object->getName()] = current_object;
    main_namespace["this"] = current_object;

    if( camera != NULL )
    {
        pointer_wrapper<Camera*> camera_ptr(this->camera);
        main_namespace["scene_camera"] = camera_ptr;
    }
}

void scriptMng::setInUseScript(pScript * c_script)
{
    ///Setting up keywords/variables for script...

    if( c_script != NULL )
    {
        pointer_wrapper<pScript*> current_script(c_script);
        main_namespace["this_script"] = current_script;
    }
    else
        main_namespace["this_script"] = 0;
}

pScript *  scriptMng::addScript(std::string file_path)
{
    /**
        Loads a script source
        Only will return a valid added script. It will return NULL if script already exist.
        Use getScript if you want to get access to a particular script.
    */
    ///Can't seem to open another file after the first? i_file fails to 2nd time.
    std::ifstream i_file;

    std::string ext;
    std::string file_name;
    std::string data;

    pScript * r_script = NULL;

    int found = file_path.find_last_of(".");

    if(found > 0)
        ext = file_path.substr(found+1);

    if( ext.compare("py") == 0)
    {
        for(int i=0; i<(int)file_path.length(); i++)
            if(file_path[i] == '\\')
                file_path[i] = '/';

        found = file_path.find_last_of('/');
        file_name = file_path.substr(found+1, file_path.length()-(found+1)-(ext.length()+1));

        std::cout << file_path << std::endl;
        i_file.open(file_path.c_str(), std::ios::in);
        if(i_file.fail())
        {
            std::cout << "\nscriptMng -> addScript: File Not Found!\next: " << ext << std::endl;
            i_file.close();
            return 0;
        }

            char buf[256];

            while(!i_file.eof())
            {
                 i_file.getline(buf,256);
                 data.append(buf);
                 data.append("\n");
            }

        i_file.close();

        std::cout << "\n" << data << " " << i_file.is_open() << "\n" << std::endl;

        ///Check if script is already loaded
        if(script_manager.find( file_name ) != script_manager.end() )
        {
            std::cout << "Script already loaded! Just reloading!" << std::endl;
            pScript * o_script = script_manager.find( file_name )->second;
            if(data.length() != 0)
                o_script->loadScript(data);
        }
        else
        {
            std::cout << "New script loaded!" << std::endl;
            pScript * script = new pScript(this, data);
            script->setName(file_name);
            script->setBoundName(file_name);
            script->setFilePath(file_path);

            ///Loads Script But Script Is Boundless
            script_manager.insert( scriptManager::value_type(script->getBoundName(), script) );
            vscript_manager.push_back(script);

            r_script = script;
        }

    }
    else
        std::cout << "\nscriptMng -> addScript: Not A Script File!\n" << std::endl;

    return r_script;
}

pScript * scriptMng::addNewScript(std::string script_name, std::string object_name)
{
    /**
    Makes a new script source
    */

    int i=0;
    char buf[10];
    pScript * new_script = new pScript(this);
    new_script->setName(script_name);

    //the key is different (probably bbecause of the relink ) than the script name since I'm aoutomatically attaching
    //it to an object. may want to create a better way of doing this.

    scriptManager::iterator itt = script_manager.begin();
    if( itt != script_manager.end() )
    while( itt->second->getName().compare( script_name ) == 0 )
    {
        itoa(i, buf, 10);

        std::string tmp = "";
        tmp.append( script_name );
        tmp.append("_");
        tmp.append(buf);
        new_script->setName(tmp);

        i++;

        std::cout << "CHECKING:" << tmp << std::endl;
    }

    script_manager.insert(scriptManager::value_type(new_script->getName(), new_script));
    vscript_manager.push_back(new_script);


    /// NEW CODE ///

    if( script_manager2.find(object_name) == script_manager2.end())
    {
        scriptManager tmp_scriptman;
        tmp_scriptman.insert( scriptManager::value_type(new_script->getName(), new_script) );
        script_manager2.insert( scriptManager2::value_type(object_name, tmp_scriptman ) );
        //vscript_manager.push_back(new_script);

        std::cout << "SM2" << std::endl;
    }
    else
    {

        while( script_manager2[object_name].find(script_name) != script_manager2[object_name].end() )
        {
            itoa(i, buf, 10);

            std::string tmp = "";
            tmp.append( script_name );
            tmp.append("_");
            tmp.append(buf);
            new_script->setName(tmp);

            i++;

            std::cout << "CHECKING:" << tmp << std::endl;
        }
        script_manager2[object_name].insert( scriptManager::value_type(new_script->getName(), new_script) );
        //vscript_manager.push_back(new_script);
    }

    /// /////////////////////////


    return new_script;
}

pScript * scriptMng::addNewScript(std::string script_name)
{
    pScript * new_script = new pScript(this);
    new_script->setName(script_name);

    script_manager.insert(scriptManager::value_type(script_name, new_script));
    vscript_manager.push_back(new_script);

    return new_script;
}

bool scriptMng::searchScript(std::string script_name)
{
    bool found = false;

    if( script_manager.size() != 0)
        if( script_manager.find(script_name) != script_manager.end() )
            found = true;

    return found;
}

bool scriptMng::searchScriptBound(std::string bound_name)
{
    bool found = false;

    if( script_manager.find(bound_name) != script_manager.end() )
        found = true;

    return found;
}

void scriptMng::reLinkScriptsAll(bool linktype)
{
    //pScript * script = new pScript(this);
/*
    pScript * script = NULL;

    for(scriptManager::iterator it = script_manager.begin(); it != script_manager.end(); ++it)
    {
        if( it->second->isReLink() )
        {
            //script->loadScript(it->second->getData());
            //script->setBoundName(it->second->getBoundName());
            script = it->second;

            //delete it->second;
            script_manager.erase(it);

            if( linktype )
                script_manager.insert( scriptManager::value_type(script->getBoundName(), script) );
            else
                script_manager.insert( scriptManager::value_type(script->getName(), script) );
        }
    }
*/

}

void scriptMng::reLinkScript(std::string script_name, bool linktype)
{
    ///script disappears when detaching

    //pScript * script = new pScript(this);
/*
    pScript * script = NULL;

    if( searchScript(script_name) )
    {
        scriptManager::iterator it = script_manager.find(script_name);

        if( it->second->isReLink() )
        {
            ///Find a way to not do a delete than insert to replace data...
            ///Look into changing the key to std::string * so that I can have 1 script bound to multiple objects.

            //script->loadScript(it->second->getData());
            //script->setBoundName(it->second->getBoundName());
            //script->setName(it->second->getName());
            script = it->second;

            //delete it->second;
            script_manager.erase(it);

            if( linktype )
                script_manager.insert( scriptManager::value_type(script->getBoundName(), script) );
            else
                script_manager.insert( scriptManager::value_type(script->getName(), script) );
        }
    }
*/
}

pScript * scriptMng::GetScriptByIndex(int index)
{
    if((index < 0) || (vscript_manager.size()<0) || (index>=(int)vscript_manager.size()) || (vscript_manager.size()==0))
        return NULL;

    return vscript_manager[index];

}

pScript * scriptMng::getScript(std::string script_name)
{
    pScript * script = NULL;

    if( searchScript(script_name) )
    {
        scriptManager::iterator it = script_manager.find(script_name);
        script = it->second;
    }

    return script;

}

int scriptMng::get_number_of_scripts()
{
    return vscript_manager.size();
}

void scriptMng::getAllScriptName(std::string * modify_str)
{
    int counter = 0;

    for(scriptManager::iterator it = script_manager.begin(); it != script_manager.end(); ++it)
    {
        modify_str[counter].append(it->first);
        counter++;
    }

}

void scriptMng::RemoveAll()
{
    if( script_manager.size() != 0 )
    {
        for(scriptManager::iterator it = script_manager.begin(); it != script_manager.end(); ++it)
            delete it->second;
        script_manager.clear();
        script_manager2.clear();
        vscript_manager.clear();
    }
}
