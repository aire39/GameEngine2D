#ifndef SHADER_H
#define SHADER_H

#include "../Common/GLee.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Shader
{
    private:
        char * nfileVertex;     ///Char String for vertex file name
        char * nfileFragment;   ///Char String for fragment file name
		char * bufferV;          ///Char String for holding file information : Stores vertex info
		char * bufferF;			///Char String for holding file information : Stores fragment/pixel info
        bool isUsed;            ///Check to see if shader is in use

        unsigned int vertShadeHandler;  ///Vertex Shader Handler
        unsigned int programHandler;    ///Shader Object Handler
        unsigned int fragShadeHandler;  ///Fragment Shader Handler (Fragment also means Pixel Shader)

        char * readShaderFile(char * sFile);  ///Read Shader Files
        void setupShader();                   ///Setup/Compile Shader Scripts


    public:
        Shader();
        Shader( char * vertexFile, char * fragFile);
        ~Shader();

        void loadFile( char * vertexFile, char * fragFile); ///Easily Load Shader Files

        bool isShaderUsed();                                ///Returns if Shader is in use or not
        bool useShader(bool inUse);                         ///Function to turn on or off Shader use and return status
        void useShader();                                   ///Function to use Shader
        void stopShader();                                  ///Function to stop shader usage

        void shaderLog(bool b = false);                     ///Function to print out shader compile errors if false but will print to
                                                            ///file when true [Default: false] [file/console output]

        void shaderLog(char * fileLocation);                ///Function to print out shader compile errors [file output]

        char * getFileName();                               ///Return File Name
        string getFileNameStr();                          ///Return File Name

        unsigned int getProgramHandler();                   ///Return Shader Object Handler


};

#endif
