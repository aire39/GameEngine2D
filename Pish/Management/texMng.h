#ifndef TEXMNG_H
#define TEXMNG_H

#include "../Common/GLee.h"

#include "../Core/Texture.h"
#include "../Core/TextureSub.h"
#include "../Core/TextureSheet.h"
#include <fstream>
#include <string>
#include <iostream>
#include <map>

using namespace std;

class texMng
{
    private:

        std::vector<Texture * > vTextures;          //holds all textures which is referenced by index
        std::vector<TextureSub * > vTextureSubs;    //holds all texturesubs which is referenced by index
        std::vector<TextureBase *> vAllTextures;    //holds all textures and texturesubs which is referenced by index

        std::map<std::string, Texture * > mTextures;        //holds all textures which is referenced by name
        std::map<std::string, TextureSub * > mTextureSubs;  //holds all texture subs which is referenced by name
        std::map<std::string, TextureBase *> mAllTextures;  //holds all textures and texturesubs which is referenced by name

        std::string ctexture_name;        //selected textures name
        std::string ctexturesub_name;     //selected textures sub texture name

        std::string recent;               //Recently added or deleted

    public:
                                          ///Constructor
        texMng();
                                          ///Copy Contructor
        texMng(const texMng & right);
                                          ///Destructor
        ~texMng();

        ////////////////////////
        //Add/Remove Functions//
        ////////////////////////
                                                                    ///Add texture by path
        void addTexture(TextureBase * texture);
                                                                    ///Add texture by path
        Texture * addTexture(const char * texture_path, bool key=false);
                                                                    ///Remove texture by index
        void removeTexture(int texture_Index);
                                                              ///Remove texture by name
        void removeTexture(const char * texture_name);
                                                              ///Remove all textures
        void removeAllTextures();

        /////////////////
        //Get Functions//
        /////////////////
                                                            ///Get Texture By Name
        Texture * GetTexture(const char * texture_name);
                                                            ///Get Texture By Index
        Texture * GetTexture(int texture_index);

                                                            ///Get Number Of Textures
        int GetNumberOfTextures();
                                                            ///Get Number Of TextureSubs [May Bot Work Correctly ATM]
        int GetNumberOfTextureSubs();
                                                            ///Get Number Of All Textures [May Bot Work Correctly ATM]
        int GetNumberOfAllTextures();

        ///////////////////////
        //Selection Functions//
        ///////////////////////
                                                            ///Get The Selected Texture From The Manager
        std::string GetSelectedTexture();
                                                            ///Get The Selected Textures Sub From The Manager
        std::string GetSelectedTexture2();
                                                            ///Set The Selected Texture From The Manager
        void SetSelectedTexture(std::string texture_name);
                                                            ///Set The Selected Textures Sub From The Manager
        void SetSelectedTexture2(std::string texture_name);

                                                            ///Get Recently Added/Deleted Textures Name
        std::string GetRecent();

        //////////////
        //////////////
        //////////////

        texMng operator= (const texMng & right);

};

#endif
