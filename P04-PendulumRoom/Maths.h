#ifndef MATHS_H
#define MATHS_H


/** \brief gravitational acceleration in m / ms^2
 */
constexpr float g()
{
    return 0.00000981f;   
} 


constexpr float pi()
{
    return 3.141592f;
}


constexpr float twoPi()
{
    return 2.0f * pi();
}


inline float radians(float degrees)
{
    return degrees * pi() / 180.0f;
}


#endif // MATHS_H