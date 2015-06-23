#include "Shader.h"
#ifndef __WIN32__
#include <cstring>
#endif // __WIN32__

Shader::Shader()
{
    isUsed = false;
    nfileVertex = NULL;
    nfileFragment = NULL;
	bufferV = NULL;
	bufferF = NULL;

}

Shader::Shader( char * vertexFile, char * fragFile)
{
    isUsed = false;
    nfileVertex = vertexFile;
    nfileFragment = fragFile;

    setupShader();
}


Shader::~Shader()
{
    if(glIsShader(vertShadeHandler))
    {
		glDeleteShader(vertShadeHandler);
		glDeleteShader(fragShadeHandler);
		glDetachShader(programHandler, vertShadeHandler);
		glDetachShader(programHandler, fragShadeHandler);
    }

    if(glIsProgram(programHandler))
		glDeleteProgram(programHandler);

    //delete [] bufferV; // It seems the shader compile will do it for me whent I detach & delete
    bufferV = NULL;

    //delete [] bufferF;
    bufferF = NULL;

}


char * Shader::readShaderFile(char * sFile)
{
            int iter = 0;
            int length = 0;
            fstream file;


            file.open(sFile, ios::in);
            if(!file)
            {
                //wxMessageDialog *msg = new wxMessageDialog(NULL, "File Not Found!", "File Error");
                //msg->ShowModal();
                //delete msg;

                cout << "FILE ERROR: File Not Found!" << endl;
            }


            file.seekg(0, ios::end);
            length = file.tellg();
            file.seekg(0, ios::beg);


			if(bufferV == NULL)
			{
				bufferV = new char[length];
				bufferV[length] = 0;

				while(file.good())
				{
					bufferV[iter++] = file.get();
					if(iter > length)
					  iter = length;
				}

				bufferV[iter-1] = 0;

				file.close();

				if(bufferV != 0)
					return bufferV;
				else
					return 0;

			}
			else
			{
				bufferF = new char[length];
				bufferF[length] = 0;

				while(file.good())
				{
					bufferF[iter++] = file.get();
					if(iter > length)
					  iter = length;
				}

				bufferF[iter-1] = 0;

				file.close();

				if(bufferF != 0)
					return bufferF;
				else
					return 0;
			}

}


void Shader::setupShader()
{
        	char *vertShaderSource;
            char *fragShaderSource;

    		vertShadeHandler = glCreateShader(GL_VERTEX_SHADER);
    		fragShadeHandler = glCreateShader(GL_FRAGMENT_SHADER);

    		vertShaderSource = readShaderFile(nfileVertex);
    		fragShaderSource = readShaderFile(nfileFragment);

    		const char * vv = vertShaderSource;
    		const char * ff = fragShaderSource;


    		glShaderSource(vertShadeHandler, 1, &vv, NULL);
    		glShaderSource(fragShadeHandler, 1, &ff, NULL);

    		glCompileShader(vertShadeHandler);
    		glCompileShader(fragShadeHandler);

    		programHandler = glCreateProgram();

    		glAttachShader(programHandler,vertShadeHandler);
    		glAttachShader(programHandler,fragShadeHandler);

    		glLinkProgram(programHandler);

}



void Shader::loadFile( char * vertexFile, char * fragFile)
{
    nfileVertex = vertexFile;
    nfileFragment = fragFile;

    setupShader();
}

bool Shader::isShaderUsed()
{
    if(isUsed)
    {
        glUseProgram(programHandler);
        return isUsed;
    }
    else
    {
        glUseProgram(0);
        return isUsed;
    }
}

bool Shader::useShader(bool inUse)
{
    isUsed = inUse;

    if(isUsed)
    {
        glUseProgram(programHandler);
        return isUsed;
    }
    else
    {
        glUseProgram(0);
        return isUsed;
    }

    return isUsed;
}

void Shader::useShader()
{
    glUseProgram(programHandler);
}

void Shader::stopShader()
{
    glUseProgram(0);
}

char * Shader::getFileName()
{
    string path = nfileVertex;
    string name;

    char *p;
    p = strrchr((char *)path.c_str(), '/'); //Looks for last occurance of '/' and store the rest
    name = p+1;               //of the string (after '/') into string variable name.

    int L = strlen((char *)name.c_str());  //Grabs the length of the name variable string and is used to create the
    name.erase(L-5, 5);            //starting position to erase the ext and just leave the name.
                                         //startPos, how many char to erase

    return (char *)name.c_str();
}


