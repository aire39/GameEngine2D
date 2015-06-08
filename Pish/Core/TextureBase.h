#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <string>

class TextureBase
{
    protected:

        std::string texture_name;
        std::string texture_path;
        std::string texture_ext;

        int texture_width;
        int texture_height;

        bool is_texturesub;
        bool has_alpha;

    public:
                                ///Constructor
        TextureBase();
                                ///Destructor
        virtual ~TextureBase();
                                ///Check To See If Texture Has An Alpha Channel
        virtual bool HasAlpha();
                                    ///Check If Texture Is A TextureSub
        virtual bool IsTextureSub();
                                                ///Get Textures Name
        virtual const char * GetTextureName();
                                                ///Get Textures File Path
        virtual const char * GetTexturePath();
                                                ///Get Texture Extension[Format Type]
        virtual const char * GetTextureExt();

};

#endif // TEXTUREBASE_H
