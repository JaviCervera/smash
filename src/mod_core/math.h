#ifndef CORE_MATH_H
#define CORE_MATH_H

#include <math.h>

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

class Math {
public:
    static double Pi() { return 3.14159265359; }
    static double Floor(double val) { return floor(val); }
    static double Ceil(double val) { return ceil(val); }
    static long Abs(long val) { return abs(val); }
    static double FAbs(double val) { return fabs(val); }
    static double Sqr(double val) { return sqrt(val); }
    static double DegSin(double val) { return sin(val * DEG2RAD); }
    static double DegCos(double val) { return cos(val * DEG2RAD); }
    static double DegTan(double val) { return tan(val * DEG2RAD); }
    static double DegASin(double val) { return asin(val) * RAD2DEG; }
    static double DegACos(double val) { return acos(val) * RAD2DEG; }
    static double DegATan(double val) { return atan(val) * RAD2DEG; }
    static double DegATan2(double y, double x) { return atan2(y, x) * RAD2DEG; }
    static double Exp(double val) { return exp(val); }
    static double Log(double val) { return log(val); }
    static double Log10(double val) { return log10(val); }
    static int Rand(int min, int max) { return min + (rand() % ((max - min) + 1)); }
    static double FRand(double min, double max) { return Rand((int)min * 1000000, (int)max * 1000000) / 1000000.0; }
    static void SeedRand(unsigned int seed) { srand(seed); }
    static double Wrap(double value, double module) { if (module == 0) return value; return value - module*floor(value/module); }
protected:
    Math() {}
};

#undef DEG2RAD
#undef RAD2DEG

#endif // CORE_MATH_H
