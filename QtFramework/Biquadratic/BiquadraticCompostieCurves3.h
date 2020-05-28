#ifndef BIQUADRATICCOMPOSTIECURVES3_H
#define BIQUADRATICCOMPOSTIECURVES3_H

#include "BiquadraticArcs3.h"
#include <Core/Colors4.h>

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

            ArcAttributes *previous, *next; //they are initialized as nulltpr by default

            //TO DO ctor, copy const (deep copy), operator= (deep copy), dtor
        protected:
            std::vector<ArcAttributes> _attributes;

            // _attributes[i].arc = new BiquadraticArcs3();
            // (*_attributes[i].arc)[j] = p_j; j = 0,1,2,3
            //_attributes[i].arc -> UpdateVertexBufferObjectsOfData();
            //_attributes[i].arc -> RenderData();
            // _attributes[i].image = _attributes[i].arc->GenerateImage(..,..,..);
            //_attributes[i].image->UpdateVertexBufferObjects(..);
            //i_attributes[i].image->RenderDerivatives(..,..);
            //_attributes[i].glColor4fv(&(*_attributes[i].color)[0]);

            GLboolean InsertNewIsolatedArc();
            GLboolean ContinueExistingArc(const size_t &arc_index,Direction direction);

            GLboolean JoinExistingArcs(const size_t &arc_index1, Direction direction1,
                                       const size_t &arc_index2, Direction direction2);
            GLboolean MergeExistingArcs(const size_t &arc_index1, Direction direction1,
                                        const size_t &arc_index2, Direction direction2);
            //render all arc, rendere selected arc, update selected arc

            //other setters/getters
        };
    };
}

#endif // BIQUADRATICCOMPOSTIECURVES3_H
