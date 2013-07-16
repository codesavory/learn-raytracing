#ifndef __SMALLPT_UTILS_H__
#define __SMALLPT_UTILS_H__

#define _USE_MATH_DEFINES
#include <math.h>

struct RandomLCG 
{
    unsigned mSeed;
    RandomLCG(unsigned seed = 0) : mSeed(seed) {}
    float operator()() { mSeed = 214013 * mSeed + 2531011; return mSeed * (1.0f / 4294967296); }
};

struct Vec 
{   
    double x, y, z;                  // position, also color (r, g,b)

    Vec(double x_= 0, double y_= 0, double z_= 0)
    { 
        x = x_; 
        y = y_; 
        z = z_; 
    }

    Vec operator+(const Vec &b) const 
    { 
        return Vec(x + b.x, y + b.y, z + b.z); 
    }

    Vec operator-(const Vec &b) const 
    { 
        return Vec(x-b.x, y-b.y, z-b.z); 
    }

    Vec operator*(double b) const 
    { 
        return Vec(x * b, y * b, z * b);
    }

    Vec mult(const Vec &b) const
    { 
        return Vec(x * b.x, y * b.y, z * b.z);
    }

    Vec& norm()
    { 
        return *this = *this * (1/sqrt(x * x + y * y + z * z)); 
    }

    double dot(const Vec &b) const
    { 
        return x * b.x + y * b.y + z * b.z; 
    }

    Vec cross(const Vec &b)
    {
        return Vec(y * b.z-z * b.y, z * b.x-x * b.z, x * b.y-y * b.x);
    }
};

struct Ray 
{
    Vec orig, dir; 
    Ray(const Vec &o_, const Vec &d_) : orig(o_), dir(d_) {} 
};

inline double clamp(double x){ return x<0 ? 0 : x>1 ? 1 : x; }

inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }

inline double tentFilterRandom(RandomLCG& Xi)
{
    double r = 2 * Xi();
    return r < 1 ? sqrt(r)-1: 1-sqrt(2-r);
}

#endif // __SMALLPT_UTILS_H__