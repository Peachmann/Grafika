#include "BiquadraticCompostieCurves3.h"
#include <iostream>

using namespace cagd;

BiquadraticCompositeCurve3::BiquadraticCompositeCurve3()
{
    _maxArcNumber = 1000;
    _attributes.reserve(_maxArcNumber);
}

GLboolean BiquadraticCompositeCurve3::SetCurveData(GLuint index, GLuint div_point_count, GLuint max_order_of_derivatives)
{
    //Check for existing arc
    if(index >= _attributes.size() || !_attributes[index].arc)
        return GL_FALSE;

    //Set points

    if(index == 0)
    {
        DCoordinate3 point = *new DCoordinate3(-1.0 , 0.0, 0.0);
        _attributes[index].arc->SetData(0,point);
        point = *new DCoordinate3(-2.0, 2.0, 0.0);
        _attributes[index].arc->SetData(1,point);
        point = *new DCoordinate3(1.0, 1.0, 0.0);
        _attributes[index].arc->SetData(2,point);
        point = *new DCoordinate3(3.0, 0.0, 0.0);
        _attributes[index].arc->SetData(3,point);
    }
    else
    { DCoordinate3 point = *new DCoordinate3(2.0 , 0.0, 0.0);
        _attributes[index].arc->SetData(0,point);
        point = *new DCoordinate3(1.0, 2.0, 0.0);
        _attributes[index].arc->SetData(1,point);
        point = *new DCoordinate3(4.0, 1.0, 0.0);
        _attributes[index].arc->SetData(2,point);
        point = *new DCoordinate3(6.0, 0.0, 0.0);
        _attributes[index].arc->SetData(3,point);
    }


    //UpdateVBO of Data
    _attributes[index].arc->UpdateVertexBufferObjectsOfData();

    //Reset image if exists
    if(_attributes[index].image)
    {
        delete _attributes[index].image;
        _attributes[index].image = nullptr;
    }

    //Generate image
    _attributes[index].image = _attributes[index].arc->GenerateImage(max_order_of_derivatives,div_point_count);

    //Error in generate
    if(!_attributes[index].image)
        return GL_FALSE;

    //Update VBO
    if(!_attributes[index].image->UpdateVertexBufferObjects())
    {
        //If error delete generated arc/image
        delete _attributes[index].arc;
        delete _attributes[index].image;
        _attributes.resize(_attributes.size() - 1);
        return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::InsertNewIsolatedArc(GLuint index, Color4* color)
{

    //Insert new attribute (arc)
      GLint attr_size = _attributes.size();
     _attributes.resize(attr_size + 1);
     _attributes[index].arc = new BiquadraticArcs3();

     //Check if arc was created

    if(!_attributes[attr_size].arc)
    {
        _attributes.pop_back();
        return GL_FALSE;
    }

    //Set Data
    if(!SetCurveData(index))
    {
        _attributes.pop_back();
        return GL_FALSE;
    }

    _attributes[index].color = color;

    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::MergeExistingArcs(const size_t &arc_index1, Direction direction1, const size_t &arc_index2, Direction direction2,
                                                        GLuint max_order_of_derivatives, GLuint div_point_count)
{
    //Check for neighbours
    if(direction1 == LEFT && _attributes[arc_index1].previous)
        return GL_FALSE;
    if(direction1 == RIGHT && _attributes[arc_index1].next)
        return GL_FALSE;

    if(direction2 == LEFT && _attributes[arc_index2].previous)
        return GL_FALSE;
    if(direction2 == RIGHT && _attributes[arc_index2].next)
        return GL_FALSE;

    DCoordinate3 point1,point2;

    if(direction1 == RIGHT && direction2 == LEFT)
    {


        point1 = _attributes[arc_index1].arc->GetData(2);   //2nd to right
        point2 = _attributes[arc_index2].arc->GetData(1);   //2nd to left

        _attributes[arc_index1].arc->SetData(3, (point1 + point2) / 2.0);
        _attributes[arc_index2].arc->SetData(0,(point1 + point2) / 2.0);

    }

    if(direction1 == RIGHT && direction2 == RIGHT)
    {
        point1 = _attributes[arc_index1].arc->GetData(2);   //2nd to right
        point2 = _attributes[arc_index2].arc->GetData(2);   //2nd to right

        _attributes[arc_index1].arc->SetData(3,(point1 + point2) / 2.0);
        _attributes[arc_index2].arc->SetData(3,(point1 + point2) / 2.0);
    }

    if(direction1 == LEFT && direction2 == LEFT)
    {
        point1 = _attributes[arc_index1].arc->GetData(1);   //2nd to right
        point2 = _attributes[arc_index2].arc->GetData(1);   //2nd to right

        _attributes[arc_index1].arc->SetData(0,(point1 + point2) / 2.0);
        _attributes[arc_index2].arc->SetData(0,(point1 + point2) / 2.0);
    }

    if(direction1 == LEFT && direction2 == RIGHT)
    {
        point1 = _attributes[arc_index1].arc->GetData(1);   //2nd to right
        point2 = _attributes[arc_index2].arc->GetData(2);   //2nd to right

        _attributes[arc_index1].arc->SetData(0,(point1 + point2) / 2.0);
        _attributes[arc_index2].arc->SetData(3,(point1 + point2) / 2.0);
    }



    UpdateArc(arc_index1,div_point_count,max_order_of_derivatives);
    UpdateArc(arc_index2,div_point_count,max_order_of_derivatives);

    _attributes[arc_index1].next = &_attributes[arc_index2];
    _attributes[arc_index2].previous = &_attributes[arc_index1];

    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::JoinExistingArcs(const size_t &arc_index1, Direction direction1, const size_t &arc_index2, Direction direction2)
{
    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::ContinueExistingArc(const size_t &arc_index, Direction direction)
{
    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::RenderArcs(GLboolean d1, GLboolean d2, GLboolean polygon)
{
    for(GLuint  i = 0; i < _attributes.size(); i++)
    {
        if(!_attributes[i].image)
        {
            return GL_FALSE;
        }


        if(polygon)
        {
            glColor3f(1.0,1.0,1.0);
            _attributes[i].arc->RenderData(GL_LINE_STRIP);
        }

        glColor3f(_attributes[i].color->r(),_attributes[i].color->g(),_attributes[i].color->b());
        _attributes[i].image->RenderDerivatives(0,GL_LINE_STRIP);
        if(d1)
        {
            glColor3f(0.0,1.0,0.0);
            _attributes[i].image ->RenderDerivatives(1,GL_LINES);
            _attributes[i].image ->RenderDerivatives(1,GL_POINTS);
        }

        if(d2)
        {
            glColor3f(0.0,0.0,1.0);
            _attributes[i].image ->RenderDerivatives(2,GL_LINES);
            _attributes[i].image ->RenderDerivatives(2,GL_POINTS);
        }

        //RENDER 1 1.5 0

    }

    return GL_TRUE;
}

void BiquadraticCompositeCurve3::UpdateArc(GLuint index, GLuint max_order_of_derivatives, GLuint div_point_count)
{
    //UpdateVBO of Data
    _attributes[index].arc->UpdateVertexBufferObjectsOfData();

    //Reset image if exists
    if(_attributes[index].image)
    {
        delete _attributes[index].image;
        _attributes[index].image = nullptr;
    }

    //Generate image
    _attributes[index].image = _attributes[index].arc->GenerateImage(max_order_of_derivatives,div_point_count);


    //Update VBO
    _attributes[index].image->UpdateVertexBufferObjects();


}

