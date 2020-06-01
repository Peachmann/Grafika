#pragma once

#include <GL/glew.h>
#include <QGLWidget>
#include <QGLFormat>
#include "../Parametric/ParametricCurves3.h"
#include "../Parametric/ParametricSurfaces3.h"
#include <QTimer>
#include "../Core/TriangulatedMeshes3.h"
#include "../Core/Matrices.h"
#include "../Cyclic/CyclicCurves3.h"
#include "../Biquadratic/BiquadraticPatches3.h"
#include "../Biquadratic/BiquadraticArcs3.h"
#include "../Biquadratic/BiquadraticCompostieCurves3.h"
#include "../Biquadratic/BiquadraticCompositeSurfaces3.h"
#include "../Core/ShaderPrograms.h"
#include "../Core/Colors4.h"
#include "SideWidget.h"

namespace cagd
{
    class GLWidget: public QGLWidget
    {
        Q_OBJECT

    private:

        SideWidget *_side_widget;

        // variables defining the projection matrix
        double       _aspect;            // aspect ratio of the rendering window
        double       _fovy;              // field of view in direction y
        double       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        double       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // your other declarations

        ParametricCurve3* _pc;
        GenericCurve3* _image_of_pc;

        CyclicCurve3* _cc;
        GenericCurve3* _image_of_cc;
        GenericCurve3* _image_of_cc_interpolated;

        ParametricSurface3* _parametricsurface;
        TriangulatedMesh3* _surface;
        GLint _surfID = 0;
        GLint _curveID = 0;
        GLint _homeworkID = 0;
        GLint _modelID = 0;
        GLint _colorID = 0;
        GLint _polyID = 0;
        GLint _n;
        GLint _patch_status = 2;
        GLint _control_net_status = 2;
        GLint _uisolines = 0, _visolines = 0;

        int _d0 = 2;
        int _d1 = 2;
        int _d2 = 2;

        int _currentpoint = 0;

        QTimer *_timer;
        GLfloat _angle;
        TriangulatedMesh3 _mouse,_model;

        RowMatrix<TriangulatedMesh3> models;
        RowMatrix<ParametricSurface3*> surfaces;
        RowMatrix<ParametricCurve3*> curves;

        BiquadraticPatch3 _patch;
        //BiquadraticArcs3 _arc;

        TriangulatedMesh3 *_before_interpolation, *_after_interpolation;

        ColumnMatrix<DCoordinate3> _data_p;
        ColumnMatrix<GLdouble> _knot;

        GLint _shaderID;
        ShaderProgram _currentShader;
        RowMatrix<ShaderProgram> _shaders;
        float _scale_factor = 0;
        float _smoothing = 0;
        float _shading = 0;

        float _toon_color_1 = 0.0,_toon_color_2 = 0.0,_toon_color_3 = 0.0,_toon_color_4 = 0.0;


        /*Arcs / Patch*/
        RowMatrix<GenericCurve3*>* _uiso;
        RowMatrix<GenericCurve3*>* _viso;

        BiquadraticArcs3* _arc;
        GenericCurve3* _image_of_arc;
        GenericCurve3* _image_of_arc_interpolated;

        /*Curve*/
        GLuint _curveindex = 0;
        RowMatrix<Color4*> _colors;

        BiquadraticCompositeCurve3 *_curve;

        /* Surface */

        BiquadraticCompositeSurface3 *_composite_surface;
        void *depth;
        GLuint _surfaceindex = 0;

        /* Double spinboxes */
        GLdouble x_value;
        GLdouble y_value;
        GLdouble z_value;

    signals:
        void xcoordhasChanged(double);
        void ycoordhasChanged(double);
        void zcoordhasChanged(double);

    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);
        void mousePressEvent(QMouseEvent *event);
        void set_side_widget(SideWidget *w);

        virtual ~GLWidget();

    public slots:
        // public event handling methods/slots
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);

        void set_homeworkID(int value);
        void set_curveID(int value);
        void set_modelID(int value);
        void set_colorID(int value);
        void set_polyID(int value);
        void set_surfID(int value);

        void set_d0(int value);
        void set_d1(int value);
        void set_d2(int value);

        void _animate();
        void _deanimate();

        /* Interpolating Cyclic curve */

        void set_current_point(int point);
        void _set_data_p_x(double off);
        void _set_data_p_y(double off);
        void _set_data_p_z(double off);
        void _set_spinboxes(int point);

        /* Shader */
        void _load_shaders();
        void enable_shader(int value);
        void set_shader(int value);
        void set_individual_shader(int value);

        /* Toon Color Changer */
        void set_toon_color_1(double value);
        void set_toon_color_2(double value);
        void set_toon_color_3(double value);
        void set_toon_color_4(double value);

        /* Reflection Lines */

        void set_scaling_factor(double value);
        void set_smoothing(double value);
        void set_shading(double value);

        /* Patch */
        void set_patch_enable(int value);
        void set_control_net(int value);
        void set_visolines(int value);
        void set_uisolines(int value);
        /* Other */
        void renderCyclic();
        void arc();
        void patch();
        void renderArc();
        void set_derivative_scale(int);



        /* Arc controller */
        void add_arc();
        void delete_arc();
        void do_arc_operation();
        GLuint get_index_by_color(Color4* color);

        /* Patch controller */
        void add_patch();
        void delete_patch();
        void do_patch_operation();
        void change_patch_material(int value);

        void shift();

        /* Curve */
        void curve();
        void loadColors();

        /* Suface */
        void surface();

   private:
        void testMatrices();
        void pCurves();
        void pSurfaces();
        void _models();
        void playground();
        void testLab3();
        void cCurves();
        void rendercCurves();
   private slots:

    };
}
