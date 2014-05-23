
#include <QtGui>
#include <math.h>

#include "BRodriguez2009Cluster.h"
#include "BStackImageGenerator.h"
#include "BCommon.h"

// BStackImageGenerator::BStackImageGenerator(void)
// {
//     StackImage = NULL;
// }

// BStackImageGenerator::~BStackImageGenerator(void)
// {
//     SAFEDELETE(StackImage);
// }

#define MODULATED_RANDOM(a, mean, sd) ((a) * getRandNormal((mean), (sd)))

void fillCylinder(MStackImage *StackImage,
                  POINT3D inStart, POINT3D inEnd, double r, unsigned char value)
{
    struct {
        struct {
            int x;
            int y;
            int z;
        } from;
        struct {
            int x;
            int y;
            int z;
        } to;
    } drawRange;

    // dprintf("fillCylinder " \
    //         "StackImage = %p, " \
    //         "start (%f, %f, %f), " \
    //         "end (%f, %f, %f), " \
    //         "r = %f\n",
    //         StackImage,
    //         inStart.x, inStart.y, inStart.z,
    //         inEnd.x, inEnd.y, inEnd.z,
    //         r);

    QVector3D start(inStart.x, inStart.y, inStart.z);
    QVector3D end(inEnd.x, inEnd.y, inEnd.z);
    drawRange.from.x = start.x() - r;
    drawRange.from.y = start.y() - r;
    drawRange.from.z = start.z() - r;
    drawRange.to.x = start.x() + r;
    drawRange.to.y = start.y() + r;
    drawRange.to.z = start.z() + r;

    if (r < 1.2) {
        r = 1.2;
    }

    int sizex = StackImage->getX();
    int sizey = StackImage->getY();
    int sizez = StackImage->getZ();
    int pageSize = sizex * sizey;
    double rr = r * r;

    double zDist = end.z() - start.z();
    QVector3D axisVector(end.x() - start.x(),
                         end.y() - start.y(),
                         end.z() - start.z());
    double length
        = axisVector.x() * axisVector.x()
        + axisVector.y() * axisVector.y()
        + axisVector.z() * axisVector.z();
    length = sqrt(length);
    QVector3D normalVector(axisVector);
    normalVector.normalize();

    QList<QVector3D> brushedCirleVoxels;

    // fill boundary plane
    for (int k = drawRange.from.z; k < drawRange.to.z; k++) {
        int pageStep = pageSize * k;
        int dz = start.z() - k;
        int dz2 = dz * dz;
        for (int j = drawRange.from.y; j < drawRange.to.y; j++) {
            int overHead = pageStep + sizex * j;
            int dy = start.y() - j;
            int dy2 = dy * dy;
            for (int i = drawRange.from.x; i < drawRange.to.x; i++) {
                int dx = start.x() - i;
                int dx2 = dx * dx;
                QVector3D voxelPos(i, j, k);
                double d = voxelPos.distanceToPlane(start, normalVector);
                if (dx2 + dy2 + dz2 > rr || 3 < d * d) {
                    continue;
                }
                // dprintf("generate_tree added voxelPos (%f, %f, %f)\n",
                //         voxelPos.x(), voxelPos.y(), voxelPos.z());
                brushedCirleVoxels.append(voxelPos);
                //StackImage->setData(overHead + i, 255);
            }
        }
    }

    if (brushedCirleVoxels.count() == 0) {
        brushedCirleVoxels.append(start);
        // QVector3D tempx(start.x()-1, start.y(), start.z());
        // brushedCirleVoxels.append(tempx);
        // tempx.setX(tempx.x() + 1);
        // brushedCirleVoxels.append(tempx);
        // tempx.setX(tempx.x() + 1);
        // brushedCirleVoxels.append(tempx);
        // QVector3D tempy(start.x(), start.y()-1, start.z());
        // brushedCirleVoxels.append(tempy);
        // tempy.setX(tempy.x() + 1);
        // brushedCirleVoxels.append(tempy);
        // tempy.setX(tempy.x() + 1);
        // brushedCirleVoxels.append(tempy);
        // QVector3D tempz(start.x(), start.y()-1, start.z());
        // brushedCirleVoxels.append(tempz);
        // tempz.setX(tempz.x() + 1);
        // brushedCirleVoxels.append(tempz);
        // tempz.setX(tempz.x() + 1);
        // brushedCirleVoxels.append(tempz);
    }

    // fill cylinder body
    //for (double z = start.z(); z < end.z(); z += 1) {
    for (int i = 0; ; i++) {
        QVector3D shiftVector(i * normalVector);
        // dprintf("generate_tree shiftVector.length() = %f\n",
        //         shiftVector.length());
        if (shiftVector.length() > length) break;
        for (int j = 0; j < brushedCirleVoxels.count(); j++) {
            QVector3D curTargetVoxel(brushedCirleVoxels[j] + shiftVector);
            StackImage->setData((int)curTargetVoxel.x(),
                                (int)curTargetVoxel.y(),
                                (int)curTargetVoxel.z(),
                                value);
        }
    }
    // dprintf("generate_tree brushedCirleVoxels.count() = %d\n",
    //         brushedCirleVoxels.count());

    // boundary treatment : start plane
    for (int k = drawRange.from.z; k < drawRange.to.z; k++) {
        int pageStep = pageSize * k;
        int dz = start.z() - k;
        int dz2 = dz * dz;
        for (int j = drawRange.from.y; j < drawRange.to.y; j++) {
            int overHead = pageStep + sizex * j;
            int dy = start.y() - j;
            int dy2 = dy * dy;
            for (int i = drawRange.from.x; i < drawRange.to.x; i++) {
                int dx = start.x() - i;
                int dx2 = dx * dx;
                if (dx2 + dy2 + dz2 <= rr) {
                    //dprintf("*");
                    StackImage->setData(overHead + i, value);
                }
            }
        }
    }
    //dprintf("\n");

    drawRange.from.x = end.x() - r;
    drawRange.from.y = end.y() - r;
    drawRange.from.z = end.z() - r;
    drawRange.to.x = end.x() + r;
    drawRange.to.y = end.y() + r;

    drawRange.to.z = end.z() + r;
    // boundary treatment : end plane
    for (int k = drawRange.from.z; k < drawRange.to.z; k++) {
        int pageStep = pageSize * k;
        int dz = end.z() - k;
        int dz2 = dz * dz;
        for (int j = drawRange.from.y; j < drawRange.to.y; j++) {
            int overHead = pageStep + sizex * j;
            int dy = end.y() - j;
            int dy2 = dy * dy;
            for (int i = drawRange.from.x; i < drawRange.to.x; i++) {
                int dx = end.x() - i;
                int dx2 = dx * dx;
                if (dx2 + dy2 + dz2 <= rr) {
                    StackImage->setData(overHead + i, value);
                }
            }
        }
    }
}

