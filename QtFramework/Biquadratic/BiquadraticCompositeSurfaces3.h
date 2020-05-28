#ifndef BIQUADRATICCOMPOSITESURFACES3_H
#define BIQUADRATICCOMPOSITESURFACES3_H
#include "BiquadraticPatches3.h"
#include <Core/Materials.h>
//#include <Core/ShaderPrograms.h>

namespace cagd {
    class BiquadraticCompositeSurface3
    {
    public:
        enum Direction{N, NW, W,SW,S,SE,E,NE};

        class PatchAttributes
        {
        public:
            BiquadraticPatch3 *patch;
            TriangulatedMesh3 *mesh;
            Material *material;
            //ShaderProgram *shader;
            PatchAttributes *neighbours[8]; //nullptr at start

            //TO DO ctor, copy const (deep copy), operator= (deep copy), dtor
        protected:
            std::vector<PatchAttributes> _attributes;

            // _attributes[i].patch = new BiquadraticPatch3();
            // (*_attributes[i].patch)[j] = p_j; j = 0,1,2,3
            //_attributes[i].patch -> UpdateVertexBufferObjectsOfData();
            //_attributes[i].patch -> RenderData();
            // _attributes[i].image = _attributes[i].patch->GenerateImage(..,..,..);
            //_attributes[i].image->UpdateVertexBufferObjects(..);
            //i_attributes[i].image->RenderDerivatives(..,..);
            //_attributes[i].glColor4fv(&(*_attributes[i].color)[0]);

            GLboolean InsertNewIsolatedPatch();
            GLboolean ContinueExistingPatch(const size_t &patch_index,Direction direction);

            GLboolean JoinExistingPatches(const size_t &patch_index1, Direction direction1,
                                       const size_t &patch_index2, Direction direction2);
            GLboolean MergeExistingPatches(const size_t &patch_index1, Direction direction1,
                                        const size_t &patch_index2, Direction direction2);
            //render all patches, rendere selected patch, update selected patch

            //other setters/getters
        };
    };
}
#endif // BIQUADRATICCOMPOSITESURFACES3_H
