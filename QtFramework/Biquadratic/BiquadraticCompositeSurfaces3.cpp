#include "BiquadraticCompositeSurfaces3.h";
#include "fstream";


using namespace std;
using namespace cagd;


BiquadraticCompositeSurface3::PatchAttributes::PatchAttributes()
{
    patch = nullptr;
    mesh = nullptr;
    shader = nullptr;
    u_isolines = nullptr;
    v_isolines = nullptr;
    for(GLint i =  0; i < 8; i++)
    {
        neighbours[i] = nullptr;
    }
}

BiquadraticCompositeSurface3::PatchAttributes::PatchAttributes(const PatchAttributes &rhs)
{
    this->patch = rhs.patch;
    this->mesh = rhs.mesh;
    this->shader = rhs.shader;
    this->u_isolines = rhs.u_isolines;
    this->v_isolines = rhs.v_isolines;

    if(rhs.u_isolines)
    {
        for(GLuint i = 0 ; i < rhs.u_isolines->GetColumnCount();i++)
        {
            if((*rhs.u_isolines)[i])
            {
                (*u_isolines)[i] = new GenericCurve3(*(*rhs.u_isolines)[i]);
            }
        }
    }

    if (rhs.v_isolines)
    {
        for (GLuint j = 0; j < rhs.v_isolines->GetColumnCount(); j++)
        {
            if ((*rhs.v_isolines)[j])
            {
                (*v_isolines)[j] = new GenericCurve3(*(*rhs.u_isolines)[j]);
            }
        }
    }

    for (GLuint i = 0; i < 8; i++) {
        neighbours[i] = rhs.neighbours[i];
    }
}

BiquadraticCompositeSurface3::PatchAttributes& BiquadraticCompositeSurface3::PatchAttributes::operator=(const PatchAttributes &rhs)
{
    if(this != &rhs)
    {
        if(patch)
            delete patch,patch = nullptr;
        if(mesh)
            delete mesh,mesh = nullptr;

        if(u_isolines)
        {
            for(GLuint i = 0; i < u_isolines->GetColumnCount();i++)
            {
                if((*u_isolines)[i])
                {
                    delete (*u_isolines)[i], (*u_isolines)[i] = nullptr;
                }
            }
            delete u_isolines,u_isolines = nullptr;
        }

        if(v_isolines)
        {
            for(GLuint i = 0; i < v_isolines->GetColumnCount();i++)
            {
                if((*v_isolines)[i])
                {
                    delete (*v_isolines)[i], (*u_isolines)[i] = nullptr;
                }
            }
            delete v_isolines,v_isolines = nullptr;
        }

        this->patch = rhs.patch;
        this->mesh = rhs.mesh;
        this->material = rhs.material;
        this->shader = rhs.shader;

        u_isolines = new RowMatrix<GenericCurve3*>(rhs.u_isolines->GetColumnCount());
        v_isolines = new RowMatrix<GenericCurve3*>(rhs.v_isolines->GetColumnCount());

        if(rhs.u_isolines)
        {
            for(GLuint i = 0 ; i < rhs.u_isolines->GetColumnCount();i++)
            {
                if((*rhs.u_isolines)[i])
                {
                    (*u_isolines)[i] = new GenericCurve3(*(*rhs.u_isolines)[i]);
                }
            }
        }

        if (rhs.v_isolines)
        {
            for (GLuint j = 0; j < rhs.v_isolines->GetColumnCount(); j++)
            {
                if ((*rhs.v_isolines)[j])
                {
                    (*v_isolines)[j] = new GenericCurve3(*(*rhs.u_isolines)[j]);
                }
            }
        }

        for (GLuint i = 0; i < 8; i++) {
            neighbours[i] = rhs.neighbours[i];
        }
    }
    return *this;
}

BiquadraticCompositeSurface3::PatchAttributes::~PatchAttributes()
{
    if(patch)
        delete patch, patch = nullptr;

    if(this->mesh)
        delete mesh, mesh = nullptr;

    if(u_isolines)
    {
        for (GLuint i = 0; i < u_isolines->GetColumnCount(); i++)
        {
            if ((*u_isolines)[i])
            {
                delete (*u_isolines)[i], (*u_isolines)[i] = nullptr;
            }
        }
        delete u_isolines, u_isolines = nullptr;
    }

    if (v_isolines)
    {
        for (GLuint j = 0; j < v_isolines->GetColumnCount(); j++)
        {
            if ((*v_isolines)[j])
            {
                delete (*v_isolines)[j], (*v_isolines)[j] = nullptr;
            }
        }
        delete v_isolines, v_isolines = nullptr;
    }
}

BiquadraticCompositeSurface3::BiquadraticCompositeSurface3(GLuint max)
{
    _maxPatches = max;
    _attributes.reserve(_maxPatches);
}

BiquadraticCompositeSurface3::BiquadraticCompositeSurface3(const BiquadraticCompositeSurface3 & rhs)
{
    this->_maxPatches = rhs._maxPatches;
    _attributes = rhs._attributes;
}

BiquadraticCompositeSurface3& BiquadraticCompositeSurface3::operator=(const BiquadraticCompositeSurface3 &rhs)
{
    if(this != &rhs)
    {
        this->_maxPatches = rhs._maxPatches;
        this->_attributes = rhs._attributes;
    }
    return  *this;
}

BiquadraticCompositeSurface3::~BiquadraticCompositeSurface3()
{
    _attributes.clear();
}

GLboolean BiquadraticCompositeSurface3::InsertNewIsolatedPatch(GLuint index, Material& material, GLuint u_div_point_count, GLuint v_div_point_count, GLuint u_isoline_count, GLuint v_isoline_count, GLenum usage_flag)
{
    //Increment vector
    GLuint n = _attributes.size();

    _attributes.resize(n + 1);
    _attributes[n].index = index;
    std::cout<<"New patch given index of: "<<_attributes[n].index<<endl;
    _attributes[n].material = &material;

    _attributes[n].patch = new (nothrow) BiquadraticPatch3();

    if(!_attributes[n].patch)
    {
        std::cout<<"Patch not created!\n";
        _attributes.pop_back();
        return GL_FALSE;
    }

    //Set CPs
    if(n == 0)
    {
        _attributes[n].patch->SetData(0, 0, -2.0, -2.0, 0.0);
        _attributes[n].patch->SetData(0, 1, -2.0, -1.0, 0.0);
        _attributes[n].patch->SetData(0, 2, -2.0, 1.0, 0.0);
        _attributes[n].patch->SetData(0, 3, -2.0, 2.0, 3.0);

        _attributes[n].patch->SetData(1, 0, -1.0, -2.0, 0.0);
        _attributes[n].patch->SetData(1, 1, -1.0, -1.0, 2.0);
        _attributes[n].patch->SetData(1, 2, -1.0, 1.0, 2.0);
        _attributes[n].patch->SetData(1, 3, -1.0, 2.0, 0.0);

        _attributes[n].patch->SetData(2, 0, 1.0, -2.0, 0.0);
        _attributes[n].patch->SetData(2, 1, 1.0, -1.0, 2.0);
        _attributes[n].patch->SetData(2, 2, 1.0, 1.0, 2.0);
        _attributes[n].patch->SetData(2, 3, 1.0, 2.0, 0.0);

        _attributes[n].patch->SetData(3, 0, 2.0, -2.0, 3.0);
        _attributes[n].patch->SetData(3, 1, 2.0, -1.0, 0.0);
        _attributes[n].patch->SetData(3, 2, 2.0, 1.0, 0.0);
        _attributes[n].patch->SetData(3, 3, 2.0, 2.0, 0.0);
    }
    else
    {
        _attributes[n].patch->SetData(0, 0, 3.0, -2.0, 0.0);
        _attributes[n].patch->SetData(0, 1, 3.0, -1.0, 0.0);
        _attributes[n].patch->SetData(0, 2, 3.0, 1.0, 0.0);
        _attributes[n].patch->SetData(0, 3, 3.0, 2.0, 0.0);

        _attributes[n].patch->SetData(1, 0, 4.0, -2.0, 0.0);
        _attributes[n].patch->SetData(1, 1, 4.0, -1.0, 2.0);
        _attributes[n].patch->SetData(1, 2, 4.0, 1.0, 2.0);
        _attributes[n].patch->SetData(1, 3, 4.0, 2.0, 0.0);

        _attributes[n].patch->SetData(2, 0, 6.0, -2.0, 0.0);
        _attributes[n].patch->SetData(2, 1, 6.0, -1.0, 2.0);
        _attributes[n].patch->SetData(2, 2, 6.0, 1.0, 2.0);
        _attributes[n].patch->SetData(2, 3, 6.0, 2.0, 0.0);

        _attributes[n].patch->SetData(3, 0, 7.0, -2.0, 0.0);
        _attributes[n].patch->SetData(3, 1, 7.0, -1.0, 0.0);
        _attributes[n].patch->SetData(3, 2, 7.0, 1.0, 0.0);
        _attributes[n].patch->SetData(3, 3, 7.0, 2.0, 0.0);
    }


    //Update dataVBO
    _attributes[n].patch->UpdateVertexBufferObjectsOfData();

    // U isoparametric lines
    _attributes[n].u_isolines = _attributes[n].patch->GenerateUIsoparametricLines(u_isoline_count,1,u_div_point_count);

    if(!_attributes[n].u_isolines)
    {
        std::cout<<"Cannot create uisoline !\n";
        _attributes.pop_back();
        return GL_FALSE;
    }
    // U isoparametric lines UpdateVBO
    for(GLuint i = 0; i < _attributes[n].u_isolines->GetColumnCount();i++)
    {
        if(!(*_attributes[n].u_isolines)[i]->UpdateVertexBufferObjects())
        {
            std::cout<<"Cannot update uisoline !\n";
            _attributes.pop_back();
            return GL_FALSE;
        }
    }

    _attributes[n].v_isolines = _attributes[n].patch->GenerateVIsoparametricLines(v_isoline_count,1,v_div_point_count);

    if(!_attributes[n].v_isolines)
    {
        std::cout<<"Cannot create visoline !\n";
        _attributes.pop_back();
        return GL_FALSE;
    }

    for(GLuint  i = 0; i < _attributes[n].v_isolines->GetColumnCount();i++)
    {
        if(!(*_attributes[n].v_isolines)[i]->UpdateVertexBufferObjects())
        {
            std::cout<<"Cannot update visoline !\n";
            _attributes.pop_back();
            return GL_FALSE;
        }
    }

    //Generate Image/Mesh
    _attributes[n].mesh = _attributes[n].patch->GenerateImage(u_div_point_count,v_div_point_count);

    if(!_attributes[n].mesh)
    {
        std::cout<<"Image/mesh not created!\n";
        _attributes.pop_back();
        return GL_FALSE;
    }

    //UpdateVBO
    if(!_attributes[n].mesh->UpdateVertexBufferObjects())
    {
        std::cout<<"Cannot update VBO!\n";
        _attributes.pop_back();
        return GL_FALSE;
    }


    return GL_TRUE;

}

int BiquadraticCompositeSurface3::GetDirectionIndex(Direction direction) const {

    switch(direction) {

    case N:
        return 0;
    case NW:
        return 1;
    case W:
        return 2;
    case SW:
        return 3;
    case S:
        return 4;
    case SE:
        return 5;
    case E:
        return 6;
    case NE:
        return 7;
    default:
        return -1;
    }
}

