/* 
 * File:   common.h
 * Author: naska
 *
 * Created on 2010/10/28, 18:49
 */

#ifndef ___COMMON_H___
#define	___COMMON_H___

#define ___DEBUG___

#ifdef ___DEBUG___
#define ___SETTING_FOR_DEBUG___
#endif

#ifdef ___DEBUG___
#include <stdio.h>
#define dprintf(format, ...) { printf((format), ##__VA_ARGS__); fflush(stdout); }
#define dputs(message) { puts(message); fflush(stdout); }
#else
#define dprintf(format, ...) {};
#define dputs(message) {};
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef SAFEDELETE
#define SAFEDELETE(p)   if ((p) != NULL) { delete (p); (p) = NULL; }
#endif

#ifndef ASAFEDELETE
#define ASAFEDELETE(p)  if ((p) != NULL) { delete[] (p); (p) = NULL; }
#endif

#ifndef PI
#define PI 3.1415926535897932384626
#endif

#ifndef POSITIVE_PASS
#define POSITIVE_PASS(value) (((value) > 0) * (value))
#endif

#ifndef CLIP_VALUE_INT
#define CLIP_VALUE_INT(value, threshold) ((!!((value)/threshold))*((threshold)-1) \
                                          + (!((value)/threshold))*((value)%(threshold)))
#endif

// random value generator
double getRandUniform(void);
double getRandNormal(double mean, double SD);

/**
 *
 * @param str
 * @return integer:1, float:2, non numerical number: 0, error: negative
 */
int isStrNumber(const char *str);


// r, g, b : 0.0 ~ 1.0
// h       : 0.0 ~ 360.0
// s, v    : 0.0 ~ 1.0
int rgb2hsv(double r, double g, double b, double *h, double *s, double *v);

// r, g, b, s, v : 0.0 ~ 1.0
// h             : 0.0 ~ 360.0
int hsv2rgb(double h, double s, double v, double *r, double *g, double *b);

#endif	/* COMMON_H */
