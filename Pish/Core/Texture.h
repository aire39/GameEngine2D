#ifndef TEXTURE_H
#define TEXTURE_H

/**
Creates a texture from a source or directly

Supported Formats So Far(4):
.png
.jpg
.bmp
.tga
index, rgba, rgb

doesn't have to be a non power of 2 texture/image
*/

#include "../Core/TextureBase.h"

#include <GL/gl.h>
#include "IL/il.h"
#include "IL/ilu.h"

class TextureSub;

class Texture : public TextureBase
{
    private:

        TextureSub * texture_sub;               //child instance for a texture base with this texture as it's master
                                                ///check image type [Private]
        int CheckExtension(const char * ext);
                                                ///Build Texture [Private]
        void BuildTexture();

        unsigned int ilId;               //devIL image id
        unsigned int texture_id;         //texture id

        unsigned char * texture_data;    //Holds RGBA values
        unsigned char * texture_data3;   //Holds RGB  values

    public:
                    ///Constructor
        Texture();
                    ///Destructor
        ~Texture();

        /////////////////////
        //Load Texture Data//
        /////////////////////
                                      ///Load Texture
        bool Load(const char * path);
                                                                                            ///Load Texture Data Directly
        void LoadTextureData(unsigned char * data, int width, int height, bool has_alpha=0);
                                                                                            ///Load Texture Data Directly
        void LoadTextureData(unsigned char * data, unsigned char * data3, int width, int height, bool has_alpha=0);

        ////////////////////
        //Get Texture Data//
        ////////////////////

                            ///Get devIL Image ID
        int GetImageID();
                            ///Get Texture Object ID
        int GetTextureID();
                                            ///Get Texture Width By LOD (Default Is Width Of Base)
        int GetTextureWidth(int base=0);
                                            ///Get Texture Height By LOD (Default Is Height Of Base)
        int GetTextureHeight(int base=0);
                                            ///Get Texture Data RGBA Format
        unsigned char * GetTextureData();
                                            ///Get Texture Data RGB Format
        unsigned char * GetTextureData3();

        ////////////////////////////
        //Set Connected TextureSub//
        ////////////////////////////
                                                        ///Get TextureSub
        TextureSub * GetTextureSub();
                                                        ///Set A TextureSub
        void SetTextureSub( TextureSub * texture_sub );

        /////////////////////
        //Ttexture Settings//
        /////////////////////
                                                                    ///Change The Name Of The Texture
        void OverideTextureName(const char * texture_name);
                                                                    ///Set Texture Filtering
        void SetFilter( int min_filter = 0, int mag_filter = 0 );
                                                                    ///Create x Number Of Level Of Detail For Texture
        void CreateLOD(int levels=0);
                                                                    ///Use Texture
        void UseTexture();

        ///////////////////
        //Other Functions//
        ///////////////////
                                                                                                    ///Convert Data Allocated With New operator With malloc
        static unsigned char * ConvertFromNewToAlloc(Texture * texture, bool using_alpha = false);

};

#endif // TEXTURE_H