GLboolean BiquadraticCompositeSurface3::ContinueExistingPatch(const size_t &patch_index, Direction direction, string mat)
{
    int direc_ind = GetDirectionIndex(direction);
    //check if it already has this neighbor
    if(_attributes[patch_index].neighbours[direc_ind] != nullptr) {
        return GL_FALSE;
    }

    GLint attr_size = _attributes.size();
    _attributes.resize(attr_size + 1);
    _attributes[attr_size].patch = new BiquadraticPatch3();

    if(!_attributes[attr_size].patch)
    {
        _attributes.pop_back();
        return GL_FALSE;
    }

    if(direc_ind % 2 == 0) { // N, E, S, W
        for(int i = 0; i < 4; i++) {
            DCoordinate3 p0, p1;
            switch (direc_ind) {

            case 0:
                //get
                _attributes[patch_index].patch->GetData(i,3,p0);//0i
                _attributes[patch_index].patch->GetData(i,2,p1);//1i
                //set
                _attributes[attr_size].patch->SetData(i,0, p0);
                _attributes[attr_size].patch->SetData(i,1, 2.0 * p0 - p1);
                _attributes[attr_size].patch->SetData(i,2, 3.0 * p0 - 2.0 * p1);
                _attributes[attr_size].patch->SetData(i,3, 4.0 * p0 - 3.0 * p1);
                //neighbours
                _attributes[patch_index].neighbours[0] = &_attributes[attr_size];
                _attributes[attr_size].neighbours[4] = &_attributes[patch_index];
                break;
            case 2:
                //get
                _attributes[patch_index].patch->GetData(0,i,p0);//i3
                _attributes[patch_index].patch->GetData(1,i,p1);//i2
                //set
                _attributes[attr_size].patch->SetData(3,i, p0);
                _attributes[attr_size].patch->SetData(2,i, 2.0 * p0 - p1);
                _attributes[attr_size].patch->SetData(1,i, 3.0 * p0 - 2.0 * p1);
                _attributes[attr_size].patch->SetData(0,i, 4.0 * p0 - 3.0 * p1);
                //neighbours
                _attributes[patch_index].neighbours[2] = &_attributes[attr_size];
                _attributes[attr_size].neighbours[6] = &_attributes[patch_index];
                break;
            case 4:
                //get
                _attributes[patch_index].patch->GetData(i,0,p0);//0i
                _attributes[patch_index].patch->GetData(i,1,p1);//1i
                //set
                _attributes[attr_size].patch->SetData(i,3, p0);
                _attributes[attr_size].patch->SetData(i,2, 2.0 * p0 - p1);
                _attributes[attr_size].patch->SetData(i,1, 3.0 * p0 - 2.0 * p1);
                _attributes[attr_size].patch->SetData(i,0, 4.0 * p0 - 3.0 * p1);
                //neighbours
                _attributes[patch_index].neighbours[4] = &_attributes[attr_size];
                _attributes[attr_size].neighbours[0] = &_attributes[patch_index];
                break;
            case 6:
                //get
                _attributes[patch_index].patch->GetData(3,i,p0);//i3
                _attributes[patch_index].patch->GetData(2,i,p1);//i2
                //set
                _attributes[attr_size].patch->SetData(0,i, p0);
                _attributes[attr_size].patch->SetData(1,i, 2.0 * p0 - p1);
                _attributes[attr_size].patch->SetData(2,i, 3.0 * p0 - 2.0 * p1);
                _attributes[attr_size].patch->SetData(3,i, 4.0 * p0 - 3.0 * p1);
                //neighbours
                _attributes[patch_index].neighbours[6] = &_attributes[attr_size];
                _attributes[attr_size].neighbours[2] = &_attributes[patch_index];
                break;
            default:
                std::cout<<"We should not be here..."<<std::endl;
                return GL_FALSE;
            }
        }
    } else { // NE, SE, SW, NW
        DCoordinate3 p0, p1, p2, p3;
        switch (direc_ind) {

        case 1:
            //get
            _attributes[patch_index].patch->GetData(1,2,p0);
            _attributes[patch_index].patch->GetData(1,3,p1);
            _attributes[patch_index].patch->GetData(0,2,p2);
            _attributes[patch_index].patch->GetData(0,3,p3);
            //set
            _attributes[attr_size].patch->SetData(0,0, 4.0 * p3 - 3.0 * p1);
            _attributes[attr_size].patch->SetData(0,1, 8.0 * p3 - 4.0 * p2 - 6.0 * p1 + 3.0 * p0);
            _attributes[attr_size].patch->SetData(0,2, 12.0 * p3 - 8.0 * p2 - 9.0 * p1 + 6.0 * p0);
            _attributes[attr_size].patch->SetData(0,3, 16.0 * p3 - 12.0 * p2 - 12.0 * p1 + 9.0 * p0);
            _attributes[attr_size].patch->SetData(1,0, 3.0 * p3 - 2.0 * p1);
            _attributes[attr_size].patch->SetData(1,1, 6.0 * p3 - 3.0 * p2 - 4.0 * p1 + 2.0 * p0);
            _attributes[attr_size].patch->SetData(1,2, 9.0 * p3 - 6.0 * p2 - 6.0 * p1 + 4.0 * p0);
            _attributes[attr_size].patch->SetData(1,3, 12.0 * p3 - 9.0 * p2 - 8.0 * p1 + 6.0 * p0);
            _attributes[attr_size].patch->SetData(2,0, 2.0 * p3 - p1);
            _attributes[attr_size].patch->SetData(2,1, 4.0 * p3 - 2.0 * p2 - 2.0 * p1 + p0);
            _attributes[attr_size].patch->SetData(2,2, 6.0 * p3 - 4.0 * p2 - 3.0 * p1 + 2.0 * p0);
            _attributes[attr_size].patch->SetData(2,3, 8.0 * p3 - 6.0 * p2 - 4.0 * p1 + 3.0 * p0);
            _attributes[attr_size].patch->SetData(3,0, p3);
            _attributes[attr_size].patch->SetData(3,1, 2.0 * p3 - p2);
            _attributes[attr_size].patch->SetData(3,2, 3.0 * p3 - 2.0 * p2);
            _attributes[attr_size].patch->SetData(3,3, 4.0 * p3 - 3.0 * p2);
            //neighbours
            _attributes[patch_index].neighbours[1] = &_attributes[attr_size];
            _attributes[attr_size].neighbours[5] = &_attributes[patch_index];

            break;
        case 3://get
            _attributes[patch_index].patch->GetData(1,1,p0);
            _attributes[patch_index].patch->GetData(1,0,p1);
            _attributes[patch_index].patch->GetData(0,1,p2);
            _attributes[patch_index].patch->GetData(0,0,p3);
            //set
            _attributes[attr_size].patch->SetData(0,0, 16.0 * p3 - 12.0 * p2 - 12.0 * p1 + 9.0 * p0);
            _attributes[attr_size].patch->SetData(0,1, 12.0 * p3 - 8.0 * p2 - 9.0 * p1 + 6.0 * p0);
            _attributes[attr_size].patch->SetData(0,2, 8.0 * p3 - 4.0 * p2 - 6.0 * p1 + 3.0 * p0);
            _attributes[attr_size].patch->SetData(0,3, 4.0 * p3 - 3.0 * p1);
            _attributes[attr_size].patch->SetData(1,0, 12.0 * p3 - 9.0 * p2 - 8.0 * p1 + 6.0 * p0);
            _attributes[attr_size].patch->SetData(1,1, 9.0 * p3 - 6.0 * p2 - 6.0 * p1 + 4.0 * p0);
            _attributes[attr_size].patch->SetData(1,2, 6.0 * p3 - 3.0 * p2 - 4.0 * p1 + 2.0 * p0);
            _attributes[attr_size].patch->SetData(1,3, 3.0 * p3 - 2.0 * p1);
            _attributes[attr_size].patch->SetData(2,0, 8.0 * p3 - 6.0 * p2 - 4.0 * p1 + 3.0 * p0);
            _attributes[attr_size].patch->SetData(2,1, 6.0 * p3 - 4.0 * p2 - 3.0 * p1 + 2.0 * p0);
            _attributes[attr_size].patch->SetData(2,2, 4.0 * p3 - 2.0 * p2 - 2.0 * p1 + p0);
            _attributes[attr_size].patch->SetData(2,3, 2.0 * p3 - p1);
            _attributes[attr_size].patch->SetData(3,0, 4.0 * p3 - 3.0 * p2);
            _attributes[attr_size].patch->SetData(3,1, 3.0 * p3 - 2.0 * p2);
            _attributes[attr_size].patch->SetData(3,2, 2.0 * p3 - p2);
            _attributes[attr_size].patch->SetData(3,3, p3);
            //neighbours
            _attributes[patch_index].neighbours[3] = &_attributes[attr_size];
            _attributes[attr_size].neighbours[7] = &_attributes[patch_index];
            break;
        case 5:
            //get
            _attributes[patch_index].patch->GetData(2,1,p0);
            _attributes[patch_index].patch->GetData(2,0,p1);
            _attributes[patch_index].patch->GetData(3,1,p2);
            _attributes[patch_index].patch->GetData(3,0,p3);
            //set
            _attributes[attr_size].patch->SetData(0,0, 4.0 * p3 - 3.0 * p2);
            _attributes[attr_size].patch->SetData(0,1, 3.0 * p3 - 2.0 * p2);
            _attributes[attr_size].patch->SetData(0,2, 2.0 * p3 - p2);
            _attributes[attr_size].patch->SetData(0,3, p3);
            _attributes[attr_size].patch->SetData(1,0, 8.0 * p3 - 6.0 * p2 - 4.0 * p1 + 3.0 * p0);
            _attributes[attr_size].patch->SetData(1,1, 6.0 * p3 - 4.0 * p2 - 3.0 * p1 + 2.0 * p0);
            _attributes[attr_size].patch->SetData(1,2, 4.0 * p3 - 2.0 * p2 - 2.0 * p1 + p0);
            _attributes[attr_size].patch->SetData(1,3, 2.0 * p3 - p1);
            _attributes[attr_size].patch->SetData(2,0, 12.0 * p3 - 9.0 * p2 - 8.0 * p1 + 6.0 * p0);
            _attributes[attr_size].patch->SetData(2,1, 9.0 * p3 - 6.0 * p2 - 6.0 * p1 + 4.0 * p0);
            _attributes[attr_size].patch->SetData(2,2, 6.0 * p3 - 3.0 * p2 - 4.0 * p1 + 2.0 * p0);
            _attributes[attr_size].patch->SetData(2,3, 3.0 * p3 - 2.0 * p1);
            _attributes[attr_size].patch->SetData(3,0, 16.0 * p3 - 12.0 * p2 - 12.0 * p1 + 9.0 * p0);
            _attributes[attr_size].patch->SetData(3,1, 12.0 * p3 - 8.0 * p2 - 9.0 * p1 + 6.0 * p0);
            _attributes[attr_size].patch->SetData(3,2, 8.0 * p3 - 4.0 * p2 - 6.0 * p1 + 3.0 * p0);
            _attributes[attr_size].patch->SetData(3,3, 4.0 * p3 - 3.0 * p1);
            //neighbours
            _attributes[patch_index].neighbours[5] = &_attributes[attr_size];
            _attributes[attr_size].neighbours[1] = &_attributes[patch_index];
            break;
        case 7:
            //get
            _attributes[patch_index].patch->GetData(2,2,p0);
            _attributes[patch_index].patch->GetData(2,3,p1);
            _attributes[patch_index].patch->GetData(3,2,p2);
            _attributes[patch_index].patch->GetData(3,3,p3);
            //set
            _attributes[attr_size].patch->SetData(0,0, p3);
            _attributes[attr_size].patch->SetData(0,1, 2.0 * p3 - p2);
            _attributes[attr_size].patch->SetData(0,2, 3.0 * p3 - 2.0 * p2);
            _attributes[attr_size].patch->SetData(0,3, 4.0 * p3 - 3.0 * p2);
            _attributes[attr_size].patch->SetData(1,0, 2.0 * p3 - p1);
            _attributes[attr_size].patch->SetData(1,1, 4.0 * p3 - 2.0 * p2 - 2.0 * p1 + p0);
            _attributes[attr_size].patch->SetData(1,2, 6.0 * p3 - 4.0 * p2 - 3.0 * p1 + 2.0 * p0);
            _attributes[attr_size].patch->SetData(1,3, 8.0 * p3 - 6.0 * p2 - 4.0 * p1 + 3.0 * p0);
            _attributes[attr_size].patch->SetData(2,0, 3.0 * p3 - 2.0 * p1);
            _attributes[attr_size].patch->SetData(2,1, 6.0 * p3 - 3.0 * p2 - 4.0 * p1 + 2.0 * p0);
            _attributes[attr_size].patch->SetData(2,2, 9.0 * p3 - 6.0 * p2 - 6.0 * p1 + 4.0 * p0);
            _attributes[attr_size].patch->SetData(2,3, 12.0 * p3 - 9.0 * p2 - 8.0 * p1 + 6.0 * p0);
            _attributes[attr_size].patch->SetData(3,0, 4.0 * p3 - 3.0 * p1);
            _attributes[attr_size].patch->SetData(3,1, 8.0 * p3 - 4.0 * p2 - 6.0 * p1 + 3.0 * p0);
            _attributes[attr_size].patch->SetData(3,2, 12.0 * p3 - 8.0 * p2 - 9.0 * p1 + 6.0 * p0);
            _attributes[attr_size].patch->SetData(3,3, 16.0 * p3 - 12.0 * p2 - 12.0 * p1 + 9.0 * p0);
            //neighbours
            _attributes[patch_index].neighbours[7] = &_attributes[attr_size];
            _attributes[attr_size].neighbours[3] = &_attributes[patch_index];
            break;
        default:
            std::cout<<"We should not be here..."<<std::endl;
            return GL_FALSE;
        }
    }

    if(mat == "Gold")
        _attributes[attr_size].material = &MatFBGold;
    if(mat == "Ruby")
        _attributes[attr_size].material = &MatFBRuby;
    if(mat == "Emerald")
        _attributes[attr_size].material = &MatFBEmerald;
    if(mat == "Brass")
        _attributes[attr_size].material = &MatFBBrass;
    if(mat == "Pearl")
        _attributes[attr_size].material = &MatFBPearl;
    if(mat == "Turquoise")
        _attributes[attr_size].material = &MatFBTurquoise;
    if(mat == "Silver")
        _attributes[attr_size].material = &MatFBSilver;

    //Update dataVBO
    _attributes[attr_size].patch->UpdateVertexBufferObjectsOfData();

    // U isoparametric lines
    _attributes[attr_size].u_isolines = _attributes[attr_size].patch->GenerateUIsoparametricLines(30,1,30);

    if(!_attributes[attr_size].u_isolines)
    {
        std::cout<<"Cannot create uisoline !\n";
        _attributes.pop_back();
        return GL_FALSE;
    }
    // U isoparametric lines UpdateVBO
    for(GLuint i = 0; i < _attributes[attr_size].u_isolines->GetColumnCount();i++)
    {
        if(!(*_attributes[attr_size].u_isolines)[i]->UpdateVertexBufferObjects())
        {
            std::cout<<"Cannot update uisoline !\n";
            _attributes.pop_back();
            return GL_FALSE;
        }
    }

    _attributes[attr_size].v_isolines = _attributes[attr_size].patch->GenerateVIsoparametricLines(30,1,30);

    if(!_attributes[attr_size].v_isolines)
    {
        std::cout<<"Cannot create visoline !\n";
        _attributes.pop_back();
        return GL_FALSE;
    }

    for(GLuint  i = 0; i < _attributes[attr_size].v_isolines->GetColumnCount();i++)
    {
        if(!(*_attributes[attr_size].v_isolines)[i]->UpdateVertexBufferObjects())
        {
            std::cout<<"Cannot update visoline !\n";
            _attributes.pop_back();
            return GL_FALSE;
        }
    }

    //Generate Image/Mesh
    _attributes[attr_size].mesh = _attributes[attr_size].patch->GenerateImage(30,30);

    if(!_attributes[attr_size].mesh)
    {
        std::cout<<"Image/mesh not created!\n";
        _attributes.pop_back();
        return GL_FALSE;
    }

    //UpdateVBO
    if(!_attributes[attr_size].mesh->UpdateVertexBufferObjects())
    {
        std::cout<<"Cannot update VBO!\n";
        _attributes.pop_back();
        return GL_FALSE;
    }
    return GL_TRUE;
}

