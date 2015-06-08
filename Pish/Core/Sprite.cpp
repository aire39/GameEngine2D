#include "Sprite.h"

Sprite::Sprite()
{
    e_layer = 0;
    vertCount = 4;    //4 vertices for 2 triangles that make 1 square
    //shaderID = 0;     //Set to use default shader (first shader loaded)
    drawType = GL_STATIC_DRAW_ARB;
    sel = false;      //set selection to false (not selected)
    position.setXYZ(0.0f, 0.0f, 0.0f);
    color.setXYZW(1.0f, 1.0f, 1.0f, 1.0f);
    scale.setXYZ(1.0f, 1.0f, 1.0f);
    //setLevel(0);      //Defaults sprites layor level to 0
    texID = 0;

    h_flip = false;
    v_flip = false;

    play_index = 0;
    play_animation = false;

    texture_manager = NULL;
    texture_name =  "";

    textureRepeatX = textureRepeatY = 1;
}

Sprite::Sprite(const Sprite& sprite)
{
    position = sprite.position;
    rotation_degree = sprite.rotation_degree;
    scale    = sprite.scale;
    color    = sprite.color;
    e_layer  = sprite.e_layer;

    animation_stock = sprite.animation_stock;

    texID = sprite.texID;
    texture_name = sprite.texture_name;
    textureRepeatX = sprite.textureRepeatX;
    textureRepeatY = sprite.textureRepeatY;

    if( ((Sprite&)sprite).isSpriteHFlip() )
        flipHorizontalTexCoordinates();

    if( ((Sprite&)sprite).isSpriteVFlip() )
        flipVerticleTexCoordinates();
}

Sprite::~Sprite()
{
    /*
    delete [] verts;
    verts = NULL;

    delete [] texC;
    texC = NULL;

    delete [] indices;
    indices = NULL;
    */

/*
    #ifdef __WXDEBUG__
        std::cout << "Deleting " << this->getName() << "!" << std::endl;
    #endif
*/

    glDeleteBuffersARB(3, buffer);

    for(int i=0; i<(int)animation_stock.size(); i++)
    {
        delete animation_stock[i];
        animation_stock[i] = NULL;
    }
    animation_stock.clear();
}

void Sprite::init()
{
    buildSprite();    //Start building sprite
    buildVBOData();   //start turning data into VBO
}


void Sprite::setSelected(bool selected)
{
    sel = selected;
}

void Sprite::buildSprite()
{
    verts   = new CVert3<GLfloat>[vertCount];
    texC    = new CTexCoord2<GLfloat>[vertCount];
    indices = new GLushort[6];

    verts[0].setPos( 1.0f, -1.0f, 0.0f);
    verts[1].setPos( 1.0f,  1.0f, 0.0f);
    verts[2].setPos(-1.0f,  1.0f, 0.0f);
    verts[3].setPos(-1.0f, -1.0f, 0.0f);

    texC[0].setPos( 1.0f, 0.0f);
    texC[1].setPos( 1.0f, 1.0f);
    texC[2].setPos( 0.0f, 1.0f);
    texC[3].setPos( 0.0f, 0.0f);

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;


    /*

   (-1,1) #3[2]     (1,1) #1[1]
    *-------------*
    | -           |
    |   -         |
    |     -       |
    |       -     |
    |         -   |
    |           - |
    *-------------*
    (-1,-1) #4[3]    (1,-1) #2[0]

    */
}

void Sprite::buildVBOData()
{
    glGenBuffersARB( 3, buffer);

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[VBO]);
    glBufferDataARB( GL_ARRAY_BUFFER_ARB , vertCount*sizeof(*verts), verts, drawType);
    glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );


    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, buffer[INDICES]);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(GLushort)*6 , indices, drawType);
    //Note: For some reason when creating an array of indices sizeof will not report the correct size
    //Therefor at the moment its best to use sizeof(type)*amount to get the real size of an array

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[TEXC]);
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, vertCount*sizeof(*texC),  texC, drawType);
    glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );


    if(verts != NULL)
    {
        delete [] verts;
        verts = NULL;
    }

    //delete [] texC;
    //texC = NULL;

    if(indices != NULL)
    {
        delete [] indices;
        indices = NULL;
    }
}