int generate_tree(MStackImage *StackImage, int bifurcatingNum,
                  double a, double diam, double b, double perturbationRatio,
                  unsigned char value)
{
    int sizex = 512;
    int sizey = 512;
    int sizez = 512;
    int length = sizex * sizey * sizez;
    double scalex = 1.;
    double scaley = 1.;
    double scalez = 1.;
    //StackImage = new MStackImage(sizex, sizey, sizez);
    StackImage->reset(sizex, sizey, sizez);
    StackImage->setScaleX(scalex);
    StackImage->setScaleY(scaley);
    StackImage->setScaleZ(scalez);

    // int bifurcatingNum = 7;
    // double a = 100.;
    // double b = 0.1;
    // double diam = 10.;
    double r = diam / 2;

    // start point
    int sx = sizex / 3;
    int sy = sizey / 2;
    int sz = 10 * r;

    struct {
        struct {
            double x;
            double y;
            double z;
        } from;
        struct {
            double x;
            double y;
            double z;
        } to;
    } boundingBox; 

    double *attenuationTable = new double[bifurcatingNum + 1];

    for (int i = 0; i <= bifurcatingNum; i++) {
        attenuationTable[i] = exp(-b * i);
        dprintf("generate_tree attenuationTable[%d] = %f\n",
                i, attenuationTable[i]);
    }

    double coef1_r3 = 1 / sqrt(3.);
    double coef1_2r3 = coef1_r3 / 2.;
    double coefr2_r3 = sqrt(1.5);
    double allongement = a;
    for (int i = 0; i < bifurcatingNum; i++) {
        double ai = a * attenuationTable[i];
        allongement += ai;
        if (sx - coef1_2r3 * ai - r < 0
            || sizex < sx + coef1_2r3 * ai + r
            || sy - 0.5 * ai - r < 0
            || sizey < sy + 0.5 * ai + r
            || sz - 10 * r < 0
            || sizez < 10 * r + allongement + coefr2_r3 * ai) {
            bifurcatingNum = i - 1;
            break;
        }
    }

    dprintf("generate_tree bifurcatingNum = %d\n", bifurcatingNum);

    // initialize
    StackImage->reset();

    QList<POINT3D> startList;
    QList<POINT3D> startListNew;
    startList.append(POINT3D(sx, sy, sz));

    RodClusterList ClusterList;
    ClusterList.setScaling(1., 1., 1.);
    RodCluster *curCluster = new RodCluster;
    curCluster->setNode(POINT3D(sx, sy, sz));
    curCluster->setDiam(r*2);
    curCluster->setDistance(0);
    ClusterList.addCluster(curCluster);

    QList<RodCluster *> curClusterList;
    QList<RodCluster *> curClusterListNew;
    curClusterList.append(curCluster);

    double unitCompartmentLength = 5.; // um
    double diamPerturbationRatio = perturbationRatio / 5.;

    for (int i = 0; i < bifurcatingNum; i++) {
        dprintf("generate_tree %dth bifercation\n", i+1);
        double ai = a * attenuationTable[i];
        double ri = r * attenuationTable[i];
        int divisionPerOneBranch = ai / unitCompartmentLength;
        startListNew.clear();
        curClusterListNew.clear();
        for (int j = 0; j < startList.count(); j++) {
            POINT3D start;
            POINT3D end;
            double curR;

            start.x = startList[j].x;
            start.y = startList[j].y;
            start.z = startList[j].z;

            RodCluster *curParentCluster = curClusterList[j];

            // allongement branch
            for (int k = 1; k < divisionPerOneBranch; k++) {
                end.x = start.x + MODULATED_RANDOM(perturbationRatio, 0, 1);
                end.y = start.y + MODULATED_RANDOM(perturbationRatio, 0, 1);
                end.z = start.z + unitCompartmentLength + MODULATED_RANDOM(perturbationRatio, 0, 1);
                curR = getRandNormal(ri * 1.3, ri * diamPerturbationRatio);
                //curR = ri + getRandNormal(ri, ri * diamPerturbationRatio);

                // stackimage
                fillCylinder(StackImage, start, end, curR, value);

                // cluster list
                curCluster = new RodCluster();
                curCluster->setNode(end);
                curCluster->setDiam(curR * 2);
                curCluster->setDistance(curParentCluster->getDistance() + 1);
                curCluster->addParent(curParentCluster);
                ClusterList.addCluster(curCluster);
                curParentCluster->addChild(curCluster);
                start.x = end.x;
                start.y = end.y;
                start.z = end.z;
                curParentCluster = curCluster;
            }
            end.x = startList[j].x;
            end.y = startList[j].y;
            end.z = startList[j].z + ai;
            //curR = ri + getRandNormal(ri, ri * diamPerturbationRatio);
            curR = getRandNormal(ri * 1.3, ri * diamPerturbationRatio);
            fillCylinder(StackImage, start, end, curR, value);
            curCluster = new RodCluster();
            curCluster->setNode(end);
            curCluster->setDiam(curR * 2);
            curCluster->setDistance(curParentCluster->getDistance() + 1);
            curCluster->addParent(curParentCluster);
            ClusterList.addCluster(curCluster);
            curParentCluster->addChild(curCluster);
            start.x = end.x;
            start.y = end.y;
            start.z = end.z;
             curParentCluster = curCluster;

            RodCluster *endPointClusterOfAllongementBranch = curCluster;
            POINT3D endPointOfAllongementBranch;
            endPointOfAllongementBranch.x = end.x;
            endPointOfAllongementBranch.y = end.y;
            endPointOfAllongementBranch.z = end.z;

            // alpha branch
            for (int k = 1; k < divisionPerOneBranch; k++) {
                end.x = start.x + coef1_r3 * (unitCompartmentLength) + MODULATED_RANDOM(perturbationRatio, 0, 1);
                end.y = start.y + 0 + MODULATED_RANDOM(perturbationRatio, 0, 1);
                end.z = start.z + coefr2_r3 * (unitCompartmentLength) + MODULATED_RANDOM(perturbationRatio, 0, 1);
                curR = getRandNormal(ri, ri * diamPerturbationRatio);
                //curR = ri + getRandNormal(ri, ri * diamPerturbationRatio);
                fillCylinder(StackImage, start, end, curR, value);
                curCluster = new RodCluster();
                curCluster->setNode(end);
                curCluster->setDiam(curR * 2);
                curCluster->setDistance(curParentCluster->getDistance() + 1);
                curCluster->addParent(curParentCluster);
                curParentCluster->addChild(curCluster);
                ClusterList.addCluster(curCluster);
                start.x = end.x;
                start.y = end.y;
                start.z = end.z;
                curParentCluster = curCluster;
            }
            end.x = endPointOfAllongementBranch.x + coef1_r3 * ai + MODULATED_RANDOM(perturbationRatio, 0, 1);
            end.y = endPointOfAllongementBranch.y + 0 + MODULATED_RANDOM(perturbationRatio, 0, 1);
            end.z = endPointOfAllongementBranch.z + coefr2_r3 * ai + MODULATED_RANDOM(perturbationRatio, 0, 1);
            curR = getRandNormal(ri, ri * diamPerturbationRatio);
            //curR = ri + getRandNormal(ri, ri * diamPerturbationRatio);
            fillCylinder(StackImage, start, end, curR, value);
            curCluster = new RodCluster();
            curCluster->setNode(end);
            curCluster->setDiam(curR * 2);
            curCluster->setDistance(curParentCluster->getDistance() + 1);
            curCluster->addParent(curParentCluster);
            curParentCluster->addChild(curCluster);
            ClusterList.addCluster(curCluster);
            startListNew.append(end);
            curClusterListNew.append(curCluster);

            start.x = endPointOfAllongementBranch.x;
            start.y = endPointOfAllongementBranch.y;
            start.z = endPointOfAllongementBranch.z;
            curParentCluster = endPointClusterOfAllongementBranch;

            // beta branch
            for (int k = 1; k < divisionPerOneBranch; k++) {
                end.x = start.x - coef1_2r3 * (unitCompartmentLength) + MODULATED_RANDOM(perturbationRatio, 0, 1);
                end.y = start.y - 0.5 * (unitCompartmentLength) + MODULATED_RANDOM(perturbationRatio, 0, 1);
                end.z = start.z + coefr2_r3 * (unitCompartmentLength) + MODULATED_RANDOM(perturbationRatio, 0, 1);
                curR = getRandNormal(ri, ri * diamPerturbationRatio);
                //curR = ri + getRandNormal(ri, ri * diamPerturbationRatio);
                fillCylinder(StackImage, start, end, curR, value);
                curCluster = new RodCluster();
                curCluster->setNode(end);
                curCluster->setDiam(curR * 2);
                curCluster->setDistance(curParentCluster->getDistance() + 1);
                curCluster->addParent(curParentCluster);
                curParentCluster->addChild(curCluster);
                ClusterList.addCluster(curCluster);
                start.x = end.x;
                start.y = end.y;
                start.z = end.z;
                curParentCluster = curCluster;
            }
            end.x = endPointOfAllongementBranch.x - coef1_2r3 * ai + MODULATED_RANDOM(perturbationRatio, 0, 1);
            end.y = endPointOfAllongementBranch.y - 0.5 * ai + MODULATED_RANDOM(perturbationRatio, 0, 1);
            end.z = endPointOfAllongementBranch.z + coefr2_r3 * ai + MODULATED_RANDOM(perturbationRatio, 0, 1);
            curR = getRandNormal(ri, ri * diamPerturbationRatio);
            //curR = ri + getRandNormal(ri, ri * diamPerturbationRatio);
            fillCylinder(StackImage, start, end, curR, value);
            curCluster = new RodCluster();
            curCluster->setNode(end);
            curCluster->setDiam(curR * 2);
            curCluster->setDistance(curParentCluster->getDistance() + 1);
            curCluster->addParent(curParentCluster);
            curParentCluster->addChild(curCluster);
            ClusterList.addCluster(curCluster);
            startListNew.append(end);
            curClusterListNew.append(curCluster);

            start.x = endPointOfAllongementBranch.x;
            start.y = endPointOfAllongementBranch.y;
            start.z = endPointOfAllongementBranch.z;
            curParentCluster = endPointClusterOfAllongementBranch;

            // gamma branch
            for (int k = 1; k < divisionPerOneBranch; k++) {
                end.x = start.x - coef1_2r3 * (unitCompartmentLength) + MODULATED_RANDOM(perturbationRatio, 0, 1);
                end.y = start.y + 0.5 * (unitCompartmentLength) + MODULATED_RANDOM(perturbationRatio, 0, 1);
                end.z = start.z + coefr2_r3 * (unitCompartmentLength) + MODULATED_RANDOM(perturbationRatio, 0, 1);
                curR = getRandNormal(ri, ri * diamPerturbationRatio);
                //curR = ri + getRandNormal(ri, ri * diamPerturbationRatio);
                fillCylinder(StackImage, start, end, curR, value);
                curCluster = new RodCluster();
                curCluster->setNode(end);
                curCluster->setDiam(curR * 2);
                curCluster->setDistance(curParentCluster->getDistance() + 1);
                curCluster->addParent(curParentCluster);
                curParentCluster->addChild(curCluster);
                ClusterList.addCluster(curCluster);
                start.x = end.x;
                start.y = end.y;
                start.z = end.z;
                curParentCluster = curCluster;
            }
            end.x = endPointOfAllongementBranch.x - coef1_2r3 * ai + MODULATED_RANDOM(perturbationRatio, 0, 1);
            end.y = endPointOfAllongementBranch.y + 0.5 * ai + MODULATED_RANDOM(perturbationRatio, 0, 1);
            end.z = endPointOfAllongementBranch.z + coefr2_r3 * ai + MODULATED_RANDOM(perturbationRatio, 0, 1);
            curR = getRandNormal(ri, ri * diamPerturbationRatio);
            //curR = ri + getRandNormal(ri, ri * diamPerturbationRatio);
            fillCylinder(StackImage, start, end, curR, value);
            curCluster = new RodCluster();
            curCluster->setNode(end);
            curCluster->setDiam(curR * 2);
            curCluster->setDistance(curParentCluster->getDistance() + 1);
            curCluster->addParent(curParentCluster);
            curParentCluster->addChild(curCluster);
            ClusterList.addCluster(curCluster);
            startListNew.append(end);
            curClusterListNew.append(curCluster);

            start.x = endPointOfAllongementBranch.x;
            start.y = endPointOfAllongementBranch.y;
            start.z = endPointOfAllongementBranch.z;
            curParentCluster = endPointClusterOfAllongementBranch;
        }
        startList = startListNew;
        curClusterList = curClusterListNew;
    }

    for (unsigned int i = 0; i < ClusterList.getClusterNum(); i++) {
        RodCluster *curCluster = ClusterList.getCluster(i);
        curCluster->setClusterNo(i);
        curCluster->setNodeNo(i);
    }
    ClusterList.print("generated_tree_structure.txt");

    ASAFEDELETE(attenuationTable);

    dprintf("generate_tree finished\n");

    return 0;
}