GLboolean BiquadraticCompositeSurface3::JoinExistingPatches(const size_t &patch_index1, Direction direction1, const size_t &patch_index2, Direction direction2, string mat)
{
    int direc_ind1 = GetDirectionIndex(direction1);
    int direc_ind2 = GetDirectionIndex(direction2);
    //check if it already has this neighbor
    if(_attributes[patch_index1].neighbours[direc_ind1] != nullptr || _attributes[patch_index2].neighbours[direc_ind2] != nullptr) {
        return GL_FALSE;
    }

    GLint attr_size = _attributes.size();
    _attributes.resize(attr_size + 1);
    _attributes[attr_size].patch = new BiquadraticPatch3();

    if(!_attributes[attr_size].patch)
    {
        _attributes.pop_back();
        return GL_FALSE;
    }

    if(direc_ind1 % 2 == 0 && direc_ind2 % 2 == 0) {
        for(int i = 0; i < 4; i++) {
            DCoordinate3 p0, p1, p2, p3;
            switch(direc_ind1) {

            case 0:
                //get
                _attributes[patch_index1].patch->GetData(i,3,p0);
                _attributes[patch_index1].patch->GetData(i,2,p1);
                break;
            case 2:
                //get
                _attributes[patch_index1].patch->GetData(0,i,p0);
                _attributes[patch_index1].patch->GetData(1,i,p1);
                break;
            case 4:
                //get
                _attributes[patch_index1].patch->GetData(i,0,p0);
                _attributes[patch_index1].patch->GetData(i,1,p1);
                break;
            case 6:
                //get
                _attributes[patch_index1].patch->GetData(3,i,p0);
                _attributes[patch_index1].patch->GetData(2,i,p1);
                break;

            }
            switch(direc_ind2) {

            case 0:
                //get
                _attributes[patch_index2].patch->GetData(i,3,p3);
                _attributes[patch_index2].patch->GetData(i,2,p2);
                break;
            case 2:
                //get
                _attributes[patch_index2].patch->GetData(0,i,p3);
                _attributes[patch_index2].patch->GetData(1,i,p2);
                break;
            case 4:
                //get
                _attributes[patch_index2].patch->GetData(i,0,p3);
                _attributes[patch_index2].patch->GetData(i,1,p2);
                break;
            case 6:
                //get
                _attributes[patch_index2].patch->GetData(3,i,p3);
                _attributes[patch_index2].patch->GetData(2,i,p2);
                break;

            }
            //set
            _attributes[attr_size].patch->SetData(i,0, p0);
            _attributes[attr_size].patch->SetData(i,1, 2.0 * p0 - p1);
            _attributes[attr_size].patch->SetData(i,2, 2.0 * p3 - p2);
            _attributes[attr_size].patch->SetData(i,3, p3);
        }
        _attributes[attr_size].neighbours[6] = &_attributes[patch_index2];
        _attributes[attr_size].neighbours[2] = &_attributes[patch_index1];
        _attributes[patch_index1].neighbours[direc_ind1] = &_attributes[attr_size];
        _attributes[patch_index2].neighbours[direc_ind2] = &_attributes[attr_size];

    } else if(direc_ind1 % 2 == 1 && direc_ind2 % 2 == 1) {
        DCoordinate3 p0, p1, p2, p3, p4, p5, p6, p7;
        switch(direc_ind1) {

        case 1:
            //get
            _attributes[patch_index1].patch->GetData(0,4,p0);
            _attributes[patch_index1].patch->GetData(0,3,p1);
            _attributes[patch_index1].patch->GetData(1,4,p2);
            _attributes[patch_index1].patch->GetData(1,3,p3);
            break;
        case 3:
            //get
            _attributes[patch_index1].patch->GetData(3,3,p0);
            _attributes[patch_index1].patch->GetData(2,3,p1);
            _attributes[patch_index1].patch->GetData(3,2,p2);
            _attributes[patch_index1].patch->GetData(2,2,p3);
            break;
        case 5:
            //get
            _attributes[patch_index1].patch->GetData(3,0,p0);
            _attributes[patch_index1].patch->GetData(2,0,p1);
            _attributes[patch_index1].patch->GetData(3,1,p2);
            _attributes[patch_index1].patch->GetData(2,1,p3);
            break;
        case 7:
            //get
            _attributes[patch_index1].patch->GetData(0,0,p0);
            _attributes[patch_index1].patch->GetData(0,1,p1);
            _attributes[patch_index1].patch->GetData(1,0,p2);
            _attributes[patch_index1].patch->GetData(1,1,p3);
            break;

        }
        switch(direc_ind2) {

        case 1:
            //get
            _attributes[patch_index2].patch->GetData(0,4,p7);
            _attributes[patch_index2].patch->GetData(0,3,p6);
            _attributes[patch_index2].patch->GetData(1,4,p5);
            _attributes[patch_index2].patch->GetData(1,3,p4);
            break;
        case 3:
            //get
            _attributes[patch_index2].patch->GetData(3,3,p7);
            _attributes[patch_index2].patch->GetData(2,3,p6);
            _attributes[patch_index2].patch->GetData(3,2,p5);
            _attributes[patch_index2].patch->GetData(2,2,p4);
            break;
        case 5:
            //get
            _attributes[patch_index2].patch->GetData(3,0,p7);
            _attributes[patch_index2].patch->GetData(2,0,p6);
            _attributes[patch_index2].patch->GetData(3,1,p5);
            _attributes[patch_index2].patch->GetData(2,1,p4);
            break;
        case 7:
            //get
            _attributes[patch_index2].patch->GetData(0,0,p7);
            _attributes[patch_index2].patch->GetData(0,1,p6);
            _attributes[patch_index2].patch->GetData(1,0,p5);
            _attributes[patch_index2].patch->GetData(1,1,p4);
            break;

        }

        //set
        _attributes[attr_size].patch->SetData(0,0, p0);//
        _attributes[attr_size].patch->SetData(0,1, 2.0 * p0 - p2);//
        _attributes[attr_size].patch->SetData(1,0, 2.0 * p0 - p1);//
        _attributes[attr_size].patch->SetData(1,1, 2.0 * p0 - p3); //
        _attributes[attr_size].patch->SetData(0,2, 2.0 * p0 - p1);
        _attributes[attr_size].patch->SetData(0,3, p3);
        _attributes[attr_size].patch->SetData(1,2, p7 + p0 - p4 - p3 + 0.5 * p6 + 0.5 * p1); //
        _attributes[attr_size].patch->SetData(1,3, p3);
        _attributes[attr_size].patch->SetData(2,0, p0);
        _attributes[attr_size].patch->SetData(2,1, 2.0 * p0 - p1);
        _attributes[attr_size].patch->SetData(3,0, p0);
        _attributes[attr_size].patch->SetData(3,1, 2.0 * p0 - p1);
        _attributes[attr_size].patch->SetData(2,2, 2.0 * p7 - p4);//
        _attributes[attr_size].patch->SetData(2,3, 2.0 * p7 - p5);//
        _attributes[attr_size].patch->SetData(3,2, 2.0 * p7 - p6);//
        _attributes[attr_size].patch->SetData(3,3, p7); //

        _attributes[attr_size].neighbours[3] = &_attributes[patch_index2];
        _attributes[attr_size].neighbours[7] = &_attributes[patch_index1];
        switch(direc_ind1) {
        case 0:
            _attributes[patch_index1].neighbours[2] = &_attributes[attr_size];
            break;
        case 1:
            _attributes[patch_index1].neighbours[1] = &_attributes[attr_size];
            break;
        case 2:
            _attributes[patch_index1].neighbours[4] = &_attributes[attr_size];
            break;
        case 3:
            _attributes[patch_index1].neighbours[7] = &_attributes[attr_size];
            break;
        case 4:
            _attributes[patch_index1].neighbours[6] = &_attributes[attr_size];
            break;
        case 5:
            _attributes[patch_index1].neighbours[5] = &_attributes[attr_size];
            break;
        case 6:
            _attributes[patch_index1].neighbours[0] = &_attributes[attr_size];
            break;
        case 7:
            _attributes[patch_index1].neighbours[3] = &_attributes[attr_size];
            break;
        }
        switch(direc_ind2) {
        case 0:
            _attributes[patch_index2].neighbours[2] = &_attributes[attr_size];
            break;
        case 1:
            _attributes[patch_index2].neighbours[1] = &_attributes[attr_size];
            break;
        case 2:
            _attributes[patch_index2].neighbours[4] = &_attributes[attr_size];
            break;
        case 3:
            _attributes[patch_index2].neighbours[7] = &_attributes[attr_size];
            break;
        case 4:
            _attributes[patch_index2].neighbours[6] = &_attributes[attr_size];
            break;
        case 5:
            _attributes[patch_index2].neighbours[5] = &_attributes[attr_size];
            break;
        case 6:
            _attributes[patch_index2].neighbours[0] = &_attributes[attr_size];
            break;
        case 7:
            _attributes[patch_index2].neighbours[3] = &_attributes[attr_size];
            break;
        }
    } else if(direc_ind1 % 2 == 1) {

    } else if(direc_ind2 % 2 == 1) {

    }

    if(mat == "Gold")
        _attributes[attr_size].material = &MatFBGold;
    if(mat == "Ruby")
        _attributes[attr_size].material = &MatFBRuby;
    if(mat == "Emerald")
        _attributes[attr_size].material = &MatFBEmerald;
    if(mat == "Brass")
        _attributes[attr_size].material = &MatFBBrass;
    if(mat == "Pearl")
        _attributes[attr_size].material = &MatFBPearl;
    if(mat == "Turquoise")
        _attributes[attr_size].material = &MatFBTurquoise;
    if(mat == "Silver")
        _attributes[attr_size].material = &MatFBSilver;

    //Update dataVBO
    _attributes[attr_size].patch->UpdateVertexBufferObjectsOfData();

    // U isoparametric lines
    _attributes[attr_size].u_isolines = _attributes[attr_size].patch->GenerateUIsoparametricLines(30,1,30);

    if(!_attributes[attr_size].u_isolines)
    {
        std::cout<<"Cannot create uisoline !\n";
        _attributes.pop_back();
        return GL_FALSE;
    }
    // U isoparametric lines UpdateVBO
    for(GLuint i = 0; i < _attributes[attr_size].u_isolines->GetColumnCount();i++)
    {
        if(!(*_attributes[attr_size].u_isolines)[i]->UpdateVertexBufferObjects())
        {
            std::cout<<"Cannot update uisoline !\n";
            _attributes.pop_back();
            return GL_FALSE;
        }
    }

    _attributes[attr_size].v_isolines = _attributes[attr_size].patch->GenerateVIsoparametricLines(30,1,30);

    if(!_attributes[attr_size].v_isolines)
    {
        std::cout<<"Cannot create visoline !\n";
        _attributes.pop_back();
        return GL_FALSE;
    }

    for(GLuint  i = 0; i < _attributes[attr_size].v_isolines->GetColumnCount();i++)
    {
        if(!(*_attributes[attr_size].v_isolines)[i]->UpdateVertexBufferObjects())
        {
            std::cout<<"Cannot update visoline !\n";
            _attributes.pop_back();
            return GL_FALSE;
        }
    }

    //Generate Image/Mesh
    _attributes[attr_size].mesh = _attributes[attr_size].patch->GenerateImage(30,30);

    if(!_attributes[attr_size].mesh)
    {
        std::cout<<"Image/mesh not created!\n";
        _attributes.pop_back();
        return GL_FALSE;
    }

    //UpdateVBO
    if(!_attributes[attr_size].mesh->UpdateVertexBufferObjects())
    {
        std::cout<<"Cannot update VBO!\n";
        _attributes.pop_back();
        return GL_FALSE;
    }


    for(int i = 0; i < 8; i++) {
        if(_attributes[patch_index1].neighbours[i] == nullptr) {
            cout<<i<<"nullptr"<<endl;
        } else {
            cout<<i<<"JO"<<endl;
        }
    }
    for(int i = 0; i < 8; i++) {
        if(_attributes[patch_index2].neighbours[i] == nullptr) {
            cout<<i<<"nullptr"<<endl;
        } else {
            cout<<i<<"JO"<<endl;
        }
    }

    return GL_TRUE;
}