void Sprite::updateVBOData()
{
    if(verts != NULL)
    {
        glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[VBO]);
        glBufferSubDataARB( GL_ARRAY_BUFFER_ARB , 0, vertCount*sizeof(*verts), verts);
    }

    if( indices != NULL )
    {
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, buffer[INDICES]);
        glBufferSubDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0, sizeof(GLushort)*6 , indices);
        //Note: For some reason when creating an array of indices sizeof will not report the correct size
        //Therefor at the moment its best to use sizeof(type)*amount to get the real size of an array
    }

    if( texC != NULL )
    {
        glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[TEXC]);
        glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, 0, vertCount*sizeof(*texC),  texC);
        //glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );
    }
}

unsigned char * Sprite::getColorID()
{
    return colorID;
}


void Sprite::picking()
{
    if( is_renderable )
    {

        glPushMatrix();

        glColor3f(colorID[0]/255.0f, colorID[1]/255.0f, colorID[2]/255.0f);
        glTranslatef(position.getX(), position.getY(), position.getZ() );
        glRotatef(rotation_degree, 0, 0, 1);
        glScalef(scale.getX(), scale.getY(), scale.getZ());


        if(glIsEnabled( GL_VERTEX_ARRAY ))
        {
            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[TEXC]);
            glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[VBO]);
            glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, buffer[INDICES]);

            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        }
        else
        {
            glEnableClientState( GL_VERTEX_ARRAY );               //Enable usage of VBO's
            glEnableClientState( GL_TEXTURE_COORD_ARRAY );        //Enable usage of VBO's with textures coords

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[TEXC]);
            glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[VBO]);
            glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, buffer[INDICES]);

            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);//draw vertices/sprite

            glDisableClientState( GL_VERTEX_ARRAY );              //turn off vbo
            glDisableClientState( GL_TEXTURE_COORD_ARRAY );       //turn off vbo with texture coords
        }

        glPopMatrix();

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    }
}

void Sprite::draw()
{

    if( is_renderable )
    {
        glPushMatrix();

        if( play_animation )
        {
            animation_stock[ play_index ]->Start();
            animation_stock[ play_index ]->Play();

            if( (texture_manager != NULL) && (animation_stock.size() > 0) )
            {
                if( animation_stock[ play_index ]->s_CurrentFrame2().empty() )
                {
                    if( texture_manager->GetTexture( animation_stock[ play_index ]->s_CurrentFrame().c_str() ) != NULL )
                        texture_manager->GetTexture( animation_stock[ play_index ]->s_CurrentFrame().c_str() )->UseTexture();
                    else
                        glBindTexture(GL_TEXTURE_2D, 0);
                }

                else
                    glBindTexture( GL_TEXTURE_2D, texture_manager->GetTexture( animation_stock[ play_index ]->s_CurrentFrame().c_str() )->GetTextureSub()->GetTexture( animation_stock[ play_index ]->s_CurrentFrame2().c_str() )->GetTextureID() );
            }
        }
        else
        {

            if( texture_manager != NULL )
            {
                if( texture_manager->GetTexture( texture_name.c_str() ) != NULL )
                {
                    if( texturesub_name.empty() )
                        texture_manager->GetTexture( texture_name.c_str() )->UseTexture();
                    else if( !texturesub_name.empty() && (texture_manager->GetTexture( texture_name.c_str() )->GetTextureSub() != NULL ) )
                        texture_manager->GetTexture( texture_name.c_str() )->GetTextureSub()->GetTexture(texturesub_name.c_str())->UseTexture();
                    else
                        texturesub_name.clear();
                }
                else
                    glBindTexture(GL_TEXTURE_2D, 0);
            }
            else
                glBindTexture( GL_TEXTURE_2D, 0);

            glMatrixMode( GL_TEXTURE );
            glLoadIdentity();
            glScalef(textureRepeatX, textureRepeatY, 1.0);
            glMatrixMode( GL_MODELVIEW );
        }

        glColor4fv(color.getXYZW());
        glTranslatef(position.getX(), position.getY(), e_layer+(position.getZ()/1000.0f) );
        glRotatef(rotation_degree, 0, 0, 1);
        glScalef(scale.getX(), scale.getY(), scale.getZ());


        if(glIsEnabled( GL_VERTEX_ARRAY ))
        {
            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[TEXC]);
            glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[VBO]);
            glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, buffer[INDICES]);

            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        }
        else
        {
            glEnableClientState( GL_VERTEX_ARRAY );               //Enable usage of VBO's
            glEnableClientState( GL_TEXTURE_COORD_ARRAY );        //Enable usage of VBO's with textures coords

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[TEXC]);
            glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[VBO]);
            glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, buffer[INDICES]);

            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);//draw vertices/sprite

            glDisableClientState( GL_VERTEX_ARRAY );              //turn off vbo
            glDisableClientState( GL_TEXTURE_COORD_ARRAY );       //turn off vbo with texture coords
        }

        glPopMatrix();

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    }

}

