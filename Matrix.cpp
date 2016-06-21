//
// Created by janco on 6/21/16.
//

#include "Matrix.h"

    Matrix::Matrix(int size = 4)
    {
        data = new float[size][size];
    }

    Matrix Matrix::identity()
    {
        Matrix m = new Matrix(4);
        m.data[0,0] = 1;
        m.data[1,1] = 1;
        m.data[2,2] = 1;
        m.data[3,3] = 1;
        return m;
    }

    Matrix Matrix::rotation(float angle, Vector3 axis)
    {
        Matrix m = Matrix.identity();

        float c = (float) Math.Cos((double) angle);
        float s = (float) Math.Sin((double) angle);

        m.data[0, 0] = (float) Math.Pow(axis.x, 2) * (1 - c) + c;
        m.data[0, 1] = axis.x * axis.y * (1 - c) - axis.z * s;
        m.data[0, 2] = axis.x * axis.z * (1 - c) - axis.y * s;
        m.data[1, 0] = axis.x * axis.y * (1 - c) + axis.z * s;
        m.data[1, 1] = (float)Math.Pow(axis.y, 2) * (1 - c) + c;
        m.data[1, 2] = axis.y * axis.z * (1 - c) + axis.x * s;
        m.data[2, 0] = axis.x * axis.z * (1 - c) + axis.y * s;
        m.data[2, 1] = axis.y * axis.z * (1 - c) - axis.x * s;
        m.data[2, 2] = (float)Math.Pow(axis.z, 2) * (1 - c) + c;

        return m;
    }
    Matrix Matrix::translate(Vector3 offset)
    {
        Matrix m = Matrix.identity();

        for(int i = 0; i < 3; i++)
        {
            m.data[i, 3] = offset.data[i];
        }

        return m;
    }

    Vec3f Matrix::operator * (Matrix mat, Vec3f vec)
    {
        Vec3f v = Vec3f(0,0,0);

        for(int i = 0; i < 4; i++)
        {
            v.data[i] = 0;

            for(int p = 0; p < 4; p++)
            {
                v.data[i] += mat.data[i, p] * vec.data[p];
            }
        }

        return v;
    }

    Matrix Matrix::operator * (Matrix mat1, Matrix mat2)
    {
        Matrix m = Matrix.identity();

        for (int i = 0; i < 4; i++)
        {
            for (int p = 0; p < 4; p++)
            {
                m.data[i, p] = 0;

                for (int q = 0; q < 4; q++)
                {
                    m.data[i, p] += mat1.data[i, q] * mat2.data[q, p];
                }
            }
        }

        return m;
    }
};