GLboolean BiquadraticCompositeSurface3::MergeExistingPatches(const size_t &patch_index1, Direction direction1, const size_t &patch_index2, Direction direction2)
{
    if(patch_index1 == patch_index2)
        return GL_FALSE;
    if(_attributes[patch_index1].neighbours[direction1])
        return GL_FALSE;

    if(_attributes[patch_index2].neighbours[direction2])
        return GL_FALSE;

    RowMatrix<DCoordinate3> newPoints;
    newPoints.ResizeColumns(4);
    GLdouble x1,x2,y1,y2,z1,z2;
    GLuint patch1_position1,patch1_position2,patch2_position1,patch2_position2;

    for(GLuint i = 0 ; i < 4; i++)
    {
        switch (direction1) {
        case E:
            _attributes[patch_index1].patch->GetData(2,i,x1,y1,z1);
            patch1_position1 = 3;
            patch1_position2 = i;
            _attributes[patch_index1].neighbours[E] = &_attributes[patch_index2];

            break;
        case W:
            _attributes[patch_index1].patch->GetData(1,i,x1,y1,z1);
            patch1_position1 = 0;
            patch1_position2 = i;
            _attributes[patch_index1].neighbours[W] = &_attributes[patch_index2];
            break;
        case S:
            _attributes[patch_index1].patch->GetData(i,1,x1,y1,z1);
            patch1_position1 = i;
            patch1_position2 = 0;
            _attributes[patch_index1].neighbours[S] = &_attributes[patch_index2];
            break;
        case N:
            _attributes[patch_index1].patch->GetData(i,2,x1,y1,z1);
            patch1_position1 = i;
            patch1_position2 = 3;
            _attributes[patch_index1].neighbours[N] = &_attributes[patch_index2];
            break;
        case NE:
            if(i < 2 )
            {
                _attributes[patch_index1].patch->GetData(i,2,x1,y1,z1);
                patch1_position1 = i;
                patch1_position2 = 3;
                _attributes[patch_index1].neighbours[NE] = &_attributes[patch_index2];
            }
            else
            {
                _attributes[patch_index1].patch->GetData(2,i,x1,y1,z1);
                patch1_position1 = 3;
                patch1_position2 = i;
                _attributes[patch_index1].neighbours[NE] = &_attributes[patch_index2];
            }
            break;
        }
        switch (direction2) {
        case E:
            _attributes[patch_index2].patch->GetData(2,i,x2,y2,z2);
            patch2_position1 = 3;
            patch2_position2 = i;
            _attributes[patch_index2].neighbours[E] = &_attributes[patch_index1];
            break;
        case W:
            _attributes[patch_index2].patch->GetData(1,i,x2,y2,z2);
            patch2_position1 = 0;
            patch2_position2 = i;
            _attributes[patch_index2].neighbours[W] = &_attributes[patch_index1];

            break;
        case S:
            _attributes[patch_index2].patch->GetData(i,1,x2,y2,z2);
            patch2_position1 = i;
            patch2_position2 = 0;
            _attributes[patch_index2].neighbours[S] = &_attributes[patch_index1];
            break;
        case N:
            _attributes[patch_index2].patch->GetData(i,2,x2,y2,z2);
            patch2_position1 = i;
            patch2_position2 = 3;
            _attributes[patch_index2].neighbours[N] = &_attributes[patch_index1];
            break;
        case NW:
            if(i < 2 )
            {
                _attributes[patch_index2].patch->GetData(i,2,x2,y2,z2);
                patch2_position1 = i;
                patch2_position2 = 3;
                _attributes[patch_index2].neighbours[N] = &_attributes[patch_index1];
            }
            else
            {
                _attributes[patch_index2].patch->GetData(1,i,x2,y2,z2);
                patch2_position1 = 0;
                patch2_position2 = i;
                _attributes[patch_index2].neighbours[W] = &_attributes[patch_index1];
            }
            break;

        }

        _attributes[patch_index1].patch->SetData(patch1_position1,patch1_position2,(x1 + x2)/2.0,(y1 + y2)/2.0,(z1 + z2)/2.0);
        _attributes[patch_index2].patch->SetData(patch2_position1,patch2_position2,(x1 + x2)/2.0,(y1 + y2)/2.0,(z1 + z2)/2.0);
    }

    _attributes[patch_index1].patch->UpdateVertexBufferObjectsOfData();

    if(!UpdatePatch(patch_index1))
        return GL_FALSE;

    _attributes[patch_index2].patch->UpdateVertexBufferObjectsOfData();

    if(!UpdatePatch(patch_index2))
        return GL_FALSE;

    vector<PatchAttributes*> visited;
    visited.push_back(&_attributes[patch_index1]);
    visited.push_back(&_attributes[patch_index2]);


    for(GLuint i = 0; i < 8;i++)
    {
        if(_attributes[patch_index1].neighbours[i] && _attributes[patch_index1].neighbours[i] != &_attributes[patch_index2])
        {
            GLuint index = _attributes[patch_index1].neighbours[i]->index;
            GLuint j = 0;
            for(j = 0; j < 8; j++)
            {
                if(_attributes[patch_index1].neighbours[i]->neighbours[j] == &_attributes[patch_index1])
                    break;
            }

            BiquadraticCompositeSurface3::Direction dir1 = BiquadraticCompositeSurface3::Direction(i);
            BiquadraticCompositeSurface3::Direction dir2 = BiquadraticCompositeSurface3::Direction(j);
            MergerOthers(patch_index1,index,dir1,dir2,visited);
            //mergeOthers

        }

        if(_attributes[patch_index2].neighbours[i] && _attributes[patch_index2].neighbours[i] != &_attributes[patch_index1])
        {
            GLuint index = _attributes[patch_index2].neighbours[i]->index;
            GLuint j = 0;
            for(j = 0; j < 8; j++)
            {
                if(_attributes[patch_index2].neighbours[i]->neighbours[j] == &_attributes[patch_index2])
                    break;
            }

            BiquadraticCompositeSurface3::Direction dir1 = BiquadraticCompositeSurface3::Direction(i);
            BiquadraticCompositeSurface3::Direction dir2 = BiquadraticCompositeSurface3::Direction(j);
            //mergeOthers
            MergerOthers(patch_index2,index,dir1,dir2,visited);

        }
    }
    return GL_TRUE;
}

GLboolean BiquadraticCompositeSurface3::MergerOthers(GLuint index1, GLuint index2, Direction d1, Direction d2, std::vector<PatchAttributes *> visited)
{
    RowMatrix<DCoordinate3> newPoints;
    newPoints.ResizeColumns(4);
    GLdouble x1,x2,y1,y2,z1,z2;
    GLuint patch1_position1,patch1_position2,patch2_position1,patch2_position2;

    for(GLuint i = 0; i < 4; i++)
    {
        switch (d2) {
        case W:
            _attributes[index2].patch->GetData(1,i,x2,y2,z2);
            patch1_position1 = 1;
            patch1_position2 = i;
            patch2_position1 = 0;
            patch2_position2 = i;
            break;
        case E:
            _attributes[index2].patch->GetData(2,i,x2,y2,z2);
            patch1_position1 = 2;
            patch1_position2 = i;
            patch2_position1 = 3;
            patch2_position2 = i;
            break;
        case S:
            _attributes[index2].patch->GetData(i,1,x2,y2,z2);
            patch1_position1 = i;
            patch1_position2 = 1;
            patch2_position1 = i;
            patch2_position2 = 0;
            break;
        case N:
            _attributes[index2].patch->GetData(i,2,x2,y2,z2);
            patch1_position1 = i;
            patch1_position2 = 2;
            patch2_position1 = i;
            patch2_position2 = 3;
            break;
        }

        switch (d1) {
        case E:
            _attributes[index1].patch->GetData(3,i,x1,y1,z1);
            _attributes[index2].patch->SetData(patch1_position1,patch1_position2,
                                               2.0 * (*_attributes[index1].patch)(3,i) - (*_attributes[index1].patch)(2,i));
            break;
        case W:
            _attributes[index1].patch->GetData(0,i,x1,y1,z1);
            _attributes[index2].patch->SetData(patch1_position1,patch1_position2,
                                               2.0*(*_attributes[index1].patch)(0,i) - (*_attributes[index1].patch)(1,i));
            break;
        case S:
            _attributes[index1].patch->GetData(i,0,x1,y1,z1);
            _attributes[index2].patch->SetData(patch1_position1,patch1_position2,
                                               2.0 * (*_attributes[index1].patch)(i,0) - (*_attributes[index1].patch)(i,1));
            break;
        case N:
            _attributes[index1].patch->GetData(i,3,x1,y1,z1);
            _attributes[index2].patch->SetData(patch1_position1,patch1_position2,
                                               2.0* (*_attributes[index1].patch)(i,3) - (*_attributes[index1].patch)(i,2));
            break;

        }

        _attributes[index2].patch->SetData(patch2_position1,patch2_position2,x1,y1,z1);

    }

    _attributes[index2].patch->UpdateVertexBufferObjectsOfData();

    UpdatePatch(index2);

    visited.push_back(&_attributes[index2]);

    for(GLuint i = 0; i < 8; i++)
    {
        if(_attributes[index2].neighbours[i])
        {
            bool ok = true;
            for(GLuint k = 0; k < visited.size(); k++)
            {
                if(visited[k] == _attributes[index2].neighbours[i])
                {
                    ok = false;
                    break;
                }
            }

            if(ok)
            {
                GLuint index = _attributes[index2].neighbours[i]->index;
                int j;
                for(int j = 0; j < 8;j++)
                {
                    if(_attributes[index2].neighbours[i]->neighbours[j] == &_attributes[index2])
                        break;
                }

                BiquadraticCompositeSurface3::Direction dir1 = BiquadraticCompositeSurface3::Direction(i);
                BiquadraticCompositeSurface3::Direction dir2 = BiquadraticCompositeSurface3::Direction(j);
                MergerOthers(index2,index,dir1,dir2,visited);
            }
        }
    }


    return GL_TRUE;

}

