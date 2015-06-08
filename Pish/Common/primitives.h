#ifndef PRIMITIVES_H
#define PRIMITIVES_H

template < class T >
class CVert2
{
    private:
        T x;
        T y;

    public:

        CVert2()
        {
            x = y = 0;
        }

        CVert2(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        void setPos(T a)
        {
            x = a;
        }

        void setPos(T a, T b)
        {
            x = a;
            y = b;
        }

        T getPointX()
        {
            return x;
        }

        T getPointY()
        {
            return y;
        }

        T * getPoint(int xy = 0)
        {
            switch(xy)
            {
                case 0:
                    return &x;
                break;

                case 1:
                    return &y;
                break;

                default:
                    return &x;
                break;
            }

        }

};

template < class T >
class CVert3
{
    private:
        T x;
        T y;
        T z;

    public:

        CVert3()
        {
            x = y = z = 0;
        }

        CVert3(T x, T y, T z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        void setPos(T a)
        {
            x = a;
        }

        void setPos(T a, T b)
        {
            x = a;
            y = b;
        }

        void setPos(T a, T b, T c)
        {
            x = a;
            y = b;
            z = c;
        }

        T getPointX()
        {
            return x;
        }

        T getPointY()
        {
            return y;
        }

        T getPointZ()
        {
            return z;
        }

        T * getPoint(int xyz)
        {
            switch(xyz)
            {
                case 0:
                    return &x;
                break;

                case 1:
                    return &y;
                break;

                case 2:
                    return &z;
                break;

                default:
                    return &x;
                break;
            }

        }

};


template < class T >
class CVert4
{
    private:
        T x;
        T y;
        T z;
        T w;

    public:

        CVert4()
        {
            x = y = z = 0;
            w = 1;
        }

        CVert4(T x, T y, T z, T w = 1)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        void setPos(T a)
        {
            x = a;
        }

        void setPos(T a, T b)
        {
            x = a;
            y = b;
        }

        void setPos(T a, T b, T c)
        {
            x = a;
            y = b;
            z = c;
        }

        void setPos(T a, T b, T c, T d)
        {
            x = a;
            y = b;
            z = c;
            w = d;
        }

        T getPointX()
        {
            return x;
        }

        T getPointY()
        {
            return y;
        }

        T getPointZ()
        {
            return z;
        }

        T getPointW()
        {
            return w;
        }

        T * getPoint(int xyzw)
        {
            switch(xyzw)
            {
                case 0:
                    return &x;
                break;

                case 1:
                    return &y;
                break;

                case 2:
                    return &z;
                break;

                case 3:
                    return &w;
                break;

                default:
                    return &x;
                break;
            }

        }

};

template < class T >
class CTexCoord2
{
    private:
        T u;
        T v;

    public:

        CTexCoord2()
        {
            u = v = 0;
        }

        void setPos(T a)
        {
            u = a;
        }

        void setPos(T a, T b)
        {
            u = a;
            v = b;
        }

        CTexCoord2<T> operator= (CTexCoord2<GLfloat> texC)
        {
            this->u = texC.u;
            this->v = texC.v;

            return (*this);
        }
};

template < class T >
class CTexCoord3
{
    private:
        T u;
        T v;
        T p;

    public:

        CTexCoord3()
        {
            u = v = p = 0;
        }

        void setPos(T a)
        {
            u = a;
        }

        void setPos(T a, T b)
        {
            u = a;
            v = b;
        }

        void setPos(T a, T b, T c)
        {
            u = a;
            v = b;
            p = c;
        }
};

#endif
