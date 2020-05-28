#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}

//Torus Knot


GLdouble torus_knot::u_min = 0;
GLdouble torus_knot::u_max = SIX_PI;

DCoordinate3 torus_knot::d0(GLdouble u)
{
    return DCoordinate3((2.0 + cos(2*u/3)) * cos(u),(2.0 + cos(2*u/3)) * sin(u),sin(2*u/3));
}

DCoordinate3 torus_knot::d1(GLdouble u)
{
    return DCoordinate3((-2.0 - cos(2.0*u/3.0))*sin(u) - 2.0/3.0 * sin(2.0*u/3.0)*cos(u),
                        (2.0+cos(2.0*u/3.0))*cos(u) - 2.0/3.0*sin(2.0*u/3.0)*sin(u)
                        ,2.0/3.0 * cos(2.0*u/3.0));

}

DCoordinate3 torus_knot::d2(GLdouble u)
{
    return DCoordinate3((12.0*sin(2.0*u/3.0)*sin(u) + (-13.0* cos(2.0*u/3.0) - 18)*cos(u))/9.0,
                        -(((13.0*cos(2.0*u/3.0)+18)*sin(u) + 12.0 * sin(2.0*u/3.0) * cos(u))/9.0)
                        ,-(4.0/9.0 * sin(2.0*u/3.0)));
}

//Helix

GLdouble helix::u_min = -TWO_PI;
GLdouble helix::u_max = TWO_PI;

DCoordinate3 helix::d0(GLdouble u)
{
    return DCoordinate3(TWO_PI*cos(u),TWO_PI*sin(u),u);
}

DCoordinate3 helix::d1(GLdouble u)
{
    return DCoordinate3((-TWO_PI)*sin(u),TWO_PI*cos(u),1.0);
}

DCoordinate3 helix::d2(GLdouble u)
{
    return DCoordinate3((-TWO_PI)*cos(u),(-TWO_PI)*sin(u),0.0);
}

//Elipse

GLdouble ellipse::u_min = -10.0;
GLdouble ellipse::u_max = 10.0;

DCoordinate3 ellipse::d0(GLdouble u)
{
    return DCoordinate3(3.0*cos(u),4.0*sin(u),u*2);
}

DCoordinate3 ellipse::d1(GLdouble u)
{
    return DCoordinate3((-3.0)*sin(u),4.0*cos(u),2.0);
}

DCoordinate3 ellipse::d2(GLdouble u)
{
    return DCoordinate3((-3.0)*cos(u),(-4.0)*sin(u),0.0);
}

//Hypocloid

GLdouble hypocloid::u_min = -TWO_PI;
GLdouble hypocloid::u_max = TWO_PI;

DCoordinate3 hypocloid::d0(GLdouble u)
{
    return DCoordinate3(3.0*cos(u) + cos(3.0*u),3.0*sin(u) - sin(3.0*u),1);
}

DCoordinate3 hypocloid::d1(GLdouble u)
{
    return DCoordinate3((-3.0)*sin(3.0*u) - 3.0*sin(u),(-3.0)*(cos(3.0*u)-cos(u)),0.0);
}

DCoordinate3 hypocloid::d2(GLdouble u)
{
    return DCoordinate3((-3.0)*(3.0*cos(3.0*u) + cos(u)),9.0*sin(3.0*u) - 3.0*sin(u),0.0);
}

//Epicycloid

GLdouble epicycloid::u_min = -TWO_PI;
GLdouble epicycloid::u_max = TWO_PI;

DCoordinate3 epicycloid::d0(GLdouble u)
{
    return DCoordinate3(2.0*cos(u) - cos(2.0*u),2.0*sin(u) - sin(2.0*u),u);
}

DCoordinate3 epicycloid::d1(GLdouble u)
{
    return DCoordinate3(2.0*(sin(2.0*u) - sin(u)),(-2.0)*(cos(2.0*u) - cos(u)),1.0);
}

DCoordinate3 epicycloid::d2(GLdouble u)
{
    return DCoordinate3(2.0*(2.0*cos(2.0*u) - cos(u)),4.0*sin(2.0*u) - 2.0*sin(u),0.0);
}

//Rose Curves

GLdouble rose::u_min = -TWO_PI;
GLdouble rose::u_max = TWO_PI;

DCoordinate3 rose::d0(GLdouble u)
{
    return DCoordinate3(cos(2.0*u) * cos(u),cos(2.0*u) * sin(u),u);
}

