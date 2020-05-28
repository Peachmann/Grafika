#ifndef BIQUADRATICARCS3_H
#define BIQUADRATICARCS3_H

#include <Core/LinearCombination3.h>

namespace cagd {
    class BiquadraticArcs3: public LinearCombination3
    {
    protected:
        //alpha
    private:
        GLuint _n;
    public:
        BiquadraticArcs3();

        // values[i] = F_i(u), i = 0..3
        GLboolean BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble>& values) const;
        GLboolean SetData(GLuint i,DCoordinate3 point);
        DCoordinate3& GetData(GLuint i);
        //d[0] = curve point
        //d[1] = tangent vector
        //d[2] = acceleration vector
        //if(max_order_of derivaties >=4) return GL_FALSE
        GLboolean CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives& d) const;
        GLboolean  BlendingFunctionValues_d1(GLdouble u, RowMatrix<GLdouble>& values) const;
        GLboolean  BlendingFunctionValues_d2(GLdouble u, RowMatrix<GLdouble>& values) const;
        GLboolean  BlendingFunctionValues_d3(GLdouble u, RowMatrix<GLdouble>& values) const;
        //setters/getters
    };
}

#endif // BIQUADRATICARCS3_H
