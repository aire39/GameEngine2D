#include "../Core/Entity.h"

unsigned char Entity::gColorID[3] = {0,0,0};

Entity::Entity()
{
    e_layer = 0;
    color.setXYZ(0.0f, 1.0f, 0.0f);
    rotation_degree = 0.0f;
    scale.setXYZ(1.0f,1.0f,1.0f);
    name = "";


   colorID[0] = gColorID[0];
   colorID[1] = gColorID[1];
   colorID[2] = gColorID[2];

   gColorID[0]++;
   if(gColorID[0] > 255)
   {
        gColorID[0] = 0;
        gColorID[1]++;
        if(gColorID[1] > 255)
        {
             gColorID[1] = 0;
             gColorID[2]++;
        }
   }

   is_renderable = true;

}

Entity::Entity(const Entity& entity)
{
    position = entity.position;
    rotation_degree = entity.rotation_degree;
    scale = entity.scale;
    color = entity.color;
    e_layer = entity.e_layer;
}

Entity::~Entity()
{
    /*
    #ifdef __WXDEBUG__
        std::cout << "Deleting Entity!" << std::endl;
    #endif
    */
}

void Entity::isRenderable(bool render)
{
    is_renderable = render;
}

void Entity::setName(std::string name)
{
    this->name = name;
}

std::string Entity::getName()
{
    return this->name;
}

void Entity::setPosition(float x, float y, float z)
{
    position.setXYZ(x, y, z);
}

void Entity::setPosition(Vec3<float> position)
{
    this->position = position;
}

Vec3<float> Entity::getPosition()
{
    return position;
}

bool Entity::SetScreenPosition(double x, double y, double * camera)
{
    double screen_pos[3];
    double p[16];
    int    v[4];

    glGetDoublev(GL_PROJECTION_MATRIX, p);
    glGetIntegerv(GL_VIEWPORT, v);

    if( gluUnProject(x, y, 0.0,
                     camera,
                     p,
                     v,
                     &screen_pos[0],
                     &screen_pos[1],
                     &screen_pos[2]) )
       {
           //std::cout << screen_pos[0]/10.0f << " , " << screen_pos[1]/10.0f << std::endl;
           position.setXYZ((float)(screen_pos[0]/10.0), (float)(-screen_pos[1]/10.0), 0.0f);
           return 1;
       }
       else
       {
           std::cout << "SetScreenPosition Failed : " << name << std::endl;
       }

    return 0;
}

Vec3<float> Entity::getScreenPosition()
{
    return position;
}

void Entity::setRotation(float degree)
{
    rotation_degree = degree;
}

float Entity::getRotation()
{
    return rotation_degree;
}

void Entity::setScale(float x, float y, float z)
{
    scale.setXYZ(x, y, z);
}

void Entity::setScale(Vec3<float> scale)
{
    this->scale = scale;
}

Vec3<float> Entity::getScale()
{
    return scale;
}

void Entity::setColor(float r, float g, float b, float a)
{
    color.setXYZW(r, g, b, a);
}

void Entity::setColor(Vec4<float> color)
{
    this->color = color;
}

Vec4<float> Entity::getColor()
{
    return color;
}

void Entity::setLayer(int e_layer)
{
    this->e_layer = e_layer;
}

int Entity::getLayer()
{
    return e_layer;
}

void Entity::setTexture(unsigned int textureID)
{
}

void Entity::setTexture(std::string textureName)
{
}

unsigned int Entity::getTexture()
{
    return 0;
}

std::string Entity::s_getTexture()
{
    std::string _str = "";
    return _str;
}

void Entity::picking()
{
    glPointSize(10.0f);
    glColor3ubv(colorID);
    glPushMatrix();
    glTranslatef(position.getX(), position.getY(), position.getZ());
    glBegin( GL_POINTS );
        glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

unsigned char * Entity::getColorID()
{
    return colorID;
}

void Entity::draw_raw()
{
    if(is_renderable)
    {
        glPointSize(10.0f);
        glPushMatrix();
        glTranslatef(position.getX(), position.getY(), position.getZ());
        glBegin( GL_POINTS );
            glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();
        glPopMatrix();
    }
}

void Entity::draw()
{

    if( is_renderable )
    {
        glDisable( GL_TEXTURE_2D );
        glPointSize(10.0f);
        glColor4fv(color.getXYZW());
        glPushMatrix();
        glTranslatef(position.getX(), position.getY(), e_layer+(position.getZ()/1000.0f));
        glBegin( GL_POINTS );
            glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();
        glPopMatrix();
        glEnable( GL_TEXTURE_2D );
    }

}

void Entity::operator=(const Entity & right)
{
    position = right.position;
    rotation_degree = right.rotation_degree;
    scale = right.scale;
    color = right.color;
    e_layer = right.e_layer;
}
