///////////////////////////////////////////////////////////////////////////////
// Matrice.h
// =========
// NxN Matrix Math classes
//
// The elements of the matrix are stored as column major order.
// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
//            | 2 5 8 |    |  2  6 10 14 |
//                         |  3  7 11 15 |
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2005-06-24
// UPDATED: 2015-13-01 by Loïc Payol
//
// Copyright (C) 2005 Song Ho Ahn
///////////////////////////////////////////////////////////////////////////////

#pragma once

const float DEG2RAD = 3.141593f / 180;
const float EPSILON = 0.00001f;

#include "Vectors.h"

///////////////////////////////////////////////////////////////////////////
// 4x4 matrix
///////////////////////////////////////////////////////////////////////////
class Matrix4
{
public:
    // constructors
    Matrix4();  // init with identity
    Matrix4(const float src[16]);
    Matrix4(float m00, float m01, float m02, float m03, // 1st column
            float m04, float m05, float m06, float m07, // 2nd column
            float m08, float m09, float m10, float m11, // 3rd column
            float m12, float m13, float m14, float m15);// 4th column

    void        set(const float src[16]);
    void        set(float m00, float m01, float m02, float m03, // 1st column
                    float m04, float m05, float m06, float m07, // 2nd column
                    float m08, float m09, float m10, float m11, // 3rd column
                    float m12, float m13, float m14, float m15);// 4th column
    void        setRow(int index, const float row[4]);
    void        setRow(int index, const Vector4& v);
    void        setRow(int index, const Vector3& v);
    void        setColumn(int index, const float col[4]);
    void        setColumn(int index, const Vector4& v);
    void        setColumn(int index, const Vector3& v);

    const float* get() const;
    float        getDeterminant();

    Matrix4&    identity();

    // operators
    Matrix4     operator+(const Matrix4& rhs) const;    // add rhs
    Matrix4     operator-(const Matrix4& rhs) const;    // subtract rhs
    Matrix4&    operator+=(const Matrix4& rhs);         // add rhs and update this object
    Matrix4&    operator-=(const Matrix4& rhs);         // subtract rhs and update this object
    Vector4     operator*(const Vector4& rhs) const;    // multiplication: v' = M * v
    Vector3     operator*(const Vector3& rhs) const;    // multiplication: v' = M * v
    Matrix4     operator*(const Matrix4& rhs) const;    // multiplication: M3 = M1 * M2
    Matrix4&    operator*=(const Matrix4& rhs);         // multiplication: M1' = M1 * M2
    bool        operator==(const Matrix4& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const Matrix4& rhs) const;   // exact compare, no epsilon
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend Matrix4 operator-(const Matrix4& m);                     // unary operator (-)
    friend Matrix4 operator*(float scalar, const Matrix4& m);       // pre-multiplication
    friend Vector3 operator*(const Vector3& vec, const Matrix4& m); // pre-multiplication
    friend Vector4 operator*(const Vector4& vec, const Matrix4& m); // pre-multiplication

protected:

private:
    float       getCofactor(float m0, float m1, float m2,
                            float m3, float m4, float m5,
                            float m6, float m7, float m8);

    float m[16];

};
// END OF MATRIX4 INLINE //////////////////////////////////////////////////////