DCoordinate3 rose::d1(GLdouble u)
{
    return DCoordinate3((-2)*cos(u)*sin(2.0*u) - sin(u)*cos(2.0*u),
                        cos(u)*cos(2.0*u) - 2.0*sin(u)*sin(2.0*u),1.0);
}

DCoordinate3 rose::d2(GLdouble u)
{
    return DCoordinate3(4.0*sin(u)*sin(2.0*u) -5.0*cos(u)*cos(2.0*u),
                        (-4.0)*cos(u)*sin(2.0*u) - 5.0*sin(u)*cos(2.0*u),0.0);
}

//Torus Surface
GLdouble torus_knot_surface::u_min = 0;
GLdouble torus_knot_surface::u_max = TWO_PI;
GLdouble torus_knot_surface::v_min = 0;
GLdouble torus_knot_surface::v_max = TWO_PI;
GLdouble torus_knot_surface::parameter_1 = 2;
GLdouble torus_knot_surface::parameter_2 = 1;

DCoordinate3 torus_knot_surface::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((parameter_1 + parameter_2*cos(u))*cos(v),
                        (parameter_1 + parameter_2*cos(u))*sin(v),
                        parameter_2*sin(u));
}

DCoordinate3 torus_knot_surface::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-cos(v) * sin(u),
                        -sin(v)*sin(u),
                        cos(u));
}

DCoordinate3 torus_knot_surface::d10(GLdouble u,GLdouble v)
{
    return DCoordinate3(-(cos(u)+2)*sin(v),(cos(u) + 2)*cos(v),0);
}

// Cylinder
GLdouble cylinder::u_min = 0;
GLdouble cylinder::u_max = TWO_PI;
GLdouble cylinder::v_min = 0;
GLdouble cylinder::v_max = PI;
GLdouble cylinder::parameter_1 = 2;

DCoordinate3 cylinder::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(u),sin(u),v);
}

DCoordinate3 cylinder::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-sin(u),cos(u),0);
}

DCoordinate3 cylinder::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(0,0,1);
}

//Sphere

GLdouble sphere::u_min = 0;
GLdouble sphere::u_max = TWO_PI;

GLdouble sphere::v_min = EPS;
GLdouble sphere::v_max = PI - EPS;

GLdouble sphere::parameter_1 = 2;

DCoordinate3 sphere::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(2.0*sin(v)*cos(u),2.0*sin(v)*sin(u),2.0*cos(v));
}

DCoordinate3 sphere::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-2.0*sin(v)*sin(u),2.0*sin(v)*cos(u),0);
}

DCoordinate3 sphere::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(2.0*cos(u)*cos(v),2.0*sin(u)*cos(v),-2.0* sin(v));
}

//Cone

GLdouble cone::u_min = 0;
GLdouble cone::u_max = 3;

GLdouble cone::v_min = EPS;
GLdouble cone::v_max = TWO_PI - EPS;

GLdouble cone::parameter_1 = 3.0;
GLdouble cone::parameter_2 = 2.0;


DCoordinate3 cone::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(((3.0 - u)/3.0)*2.0*cos(v),((3.0 - u)/3.0)*2.0*sin(v),u);
}

DCoordinate3 cone::d10(GLdouble u,GLdouble v)
{
    return DCoordinate3(-6.0*cos(v)/(u*u),-6.0 * sin(v)/(u*u),1);
}

DCoordinate3 cone::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3((2.0*u - 6.0)*sin(v)/u,(2.0*(3.0-u)*cos(v))/u,0);
}

//Screw

GLdouble screw::u_min = -TWO_PI;
GLdouble screw::u_max = TWO_PI;

GLdouble screw::v_min = -TWO_PI;
GLdouble screw::v_max = TWO_PI;

DCoordinate3 screw::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(v*cos(u),u,v*sin(u));
}

DCoordinate3 screw::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-v*sin(u),1,v*cos(u));
}

DCoordinate3 screw::d01(GLdouble u, GLdouble v)
{
    return  DCoordinate3(cos(u),0,sin(u));
}

//Parabolic cylinder

GLdouble parabolic::u_min = -PI;
GLdouble parabolic::u_max = PI;

GLdouble parabolic::v_min = -PI;
GLdouble parabolic::v_max = PI;

DCoordinate3 parabolic::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(v* cos(u),v,v*sin(u));
}

DCoordinate3 parabolic::d10(GLdouble u, GLdouble v)
{
    return  DCoordinate3(-v * sin(u),0,v * cos(u));
}

DCoordinate3 parabolic::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(u),1,sin(u));
}



