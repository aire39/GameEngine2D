#include "../Core/TextureSheet.h"

TextureSheet::TextureSheet()
{
    master_texture = NULL;
}

TextureSheet::~TextureSheet()
{
}

void TextureSheet::AttachMasterTexture(Texture * master_texture)
{
    this->master_texture = master_texture;
}

