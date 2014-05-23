
#include "BCommon.h"

#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

static int genRandUniform_initialized = 0;

double getRandUniform_gen(void)
{
    return rand()/(1.0 + RAND_MAX);
}

double getRandUniform_init(void)
{
    srand((unsigned)time(NULL));
    genRandUniform_initialized = 1;
    return getRandUniform_gen();
}

double getRandUniform(void)
{
    static double (*func[2])(void)
        = {getRandUniform_init, getRandUniform_gen};
    return func[genRandUniform_initialized]();
}

double getRandNormal(double mean, double SD)
{
    double u1 = getRandUniform();
    double u2 = getRandUniform();
    double n1 = mean + SD * sqrt(-2 * log(u1)) * sin(2 * PI * u2);
    //double n2 = mean + SD * sqrt(-2 * log(u1)) * cos(2 * PI * u2);
    return n1;
}

int issign(char c)
{
    if (c == '+') return 1;
    if (c == '-') return 1;
    return 0;
}

int isdot(char c)
{
    if (c == '.') return 1;
    return 0;
}

int isStrNumber(const char *str)
{
    int isFloat = 0;

    if (!str) { return -1; }

    int length = strlen(str);

    if (length <= 0) { return -2; }

    if (str[0] == ' ') { return isStrNumber(str+1); }

    if (!isdigit(str[0]) && !issign(str[0]) && !isdot(str[0])) { return 0; }

    for (int i = 1; i < length; i++) {
        if (!isdigit(str[i]) && !isdot(str[i])) {
            return 0;
        }
        if (isdot(str[i])) {
            if (isFloat == 1) {
                return 0;
            } else {
                isFloat = 1;
            }
        }
    }

    return 1 + isFloat;
}

// r, g, b : 0.0 ~ 1.0
// h       : 0.0 ~ 360.0
// s, v    : 0.0 ~ 1.0
int rgb2hsv(double r, double g, double b, double *h, double *s, double *v)
{
    double rgb[3] = {r, g, b};
    double max = 0., min = 0.;
    int maxi = 0;
    for (int i = 0; i < 3; i++) {
        if (max < rgb[i]) {
            max = rgb[i];
            maxi = i;
        } else if (min > rgb[i]) {
            min = rgb[i];
        }
    }

    *h = 60. * (rgb[(maxi + 1)%3] - rgb[(maxi + 2)%3]) / (max - min)
        + 120 * maxi;
    *s = (max - min) / max;
    *v = max;
    
    return 0;
}

// r, g, b, s, v : 0.0 ~ 1.0
// h             : 0.0 ~ 360.0
int hsv2rgb(double h, double s, double v, double *r, double *g, double *b)
{
    int hi = (int)(h / 60) % 6;
    double f = h / 60. - hi;
    double p = v * (1. - s);
    double q = v * (1. - f * s);
    double t = v * (1. - (1. - f) * s);

    switch (hi) {
        case 0: *r = v; *g = t; *b = p; break;
        case 1: *r = q; *g = v; *b = p; break;
        case 2: *r = p; *g = v; *b = t; break;
        case 3: *r = p; *g = q; *b = v; break;
        case 4: *r = t; *g = p; *b = v; break;
        case 5: *r = v; *g = p; *b = q; break;
    }
}
