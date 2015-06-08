#ifndef AMATH_H
#define AMATH_H

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
///////////////////
//2D Vector Class//
///////////////////

#define PI 3.14159265
#define EPSILON 0.0001


/*////////////////////
//                  //
//  VECTOR CLASSES  //
//   AND FUNCTION   //
//                  //
////////////////////*/
namespace vector_math{


template <class T>
class Vec3;
template <class T>
class Vec4;


template<class T = float>
class Vec2
{
    private:
        T components[2];

    public:

        Vec2<T>()
        {
            components[0] = 0;
            components[1] = 0;
        }


        template<class U>
        Vec2<T>(const Vec2<U> & v)
        {
            components[0] = v.components[0];
            components[1] = v.components[1];
        }


        Vec2<T>(T x, T y)
        {
            this->components[0] = x;
            this->components[1] = y;
        }


        template <class U>
        Vec2<T>(const U& right)
        {
            components[0] = right;
            components[1] = right;
        }


        template <class U>
        Vec2<T>(const Vec3<U>& right)
        {
            components[0] = right.getX();
            components[1] = right.getY();
        }


        template<class U>
        Vec2<T> operator = (const Vec2<U>& right)
        {
            components[0] = right.components[0];
            components[1] = right.components[1];

            return *this;
        }


        template<class U>
        Vec2<T> operator = (const Vec3<U>& right)
        {
            components[0] = right.getX();
            components[1] = right.getY();

            return *this;
        }


        template<class U>
        Vec2<T> operator = (const Vec4<U>& right)
        {
            components[0] = right.getX();
            components[1] = right.getY();

            return *this;
        }