// int BStackImageGenerator::generate(GENERATING_IMAGETYPE type)
// {
//     int ret;

//     switch (type)
//     {
//         case BStackImageGenerator::TREE:
//             ret = generate_tree(StackImage);
//             break;
//     }
//     return ret;
// }


int generate_extraneous_object(MStackImage *StackImage,
                               double length,
                               double diam,
                               double rotationTheata,
                               double rotationPhi,
                               unsigned char value)
{
    if (StackImage == NULL) return -1;

    int sizex =  StackImage->getX();
    int sizey =  StackImage->getY();
    int sizez =  StackImage->getZ();
    double scalex = StackImage->getScaleX();
    double scaley = StackImage->getScaleY();
    double scalez = StackImage->getScaleZ();

    double r = diam / 2.;

    rotationTheata = rotationTheata / 180. * PI; // degree 2 radian
    rotationPhi = rotationPhi / 180. * PI; // degree 2 radian

    double cosPhi = cos(rotationPhi);
    QVector3D direction(cosPhi * cos(rotationTheata),
                        cosPhi * sin(rotationTheata),
                        sin(rotationPhi));

    dprintf("generate_extraneous_object " \
            "length = %f, " \
            "diam = %f, " \
            "rotation (%f, %f), " \
            "value = %u\n",
            length, diam, rotationTheata, rotationPhi, value);

    POINT3D basePoint(getRandNormal(sizex / 3, 30),
                      getRandNormal(sizey / 2, 30),
                      getRandNormal(sizez * 3 / 4, 30));
    POINT3D start(basePoint.x + direction.x() * length / 2,
                  basePoint.y + direction.y() * length / 2,
                  basePoint.z + direction.z() * length / 2);
    POINT3D end(basePoint.x - direction.x() * length / 2,
                basePoint.y - direction.y() * length / 2,
                basePoint.z - direction.z() * length / 2);

    if (start.x < diam) start.x = 0;
    if (start.y < diam) start.y = 0;
    if (start.z < diam) start.z = 0;
    if (sizex < start.x + diam) start.x = sizex - diam;
    if (sizex < start.y + diam) start.y = sizex - diam;
    if (sizex < start.z + diam) start.z = sizex - diam;
    if (end.x < diam) end.x = 0;
    if (end.y < diam) end.y = 0;
    if (end.z < diam) end.z = 0;
    if (sizex < end.x + diam) end.x = sizex - diam;
    if (sizex < end.y + diam) end.y = sizex - diam;
    if (sizex < end.z + diam) end.z = sizex - diam;

    dprintf("generate_extraneous_object " \
            "start (%f, %f, %f), " \
            "end (%f, %f, %f)\n",
            start.x, start.y, start.z,
            end.x, end.y, end.z);

    fillCylinder(StackImage, start, end, r, value);

    return 0;
}