string Shader::getFileNameStr()
{
    string path = nfileVertex;
    string name;

    char *p;
    p = strrchr((char *)path.c_str(), '/'); //Looks for last occurance of '/' and store the rest
    name = p+1;               //of the string (after '/') into string variable name.

    int L = strlen((char *)name.c_str());  //Grabs the length of the name variable string and is used to create the
    name.erase(L-5, 5);            //starting position to erase the ext and just leave the name.
                                         //startPos, how many char to erase

    return name;
}

unsigned int Shader::getProgramHandler()
{
    return programHandler;
}

void Shader::shaderLog(bool b)
{
    string str = getFileName();
    cout << "shader test:" << str << "..." << endl;

    char * logBufferV;
    char * logBufferF;
    char * logBufferP;

    int infoLengthV = 0;
    int infoLengthF = 0;
    int infoLengthP = 0;

    int infoLengthV_h = 0;
    int infoLengthF_h = 0;
    int infoLengthP_h = 0;

    glGetShaderiv(vertShadeHandler, GL_INFO_LOG_LENGTH, &infoLengthV);
    glGetShaderiv(fragShadeHandler, GL_INFO_LOG_LENGTH, &infoLengthF);
    glGetProgramiv(programHandler , GL_INFO_LOG_LENGTH, &infoLengthP);

    logBufferF = new char[infoLengthF];
    logBufferP = new char[infoLengthP];
    logBufferV = new char[infoLengthV];

    fstream file;

    if(b)
    {
        glGetShaderInfoLog(vertShadeHandler, infoLengthV, &infoLengthV_h, logBufferV);
        glGetShaderInfoLog(fragShadeHandler, infoLengthF, &infoLengthF_h, logBufferF);
        glGetProgramInfoLog(programHandler, infoLengthP, &infoLengthP_h, logBufferP);

        file.open("./ShaderLog/TestLog.txt", ios::out);

        file << logBufferV << endl;
        file << logBufferF << endl;
        file << logBufferP << endl;

        file.close();
    }
    else
    {
        glGetShaderInfoLog(vertShadeHandler, infoLengthV, &infoLengthV_h, logBufferV);
        cout << logBufferV << endl;

        glGetShaderInfoLog(fragShadeHandler, infoLengthF, &infoLengthF_h, logBufferF);
        cout << logBufferF << endl;

        glGetProgramInfoLog(programHandler , infoLengthP, &infoLengthP_h, logBufferP);
        cout << logBufferP << endl;
    }

    delete logBufferF;
    delete logBufferP;
    delete logBufferV;
}

void Shader::shaderLog(char * fileLocation)
{
    cout << "shader test:" << getFileName() << "..." << endl;

    char * logBufferV;
    char * logBufferF;
    char * logBufferP;

    int infoLengthV = 0;
    int infoLengthF = 0;
    int infoLengthP = 0;

    int infoLengthV_h = 0;
    int infoLengthF_h = 0;
    int infoLengthP_h = 0;

    glGetShaderiv(vertShadeHandler, GL_INFO_LOG_LENGTH, &infoLengthV);
    glGetShaderiv(fragShadeHandler, GL_INFO_LOG_LENGTH, &infoLengthF);
    glGetProgramiv(programHandler, GL_INFO_LOG_LENGTH, &infoLengthP);

    logBufferF = new char[infoLengthF];
    logBufferP = new char[infoLengthP];
    logBufferV = new char[infoLengthV];

    fstream file;

    glGetShaderInfoLog(vertShadeHandler, infoLengthV, &infoLengthV_h, logBufferV);
    glGetShaderInfoLog(fragShadeHandler, infoLengthF, &infoLengthF_h, logBufferF);
    glGetProgramInfoLog(programHandler, infoLengthP, &infoLengthP_h, logBufferP);

    file.open(fileLocation, ios::out);

    file << logBufferV << endl;
    file << logBufferF << endl;
    file << logBufferP << endl;

    file.close();

    delete logBufferF;
    delete logBufferP;
    delete logBufferV;
}