        template<class U>
        Vec2<T> operator + (const Vec2<U>& right)
        {
            Vec2<T> tmp;
            T x_ = components[0], y_ = components[1];

            x_ += right.components[0];
            y_ += right.components[1];

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<class U>
        Vec2<T> operator + (const U& right)
        {
            Vec2<T> tmp;
            T x_ = components[0], y_ = components[1];

            x_ += right;
            y_ += right;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<class U>
        Vec2<T> operator += (const Vec2<U>& right)
        {
            components[0] += right.components[0];
            components[1] += right.components[1];

            return *this;
        }


        template<class U>
        Vec2<T> operator += (const U& right)
        {
            components[0] += right;
            components[1] += right;

            return *this;
        }


        template<class U>
        Vec2<T> operator - (const Vec2<U>& right)
        {
            Vec2<T> tmp;
            T x_ = components[0], y_ = components[1];

            x_ -= right.components[0];
            y_ -= right.components[1];

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<class U>
        Vec2<T> operator - (const U& right)
        {
            Vec2<T> tmp;
            T x_ = components[0], y_ = components[1];

            x_ -= right;
            y_ -= right;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<class U>
        Vec2<T> operator -= (const Vec2<U>& right)
        {
            components[0] -= right.components[0];
            components[1] -= right.components[1];

            return *this;
        }


        template<class U>
        Vec2<T> operator -= (const U& right)
        {
            components[0] -= right;
            components[1] -= right;

            return *this;
        }


        Vec2<T> operator - ()
        {
            Vec2<T> tmp;
            T x_ = components[0], y_ = components[1];

            x_ *= -1;
            y_ *= -1;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<class U>
        Vec2<T> operator * (const Vec2<U>& right)
        {
            Vec2<T> tmp;
            T x_ = components[0], y_ = components[1];

            x_ *= right.components[0];
            y_ *= right.components[1];

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<class U>
        Vec2<T> operator * (const U& right)
        {
            Vec2<T> tmp;
            T x_ = components[0], y_ = components[1];

            x_ *= right;
            y_ *= right;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<class U>
        Vec2<T> operator *= (const Vec2<U>& right)
        {
            components[0] *= right.components[0];
            components[1] *= right.components[1];

            return *this;
        }


        template<class U>
        Vec2<T> operator *= (const U& right)
        {
            components[0] *= right;
            components[1] *= right;

            return *this;
        }


        template<class U>
        Vec2<T> operator / (const Vec2<U>& right)
        {
            Vec2<T> tmp;
            T x_ = components[0], y_ = components[1];

            x_ /= right.components[0];
            y_ /= right.components[1];

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<class U>
        Vec2<T> operator / (const U& right)
        {
            Vec2<T> tmp;
            T x_ = components[0], y_ = components[1];

            x_ /= right;
            y_ /= right;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<class U>
        Vec2<T> operator /= (const U& right)
        {
            components[0] /= right;
            components[1] /= right;

            return *this;
        }


        template<class U>
        Vec2<T> operator /= (const Vec2<U>& right)
        {
            components[0] /= right.components[0];
            components[1] /= right.components[1];

            return *this;
        }


        T getX() const
        {
            return components[0];
        }

        T getY() const
        {
            return components[1];
        }

        const T * getXY()
        {
            float temp[2];

            temp[0] = components[0];
            temp[1] = components[1];

            return temp;
        }

        void setX(T X)
        {
            components[0] = X;
        }

        void setY(T Y)
        {
            components[1] = Y;
        }

        void setXY(T X, T Y)
        {
            components[0] = X;
            components[1] = Y;
        }

};


///////////////////
//3D Vector Class//
///////////////////

template<class T = float>
class Vec3
{
    private:

        T components[3];

    public:
        Vec3<T>()
        {
            components[0] = 0;
            components[1] = 0;
            components[2] = 0;
        }


        Vec3<T>(T x, T y, T z)
        {
            this->components[0] = x;
            this->components[1] = y;
            this->components[2] = z;
        }


        template <class U>
        Vec3<T>(const Vec3<U>& right)
        {
            components[0] = right.components[0];
            components[1] = right.components[1];
            components[2] = right.components[2];
        }


        template <class U>
        bool operator == (const U& right)
        {
            if(components[0] == right && components[1] == right && components[2] == right)
                return true;
            else
                return false;
        }


        template <class U>
        Vec3<T> operator = (const U& right)
        {
            components[0] = right;
            components[1] = right;
            components[2] = right;

            return *this;
        }


        template <class U>
        Vec3<T> operator = (const Vec3<U>& right)
        {
            components[0] = right.components[0];
            components[1] = right.components[1];
            components[2] = right.components[2];

            return *this;
        }


        template <class U>
        Vec3<T> operator = (const Vec2<U>& right)
        {
            this->components[0] = right.getX();
            this->components[1] = right.getY();

            return *this;
        }


        template <class U>
        Vec3<T> operator = (const Vec4<U>& right)
        {
            components[0] = right.getX();
            components[1] = right.getY();
            components[2] = right.getZ();

            return *this;
        }


        template <class U>
        Vec3<T> operator + (const Vec3<U>& right)
        {
            Vec3<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2];

            x_ += right.components[0];
            y_ += right.components[1];
            z_ += right.components[2];

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <class U>
        Vec3<T> operator + (const U& right)
        {
            Vec3<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2];

            x_ += right;
            y_ += right;
            z_ += right;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <class U>
        Vec3<T> operator += (const Vec3<U>& right)
        {
            components[0] += right.components[0];
            components[1] += right.components[1];
            components[2] += right.components[2];

            return *this;
        }


        template <class U>
        Vec3<T> operator += (const U& right)
        {
            components[0] += right;
            components[1] += right;
            components[2] += right;

            return *this;
        }


        template <class U>
        Vec3<T> operator - (const Vec3<U>& right)
        {
            Vec3<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2];

            x_ -= right.components[0];
            y_ -= right.components[1];
            z_ -= right.components[2];

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <class U>
        Vec3<T> operator - (const U& right)
        {
            Vec3<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2];

            x_ -= right;
            y_ -= right;
            z_ -= right;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <class U>
        Vec3<T> operator -= (const Vec3<U>& right)
        {
            components[0] -= right.components[0];
            components[1] -= right.components[1];
            components[2] -= right.components[2];

            return *this;
        }


        template <class U>
        Vec3<T> operator -= (const U& right)
        {
            components[0] -= right;
            components[1] -= right;
            components[2] -= right;

            return *this;
        }


        Vec3<T> operator - ()
        {
            Vec3<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2];

            x_ *= -1;
            y_ *= -1;
            z_ *= -1;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <class U>
        Vec3<T> operator * (const Vec3<U>& right)
        {
            Vec3<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2];

            x_ *= right.components[0];
            y_ *= right.components[1];
            z_ *= right.components[2];

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <class U>
        Vec3<T> operator * (const U& right)
        {
            Vec3<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2];

            x_ *= right;
            y_ *= right;
            z_ *= right;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <class U>
        Vec3<T> operator *= (const Vec3<U>& right)
        {
            components[0] *= right.components[0];
            components[1] *= right.components[1];
            components[2] *= right.components[2];

            return *this;
        }


        template <class U>
        Vec3<T> operator *= (const U& right)
        {
            components[0] *= right;
            components[1] *= right;
            components[2] *= right;

            return *this;
        }


        template <class U>
        Vec3<T> operator / (const Vec3<U>& right)
        {
            Vec3<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2];

            x_ /= right.components[0];
            y_ /= right.components[1];
            z_ /= right.components[2];

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <class U>
        Vec3<T> operator / (const U& right)
        {
            Vec3<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2];

            x_ /= right;
            y_ /= right;
            z_ /= right;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <class U>
        Vec3<T> operator /= (const U& right)
        {
            components[0] /= right;
            components[1] /= right;
            components[2] /= right;

            return *this;
        }


        template <class U>
        Vec3<T> operator /= (const Vec3<U>& right)
        {
            components[0] /= right.components[0];
            components[1] /= right.components[1];
            components[2] /= right.components[2];

            return *this;
        }


        bool operator < (const Vec3<T> & right)
        {
            bool b = true;

            if( components[0] < right.components[0] && components[1] < right.components[1] && components[2] < right.components[2])
                b = false;

            return b;

        }


        bool operator > (const Vec3<T> & right)
        {
            bool b = true;

            if( components[0] < right.components[0] && components[1] < right.components[1] && components[2] < right.components[2])
                b = false;

            return b;

        }

        T getX() const
        {
            return components[0];
        }

        T getY() const
        {
            return components[1];
        }

        T getZ() const
        {
            return components[2];
        }

        const T * getXY()
        {
            float temp[2];
            temp[0] = components[0];
            temp[1] = components[1];

            return temp;
        }

        const T * getXYZ()
        {
            float temp[3];
            temp[0] = components[0];
            temp[1] = components[1];
            temp[2] = components[2];

            return temp;
        }

        void setX(T X)
        {
            components[0] = X;
        }

        void setY(T Y)
        {
            components[1] = Y;
        }

        void setZ(T Z)
        {
            components[2] = Z;
        }

        void setXY(T X, T Y)
        {
            components[0] = X;
            components[1] = Y;
        }

        void setXYZ(T X, T Y, T Z)
        {
            components[0] = X;
            components[1] = Y;
            components[2] = Z;
        }

};



///////////////////
//4D Vector Class//
///////////////////

template<class T = float>
class Vec4
{
    private:

        T components[4];

    public:
        Vec4<T>()
        {
            components[0] = 0;
            components[1] = 0;
            components[2] = 0;
            components[3] = 1;
        }


        Vec4<T>(T x, T y, T z, T w)
        {
            this->components[0] = x;
            this->components[1] = y;
            this->components[2] = z;
            this->components[3] = w;
        }


        template <class U>
        Vec4<T>(const Vec4<U>& right)
        {
            components[0] = right.components[0];
            components[1] = right.components[1];
            components[2] = right.components[2];
            components[3] = right.components[3];
        }

        template <class U>
        Vec4<T> operator = (const U& right)
        {
            components[0] = right;
            components[1] = right;
            components[2] = right;
            components[3] = right;

            return *this;
        }

        template <class U>
        Vec4<T> operator = (const Vec4<U>& right)
        {
            components[0] = right.components[0];
            components[1] = right.components[1];
            components[2] = right.components[2];
            components[3] = right.components[3];

            return *this;
        }


        template <class U>
        Vec4<T> operator = (const Vec2<U>& right)
        {
            components[0] = right.getX();
            components[1] = right.getY();

            return *this;
        }


        template <class U>
        Vec4<T> operator = (const Vec3<U>& right)
        {
            components[0] = right.getX();
            components[1] = right.getY();
            components[2] = right.getZ();

            return *this;
        }


        template <class U>
        Vec4<T> operator + (const Vec4<U>& right)
        {
            Vec4<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2], w_ = components[3];

            x_ += right.components[0];
            y_ += right.components[1];
            z_ += right.components[2];
            w_ += right.components[3];

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <class U>
        Vec4<T> operator + (const U& right)
        {
            Vec4<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2], w_ = components[3];

            x_ += right;
            y_ += right;
            z_ += right;
            w_ += right;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <class U>
        Vec4<T> operator += (const Vec4<U>& right)
        {
            components[0] += right.components[0];
            components[1] += right.components[1];
            components[2] += right.components[2];
            components[3] += right.components[3];

            return *this;
        }


        template <class U>
        Vec4<T> operator += (const U& right)
        {
            components[0] += right;
            components[1] += right;
            components[2] += right;
            components[3] += right;

            return *this;
        }


        template <class U>
        Vec4<T> operator - (const Vec4<U>& right)
        {
            Vec4<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2], w_ = components[3];

            x_ -= right.components[0];
            y_ -= right.components[1];
            z_ -= right.components[2];
            w_ -= right.components[3];

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <class U>
        Vec4<T> operator - (const U& right)
        {
            Vec4<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2], w_ = components[3];

            x_ -= right;
            y_ -= right;
            z_ -= right;
            w_ -= right;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <class U>
        Vec4<T> operator -= (const Vec4<U>& right)
        {
            components[0] -= right.components[0];
            components[1] -= right.components[1];
            components[2] -= right.components[2];
            components[3] -= right.components[3];

            return *this;
        }


        template <class U>
        Vec4<T> operator -= (const U& right)
        {
            components[0] -= right;
            components[1] -= right;
            components[2] -= right;
            components[3] -= right;

            return *this;
        }


        Vec4<T> operator - ()
        {
            Vec4<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2], w_ = components[3];

            x_ *= -1;
            y_ *= -1;
            z_ *= -1;
            //w_ *= -1;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <class U>
        Vec4<T> operator * (const Vec4<U>& right)
        {
            Vec4<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2], w_ = components[3];

            x_ *= right.components[0];
            y_ *= right.components[1];
            z_ *= right.components[2];
            w_ *= right.components[3];

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <class U>
        Vec4<T> operator * (const U& right)
        {
            Vec4<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2], w_ = components[3];

            x_ *= right;
            y_ *= right;
            z_ *= right;
            w_ *= right;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <class U>
        Vec4<T> operator *= (const Vec4<U>& right)
        {
            components[0] *= right.components[0];
            components[1] *= right.components[1];
            components[2] *= right.components[2];
            components[3] *= right.components[3];

            return *this;
        }


        template <class U>
        Vec4<T> operator *= (const U& right)
        {
            components[0] *= right;
            components[1] *= right;
            components[2] *= right;
            components[3] *= right;

            return *this;
        }


        template <class U>
        Vec4<T> operator / (const Vec4<U>& right)
        {
            Vec4<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2], w_ = components[3];

            x_ /= right.components[0];
            y_ /= right.components[1];
            z_ /= right.components[2];
            w_ /= right.components[3];

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <class U>
        Vec4<T> operator / (const U& right)
        {
            Vec4<T> tmp;
            T x_ = components[0], y_ = components[1], z_ = components[2], w_ = components[3];

            x_ /= right;
            y_ /= right;
            z_ /= right;
            w_ /= right;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <class U>
        Vec4<T> operator /= (const U& right)
        {
            components[0] /= right;
            components[1] /= right;
            components[2] /= right;
            components[3] /= right;

            return *this;
        }


        template <class U>
        Vec4<T> operator /= (const Vec4<U>& right)
        {
            components[0] /= right.components[0];
            components[1] /= right.components[1];
            components[2] /= right.components[2];
            components[3] /= right.components[3];

            return *this;
        }


        T getX() const
        {
            return components[0];
        }

        T getY() const
        {
            return components[1];
        }

        T getZ() const
        {
            return components[2];
        }

        T getW() const
        {
            return components[3];
        }

        const T * getXY()
        {
			float * temp = new float[2];
            temp[0] = components[0];
            temp[1] = components[1];

            return temp;
        }

        const T * getXYZ()
        {
			float * temp = new float[3];
            temp[0] = components[0];
            temp[1] = components[1];
            temp[2] = components[2];

            return temp;
        }

        const T * getXYZW()
        {
            float * temp = new float[4];
            temp[0] = components[0];
            temp[1] = components[1];
            temp[2] = components[2];
            temp[3] = components[3];

            return temp;
        }

        void setX(T X)
        {
            components[0] = X;
        }

        void setY(T Y)
        {
            components[1] = Y;
        }

        void setZ(T Z)
        {
            components[2] = Z;
        }

        void setW(T W)
        {
            components[3] = W;
        }

        void setXY(T X, T Y)
        {
            components[0] = X;
            components[1] = Y;
        }

        void setXYZ(T X, T Y, T Z)
        {
            components[0] = X;
            components[1] = Y;
            components[2] = Z;
        }

        void setXYZW(T X, T Y, T Z, T W)
        {
            components[0] = X;
            components[1] = Y;
            components[2] = Z;
            components[3] = W;
        }

};

//////////////////
//MATH FUNCTIONS//
//////////////////
template <class T>
inline T Magnitude(Vec2<T> v)
{
    T r = 0;

    r = (v.getX()*v.getX()) + (v.getY()*v.getY());

    return sqrtf(r);
}

template <class T, class U>
inline T Magnitude(Vec2<U> v)
{
    T r = 0;

    r = (v.getX()*v.getX()) + (v.getY()*v.getY());

    return sqrtf(r);
}



template <class T, class U>
inline T Magnitude(Vec3<U> v)
{
    T r = 0;

    r = (v.getX()*v.getX()) + (v.getY()*v.getY()) + (v.getZ()*v.getZ());

    return sqrtf(r);
}
template <class T>
inline T Magnitude(Vec3<T> v)
{
    T r = 0;

    r = (v.getX()*v.getX()) + (v.getY()*v.getY()) + (v.getZ()*v.getZ());

    return sqrtf(r);
}



template <class T, class U>
inline T Magnitude(Vec4<U> v)
{
    T r = 0;

    r = (v.getX()*v.getX()) + (v.getY()*v.getY()) + (v.getZ()*v.getZ());

    return sqrtf(r);
}



template <class T, class U, class V>
inline T DotProduct(Vec2<U> v, Vec2<V> u)
{
    T r = 0;

    r = v.getX()*u.getX() + v.getY()*u.getY();

    return r;
}



template <class T, class U, class V>
inline T DotProduct(Vec3<U> v, Vec3<V> u)
{
    return v.getX()*u.getX() + v.getY()*u.getY() + v.getZ()*u.getZ();
}
template <class T>
inline T DotProduct(Vec3<T> v, Vec3<T> u)
{
    return v.getX()*u.getX() + v.getY()*u.getY() + v.getZ()*u.getZ();
}



template <class T, class U, class V>
inline T DotProduct(Vec4<U> v, Vec4<V> u)
{
    T r = 0;

    r = v.getX()*u.getX() + v.getY()*u.getY() + v.getZ()*u.getZ();

    return r;
}

template <class T, class U, class V>
inline Vec3<T> CrossProduct(Vec3<U> v, Vec3<V> u)
{
    Vec3<T> r;

    r.setX( (v.getY()*u.getZ()) - (v.getZ()*u.getY()) );
    r.setY( (v.getZ()*u.getX()) - (v.getX()*u.getZ()) );
    r.setZ( (v.getX()*u.getY()) - (v.getY()*u.getX()) );

    return r;
}

template <class T>
inline Vec3<T> CrossProduct(Vec3<T> v, Vec3<T> u)
{
    Vec3<T> r;

    r.setX( (v.getY()*u.getZ()) - (v.getZ()*u.getY()) );
    r.setY( (v.getZ()*u.getX()) - (v.getX()*u.getZ()) );
    r.setZ( (v.getX()*u.getY()) - (v.getY()*u.getX()) );

    return r;
}

template <class T, class U, class V>
inline Vec4<T> CrossProduct(Vec4<U> v, Vec4<V> u)
{
    Vec4<T> r;

    r.setX( (v.getY()*u.getZ()) - (v.getZ()*u.getY()) );
    r.setY( (v.getZ()*u.getX()) - (v.getX()*u.getZ()) );
    r.setZ( (v.getX()*u.getY()) - (v.getY()*u.getX()) );

    return r;
}

template <class T>
inline Vec2<T> Normalize(Vec2<T> v)
{
    return v / Magnitude(v);
}

template <class T, class U>
inline Vec2<T> Normalize(Vec2<U> v)
{
    return v / Magnitude(v);
}

template <class T>
Vec3<T> Normalize(Vec3<T> v)
{
    if( Magnitude(v) == 0 )
        return v;

    return v/Magnitude(v);
}

template <class T, class U>
inline Vec3<T> Normalize(Vec3<U> v)
{
    if( Magnitude(v) == 0 )
        return v;

    return v / Magnitude(v);
}

template <class T, class U>
inline Vec4<T> Normalize(Vec4<U> v)
{
    if( Magnitude(v) == 0 )
        return v;

    return v / Magnitude(v);
}

template <class T, class U, class V>
inline Vec2<T> Projection(Vec2<U> v, Vec2<V> u)
{
    return u * (DotProduct(v, u)/(Magnitude(u)*Magnitude(u)));
}



template <class T, class U, class V>
inline Vec3<T> Projection(Vec3<U> v, Vec3<V> u)
{
    return (u * (DotProduct(v, u)/(Magnitude(u)*Magnitude(u))));
}
template <class T>
inline Vec3<T> Projection(Vec3<T> v, Vec3<T> u)
{
    return (u * (DotProduct(v, u)/(Magnitude(u)*Magnitude(u))));
}

template <class T, class U, class V>
inline Vec4<T> Projection(Vec4<U> v, Vec4<V> u)
{
    return u *(DotProduct(v, u)/(Magnitude(u)*Magnitude(u)));
}



template <class T, class U, class V>
inline Vec2<T> Rotate2D(U angle, Vec2<V> v)
{
    return (v = Vec2<float>(v.getX() + cos(angle * (PI/180.0)) , v.getY() + sin(angle * (PI/180.0)) ));
}

template <class T, class U, class V>
inline Vec3<T> Rotate2D(U angle, Vec3<V> v)
{
    return (v = Vec3<float>(v.getX() + cos(angle * (PI/180.0)) , v.getY() + sin(angle * (PI/180.0)) , v.getZ() ));
}

template <class T, class U, class V>
inline Vec4<T> Rotate2D(U angle, Vec4<V> v)
{
    return (v = Vec4<float>(v.getX() + cos(angle * (PI/180.0)) , v.getY() + sin(angle * (PI/180.0)) , v.getZ(), v.getW() ));
}


template<class T>
inline T AngBetweenVecs(Vec2<T> origin, Vec2<T> v, Vec2<T> u)
{
    Vec2<T> tmpv, tmpu;
    T angle;

    tmpv = v-origin;
    tmpu = u-origin;

    angle = acos( DotProduct(tmpv, tmpu)/( Magnitude(tmpv)*Magnitude(tmpu)) );

    cout << angle << " angle.." << endl;

    return Radian2Degree(angle);

}

template<class T, class V, class U>
inline T AngBetweenVecs(Vec2<T> origin, Vec2<V> v, Vec2<U> u)
{
    Vec2<T> tmpv, tmpu;
    T angle;

    tmpv = v-origin;
    tmpu = u-origin;

    angle = acos( DotProduct(tmpv, tmpu)/( Magnitude(tmpv)*Magnitude(tmpu)) );

    cout << angle << " angle.." << endl;

    return Radian2Degree(angle);

}


template<class T>
inline T AngBetweenVecs(Vec3<T> origin, Vec3<T> v, Vec3<T> u)
{
    Vec3<T> tmpv, tmpu;
    T angle;

    tmpv = v-origin;
    tmpu = u-origin;

    angle = acos( DotProduct(tmpv, tmpu)/( Magnitude(tmpv)*Magnitude(tmpu)) );

    return Radian2Degree(angle);

}

template<class T, class V, class U>
inline T AngBetweenVecs(Vec3<T> origin, Vec3<V> v, Vec3<U> u)
{
    Vec3<T> tmpv, tmpu;
    T angle;

    tmpv = v-origin;
    tmpu = u-origin;

    angle = acos( DotProduct(tmpv, tmpu)/( Magnitude(tmpv)*Magnitude(tmpu)) );

    return Radian2Degree(angle);

}

inline Vec2<float> RandomVector2D(int range, float mag)
{
    int tx = (rand() % (range * 2))-range;
    int ty = (rand() % (range * 2))-range;

    float tx2 = (float)tx/(float)range;
    float ty2 = (float)ty/(float)range;

    Vec2<float> v2 = Vec2<float>(tx2, ty2);
    v2 = Normalize(v2);

    v2 *= mag;

    return v2;
}

inline float RandomFloat(int range0, int range1)
{
    int temp = range0 + rand() % range1;
    float value = (float)temp/(float)range1;

    return value;
}

}

namespace matrix_math
{


/*////////////////////
//                  //
//  MATRIX CLASSES  //
//   AND FUNCTION   //
//                  //
////////////////////*/

////////////////////
//Matrix 3X3 Class//
////////////////////

//Matrix Determinate, Inverse, Minor, matrixVecMultiply Not Done for Mat3x3 Yet
template <class T>
class Mat4X4;

template<class T = float>
class Mat3X3
{


    public:

        T matrixA[9];

        Mat3X3<T>()
        {
            for(int i=0; i<9; i++)
                matrixA[i] = 0;
        }

        template<class U>
        Mat3X3<T>(const Mat3X3<U>& right)
        {
            for(int i=0; i<9; i++)
                this->matrixA[i] = right.matrixA[i];
        }

        void zeroClear()
        {
            for(int i=0; i<9; i++)
                matrixA[i] = 0;
        }

        void identityClear()
        {
            for(int i=0; i<3; i++)
                matrixA[i+(i*3)] = 1;
        }

        template<class U>
        void operator= (const Mat3X3<U> & right)
        {
            for(int i=0; i<9; i++)
                this->matrixA[i] = right.matrixA[i];
        }

        template<class U>
        void operator= (const Mat4X4<U> & right)
        {
            this->matrixA[0] = right.matrixA[0];
            this->matrixA[1] = right.matrixA[1];
            this->matrixA[2] = right.matrixA[2];

            this->matrixA[3] = right.matrixA[4];
            this->matrixA[4] = right.matrixA[5];
            this->matrixA[5] = right.matrixA[6];

            this->matrixA[6] = right.matrixA[8];
            this->matrixA[7] = right.matrixA[9];
            this->matrixA[8] = right.matrixA[10];
        }

        template<class U>
        Mat3X3<T> operator* (const Mat3X3<U> & right)
        {
            Mat3X3<T> tmp;

            tmp = MatrixMult((*this), right);

            return tmp;
        }

        template<class U>
        Mat3X3<T> operator*= (const Mat3X3<U> & right)
        {
            Mat3X3<T> tmp;

            tmp = MatrixMult((*this), right);

            matrixA = tmp.matrixA;

            return *this;
        }
};



////////////////////
//Matrix 4X4 Class//
////////////////////

template<class T = float>
class Mat4X4
{


    public:

        T matrixA[16];

        Mat4X4<T>()
        {
            for(int i=0; i<16; i++)
                matrixA[i] = 0;
        }

        template<class U>
        Mat4X4<T>(const Mat4X4<U>& right)
        {
            for(int i=0; i<16; i++)
                this->matrixA[i] = right.matrixA[i];
        }

        void zeroClear()
        {
            for(int i=0; i<16; i++)
                matrixA[i] = 0;
        }

        void identityClear()
        {

            for(int i=0; i<16; i++)
                matrixA[i] = 0;

            for(int i=0; i<4; i++)
                matrixA[i+(i*4)] = 1;
        }

        template<class U>
        void operator= (const Mat4X4<U> & right)
        {
            for(int i=0; i<16; i++)
                this->matrixA[i] = right.matrixA[i];
        }

        template<class U>
        void operator= (const Mat3X3<U> & right)
        {
                this->matrixA[0] = right.matrixA[0];
                this->matrixA[1] = right.matrixA[1];
                this->matrixA[2] = right.matrixA[2];

                this->matrixA[4] = right.matrixA[3];
                this->matrixA[5] = right.matrixA[4];
                this->matrixA[6] = right.matrixA[5];

                this->matrixA[8]  = right.matrixA[6];
                this->matrixA[9]  = right.matrixA[7];
                this->matrixA[10] = right.matrixA[8];
        }

        template<class U>
        Mat4X4<T> operator* (const Mat4X4<U> & right)
        {
            Mat4X4<T> tmp;

            tmp = MatrixMult((*this), right);

            return tmp;
        }

        template<class U>
        Mat4X4<T> operator*= (const Mat4X4<U> & right)
        {
            Mat4X4<T> tmp;

            tmp = MatrixMult((*this), right);

            for(int i=0; i<16; i++)
            matrixA[i] = tmp.matrixA[i];

            return *this;
        }

        template<class U>
        Mat4X4<T> operator+ (const Mat4X4<U> & right)
        {
            Mat4X4<T> tmp;

            for(int i=0; i<16; i++)
                tmp.matrixA[i] = matrixA[i] + right.matrixA[i];

            return tmp;
        }
};


template <class T, class U>
inline T MatrixDeterminate(const Mat4X4<U> & m)
{
    T det = 0;


        if(m.matrixA[3 + (0*4)] == 0 && m.matrixA[3 + (1*4)] == 0 && m.matrixA[3 + (2*4)] == 0)
        {
            det = m.matrixA[3 + (3*4)] * ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (2*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (2*4)]) + m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (2*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (2*4)]));
        }
        else
        {
            T E_tmp, F_tmp, G_tmp, H_tmp;

            E_tmp =  m.matrixA[0 + (0*4)] * ( m.matrixA[1 + (1*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]));
            F_tmp = -m.matrixA[1 + (0*4)] * ( m.matrixA[0 + (1*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]));
            G_tmp =  m.matrixA[2 + (0*4)] * ( m.matrixA[0 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]));
            H_tmp = -m.matrixA[3 + (0*4)] * ( m.matrixA[0 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[2 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]));

            det = E_tmp + F_tmp + G_tmp + H_tmp;
        }

    return det;
}
template <class T>
inline T MatrixDeterminate(const Mat4X4<T> & m)
{
    T det = 0;


        if(m.matrixA[3 + (0*4)] == 0 && m.matrixA[3 + (1*4)] == 0 && m.matrixA[3 + (2*4)] == 0)
        {
            det = m.matrixA[3 + (3*4)] * ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (2*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (2*4)]) + m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (2*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (2*4)]));
        }
        else
        {
            T E_tmp, F_tmp, G_tmp, H_tmp;

            E_tmp =  m.matrixA[0 + (0*4)] * ( m.matrixA[1 + (1*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]));
            F_tmp = -m.matrixA[1 + (0*4)] * ( m.matrixA[0 + (1*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]));
            G_tmp =  m.matrixA[2 + (0*4)] * ( m.matrixA[0 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]));
            H_tmp = -m.matrixA[3 + (0*4)] * ( m.matrixA[0 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[2 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]));

            det = E_tmp + F_tmp + G_tmp + H_tmp;
        }

    return det;
}

template <class T, class U, class V>
inline Mat3X3<T> MatrixMult(const Mat3X3<U> & m, const Mat3X3<V> & n)
{
    Mat3X3<T> tmp;

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            for(int k=0; k<3; k++)
                tmp.matrixA[j + (i*3)] += m.matrixA[k + (i*3)] * n.matrixA[j + (k*3)];

    return tmp;
}

template <class T, class U, class V>
inline Mat4X4<T> MatrixMult(const Mat4X4<U> & m, const Mat4X4<V> & n)
{
    Mat4X4<T> tmp;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                tmp.matrixA[j + (i*4)] += m.matrixA[k + (i*4)] * n.matrixA[j + (k*4)];

    return tmp;
}

template <class T>
inline Mat4X4<T> MatrixMult(const Mat4X4<T> & m, const Mat4X4<T> & n)
{
    Mat4X4<T> tmp;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                tmp.matrixA[j + (i*4)] += m.matrixA[k + (i*4)] * n.matrixA[j + (k*4)];

    return tmp;
}


template <class T, class U>
inline Mat4X4<T> MatrixMinor(const Mat4X4<U> & m)
{
    Mat4X4<T> t_mat;

    t_mat.matrixA[0 + (0*4)] = ( m.matrixA[1 + (1*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]))* 1;
    t_mat.matrixA[1 + (0*4)] = ( m.matrixA[0 + (1*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]))*-1;
    t_mat.matrixA[2 + (0*4)] = ( m.matrixA[0 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]))* 1;
    t_mat.matrixA[3 + (0*4)] = ( m.matrixA[0 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[2 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]))*-1;

    t_mat.matrixA[0 + (1*4)] = ( m.matrixA[1 + (0*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]))*-1;
    t_mat.matrixA[1 + (1*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]))* 1;
    t_mat.matrixA[2 + (1*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]))*-1;
    t_mat.matrixA[3 + (1*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[2 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]))* 1;

