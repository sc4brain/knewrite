#ifndef ___B_STACK_IMAGE_GENERATOR_H___
#define ___B_STACK_IMAGE_GENERATOR_H___

#include "MStackImage.h"
#include "CObjectCommunicator.h"

void fillCylinder(MStackImage *StackIMage,
                  POINT3D inStart, POINT3D inEnd, double r, unsigned char value);

//int generate_tree(MStackImage *StackImage);
int generate_tree(MStackImage *StackImage,
                  int bifurcatingNum = 5,       // param1
                  double a = 100,               // param2
                  double diam = 7.,             // param3
                  double b = 0.7,               // param4
                  double perturbationRatio = 0.1, // param5
                  unsigned char value = 255); // brightness

int generate_extraneous_object(MStackImage *StackImage,
                               double length,
                               double diam,
                               double rotationTheata, // degree
                               double rotationPhi, // degree
                               unsigned char value);


/* class BStackImageGenerator */
/* { */
/*  public: */
/*     BStackImageGenerator(); */
/*     ~BStackImageGenerator(); */

/*     enum GENERATING_IMAGETYPE { */
/*         TREE = 0, */
/*         GENERATABLE_MAXID, */
/*     }; */

/*     int generate(GENERATING_IMAGETYPE type); */
/*     MStackImage &getImage(void) const; */

/*  protected: */
/*     MStackImage *StackImage; */
/* }; */

#endif//___B_STACK_IMAGE_GENERATOR_H___
