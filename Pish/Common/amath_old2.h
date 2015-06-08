#ifndef AMATH_H
#define AMATH_H

#include <cmath>
#include <iostream>
using namespace std;
///////////////////
//2D Vector Class//
///////////////////

#define PI 3.14159265


/*////////////////////
//                  //
//  VECTOR CLASSES  //
//   AND FUNCTION   //
//                  //
////////////////////*/

template <typename T>
class Vec3;
template <typename T>
class Vec4;


template<typename T>
class Vec2
{
    private:
        T x;
        T y;
        T temp[2];

    public:

        Vec2<T>()
        {
            x = 0;
            y = 0;
        }


        template<typename U>
        Vec2<T>(const Vec2<U> & v)
        {
            x = 0;
            y = 0;
        }


        Vec2<T>(T x, T y)
        {
            this->x = x;
            this->y = y;
        }


        template <typename U>
        Vec2<T>(const Vec2<U>& right)
        {
            x = right.x;
            y = right.y;
        }


        template<typename U>
        Vec2<T> operator = (const Vec2<U>& right)
        {
            x = right.x;
            y = right.y;

            return *this;
        }


        template<typename U>
        Vec2<T> operator = (const Vec3<U>& right)
        {
            x = right.getX();
            y = right.getY();

            return *this;
        }


        template<typename U>
        Vec2<T> operator = (const Vec4<U>& right)
        {
            x = right.getX();
            y = right.getY();

            return *this;
        }