    t_mat.matrixA[0 + (2*4)] = ( m.matrixA[1 + (0*4)]*( m.matrixA[2 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[1 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (3*4)]))* 1;
    t_mat.matrixA[1 + (2*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[2 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (3*4)]))*-1;
    t_mat.matrixA[2 + (2*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (3*4)]))* 1;
    t_mat.matrixA[3 + (2*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (3*4)]))*-1;

    t_mat.matrixA[0 + (3*4)] = ( m.matrixA[1 + (0*4)]*( m.matrixA[2 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[2 + (2*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[1 + (2*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (2*4)]))*-1;
    t_mat.matrixA[1 + (3*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[2 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[2 + (2*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[0 + (2*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (2*4)]))* 1;
    t_mat.matrixA[2 + (3*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[1 + (2*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[0 + (2*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (2*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (2*4)]))*-1;
    t_mat.matrixA[3 + (3*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (2*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (2*4)]) + m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (2*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (2*4)]))* 1;

    return t_mat;
}
template <class T>
inline Mat4X4<T> MatrixMinor(const Mat4X4<T> & m)
{
    Mat4X4<T> t_mat;

    t_mat.matrixA[0 + (0*4)] = ( m.matrixA[1 + (1*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]))* 1;
    t_mat.matrixA[1 + (0*4)] = ( m.matrixA[0 + (1*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]))*-1;
    t_mat.matrixA[2 + (0*4)] = ( m.matrixA[0 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]))* 1;
    t_mat.matrixA[3 + (0*4)] = ( m.matrixA[0 + (1*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[2 + (1*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]))*-1;

    t_mat.matrixA[0 + (1*4)] = ( m.matrixA[1 + (0*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]))*-1;
    t_mat.matrixA[1 + (1*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[2 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]))* 1;
    t_mat.matrixA[2 + (1*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]))*-1;
    t_mat.matrixA[3 + (1*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (2*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[2 + (0*4)]*( m.matrixA[0 + (2*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (2*4)]*m.matrixA[0 + (3*4)]))* 1;

    t_mat.matrixA[0 + (2*4)] = ( m.matrixA[1 + (0*4)]*( m.matrixA[2 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[1 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (3*4)]))* 1;
    t_mat.matrixA[1 + (2*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[2 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[2 + (3*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (3*4)]))*-1;
    t_mat.matrixA[2 + (2*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[3 + (3*4)] - m.matrixA[3 + (1*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (3*4)]))* 1;
    t_mat.matrixA[3 + (2*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (3*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (3*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (3*4)]) + m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (3*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (3*4)]))*-1;

    t_mat.matrixA[0 + (3*4)] = ( m.matrixA[1 + (0*4)]*( m.matrixA[2 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[2 + (2*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[1 + (2*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (2*4)]))*-1;
    t_mat.matrixA[1 + (3*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[2 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[2 + (2*4)]) - m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[0 + (2*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (2*4)]))* 1;
    t_mat.matrixA[2 + (3*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[1 + (2*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[3 + (2*4)] - m.matrixA[3 + (1*4)]*m.matrixA[0 + (2*4)]) + m.matrixA[3 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (2*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (2*4)]))*-1;
    t_mat.matrixA[3 + (3*4)] = ( m.matrixA[0 + (0*4)]*( m.matrixA[1 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[1 + (2*4)]) - m.matrixA[1 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[2 + (2*4)] - m.matrixA[2 + (1*4)]*m.matrixA[0 + (2*4)]) + m.matrixA[2 + (0*4)]*( m.matrixA[0 + (1*4)]*m.matrixA[1 + (2*4)] - m.matrixA[1 + (1*4)]*m.matrixA[0 + (2*4)]))* 1;

    return t_mat;
}


template <class T>
inline Mat3X3<T> MatrixTranspose(const Mat3X3<T> & m)
{
    Mat3X3<T> m_tmp;

    m_tmp.matrixA[0 ] = m.matrixA[0 ];   m_tmp.matrixA[1 ] = m.matrixA[3 ];   m_tmp.matrixA[2 ] = m.matrixA[6 ];
    m_tmp.matrixA[3 ] = m.matrixA[1 ];   m_tmp.matrixA[4 ] = m.matrixA[4 ];   m_tmp.matrixA[5 ] = m.matrixA[7 ];
    m_tmp.matrixA[6 ] = m.matrixA[2 ];   m_tmp.matrixA[7 ] = m.matrixA[5 ];   m_tmp.matrixA[8 ] = m.matrixA[8 ];


    return m_tmp;
}


template <class T, class U>
inline Mat3X3<T> MatrixTranspose(const Mat3X3<U> & m)
{
    Mat3X3<T> m_tmp;

    m_tmp.matrixA[0 ] = m.matrixA[0 ];   m_tmp.matrixA[1 ] = m.matrixA[3 ];   m_tmp.matrixA[2 ] = m.matrixA[6 ];
    m_tmp.matrixA[3 ] = m.matrixA[1 ];   m_tmp.matrixA[4 ] = m.matrixA[4 ];   m_tmp.matrixA[5 ] = m.matrixA[7 ];
    m_tmp.matrixA[6 ] = m.matrixA[2 ];   m_tmp.matrixA[7 ] = m.matrixA[5 ];   m_tmp.matrixA[8 ] = m.matrixA[8 ];


    return m_tmp;
}


template <class T, class U>
inline Mat4X4<T> MatrixTranspose(const Mat4X4<U> & m)
{
    Mat4X4<T> m_tmp;

    m_tmp.matrixA[0 ] = m.matrixA[0 ];   m_tmp.matrixA[1 ] = m.matrixA[4 ];   m_tmp.matrixA[2 ] = m.matrixA[8 ];   m_tmp.matrixA[3 ] = m.matrixA[12];
    m_tmp.matrixA[4 ] = m.matrixA[1 ];   m_tmp.matrixA[5 ] = m.matrixA[5 ];   m_tmp.matrixA[6 ] = m.matrixA[9 ];   m_tmp.matrixA[7 ] = m.matrixA[13];
    m_tmp.matrixA[8 ] = m.matrixA[2 ];   m_tmp.matrixA[9 ] = m.matrixA[6 ];   m_tmp.matrixA[10] = m.matrixA[10];   m_tmp.matrixA[11] = m.matrixA[14];
    m_tmp.matrixA[12] = m.matrixA[3 ];   m_tmp.matrixA[13] = m.matrixA[7 ];   m_tmp.matrixA[14] = m.matrixA[11];   m_tmp.matrixA[15] = m.matrixA[15];

    return m_tmp;
}
template <class T>
inline Mat4X4<T> MatrixTranspose(const Mat4X4<T> & m)
{
    Mat4X4<T> m_tmp;

    m_tmp.matrixA[0 ] = m.matrixA[0 ];   m_tmp.matrixA[1 ] = m.matrixA[4 ];   m_tmp.matrixA[2 ] = m.matrixA[8 ];   m_tmp.matrixA[3 ] = m.matrixA[12];
    m_tmp.matrixA[4 ] = m.matrixA[1 ];   m_tmp.matrixA[5 ] = m.matrixA[5 ];   m_tmp.matrixA[6 ] = m.matrixA[9 ];   m_tmp.matrixA[7 ] = m.matrixA[13];
    m_tmp.matrixA[8 ] = m.matrixA[2 ];   m_tmp.matrixA[9 ] = m.matrixA[6 ];   m_tmp.matrixA[10] = m.matrixA[10];   m_tmp.matrixA[11] = m.matrixA[14];
    m_tmp.matrixA[12] = m.matrixA[3 ];   m_tmp.matrixA[13] = m.matrixA[7 ];   m_tmp.matrixA[14] = m.matrixA[11];   m_tmp.matrixA[15] = m.matrixA[15];

    return m_tmp;
}


template <class T, class U>
inline Mat4X4<T> MatrixInverse(const Mat4X4<U> & m)
{
    Mat4X4<T> minor; //hold matrix minor
    Mat4X4<T> inv;   //hold matrix inverse

    const T det = MatrixDeterminate(m);
    minor = MatrixMinor(m);
    inv = MatrixTranspose(minor);

    for(int i=0; i<16; i++)
        inv.matrixA[i] /= det;

    return inv;

}
template <class T>
inline Mat4X4<T> MatrixInverse(const Mat4X4<T> & m)
{
    Mat4X4<T> minor; //hold matrix minor
    Mat4X4<T> inv;   //hold matrix inverse

    const T det = MatrixDeterminate(m);
    minor = MatrixMinor(m);
    inv = MatrixTranspose(minor);

    for(int i=0; i<16; i++)
        inv.matrixA[i] /= det;

    return inv;

};


template <class T, class U, class V>
inline vector_math::Vec4<T> matrixVecMultiply(const Mat4X4<U> & m, vector_math::Vec4<V> v)
{
    vector_math::Vec4<T> tmp;
    T tx, ty, tz, tw;
    T x=0, y=0, z=0, w=0;

    tx = v.getX();
    ty = v.getY();
    tz = v.getZ();
    tw = v.getW();

    for(int i=0; i<4; i++)
    {
        x += m.matrixA[i + (i*0)] * tx;
        y += m.matrixA[i + (i*1)] * ty;
        z += m.matrixA[i + (i*2)] * tz;
        w += m.matrixA[i + (i*3)] * tw;
    }

/*
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1

0  1  2  3    x
4  5  6  7    y
8  9  10 11   z
12 13 14 15   w
*/

/*
    x = (m.matrixA[0 + (0*4)] * tx) + (m.matrixA[0 + (1*4)] * ty) + (m.matrixA[0 + (2*4)] * tz) + (m.matrixA[0 + (3*4)] * tw);
    y = (m.matrixA[1 + (0*4)] * tx) + (m.matrixA[1 + (1*4)] * ty) + (m.matrixA[1 + (2*4)] * tz) + (m.matrixA[0 + (3*4)] * tw);
    z = (m.matrixA[2 + (0*4)] * tx) + (m.matrixA[2 + (1*4)] * ty) + (m.matrixA[2 + (2*4)] * tz) + (m.matrixA[0 + (3*4)] * tw);
    w = (m.matrixA[3 + (0*4)] * tx) + (m.matrixA[3 + (1*4)] * ty) + (m.matrixA[3 + (2*4)] * tz) + (m.matrixA[0 + (3*4)] * tw);
*/
    tmp.setXYZW(x, y, z, w);

    return tmp;
}

template <class T>
Mat4X4<T> MatrixRotationRoll(T angle)
{
    /*
    Rotate along the Z-Axis
    */
    Mat4X4<T> RollMatrix;
    RollMatrix.identityClear();


    RollMatrix.matrixA[0] = cos(Degree2Radian(angle));
    RollMatrix.matrixA[1] = sin(Degree2Radian(angle));
    RollMatrix.matrixA[4] = -sin(Degree2Radian(angle));
    RollMatrix.matrixA[5] = cos(Degree2Radian(angle));

    return MatrixTranspose(RollMatrix);
}

template <class T>
Mat4X4<T> MatrixRotationYaw(T angle)
{
    /*
    Rotate along the Y-Axis
    */
    Mat4X4<T> YawMatrix;
    YawMatrix.identityClear();


    YawMatrix.matrixA[0] = cos(Degree2Radian(angle));
    YawMatrix.matrixA[2] = -sin(Degree2Radian(angle));
    YawMatrix.matrixA[8] = sin(Degree2Radian(angle));
    YawMatrix.matrixA[10] = cos(Degree2Radian(angle));

    return MatrixTranspose(YawMatrix);
}

template <class T>
Mat4X4<T> MatrixRotationPitch(T angle)
{
    /*
    Rotate along the X-Axis
    */
    Mat4X4<T> PitchMatrix;
    PitchMatrix.identityClear();


    PitchMatrix.matrixA[5]  = cos(Degree2Radian(angle));
    PitchMatrix.matrixA[6]  = sin(Degree2Radian(angle));
    PitchMatrix.matrixA[9]  = -sin(Degree2Radian(angle));
    PitchMatrix.matrixA[10] = cos(Degree2Radian(angle));

    return MatrixTranspose(PitchMatrix);
}

template <class T>
Mat4X4<T> MatrixTranslation(T x, T y, T z)
{
    Mat4X4<T> TransMatrix;
    TransMatrix.identityClear();

    TransMatrix.matrixA[3] = x;
    TransMatrix.matrixA[7] = y;
    TransMatrix.matrixA[11] = z;
    TransMatrix.matrixA[15] = T(1);

    return TransMatrix;
}

template <class T>
Mat4X4<T> MatrixScale(T x, T y, T z)
{
    Mat4X4<T> ScaleMatrix;
    ScaleMatrix.identityClear();

    ScaleMatrix.matrixA[0]  = x;
    ScaleMatrix.matrixA[5]  = y;
    ScaleMatrix.matrixA[10] = z;

    return ScaleMatrix;
}

template <class T>
inline Mat4X4<T> PerspectiveMatrix(T fovy, T aspect, T zNear, T zFar)
{
    Mat4X4<T> M;
    M.identityClear();

    const T f = T(1)/tan(Degree2Radian(fovy)/T(2));

    M.matrixA[0] = f / aspect;
    M.matrixA[1] = 0;
    M.matrixA[2] = 0;
    M.matrixA[3] = 0;

    M.matrixA[4] = 0;
    M.matrixA[5] = f;
    M.matrixA[6] = 0;
    M.matrixA[7] = 0;

    M.matrixA[8] = 0;
    M.matrixA[9] = 0;
    M.matrixA[10] = (zFar + zNear)/(zNear-zFar);
    M.matrixA[11] = (T(2)*zNear*zFar)/(zNear-zFar);

    M.matrixA[12] = 0;
    M.matrixA[13] = 0;
    M.matrixA[14] = T(-1);
    M.matrixA[15] = 0;


    return M;

}

template <class T>
inline Mat4X4<T> PerspectiveMatrixRAD(T fovy, T aspect, T zNear, T zFar)
{
    Mat4X4<T> M;
    M.identityClear();

    const T f = T(1)/tan(fovy/T(2));

    M.matrixA[0] = f / aspect;
    M.matrixA[1] = 0;
    M.matrixA[2] = 0;
    M.matrixA[3] = 0;

    M.matrixA[4] = 0;
    M.matrixA[5] = f;
    M.matrixA[6] = 0;
    M.matrixA[7] = 0;

    M.matrixA[8] = 0;
    M.matrixA[9] = 0;
    M.matrixA[10] = (zFar + zNear)/(zNear-zFar);
    M.matrixA[11] = (T(2)*zNear*zFar)/(zNear-zFar);

    M.matrixA[12] = 0;
    M.matrixA[13] = 0;
    M.matrixA[14] = T(-1);
    M.matrixA[15] = 0;


    return M;

}

template <class T>
inline Mat4X4<T> LookAtMatrix(T eyex, T eyey, T eyez, T atx, T aty, T atz, T upx, T upy, T upz)
{
    Mat4X4<T> M;
    M.identityClear();

    vector_math::Vec3<T> Eye = vector_math::Vec3<T>(eyex, eyey, eyez);
    vector_math::Vec3<T> At  = vector_math::Vec3<T>(atx, aty, atz);
    vector_math::Vec3<T> Up  = vector_math::Vec3<T>(upx, upy, upz);

    Up = vector_math::Normalize(Up);

    vector_math::Vec3<T> F = At - Eye;
    F = vector_math::Normalize<T>(F);

    vector_math::Vec3<T> S = vector_math::CrossProduct(F, Up);
    S = vector_math::Normalize<T>(S);

    vector_math::Vec3<T> U = vector_math::CrossProduct(S, F);
    U = vector_math::Normalize<T>(U);

    M.matrixA[0] =  S.getX();
    M.matrixA[1] =  S.getY();
    M.matrixA[2] =  S.getZ();
    M.matrixA[3] =  -vector_math::DotProduct(S, Eye);

    M.matrixA[4] =  U.getX();
    M.matrixA[5] =  U.getY();
    M.matrixA[6] =  U.getZ();
    M.matrixA[7] =  -vector_math::DotProduct(U, Eye);

    M.matrixA[8]  = -F.getX();
    M.matrixA[9]  = -F.getY();
    M.matrixA[10] = -F.getZ();
    M.matrixA[11] = -vector_math::DotProduct(-F, Eye);

    M.matrixA[12] = T(0);
    M.matrixA[13] = T(0);
    M.matrixA[14] = T(0);
    M.matrixA[15] = T(1);

    return M;

}

template <class T>
inline Mat4X4<T> LookAtMatrix( vector_math::Vec3<T> Eye, vector_math::Vec3<T> At, vector_math::Vec3<T> Up)
{
    Mat4X4<T> M;
    M.identityClear();

    Up = vector_math::Normalize(Up);

    vector_math::Vec3<T> F = At - Eye;
    F = vector_math::Normalize<T>(F);

    vector_math::Vec3<T> S = vector_math::CrossProduct(F, Up);
    S = vector_math::Normalize<T>(S);

    vector_math::Vec3<T> U = vector_math::CrossProduct(S, F);
    U = vector_math::Normalize<T>(U);

    M.matrixA[0] =  S.getX();
    M.matrixA[1] =  S.getY();
    M.matrixA[2] =  S.getZ();
    M.matrixA[3] =  -vector_math::DotProduct(S, Eye);

    M.matrixA[4] =  U.getX();
    M.matrixA[5] =  U.getY();
    M.matrixA[6] =  U.getZ();
    M.matrixA[7] =  -vector_math::DotProduct(U, Eye);

    M.matrixA[8]  = -F.getX();
    M.matrixA[9]  = -F.getY();
    M.matrixA[10] = -F.getZ();
    M.matrixA[11] = -vector_math::DotProduct(-F, Eye);

    M.matrixA[12] = T(0);
    M.matrixA[13] = T(0);
    M.matrixA[14] = T(0);
    M.matrixA[15] = T(1);

    return M;

}

template <class T> //Special Case
inline Mat4X4<T> LookAtMatrix(T eyex, T eyey, T eyez, T atx, T aty, T atz, T upx, T upy, T upz, T rightx, T righty, T rightz)
{
    Mat4X4<T> M;
    M.identityClear();

    vector_math::Vec3<T> Eye = vector_math::Vec3<T>(eyex, eyey, eyez);
    vector_math::Vec3<T> At  = vector_math::Vec3<T>(atx, aty, atz);
    vector_math::Vec3<T> Up  = vector_math::Vec3<T>(upx, upy, upz);
    vector_math::Vec3<T> Right  = vector_math::Vec3<T>(rightx, righty, rightz);

    At = vector_math::Normalize(At);
    Up = vector_math::CrossProduct(At, Right);
    Up = vector_math::Normalize(Up);
    Right = vector_math::CrossProduct(Up, At);
    Right = vector_math::Normalize(Right);


    M.matrixA[0] =  Right.getX();
    M.matrixA[1] =  Right.getY();
    M.matrixA[2] =  Right.getZ();
    M.matrixA[3] =  -vector_math::DotProduct(Right, Eye);

    M.matrixA[4] =  Up.getX();
    M.matrixA[5] =  Up.getY();
    M.matrixA[6] =  Up.getZ();
    M.matrixA[7] =  -vector_math::DotProduct(Up, Eye);

    M.matrixA[8]  = At.getX();
    M.matrixA[9]  = At.getY();
    M.matrixA[10] = At.getZ();
    M.matrixA[11] = -vector_math::DotProduct(At, Eye);

    M.matrixA[12] = T(0);
    M.matrixA[13] = T(0);
    M.matrixA[14] = T(0);
    M.matrixA[15] = T(1);

    return M;

}

template <class T>
inline Mat4X4<T> LookAtMatrix( vector_math::Vec3<T> Eye, vector_math::Vec3<T> At, vector_math::Vec3<T> Up, vector_math::Vec3<T> Right)
{
    Mat4X4<T> M;
    M.identityClear();

    At = vector_math::Normalize(At);
    Up = vector_math::CrossProduct(At, Right);
    Up = vector_math::Normalize(Up);
    Right = vector_math::CrossProduct(Up, At);
    Right = vector_math::Normalize(Right);


    M.matrixA[0] =  Right.getX();
    M.matrixA[1] =  Up.getX();
    M.matrixA[2] =  At.getX();
    M.matrixA[3] =  T(0);

    M.matrixA[4] =  Right.getY();
    M.matrixA[5] =  Up.getY();
    M.matrixA[6] =  At.getY();
    M.matrixA[7] =  T(0);

    M.matrixA[8]  = Right.getZ();
    M.matrixA[9]  = Up.getZ();
    M.matrixA[10] = At.getZ();
    M.matrixA[11] = T(0);

    M.matrixA[12] = -vector_math::DotProduct(Right, Eye);
    M.matrixA[13] = -vector_math::DotProduct(Up, Eye);
    M.matrixA[14] = -vector_math::DotProduct(At, Eye);
    M.matrixA[15] = T(1);

    M = MatrixTranspose(M);

    return M;

}

};
/*////////////////////
//                  //
//      ALGEBRA     //
//    AND FUNCTION  //
//                  //
////////////////////*/


template <class T>
inline T Degree2Radian(T angle)
{
    return angle*(PI/180);
}
template <class T, class U>
inline T Degree2Radian(U angle)
{
    return angle*(PI/180);
}


template <class T>
inline T Radian2Degree(T angle)
{
    return angle*(180/PI);
}
template <class T, class U>
inline T Radian2Degree(U angle)
{
    return angle*(180/PI);
}

template <class T>
inline bool Reflex(vector_math::Vec3<T> mid, vector_math::Vec3<T> v, vector_math::Vec3<T> u)
{
    return 0;
}


#endif
