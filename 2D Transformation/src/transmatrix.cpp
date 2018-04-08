#include "transmatrix.h"
#include <QDebug>
#include <QtMath>

TransMatrix::TransMatrix()
{
    int x;
    for (int i = 0; i<3; i++){
        for (int j =0; j<3; j++){
            x = (i==j) ? 1 : 0;
            matTrans[i][j] = x;
            matScale[i][j] = x;
            matRotate[i][j] = x;
            matRef[i][j] = x;
        }
    }
}

void TransMatrix::setPoints(std::vector<QPoint> points)
{
    total_points = points.size();
    pointMat = new int*[total_points];
    QPoint temp;
    for (int i = 0; i < total_points; ++i){
        temp = points.at(i);
        pointMat[i] = new int[3];
        pointMat[i][0] = temp.x();
        pointMat[i][1] = temp.y();
        pointMat[i][2] = 1;
    }
}

std::vector<QPoint> TransMatrix::translate(float tx, float ty)
{
    matTrans[2][0] = tx;
    matTrans[2][1] = ty;
    float** result = matMultiply(pointMat,matTrans,total_points,3,3,3);
    std::vector<QPoint> newPoints;
    for (int i = 0; i < total_points; ++i) {
        newPoints.push_back(QPoint(result[i][0],result[i][1]));
    }
    return newPoints;
}

std::vector<QPoint> TransMatrix::scale(float sx, float sy)
{
    matScale[0][0] = sx;
    matScale[1][1] = sy;
    float** result = matMultiply(pointMat,matScale,total_points,3,3,3);
    std::vector<QPoint> newPoints;
    for (int i = 0; i < total_points; ++i) {
        newPoints.push_back(QPoint(round(result[i][0]),round(result[i][1])));
    }
    return newPoints;
}

std::vector<QPoint> TransMatrix::rotate(float theta)
{
    qDebug() << sin(30*M_PI/180);
    matRotate[0][0] = cos(theta);
    matRotate[0][1] = sin(theta);
    matRotate[1][0] = -sin(theta);
    matRotate[1][1] = cos(theta);

    float** result = matMultiply(pointMat,matRotate,total_points,3,3,3);
    std::vector<QPoint> newPoints;
    for (int i = 0; i < total_points; ++i) {
        newPoints.push_back(QPoint(round(result[i][0]),round(result[i][1])));
    }
    return newPoints;
}

std::vector<QPoint> TransMatrix::reflectX()
{
    matRef[1][1] = -1;
    float** result = matMultiply(pointMat,matRef,total_points,3,3,3);
    std::vector<QPoint> newPoints;
    for (int i = 0; i < total_points; ++i) {
        newPoints.push_back(QPoint(round(result[i][0]),round(result[i][1])));
    }
    return newPoints;

}

std::vector<QPoint> TransMatrix::reflectY()
{
    matRef[0][0] = -1;

    float** result = matMultiply(pointMat,matRef,total_points,3,3,3);
    std::vector<QPoint> newPoints;
    for (int i = 0; i < total_points; ++i) {
        newPoints.push_back(QPoint(round(result[i][0]),round(result[i][1])));
    }
    return newPoints;
}

std::vector<QPoint> TransMatrix::reflectYX()
{
    matRef[0][0] = 0;
    matRef[0][1] = 1;
    matRef[1][0] = 1;
    matRef[1][1] = 0;
    float** result = matMultiply(pointMat,matRef,total_points,3,3,3);
    std::vector<QPoint> newPoints;
    for (int i = 0; i < total_points; ++i) {
        newPoints.push_back(QPoint(round(result[i][0]),round(result[i][1])));
    }
    return newPoints;
}
float** TransMatrix::matMultiply(int** A, float B[3][3], int r1, int c1, int r2, int c2){
    float** C;
    C = new float*[r1];
    float sum = 0;
    for(int i=0; i<r1; i++){
        C[i] = new float[c2];
    }
    for (int i=0; i<r1; i++){
        for (int j=0; j<c2; j++){
            sum = 0;
            for(int k=0; k<c1; k++){
                sum += (A[i][k]*B[k][j]);
            }
            C[i][j] = sum;
        }
    }
    return C;
}
