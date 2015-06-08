#ifndef SHADERMNG_H
#define SHADERMNG_H

#include "../core/Shader.h"
#include <wx/glcanvas.h>
#include <wx/msgdlg.h>
#include <vector>
using namespace std;

class ShaderMng
{
    private:

        vector<Shader *> ShaderList;        ///Holds multiple shaders
        vector<Shader *>::iterator sIter;   ///Iterator for Shaders List

        int nShaders;                       ///Number of shader stored.

    public:

        ShaderMng();
        ~ShaderMng();

        void addShader(Shader * s);                 ///Add Shader
        void removeShader(const char * shaderName); ///Remove Shader by Name
        void removeShader(int index);               ///Remove Shader by index
        void removeAll();                           ///Remove All Shaders

        void showShader(const char * shaderName);   ///Show Shader by using name
        void showShader(int index);                 ///Show Shader by index

        void stopShader(const char * shaderName);   ///Stops using Shader
        void stopShader(int index);                 ///Stops using Shader
        void stopAll();                             ///Stops use of all Shaders

        Shader * getShader(const char * shaderName); ///Get Shader Info by name
        Shader * getShader(int index);               ///Get Shader by index
        int getNumShaders();                         ///Return number of shaders stored

        int getShaderIndex(const char * shaderName);   ///Get Shader Index : input name to get index
        char *   getShaderName(int index);             ///Get Shader Name  : input index to get name
        wxString getShaderNameStr(int index);          ///Get Shader Name  : input index to get name (returns string)

        void toUniformVar(const char* shaderName, const char * varName, int value);   ///Attach c++ variables to shader variables : int 1 value (to pick shader use name)
        void toUniformVar(int sIndex, const char * varName, int value);               ///Attach c++ variables to shader variables : int 1 value
        void toUniformVar(const char* shaderName, const char * varName, float value); ///Attach c++ variables to shader variables : float 1 value (to pick shader use name)
        void toUniformVar(int sIndex, const char * varName, float value);             ///Attach c++ variables to shader variables : float 1 value

        void toUniformVar(const char* shaderName, const char * varName, int value, int value2);     ///Attach c++ variables to shader variables : int 2 values (to pick shader use name)
        void toUniformVar(int sIndex, const char * varName, int value, int value2);                 ///Attach c++ variables to shader variables : int 2 values
        void toUniformVar(const char* shaderName, const char * varName, float value, float value2); ///Attach c++ variables to shader variables : float 2 values (to pick shader use name)
        void toUniformVar(int sIndex, const char * varName, float value, float value2);             ///Attach c++ variables to shader variables : float 2 values

        void toUniformVar(const char* shaderName, const char * varName, int value, int value2, int value3);         ///Attach c++ variables to shader variables : int 3 values (to pick shader use name)
        void toUniformVar(int sIndex, const char * varName, int value, int value2, int value3);                     ///Attach c++ variables to shader variables : int 3 values
        void toUniformVar(const char* shaderName, const char * varName, float value, float value2, float value3);   ///Attach c++ variables to shader variables : float 3 values (to pick shader use name)
        void toUniformVar(int sIndex, const char * varName, float value, float value2, float value3);               ///Attach c++ variables to shader variables : float 3 values

        void toUniformVar(const char* shaderName, const char * varName, int value, int value2, int value3, int value4);         ///Attach c++ variables to shader variables : int 4 values (to pick shader use name)
        void toUniformVar(int sIndex, const char * varName, int value, int value2, int value3, int value4);                     ///Attach c++ variables to shader variables : int 4 values
        void toUniformVar(const char* shaderName, const char * varName, float value, float value2, float value3, float value4); ///Attach c++ variables to shader variables : float 4 values (to pick shader use name)
        void toUniformVar(int sIndex, const char * varName, float value, float value2, float value3, float value4);             ///Attach c++ variables to shader variables : float 4 values

        void toUniformVarArr(int sIndex, const char * varName, int numArr, int * value);                ///Attach c++ variables to shader variables : int array of 1 values
        void toUniformVarArr(const char* shaderName, const char * varName, int numArr, int * value);    ///Attach c++ variables to shader variables : int array of 1 values (to pick shader use name)
        void toUniformVarArr(int sIndex, const char * varName, int numArr, float * value);              ///Attach c++ variables to shader variables : float array of 1 values
        void toUniformVarArr(const char* shaderName, const char * varName, int numArr, float * value);  ///Attach c++ variables to shader variables : float array of 1 values (to pick shader use name)

        //There are few more glUniform types needed to be added here...

};


#endif
