#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "../Common/glee.h"
#include <gl/glu.h>
#include "../Common/amath.h"
#include <string>

using namespace vector_math;

class Entity
{
    private:

        static unsigned char gColorID[3];

    protected:

        std::string name;
        Vec4<float> color;
        Vec3<float> position;
        Vec3<float> scale;
        float rotation_degree;
        int e_layer;
        unsigned char colorID[3];

        bool is_renderable;

    public:
        Entity();
        Entity(const Entity& entity);
        virtual ~Entity();

        virtual void setName(std::string name);
        virtual std::string getName();

        virtual void init(){}

        virtual void isRenderable(bool render = true);

        virtual void setPosition(float x=0.0f, float y=0.0f, float z=0.0f);
        virtual void setPosition( Vec3<float> position );
        virtual Vec3<float> getPosition();

        virtual bool SetScreenPosition(double x, double y, double * camera);
        virtual Vec3<float> getScreenPosition();

        virtual void setRotation(float degree = 0.0f);
        virtual float getRotation();

        virtual void setScale(float x=1.0f, float y=1.0f, float z=1.0f);
        virtual void setScale( Vec3<float> scale );
        virtual Vec3<float> getScale();

        virtual void setColor(float r=1.0f, float g=1.0f, float b=1.0f, float a=1.0f);
        virtual void setColor(Vec4<float> color);
        virtual Vec4<float> getColor();

        virtual void setLayer(int e_layer=0);
        virtual int getLayer();

        virtual void setTexture(unsigned int textureID=0);
        virtual void setTexture(std::string textureName="");
        virtual unsigned int  getTexture();
        virtual std::string s_getTexture();

        virtual void picking();
        virtual unsigned char * getColorID();
        virtual void draw_raw();
        virtual void draw();

        virtual void operator= (const Entity & right);

};



#endif // ENTITY_H
