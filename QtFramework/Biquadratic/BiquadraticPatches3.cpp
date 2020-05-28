#include "BiquadraticPatches3.h"

using namespace cagd;

BiquadraticPatch3::BiquadraticPatch3():TensorProductSurface3(0.0,1.0,0.0,1.0,4,4)
{
}


GLdouble f2(GLdouble t)
{
    GLdouble t2 = t * t;
    return -t2 * (t2 + 2.0 *t - 3.0);
}

GLdouble f3(GLdouble t)
{
    return t*t*t*t;
}

GLdouble f0(GLdouble t)
{
    return f3(1-t);
}

GLdouble f1(GLdouble t)
{
    GLdouble t2 = t*t, t3 = t2*t;
    return -t*(t3 - 6.0*t2+9.0*t-4.0);
}

GLdouble f2_d1(GLdouble t)
{
    GLdouble t2 = t*t;
    return -2.0 * t * (2.0 * t2 + 3.0 * t - 3.0);
}

GLdouble f2_d2(GLdouble t)
{
    GLdouble t2 = t*t;
    return -6.0 * ( 2 * t2 + 2 * t - 1);
}

GLdouble f2_d3(GLdouble t)
{
    return -24.0 * t -12.0;
}

GLdouble f3_d1(GLdouble t)
{
    return 4.0 * (t*t*t);
}

GLdouble f3_d2(GLdouble t)
{
    return 12.0 * (t * t);
}

GLdouble f3_d3(GLdouble t)
{
    return 24.0 * t;
}

GLdouble f0_d1(GLdouble t)
{
    return -f3_d1(1 - t);
}

GLdouble f0_d2(GLdouble t)
{
    return f3_d2(1 - t);
}

GLdouble f0_d3(GLdouble t)
{
    return -f3_d3(1 - t);
}

GLdouble f1_d1(GLdouble t)
{
    GLdouble t2 = t*t, t3 = t2*t;
    return -4.0*t3 + 18.0*t2 - 18.0*t + 4.0;
}

GLdouble f1_d2(GLdouble t)
{
    return -12.0 * t*t + 36.0 * t - 18.0;
}

GLdouble f1_d3(GLdouble t)
{
    return 36.0 - 24.0 * t;
}

GLboolean BiquadraticPatch3::SetCorner(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z)
{
    if (i > 1 || j > 1)
       {
           return GL_FALSE;
       }

       DCoordinate3 &corner = _data(i, j);

       corner[0] = x;
       corner[1] = y;
       corner[2] = z;

       return GL_TRUE;
}

DCoordinate3& BiquadraticPatch3::GetCorner(GLuint i, GLuint j){
    return _data(i,j);
}
GLboolean BiquadraticPatch3::SetCorner(GLuint i, GLuint j, const DCoordinate3 &corner)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    _data(i, j) = corner;

    return GL_TRUE;
}

GLboolean BiquadraticPatch3::SetUTangent(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    DCoordinate3 &tangent = _data(i + 2, j);

    tangent[0] = x;
    tangent[1] = y;
    tangent[2] = z;

    return GL_TRUE;
}

DCoordinate3& BiquadraticPatch3::GetUTangent(GLuint i, GLuint j)
{
    return _data(i + 2, j);
}

DCoordinate3& BiquadraticPatch3::GetVTangent(GLuint i, GLuint j)
{
    return _data(i, j + 2);
}

DCoordinate3& BiquadraticPatch3::GetTwist(GLuint i, GLuint j)
{
    return _data(i + 2, j + 2);
}

GLboolean BiquadraticPatch3::SetUTangent(GLuint i, GLuint j, const DCoordinate3 &tangent)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    _data(i + 2, j) = tangent;

    return GL_TRUE;
}

GLboolean BiquadraticPatch3::SetVTangent(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    DCoordinate3 &tangent = _data(i, j + 2);

    tangent[0] = x;
    tangent[1] = y;
    tangent[2] = z;

    return GL_TRUE;
}

GLboolean BiquadraticPatch3::SetVTangent(GLuint i, GLuint j, const DCoordinate3 &tangent)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    _data(i, j + 2) = tangent;

    return GL_TRUE;
}

GLboolean BiquadraticPatch3::SetTwist(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    DCoordinate3 &twist = _data(i + 2, j + 2);

    twist[0] = x;
    twist[1] = y;
    twist[2] = z;

    return GL_TRUE;
}



GLboolean BiquadraticPatch3::SetTwist(GLuint i, GLuint j, const DCoordinate3 &twist)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    _data(i + 2, j + 2) = twist;

    return GL_TRUE;
}

GLboolean BiquadraticPatch3::UBlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &blending_values) const
{
    if(u < _u_min || u > _u_max)
    {
        return GL_FALSE;
    }

    blending_values.ResizeColumns(4);
    blending_values(0) = f0(u);
    blending_values(1) = f1(u);
    blending_values(2) = f2(u);
    blending_values(3) = f3(u);

    return GL_TRUE;

}

GLboolean BiquadraticPatch3::VBlendingFunctionValues(GLdouble v, RowMatrix<GLdouble> &blending_values) const
{
    if(v < _v_min || v > _v_max)
    {
        return GL_FALSE;
    }

    blending_values.ResizeColumns(4);
    blending_values(0) = f0(v);
    blending_values(1) = f1(v);
    blending_values(2) = f2(v);
    blending_values(3) = f3(v);

    return GL_TRUE;
}

