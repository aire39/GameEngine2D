#include "../Core/Text.h"
#include <cstring>

Text::Text(std::string text)
{
    e_layer = 0;
    AllowAnimation = false;

    this->text = text;

    if( !font.Create("./Fonts/verdana.glf", 1) )
        std::cout << "Failed to load font!" << std::endl;
    else
        std::cout << "Load font is success!" << std::endl;

    scale.setXYZ(0.1, 0.1, 0.1);
    color.setXYZ(1.0f, 1.0f, 1.0f);

    animate_text.EndFrame( text.length() );
}

Text::Text(const Text & text_)
{
    position = text_.position;
    rotation_degree = text_.rotation_degree;
    scale    = text_.scale;
    color    = text_.color;
    e_layer  = text_.e_layer;

    text = text_.text;
    font = text_.font;
}

Text::~Text()
{
    font.Destroy();
}

void Text::setText(std::string text)
{
    this->text = text;
    animate_text.EndFrame( text.length() );
}

std::string Text::getText()
{
    return text;
}

void Text::AnimateText(bool b)
{
    AllowAnimation = b;

    if( AllowAnimation )
        animate_text.Start();
    else
        animate_text.Pause();
}

void Text::SetFrameRate(int framerate)
{
    animate_text.SetFPS(framerate);
}

bool Text::IsAnimating()
{
    return AllowAnimation;
}

int Text::GetFrameRate()
{
    return animate_text.GetFrameRate();
}

void Text::picking()
{
    if( is_renderable )
    {
        glColor3ubv( colorID );
        glPushMatrix();

            glTranslatef( position.getX(), position.getY(), position.getZ() );
            glScalef(scale.getX(), scale.getY(), scale.getZ());
            glRotatef( rotation_degree , 0, 0, 1 );

            font.Begin();
            font.DrawString(text, -font.GetTexWidth()/8.0f, font.GetTexWidth()/16.0f);

        glPopMatrix();
    }
}

void Text::draw_raw()
{
    if( is_renderable )
    {
        glPushMatrix();

            glTranslatef( position.getX(), position.getY(), position.getZ() );
            glScalef(scale.getX(), scale.getY(), scale.getZ());
            glRotatef( rotation_degree , 0, 0, 1 );

            font.Begin();
            font.DrawString(text, -font.GetTexWidth()/8.0f, font.GetTexWidth()/16.0f);

        glPopMatrix();
    }
}

void Text::draw()
{
    if( is_renderable )
    {
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();

            glColor3fv( color.getXYZ() );
            glTranslatef( position.getX(), position.getY(), e_layer+(position.getZ()/1000.0f) );
            glScalef(scale.getX(), scale.getY(), scale.getZ());
            glRotatef( rotation_degree , 0, 0, 1 );

            font.Begin();

            if(!AllowAnimation)
                font.DrawString(text, -font.GetTexWidth()/8.0f, font.GetTexWidth()/16.0f);
            else
            {
                animate_text.Play();
                font.DrawString(text.substr(0, (int)animate_text.CurrentFrame()), -font.GetTexWidth()/8.0f, font.GetTexWidth()/16.0f);
            }

        glPopMatrix();
    }
}

void Text::operator=(const Text & right)
{
    position = right.position;
    rotation_degree = right.rotation_degree;
    scale    = right.scale;
    color    = right.color;
    e_layer  = right.e_layer;

    text = right.text;
    font = right.font;
}