GLboolean BiquadraticCompositeSurface3::ShiftPatch(GLuint index, GLdouble off_x, GLdouble off_y, GLdouble off_z)
{

    DCoordinate3 point,shiftPoint;
    shiftPoint = DCoordinate3(off_x,off_z,off_y);

    for(GLuint i = 0 ; i < 4; i++)
    {
        for(GLuint j = 0 ; j < 4; j++)
        {
            _attributes[index].patch->GetData(i,j,point);
            _attributes[index].patch->SetData(i,j,point + shiftPoint);
        }
    }
    _attributes[index].patch->UpdateVertexBufferObjectsOfData();
    if(!UpdatePatch(index))
    {
        std::cout<<"Error in Update!\n";
    }

    std::vector<PatchAttributes*> visited;
    visited.push_back(&_attributes[index]);

    for(GLuint i = 0 ; i < 8; i++)
    {

        GLboolean ok = GL_TRUE;
        if(_attributes[index].neighbours[i])
        {

            for(GLuint j = 0 ; j < visited.size(); j++)
            {
                if(visited[j] == _attributes[index].neighbours[i])
                {
                    ok = GL_FALSE;
                    break;
                }
            }
            if(ok)
            {

                ShiftNeighbours((*_attributes[index].neighbours[i]),visited,off_x,off_y,off_z);
            }
        }
    }

    /*
    for(GLuint i = 0; i < _attributes.size();i++)
    {
        PrintNeighbours(i);
    }
    */
    return GL_TRUE;
}


GLboolean BiquadraticCompositeSurface3::ShiftNeighbours(PatchAttributes &attr, std::vector<PatchAttributes *> visited, GLdouble off_x, GLdouble off_y, GLdouble off_z)
{
    DCoordinate3 point,shiftPoint;
    shiftPoint = DCoordinate3(off_x,off_y,off_z);

    for(int i = 0 ; i < 4; i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            attr.patch->GetData(i,j,point);
            attr.patch->SetData(i,j,point + shiftPoint);
        }
    }

    attr.patch->UpdateVertexBufferObjectsOfData();

    GLuint index;

    for(index = 0; index < _attributes.size();index++)
    {
        if(&_attributes[index] == &attr)
            break;
    }

    UpdatePatch(index);

    visited.push_back(&attr);

    for(GLuint i = 0; i < 8; i++)
    {
        GLboolean ok = GL_TRUE;
        if(attr.neighbours[i])
        {
            for(GLuint j = 0 ; j < visited.size(); j++)
            {
                if(visited[j] == attr.neighbours[i])
                {
                    ok = GL_FALSE;
                    break;
                }
            }
            if(ok)
            {
                ShiftNeighbours((*attr.neighbours[i]),visited,off_x,off_y,off_z);
            }
        }
    }

    return GL_TRUE;
}
GLboolean BiquadraticCompositeSurface3::UpdatePatch(GLuint index)
{
    //GenerateIMage
    if(_attributes[index].mesh)
        delete _attributes[index].mesh, _attributes[index].mesh = nullptr;
    _attributes[index].mesh = _attributes[index].patch->GenerateImage(30,30);

    if(!_attributes[index].mesh)
    {
        return GL_FALSE;
    }

    //UpdateVBO
    if(!_attributes[index].mesh->UpdateVertexBufferObjects())
    {
        return GL_FALSE;
    }

    //ISOLINE RESET
    if(_attributes[index].u_isolines)
    {
        for(GLuint i = 0; i < _attributes[index].u_isolines->GetColumnCount(); i++)
        {
            if((*_attributes[index].u_isolines)[i])
            {
                delete (*_attributes[index].u_isolines)[i], (*_attributes[index].u_isolines)[i] = nullptr;
            }
        }
    }
    delete _attributes[index].u_isolines,_attributes[index].u_isolines = nullptr;

    if(_attributes[index].v_isolines)
    {
        for(GLuint i = 0; i < _attributes[index].v_isolines->GetColumnCount(); i++)
        {
            if((*_attributes[index].v_isolines)[i])
            {
                delete (*_attributes[index].v_isolines)[i], (*_attributes[index].v_isolines)[i] = nullptr;
            }
        }
    }
    delete _attributes[index].v_isolines,_attributes[index].v_isolines = nullptr;

    _attributes[index].u_isolines = _attributes[index].patch->GenerateUIsoparametricLines(30,1,30);

    if(!_attributes[index].u_isolines)
    {
        return GL_FALSE;
    }

    for(GLuint i = 0; i < _attributes[index].u_isolines->GetColumnCount();i++)
    {
        if(!(*_attributes[index].u_isolines)[i]->UpdateVertexBufferObjects())
        {
            return GL_FALSE;
        }
    }

    _attributes[index].v_isolines = _attributes[index].patch->GenerateVIsoparametricLines(30,1,30);

    if(!_attributes[index].v_isolines)
    {
        return GL_FALSE;
    }

    for(GLuint i = 0; i < _attributes[index].v_isolines->GetColumnCount();i++)
    {
        if(!(*_attributes[index].v_isolines)[i]->UpdateVertexBufferObjects())
        {
            return GL_FALSE;
        }
    }

    return GL_TRUE;

}

GLboolean BiquadraticCompositeSurface3::RenderPatches(GLboolean d1, GLboolean u_lines, GLboolean v_lines, GLboolean polygon, GLuint light)
{

    if(_attributes.size() == 0)
    {
        std::cout<<"No elements!"<<std::endl;
        return GL_FALSE;
    }
    for(GLuint i = 0 ; i < _attributes.size(); i++)
    {


        if(u_lines)
        {
            for(GLuint j = 0 ; j < _attributes[i].u_isolines->GetColumnCount();j++)
            {
                (*_attributes[i].u_isolines)[j]->RenderDerivatives(0,GL_LINE_STRIP);
                if(d1)
                {
                    (*_attributes[i].u_isolines)[j]->RenderDerivatives(1,GL_LINES);
                }
            }
        }

        if(v_lines)
        {
            for(GLuint j = 0 ; j < _attributes[i].v_isolines->GetColumnCount();j++)
            {
                (*_attributes[i].v_isolines)[j]->RenderDerivatives(0,GL_LINE_STRIP);
                if(d1)
                {
                    (*_attributes[i].v_isolines)[j]->RenderDerivatives(1,GL_LINES);
                }
            }
        }
        if(polygon)
        {
            glColor3f(0.8,0.8,0.8);
            glPointSize(25.0f);
            glBegin(GL_POINTS);
            for(GLuint ii = 0; ii < 4; ii++)
            {
                if(ii == 3) {
                    glColor3f(0.2,0.9,0.5);
                }
                for(GLuint jj = 0; jj < 4; jj++)
                {
                    if(ii == 3 && jj == 3) {
                        glColor3f(0.8,0.3,0.5);
                    }
                    GLdouble x,y,z;
                    _attributes[i].patch->GetData(ii,jj,x,y,z);
                    glVertex3f(x,y,z);
                }
            }
            glEnd();
            glPointSize(1.0f);

            glLineWidth(3.0f);
            glColor3f(1.0,1.0,1.0);
            _attributes[i].patch->RenderData();
            glLineWidth(1.0f);
        }

        switch (light) {
        case 0: {
            HCoordinate3 dir(10.0, 10.0, 10.0, 0.0);
            Color4 ambient(0.4, 0.4, 0.4, 1.0);
            Color4 diffuse(0.8, 0.8, 0.8, 1.0);
            Color4 specular(1.0, 1.0, 1.0, 1.0);
            DirectionalLight *directionalL = new DirectionalLight(GL_LIGHT0, dir, ambient, diffuse, specular);
            directionalL->Enable();
            if(_attributes[i].mesh)
            {
                _attributes[i].material->Apply();
                _attributes[i].mesh->Render();
            }
            directionalL->Disable();
            delete directionalL;
            break;
        }
        case 1: {
            HCoordinate3 dir(10.0, 10.0, 10.0, 0.0), spotdir(1.0, 1.0, 1.0, 0.0);
            Color4 ambient(0.4, 0.4, 0.4, 1.0);
            Color4 diffuse(0.8, 0.8, 0.8, 1.0);
            Color4 specular(1.0, 1.0, 1.0, 1.0);
            Spotlight *spotL = new Spotlight(GL_LIGHT0, dir, ambient, diffuse, specular, 1.0, 1.0, 1.0, spotdir, 30.0, 10.0);
            spotL->Enable();
            if(_attributes[i].mesh)
            {
                _attributes[i].material->Apply();
                _attributes[i].mesh->Render();
            }
            spotL->Disable();
            break;
        }
        case 3: {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);

            if(_attributes[i].mesh)
            {
                _attributes[i].material->Apply();
                _attributes[i].mesh->Render();
            }

            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
            glDisable(GL_NORMALIZE);
            break;
        }

        }
    }

    return GL_TRUE;
}

void BiquadraticCompositeSurface3::SetShaderForAll(ShaderProgram &shader)
{

    for(GLuint i = 0; i < _attributes.size(); i++)
    {
        _attributes[i].shader = &shader;
    }
}

void BiquadraticCompositeSurface3::SetShaderByIndex(GLuint index, ShaderProgram &shader)
{
    _attributes[index].shader = &shader;
    cout<<"Shader set for: " <<index<<endl;
    _attributes[index].shader->Enable();


}

void BiquadraticCompositeSurface3::SetMaterialForAll(Material &material)
{
    for(GLuint i = 0; i < _attributes.size(); i++)
    {
        _attributes[i].material = &material;
    }
}

void BiquadraticCompositeSurface3::SetMaterialByIndex(GLuint index, Material &material)
{
    _attributes[index].material = &material;
}

BiquadraticCompositeSurface3::PatchAttributes BiquadraticCompositeSurface3::getPatchAttributes(GLuint index)
{
    return _attributes[index];
}

GLuint BiquadraticCompositeSurface3::getPatchIndex(GLuint patch_index)
{
    return _attributes[patch_index].index;
}

void BiquadraticCompositeSurface3::PrintNeighbours(GLuint index)
{
    //N, NW, W,SW,S,SE,E,NE
    std::cout<<_attributes[index].material<<endl;
    cout<<"N: "<<_attributes[index].neighbours[0]<<endl;
    cout<<"NE: "<<_attributes[index].neighbours[7]<<endl;
    cout<<"E: "<<_attributes[index].neighbours[6]<<endl;
    cout<<"SE: "<<_attributes[index].neighbours[5]<<endl;
    cout<<"S: "<<_attributes[index].neighbours[4]<<endl;
    cout<<"SW: "<<_attributes[index].neighbours[3]<<endl;
    cout<<"W: "<<_attributes[index].neighbours[2]<<endl;
    cout<<"NW: "<<_attributes[index].neighbours[1]<<endl;
}

