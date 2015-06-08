#include "../Core/TextureSub.h"
#include "../Core/Texture.h"
#include <stdlib.h>
#include <iostream>

TextureSub::TextureSub()
{
    master_texture = NULL;
    is_choped     = false;
    is_texturesub = true;

    nchopx = 0;
    nchopy = 0;
}

TextureSub::~TextureSub()
{
    for(int i=0; i<(int)children.size(); i++)
        delete children[i];

    children.clear();
    master_texture->SetTextureSub(NULL);
    master_texture = NULL;

    nchopx = 0;
    nchopy = 0;
}

void TextureSub::chopfunc(int nrow, int ncol, int width_incr, int height_inc)
{
    ilBindImage( master_texture->GetImageID() );

    if( width_incr < 0 )
        width_incr = ilGetInteger(IL_IMAGE_WIDTH)/ncol;
    if( height_inc < 0 )
        height_inc = ilGetInteger(IL_IMAGE_HEIGHT)/nrow;

    nchopx = ncol;
    nchopy = nrow;

    for(int i=0; i<nrow; i++)
    {
        for(int j=0; j<ncol; j++)
        {
            char hold[10];
            itoa( j+(i*ncol), hold, 10 );

            std::string set_name;
            Texture * texture_sub = new Texture();

            set_name = master_texture->GetTextureName();
            set_name.append( hold );

            texture_sub->OverideTextureName( set_name.c_str() );

            unsigned char * sub_data = NULL;
            unsigned char * sub_data3 = NULL;

            if( master_texture->HasAlpha() )
            {
                sub_data = new unsigned char[width_incr*height_inc*4];
                sub_data3 = new unsigned char[width_incr*height_inc*3];
                ilCopyPixels(j*width_incr, i*height_inc, 0, width_incr, height_inc, 1, IL_RGBA, IL_UNSIGNED_BYTE, sub_data);
                ilCopyPixels(j*width_incr, i*height_inc, 0, width_incr, height_inc, 1, IL_RGB, IL_UNSIGNED_BYTE, sub_data3);
                texture_sub->LoadTextureData(sub_data, sub_data3, width_incr, height_inc, true);
            }
            else
            {
                sub_data3 = new unsigned char[width_incr*height_inc*3];
                sub_data = new unsigned char[width_incr*height_inc*4];
                ilCopyPixels(j*width_incr, i*height_inc, 0, width_incr, height_inc, 1, IL_RGB, IL_UNSIGNED_BYTE, sub_data3);
                ilCopyPixels(j*width_incr, i*height_inc, 0, width_incr, height_inc, 1, IL_RGBA, IL_UNSIGNED_BYTE, sub_data);
                texture_sub->LoadTextureData(sub_data, sub_data3, width_incr, height_inc);
            }

            children.push_back(texture_sub);
            mchildren.insert( std::map<std::string, Texture *>::value_type(set_name, texture_sub) );

        }
    }
}

void TextureSub::AttachMasterTexture(Texture * master_texture)
{
    this->master_texture = master_texture;
    this->master_texture->SetTextureSub(this);
}

bool TextureSub::ChopTexture(int nrow, int ncol, int width_incr, int height_inc)
{
    if( (master_texture == NULL) || (is_choped == true) )
        return is_choped;

    if( (nrow <= 1) && (ncol <= 1) )
        return is_choped;

    //If Function Can Get Processed Then is_choped is true
    chopfunc(nrow, ncol);
    is_choped = true;

    return is_choped;
}

Texture * TextureSub::GetMasterTexture()
{
    return master_texture;
}

Texture * TextureSub::GetTexture(int index)
{
    if( (index < 0) || (index >= (int)children.size()) )
        return NULL;

    return children[index];
}

Texture * TextureSub::GetTexture(std::string texture_name)
{
    if( mchildren.find(texture_name) != mchildren.end() )
        return mchildren[texture_name];

    return NULL;
}

bool TextureSub::IsChoped()
{
    return is_choped;
}

int TextureSub::GetNumberOfChopedX()
{
    return nchopx;
}

int TextureSub::GetNumberOfChopedY()
{
    return nchopx;
}

int TextureSub::GetNumberOfSubs()
{
    return children.size();
}
