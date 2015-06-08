#include "ShaderMng.h"

ShaderMng::ShaderMng()
{
    nShaders = 0;
}


ShaderMng::~ShaderMng()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting shaderManager!" << std::endl;
    #endif
    ShaderList.clear();
}


void ShaderMng::addShader(Shader * s)
{
    ShaderList.push_back(s);
    nShaders++;
}


void ShaderMng::removeShader(const char * shaderName)
{
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }

    ShaderList.erase(sIter);
    nShaders--;
}


void ShaderMng::removeShader(int index)
{
    for(int i=0; i<index; i++)
        sIter++;

    ShaderList.erase(sIter);
    nShaders--;
}


void ShaderMng::removeAll()
{
    //for(sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    //    ShaderList.erase(sIter);

	if(ShaderList.size() > 0)
	{
		ShaderList.clear();
		nShaders = 0;
	}
}


void ShaderMng::showShader(const char * shaderName)
{
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }

    (*sIter)->useShader();

}


void ShaderMng::showShader(int index)
{
    ShaderList[index]->useShader();
}


void ShaderMng::stopShader(const char * shaderName)
{
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }

    (*sIter)->stopShader();
}


void ShaderMng::stopShader(int index)
{
    ShaderList[index]->stopShader();
}


void ShaderMng::stopAll()
{
    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
        (*sIter)->stopShader();
}


Shader * ShaderMng::getShader(const char * shaderName)
{
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }

    return (*sIter);
}


Shader * ShaderMng::getShader(int index)
{
    return ShaderList[index];
}


int ShaderMng::getNumShaders()
{
    return nShaders;
}


int ShaderMng::getShaderIndex(const char * shaderName)
{
    wxString str = shaderName;
    int i=0;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;

        i++;
    }

    return i;
}


char * ShaderMng::getShaderName(int index)
{
    return ShaderList[index]->getFileName();
}


wxString ShaderMng::getShaderNameStr(int index)
{
    return ShaderList[index]->getFileName();
}


/////////////////////////////////////////Uniform Variable Functions//////////////////////////////////////////////////////////

//Note: Atm seems to only work with my NVIDIA card.

void ShaderMng::toUniformVar(const char* shaderName, const char * varName, int value)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform1i(loc, value);
}


void ShaderMng::toUniformVar(int sIndex, const char * varName, int value)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform1i(loc, value);
}


void ShaderMng::toUniformVar(const char* shaderName, const char * varName, float value)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform1f(loc, value);
}


void ShaderMng::toUniformVar(int sIndex, const char * varName, float value)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform1f(loc, value);
}



void ShaderMng::toUniformVar(const char* shaderName, const char * varName, int value, int value2)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform2i(loc, value, value2);
}


void ShaderMng::toUniformVar(int sIndex, const char * varName, int value, int value2)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform2i(loc, value, value2);
}


void ShaderMng::toUniformVar(const char* shaderName, const char * varName, float value, float value2)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform2f(loc, value, value2);
}


void ShaderMng::toUniformVar(int sIndex, const char * varName, float value, float value2)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform2f(loc, value, value2);
}



void ShaderMng::toUniformVar(const char* shaderName, const char * varName, int value, int value2, int value3)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform3i(loc, value, value2, value3);
}


void ShaderMng::toUniformVar(int sIndex, const char * varName, int value, int value2, int value3)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform3i(loc, value, value2, value3);
}


void ShaderMng::toUniformVar(const char* shaderName, const char * varName, float value, float value2, float value3)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform3f(loc, value, value2, value3);
}


void ShaderMng::toUniformVar(int sIndex, const char * varName, float value, float value2, float value3)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform3f(loc, value, value2, value3);
}



void ShaderMng::toUniformVar(const char* shaderName, const char * varName, int value, int value2, int value3, int value4)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform4i(loc, value, value2, value3, value4);
}


void ShaderMng::toUniformVar(int sIndex, const char * varName, int value, int value2, int value3, int value4)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform4i(loc, value, value2, value3, value4);
}


void ShaderMng::toUniformVar(const char* shaderName, const char * varName, float value, float value2, float value3, float value4)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform4f(loc, value, value2, value3, value4);
}


void ShaderMng::toUniformVar(int sIndex, const char * varName, float value, float value2, float value3, float value4)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform4f(loc, value, value2, value3, value4);
}




void ShaderMng::toUniformVarArr(int sIndex, const char * varName, int numArr, int * value)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform1iv(loc, numArr, value);
}


void ShaderMng::toUniformVarArr(const char* shaderName, const char * varName, int numArr, int * value)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform1iv(loc, numArr, value);
}


void ShaderMng::toUniformVarArr(int sIndex, const char * varName, int numArr, float * value)
{
    int loc;
    loc = glGetUniformLocation(ShaderList[sIndex]->getProgramHandler(), varName);

/*
    char buf[2];
    itoa(loc, buf, 10);
    wxMessageDialog *msg = new wxMessageDialog(NULL, buf, "Test");
    msg->ShowModal();
    delete msg;
*/
    glUniform1fv(loc, numArr, value);
}


void ShaderMng::toUniformVarArr(const char* shaderName, const char * varName, int numArr, float * value)
{
    int loc;
    wxString str = shaderName;

    for( sIter = ShaderList.begin(); sIter != ShaderList.end(); sIter++)
    {
        if(str.Cmp( (*sIter)->getFileNameStr() ) == 0)
            break;
    }


    loc = glGetUniformLocation((*sIter)->getProgramHandler(), varName);

    glUniform1fv(loc, numArr, value);
}
