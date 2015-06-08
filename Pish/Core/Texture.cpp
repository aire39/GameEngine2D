#include "../Core/Texture.h"
#include "../Core/TextureSub.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>

Texture::Texture()
{
    texture_sub = NULL;
    is_texturesub = false;

    texture_data = NULL;
    texture_data3 = NULL;

    texture_id = 0;
    ilId = 0;

    texture_width = 0;
    texture_height = 0;
}

Texture::~Texture()
{
    ilDeleteImages(1, &ilId);
    glDeleteTextures(1, &texture_id);

    ilId = 0;
    texture_id = 0;

    if( texture_data != NULL )
        delete [] texture_data;

    if( texture_data3 != NULL )
        delete [] texture_data3;

    texture_data = NULL;
    texture_data3 = NULL;
}

int Texture::CheckExtension(const char * ext)
{
    int ext_type = -1;

    if( strcmp(ext, ".png") == 0 )
        ext_type = 0;
    else if( strcmp(ext, ".jpg") == 0 )
        ext_type = 1;
    else if( strcmp(ext, ".tga") == 0 )
        ext_type = 2;
    else if( strcmp(ext, ".bmp") == 0 )
        ext_type = 3;

    return ext_type;

}

void Texture::BuildTexture()
{
    glGenTextures(1, &texture_id);

    SetFilter(GL_LINEAR, GL_LINEAR);          //Sets the bind texture to zero after it sets the filter
    glBindTexture(GL_TEXTURE_2D, texture_id); //So this needs to be called here.

    if(has_alpha)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, /*width*/ilGetInteger(IL_IMAGE_WIDTH), /*height*/ilGetInteger(IL_IMAGE_HEIGHT), /*border*/0, GL_RGBA, GL_UNSIGNED_BYTE, /*pixel data*/ilGetData());
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, /*width*/ilGetInteger(IL_IMAGE_WIDTH), /*height*/ilGetInteger(IL_IMAGE_HEIGHT), /*border*/0, GL_RGB, GL_UNSIGNED_BYTE, /*pixel data*/ilGetData());

    CreateLOD(5);
}

bool Texture::Load(const char * path)
{
    /////////////////////////////////
    ////Init devIL and Load Image////
    /////////////////////////////////

    ilInit();

    ilGenImages(1, &ilId);
    ilBindImage(ilId);

    if(!ilLoadImage( path) )
    {
        std::cout << "Failed Loading Texture!" << std::endl;
        return 0;
    }

    texture_width = ilGetInteger(IL_IMAGE_WIDTH);
    texture_height = ilGetInteger(IL_IMAGE_HEIGHT);

    if(ilGetInteger( IL_IMAGE_FORMAT ) == IL_COLOR_INDEX )
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    if( (ilGetInteger(IL_IMAGE_FORMAT) == IL_RGBA) || (ilGetInteger(IL_IMAGE_FORMAT) == IL_BGRA) )
    {
        texture_data = new unsigned char[ilGetInteger(IL_IMAGE_WIDTH)*ilGetInteger(IL_IMAGE_HEIGHT)*4];
        ilCopyPixels(0, 0, 0, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 1, IL_RGBA, IL_UNSIGNED_BYTE, texture_data);

        texture_data3 = new unsigned char[ilGetInteger(IL_IMAGE_WIDTH)*ilGetInteger(IL_IMAGE_HEIGHT)*3];
        ilCopyPixels(0, 0, 0, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 1, IL_RGB, IL_UNSIGNED_BYTE, texture_data3);

        has_alpha = 1;
    }
    else
    {
        texture_data3 = new unsigned char[ilGetInteger(IL_IMAGE_WIDTH)*ilGetInteger(IL_IMAGE_HEIGHT)*3];
        ilCopyPixels(0, 0, 0, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 1, IL_RGB, IL_UNSIGNED_BYTE, texture_data3);

        texture_data = new unsigned char[ilGetInteger(IL_IMAGE_WIDTH)*ilGetInteger(IL_IMAGE_HEIGHT)*4];
        ilCopyPixels(0, 0, 0, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 1, IL_RGBA, IL_UNSIGNED_BYTE, texture_data);
        has_alpha = 0;
    }


    ////////////////////////////////
    ////Extract File Information////
    ////////////////////////////////

    this->texture_path = path;

    char *p;
    p = strrchr((char *)path, '/');  //Looks for last occurance of '/' and store the rest
    if( p == NULL)
    p = strrchr((char *)path, '\\');
    this->texture_name = p+1;        //of the string (after '/') into string variable name.

    p = strchr((char *)this->texture_name.c_str(), '.'); //Looks for first occurance of '.' and store the rest (including '.')
    this->texture_ext = p;                               //of the string into string variable ext.

    int L = strlen((char *)this->texture_name.c_str());  //Grabs the length of the name variable string and is used to create the
    this->texture_name.erase(L-4, 4);                    //starting position to erase the ext and just leave the name.
                                                         //startPos, how many char to erase


    ///////////////////////////////////////
    ////Build Image As a Opengl Texture////
    ///////////////////////////////////////
    if( CheckExtension(texture_ext.c_str()) > -1 )
        BuildTexture();
    else
    {
        ilDeleteImages(1, &ilId);
        ilId = 0;
        std::cout << "Format Not Supported!" << std::endl;
        return 0;
    }

    return 1;

}

