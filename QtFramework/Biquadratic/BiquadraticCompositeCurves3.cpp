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
    _attributes[index].index = index;

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
    //Insert new attribute (arc)
    GLint attr_size = _attributes.size();
    _attributes.resize(attr_size + 1);
    _attributes[attr_size].arc = new BiquadraticArcs3();

    //If selected arcs have already neighbours
    if((direction1 == LEFT && _attributes[arc_index1].previous != nullptr) ||
            (direction1 == RIGHT && _attributes[arc_index1].next != nullptr) ||
            (direction2 == LEFT && _attributes[arc_index2].previous != nullptr) ||
            (direction2 == RIGHT && _attributes[arc_index2].next != nullptr)) {
        return GL_FALSE;
    }

    if(!_attributes[attr_size].arc)
    {
        _attributes.pop_back();
        return GL_FALSE;
    }

    DCoordinate3 p0, p1, p2, p3;
    // setting up first 2 points
    switch (direction1) {

    case LEFT:
        p0 = _attributes[arc_index1].arc->GetData(0);
        p1 = _attributes[arc_index1].arc->GetData(1);
        _attributes[arc_index1].previous = &_attributes[attr_size];
        break;
    case RIGHT:
        p0 = _attributes[arc_index1].arc->GetData(3);
        p1 = _attributes[arc_index1].arc->GetData(2);
        _attributes[arc_index1].next = &_attributes[attr_size];
        break;
    default:
        std :: cout << "That should not have happened..." << std :: endl;
        return GL_FALSE;
    }

    // setting up other 2 points
    switch (direction2) {

    case LEFT:
        p3 = _attributes[arc_index2].arc->GetData(0);
        p2 = _attributes[arc_index2].arc->GetData(1);
        _attributes[arc_index2].previous = &_attributes[attr_size];
        break;
    case RIGHT:
        p3 = _attributes[arc_index2].arc->GetData(3);
        p2 = _attributes[arc_index2].arc->GetData(2);
        _attributes[arc_index2].next = &_attributes[attr_size];
        break;
    default:
        std :: cout << "That should not have happened..." << std :: endl;
        return GL_FALSE;
    }

    // setting up the new arc
    _attributes[attr_size].arc->SetData(0,p0);
    _attributes[attr_size].arc->SetData(1,(2.0 *  p0 - p1));
    _attributes[attr_size].arc->SetData(2,(2.0 * p3 - p2));
    _attributes[attr_size].arc->SetData(3,p3);

    _attributes[attr_size].color = new Color4(0.2f,0.7f,0.8f);

    //Reset image if exists
    if(_attributes[attr_size].image)
    {
        delete _attributes[attr_size].image;
        _attributes[attr_size].image = nullptr;
    }

    //Generate image
    _attributes[attr_size].image = _attributes[attr_size].arc->GenerateImage(3,30);

    //Error in generate
    if(!_attributes[attr_size].image)
        return GL_FALSE;

    //Update VBO
    if(!_attributes[attr_size].image->UpdateVertexBufferObjects())
    {
        //If error delete generated arc/image
        delete _attributes[attr_size].arc;
        delete _attributes[attr_size].image;
        _attributes.resize(_attributes.size() - 1);
        return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::ContinueExistingArc(const size_t &arc_index, Direction direction)
{
    std::cout<<__LINE__<<std::endl;
    //Insert new attribute (arc)
    GLint attr_size = _attributes.size();
    _attributes.resize(attr_size + 1);
    _attributes[attr_size].arc = new BiquadraticArcs3();
    std::cout<<__LINE__<<std::endl;
    if((direction == LEFT && _attributes[arc_index].previous != nullptr) || (direction == RIGHT && _attributes[arc_index].next != nullptr)) {
        return GL_FALSE;
    }
    std::cout<<__LINE__<<std::endl;
    if(!_attributes[attr_size].arc)
    {
        _attributes.pop_back();
        return GL_FALSE;
    }

    DCoordinate3 p0, p1;
    // setting up the first 2 points
    std::cout<<__LINE__<<std::endl;
    switch (direction) {

    case LEFT:
        p0 = _attributes[arc_index].arc->GetData(0);
        p1 = _attributes[arc_index].arc->GetData(1);
        _attributes[arc_index].previous = &_attributes[attr_size];
        break;
    case RIGHT:
        p0 = _attributes[arc_index].arc->GetData(3);
        p1 = _attributes[arc_index].arc->GetData(2);
        _attributes[arc_index].next = &_attributes[attr_size];
        break;
    default:
        std :: cout << "That should not have happened..." << std :: endl;
        return GL_FALSE;
    }
    std::cout<<__LINE__<<std::endl;
    // calculating new arc points
    _attributes[attr_size].arc->SetData(0,p0);
    _attributes[attr_size].arc->SetData(1,(2.0 * p0 - p1) );
    _attributes[attr_size].arc->SetData(2,(3.0 * p0 - 2.0 * p1));
    _attributes[attr_size].arc->SetData(3,(4.0 * p0 - 3.0 * p1));
    _attributes[attr_size].color = new Color4(0.2f,0.7f,0.8f);

    _attributes[attr_size].arc->UpdateVertexBufferObjectsOfData();

    //Reset image if exists
    if(_attributes[attr_size].image)
    {
        delete _attributes[attr_size].image;
        _attributes[attr_size].image = nullptr;
    }

    //Generate image
    _attributes[attr_size].image = _attributes[attr_size].arc->GenerateImage(3,30);

    //Error in generate
    if(!_attributes[attr_size].image)
        return GL_FALSE;

    //Update VBO
    if(!_attributes[attr_size].image->UpdateVertexBufferObjects())
    {
        //If error delete generated arc/image
        delete _attributes[attr_size].arc;
        delete _attributes[attr_size].image;
        _attributes.resize(_attributes.size() - 1);
        return GL_FALSE;
    }

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
    std::cout<<__LINE__<<std::endl;
    //Generate image
    _attributes[index].image = _attributes[index].arc->GenerateImage(max_order_of_derivatives,div_point_count);

    //Update VBO
    _attributes[index].image->UpdateVertexBufferObjects();
}


GLboolean BiquadraticCompositeCurve3::moveOnAxisX(const size_t &arc_index, GLdouble offset) {

    ArcAttributes* first = &_attributes[arc_index];
    std:: cout<< &first << " " << &_attributes[arc_index] << std::endl;
    // set the chosen arc
    for(GLint i = 0; i < 4; i++) {
        GLdouble x = _attributes[arc_index].arc->GetData(i).x();
        first->arc->SetData(i, DCoordinate3(x + offset, first->arc->GetData(i).y(), first->arc->GetData(i).z()));
    }
    UpdateArc_2(*first,30,3);

    ArcAttributes *next;
    next = first->previous;

    while(next != nullptr) {
        if(next->arc == first->arc) {
            break;
        }
        for(GLint i = 0; i < 4; i++) {
            GLdouble x = next->arc->GetData(i).x();
            next->arc->SetData(i, DCoordinate3(x + offset, next->arc->GetData(i).y(), next->arc->GetData(i).z()));
        }

        UpdateArc_2(*next,30,3);
        next = next->previous;
    }

    if(next == nullptr) {
        next = first->next;
        while(next != nullptr) {
            for(GLint i = 0; i < 4; i++) {
                GLdouble x = next->arc->GetData(i).x();
                next->arc->SetData(i, DCoordinate3(x + offset, next->arc->GetData(i).y(), next->arc->GetData(i).z()));
            }
            UpdateArc_2(*next,30,3);
            next = next->next;
        }
    }
    return GL_TRUE;
}


GLboolean BiquadraticCompositeCurve3::ShiftArc(const size_t &arc_index, GLdouble off_x, GLdouble off_y, GLdouble off_z)
{
    GLdouble curr_x,curr_y,curr_z;


    for(GLuint i = 0 ; i < 4; i++)
    {
        curr_x = _attributes[arc_index].arc->GetData(i).x();
        curr_y = _attributes[arc_index].arc->GetData(i).y();
        curr_z = _attributes[arc_index].arc->GetData(i).z();

        curr_x += off_x;
        curr_z += off_z;
        curr_y += off_y;

        _attributes[arc_index].arc->SetData(i,DCoordinate3(curr_x,curr_y,curr_z));
    }
    /*
    //UpdateVBO of Data
    _attributes[arc_index].arc->UpdateVertexBufferObjectsOfData();

    //Reset image if exists
    if(_attributes[arc_index].image)
    {
        delete _attributes[arc_index].image;
        _attributes[arc_index].image = nullptr;
    }

    //Generate image
    _attributes[arc_index].image = _attributes[arc_index].arc->GenerateImage(3,30);

    //Error in generate
    if(!_attributes[arc_index].image)
        return GL_FALSE;

    //Update VBO
    if(!_attributes[arc_index].image->UpdateVertexBufferObjects())
    {
        //If error delete generated arc/image
        delete _attributes[arc_index].arc;
        delete _attributes[arc_index].image;
        _attributes.resize(_attributes.size() - 1);
        return GL_FALSE;
    }
    */

    UpdateArc_2(arc_index,30,3);
    if(_attributes[arc_index].next)
    {
        ShiftArc(*_attributes[arc_index].next,off_x,off_y,off_z,&_attributes[arc_index]);
    }

    if(_attributes[arc_index].previous)
    {
        ShiftArc(*_attributes[arc_index].previous,off_x,off_y,off_z,&_attributes[arc_index]);
    }

    return GL_TRUE;
}



GLboolean BiquadraticCompositeCurve3::ShiftArc(ArcAttributes &arc_att, GLdouble off_x, GLdouble off_y, GLdouble off_z,ArcAttributes *first)
{
    GLdouble curr_x,curr_y,curr_z;

    for(GLuint i = 0 ; i < 4; i++)
    {
        curr_x = arc_att.arc->GetData(i).x();
        curr_y = arc_att.arc->GetData(i).y();
        curr_z = arc_att.arc->GetData(i).z();

        curr_x += off_x;
        curr_z += off_z;
        curr_y += off_y;

        arc_att.arc->SetData(i,DCoordinate3(curr_x,curr_y,curr_z));

        UpdateArc_2(arc_att,30,3);
        if(arc_att.next && arc_att.next != first)
        {
            ShiftArc(*arc_att.next,off_x,off_y,off_z,first);
        }

        if(arc_att.previous != first)
        {
            ShiftArc(*arc_att.previous,off_x,off_y,off_z,first);
        }

        return GL_TRUE;
    }
}

GLboolean BiquadraticCompositeCurve3::UpdateArc_2(GLuint arc_index, GLuint div_point_count, GLuint max_order_of_derivatives)
{
    //UpdateVBO of Data
    _attributes[arc_index].arc->UpdateVertexBufferObjectsOfData();

    //Reset image if exists
    if(_attributes[arc_index].image)
    {
        delete _attributes[arc_index].image;
        _attributes[arc_index].image = nullptr;
    }

    //Generate image
    _attributes[arc_index].image = _attributes[arc_index].arc->GenerateImage(max_order_of_derivatives,div_point_count);

    //Error in generate
    if(!_attributes[arc_index].image)
        return GL_FALSE;

    //Update VBO
    if(!_attributes[arc_index].image->UpdateVertexBufferObjects())
    {
        //If error delete generated arc/image
        delete _attributes[arc_index].arc;
        delete _attributes[arc_index].image;
        _attributes.resize(_attributes.size() - 1);
        return GL_FALSE;
    }
    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::UpdateArc_2(ArcAttributes &arc_att, GLuint div_point_count, GLuint max_order_of_derivatives)
{
    //UpdateVBO of Data
    arc_att.arc->UpdateVertexBufferObjectsOfData();

    //Reset image if exists
    if(arc_att.image)
    {
        delete arc_att.image;
        arc_att.image = nullptr;
    }

    //Generate image
    arc_att.image = arc_att.arc->GenerateImage(max_order_of_derivatives,div_point_count);

    //Error in generate
    if(!arc_att.image)
        return GL_FALSE;

    //Update VBO
    if(!arc_att.image->UpdateVertexBufferObjects())
    {
        //If error delete generated arc/image
        delete arc_att.arc;
        delete arc_att.image;
        _attributes.resize(_attributes.size() - 1);
        return GL_FALSE;
    }
    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::moveOnAxisY(const size_t &arc_index, GLdouble offset) {

    ArcAttributes first = _attributes[arc_index];
    DCoordinate3 off = *new DCoordinate3(0.0, offset, 0.0);
    // set the chosen arc
    for(GLint i = 0; i < 4; i++) {
        first.arc->SetData(i, first.arc->GetData(i) + off);
    }

    first.arc->UpdateVertexBufferObjectsOfData();

    //Reset image if exists
    if(first.image)
    {
        delete first.image;
        first.image = nullptr;
    }

    //Generate image
    first.image = first.arc->GenerateImage(3,30);

    //Error in generate
    if(!first.image)
        return GL_FALSE;

    //Update VBO
    if(!first.image->UpdateVertexBufferObjects())
    {
        //If error delete generated arc/image
        delete first.arc;
        delete first.image;
        _attributes.resize(_attributes.size() - 1);
        return GL_FALSE;
    }

    first = *first.previous;

    while(first.arc != nullptr && first.arc != _attributes[arc_index].arc) {
        for(GLint i = 0; i < 4; i++) {
            first.arc->SetData(i, first.arc->GetData(i) + off);
        }
        first.arc->UpdateVertexBufferObjectsOfData();

        //Reset image if exists
        if(first.image)
        {
            delete first.image;
            first.image = nullptr;
        }

        //Generate image
        first.image = first.arc->GenerateImage(3,30);

        //Error in generate
        if(!first.image)
            return GL_FALSE;

        //Update VBO
        if(!first.image->UpdateVertexBufferObjects())
        {
            //If error delete generated arc/image
            delete first.arc;
            delete first.image;
            _attributes.resize(_attributes.size() - 1);
            return GL_FALSE;
        }
        first = *first.previous;
    }

    if(first.arc == nullptr) {
        first = *_attributes[arc_index].next;
        while(first.arc != nullptr) {
            for(GLint i = 0; i < 4; i++) {
                first.arc->SetData(i, first.arc->GetData(i) + off);
            }
            first.arc->UpdateVertexBufferObjectsOfData();

            //Reset image if exists
            if(first.image)
            {
                delete first.image;
                first.image = nullptr;
            }

            //Generate image
            first.image = first.arc->GenerateImage(3,30);

            //Error in generate
            if(!first.image)
                return GL_FALSE;

            //Update VBO
            if(!first.image->UpdateVertexBufferObjects())
            {
                //If error delete generated arc/image
                delete first.arc;
                delete first.image;
                _attributes.resize(_attributes.size() - 1);
                return GL_FALSE;
            }
            first = *first.next;
        }
    }

    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::moveOnAxisZ(const size_t &arc_index, GLdouble offset) {

    ArcAttributes first = _attributes[arc_index];
    DCoordinate3 off = *new DCoordinate3(0.0, 0.0, offset);
    // set the chosen arc
    for(GLint i = 0; i < 4; i++) {
        first.arc->SetData(i, first.arc->GetData(i) + off);
    }

    first.arc->UpdateVertexBufferObjectsOfData();

    //Reset image if exists
    if(first.image)
    {
        delete first.image;
        first.image = nullptr;
    }

    //Generate image
    first.image = first.arc->GenerateImage(3,30);

    //Error in generate
    if(!first.image)
        return GL_FALSE;

    //Update VBO
    if(!first.image->UpdateVertexBufferObjects())
    {
        //If error delete generated arc/image
        delete first.arc;
        delete first.image;
        _attributes.resize(_attributes.size() - 1);
        return GL_FALSE;
    }

    first = *first.previous;

    while(first.arc != nullptr && first.arc != _attributes[arc_index].arc) {
        for(GLint i = 0; i < 4; i++) {
            first.arc->SetData(i, first.arc->GetData(i) + off);
        }
        first.arc->UpdateVertexBufferObjectsOfData();

        //Reset image if exists
        if(first.image)
        {
            delete first.image;
            first.image = nullptr;
        }

        //Generate image
        first.image = first.arc->GenerateImage(3,30);

        //Error in generate
        if(!first.image)
            return GL_FALSE;

        //Update VBO
        if(!first.image->UpdateVertexBufferObjects())
        {
            //If error delete generated arc/image
            delete first.arc;
            delete first.image;
            _attributes.resize(_attributes.size() - 1);
            return GL_FALSE;
        }
        first = *first.previous;
    }

    if(first.arc == nullptr) {
        first = *_attributes[arc_index].next;
        while(first.arc != nullptr) {
            for(GLint i = 0; i < 4; i++) {
                first.arc->SetData(i, first.arc->GetData(i) + off);
            }
            first.arc->UpdateVertexBufferObjectsOfData();

            //Reset image if exists
            if(first.image)
            {
                delete first.image;
                first.image = nullptr;
            }

            //Generate image
            first.image = first.arc->GenerateImage(3,30);

            //Error in generate
            if(!first.image)
                return GL_FALSE;

            //Update VBO
            if(!first.image->UpdateVertexBufferObjects())
            {
                //If error delete generated arc/image
                delete first.arc;
                delete first.image;
                _attributes.resize(_attributes.size() - 1);
                return GL_FALSE;
            }
            first = *first.next;
        }
    }

    return GL_TRUE;
}

std::vector<BiquadraticCompositeCurve3::ArcAttributes> BiquadraticCompositeCurve3::get_attributes()
{
    return _attributes;
}