void BiquadraticCompositeSurface3::clear()
{
    _attributes.clear();
}

GLboolean BiquadraticCompositeSurface3::MoveControlPoint(GLuint patch_index, GLuint point_i, GLuint point_j, GLdouble xp, GLdouble yp, GLdouble zp) {

    DCoordinate3 point(xp,yp,zp);
    std::vector<PatchAttributes*> visited;

    if(point_i == 0 || point_j == 0 || point_i == 3 || point_j == 3) {

        GLuint sum = 4 * point_i + point_j;
        int i = 0, x = 0, y = 0;
        DCoordinate3 p0, p1, op;
        switch(sum) {
        case 0:
            visited.push_back(&_attributes[patch_index]);
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    if(i == patch_index) continue;

                    _attributes[patch_index].patch->GetData(0, 0, p0);
                    _attributes[i].patch->GetData(0, 0, p1);
                    if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                        MoveControlPointNeighbours(i,0,0,point,visited);
                    } else {
                        _attributes[i].patch->GetData(0, 3, p1);
                        if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                            MoveControlPointNeighbours(i,0,3,point,visited);
                        } else {
                            _attributes[i].patch->GetData(3, 0, p1);
                            if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                MoveControlPointNeighbours(i,3,0,point,visited);
                            } else {
                                _attributes[i].patch->GetData(3, 3, p1);
                                if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                    MoveControlPointNeighbours(i,3,3,point,visited);
                                }
                            }
                        }
                    }
                }
            }
            _attributes[patch_index].patch->GetData(0, 0, op);
            _attributes[patch_index].patch->SetData(0, 0, op + point);
            _attributes[patch_index].patch->GetData(0, 1, op);
            _attributes[patch_index].patch->SetData(0, 1, op + point);
            _attributes[patch_index].patch->GetData(1, 0, op);
            _attributes[patch_index].patch->SetData(1, 0, op + point);
            _attributes[patch_index].patch->GetData(1, 1, op);
            _attributes[patch_index].patch->SetData(1, 1, op + point);

            UpdatePatch(patch_index);
            break;
        case 1:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    _attributes[patch_index].patch->GetData(0, 1, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        _attributes[patch_index].patch->GetData(0, 1, op);
                        _attributes[i].patch->SetData(x,y, op + point);;
                    }
                }
            }
            _attributes[patch_index].patch->GetData(0, 1, op);
            _attributes[patch_index].patch->SetData(0, 1, op + point);

            UpdatePatch(patch_index);
            MoveControlPointNeighbours(patch_index,1,1,-point,visited);
            _attributes[patch_index].patch->GetData(1, 1, op);
            _attributes[patch_index].patch->SetData(1, 1, op + 2 * point);
            break;
        case 2:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }

                    _attributes[patch_index].patch->GetData(0, 2, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        _attributes[patch_index].patch->GetData(0, 2, op);
                        _attributes[i].patch->SetData(x,y, op + point);
                    }
                }
            }
            _attributes[patch_index].patch->GetData(0, 2, op);
            _attributes[patch_index].patch->SetData(0, 2, op + point);

            UpdatePatch(patch_index);
            MoveControlPointNeighbours(patch_index,1,2,-point,visited);
            _attributes[patch_index].patch->GetData(1, 2, op);
            _attributes[patch_index].patch->SetData(1, 2, op + 2 * point);
            break;
        case 3:
            visited.push_back(&_attributes[patch_index]);
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    if(i == patch_index) continue;

                    _attributes[patch_index].patch->GetData(0, 3, p0);
                    _attributes[i].patch->GetData(0, 0, p1);
                    if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                        MoveControlPointNeighbours(i,0,0,point,visited);
                    } else {
                        _attributes[i].patch->GetData(0, 3, p1);
                        if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                            MoveControlPointNeighbours(i,0,3,point,visited);
                        } else {
                            _attributes[i].patch->GetData(3, 0, p1);
                            if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                MoveControlPointNeighbours(i,3,0,point,visited);
                            } else {
                                _attributes[i].patch->GetData(3, 3, p1);
                                if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                    MoveControlPointNeighbours(i,3,3,point,visited);
                                }
                            }
                        }
                    }
                }
            }
            _attributes[patch_index].patch->GetData(0, 2, op);
            _attributes[patch_index].patch->SetData(0, 2, op + point);
            _attributes[patch_index].patch->GetData(0, 3, op);
            _attributes[patch_index].patch->SetData(0, 3, op + point);
            _attributes[patch_index].patch->GetData(1, 2, op);
            _attributes[patch_index].patch->SetData(1, 2, op + point);
            _attributes[patch_index].patch->GetData(1, 3, op);
            _attributes[patch_index].patch->SetData(1, 3, op + point);

            UpdatePatch(patch_index);
            break;
        case 4:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    _attributes[patch_index].patch->GetData(1, 0, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        _attributes[patch_index].patch->GetData(1, 0, op);
                        _attributes[i].patch->SetData(x,y, op + point);
                    }
                }
            }
            _attributes[patch_index].patch->GetData(1, 0, op);
            _attributes[patch_index].patch->SetData(1, 0, op + point);

            UpdatePatch(patch_index);
            MoveControlPointNeighbours(patch_index,1,1,-point,visited);
            _attributes[patch_index].patch->GetData(1, 1, op);
            _attributes[patch_index].patch->SetData(1, 1, op + 2 * point);
            break;
        case 7:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    _attributes[patch_index].patch->GetData(1, 3, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        _attributes[patch_index].patch->GetData(1, 3, op);
                        _attributes[i].patch->SetData(x,y, op + point);;
                    }
                }
            }
            _attributes[patch_index].patch->GetData(1, 3, op);
            _attributes[patch_index].patch->SetData(1, 3, op + point);

            UpdatePatch(patch_index);
            MoveControlPointNeighbours(patch_index,1,2,-point,visited);
            _attributes[patch_index].patch->GetData(1, 2, op);
            _attributes[patch_index].patch->SetData(1, 2, op + 2 * point);
            break;
        case 8:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    _attributes[patch_index].patch->GetData(2, 0, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        _attributes[patch_index].patch->GetData(2, 0, op);
                        _attributes[i].patch->SetData(x,y, op + point);;
                    }
                }
            }
            _attributes[patch_index].patch->GetData(2, 0, op);
            _attributes[patch_index].patch->SetData(2, 0, op + point);

            UpdatePatch(patch_index);
            MoveControlPointNeighbours(patch_index,2,1,-point,visited);
            _attributes[patch_index].patch->GetData(2, 1, op);
            _attributes[patch_index].patch->SetData(2, 1, op + 2 * point);
            break;
        case 11:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    _attributes[patch_index].patch->GetData(2, 3, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        _attributes[patch_index].patch->GetData(2, 3, op);
                        _attributes[i].patch->SetData(x,y, op + point);
                    }
                }
            }
            _attributes[patch_index].patch->GetData(2, 3, op);
            _attributes[patch_index].patch->SetData(2, 3, op + point);

            UpdatePatch(patch_index);
            MoveControlPointNeighbours(patch_index,2,2,-point,visited);
            _attributes[patch_index].patch->GetData(2, 2, op);
            _attributes[patch_index].patch->SetData(2, 2, op + 2 * point);
            break;
        case 12:
            visited.push_back(&_attributes[patch_index]);
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    if(i == patch_index) continue;

                    _attributes[patch_index].patch->GetData(3, 0, p0);
                    _attributes[i].patch->GetData(0, 0, p1);
                    if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                        MoveControlPointNeighbours(i,0,0,point,visited);
                    } else {
                        _attributes[i].patch->GetData(0, 3, p1);
                        if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                            MoveControlPointNeighbours(i,0,3,point,visited);
                        } else {
                            _attributes[i].patch->GetData(3, 0, p1);
                            if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                MoveControlPointNeighbours(i,3,0,point,visited);
                            } else {
                                _attributes[i].patch->GetData(3, 3, p1);
                                if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                    MoveControlPointNeighbours(i,3,3,point,visited);
                                }
                            }
                        }
                    }
                }
            }
            _attributes[patch_index].patch->GetData(2, 0, op);
            _attributes[patch_index].patch->SetData(2, 0, op + point);
            _attributes[patch_index].patch->GetData(2, 1, op);
            _attributes[patch_index].patch->SetData(2, 1, op + point);
            _attributes[patch_index].patch->GetData(3, 0, op);
            _attributes[patch_index].patch->SetData(3, 0, op + point);
            _attributes[patch_index].patch->GetData(3, 1, op);
            _attributes[patch_index].patch->SetData(3, 1, op + point);

            UpdatePatch(patch_index);
            break;
        case 13:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    _attributes[patch_index].patch->GetData(3, 1, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        _attributes[patch_index].patch->GetData(3, 1, op);
                        _attributes[i].patch->SetData(x,y, op + point);
                    }
                }
            }
            _attributes[patch_index].patch->GetData(3, 1, op);
            _attributes[patch_index].patch->SetData(3, 1, op + point);

            UpdatePatch(patch_index);
            MoveControlPointNeighbours(patch_index,2,1,-point,visited);
            _attributes[patch_index].patch->GetData(2, 1, op);
            _attributes[patch_index].patch->SetData(2, 1, op + 2 * point);
            break;
        case 14:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    _attributes[patch_index].patch->GetData(3, 2, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        _attributes[patch_index].patch->GetData(3, 2, op);
                        _attributes[i].patch->SetData(x,y, op + point);;
                    }
                }
            }
            _attributes[patch_index].patch->GetData(3, 2, op);
            _attributes[patch_index].patch->SetData(3, 2, op + point);

            UpdatePatch(patch_index);
            MoveControlPointNeighbours(patch_index,2,2,-point,visited);
            _attributes[patch_index].patch->GetData(2, 2, op);
            _attributes[patch_index].patch->SetData(2, 2, op + 2 * point);
            break;
        case 15:
            visited.push_back(&_attributes[patch_index]);
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    if(i == patch_index) continue;

                    _attributes[patch_index].patch->GetData(3, 3, p0);
                    _attributes[i].patch->GetData(0, 0, p1);
                    if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                        MoveControlPointNeighbours(i,0,0,point,visited);
                    } else {
                        _attributes[i].patch->GetData(0, 3, p1);
                        if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                            MoveControlPointNeighbours(i,0,3,point,visited);
                        } else {
                            _attributes[i].patch->GetData(3, 0, p1);
                            if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                MoveControlPointNeighbours(i,3,0,point,visited);
                            } else {
                                _attributes[i].patch->GetData(3, 3, p1);
                                if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                    MoveControlPointNeighbours(i,3,3,point,visited);
                                }
                            }
                        }
                    }
                }
            }
            _attributes[patch_index].patch->GetData(2, 2, op);
            _attributes[patch_index].patch->SetData(2, 2, op + point);
            _attributes[patch_index].patch->GetData(2, 3, op);
            _attributes[patch_index].patch->SetData(2, 3, op + point);
            _attributes[patch_index].patch->GetData(3, 2, op);
            _attributes[patch_index].patch->SetData(3, 2, op + point);
            _attributes[patch_index].patch->GetData(3, 3, op);
            _attributes[patch_index].patch->SetData(3, 3, op + point);

            UpdatePatch(patch_index);
            break;
        }
        UpdatePatch(patch_index);
    } else {

        DCoordinate3 op;
        _attributes[patch_index].patch->GetData(point_i, point_j, op);
        _attributes[patch_index].patch->SetData(point_i, point_j, op + point);

        UpdatePatch(patch_index);

        visited.push_back(&_attributes[patch_index]);
        GLuint sum = 4 * point_i + point_j;
        int i = 0, j = 0, x = 0, y = 0;
        DCoordinate3 p0, p1;
        switch(sum) {
        case 5:
            for(int l = 0; l < 8; l += 2) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; j = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                    _attributes[patch_index].patch->GetData(0, 1, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        if(x == 3) x--;
                        if(x == 0) x++;
                        if(y == 3) y--;
                        if(y == 0) y++;
                        MoveControlPointNeighbours(i, x, y, -point, visited);
                    } else {
                        i = 0; j = 0; x = 0; y = 0;
                        while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                        while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                        _attributes[patch_index].patch->GetData(1, 0, p0);
                        _attributes[i].patch->GetData(x, y, p1);
                        while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                            y++;
                            if(y == 4) {
                                x++;
                                y = 0;
                            }
                            if(x == 4) {
                                break;
                            }
                            _attributes[i].patch->GetData(x, y, p1);
                        }
                        if(x != 4) {
                            if(x == 3) x--;
                            if(x == 0) x++;
                            if(y == 3) y--;
                            if(y == 0) y++;
                            MoveControlPointNeighbours(i, x, y, -point, visited);
                        }
                    }
                }
            }

            if(_attributes[patch_index].neighbours[3] != nullptr) {
                i = 0; j = 0; x = 0; y = 0;
                while(&_attributes[i] != _attributes[patch_index].neighbours[3]) { i++; }
                while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                _attributes[patch_index].patch->GetData(0, 0, p0);
                _attributes[i].patch->GetData(x, y, p1);
                while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                    y++;
                    if(y == 4) {
                        x++;
                        y = 0;
                    }
                    _attributes[i].patch->GetData(x, y, p1);
                }
                if(x == 3) x--;
                if(x == 0) x++;
                if(y == 3) y--;
                if(y == 0) y++;
                MoveControlPointNeighbours(i, x, y, point, visited);
            }
            break;
        case 6:
            for(int l = 0; l < 8; l += 2) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; j = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                    _attributes[patch_index].patch->GetData(0, 2, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        if(x == 3) x--;
                        if(x == 0) x++;
                        if(y == 3) y--;
                        if(y == 0) y++;
                        MoveControlPointNeighbours(i, x, y, -point, visited);
                    } else {
                        i = 0; j = 0; x = 0; y = 0;
                        while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                        while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                        _attributes[patch_index].patch->GetData(1, 3, p0);
                        _attributes[i].patch->GetData(x, y, p1);
                        while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                            y++;
                            if(y == 4) {
                                x++;
                                y = 0;
                            }
                            if(x == 4) {
                                break;
                            }
                            _attributes[i].patch->GetData(x, y, p1);
                        }
                        if(x != 4) {
                            if(x == 3) x--;
                            if(x == 0) x++;
                            if(y == 3) y--;
                            if(y == 0) y++;
                            MoveControlPointNeighbours(i, x, y, -point, visited);
                        }
                    }
                }
            }

            if(_attributes[patch_index].neighbours[1] != nullptr) {
                i = 0; j = 0; x = 0; y = 0;
                while(&_attributes[i] != _attributes[patch_index].neighbours[1]) { i++; }
                while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                _attributes[patch_index].patch->GetData(0, 3, p0);
                _attributes[i].patch->GetData(x, y, p1);
                while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                    y++;
                    if(y == 4) {
                        x++;
                        y = 0;
                    }
                    _attributes[i].patch->GetData(x, y, p1);
                }
                if(x == 3) x--;
                if(x == 0) x++;
                if(y == 3) y--;
                if(y == 0) y++;
                MoveControlPointNeighbours(i, x, y, point, visited);
            }
            break;
        case 9:
            for(int l = 0; l < 8; l += 2) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; j = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                    _attributes[patch_index].patch->GetData(2, 0, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        if(x == 3) x--;
                        if(x == 0) x++;
                        if(y == 3) y--;
                        if(y == 0) y++;
                        MoveControlPointNeighbours(i, x, y, -point, visited);
                    } else {
                        i = 0; j = 0; x = 0; y = 0;
                        while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                        while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                        _attributes[patch_index].patch->GetData(3, 1, p0);
                        _attributes[i].patch->GetData(x, y, p1);
                        while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                            y++;
                            if(y == 4) {
                                x++;
                                y = 0;
                            }
                            if(x == 4) {
                                break;
                            }
                            _attributes[i].patch->GetData(x, y, p1);
                        }
                        if(x != 4) {
                            if(x == 3) x--;
                            if(x == 0) x++;
                            if(y == 3) y--;
                            if(y == 0) y++;
                            MoveControlPointNeighbours(i, x, y, -point, visited);
                        }
                    }
                }
            }

            if(_attributes[patch_index].neighbours[5] != nullptr) {
                i = 0; j = 0; x = 0; y = 0;
                while(&_attributes[i] != _attributes[patch_index].neighbours[5]) { i++; }
                while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                _attributes[patch_index].patch->GetData(3, 0, p0);
                _attributes[i].patch->GetData(x, y, p1);
                while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                    y++;
                    if(y == 4) {
                        x++;
                        y = 0;
                    }
                    _attributes[i].patch->GetData(x, y, p1);
                }
                if(x == 3) x--;
                if(x == 0) x++;
                if(y == 3) y--;
                if(y == 0) y++;
                MoveControlPointNeighbours(i, x, y, point, visited);
            }
            break;
        case 10:
            for(int l = 0; l < 8; l += 2) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; j = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                    _attributes[patch_index].patch->GetData(2, 3, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        if(x == 3) x--;
                        if(x == 0) x++;
                        if(y == 3) y--;
                        if(y == 0) y++;
                        MoveControlPointNeighbours(i, x, y, -point, visited);
                    } else {
                        i = 0; j = 0; x = 0; y = 0;
                        while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                        while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                        _attributes[patch_index].patch->GetData(3, 2, p0);
                        _attributes[i].patch->GetData(x, y, p1);
                        while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                            y++;
                            if(y == 4) {
                                x++;
                                y = 0;
                            }
                            if(x == 4) {
                                break;
                            }
                            _attributes[i].patch->GetData(x, y, p1);
                        }
                        if(x != 4) {
                            if(x == 3) x--;
                            if(x == 0) x++;
                            if(y == 3) y--;
                            if(y == 0) y++;
                            MoveControlPointNeighbours(i, x, y, -point, visited);
                        }
                    }
                }
            }

            if(_attributes[patch_index].neighbours[7] != nullptr) {
                i = 0; j = 0; x = 0; y = 0;
                while(&_attributes[i] != _attributes[patch_index].neighbours[7]) { i++; }
                while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                _attributes[patch_index].patch->GetData(3, 3, p0);
                _attributes[i].patch->GetData(x, y, p1);
                while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                    y++;
                    if(y == 4) {
                        x++;
                        y = 0;
                    }
                    _attributes[i].patch->GetData(x, y, p1);
                }
                if(x == 3) x--;
                if(x == 0) x++;
                if(y == 3) y--;
                if(y == 0) y++;
                MoveControlPointNeighbours(i, x, y, point, visited);
            }
            break;
        }
    }
    return GL_TRUE;
}

