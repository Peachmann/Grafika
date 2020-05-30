#include "BiquadraticCompositeSurfaces3.h";


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

GLboolean BiquadraticCompositeSurface3::ContinueExistingPatch(const size_t &patch_index, Direction direction)
{
    return GL_TRUE;
}

GLboolean BiquadraticCompositeSurface3::JoinExistingPatches(const size_t &patch_index1, Direction direction1, const size_t &patch_index2, Direction direction2)
{
    return GL_TRUE;
}

GLboolean BiquadraticCompositeSurface3::MergeExistingPatches(const size_t &patch_index1, Direction direction1, const size_t &patch_index2, Direction direction2)
{
    return GL_TRUE;
}

GLboolean BiquadraticCompositeSurface3::ShiftPatch(GLuint index, GLdouble off_x, GLdouble off_y, GLdouble off_z)
{
    return GL_TRUE;
}

GLboolean BiquadraticCompositeSurface3::RenderPatches(GLboolean d1, GLboolean u_lines, GLboolean v_lines, GLboolean polygon)
{

    //std::cout<<"Belemegy " << _attributes.size() <<"\n";
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

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

        if(polygon)
        {
            glLineWidth(3.0f);
            glColor3f(1.0,1.0,1.0);
            _attributes[i].patch->RenderData();
             glLineWidth(1.0f);
        }

        if(_attributes[i].mesh)
        {
            _attributes[i].material->Apply();
            _attributes[i].mesh->Render();
        }



        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_NORMALIZE);
    }

    return GL_TRUE;
}

void BiquadraticCompositeSurface3::SetShaderForAll()
{

}

void BiquadraticCompositeSurface3::SetShaderByIndex(GLuint index)
{

}

void BiquadraticCompositeSurface3::SetMaterialForAll()
{

}

void BiquadraticCompositeSurface3::SetMaterialByIndex(GLuint index)
{

}







