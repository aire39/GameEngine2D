#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
using namespace boost::python;
///////////////////
//2D Vector Class//
///////////////////

/*////////////////////
//                  //
//  VECTOR CLASSES  //
//   AND FUNCIONS   //
//                  //
////////////////////*/

class Vec2
{
    private:
        float x;
        float y;

    public:

        Vec2()
        {
            x = 0;
            y = 0;
        }


        float getX() const
        {
            return x;
        }

        float getY() const
        {
            return y;
        }


        void setX(float X)
        {
            x = X;
        }

        void setY(float Y)
        {
            y = Y;
        }

        void setXY(float X, float Y)
        {
            x = X;
            y = Y;
        }

};


///////////////////
//3D Vector Class//
///////////////////

class Vec3
{
    private:
        float x;
        float y;
        float z;

    public:
        Vec3()
        {
            x = 0;
            y = 0;
            z = 0;
        }



        float getX() const
        {
            return x;
        }

        float getY() const
        {
            return y;
        }

        float getZ() const
        {
            return z;
        }


        void setX(float X)
        {
            x = X;
        }

        void setY(float Y)
        {
            y = Y;
        }

        void setZ(float Z)
        {
            z = Z;
        }

        void setXY(float X, float Y)
        {
            x = X;
            y = Y;
        }

        void setXYZ(float X, float Y, float Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

};



///////////////////
//4D Vector Class//
///////////////////


class Vec4
{
    private:
        float x;
        float y;
        float z;
        float w;

    public:
        Vec4()
        {
            x = 0;
            y = 0;
            z = 0;
            w = 1;
        }


        float getX() const
        {
            return x;
        }

        float getY() const
        {
            return y;
        }

        float getZ() const
        {
            return z;
        }

        float getW() const
        {
            return w;
        }

        void setX(float X)
        {
            x = X;
        }

        void setY(float Y)
        {
            y = Y;
        }

        void setZ(float Z)
        {
            z = Z;
        }

        void setW(float W)
        {
            w = W;
        }

        void setXY(float X, float Y)
        {
            x = X;
            y = Y;
        }

        void setXYZ(float X, float Y, float Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        void setXYZW(float X, float Y, float Z, float W)
        {
            x = X;
            y = Y;
            z = Z;
            w = W;
        }

};



BOOST_PYTHON_MODULE(pshVectorMath)
{



    class_<Vec4>("vec4", init<>())
        .add_property("x", &Vec4::setX, &Vec4::getX)
        .add_property("y", &Vec4::setY, &Vec4::getY)
        .add_property("z", &Vec4::setZ, &Vec4::getZ)
        .add_property("w", &Vec4::setW, &Vec4::getW)
        ;

    class_<Vec3>("vec3", init<>())
        .add_property("x", &Vec3::setX, &Vec3::getX)
        .add_property("y", &Vec3::setY, &Vec3::getY)
        .add_property("z", &Vec3::setZ, &Vec3::getZ)
        ;


    class_<Vec2>("vec2", init<>())
        .add_property("x", &Vec2::setX, &Vec2::getX)
        .add_property("y", &Vec2::setY, &Vec2::getY)
        ;

}
