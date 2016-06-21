//
// Created by janco on 6/21/16.
//

#ifndef CRYSTALPOINT_MATRIX_H
#define CRYSTALPOINT_MATRIX_H


class Matrix {
private:
public:
    float *data;

    Matrix(int i = 4);
    ~Matrix();

    static Matrix rotation(int angle, Vec3f axis);
    static Matrix identity(void);
    static Matrix translate(Vec3f offset);

    Matrix operator * (Matrix m1, Matrix m2);
    Vec3f operator * (Matrix m, Vec3f v);
}


#endif //CRYSTALPOINT_MATRIX_H