GLboolean BiquadraticCompositeSurface3::MoveControlPointNeighbours(GLuint patch_index, int point_i, int point_j, DCoordinate3 point, std::vector<PatchAttributes*> visited) {

    for(GLuint j = 0 ; j < visited.size(); j++)
    {
        if(visited[j] == &_attributes[patch_index])
        {
            return GL_FALSE;
        }
    }
    DCoordinate3 p;
    int s = point_i * 4 + point_j;
    if(s != 0 && s != 3 && s != 12 && s != 15) {
        _attributes[patch_index].patch->GetData(point_i, point_j, p);
        _attributes[patch_index].patch->SetData(point_i, point_j, p + point);
        UpdatePatch(patch_index);
    }

    visited.push_back(&_attributes[patch_index]);

    if(point_i == 0 || point_j == 0 || point_i == 3 || point_j == 3) {
        DCoordinate3 op;
        /*_attributes[patch_index].patch->GetData(point_i, point_j, op);
        _attributes[patch_index].patch->SetData(point_i, point_j, op + point);*/
        int sum = point_i * 4 + point_j;
        int i = 0, x = 0, y = 0;
        DCoordinate3 p0, p1;
        switch(sum) {
        case 0:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    if(i == patch_index) continue;

                    _attributes[patch_index].patch->GetData(0, 0, p0);
                    _attributes[i].patch->GetData(0, 0, p1);
                    if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                        MoveControlPointNeighbours(i,0,0,point,visited);
                    } else {
                        _attributes[i].patch->GetData(0, 3, p1);
                        if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                            MoveControlPointNeighbours(i,0,3,point,visited);
                        } else {
                            _attributes[i].patch->GetData(3, 0, p1);
                            if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                MoveControlPointNeighbours(i,3,0,point,visited);
                            } else {
                                _attributes[i].patch->GetData(3, 3, p1);
                                if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                    MoveControlPointNeighbours(i,3,3,point,visited);
                                }
                            }
                        }
                    }
                }
            }
            _attributes[patch_index].patch->GetData(0, 0, op);
            _attributes[patch_index].patch->SetData(0, 0, op + point);
            _attributes[patch_index].patch->GetData(0, 1, op);
            _attributes[patch_index].patch->SetData(0, 1, op + point);
            _attributes[patch_index].patch->GetData(1, 0, op);
            _attributes[patch_index].patch->SetData(1, 0, op + point);
            _attributes[patch_index].patch->GetData(1, 1, op);
            _attributes[patch_index].patch->SetData(1, 1, op + point);

            UpdatePatch(patch_index);
            break;
        case 3:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    if(i == patch_index) continue;

                    _attributes[patch_index].patch->GetData(0, 3, p0);
                    _attributes[i].patch->GetData(0, 0, p1);
                    if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                        MoveControlPointNeighbours(i,0,0,point,visited);
                    } else {
                        _attributes[i].patch->GetData(0, 3, p1);
                        if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                            MoveControlPointNeighbours(i,0,3,point,visited);
                        } else {
                            _attributes[i].patch->GetData(3, 0, p1);
                            if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                MoveControlPointNeighbours(i,3,0,point,visited);
                            } else {
                                _attributes[i].patch->GetData(3, 3, p1);
                                if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                    MoveControlPointNeighbours(i,3,3,point,visited);
                                }
                            }
                        }
                    }
                }
            }
            _attributes[patch_index].patch->GetData(0, 2, op);
            _attributes[patch_index].patch->SetData(0, 2, op + point);
            _attributes[patch_index].patch->GetData(0, 3, op);
            _attributes[patch_index].patch->SetData(0, 3, op + point);
            _attributes[patch_index].patch->GetData(1, 2, op);
            _attributes[patch_index].patch->SetData(1, 2, op + point);
            _attributes[patch_index].patch->GetData(1, 3, op);
            _attributes[patch_index].patch->SetData(1, 3, op + point);

            UpdatePatch(patch_index);
            break;
        case 12:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    if(i == patch_index) continue;

                    _attributes[patch_index].patch->GetData(3, 0, p0);
                    _attributes[i].patch->GetData(0, 0, p1);
                    if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                        MoveControlPointNeighbours(i,0,0,point,visited);
                    } else {
                        _attributes[i].patch->GetData(0, 3, p1);
                        if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                            MoveControlPointNeighbours(i,0,3,point,visited);
                        } else {
                            _attributes[i].patch->GetData(3, 0, p1);
                            if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                MoveControlPointNeighbours(i,3,0,point,visited);
                            } else {
                                _attributes[i].patch->GetData(3, 3, p1);
                                if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                    MoveControlPointNeighbours(i,3,3,point,visited);
                                }
                            }
                        }
                    }
                }
            }
            _attributes[patch_index].patch->GetData(2, 0, op);
            _attributes[patch_index].patch->SetData(2, 0, op + point);
            _attributes[patch_index].patch->GetData(2, 1, op);
            _attributes[patch_index].patch->SetData(2, 1, op + point);
            _attributes[patch_index].patch->GetData(3, 0, op);
            _attributes[patch_index].patch->SetData(3, 0, op + point);
            _attributes[patch_index].patch->GetData(3, 1, op);
            _attributes[patch_index].patch->SetData(3, 1, op + point);

            UpdatePatch(patch_index);
            break;
        case 15:
            for(int l = 0; l < 8; l++) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    if(i == patch_index) continue;

                    _attributes[patch_index].patch->GetData(3, 3, p0);
                    _attributes[i].patch->GetData(0, 0, p1);
                    if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                        MoveControlPointNeighbours(i,0,0,point,visited);
                    } else {
                        _attributes[i].patch->GetData(0, 3, p1);
                        if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                            MoveControlPointNeighbours(i,0,3,point,visited);
                        } else {
                            _attributes[i].patch->GetData(3, 0, p1);
                            if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                MoveControlPointNeighbours(i,3,0,point,visited);
                            } else {
                                _attributes[i].patch->GetData(3, 3, p1);
                                if(p1.x() == p0.x() && p1.y() == p0.y() && p1.z() == p0.z()) {
                                    MoveControlPointNeighbours(i,3,3,point,visited);
                                }
                            }
                        }
                    }
                }
            }
            _attributes[patch_index].patch->GetData(2, 2, op);
            _attributes[patch_index].patch->SetData(2, 2, op + point);
            _attributes[patch_index].patch->GetData(2, 3, op);
            _attributes[patch_index].patch->SetData(2, 3, op + point);
            _attributes[patch_index].patch->GetData(3, 2, op);
            _attributes[patch_index].patch->SetData(3, 2, op + point);
            _attributes[patch_index].patch->GetData(3, 3, op);
            _attributes[patch_index].patch->SetData(3, 3, op + point);

            UpdatePatch(patch_index);
            break;
        }

        UpdatePatch(patch_index);
    } else {

        GLuint sum = 4 * point_i + point_j;
        int i = 0, j = 0, x = 0, y = 0;
        DCoordinate3 p0, p1;
        switch(sum) {
        case 5:
            for(int l = 0; l < 8; l += 2) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; j = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                    _attributes[patch_index].patch->GetData(0, 1, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        if(x == 3) x--;
                        if(x == 0) x++;
                        if(y == 3) y--;
                        if(y == 0) y++;
                        MoveControlPointNeighbours(i, x, y, -point, visited);
                    } else {
                        i = 0; j = 0; x = 0; y = 0;
                        while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                        while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                        _attributes[patch_index].patch->GetData(1, 0, p0);
                        _attributes[i].patch->GetData(x, y, p1);
                        while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                            y++;
                            if(y == 4) {
                                x++;
                                y = 0;
                            }
                            if(x == 4) {
                                break;
                            }
                            _attributes[i].patch->GetData(x, y, p1);
                        }
                        if(x != 4) {
                            if(x == 3) x--;
                            if(x == 0) x++;
                            if(y == 3) y--;
                            if(y == 0) y++;
                            MoveControlPointNeighbours(i, x, y, -point, visited);
                        }
                    }
                }
            }

            if(_attributes[patch_index].neighbours[3] != nullptr) {
                i = 0; j = 0; x = 0; y = 0;
                while(&_attributes[i] != _attributes[patch_index].neighbours[3]) { i++; }
                while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                _attributes[patch_index].patch->GetData(0, 0, p0);
                _attributes[i].patch->GetData(x, y, p1);
                while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                    y++;
                    if(y == 4) {
                        x++;
                        y = 0;
                    }
                    _attributes[i].patch->GetData(x, y, p1);
                }
                if(x == 3) x--;
                if(x == 0) x++;
                if(y == 3) y--;
                if(y == 0) y++;
                MoveControlPointNeighbours(i, x, y, point, visited);
            }
            break;
        case 6:
            for(int l = 0; l < 8; l += 2) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; j = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                    _attributes[patch_index].patch->GetData(0, 2, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        if(x == 3) x--;
                        if(x == 0) x++;
                        if(y == 3) y--;
                        if(y == 0) y++;
                        MoveControlPointNeighbours(i, x, y, -point, visited);
                    } else {
                        i = 0; j = 0; x = 0; y = 0;
                        while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                        while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                        _attributes[patch_index].patch->GetData(1, 3, p0);
                        _attributes[i].patch->GetData(x, y, p1);
                        while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                            y++;
                            if(y == 4) {
                                x++;
                                y = 0;
                            }
                            if(x == 4) {
                                break;
                            }
                            _attributes[i].patch->GetData(x, y, p1);
                        }
                        if(x != 4) {
                            if(x == 3) x--;
                            if(x == 0) x++;
                            if(y == 3) y--;
                            if(y == 0) y++;
                            MoveControlPointNeighbours(i, x, y, -point, visited);
                        }
                    }
                }
            }

            if(_attributes[patch_index].neighbours[1] != nullptr) {
                i = 0; j = 0; x = 0; y = 0;
                while(&_attributes[i] != _attributes[patch_index].neighbours[1]) { i++; }
                while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                _attributes[patch_index].patch->GetData(0, 3, p0);
                _attributes[i].patch->GetData(x, y, p1);
                while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                    y++;
                    if(y == 4) {
                        x++;
                        y = 0;
                    }
                    _attributes[i].patch->GetData(x, y, p1);
                }
                if(x == 3) x--;
                if(x == 0) x++;
                if(y == 3) y--;
                if(y == 0) y++;
                MoveControlPointNeighbours(i, x, y, point, visited);
            }
            break;
        case 9:
            for(int l = 0; l < 8; l += 2) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; j = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                    _attributes[patch_index].patch->GetData(2, 0, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        if(x == 3) x--;
                        if(x == 0) x++;
                        if(y == 3) y--;
                        if(y == 0) y++;
                        MoveControlPointNeighbours(i, x, y, -point, visited);
                    } else {
                        i = 0; j = 0; x = 0; y = 0;
                        while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                        while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                        _attributes[patch_index].patch->GetData(3, 1, p0);
                        _attributes[i].patch->GetData(x, y, p1);
                        while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                            y++;
                            if(y == 4) {
                                x++;
                                y = 0;
                            }
                            if(x == 4) {
                                break;
                            }
                            _attributes[i].patch->GetData(x, y, p1);
                        }
                        if(x != 4) {
                            if(x == 3) x--;
                            if(x == 0) x++;
                            if(y == 3) y--;
                            if(y == 0) y++;
                            MoveControlPointNeighbours(i, x, y, -point, visited);
                        }
                    }
                }
            }

            if(_attributes[patch_index].neighbours[5] != nullptr) {
                i = 0; j = 0; x = 0; y = 0;
                while(&_attributes[i] != _attributes[patch_index].neighbours[5]) { i++; }
                while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                _attributes[patch_index].patch->GetData(3, 0, p0);
                _attributes[i].patch->GetData(x, y, p1);
                while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                    y++;
                    if(y == 4) {
                        x++;
                        y = 0;
                    }
                    _attributes[i].patch->GetData(x, y, p1);
                }
                if(x == 3) x--;
                if(x == 0) x++;
                if(y == 3) y--;
                if(y == 0) y++;
                MoveControlPointNeighbours(i, x, y, point, visited);
            }
            break;
        case 10:
            for(int l = 0; l < 8; l += 2) {
                if(_attributes[patch_index].neighbours[l] != nullptr) {
                    i = 0; j = 0; x = 0; y = 0;
                    while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                    while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                    _attributes[patch_index].patch->GetData(2, 3, p0);
                    _attributes[i].patch->GetData(x, y, p1);
                    while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                        y++;
                        if(y == 4) {
                            x++;
                            y = 0;
                        }
                        if(x == 4) {
                            break;
                        }
                        _attributes[i].patch->GetData(x, y, p1);
                    }
                    if(x != 4) {
                        if(x == 3) x--;
                        if(x == 0) x++;
                        if(y == 3) y--;
                        if(y == 0) y++;
                        MoveControlPointNeighbours(i, x, y, -point, visited);
                    } else {
                        i = 0; j = 0; x = 0; y = 0;
                        while(&_attributes[i] != _attributes[patch_index].neighbours[l]) { i++; }
                        while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                        _attributes[patch_index].patch->GetData(3, 2, p0);
                        _attributes[i].patch->GetData(x, y, p1);
                        while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                            y++;
                            if(y == 4) {
                                x++;
                                y = 0;
                            }
                            if(x == 4) {
                                break;
                            }
                            _attributes[i].patch->GetData(x, y, p1);
                        }
                        if(x != 4) {
                            if(x == 3) x--;
                            if(x == 0) x++;
                            if(y == 3) y--;
                            if(y == 0) y++;
                            MoveControlPointNeighbours(i, x, y, -point, visited);
                        }
                    }
                }
            }

            if(_attributes[patch_index].neighbours[7] != nullptr) {
                i = 0; j = 0; x = 0; y = 0;
                while(&_attributes[i] != _attributes[patch_index].neighbours[7]) { i++; }
                while(_attributes[i].neighbours[j] != &_attributes[patch_index]) { j++; }
                _attributes[patch_index].patch->GetData(3, 3, p0);
                _attributes[i].patch->GetData(x, y, p1);
                while(p0.x() != p1.x() || p0.y() != p1.y() || p0.z() != p1.z()) {
                    y++;
                    if(y == 4) {
                        x++;
                        y = 0;
                    }
                    _attributes[i].patch->GetData(x, y, p1);
                }
                if(x == 3) x--;
                if(x == 0) x++;
                if(y == 3) y--;
                if(y == 0) y++;
                MoveControlPointNeighbours(i, x, y, point, visited);
            }
            break;
        }
    }
    return GL_TRUE;
}