GLboolean BiquadraticPatch3::UBlendingFunctionValues_d1(GLdouble u, RowMatrix<GLdouble> &u_d1_blending_values) const
{
    if(u < _u_min || u > _u_max)
    {
        return GL_FALSE;
    }

    u_d1_blending_values.ResizeColumns(4);
    u_d1_blending_values(0) = f0_d1(u);
    u_d1_blending_values(1) = f1_d1(u);
    u_d1_blending_values(2) = f2_d1(u);
    u_d1_blending_values(3) = f3_d1(u);

    return GL_TRUE;
}

GLboolean BiquadraticPatch3::VBlendingFunctionValues_d1(GLdouble v, RowMatrix<GLdouble> &v_d1_blending_values) const
{
    if(v < _v_min || v > _v_max)
            return GL_FALSE;

        v_d1_blending_values.ResizeColumns(4);
        v_d1_blending_values[0] = f0_d1(v);
        v_d1_blending_values[1] = f1_d1(v);
        v_d1_blending_values[2] = f2_d1(v);
        v_d1_blending_values[3] = f3_d1(v);
        return GL_TRUE;
}

GLboolean BiquadraticPatch3::UBlendingFunctionValues_d2(GLdouble u, RowMatrix<GLdouble> &u_d2_blending_values) const
{
    if(u < _u_min || u > _u_max)
    {
        return GL_FALSE;
    }

    u_d2_blending_values.ResizeColumns(4);

    u_d2_blending_values(0) = f0_d2(u);

    u_d2_blending_values(1) = f1_d2(u);

    u_d2_blending_values(2) = f2_d2(u);

    u_d2_blending_values(3) = f3_d2(u);


    return GL_TRUE;
}

GLboolean BiquadraticPatch3::VBlendingFunctionValues_d2(GLdouble v, RowMatrix<GLdouble> &v_d2_blending_values) const
{
    if(v < _v_min || v > _v_max)
            return GL_FALSE;

        v_d2_blending_values.ResizeColumns(4);

        v_d2_blending_values[0] = f0_d2(v);

        v_d2_blending_values[1] = f1_d2(v);

        v_d2_blending_values[2] = f2_d2(v);

        v_d2_blending_values[3] = f3_d2(v);
        return GL_TRUE;
}

GLboolean BiquadraticPatch3::UBlendingFunctionValues_d3(GLdouble u, RowMatrix<GLdouble> &u_d3_blending_values) const
{
    if(u < _u_min || u > _u_max)
    {
        return GL_FALSE;
    }

    u_d3_blending_values.ResizeColumns(4);
    u_d3_blending_values(0) = f0_d3(u);
    u_d3_blending_values(1) = f1_d3(u);
    u_d3_blending_values(2) = f2_d3(u);
    u_d3_blending_values(3) = f3_d3(u);

    return GL_TRUE;
}

GLboolean BiquadraticPatch3::VBlendingFunctionValues_d3(GLdouble v, RowMatrix<GLdouble> &v_d3_blending_values) const
{
    if(v < _v_min || v > _v_max)
            return GL_FALSE;

        v_d3_blending_values.ResizeColumns(4);
        v_d3_blending_values[0] = f0_d3(v);
        v_d3_blending_values[1] = f1_d3(v);
        v_d3_blending_values[2] = f2_d3(v);
        v_d3_blending_values[3] = f3_d3(v);
        return GL_TRUE;
}

GLboolean BiquadraticPatch3::CalculatePartialDerivatives(GLuint maximum_order_of_partial_derivatives, GLdouble u, GLdouble v, PartialDerivatives &pd) const
{
    if(u < 0.0 || u > 1.0 || v < 0.0 || v > 1.0 || maximum_order_of_partial_derivatives > 1)
    {
        return GL_FALSE;
    }

    RowMatrix<GLdouble> u_blending_values(4),d1_u_blending_values(4);

    u_blending_values(0) = f0(u);
    u_blending_values(1) = f1(u);
    u_blending_values(2) = f2(u);
    u_blending_values(3) = f3(u);

    d1_u_blending_values(0) = f0_d1(u);
    d1_u_blending_values(1) = f1_d1(u);
    d1_u_blending_values(2) = f2_d1(u);
    d1_u_blending_values(3) = f3_d1(u);

    RowMatrix<GLdouble> v_blending_values(4),d1_v_blending_values(4);

    v_blending_values(0) = f0(v);
    v_blending_values(1) = f1(v);
    v_blending_values(2) = f2(v);
    v_blending_values(3) = f3(v);

    d1_v_blending_values(0) = f0_d1(v);
    d1_v_blending_values(1) = f1_d1(v);
    d1_v_blending_values(2) = f2_d1(v);
    d1_v_blending_values(3) = f3_d1(v);

    pd.ResizeRows(2);
    pd.LoadNullVectors();
    for(GLuint row = 0 ; row < 4; row++)
    {
        DCoordinate3 aux_d0_v,aux_d1_v;
        for(GLuint column = 0; column < 4; column++)
        {
            aux_d0_v += _data(row,column) * v_blending_values(column);
            aux_d1_v += _data(row,column) * d1_v_blending_values(column);
        }
        pd(0,0) += aux_d0_v * u_blending_values(row);
        pd(1,0) += aux_d0_v * d1_u_blending_values(row);
        pd(1,1) += aux_d1_v * u_blending_values(row);
    }

    return GL_TRUE;
}

Matrix<DCoordinate3> BiquadraticPatch3::GetMatrix()
{
    return _data;
}








