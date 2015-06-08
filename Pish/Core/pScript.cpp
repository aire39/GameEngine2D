#include "pScript.h"

pScript::pScript()
{
    mode = 0;
    relink = false;

    s_manager = NULL;
    pyData = "";

    main_module = import("__main__");
    main_namespace = main_module.attr("__dict__");

    embed_export = false;
}

pScript::pScript(scriptMng * script_manager, std::string script_data)
{
    mode = 0;
    relink = false;

    s_manager = script_manager;

    pyData = script_data;

    main_module = import("__main__");
    main_namespace = main_module.attr("__dict__");

    embed_export = false;
}

pScript::~pScript()
{
    /*
    #ifdef __WXDEBUG__
        std::cout << "deleting pScript!" << std::endl;
    #endif
    */
    for(int i=0; i<var_bools.size(); i++)
        delete var_bools[i].first;

    for(int i=0; i<var_floats.size(); i++)
        delete var_floats[i].first;

    for(int i=0; i<var_ints.size(); i++)
        delete var_ints[i].first;

    for(int i=0; i<var_strs.size(); i++)
        delete var_strs[i].first;

    for(int i=0; i<var_timers.size(); i++)
        delete var_timers[i].first;

    var_bools.clear();
    var_floats.clear();
    var_ints.clear();
    var_strs.clear();
    var_timers.clear();

    mvar_bools.clear();
    mvar_floats.clear();
    mvar_ints.clear();
    mvar_strs.clear();
    mvar_timers.clear();

}

void pScript::BindScriptManager(scriptMng * script_manager)
{
    this->s_manager = script_manager;
}

void pScript::loadScript(std::string script)
{
    main_module = import("__main__");
    main_namespace = main_module.attr("__dict__");

    if( !pyData.empty() )
        pyData.clear();

    pyData = script;
}

std::string pScript::getData()
{
    return pyData;
}

void pScript::setName(std::string script_name)
{
    this->script_name = script_name;
}

void pScript::setBoundName(std::string script_bound)
{
    key_name = script_bound;
    relink = true;
}

void pScript::setFilePath(std::string path)
{
    this->path = path;
}

std::string pScript::getName()
{
    return script_name;
}

std::string pScript::getBoundName()
{
    return key_name;
}

std::string pScript::GetFilePath()
{
    return path;
}

void pScript::setMode(int mode)
{
    this->mode = mode;
}

int pScript::getMode()
{
    return mode;
}

bool pScript::isReLink()
{
    return relink;
}

bool pScript::isRunning()
{
    bool running = false;

    switch(mode)
    {
        case 0:
        case 1:
            running = false;
        break;

        case 2:
            running = true;
        break;

        default:
            running = false;
        break;
    }

    return running;
}

void pScript::SetSaveMode(bool b)
{
    embed_export = b;
}

bool pScript::EmbedExportMode()
{
    return embed_export;
}

void pScript::init()
{
    ///Depending on type of entity
}

void pScript::stop()
{
    mode = 0;
}

void pScript::run_once()
{
    mode = 1;
}

void pScript::run()
{
    mode = 2;
}

void pScript::execute()
{
    if(!pyData.empty())
    {
        if(mode == 2)
        {
            try
            {
                //object ignore = exec(pyData.c_str(), main_namespace, main_namespace);
                //boost::python::handle_exception( exec(pyData.c_str(), main_namespace, main_namespace) );
                PyRun_SimpleString(pyData.c_str());


            }
            catch( error_already_set const & )
            {
                PyErr_Print();
            }
/*
            try
            {
                float x = 0.0f;
                object x_;
                object x_2;
                x_ = main_module.attr("tr");
                x_2 = x_.attr("k");
                x = extract<float>(x_2);
                std::cout << "\nKHGGHK:::     " << x << "\n\n";
            }catch(error_already_set)
            {
                PyErr_Print();
            }
*/

        }
        else if( mode == 1 )
        {
            try
            {
                //object ignore = exec(pyData.c_str(), main_namespace, main_namespace);
                PyRun_SimpleString(pyData.c_str());
                mode = 0;
            }
            catch( error_already_set const & )
            {
                PyErr_Print();
            }

        }
        else if( mode == 0)
        {
        }

    }

        //std::cout << "Script Entered!" << key_name << " , " << script_name << std::endl;

}

