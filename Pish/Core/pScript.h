#ifndef PSCRIPT_H
#define PSCRIPT_H

#include "../Management/scriptMng.h"
#include "../Common/UtilityFunctions.h"
#include <boost/python.hpp>
#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace boost::python;

class scriptMng;

class pScript
{
    private:


        std::map<std::string, pair<boost::timer *, int> > mvar_timers;
        std::map<std::string, pair<std::string *, int> > mvar_strs;
        std::map<std::string, pair<float *, int> > mvar_floats;
        std::map<std::string, pair<bool *, int> > mvar_bools;
        std::map<std::string, pair<int *, int> > mvar_ints;

        std::vector< pair<boost::timer *, std::string> > var_timers;
        std::vector< pair<std::string *, std::string> > var_strs;
        std::vector< pair<float *, std::string> > var_floats;
        std::vector< pair<bool *, std::string> > var_bools;
        std::vector< pair<int *, std::string> > var_ints;


        bool embed_export;

        scriptMng * s_manager;

        std::string script_name;
        std::string key_name;
        std::string pyData;
        std::string path;
        int mode;

        object  main_module;
        object  main_namespace;

        bool relink;
                                                                    ///Checks If Var Already Exist
        std::string VarAlreadyIn(int type, std::string var_name="");

    public:
                    ///Constructor
        pScript();
                    ///Constructor2
        pScript(scriptMng * script_manager, std::string script_data="");
                    ///Destructor
        ~pScript();

        ////////////////////
        //Binding Managers//
        ////////////////////
                                                            ///Bind Script Manager
        void BindScriptManager( scriptMng * script_manager );

        ///////////////////////
        //Set Data For Script//
        ///////////////////////
                                                            ///Load/Update Script Data
        void loadScript(std::string script);
                                                            ///Set Script Name
        void setName(std::string script_name);
                                                            ///Set Script File Path
        void setFilePath(std::string path);
                                                            ///Set Object Script Is Bound To [May Be Deprecated]
        void setBoundName(std::string script_bound);
                                                            ///Initialize Script
        void init();
        ///////////////////
        //Get Script Data//
        ///////////////////
                                    ///Get Script Data
        std::string getData();
                                    ///Get Script Name
        std::string getName();
                                    ///Get Objects Name That Script Is Bound To
        std::string getBoundName();
                                    ///Get Script File Path
        std::string GetFilePath();

        ////////////////////
        //Set Script Modes//
        ////////////////////
                                    ///Set Script Mode [Stop,Try,Run]
        void setMode(int mode = 0);
                                    ///Set If Script Should Be Embed/Exported When Saving Project File
        void SetSaveMode(bool b);
                                    ///Stop Running Script (setMode = 0 Is The Same)
        void stop();
                                    ///Try Running Script Once (setMode = 1 Is The Same)
        void run_once();
                                    ///Run Script (setMode >= 2 Is The Same)
        void run();
                                    ///Execute The Actual Code Of The Script
        void execute();
        ///////////////////
        //Get Script Mode//
        ///////////////////
                                    ///Get Set Script Mode
        int  getMode();
                                    ///Checks To See If Script Needs To be Relinked [May Be Deprecated]
        bool isReLink();
                                    ///Check To See If Script Is Running
        bool isRunning();
                                    ///Check To See If Script Is To Be Embeded/Exported Into Project File
        bool EmbedExportMode();


        //////////////////////////
        //Access Through Scripts//
        //////////////////////////

        void AddVar(int type, std::string var_name="");
        void AddVar(std::string type, std::string var_name="");
        void RemoveVar(int type, std::string var_name="");
        void RemoveVar(std::string type, std::string var_name="");
        void RemoveVar(int type, int index);
        void RemoveVar(std::string type, int index);

        void SetVarStr(int var_index, std::string value);
        void SetVarStr(const char * var_name, std::string value);
        void SetVarFloat(int var_index, float value);
        void SetVarFloat(const char * var_name, float value);
        void SetVarBool(int var_index, bool value);
        void SetVarBool(const char * var_name, bool value);
        void SetVarInt(int var_index, int value);
        void SetVarInt(const char * var_name, int value);

        boost::timer * GetVarTimer(int index);
        boost::timer * GetVarTimer(const char * var_name);
        std::string GetVarStr(int index);
        std::string GetVarStr(const char * var_name);
        float GetVarFloat(int index);
        float GetVarFloat(const char * var_name);
        bool GetVarBool(int index);
        bool GetVarBool(const char * var_name);
        int GetVarInt(int index);
        int GetVarInt(const char * var_name);

        bool HasVars();
        int GetNumberOfVars(std::string var_type);
        int GetNumberOfVars();
        std::string GetNameOfVar(int var_index, std::string var_type);
};

#endif // PSCRIPT_H
