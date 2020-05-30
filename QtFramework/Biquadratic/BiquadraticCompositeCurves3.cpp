#include "BiquadraticCompostieCurves3.h"
#include <iostream>
#include <qmessagebox.h>

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

        _attributes[arc_index1].next = &_attributes[arc_index2];
        _attributes[arc_index2].previous = &_attributes[arc_index1];

    }

    if(direction1 == RIGHT && direction2 == RIGHT)
    {
        point1 = _attributes[arc_index1].arc->GetData(2);   //2nd to right
        point2 = _attributes[arc_index2].arc->GetData(2);   //2nd to right

        _attributes[arc_index1].arc->SetData(3,(point1 + point2) / 2.0);
        _attributes[arc_index2].arc->SetData(3,(point1 + point2) / 2.0);

        _attributes[arc_index1].next = &_attributes[arc_index2];
        _attributes[arc_index2].next = &_attributes[arc_index1];
    }

    if(direction1 == LEFT && direction2 == LEFT)
    {
        point1 = _attributes[arc_index1].arc->GetData(1);   //2nd to right
        point2 = _attributes[arc_index2].arc->GetData(1);   //2nd to right

        _attributes[arc_index1].arc->SetData(0,(point1 + point2) / 2.0);
        _attributes[arc_index2].arc->SetData(0,(point1 + point2) / 2.0);

        _attributes[arc_index1].previous = &_attributes[arc_index2];
        _attributes[arc_index2].previous = &_attributes[arc_index1];
    }

    if(direction1 == LEFT && direction2 == RIGHT)
    {
        point1 = _attributes[arc_index1].arc->GetData(1);   //2nd to right
        point2 = _attributes[arc_index2].arc->GetData(2);   //2nd to right

        _attributes[arc_index1].arc->SetData(0,(point1 + point2) / 2.0);
        _attributes[arc_index2].arc->SetData(3,(point1 + point2) / 2.0);

        _attributes[arc_index1].previous = &_attributes[arc_index2];
        _attributes[arc_index2].next = &_attributes[arc_index1];
    }



    UpdateArc(arc_index1,div_point_count,max_order_of_derivatives);
    UpdateArc(arc_index2,div_point_count,max_order_of_derivatives);



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

    _attributes[attr_size].previous = &_attributes[arc_index2];
    _attributes[attr_size].next = &_attributes[arc_index1];

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

GLboolean BiquadraticCompositeCurve3::ContinueExistingArc(const size_t &arc_index, Direction direction)
{
    //Insert new attribute (arc)
    GLint attr_size = _attributes.size();
    _attributes.resize(attr_size + 1);
    _attributes[attr_size].arc = new BiquadraticArcs3();
    if((direction == LEFT && _attributes[arc_index].previous != nullptr) || (direction == RIGHT && _attributes[arc_index].next != nullptr)) {
        return GL_FALSE;
    }
    if(!_attributes[attr_size].arc)
    {
        _attributes.pop_back();
        return GL_FALSE;
    }

    DCoordinate3 p0, p1;
    // setting up the first 2 points
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
    //Generate image
    _attributes[index].image = _attributes[index].arc->GenerateImage(max_order_of_derivatives,div_point_count);

    //Update VBO
    _attributes[index].image->UpdateVertexBufferObjects();
}


