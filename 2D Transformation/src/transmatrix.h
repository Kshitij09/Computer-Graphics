#ifndef TRANSMATRIX_H
#define TRANSMATRIX_H

#include <vector>
#include <QImage>

class TransMatrix
{
    float** matMultiply(int** A,float B[3][3],int r1, int c1,int r2,int c2);
public:
    int total_points;
    float matTrans[3][3];
    float matScale[3][3];
    float matRef[3][3];
    float matRotate[3][3];
    int** pointMat;
    TransMatrix();
    void setPoints(std::vector<QPoint> points);
    std::vector<QPoint> translate(float tx,float ty);
    std::vector<QPoint> scale(float sx,float sy);
    std::vector<QPoint> rotate(float theta);
    std::vector<QPoint> reflectX();
    std::vector<QPoint> reflectY();
    std::vector<QPoint> reflectYX();
};

#endif // TRANSMATRIX_H