        template<typename U>
        Vec2<T> operator + (const Vec2<U>& right)
        {
            Vec2<T> tmp;
            T x_ = x, y_ = y;

            x_ += right.x;
            y_ += right.y;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<typename U>
        Vec2<T> operator + (const U& right)
        {
            Vec2<T> tmp;
            T x_ = x, y_ = y;

            x_ += right;
            y_ += right;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<typename U>
        Vec2<T> operator += (const Vec2<U>& right)
        {
            x += right.x;
            y += right.y;

            return *this;
        }


        template<typename U>
        Vec2<T> operator += (const U& right)
        {
            x += right;
            y += right;

            return *this;
        }


        template<typename U>
        Vec2<T> operator - (const Vec2<U>& right)
        {
            Vec2<T> tmp;
            T x_ = x, y_ = y;

            x_ -= right.x;
            y_ -= right.y;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<typename U>
        Vec2<T> operator - (const U& right)
        {
            Vec2<T> tmp;
            T x_ = x, y_ = y;

            x_ -= right;
            y_ -= right;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<typename U>
        Vec2<T> operator -= (const Vec2<U>& right)
        {
            x -= right.x;
            y -= right.y;

            return *this;
        }


        template<typename U>
        Vec2<T> operator -= (const U& right)
        {
            x -= right;
            y -= right;

            return *this;
        }


        Vec2<T> operator - ()
        {
            Vec2<T> tmp;
            T x_ = x, y_ = y;

            x_ *= -1;
            y_ *= -1;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<typename U>
        Vec2<T> operator * (const Vec2<U>& right)
        {
            Vec2<T> tmp;
            T x_ = x, y_ = y;

            x_ *= right.x;
            y_ *= right.y;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<typename U>
        Vec2<T> operator * (const U& right)
        {
            Vec2<T> tmp;
            T x_ = x, y_ = y;

            x_ *= right;
            y_ *= right;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<typename U>
        Vec2<T> operator *= (const Vec2<U>& right)
        {
            x *= right.x;
            y *= right.y;

            return *this;
        }


        template<typename U>
        Vec2<T> operator *= (const U& right)
        {
            x *= right;
            y *= right;

            return *this;
        }


        template<typename U>
        Vec2<T> operator / (const Vec2<U>& right)
        {
            Vec2<T> tmp;
            T x_ = x, y_ = y;

            x_ /= right.x;
            y_ /= right.y;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<typename U>
        Vec2<T> operator / (const Vec2<U>& right)
        {
            Vec2<T> tmp;
            T x_ = x, y_ = y;

            x_ /= right;
            y_ /= right;

            tmp.setXY(x_, y_);

            return tmp;
        }


        template<typename U>
        Vec2<T> operator /= (const U& right)
        {
            x /= right;
            y /= right;

            return *this;
        }


        template<typename U>
        Vec2<T> operator /= (const Vec2<U>& right)
        {
            x /= right.x;
            y /= right.y;

            return *this;
        }


        T getX() const
        {
            return x;
        }

        T getY() const
        {
            return y;
        }

        T * getXY()
        {
            temp[0] = x;
            temp[1] = y;

            return temp;
        }

        void setX(T X)
        {
            x = X;
        }

        void setY(T Y)
        {
            y = Y;
        }

        void setXY(T X, T Y)
        {
            x = X;
            y = Y;
        }

};


///////////////////
//3D Vector Class//
///////////////////

template<typename T>
class Vec3
{
    private:
        T x;
        T y;
        T z;
        T temp[3];

    public:
        Vec3<T>()
        {
            x = 0;
            y = 0;
            z = 0;
        }


        Vec3<T>(T x, T y, T z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }


        template <typename U>
        Vec3<T>(const Vec3<U>& right)
        {
            x = right.x;
            y = right.y;
            z = right.z;
        }


        template <typename U>
        Vec3<T> operator = (const Vec3<U>& right)
        {
            x = right.x;
            y = right.y;
            z = right.z;

            return *this;
        }


        template <typename U>
        Vec3<T> operator = (const Vec2<U>& right)
        {
            this->x = right.getX();
            this->y = right.getY();

            return *this;
        }


        template <typename U>
        Vec3<T> operator = (const Vec4<U>& right)
        {
            x = right.getX();
            y = right.getY();
            z = right.getZ();

            return *this;
        }


        template <typename U>
        Vec3<T> operator + (const Vec3<U>& right)
        {
            Vec3<T> tmp;
            T x_ = x, y_ = y, z_ = z;

            x_ += right.x;
            y_ += right.y;
            z_ += right.z;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <typename U>
        Vec3<T> operator + (const U& right)
        {
            Vec3<T> tmp;
            T x_ = x, y_ = y, z_ = z;

            x_ += right;
            y_ += right;
            z_ += right;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <typename U>
        Vec3<T> operator += (const Vec3<U>& right)
        {
            x += right.x;
            y += right.y;
            z += right.z;

            return *this;
        }


        template <typename U>
        Vec3<T> operator += (const U& right)
        {
            x += right;
            y += right;
            z += right;

            return *this;
        }


        template <typename U>
        Vec3<T> operator - (const Vec3<U>& right)
        {
            Vec3<T> tmp;
            T x_ = x, y_ = y, z_ = z;

            x_ -= right.x;
            y_ -= right.y;
            z_ -= right.z;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <typename U>
        Vec3<T> operator - (const U& right)
        {
            Vec3<T> tmp;
            T x_ = x, y_ = y, z_ = z;

            x_ -= right;
            y_ -= right;
            z_ -= right;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <typename U>
        Vec3<T> operator -= (const Vec3<U>& right)
        {
            x -= right.x;
            y -= right.y;
            z -= right.z;

            return *this;
        }


        template <typename U>
        Vec3<T> operator -= (const U& right)
        {
            x -= right;
            y -= right;
            z -= right;

            return *this;
        }


        Vec3<T> operator - ()
        {
            Vec3<T> tmp;
            T x_ = x, y_ = y, z_ = z;

            x_ *= -1;
            y_ *= -1;
            z_ *= -1;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <typename U>
        Vec3<T> operator * (const Vec3<U>& right)
        {
            Vec3<T> tmp;
            T x_ = x, y_ = y, z_ = z;

            x_ *= right.x;
            y_ *= right.y;
            z_ *= right.z;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <typename U>
        Vec3<T> operator * (const U& right)
        {
            Vec3<T> tmp;
            T x_ = x, y_ = y, z_ = z;

            x_ *= right;
            y_ *= right;
            z_ *= right;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <typename U>
        Vec3<T> operator *= (const Vec3<U>& right)
        {
            x *= right.x;
            y *= right.y;
            z *= right.z;

            return *this;
        }


        template <typename U>
        Vec3<T> operator *= (const U& right)
        {
            x *= right;
            y *= right;
            z *= right;

            return *this;
        }


        template <typename U>
        Vec3<T> operator / (const Vec3<U>& right)
        {
            Vec3<T> tmp;
            T x_ = x, y_ = y, z_ = z;

            x_ /= right.x;
            y_ /= right.y;
            z_ /= right.z;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <typename U>
        Vec3<T> operator / (const U& right)
        {
            Vec3<T> tmp;
            T x_ = x, y_ = y, z_ = z;

            x_ /= right;
            y_ /= right;
            z_ /= right;

            tmp.setXYZ(x_, y_, z_);

            return tmp;
        }


        template <typename U>
        Vec3<T> operator /= (const U& right)
        {
            x /= right;
            y /= right;
            z /= right;

            return *this;
        }


        template <typename U>
        Vec3<T> operator /= (const Vec3<U>& right)
        {
            x /= right.x;
            y /= right.y;
            z /= right.z;

            return *this;
        }


        bool operator < (const Vec3<T> & right)
        {
            bool b = true;

            if( x < right.x && y < right.y && z < right.z)
                b = false;

            return b;

        }


        bool operator > (const Vec3<T> & right)
        {
            bool b = true;

            if( x < right.x && y < right.y && z < right.z)
                b = false;

            return b;

        }

        T getX() const
        {
            return x;
        }

        T getY() const
        {
            return y;
        }

        T getZ() const
        {
            return z;
        }

        T * getXY()
        {
            temp[0] = x;
            temp[1] = y;

            return temp;
        }

        T * getXYZ()
        {
            temp[0] = x;
            temp[1] = y;
            temp[2] = z;

            return temp;
        }

        void setX(T X)
        {
            x = X;
        }

        void setY(T Y)
        {
            y = Y;
        }

        void setZ(T Z)
        {
            z = Z;
        }

        void setXY(T X, T Y)
        {
            x = X;
            y = Y;
        }

        void setXYZ(T X, T Y, T Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

};



///////////////////
//4D Vector Class//
///////////////////

template<typename T>
class Vec4
{
    private:
        T x;
        T y;
        T z;
        T w;
        T temp[4];

    public:
        Vec4<T>()
        {
            x = 0;
            y = 0;
            z = 0;
            w = 1;
        }


        Vec4<T>(T x, T y, T z, T w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }


        template <typename U>
        Vec4<T>(const Vec4<U>& right)
        {
            x = right.x;
            y = right.y;
            z = right.z;
            w = right.w;
        }

        template <typename U>
        Vec4<T> operator = (const Vec4<U>& right)
        {
            x = right.x;
            y = right.y;
            z = right.z;
            w = right.w;

            return *this;
        }


        template <typename U>
        Vec4<T> operator = (const Vec2<U>& right)
        {
            x = right.getX();
            y = right.getY();

            return *this;
        }


        template <typename U>
        Vec4<T> operator = (const Vec3<U>& right)
        {
            x = right.getX();
            y = right.getY();
            z = right.getZ();

            return *this;
        }


        template <typename U>
        Vec4<T> operator + (const Vec4<U>& right)
        {
            Vec4<T> tmp;
            T x_ = x, y_ = y, z_ = z, w_ = w;

            x_ += right.x;
            y_ += right.y;
            z_ += right.z;
            w_ += right.w;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <typename U>
        Vec4<T> operator + (const U& right)
        {
            Vec4<T> tmp;
            T x_ = x, y_ = y, z_ = z, w_ = w;

            x_ += right;
            y_ += right;
            z_ += right;
            w_ += right;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <typename U>
        Vec4<T> operator += (const Vec4<U>& right)
        {
            x += right.x;
            y += right.y;
            z += right.z;
            w += right.w;

            return *this;
        }


        template <typename U>
        Vec4<T> operator += (const U& right)
        {
            x += right;
            y += right;
            z += right;
            w += right;

            return *this;
        }


        template <typename U>
        Vec4<T> operator - (const Vec4<U>& right)
        {
            Vec4<T> tmp;
            T x_ = x, y_ = y, z_ = z, w_ = w;

            x_ -= right.x;
            y_ -= right.y;
            z_ -= right.z;
            w_ -= right.w;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <typename U>
        Vec4<T> operator - (const U& right)
        {
            Vec4<T> tmp;
            T x_ = x, y_ = y, z_ = z, w_ = w;

            x_ -= right;
            y_ -= right;
            z_ -= right;
            w_ -= right;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <typename U>
        Vec4<T> operator -= (const Vec4<U>& right)
        {
            x -= right.x;
            y -= right.y;
            z -= right.z;
            w -= right.w;

            return *this;
        }


        template <typename U>
        Vec4<T> operator -= (const U& right)
        {
            x -= right;
            y -= right;
            z -= right;
            w -= right;

            return *this;
        }


        Vec4<T> operator - ()
        {
            Vec4<T> tmp;
            T x_ = x, y_ = y, z_ = z, w_ = w;

            x_ *= -1;
            y_ *= -1;
            z_ *= -1;
            //w_ *= -1;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <typename U>
        Vec4<T> operator * (const Vec4<U>& right)
        {
            Vec4<T> tmp;
            T x_ = x, y_ = y, z_ = z, w_ = w;

            x_ *= right.x;
            y_ *= right.y;
            z_ *= right.z;
            w_ *= right.w;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <typename U>
        Vec4<T> operator * (const U& right)
        {
            Vec4<T> tmp;
            T x_ = x, y_ = y, z_ = z, w_ = w;

            x_ *= right;
            y_ *= right;
            z_ *= right;
            w_ *= right;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <typename U>
        Vec4<T> operator *= (const Vec4<U>& right)
        {
            x *= right.x;
            y *= right.y;
            z *= right.z;
            w *= right.w;

            return *this;
        }


        template <typename U>
        Vec4<T> operator *= (const U& right)
        {
            x *= right;
            y *= right;
            z *= right;
            w *= right;

            return *this;
        }


        template <typename U>
        Vec4<T> operator / (const Vec4<U>& right)
        {
            Vec4<T> tmp;
            T x_ = x, y_ = y, z_ = z, w_ = w;

            x_ /= right.x;
            y_ /= right.y;
            z_ /= right.z;
            w_ /= right.w;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <typename U>
        Vec4<T> operator / (const U& right)
        {
            Vec4<T> tmp;
            T x_ = x, y_ = y, z_ = z, w_ = w;

            x_ /= right;
            y_ /= right;
            z_ /= right;
            w_ /= right;

            tmp.setXYZW(x_, y_, z_, w_);

            return tmp;
        }


        template <typename U>
        Vec4<T> operator /= (const U& right)
        {
            x /= right;
            y /= right;
            z /= right;
            w /= right;

            return *this;
        }


        template <typename U>
        Vec4<T> operator /= (const Vec4<U>& right)
        {
            x /= right.x;
            y /= right.y;
            z /= right.z;
            w /= right.w;

            return *this;
        }


        T getX() const
        {
            return x;
        }

        T getY() const
        {
            return y;
        }

        T getZ() const
        {
            return z;
        }

        T getW() const
        {
            return w;
        }

        T * getXY()
        {
            temp[0] = x;
            temp[1] = y;

            return temp;
        }

        T * getXYZ()
        {
            temp[0] = x;
            temp[1] = y;
            temp[2] = z;

            return temp;
        }

        T * getXYZW()
        {
            temp[0] = x;
            temp[1] = y;
            temp[2] = z;
            temp[3] = w;

            return temp;
        }

        void setX(T X)
        {
            x = X;
        }

        void setY(T Y)
        {
            y = Y;
        }

        void setZ(T Z)
        {
            z = Z;
        }

        void setW(T W)
        {
            w = W;
        }

        void setXY(T X, T Y)
        {
            x = X;
            y = Y;
        }

        void setXYZ(T X, T Y, T Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        void setXYZW(T X, T Y, T Z, T W)
        {
            x = X;
            y = Y;
            z = Z;
            w = W;
        }

};

//////////////////
//MATH FUNCTIONS//
//////////////////
template <typename T, typename U>
inline T Magnitude(Vec2<U> v)
{
    T r = 0;

    r = (v.getX()*v.getX()) + (v.getY()*v.getY());

    return sqrtf(r);
}



template <typename T, typename U>
inline T Magnitude(Vec3<U> v)
{
    T r = 0;

    r = (v.getX()*v.getX()) + (v.getY()*v.getY()) + (v.getZ()*v.getZ());

    return sqrtf(r);
}
template <typename T>
inline T Magnitude(Vec3<T> v)
{
    T r = 0;

    r = (v.getX()*v.getX()) + (v.getY()*v.getY()) + (v.getZ()*v.getZ());

    return sqrtf(r);
}



template <typename T, typename U>
inline T Magnitude(Vec4<U> v)
{
    T r = 0;

    r = (v.getX()*v.getX()) + (v.getY()*v.getY()) + (v.getZ()*v.getZ());

    return sqrtf(r);
}



template <typename T, typename U, typename V>
inline T DotProduct(Vec2<U> v, Vec2<V> u)
{
    T r = 0;

    r = v.getX()*u.getX() + v.getY()*u.getY();

    return r;
}



template <typename T, typename U, typename V>
inline T DotProduct(Vec3<U> v, Vec3<V> u)
{
    return v.getX()*u.getX() + v.getY()*u.getY() + v.getZ()*u.getZ();
}
template <typename T>
inline T DotProduct(Vec3<T> v, Vec3<T> u)
{
    return v.getX()*u.getX() + v.getY()*u.getY() + v.getZ()*u.getZ();
}



template <typename T, typename U, typename V>
inline T DotProduct(Vec4<U> v, Vec4<V> u)
{
    T r = 0;

    r = v.getX()*u.getX() + v.getY()*u.getY() + v.getZ()*u.getZ();

    return r;
}

template <typename T, typename U, typename V>
inline Vec3<T> CrossProduct(Vec3<U> v, Vec3<V> u)
{
    Vec3<T> r;

    r.setX( (v.getX()*u.getZ()) - (v.getZ()*u.getY()) );
    r.setY( (v.getZ()*u.getX()) - (v.getX()*u.getZ()) );
    r.setZ( (v.getX()*u.getY()) - (v.getY()*u.getX()) );

    return r;
}

template <typename T, typename U, typename V>
inline Vec4<T> CrossProduct(Vec4<U> v, Vec4<V> u)
{
    Vec4<T> r;

    r.setX( (v.getX()*u.getZ()) - (v.getZ()*u.getY()) );
    r.setY( (v.getZ()*u.getX()) - (v.getX()*u.getZ()) );
    r.setZ( (v.getX()*u.getY()) - (v.getY()*u.getX()) );

    return r;
}

template <typename T, typename U>
inline Vec2<T> Normalize(Vec2<U> v)
{
    return v / Magnitude(v);
}

template <typename T, typename U>
inline Vec3<T> Normalize(Vec3<U> v)
{
    return v / Magnitude(v);
}

template <typename T, typename U>
inline Vec4<T> Normalize(Vec4<U> v)
{
    return v / Magnitude(v);
}

template <typename T, typename U, typename V>
inline Vec2<T> Projection(Vec2<U> v, Vec2<V> u)
{
    return u * (DotProduct(v, u)/(Magnitude(u)*Magnitude(u)));
}



template <typename T, typename U, typename V>
inline Vec3<T> Projection(Vec3<U> v, Vec3<V> u)
{
    return (u * (DotProduct(v, u)/(Magnitude(u)*Magnitude(u))));
}
template <typename T>
inline Vec3<T> Projection(Vec3<T> v, Vec3<T> u)
{
    return (u * (DotProduct(v, u)/(Magnitude(u)*Magnitude(u))));
}

template <typename T, typename U, typename V>
inline Vec4<T> Projection(Vec4<U> v, Vec4<V> u)
{
    return u *(DotProduct(v, u)/(Magnitude(u)*Magnitude(u)));
}



template <typename T, typename U, typename V>
inline Vec2<T> Rotate2D(U angle, Vec2<V> v)
{
    return (v = Vec2<float>(v.getX() + cos(angle * (PI/180.0)) , v.getY() + sin(angle * (PI/180.0)) ));
}

template <typename T, typename U, typename V>
inline Vec3<T> Rotate2D(U angle, Vec3<V> v)
{
    return (v = Vec3<float>(v.getX() + cos(angle * (PI/180.0)) , v.getY() + sin(angle * (PI/180.0)) , v.getZ() ));
}

template <typename T, typename U, typename V>
inline Vec4<T> Rotate2D(U angle, Vec4<V> v)
{
    return (v = Vec4<float>(v.getX() + cos(angle * (PI/180.0)) , v.getY() + sin(angle * (PI/180.0)) , v.getZ(), v.getW() ));
}


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


template<typename T>
class Mat3X3
{


    public:

        T matrixA[9];

        Mat3X3<T>()
        {
            for(int i=0; i<9; i++)
                matrixA[i] = 0;
        }

        template<typename U>
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

        template<typename U>
        void operator= (const Mat3X3<U> & right)
        {
            for(int i=0; i<9; i++)
                this->matrixA[i] = right.matrixA[i];
        }

        template<typename U>
        Mat3X3<T> operator* (const Mat3X3<U> & right)
        {
            Mat3X3<T> tmp;

            tmp = MatrixMult((*this), right);

            return tmp;
        }

        template<typename U>
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

template<typename T>
class Mat4X4
{


    public:

        T matrixA[16];

        Mat4X4<T>()
        {
            for(int i=0; i<16; i++)
                matrixA[i] = 0;
        }

        template<typename U>
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
            for(int i=0; i<4; i++)
                matrixA[i+(i*4)] = 1;
        }

        template<typename U>
        void operator= (const Mat4X4<U> & right)
        {
            for(int i=0; i<16; i++)
                this->matrixA[i] = right.matrixA[i];
        }

        template<typename U>
        Mat4X4<T> operator* (const Mat4X4<U> & right)
        {
            Mat4X4<T> tmp;

            tmp = MatrixMult((*this), right);

            return tmp;
        }

        template<typename U>
        Mat4X4<T> operator*= (const Mat4X4<U> & right)
        {
            Mat4X4<T> tmp;

            tmp = MatrixMult((*this), right);

            matrixA = tmp.matrixA;

            return *this;
        }
};


template <typename T, typename U>
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

template <typename T, typename U, typename V>
inline Mat3X3<T> MatrixMult(const Mat3X3<U> & m, const Mat3X3<V> & n)
{
    Mat3X3<T> tmp;

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            for(int k=0; k<3; k++)
                tmp.matrixA[j + (i*3)] += m.matrixA[k + (i*3)] * n.matrixA[j + (k*3)];

    return tmp;
}

template <typename T, typename U, typename V>
inline Mat4X4<T> MatrixMult(const Mat4X4<U> & m, const Mat4X4<V> & n)
{
    Mat4X4<T> tmp;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                tmp.matrixA[j + (i*4)] += m.matrixA[k + (i*4)] * n.matrixA[j + (k*4)];

    return tmp;
}

template <typename T>
inline Mat4X4<T> MatrixMult(const Mat4X4<T> & m, const Mat4X4<T> & n)
{
    Mat4X4<T> tmp;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                tmp.matrixA[j + (i*4)] += m.matrixA[k + (i*4)] * n.matrixA[j + (k*4)];

    return tmp;
}

template <typename T, typename U>
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

template <typename T, typename U>
inline Mat3X3<T> MatrixTranspose(const Mat3X3<U> & m)
{
    Mat3X3<T> m_tmp;

    m_tmp.matrixA[0 ] = m.matrixA[0 ];   m_tmp.matrixA[1 ] = m.matrixA[3 ];   m_tmp.matrixA[2 ] = m.matrixA[6 ];
    m_tmp.matrixA[3 ] = m.matrixA[1 ];   m_tmp.matrixA[4 ] = m.matrixA[4 ];   m_tmp.matrixA[5 ] = m.matrixA[7 ];
    m_tmp.matrixA[6 ] = m.matrixA[2 ];   m_tmp.matrixA[7 ] = m.matrixA[5 ];   m_tmp.matrixA[8 ] = m.matrixA[8 ];


    return m_tmp;
}

template <typename T, typename U>
inline Mat4X4<T> MatrixTranspose(const Mat4X4<U> & m)
{
    Mat4X4<T> m_tmp;

    m_tmp.matrixA[0 ] = m.matrixA[0 ];   m_tmp.matrixA[1 ] = m.matrixA[4 ];   m_tmp.matrixA[2 ] = m.matrixA[8 ];   m_tmp.matrixA[3 ] = m.matrixA[12];
    m_tmp.matrixA[4 ] = m.matrixA[1 ];   m_tmp.matrixA[5 ] = m.matrixA[5 ];   m_tmp.matrixA[6 ] = m.matrixA[9 ];   m_tmp.matrixA[7 ] = m.matrixA[13];
    m_tmp.matrixA[8 ] = m.matrixA[2 ];   m_tmp.matrixA[9 ] = m.matrixA[6 ];   m_tmp.matrixA[10] = m.matrixA[10];   m_tmp.matrixA[11] = m.matrixA[14];
    m_tmp.matrixA[12] = m.matrixA[3 ];   m_tmp.matrixA[13] = m.matrixA[7 ];   m_tmp.matrixA[14] = m.matrixA[11];   m_tmp.matrixA[15] = m.matrixA[15];

    return m_tmp;
}

template <typename T, typename U>
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


template <typename T, typename U, typename V>
inline Vec4<T> matrixVecMultiply(const Mat4X4<U> & m, Vec4<V> v)
{
    Vec4<T> tmp;
    T tx, ty, tz, tw;
    T x=0, y=0, z=0, w=0;

    tx = v.getX();
    ty = v.getY();
    tz = v.getZ();
    tw = v.getW();

    for(int i=0; i<4; i++)
    {
        x += m.matrixA[i + (0*4)] * tx;
        y += m.matrixA[i + (1*4)] * ty;
        z += m.matrixA[i + (2*4)] * tz;
        w += m.matrixA[i + (3*4)] * tw;
    }

    tmp.setXYZW(x, y, z, w);

    return tmp;
}


/*////////////////////
//                  //
//      ALGEBRA     //
//    AND FUNCTION  //
//                  //
////////////////////*/


template <typename T>
inline T Degree2Radian(T angle)
{
    return angle*(PI/180);
}
template <typename T, typename U>
inline T Degree2Radian(U angle)
{
    return angle*(PI/180);
}


template <typename T>
inline T Radian2Degree(T angle)
{
    return angle*(180/PI);
}
template <typename T, typename U>
inline T Radian2Degree(U angle)
{
    return angle*(180/PI);
}

#endif
