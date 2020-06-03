#ifndef BIQUADRATICCOMPOSTIECURVES3_H
#define BIQUADRATICCOMPOSTIECURVES3_H

#include "BiquadraticArcs3.h"
#include <Core/Colors4.h>
#include <Core/Constants.h>


namespace cagd {
    class BiquadraticCompositeCurve3
    {
    public:
        enum Direction{LEFT, RIGHT};
        class ArcAttributes
        {
        public:
            BiquadraticArcs3 *arc;
            GenericCurve3 *image; // image - arc->GenerateImage(.., ..,..);
                                  //image->UpdateVertexBufferObjects(..);
                                  //image->RenderDerivatives(..,..);
                                  //glColor4fv(&(*color)[0]);
            Color4 *color;
            // other project-specific attributes

            GLint index;

            GLboolean visited = false;

            ArcAttributes *previous, *next; //they are initialized as nulltpr by default

            //TO DO ctor, copy const (deep copy), operator= (deep copy), dtor
            //Default Constructor
            ArcAttributes()
            {
                arc = nullptr;
                image = nullptr;
                color = nullptr;
                this->index = 0;
                next = nullptr;
                previous = nullptr;
            }
            //Special constructor
            ArcAttributes(Color4 *c, GLint index)
            {
                arc = nullptr;
                image = nullptr;
                color = c;
                this->index = index;
                next = nullptr;
                previous = nullptr;
            }

        };

    protected:
        std::vector<ArcAttributes> _attributes; //at1 at2 at3
        GLuint _maxArcNumber;
    public:
        std::vector<std::string> loadedColors;
        //Default Constructor
        BiquadraticCompositeCurve3();

        //Special Constructor
        BiquadraticCompositeCurve3(GLuint arcNumber);

        // _attributes[i].arc = new BiquadraticArcs3();
        // (*_attributes[i].arc)[j] = p_j; j = 0,1,2,3
        //_attributes[i].arc -> UpdateVertexBufferObjectsOfData();
        //_attributes[i].arc -> RenderData();
        // _attributes[i].image = _attributes[i].arc->GenerateImage(..,..,..);
        //_attributes[i].image->UpdateVertexBufferObjects(..);
        //i_attributes[i].image->RenderDerivatives(..,..);
        //_attributes[i].glColor4fv(&(*_attributes[i].color)[0]);

        GLboolean InsertNewIsolatedArc(GLuint index, Color4* color = new Color4(1.0,1.0,1.0,1.0));
        GLboolean ContinueExistingArc(const size_t &arc_index,Direction direction, Color4* col);

        GLboolean JoinExistingArcs(const size_t &arc_index1, Direction direction1,
                                   const size_t &arc_index2, Direction direction2,
                                   Color4* color);
        GLboolean MergeExistingArcs(const size_t &arc_index1, Direction direction1,
                                    const size_t &arc_index2, Direction direction2,
                                    GLuint div_point_count = 30,
                                    GLuint max_order_of_derivatives  = 3);


        //render all arc, rendere selected arc, update selected arc

        GLboolean RenderArcs(GLboolean d1 = GL_FALSE, GLboolean d2 = GL_FALSE, GLboolean polygon = GL_FALSE);

        //other setters/getters

        GLboolean SetCurveData(GLuint index, GLuint div_point_count = 30, GLuint max_order_of_derivatives  = 3);

        void UpdateArc(GLuint index, GLuint div_point_count = 30, GLuint max_order_of_derivatives = 3);
        GLboolean UpdateArc_2(GLuint index,GLuint div_point_count, GLuint max_order_of_derivatives);
        GLboolean UpdateArc_2(ArcAttributes &arc_att,GLuint div_point_count, GLuint max_order_of_derivatives);

        //movements along x,y,z axis
        GLboolean moveOnAxisX(const size_t &arc_index, GLdouble offset);
        GLboolean moveOnAxisY(const size_t &arc_index, GLdouble offset);
        GLboolean moveOnAxisZ(const size_t &arc_index, GLdouble offset);
        GLboolean moveOnAllAxis(const size_t &arc_index, GLdouble offx, GLdouble offy, GLdouble offz);




        std::vector<ArcAttributes> get_attributes();

        //moving control points
        GLboolean moveControlPointX(const size_t &arc_index, const size_t &point_index, GLdouble offset);
        GLboolean moveControlPointY(const size_t &arc_index, const size_t &point_index, GLdouble offset);
        GLboolean moveControlPointZ(const size_t &arc_index, const size_t &point_index, GLdouble offset);
        GLboolean moveControlPointAll(const size_t &arc_index, const size_t &point_index, GLdouble offx, GLdouble offy, GLdouble offz);

        //Shift
        GLboolean shiftArc(const size_t &arc_index, GLdouble offx, GLdouble offy, GLdouble offz,std::vector<ArcAttributes*> _avector);

        //File operations
        GLuint ReadCurveFromFile(const std::string &file, GLuint index);
        GLboolean SaveCurveToFile(const std::string &file, RowMatrix<Color4*> colors);

        //Change color by index
        GLboolean changeArcColorByIndex(GLuint index, Color4 *colors);

        //Color to String
       GLuint convertColorToIndex(RowMatrix<Color4*> colors,Color4* color);

    };
}

#endif // BIQUADRATICCOMPOSTIECURVES3_H
