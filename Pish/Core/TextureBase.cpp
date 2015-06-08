#include "../Core/TextureBase.h"

TextureBase::TextureBase()
{
    texture_name = "";
    texture_path = "";
    texture_ext  = "";

    is_texturesub = false;
    has_alpha     = false;

    texture_width = 0;
    texture_height = 0;

}

TextureBase::~TextureBase()
{
}

bool TextureBase::HasAlpha()
{
    return has_alpha;
}

bool TextureBase::IsTextureSub()
{
    return is_texturesub;
}

const char * TextureBase::GetTextureName()
{
    return texture_name.c_str();
}

const char * TextureBase::GetTexturePath()
{
    return texture_path.c_str();
}

const char * TextureBase::GetTextureExt()
{
    return texture_ext.c_str();
}