void Texture::SetFilter(int min_filter, int mag_filter)
{
    if( texture_id != 0 )
    {
        glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mag_filter);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Texture::LoadTextureData(unsigned char * data, int width, int height, bool has_alpha)
{
    if( texture_id <= 0 )
    {
        texture_width = width;
        texture_height = height;

        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        if(has_alpha)
        {
            this->texture_data = data;
            this->has_alpha = 1;
        }

        else
        {
            this->texture_data3 = data;
            this->has_alpha = 0;
        }


        if( has_alpha )
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, /*width*/width, /*height*/height, /*border*/0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, /*width*/width, /*height*/height, /*border*/0, GL_RGB, GL_UNSIGNED_BYTE, data);

        SetFilter(GL_LINEAR, GL_LINEAR);
    }
}

void Texture::LoadTextureData(unsigned char * data, unsigned char * data3, int width, int height, bool has_alpha)
{
    if( texture_id <= 0 )
    {
        texture_width = width;
        texture_height = height;

        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        this->texture_data  = data;
        this->texture_data3 = data3;
        this->has_alpha = 1;

        if( has_alpha )
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, /*width*/width, /*height*/height, /*border*/0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, /*width*/width, /*height*/height, /*border*/0, GL_RGB, GL_UNSIGNED_BYTE, data3);

        SetFilter(GL_LINEAR, GL_LINEAR);
    }
}

void Texture::OverideTextureName(const char * texture_name)
{
    this->texture_name = texture_name;
}

int Texture::GetImageID()
{
    return ilId;
}

int Texture::GetTextureID()
{
    return texture_id;
}

int Texture::GetTextureWidth(int base)
{
    return texture_width;
}

int Texture::GetTextureHeight(int base)
{
    return texture_height;
}

TextureSub * Texture::GetTextureSub()
{
    return texture_sub;
}

unsigned char * Texture::GetTextureData()
{
    return texture_data;
}

unsigned char * Texture::GetTextureData3()
{
    return texture_data3;
}

void Texture::SetTextureSub(TextureSub * texture_sub)
{
    this->texture_sub = texture_sub;
}

void Texture::CreateLOD(int levels)
{
    if( ilId <= 0 )
    {
        std::cout << "No Image/Texture To Create LOD With!" << std::endl;
        return;
    }

    unsigned int ilcpyID = 0;
    ilGenImages(1, &ilcpyID);
    ilBindImage(ilcpyID);

    ilCopyImage(ilId);

    int internal_format = 0;
    int actual_format = 0;

    if( has_alpha )
    {
        internal_format = GL_RGBA8;
        actual_format = GL_RGBA;
    }
    else
    {
        internal_format = GL_RGB8;
        actual_format   = GL_RGB;
    }

    for(int i=2; i<levels+2; i++)
    {
        iluScale( ilGetInteger(IL_IMAGE_WIDTH)/i, ilGetInteger(IL_IMAGE_HEIGHT)/i, 0 );

        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, (i-1), internal_format, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, actual_format, GL_UNSIGNED_BYTE, ilGetData() );
    }

    ilDeleteImages(1, &ilcpyID);

}

void Texture::UseTexture()
{
    glBindTexture(GL_TEXTURE_2D, texture_id);
}


unsigned char * Texture::ConvertFromNewToAlloc(Texture * texture, bool using_alpha)
{
    unsigned char * A = NULL;

    if( using_alpha )
        A = (unsigned char *)calloc( texture->GetTextureWidth()*texture->GetTextureHeight()*4, sizeof(unsigned char) );
    else
        A = (unsigned char *)calloc( texture->GetTextureWidth()*texture->GetTextureHeight()*3, sizeof(unsigned char) );

    if( using_alpha )
        for(int i=0; i<(texture->GetTextureWidth()*texture->GetTextureHeight()*4); i++)
            A[i] = texture->GetTextureData()[i];
    else
        for(int i=0; i<(texture->GetTextureWidth()*texture->GetTextureHeight()*3); i++)
            A[i] = texture->GetTextureData3()[i];

    return A;
}
