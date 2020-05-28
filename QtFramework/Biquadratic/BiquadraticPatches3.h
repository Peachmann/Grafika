#ifndef BIQUADRATICPATCHES3_H
#define BIQUADRATICPATCHES3_H

#include <Core/TensorProductSurfaces3.h>

namespace cagd {
    class BiquadraticPatch3: public TensorProductSurface3
    {
     protected:

    public:
        BiquadraticPatch3();

        GLboolean SetCorner(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z);
                GLboolean SetCorner(GLuint i, GLuint j, const DCoordinate3 &corner);
                DCoordinate3& GetCorner(GLuint i, GLuint j);

                GLboolean SetUTangent(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z);
                GLboolean SetUTangent(GLuint i, GLuint j, const DCoordinate3 &tangent);
                DCoordinate3& GetUTangent(GLuint i, GLuint j);

                GLboolean SetVTangent(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z);
                GLboolean SetVTangent(GLuint i, GLuint j, const DCoordinate3 &tangent);
                DCoordinate3& GetVTangent(GLuint i, GLuint j);

                GLboolean SetTwist(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z);
                GLboolean SetTwist(GLuint i, GLuint j, const DCoordinate3 &twist);
                DCoordinate3& GetTwist(GLuint i, GLuint j);

                GLboolean UBlendingFunctionValues_d1(GLdouble u, RowMatrix<GLdouble> & u_d1_blending_values) const;
                GLboolean VBlendingFunctionValues_d1(GLdouble v, RowMatrix<GLdouble> & v_d1_blending_values) const;
                GLboolean UBlendingFunctionValues_d2(GLdouble u, RowMatrix<GLdouble> & u_d2_blending_values) const;
                GLboolean VBlendingFunctionValues_d2(GLdouble v, RowMatrix<GLdouble> & v_d2_blending_values) const;
                GLboolean UBlendingFunctionValues_d3(GLdouble u, RowMatrix<GLdouble> & u_d3_blending_values) const;
                GLboolean VBlendingFunctionValues_d3(GLdouble v, RowMatrix<GLdouble> & v_d3_blending_values) const;



                GLboolean UBlendingFunctionValues( GLdouble u, RowMatrix<GLdouble>& blending_values) const;
                GLboolean VBlendingFunctionValues( GLdouble v, RowMatrix<GLdouble>& blending_values) const;
                GLboolean CalculatePartialDerivatives( GLuint maximum_order_of_partial_derivatives,
                                                       GLdouble u, GLdouble v, PartialDerivatives& pd) const;
                Matrix<DCoordinate3> GetMatrix();
        //other project-specific setter/getter
    };
}

#endif // BIQUADRATICPATCHES3_H

