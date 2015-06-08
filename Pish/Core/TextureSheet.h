#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H

#include "../Core/Texture.h"

/**
Creates Sub Texture Data But Not By Choping Up Pixels But Rather By
Storing Texture Coordinates That Will Accurately Place The Objects
Texture Coordinates In The Right Position To Show Selected Texture.
[Not Implemented]
*/

class TextureSheet : public TextureBase
{
    private:

        Texture * master_texture;

    public:
                            ///Constructor
        TextureSheet();
                            ///Destructor
        ~TextureSheet();

                                                            ///Attach A Master Texture To Work With
        void AttachMasterTexture(Texture * master_texture);
};

#endif // TEXTURESHEET_H
