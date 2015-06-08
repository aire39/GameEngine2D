#ifndef TEXTURESUB_H
#define TEXTURESUB_H


#include "../Core/TextureBase.h"
#include <vector>
#include <map>
class Texture;

/**
This Class Creates Sub Textures From A Master Texture.
*/

class TextureSub : public TextureBase
{
    private:

        Texture * master_texture;                   //master texture choped from
        std::vector<Texture *> children;            //choped texture
        std::map<std::string, Texture *> mchildren; //choped texture

        int nchopx;     //number of chops x
        int nchopy;     //number of chops y
        bool is_choped; //checks to see if texture is already choped (I only give the user
                        //to choice to chop a texture once unless they delete it and redo the chop).
                                                                                ///Create Sub Textures (Actually Processing Code)
        void chopfunc(int nrow, int ncol, int width_incr=-1, int height_inc=-1);

    public:
                        ///Constructor
        TextureSub();
                        ///Destructor
        ~TextureSub();

        /////////////////////////////
        //Attach And Chop Functions//
        /////////////////////////////
                                                            ///Attach A Master Texture To Work With
        void AttachMasterTexture(Texture * master_texture);
                                                            ///Create Sub Textures From Master Texture
        bool ChopTexture(int nrow, int ncol, int width_incr=-1, int height_inc=-1);

        /////////////////////////////////
        //Get TextureSub Data Functions//
        /////////////////////////////////
                                            ///Get Master Texture
        Texture * GetMasterTexture();
                                            ///Get A Sub Texture By Index
        Texture * GetTexture(int index);
                                            ///Get A Sub Texture By Name [name of master texture + index_number]
        Texture * GetTexture(std::string texture_name);
                                            ///Check To See If TextureSub Has Choped Texture
        bool IsChoped();
                                            ///Get Number Of X Choped Textures
        int GetNumberOfChopedX();
                                            ///Get Number Of Y Choped Textures
        int GetNumberOfChopedY();
                                            ///Number Of Created Sub Textures
        int GetNumberOfSubs();
};

#endif // TEXTURESUB_H