void Sprite::draw_raw()
{
    if( is_renderable )
    {

        glPushMatrix();

        glTranslatef(position.getX(), position.getY(), e_layer+(position.getZ()/1000.0f) );
        glRotatef(rotation_degree, 0, 0, 1);
        glScalef(scale.getX(), scale.getY(), scale.getZ());

        if(glIsEnabled( GL_VERTEX_ARRAY ))
        {
            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[TEXC]);
            glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[VBO]);
            glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, buffer[INDICES]);

            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        }
        else
        {
            glEnableClientState( GL_VERTEX_ARRAY );               //Enable usage of VBO's
            glEnableClientState( GL_TEXTURE_COORD_ARRAY );        //Enable usage of VBO's with textures coords

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[TEXC]);
            glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, buffer[VBO]);
            glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, buffer[INDICES]);

            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);//draw vertices/sprite

            glDisableClientState( GL_VERTEX_ARRAY );              //turn off vbo
            glDisableClientState( GL_TEXTURE_COORD_ARRAY );       //turn off vbo with texture coords
        }

        glPopMatrix();

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    }
}

void Sprite::draw(float x, float y)
{
    if( is_renderable )
    {
        glBindBufferARB( GL_ARRAY_BUFFER, buffer[VBO]);
        glBindBufferARB( GL_ARRAY_BUFFER, buffer[TEXC]);
        glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);

        glPushMatrix();

        position.setXY(x, y);
        glTranslatef(position.getX(), position.getY(), e_layer+(position.getZ()/1000.0f));
        glRotatef(rotation_degree, 0, 0, 1);
        glScalef(scale.getX(), scale.getY(), scale.getZ());

        if(glIsEnabled( GL_VERTEX_ARRAY ))
            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        else
        {
            glEnableClientState( GL_VERTEX_ARRAY );               //Enable usage of VBO's
            glEnableClientState( GL_TEXTURE_COORD_ARRAY );        //Enable usage of VBO's with textures coords

            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);//draw vertices/sprite

            glDisableClientState( GL_VERTEX_ARRAY );              //turn off vbo
            glDisableClientState( GL_TEXTURE_COORD_ARRAY );       //turn off vbo with texture coords
        }

        glPopMatrix();

    }
}

float  Sprite::getPosX()
{
    return position.getX();
}


float  Sprite::getPosY()
{
    return position.getY();
}

bool Sprite::isSelected()
{
    return sel;
}

void Sprite::setTexture(unsigned int textureID)
{
    texID = textureID;
}


unsigned int Sprite::getTexID()
{
    return texID;
}


unsigned int Sprite::getTexture()
{
    return texID;
}

void Sprite::setTextureRepeat(int x, int y)
{
    if( x > 0 )
        textureRepeatX = x;
    else
        textureRepeatX = 1;

    if( y > 0 )
        textureRepeatY = y;
    else
        textureRepeatY = 1;
}

void Sprite::setTextureRepeatX(int x)
{
    if( x > 0 )
        textureRepeatX = x;
    else
        textureRepeatX = 1;
}

void Sprite::setTextureRepeatY(int y)
{
    if( y > 0 )
        textureRepeatY = y;
    else
        textureRepeatY = 1;
}

