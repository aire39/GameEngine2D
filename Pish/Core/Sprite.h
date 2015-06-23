#ifndef SPRITE_H
#define SPRITE_H

#include "../Common/GLee.h"
#include "../Common/primitives.h"
#include "../Common/amath.h"
#include "../Core/Entity.h"
#include "../Core/Animation.h"
#include "../Management/texMng.h"

#include <iostream>
#include <string>
using namespace std;

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/call.hpp>
using namespace boost::python;

struct Sprite : public Entity
{
    private:

        texMng * texture_manager;
        std::vector<Animation*> animation_stock;

        enum{
             VBO = 0, ///Index # for buffer [Vertex]
             INDICES, ///Index # for buffer [Indice]
             TEXC     ///Index # for buffer [TexCoord]
             };

        GLenum drawType;         ///Set for sprite to be dynamic or static

        bool sel;                ///If sprite is selected then it's true else false
        unsigned int vertCount;  ///Number of vertices
        GLuint buffer[3];        ///Name for Vertex Buffer Object, TexCoord Buffer, Indice Buffer
        unsigned int texID;      ///Texture ID
        int textureRepeatX;
        int textureRepeatY;

        CVert3<GLfloat> *verts;    ///Vertex Coordinates
        CTexCoord2<GLfloat> *texC; ///Texture Coordinates
        GLushort *indices;         ///Indices
        bool h_flip;
        bool v_flip;

        void buildSprite();      ///Builds the Sprite Plane
        void buildVBOData();     ///Puts Data into VBO
        void updateVBOData();

    public:
                                        ///Constructor
        Sprite();
                                        ///Copy Constructor
        Sprite(const Sprite& sprite);
                                        ///Destructor
        ~Sprite();
                                        ///Initialize Sprite
        void init();

        void setSelected(bool selected = false); ///Sets Sprite to know it has been selected or unselected.
        bool isSelected();                       ///See if sprite is selected or not

        void picking();
        unsigned char * getColorID();
        void draw();                     ///Draws Sprite Plane
        void draw_raw();
        void draw(float x, float y);     ///Draws Sprite Plane


        unsigned int getShaderID();            ///Get Shader ID.
        void setShaderID(unsigned int sIndex); ///Set Shader ID.

        float getPosX();                       ///Return position
        float getPosY();                       ///Return position


                                                ///To be deprecated at some point (when I change textureviewer)
        void setTexture(unsigned int textureID);///to not use an opengl canvas for rendering the textures and for
        unsigned int getTexID();                ///selection/usage
        unsigned int getTexture();              ///

        void setTextureRepeat(int x=1, int y=1);
        void setTextureRepeatX(int x=1);
        void setTextureRepeatY(int y=1);
        int  getTextureRepeatX();
        int  getTextureRepeatY();
        std::string getTextureSub();

        void flipHorizontalTexCoordinates();
        void flipVerticleTexCoordinates();

        bool isSpriteHFlip();
        bool isSpriteVFlip();

        void operator = (const Sprite& right); ///Overload = operator to make copying over contents easy

        //////////////////////////////////////////////////////////////////////////
        // Experimental

        void AddAnimation( Animation * animation );
        std::string GetAnimationName(int index);
        int GetNumberOfAnimation();

        bool play_animation;
        int  play_index;
        void play_animationSet(int index);
        void UseAnimation(bool b = false);
        void RemoveAnimation(int index);
        void SetAnimationFPS(int i, int fps);
        Animation * GetAnimation(int index);
        Animation * GetAnimation(const char * aname);
        bool IsAnimationPlaying(int index);

        //for changing how textures are called
        std::string texture_name;
        std::string texturesub_name;
        void initTextureManage(texMng * texture_manager);
        void setTexture(std::string texture_name);
        void setTextureSub(std::string texture_name);
        std::string s_getTexture();
        std::string s_getTextureSub();
};


#endif