GLboolean BiquadraticCompositeCurve3::moveOnAxisX(const size_t &arc_index, GLdouble offset) {

    ArcAttributes* first = &_attributes[arc_index];
    // set the chosen arc
    //std::cout<<"Shifting color: "<<_attributes[arc_index].color<<std::endl;


    for(GLint i = 0; i < 4; i++) {
        GLdouble x = _attributes[arc_index].arc->GetData(i).x();
        first->arc->SetData(i, DCoordinate3(x + offset, first->arc->GetData(i).y(), first->arc->GetData(i).z()));
    }
    UpdateArc_2(*first,30,3);
    std::cout<< first->index << std::endl;

    ArcAttributes *next;
    next = first->previous;

    while(next != nullptr) {
        std::cout<< next->index << std::endl;
        if(next == first) {
            break;
        }
        for(GLint i = 0; i < 4; i++) {
            GLdouble x = next->arc->GetData(i).x();
            next->arc->SetData(i, DCoordinate3(x + offset, next->arc->GetData(i).y(), next->arc->GetData(i).z()));
        }
        std::cout<<"Shifting color: "<<next->color<<std::endl;
        UpdateArc_2(*next,30,3);
        QMessageBox MsgBox;
        MsgBox.setText("2nd in next");
        MsgBox.exec();
        next = next->next;
    }

    if(next == nullptr) {
        next = first->next;
        while(next != nullptr) {
            std::cout<< next->index << std::endl;
            for(GLint i = 0; i < 4; i++) {
                GLdouble x = next->arc->GetData(i).x();
                next->arc->SetData(i, DCoordinate3(x + offset, next->arc->GetData(i).y(), next->arc->GetData(i).z()));
            }
            std::cout<<"Shifting color: "<<next->color<<std::endl;
            UpdateArc_2(*next,30,3);
            QMessageBox MsgBox;
            MsgBox.setText("3rd shift in prev irany");
            MsgBox.exec();
            next = next->next;
        }
    }
    return GL_TRUE;
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

    ArcAttributes* first = &_attributes[arc_index];
    // set the chosen arc
    for(GLint i = 0; i < 4; i++) {
        GLdouble y = _attributes[arc_index].arc->GetData(i).y();
        first->arc->SetData(i, DCoordinate3(first->arc->GetData(i).x(), y + offset, first->arc->GetData(i).z()));
    }
    UpdateArc_2(*first,30,3);
    std::cout<< first->index << std::endl;

    ArcAttributes *next;
    next = first->previous;

    while(next != nullptr) {
        std::cout<< next->index << std::endl;
        if(next == first) {
            break;
        }
        for(GLint i = 0; i < 4; i++) {
            GLdouble y = next->arc->GetData(i).y();
            next->arc->SetData(i, DCoordinate3(next->arc->GetData(i).x(), y + offset, next->arc->GetData(i).z()));
        }

        UpdateArc_2(*next,30,3);
        next = next->previous;
    }

    if(next == nullptr) {
        next = first->next;
        while(next != nullptr) {
            std::cout<< next->index << std::endl;
            for(GLint i = 0; i < 4; i++) {
                GLdouble y = next->arc->GetData(i).y();
                next->arc->SetData(i, DCoordinate3(next->arc->GetData(i).x(), y + offset, next->arc->GetData(i).z()));
            }
            UpdateArc_2(*next,30,3);
            next = next->next;
        }
    }
    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::moveOnAxisZ(const size_t &arc_index, GLdouble offset) {

    ArcAttributes* first = &_attributes[arc_index];
    // set the chosen arc
    for(GLint i = 0; i < 4; i++) {
        GLdouble z = _attributes[arc_index].arc->GetData(i).z();
        first->arc->SetData(i, DCoordinate3(first->arc->GetData(i).x(), first->arc->GetData(i).y(), z + offset));
    }
    UpdateArc_2(*first,30,3);
    std::cout<< first->index << std::endl;

    ArcAttributes *next;
    next = first->previous;

    while(next != nullptr) {
        std::cout<< next->index << std::endl;
        if(next == first) {
            break;
        }
        for(GLint i = 0; i < 4; i++) {
            GLdouble z = next->arc->GetData(i).z();
            next->arc->SetData(i, DCoordinate3(next->arc->GetData(i).x(), next->arc->GetData(i).y(), z + offset));
        }

        UpdateArc_2(*next,30,3);
        next = next->previous;
    }

    if(next == nullptr) {
        next = first->next;
        while(next != nullptr) {
            std::cout<< next->index << std::endl;
            for(GLint i = 0; i < 4; i++) {
                GLdouble z = next->arc->GetData(i).z();
                next->arc->SetData(i, DCoordinate3(next->arc->GetData(i).x(), next->arc->GetData(i).y(), z + offset));
            }
            UpdateArc_2(*next,30,3);
            next = next->next;
        }
    }
    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::moveOnAllAxis(const size_t &arc_index, GLdouble offx, GLdouble offy, GLdouble offz) {

    ArcAttributes* first = &_attributes[arc_index];
    // set the chosen arc
    for(GLint i = 0; i < 4; i++) {
        GLdouble x = _attributes[arc_index].arc->GetData(i).x();
        GLdouble y = _attributes[arc_index].arc->GetData(i).y();
        GLdouble z = _attributes[arc_index].arc->GetData(i).z();
        first->arc->SetData(i, DCoordinate3(x + offx, y + offy, z + offz));
    }
    UpdateArc_2(*first,30,3);
    std::cout<< first->index << std::endl;

    ArcAttributes *next;
    next = first->previous;

    while(next != nullptr) {
        std::cout<< next->index << std::endl;
        if(next == first) {
            break;
        }
        for(GLint i = 0; i < 4; i++) {
            GLdouble x = next->arc->GetData(i).x();
            GLdouble y = next->arc->GetData(i).y();
            GLdouble z = next->arc->GetData(i).z();
            next->arc->SetData(i, DCoordinate3(x + offx, y + offy, z + offz));
        }

        UpdateArc_2(*next,30,3);
        next = next->previous;
    }

    if(next == nullptr) {
        next = first->next;
        while(next != nullptr) {
            std::cout<< next->index << std::endl;
            for(GLint i = 0; i < 4; i++) {
                GLdouble x = next->arc->GetData(i).x();
                GLdouble y = next->arc->GetData(i).y();
                GLdouble z = next->arc->GetData(i).z();
                next->arc->SetData(i, DCoordinate3(x + offx, y + offy, z + offz));
            }
            UpdateArc_2(*next,30,3);
            next = next->next;
        }
    }
    return GL_TRUE;
}


std::vector<BiquadraticCompositeCurve3::ArcAttributes> BiquadraticCompositeCurve3::get_attributes()
{
    return _attributes;
}

GLboolean BiquadraticCompositeCurve3::moveControlPointX(const size_t &arc_index, const size_t &point_index, GLdouble offset) {

    ArcAttributes* first = &_attributes[arc_index];
    // set the chosen arc
    GLdouble x = _attributes[arc_index].arc->GetData(point_index).x();
    first->arc->SetData(point_index, DCoordinate3(x + offset, first->arc->GetData(point_index).y(), first->arc->GetData(point_index).z()));

    UpdateArc_2(*first,30,3);

    if(point_index < 2) {
        ArcAttributes *next;
        next = first->previous;

        if(next != nullptr) {
            next->arc->SetData(3, DCoordinate3(first->arc->GetData(0)));
            next->arc->SetData(2, 2.0 * first->arc->GetData(0) - first->arc->GetData(1));
            UpdateArc_2(*next,30,3);
        }

    } else {
        ArcAttributes *next;
        next = first->next;

        if(next != nullptr) {
            next->arc->SetData(0, DCoordinate3(first->arc->GetData(3)));
            next->arc->SetData(1, 2.0 * first->arc->GetData(3) - first->arc->GetData(2));
            UpdateArc_2(*next,30,3);
        }
    }

    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::moveControlPointY(const size_t &arc_index, const size_t &point_index, GLdouble offset) {
    ArcAttributes* first = &_attributes[arc_index];
    // set the chosen arc
    GLdouble y = _attributes[arc_index].arc->GetData(point_index).y();
    first->arc->SetData(point_index, DCoordinate3(first->arc->GetData(point_index).x(), y + offset, first->arc->GetData(point_index).z()));

    UpdateArc_2(*first,30,3);

    if(point_index < 2) {
        ArcAttributes *next;
        next = first->previous;

        if(next != nullptr) {
            next->arc->SetData(3, DCoordinate3(first->arc->GetData(0)));
            next->arc->SetData(2, 2.0 * first->arc->GetData(0) - first->arc->GetData(1));
            UpdateArc_2(*next,30,3);
        }

    } else {
        ArcAttributes *next;
        next = first->next;

        if(next != nullptr) {
            next->arc->SetData(0, DCoordinate3(first->arc->GetData(3)));
            next->arc->SetData(1, 2.0 * first->arc->GetData(3) - first->arc->GetData(2));
            UpdateArc_2(*next,30,3);
        }
    }

    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::moveControlPointZ(const size_t &arc_index, const size_t &point_index, GLdouble offset) {

    ArcAttributes* first = &_attributes[arc_index];
    // set the chosen arc
    GLdouble z = _attributes[arc_index].arc->GetData(point_index).z();
    first->arc->SetData(point_index, DCoordinate3(first->arc->GetData(point_index).x(), first->arc->GetData(point_index).y(), z + offset));

    UpdateArc_2(*first,30,3);

    if(point_index < 2) {
        ArcAttributes *next;
        next = first->previous;

        if(next != nullptr) {
            next->arc->SetData(3, DCoordinate3(first->arc->GetData(0)));
            next->arc->SetData(2, 2.0 * first->arc->GetData(0) - first->arc->GetData(1));
            UpdateArc_2(*next,30,3);
        }

    } else {
        ArcAttributes *next;
        next = first->next;

        if(next != nullptr) {
            next->arc->SetData(0, DCoordinate3(first->arc->GetData(3)));
            next->arc->SetData(1, 2.0 * first->arc->GetData(3) - first->arc->GetData(2));
            UpdateArc_2(*next,30,3);
        }
    }

    return GL_TRUE;
}

GLboolean BiquadraticCompositeCurve3::moveControlPointAll(const size_t &arc_index, const size_t &point_index, GLdouble offx, GLdouble offy, GLdouble offz) {

    ArcAttributes* first = &_attributes[arc_index];
    // set the chosen arc
    first->arc->SetData(point_index, DCoordinate3(first->arc->GetData(point_index).x() + offx, first->arc->GetData(point_index).y() + offy, first->arc->GetData(point_index).z() + offz));

    UpdateArc_2(*first,30,3);

    if(point_index < 2) {
        ArcAttributes *next;
        next = first->previous;

        if(next != nullptr) {
            next->arc->SetData(3, DCoordinate3(first->arc->GetData(0)));
            next->arc->SetData(2, 2.0 * first->arc->GetData(0) - first->arc->GetData(1));
            UpdateArc_2(*next,30,3);
        }

    } else {
        ArcAttributes *next;
        next = first->next;

        if(next != nullptr) {
            next->arc->SetData(0, DCoordinate3(first->arc->GetData(3)));
            next->arc->SetData(1, 2.0 * first->arc->GetData(3) - first->arc->GetData(2));
            UpdateArc_2(*next,30,3);
        }
    }

    return GL_TRUE;
}