////////////////////
////////////////////
////////////////////

////////////////////////
//Add/Remove Functions//
////////////////////////

std::string pScript::VarAlreadyIn(int type, std::string var_name)
{
        switch(type)
        {
            case 0:
            {
                if(var_name.empty())
                {
                    var_name = "timer";

                    int i=0;
                    char hold[3];
                    while( mvar_timers.find(var_name.c_str()) != mvar_timers.end() )
                    {
                        var_name = "timer";
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
                else if( mvar_timers.find(var_name.c_str()) != mvar_timers.end() )
                {
                    std::string var_hold = var_name;

                    int i=0;
                    char hold[3];
                    while( mvar_timers.find(var_name.c_str()) != mvar_timers.end() )
                    {
                        var_name = var_hold;
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
            }
            break;

            case 1:
            {
                if(var_name.empty())
                {
                    var_name = "string";

                    int i=0;
                    char hold[3];
                    while( mvar_strs.find(var_name.c_str()) != mvar_strs.end() )
                    {
                        var_name = "string";
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
                else if( mvar_strs.find(var_name.c_str()) != mvar_strs.end() )
                {
                    std::string var_hold = var_name;

                    int i=0;
                    char hold[3];
                    while( mvar_strs.find(var_name.c_str()) != mvar_strs.end() )
                    {
                        var_name = var_hold;
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
            }
            break;

            case 2:
            {
                if(var_name.empty())
                {
                    var_name = "float";

                    int i=0;
                    char hold[3];
                    while( mvar_floats.find(var_name.c_str()) != mvar_floats.end() )
                    {
                        var_name = "float";
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
                else if( mvar_floats.find(var_name.c_str()) != mvar_floats.end() )
                {
                    std::string var_hold = var_name;

                    int i=0;
                    char hold[3];
                    while( mvar_floats.find(var_name.c_str()) != mvar_floats.end() )
                    {
                        var_name = var_hold;
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
            }
            break;

            case 3:
            {
                if(var_name.empty())
                {
                    var_name = "bool";

                    int i=0;
                    char hold[3];
                    while( mvar_bools.find(var_name.c_str()) != mvar_bools.end() )
                    {
                        var_name = "bool";
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
                else if( mvar_bools.find(var_name.c_str()) != mvar_bools.end() )
                {
                    std::string var_hold = var_name;

                    int i=0;
                    char hold[3];
                    while( mvar_bools.find(var_name.c_str()) != mvar_bools.end() )
                    {
                        var_name = var_hold;
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
            }
            break;

            case 4:
            {
                if(var_name.empty())
                {
                    var_name = "int";

                    int i=0;
                    char hold[3];
                    while( mvar_ints.find(var_name.c_str()) != mvar_ints.end() )
                    {
                        var_name = "int";
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
                else if( mvar_ints.find(var_name.c_str()) != mvar_ints.end() )
                {
                    std::string var_hold = var_name;

                    int i=0;
                    char hold[3];
                    while( mvar_ints.find(var_name.c_str()) != mvar_ints.end() )
                    {
                        var_name = var_hold;
                        itoa(i, hold, 10);
                        var_name.append(hold);
                        i++;
                    }
                }
            }
            break;

        default:
        break;

        }


    return var_name;
}

void pScript::AddVar(int type, std::string var_name)
{
    convert_string_tolower(var_name);

    switch(type)
    {
        case 0: //timer
        {
            pair<boost::timer *, int>         mtimer_pair;
            pair<boost::timer *, std::string> vtimer_pair;

            var_name = VarAlreadyIn(0, var_name);
            boost::timer * timer = new boost::timer();

            mtimer_pair.first = timer;
            mtimer_pair.second = var_timers.size();
            mvar_timers.insert( std::map<std::string, pair<boost::timer *, int> >::value_type(var_name, mtimer_pair) );

            vtimer_pair.first = timer;
            vtimer_pair.second = var_name;
            var_timers.push_back(vtimer_pair);
        }

        break;

        case 1: //string
        {
            pair<std::string*, int>         mstr_pair;
            pair<std::string*, std::string> vstr_pair;

            var_name = VarAlreadyIn(1, var_name);
            std::string * nstr = new std::string;
            nstr->clear();

            mstr_pair.first = nstr;
            mstr_pair.second = var_strs.size();
            mvar_strs.insert( std::map<std::string, pair<std::string*, int> >::value_type(var_name, mstr_pair) );

            vstr_pair.first  = nstr;
            vstr_pair.second = var_name;
            var_strs.push_back(vstr_pair);

        }
        break;

        case 2: //float
        {
            pair<float*, int>         mfloat_pair;
            pair<float*, std::string> vfloat_pair;

            var_name = VarAlreadyIn(2, var_name);
            float * nfloat = new float;
            *nfloat = 0.0f;

            mfloat_pair.first = nfloat;
            mfloat_pair.second = var_floats.size();
            mvar_floats.insert( std::map<std::string, pair<float*, int> >::value_type(var_name, mfloat_pair) );

            vfloat_pair.first  = nfloat;
            vfloat_pair.second = var_name;
            var_floats.push_back(vfloat_pair);

        }
        break;

        case 3: //bool
        {
            pair<bool*, int>         mbool_pair;
            pair<bool*, std::string> vbool_pair;

            var_name = VarAlreadyIn(3, var_name);
            bool * nbool = new bool;
            *nbool = false;

            mbool_pair.first = nbool;
            mbool_pair.second = var_bools.size();
            mvar_bools.insert( std::map<std::string, pair<bool*, int> >::value_type(var_name, mbool_pair) );

            vbool_pair.first  = nbool;
            vbool_pair.second = var_name;
            var_bools.push_back(vbool_pair);

        }
        break;

        case 4: //int
        {
            pair<int*, int>         mint_pair;
            pair<int*, std::string> vint_pair;

            var_name = VarAlreadyIn(4, var_name);
            int * nint = new int;
            *nint = 0;

            mint_pair.first = nint;
            mint_pair.second = var_ints.size();
            mvar_ints.insert( std::map<std::string, pair<int*, int> >::value_type(var_name, mint_pair) );

            vint_pair.first  = nint;
            vint_pair.second = var_name;
            var_ints.push_back(vint_pair);

        }
        break;

        default:
            std::cout << "not a correct type!" << std::endl;
        break;
    }
}
void pScript::AddVar(std::string type, std::string var_name)
{
    convert_string_tolower(type);
    convert_string_tolower(var_name);

    if( type == "timer")
    {
            pair<boost::timer *, int>         mtimer_pair;
            pair<boost::timer *, std::string> vtimer_pair;

            var_name = VarAlreadyIn(0, var_name);
            boost::timer * timer = new boost::timer();

            mtimer_pair.first = timer;
            mtimer_pair.second = var_timers.size();
            mvar_timers.insert( std::map<std::string, pair<boost::timer *, int> >::value_type(var_name, mtimer_pair) );

            vtimer_pair.first = timer;
            vtimer_pair.second = var_name;
            var_timers.push_back(vtimer_pair);
    }
    else if( type == "string" )
    {
        pair<std::string*, int>         mstr_pair;
        pair<std::string*, std::string> vstr_pair;

        var_name = VarAlreadyIn(1, var_name);
        std::string * nstr = new std::string;
        nstr->clear();

        mstr_pair.first = nstr;
        mstr_pair.second = var_strs.size();
        mvar_strs.insert( std::map<std::string, pair<std::string*, int> >::value_type(var_name, mstr_pair) );

        vstr_pair.first  = nstr;
        vstr_pair.second = var_name;
        var_strs.push_back(vstr_pair);
    }
    else if( type == "float" )
    {
        pair<float*, int>         mfloat_pair;
        pair<float*, std::string> vfloat_pair;

        var_name = VarAlreadyIn(2, var_name);
        float * nfloat = new float;
        *nfloat = 0.0f;

        mfloat_pair.first = nfloat;
        mfloat_pair.second = var_floats.size();
        mvar_floats.insert( std::map<std::string, pair<float*, int> >::value_type(var_name, mfloat_pair) );

        vfloat_pair.first  = nfloat;
        vfloat_pair.second = var_name;
        var_floats.push_back(vfloat_pair);
    }
    else if( type == "bool" )
    {
        pair<bool*, int>         mbool_pair;
        pair<bool*, std::string> vbool_pair;

        var_name = VarAlreadyIn(3, var_name);
        bool * nbool = new bool;
        *nbool = false;

        mbool_pair.first = nbool;
        mbool_pair.second = var_bools.size();
        mvar_bools.insert( std::map<std::string, pair<bool*, int> >::value_type(var_name, mbool_pair) );

        vbool_pair.first  = nbool;
        vbool_pair.second = var_name;
        var_bools.push_back(vbool_pair);
    }
    else if( type == "int" )
    {
        pair<int*, int>         mint_pair;
        pair<int*, std::string> vint_pair;

        var_name = VarAlreadyIn(4, var_name);
        int * nint = new int;
        *nint = 0;

        mint_pair.first = nint;
        mint_pair.second = var_ints.size();
        mvar_ints.insert( std::map<std::string, pair<int*, int> >::value_type(var_name, mint_pair) );

        vint_pair.first  = nint;
        vint_pair.second = var_name;
        var_ints.push_back(vint_pair);
    }
    else
        std::cout << "not a correct type!" << std::endl;
}

//////Remove//////

void pScript::RemoveVar(std::string type, std::string var_name)
{
    convert_string_tolower(type);
    convert_string_tolower(var_name);

    if( type == "timer")
    {
        std::map<std::string, pair<boost::timer *, int> >::iterator mit = mvar_timers.find(var_name);

        if( mit != mvar_timers.end() )
        {
            boost::timer * timer = mit->second.first;

            var_timers.erase( var_timers.begin()+mit->second.second );
            mvar_timers.erase(mit);

            delete timer;
            timer = NULL;

        }
    }
    else if( type == "string" )
    {
        std::map<std::string, pair<std::string *, int> >::iterator mit = mvar_strs.find(var_name);

        if( mit != mvar_strs.end() )
        {
            std::string * str = mit->second.first;

            var_strs.erase( var_strs.begin()+mit->second.second );
            mvar_strs.erase(mit);

            delete str;
            str = NULL;

        }
    }
    else if( type == "float" )
    {
        std::map<std::string, pair<float *, int> >::iterator mit = mvar_floats.find(var_name);

        if( mit != mvar_floats.end() )
        {
            float * mfloat = mit->second.first;

            var_floats.erase( var_floats.begin()+mit->second.second );
            mvar_floats.erase(mit);

            delete mfloat;
            mfloat = NULL;
        }
    }
    else if( type == "bool" )
    {
        std::map<std::string, pair<bool *, int> >::iterator mit = mvar_bools.find(var_name);

        if( mit != mvar_bools.end() )
        {
            bool * mbool = mit->second.first;

            var_bools.erase( var_bools.begin()+mit->second.second );
            mvar_bools.erase(mit);

            delete mbool;
            mbool = NULL;
        }
    }
    else if( type == "int" )
    {
        std::map<std::string, pair<int *, int> >::iterator mit = mvar_ints.find(var_name);

        if( mit != mvar_ints.end() )
        {
            int * mint = mit->second.first;

            var_ints.erase( var_ints.begin()+mit->second.second );
            mvar_ints.erase(mit);

            delete mint;
            mint = NULL;
        }
    }
    else
        std::cout << "not a correct type!" << std::endl;
}

void pScript::RemoveVar(std::string type, int index)
{
    convert_string_tolower(type);

    if( type == "timer")
    {
        std::vector< pair<boost::timer *, std::string> >::iterator it = var_timers.begin()+index;

        if( it != var_timers.end() )
        {
            boost::timer * timer = it->first;

            mvar_timers.erase( it->second.c_str() );
            var_timers.erase(it);

            delete timer;
            timer = NULL;
        }
    }
    else if( type == "string" )
    {
        std::vector< pair<std::string *, std::string> >::iterator it = var_strs.begin()+index;

        if( it != var_strs.end() )
        {
            std::string * str = it->first;

            mvar_strs.erase( it->second.c_str() );
            var_strs.erase(it);

            delete str;
            str = NULL;
        }
    }
    else if( type == "float" )
    {
        std::vector< pair<float *, std::string> >::iterator it = var_floats.begin()+index;

        if( it != var_floats.end() )
        {
            float * mfloat = it->first;

            mvar_floats.erase( it->second.c_str() );
            var_floats.erase(it);

            delete mfloat;
            mfloat = NULL;
        }
    }
    else if( type == "bool" )
    {
        std::vector< pair<bool *, std::string> >::iterator it = var_bools.begin()+index;

        if( it != var_bools.end() )
        {
            bool * mbool = it->first;

            mvar_bools.erase( it->second.c_str() );
            var_bools.erase(it);

            delete mbool;
            mbool = NULL;
        }
    }
    else if( type == "int" )
    {
        std::vector< pair<int *, std::string> >::iterator it = var_ints.begin()+index;

        if( it != var_ints.end() )
        {
            int * mint = it->first;

            mvar_ints.erase( it->second.c_str() );
            var_ints.erase(it);

            delete mint;
            mint = NULL;
        }
    }
    else
        std::cout << "not a correct type!" << std::endl;
}

void pScript::RemoveVar(int type, int index)
{
    switch(type)
    {
        case 0: //timer
        {
            std::vector< pair<boost::timer *, std::string> >::iterator it = var_timers.begin()+index;

            if( it != var_timers.end() )
            {
                boost::timer * timer = it->first;

                mvar_timers.erase( it->second.c_str() );
                var_timers.erase(it);

                delete timer;
                timer = NULL;
            }
        }
        break;

        case 1: //string
        {
            std::vector< pair<std::string *, std::string> >::iterator it = var_strs.begin()+index;

            if( it != var_strs.end() )
            {
                std::string * str = it->first;

                mvar_strs.erase( it->second.c_str() );
                var_strs.erase(it);

                delete str;
                str = NULL;
            }
        }
        break;

        case 2: //float
        {
            std::vector< pair<float *, std::string> >::iterator it = var_floats.begin()+index;

            if( it != var_floats.end() )
            {
                float * mfloat = it->first;

                mvar_floats.erase( it->second.c_str() );
                var_floats.erase(it);

                delete mfloat;
                mfloat = NULL;
            }
        }
        break;

        case 3: //bool
        {
            std::vector< pair<bool *, std::string> >::iterator it = var_bools.begin()+index;

            if( it != var_bools.end() )
            {
                bool * mbool = it->first;

                mvar_bools.erase( it->second.c_str() );
                var_bools.erase(it);

                delete mbool;
                mbool = NULL;
            }
        }
        break;

        case 4: //int
        {
            std::vector< pair<int *, std::string> >::iterator it = var_ints.begin()+index;

            if( it != var_ints.end() )
            {
                int * mint = it->first;

                mvar_ints.erase( it->second.c_str() );
                var_ints.erase(it);

                delete mint;
                mint = NULL;
            }
        }
        break;

        default:
            std::cout << "not a correct type!" << std::endl;
        break;
    }
}

void pScript::RemoveVar(int type, std::string var_name)
{
    convert_string_tolower(var_name);

    switch(type)
    {
        case 0: //timer
        {
            std::map<std::string, pair<boost::timer *, int> >::iterator mit = mvar_timers.find(var_name);

            if( mit != mvar_timers.end() )
            {
                boost::timer * timer = mit->second.first;

                var_timers.erase( var_timers.begin()+mit->second.second );
                mvar_timers.erase(mit);

                delete timer;
                timer = NULL;

            }
        }
        break;

        case 1: //string
        {
            std::map<std::string, pair<std::string *, int> >::iterator mit = mvar_strs.find(var_name);

            if( mit != mvar_strs.end() )
            {
                std::string * str = mit->second.first;

                var_strs.erase( var_strs.begin()+mit->second.second );
                mvar_strs.erase(mit);

                delete str;
                str = NULL;

            }
        }
        break;

        case 2: //float
        {
            std::map<std::string, pair<float *, int> >::iterator mit = mvar_floats.find(var_name);

            if( mit != mvar_floats.end() )
            {
                float * mfloat = mit->second.first;

                var_floats.erase( var_floats.begin()+mit->second.second );
                mvar_floats.erase(mit);

                delete mfloat;
                mfloat = NULL;
            }
        }
        break;

        case 3: //bool
        {
            std::map<std::string, pair<bool *, int> >::iterator mit = mvar_bools.find(var_name);

            if( mit != mvar_bools.end() )
            {
                bool * mbool = mit->second.first;

                var_bools.erase( var_bools.begin()+mit->second.second );
                mvar_bools.erase(mit);

                delete mbool;
                mbool = NULL;
            }
        }
        break;

        case 4: //int
        {
            std::map<std::string, pair<int *, int> >::iterator mit = mvar_ints.find(var_name);

            if( mit != mvar_ints.end() )
            {
                int * mint = mit->second.first;

                var_ints.erase( var_ints.begin()+mit->second.second );
                mvar_ints.erase(mit);

                delete mint;
                mint = NULL;
            }
        }
        break;

        default:
            std::cout << "not a correct type!" << std::endl;
        break;
    }
}
/////////////////////
//Set Var Functions//
/////////////////////

void pScript::SetVarStr(int var_index, std::string value)
{
    if( (var_index >= 0) && (var_index<(int)var_strs.size()) )
       *var_strs[var_index].first = value;
}
void pScript::SetVarStr(const char * var_name, std::string value)
{
    if( mvar_strs.find(var_name) != mvar_strs.end() )
       *mvar_strs[var_name].first = value;
}

void pScript::SetVarFloat(int var_index, float value)
{
    if( (var_index >= 0) && (var_index<(int)var_floats.size()) )
       *var_floats[var_index].first = value;
}
void pScript::SetVarFloat(const char * var_name, float value)
{
    if( mvar_floats.find(var_name) != mvar_floats.end() )
       *mvar_floats[var_name].first = value;
}

void pScript::SetVarBool(int var_index, bool value)
{
    if( (var_index >= 0) && (var_index<(int)var_bools.size()) )
       *var_bools[var_index].first = value;
}
void pScript::SetVarBool(const char * var_name, bool value)
{
    if( mvar_bools.find(var_name) != mvar_bools.end() )
       *mvar_bools[var_name].first = value;
}

void pScript::SetVarInt(int var_index, int value)
{
    if( (var_index >= 0) && (var_index<(int)var_ints.size()) )
       *var_ints[var_index].first = value;
}
void pScript::SetVarInt(const char * var_name, int value)
{
    if( mvar_ints.find(var_name) != mvar_ints.end() )
       *mvar_ints[var_name].first = value;
}

/////////////////////
//Get Var Functions//
/////////////////////

boost::timer * pScript::GetVarTimer(int index)
{
    if( (var_timers.size() > 0) && (index < var_timers.size()) )
        return var_timers[index].first;

     std::cout << "pScript -> " << script_name << " : Can't Get or Find Index " << index << " Of Stored Timer." << std::endl;

    return 0;
}
boost::timer * pScript::GetVarTimer(const char * var_name)
{
    if( mvar_timers.find(var_name) != mvar_timers.end() )
        return mvar_timers[var_name].first;

    std::cout << "pScript -> " << script_name << " : Can't Get or Find Name " << var_name << " Of Stored Timer." << std::endl;

    return 0;
}

std::string pScript::GetVarStr(int index)
{
    if( (var_strs.size() > 0) && (index < var_strs.size()) )
        return *var_strs[index].first;

    std::cout << "pScript -> " << script_name << " : Can't Get or Find Index " << index << " Of Stored String." << std::endl;

    return "";
}
std::string pScript::GetVarStr(const char * var_name)
{
    if( mvar_strs.find(var_name) != mvar_strs.end() )
        return *mvar_strs[var_name].first;

    std::cout << "pScript -> " << script_name << " : Can't Get or Find Name " << var_name << " Of Stored String." << std::endl;

    return "";
}

float pScript::GetVarFloat(int index)
{
    if( (var_floats.size() > 0) && (index < var_floats.size()) )
        return *var_floats[index].first;

    std::cout << "pScript -> " << script_name << " : Can't Get or Find Index " << index << " Of Stored Float." << std::endl;

    return 0.0f;
}
float pScript::GetVarFloat(const char * var_name)
{
    if( mvar_floats.find(var_name) != mvar_floats.end() )
        return *mvar_floats[var_name].first;

    std::cout << "pScript -> " << script_name << " : Can't Get or Find Name " << var_name << " Of Stored Float." << std::endl;

    return 0.0f;
}

bool pScript::GetVarBool(int index)
{
    if( (var_bools.size() > 0) && (index < var_bools.size()) )
        return *var_bools[index].first;

    std::cout << "pScript -> " << script_name << " : Can't Get or Find Index " << index << " Of Stored Bool." << std::endl;

    return 0;
}
bool pScript::GetVarBool(const char * var_name)
{
    if( mvar_bools.find(var_name) != mvar_bools.end() )
        return *mvar_bools[var_name].first;

    std::cout << "pScript -> " << script_name << " : Can't Get or Find Name " << var_name << " Of Stored Bool." << std::endl;

    return 0;
}

int pScript::GetVarInt(int index)
{
    if( (var_ints.size() > 0) && (index < var_ints.size()) )
        return *var_ints[index].first;

    std::cout << "pScript -> " << script_name << " : Can't Get or Find Index " << index << " Of Stored Integer." << std::endl;

    return 0;
}
int pScript::GetVarInt(const char * var_name)
{
    if( mvar_ints.find(var_name) != mvar_ints.end() )
        return *mvar_ints[var_name].first;

    std::cout << "pScript -> " << script_name << " : Can't Get or Find Name " << var_name << " Of Stored Integer." << std::endl;

    return 0;
}

bool pScript::HasVars()
{
    bool has = false;

    if( var_timers.size() > 0 )
        has = true;

    if( var_strs.size() > 0 )
        has = true;

    if( var_floats.size() > 0 )
        has = true;

    if( var_bools.size() > 0 )
        has = true;

    if( var_ints.size() > 0 )
        has = true;

    return has;
}

int pScript::GetNumberOfVars(std::string var_type)
{
    convert_string_tolower(var_type);

    if( var_type.compare("timer")==0)
        return var_timers.size();
    else if( var_type.compare("string")==0)
        return var_strs.size();
    else if( var_type.compare("float")==0)
        return var_floats.size();
    else if( var_type.compare("bool")==0)
        return var_bools.size();
    else if( var_type.compare("int")==0)
        return var_ints.size();

    return -1;

}

int pScript::GetNumberOfVars()
{
    return (var_timers.size() + var_strs.size() + var_floats.size() + var_bools.size() + var_ints.size());
}

std::string pScript::GetNameOfVar(int var_index, std::string var_type)
{
    convert_string_tolower(var_type);

    if( var_type.compare("timer")==0 )
        return var_timers[var_index].second;
    else if( var_type.compare("string")==0)
        return var_strs[var_index].second;
    else if( var_type.compare("float")==0)
        return var_floats[var_index].second;
    else if( var_type.compare("bool")==0)
        return var_bools[var_index].second;
    else if( var_type.compare("int")==0)
        return var_ints[var_index].second;

    return "";
}