GLuint BiquadraticCompositeSurface3::ReadSurfaceFromFile(const std::string &file, GLuint index)
{
    loaded_materials.clear();
    fstream f;
    f.open(file, ios::in);
    if(!f.good())
        return GL_FALSE;

    std::string material;

    GLuint no_of_patches;
    f >> no_of_patches;

    Matrix<DCoordinate3> data;
    data.ResizeRows(4);
    data.ResizeColumns(4);
    for(GLuint pno = 0; pno < no_of_patches; pno++)
    {
        GLuint n = _attributes.size();
        _attributes.resize(n + 1);
        _attributes[n].index = index;
        index++;
        f >> material;
        if(material == "Ruby")
        {
            _attributes[n].material = &MatFBRuby;
        }
        else if(material == "Gold")
        {
            _attributes[n].material = &MatFBGold;
        }
        else if(material == "Brass")
        {
            _attributes[n].material = &MatFBBrass;
        }
        else if(material == "Pearl")
        {
            _attributes[n].material = &MatFBPearl;
        }
        else if(material == "Turqoise")
        {
            _attributes[n].material = &MatFBTurquoise;
        }
        else if(material == "Emerald")
        {
            _attributes[n].material = &MatFBEmerald;
        }
        else
            _attributes[n].material = &MatFBSilver;

        loaded_materials.push_back(_attributes[n].material);
        _attributes[n].patch = new (nothrow) BiquadraticPatch3();

        if(!_attributes[n].patch)
        {
            std::cout<<"Patch not created!\n";
            _attributes.pop_back();
            return GL_FALSE;
        }

        GLdouble x,y,z;
        for(GLuint i = 0; i < 4;i++)
        {
            for(GLuint j = 0; j < 4; j++)
            {
                f >> x >> y >> z;
                _attributes[n].patch->SetData(i,j,x,y,z);
            }
        }
        _attributes[n].patch->UpdateVertexBufferObjectsOfData();
        UpdatePatch(n);
    }

    f.close();
    return no_of_patches;

}

GLboolean BiquadraticCompositeSurface3::SaveSurfaceToFile(const std::string &file)
{
    fstream g;
    g.open(file, ios::out);

    DCoordinate3 point;

    g<<_attributes.size()<<endl<<endl;
    for(GLuint i = 0; i < _attributes.size(); i++)
    {
        g<<convertMaterialToText(_attributes[i].material)<<endl;
        for(GLuint j = 0; j < 4 ; j++)
        {

            for(GLuint k = 0; k < 4; k++)
            {
                _attributes[i].patch->GetData(j,k,point);
                g << point<< endl;
            }
            g<<endl;
        }
    }

    return GL_TRUE;
}

std::string BiquadraticCompositeSurface3::convertMaterialToText(Material* m)
{
    if(m == &MatFBGold)
        return "Gold";
    if(m == &MatFBRuby)
        return "Ruby";
    if(m == &MatFBBrass)
        return "Brass";
    if(m == &MatFBPearl)
        return "Pearl";
    if(m == &MatFBSilver)
        return "Silver";
    if(m == &MatFBEmerald)
        return "Emerald";
    if(m == &MatFBTurquoise)
        return "Turqoise";
    return "Ruby";
}




