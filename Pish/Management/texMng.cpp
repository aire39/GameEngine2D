#include "texMng.h"

texMng::texMng()
{
    ctexture_name = "";
    ctexturesub_name = "";
    recent = "";
}

texMng::texMng(const texMng & right)
{
    vTextures = right.vTextures;
    mTextures = right.mTextures;

    vTextureSubs = right.vTextureSubs;
    mTextureSubs = right.mTextureSubs;

    vAllTextures = right.vAllTextures;
    mAllTextures = right.mAllTextures;
}

texMng::~texMng()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting textureManager!" << std::endl;
    #endif

    if( vTextureSubs.size() > 0 )
        for(int i=0; i< (int)vTextureSubs.size(); i++)
            delete vTextureSubs[i];

    if( vTextures.size() > 0 )
        for(int i=0; i< (int)vTextures.size(); i++)
            delete vTextures[i];

    vTextures.clear();
    vTextureSubs.clear();
    vAllTextures.clear();

    mTextures.clear();
    mTextureSubs.clear();
    mAllTextures.clear();

}

void texMng::addTexture(TextureBase * texture)
{
}

Texture * texMng::addTexture(const char * texture_path, bool key)
{
    Texture * r_new_texture = new Texture();
    if( r_new_texture->Load(texture_path) )
    {
        vTextures.push_back(r_new_texture);
        mTextures.insert( std::map<std::string, Texture * >::value_type(r_new_texture->GetTextureName(), r_new_texture) );

        vAllTextures.push_back(r_new_texture);
        mAllTextures.insert( std::map<std::string, TextureBase * >::value_type(r_new_texture->GetTextureName(), r_new_texture) );

        recent = r_new_texture->GetTextureName();
    }
    else
    {
        std::cout << "New Texture Class Failed To Load Texture!" << std::endl;
        delete r_new_texture;
        r_new_texture = NULL;
    }

    return r_new_texture;
}

void texMng::removeTexture(int texture_Index)
{
    /**
    Remove Texture By Index In Manager
    */

    if( vTextures.size() > 0 )
    if( (texture_Index >= 0) && (texture_Index < (int)vTextures.size()) )
    {
        Texture * texture = vTextures[texture_Index];

        mTextures.erase( mTextures.find(texture->GetTextureName()) );
        vTextures.erase( vTextures.begin() + texture_Index );

        mAllTextures.erase( mAllTextures.find(texture->GetTextureName()) );
        vAllTextures.erase( vAllTextures.begin() + texture_Index );

        if(texture->GetTextureSub() != NULL)
        {
            TextureSub * texture_sub = texture->GetTextureSub();
            delete texture_sub;
            texture_sub = NULL;

            texture->SetTextureSub(NULL);
            delete texture;
            texture = NULL;
        }
        else
        {
            delete texture;
            texture = NULL;
        }
    }

}

void texMng::removeTexture(const char * texture_name)
{
    if( mTextures.size() > 0 )
    {
        std::map<std::string, Texture * >::iterator it = mTextures.find(texture_name);

        if(it != mTextures.end())
        {
            Texture * texture = it->second;

            for(int i=0; i<(int)vTextures.size(); i++)
                if(strcmp( vTextures[i]->GetTextureName(), texture->GetTextureName())==0)
                {
                    vTextures.erase( vTextures.begin() + i );
                    break;
                }

            mTextures.erase(it);

            delete texture;
            texture = NULL;
        }
    }

}

void texMng::removeAllTextures()
{
    if(vTextures.size() > 0)
    {
        for(int i=0; i<(int)vTextures.size(); i++)
        {
            if( vTextures[i]->GetTextureSub() != NULL )
                delete vTextures[i]->GetTextureSub();

            delete vTextures[i];
        }

        vTextures.clear();
        mTextures.clear();

        vTextureSubs.clear();
        mTextureSubs.clear();

        vAllTextures.clear();
        mAllTextures.clear();
    }
}

Texture * texMng::GetTexture(const char * texture_name)
{
    if( mTextures.find(texture_name) != mTextures.end() )
        return mTextures[texture_name];

    return NULL;
}

Texture * texMng::GetTexture(int texture_index)
{
    if(vTextures.size() > 0)
    {
        if((texture_index >= (int)vTextures.size()) || (texture_index < 0))
            return 0;

        return vTextures[texture_index];
    }
    else
        cout << "There are no textures to retrieve!" << endl;

    return 0;
}

int texMng::GetNumberOfTextures()
{
    return vTextures.size();
}

int texMng::GetNumberOfTextureSubs()
{
    return vTextureSubs.size();
}

int texMng::GetNumberOfAllTextures()
{
    return (vTextures.size() + vTextureSubs.size());
}

void texMng::SetSelectedTexture(std::string texture_name)
{
    this->ctexture_name = texture_name;
}

std::string texMng::GetSelectedTexture()
{
    return ctexture_name;
}

std::string texMng::GetSelectedTexture2()
{
    return ctexturesub_name;
}

void texMng::SetSelectedTexture2(std::string texture_name)
{
    this->ctexturesub_name = texture_name;
}

std::string texMng::GetRecent()
{
    return recent;
}

texMng texMng::operator= (const texMng & right)
{
    vTextures = right.vTextures;
    mTextures = right.mTextures;

    vTextureSubs = right.vTextureSubs;
    mTextureSubs = right.mTextureSubs;

    vAllTextures = right.vAllTextures;
    mAllTextures = right.mAllTextures;

    return *this;
}
