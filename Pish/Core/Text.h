#ifndef TEXT_H
#define TEXT_H

#include "../Core/Entity.h"
#include "../Common/glfont2.h"
#include "../Core/Animation.h"
#include <string>

using namespace glfont;

class Text : public Entity
{
    private:
        AnimationBase animate_text; //controls animation for text
        std::string text;           //text to rendered
        GLFont font;                //used to draw fonts into opengl [need a better solution than this]

        bool AllowAnimation;
    public:
                                ///Constructor
        Text(std::string="");
                                ///Copy Constructor
        Text(const Text & text_);
                                ///Destructor
        ~Text();

        ////////////
        //Set Text//
        ////////////
                                        ///Set Text
        void setText(std::string text);
                                        ///Get Text
        std::string getText();

        //////////////////////
        //Set Animation Data//
        //////////////////////
                                    ///Enable/Disable Text Animation
        void AnimateText(bool b);
                                    ///Set Animation Frame Rate [Default At 15]
        void SetFrameRate(int framerate=15);

        //////////////////////
        //Get Animation Data//
        //////////////////////
                            ///Check If Animation Playing
        bool IsAnimating();
                            ///Get Animation Frame Rate
        int  GetFrameRate();

        ///////////////
        //Object Draw//
        ///////////////
                        ///Draw Object In Picking Mode [Draws Text Objects By Their Color Index]
        void picking();
                        ///Pure Draw No Other GL Function By Those That Draw Text Object To Screen
        void draw_raw();
                        ///Draw Text Object [Will Draw As If There Was A Texture Or Animation]
        void draw();

        void operator= (const Text & right);
};

#endif // TEXT_H
