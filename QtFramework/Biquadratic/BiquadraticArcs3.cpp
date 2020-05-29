#include "BiquadraticArcs3.h"
#include <iostream>
#include <cmath>

using namespace std;



namespace cagd {
    BiquadraticArcs3::BiquadraticArcs3():LinearCombination3(0.0,1.0,4.0,GL_STATIC_DRAW)
    {
        _n = 2;
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


    GLboolean BiquadraticArcs3::BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const
    {
        if(u < _u_min || u > _u_max)
            return GL_FALSE;

        values.ResizeColumns(4);
        values(0) = f0(u);
        values(1) = f1(u);
        values(2) = f2(u);
        values(3) = f3(u);

        return GL_TRUE;
    }

    GLboolean BiquadraticArcs3::BlendingFunctionValues_d1(GLdouble u, RowMatrix<GLdouble> &values) const
    {
        if(u < _u_min || u > _u_max)
            return GL_FALSE;

        values.ResizeColumns(4);
        values(0) = f0_d1(u);
        values(1) = f1_d1(u);
        values(2) = f2_d1(u);
        values(3) = f3_d1(u);

        return GL_TRUE;
    }

    GLboolean BiquadraticArcs3::BlendingFunctionValues_d2(GLdouble u, RowMatrix<GLdouble> &values) const
    {
        if(u < _u_min || u > _u_max)
            return GL_FALSE;

        values.ResizeColumns(4);
        values(0) = f0_d2(u);
        values(1) = f1_d2(u);
        values(2) = f2_d2(u);
        values(3) = f3_d2(u);

        return GL_TRUE;
    }

    GLboolean BiquadraticArcs3::BlendingFunctionValues_d3(GLdouble u, RowMatrix<GLdouble> &values) const
    {
        if(u < _u_min || u > _u_max)
            return GL_FALSE;

        values.ResizeColumns(4);
        values(0) = f0_d3(u);
        values(1) = f1_d3(u);
        values(2) = f2_d3(u);
        values(3) = f3_d3(u);

        return GL_TRUE;
    }

    GLboolean BiquadraticArcs3::CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives &d) const
    {
        if(max_order_of_derivatives > 3)
            return GL_FALSE;

        Matrix<GLdouble> dF(max_order_of_derivatives + 1,_data.GetRowCount());
        d.ResizeRows(max_order_of_derivatives+1);
        d.LoadNullVectors();

        RowMatrix<GLdouble> u_blending_values(4);
        RowMatrix<GLdouble> u_blending_values_d1(4);
        RowMatrix<GLdouble> u_blending_values_d2(4);
        RowMatrix<GLdouble> u_blending_values_d3(4);

        if(!BlendingFunctionValues(u,u_blending_values) || !BlendingFunctionValues_d1(u,u_blending_values_d1) ||
                !BlendingFunctionValues_d2(u,u_blending_values_d2) || !BlendingFunctionValues_d3(u,u_blending_values_d3))
        {
            d.ResizeColumns(0);
            return GL_FALSE;
        }

        dF.SetRow(0,u_blending_values);
        dF.SetRow(1,u_blending_values_d1);
        dF.SetRow(2,u_blending_values_d2);
        dF.SetRow(3,u_blending_values_d3);

        d[0] = _data[0] * f0(u) + _data[1] * f1(u) + _data[2] * f2(u) + _data[3] * f3(u);
        d[1] = _data[0] * f0_d1(u) + _data[1] * f1_d1(u) + _data[2] * f2_d1(u) + _data[3] * f3_d1(u);
        d[2] = _data[0] * f0_d2(u) + _data[1] * f1_d2(u) + _data[2] * f2_d2(u) + _data[3] * f3_d2(u);

        //d[0] += centroid;

        return GL_TRUE;
    }

    GLboolean BiquadraticArcs3::SetData(GLuint i, DCoordinate3 point)
    {
        _data[i] = point;
        return GL_TRUE;
    }

    DCoordinate3& BiquadraticArcs3::GetData(GLuint i)
    {
        return _data[i];
    }
}