int Sprite::getTextureRepeatX()
{
    return textureRepeatX;
}

int Sprite::getTextureRepeatY()
{
    return textureRepeatY;
}

std::string Sprite::getTextureSub()
{
    return texturesub_name;
}

void Sprite::flipHorizontalTexCoordinates()
{
    CTexCoord2<GLfloat> temp;

    temp = texC[3];
    texC[3] = texC[0];
    texC[0] = temp;

    temp = texC[2];
    texC[2] = texC[1];
    texC[1] = temp;

    updateVBOData();

    h_flip ^= true;
}

bool Sprite::isSpriteHFlip()
{
    return h_flip;
}

void Sprite::flipVerticleTexCoordinates()
{
    CTexCoord2<GLfloat> temp;

    temp = texC[1];
    texC[1] = texC[0];
    texC[0] = temp;

    temp = texC[3];
    texC[3] = texC[2];
    texC[2] = temp;

    updateVBOData();

    v_flip ^= true;
}

bool Sprite::isSpriteVFlip()
{
    return v_flip;
}

//////////////////////Overloaded Operators//////////////////////////////////////////

//Still requires a call to init
void Sprite::operator=(const Sprite& right)
{
    //buffer[VBO] = right.buffer[VBO];
    //buffer[INDICES] = right.buffer[INDICES];
    //buffer[TEXC] = right.buffer[TEXC];
    //verts = right.verts;
    //sel = right.sel;
    //vertCount = right.vertCount;

    //name = right.name;
    position = right.position;
    rotation_degree = right.rotation_degree;
    scale    = right.scale;
    color    = right.color;
    e_layer  = right.e_layer;

    animation_stock = right.animation_stock;

    texID = right.texID;
    texture_name = right.texture_name;
    textureRepeatX = right.textureRepeatX;
    textureRepeatY = right.textureRepeatY;

    if( ((Sprite&)right).isSpriteHFlip() )
        flipHorizontalTexCoordinates();

    if( ((Sprite&)right).isSpriteVFlip() )
        flipVerticleTexCoordinates();

}


//////////////////////////////////////////////////////////////////////////////////////////

void Sprite::AddAnimation(Animation * animation)
{
    animation_stock.push_back(animation);
}

std::string Sprite::GetAnimationName(int index)
{
    return animation_stock[index]->AnimName();
}

int Sprite::GetNumberOfAnimation()
{
    return animation_stock.size();
}

void Sprite::play_animationSet(int index)
{
    play_index = index;

    if( play_index > (int)animation_stock.size()-1 )
    {
        play_index = 0;
        std::cout << "Set Doesn't Exist!" << std::endl;
    }
}

bool Sprite::IsAnimationPlaying(int index)
{
    if( ( index == play_index ) && ( play_animation == true ) )
        return true;

    return false;
}

void Sprite::UseAnimation(bool b)
{
    play_animation = b;

    if( animation_stock.size() <= 0 )
        play_animation = false;
}

void Sprite::RemoveAnimation(int index)
{
    delete animation_stock[index];
    animation_stock[index] = NULL;
    animation_stock.erase( animation_stock.begin()+index );
}

void Sprite::SetAnimationFPS(int i, int fps)
{
    animation_stock[i]->SetFPS(fps);
}

Animation * Sprite::GetAnimation(int index)
{
    if( (index >= 0) && (index < (int)animation_stock.size()) )
       return animation_stock[index];

    return 0;
}

Animation * Sprite::GetAnimation(const char * aname)
{
    for(int i=0; i<(int)animation_stock.size(); i++)
        if( animation_stock[i]->AnimName().compare(aname) == 0 )
            return animation_stock[i];

    return 0;
}

void Sprite::setTexture(std::string texture_name)
{
    this->texture_name = texture_name;
}

void Sprite::setTextureSub(std::string texture_name)
{
    this->texturesub_name = texture_name;
}

void Sprite::initTextureManage( texMng * texture_manager )
{
    this->texture_manager = texture_manager;
}

std::string Sprite::s_getTexture()
{
    return texture_name;
}

std::string Sprite::s_getTextureSub()
{
    return texturesub_name;
}
