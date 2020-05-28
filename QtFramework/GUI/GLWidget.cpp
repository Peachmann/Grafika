#include "GLWidget.h"



#if !defined(__APPLE__)
#include <GL/glu.h>
#endif

#include <iostream>
#include <fstream>
using namespace std;

#include <Core/Exceptions.h>
#include "../Core/Matrices.h"
#include "../Core/DCoordinates3.h"
#include "../Core/RealSquareMatrices.h"
#include "../Test/TestFunctions.h"
#include "../Core/Materials.h"
#include "../Core/Constants.h"
#include "../Core/HCoordinates3.h"
#include "../Core/Colors4.h"
#include "../Core/Lights.h"


namespace cagd
{
    //--------------------------------
    // special and default constructor
    //--------------------------------
    GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
    {
        _timer = new QTimer(this);
        _timer->setInterval(0);
        connect(_timer,SIGNAL(timeout()),this,SLOT(_animate()));

        models = RowMatrix<TriangulatedMesh3>(17);
        surfaces = RowMatrix<ParametricSurface3*>(7);
        curves = RowMatrix<ParametricCurve3*>(8);
        _shaders = RowMatrix<ShaderProgram>(5);


    }

    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {

        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (double)width() / (double)height();
        _z_near = 1.0;
        _z_far  = 1000.0;
        _fovy   = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0; _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0; _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling the depth test
        glEnable(GL_DEPTH_TEST);

        // setting the background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;

        // ...

        try
        {
            // initializing the OpenGL Extension Wrangler library
            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            // create and store your geometry in display lists or vertex buffer objects
            // ...
            if(_homeworkID == 1)
            {

                GLuint _n = 2;

                _cc = new CyclicCurve3(2);
                GLdouble step = TWO_PI / (2 * _n + 1);

                for(GLuint i = 0; i <= 2 * _n; i++)
                {
                    DCoordinate3 &cp = (*_cc)[i];
                    GLdouble u = i * step;
                    cp[0] = cos(u);
                    cp[1] = sin(u);
                }

                GLuint div_point_count = 200;
                GLenum usage_flag = GL_STATIC_DRAW;

                _cc->UpdateVertexBufferObjectsOfData();

                _image_of_cc = _cc->GenerateImage(_n,div_point_count);
                if(!_image_of_cc)
                {
                    cout<<"Error no _image_of_cc\n ";
                }
                if(!_image_of_cc->UpdateVertexBufferObjects(1.0,usage_flag))
                {
                    cout<<"Cannot create vertex buffer";
                }




               // cCurves();

            }
            if(_homeworkID == 0)
            {
                //testMatrices();

                glewInit();
                cout<<"Patches-----\n";
                _patch.SetData(0,0,-2.0,-2.0,0.0);
                _patch.SetData(0,1,-2.0,-1.0,0.0);
                _patch.SetData(0,2,-2.0,1.0,0.0);
                _patch.SetData(0,3,-2.0,2.0,0.0);

                _patch.SetData(1,0,-1.0,-2.0,0.0);
                _patch.SetData(1,1,-1.0,-1.0,2.0);
                _patch.SetData(1,2,-1.0,1.0,2.0);
                _patch.SetData(1,3,-1.0,2.0,0.0);

                _patch.SetData(2,0,1.0,-2.0,0.0);
                _patch.SetData(2,1,1.0,-1.0,2.0);
                _patch.SetData(2,2,1.0,1.0,2.0);
                _patch.SetData(2,3,1.0,2.0,0.0);

                _patch.SetData(3,0,2.0,-2.0,0.0);
                _patch.SetData(3,1,2.0,-1.0,0.0);
                _patch.SetData(3,2,2.0,1.0,0.0);
                _patch.SetData(3,3,2.0,2.0,0.0);

                 _patch.UpdateVertexBufferObjectsOfData();
                _uiso = _patch.GenerateUIsoparametricLines(30,1,20);
                _viso = _patch.GenerateVIsoparametricLines(30,1,20);

                for(GLuint i = 0; i < _uiso->GetColumnCount(); i++)
                {
                    (*_uiso)[i]->UpdateVertexBufferObjects();
                }

                for(GLuint i = 0; i < _viso->GetColumnCount(); i++)
                {
                    (*_viso)[i]->UpdateVertexBufferObjects();
                }

                _before_interpolation = _patch.GenerateImage(30,30);
                if(_before_interpolation)
                    _before_interpolation->UpdateVertexBufferObjects();

                //Knot in u-direction

                RowMatrix<GLdouble> u_knot_vector(4);
                u_knot_vector(0) = 0.0;
                u_knot_vector(1) = 1.0/3.0;
                u_knot_vector(2) = 2.0/3.0;
                u_knot_vector(3) = 1.0;

                //Knot in v-direction
                ColumnMatrix<GLdouble> v_knot_vector(4);
                v_knot_vector(0) = 0.0;
                v_knot_vector(1) = 1.0/3.0;
                v_knot_vector(2) = 2.0/3.0;
                v_knot_vector(3) = 1.0;

                //data_points_to_interp
                Matrix<DCoordinate3> data_points_to_interpolate(4,4);
                for(GLuint row = 0; row < 4; row++)
                {
                    for(GLuint column = 0; column < 4; ++column)
                    {
                        _patch.GetData(row,column,data_points_to_interpolate(row,column));
                    }
                }

                //Solve the interpolation problem
                if(_patch.UpdateDataForInterpolation(u_knot_vector,v_knot_vector,data_points_to_interpolate))
                {
                    _after_interpolation = _patch.GenerateImage(30,30);

                    if(_after_interpolation)
                        _after_interpolation->UpdateVertexBufferObjects();
                }







            }
            if(_homeworkID == 2)
                pCurves();
            if(_homeworkID == 3 || _homeworkID == 4)
            {
                 _models();
                 cout<<"Loading models"<<endl;
                _load_shaders();
            }
            /*)
            if(_homeworkID == 4)
            {
                _models();

                playground();
            }
            */
            if(_homeworkID == 5)
            {
                 pSurfaces();
            }
            if(_homeworkID == 6)
            {
                cCurves();
                set_current_point(0);
            }
            if(_homeworkID == 7)
            {
                arc();
            }


        }
        catch (Exception &e)
        {
            cout << e << endl;
        }


    }

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();

            // applying transformations
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);

            // render your geometry (this is oldest OpenGL rendering technique, later we will use some advanced methods)
    /*
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(1.1f, 0.0f, 0.0f);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.1f, 0.0f);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, 1.1f);
            glEnd();
*/
            if(_homeworkID == 6 || _homeworkID == 1)
            {
                renderCyclic();


                /*
            glBegin(GL_TRIANGLES);
                // attributes
                glColor3f(1.0f, 0.0f, 0.0f);
                // associated with position
                glVertex3f(1.0f, 0.0f, 0.0f);

                // attributes
                glColor3f(0.0, 1.0, 0.0);
                // associated with position
                glVertex3f(0.0, 1.0, 0.0);

                // attributes
                glColor3f(0.0f, 0.0f, 1.0f);
                // associated with position
                glVertex3f(0.0f, 0.0f, 1.0f);
            glEnd();
            */
            }
         if(_homeworkID == 0)
         {
             glewInit();



             if(_uisolines > 0)
             {
                 for(int i = 0; i<_uiso->GetColumnCount();i++)
                 {
                     (*_uiso)[i]->RenderDerivatives(0,GL_LINE_STRIP);
                     if(_d1)
                        (*_uiso)[i]->RenderDerivatives(1,GL_LINES);
                 }
             }

             if(_visolines > 0)
             {
                 for(int i = 0; i<_viso->GetColumnCount();i++)
                 {
                     (*_viso)[i]->RenderDerivatives(0,GL_LINE_STRIP);
                     if(_d1)
                        (*_viso)[i]->RenderDerivatives(1,GL_LINES);
                 }
             }




             glEnable(GL_LIGHTING);
             glEnable(GL_LIGHT0);
             glEnable(GL_NORMALIZE);



             if(_patch_status != 0)
             {
                 if(_before_interpolation)
                 {

                     MatFBRuby.Apply();
                     _before_interpolation->Render();
                 }
             }

             if(_control_net_status != 0)
             {
                 if(_after_interpolation)
                 {
                      _patch.RenderData();
                     glEnable(GL_BLEND);
                     glDepthMask(GL_FALSE);
                     glBlendFunc(GL_SRC_ALPHA,GL_ONE);
                        MatFBTurquoise.Apply();
                        _after_interpolation->Render();
                      glDepthMask(GL_TRUE);
                      glDisable(GL_BLEND);
                      glBlendFunc(GL_ONE,GL_ONE);
                 }
             }

             glDisable(GL_LIGHTING);
             glDisable(GL_LIGHT0);
             glDisable(GL_NORMALIZE);


         }
         if(_homeworkID ==2)
         {
         glewInit();
         if(_image_of_pc)
         {
            if(_d0 == 2)
            {
                glColor3f(1.0f,0.0f,0.0f);
                _image_of_pc->RenderDerivatives(0,GL_LINE_STRIP);
                glPointSize(5.0f);
                glColor3f(1.0f,1.0f,1.0f);
            }


            if(_d1 == 2)
            {
                glColor3f(0.0f, 0.5f, 0.0f);
                _image_of_pc->RenderDerivatives(1, GL_LINES);
                _image_of_pc->RenderDerivatives(1, GL_POINTS);
                glColor3f(1.0f,1.0f,1.0f);
            }

            if(_d2 == 2)
            {
                glColor3f(0.1f, 0.5f, 0.9f);
                _image_of_pc->RenderDerivatives(2, GL_LINES);
                _image_of_pc->RenderDerivatives(2, GL_POINTS);
                glColor3f(1.0f,1.0f,1.0f);
            }

            glPointSize(1.0f);
            glColor3f(1.0f,1.0f,1.0f);

         }
         }


        if(_homeworkID == 3)
        {


        glewInit();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_BLEND);
        if(_polyID == 0)
        {
              glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }
        //

        switch (_colorID) {
        case 0:
        {
            MatFBBrass.Apply();
        }
        break;
        case 1:
        {
            MatFBGold.Apply();
        }
        break;
        case 2:
        {
            MatFBSilver.Apply();
        }
        break;
        case 3:
        {
            MatFBEmerald.Apply();
        }
        break;
        case 4:
        {
            MatFBPearl.Apply();
        }
        break;
        case 5:
        {
            MatFBRuby.Apply();
        }
        break;
        case 6:
        {
            MatFBTurquoise.Apply();
        }
        break;


        }
        _model.Render();
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_NORMALIZE);
        glDisable(GL_BLEND);
       }

     if(_homeworkID == 4)
     {
         glewInit();
         glEnable(GL_LIGHTING);
         glEnable(GL_LIGHT0);
         glEnable(GL_NORMALIZE);
         if(_polyID == 0)
         {
               glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         }
         else
         {
             glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         }
         MatFBEmerald.Apply();
         _model = models[2];
         glTranslated(0.0,-1.5,-1.5);
         glScaled(0.5,0.5,0.5);
         for(int j = 0; j < 9;j++)
         {
             _model.Render();
             for (int i = 0;i < 4;i++) {
                  glTranslated(-1.0,0.0,0.0);
                  _model.Render();
             }
             glTranslated(4.0,0.0,0.0);
             for (int i = 0;i < 4;i++) {
                  glTranslated(1.0,0.0,0.0);
                  _model.Render();
             }
             glTranslated(-4.0,0.0,1.0);
         }
         glTranslated(0.0,1.0,-5.0);

         for(int i = 0; i < 5; i++)
         {
             MatFBRuby.Apply();
             _model.Render();
             glTranslated(0.0,1.0,0.0);
         }
         _model = models[13];
         _model.Render();

         _model = models[2];

         glTranslated(4.0,-5.0,4.0);
         _model.Render();
         for(int i = 0; i < 4 ; i++)
         {
             glTranslated(-1.0,1.0,-1.0);
             _model.Render();
             glTranslated(1.0,0.0,1.0);
             _model = models[1];
             _model.Render();
             glTranslated(-1.0,0.0,-1.0);
             _model = models[2];

         }
         glTranslated(4.0,-4.0,4.0);
         glTranslated(-8.0,0.0,0.0);
         _model.Render();
         for(int i = 0; i < 4 ; i++)
         {
             glTranslated(1.0,1.0,-1.0);
             _model.Render();
             glTranslated(-1.0,0.0,1.0);
             _model = models[1];
             _model.Render();
             glTranslated(1.0,0.0,-1.0);
             _model = models[2];


         }
         glTranslated(-4.0,-4.0,4.0);
         glTranslated(0.0,0.0,-8.0);
         _model.Render();
         for(int i = 0; i < 4 ; i++)
         {
             glTranslated(1.0,1.0,1.0);
             _model.Render();
             glTranslated(-1.0,0.0,-1.0);
             _model = models[1];
             _model.Render();
             glTranslated(1.0,0.0,1.0);
             _model = models[2];

         }
         glTranslated(-4.0,-4.0,-4.0);
         glTranslated(8.0,0.0,0.0);
         _model.Render();
         for(int i = 0; i < 4 ; i++)
         {
             glTranslated(-1.0,1.0,1.0);
             _model.Render();
             glTranslated(1.0,0.0,-1.0);
             _model = models[1];
             _model.Render();
             glTranslated(-1.0,0.0,1.0);
             _model = models[2];

         }
         glTranslated(4.0,-4.0,4.0);
         MatFBTurquoise.Apply();
         _model = models[0];
         for(int i = 0; i < 2; i++)
         {
             glTranslated(-1.0,0.0,0.0);
            _model.Render();

         }
         glTranslated(-2.0,0.0,0.0);
         glRotated(90.0,0.0,1.0,0.0);
         glScaled(3.0,3.0,3.0);
         glTranslated(0.0,0.25,0.0);
         _model = models[7];

         _model.Render();

         glTranslated(0.0,-0.25,0.0);
         glScaled(0.33,0.33,0.33);
         glRotated(-90.0,0.0,1.0,0.0);
         _model = models[0];
          glTranslated(-1.0,0.0,0.0);
         for(int i = 0; i < 2; i++)
         {
             glTranslated(-1.0,0.0,0.0);
            _model.Render();

         }
         _model = models[6];
         MatFBGold.Apply();
         glTranslated(-1.0,3.0,-2.0);
         glRotated(270.0,1.0,1.0,0.0);
         glScaled(3.0,3.0,3.0);
         _model.Render();

         glScaled(0.33,0.33,0.33);
          glRotated(270.0,-1.0,-1.0,0.0);
         _model = models[9];
         glTranslated(0.0,-3.0,-2.0);
         glRotated(270.0,1.0,0.0,0.0);
          _model.Render();
         glRotated(270.0,-1.0,0.0,0.0);
          _model = models[6];
          glTranslated(-1.0,3.0,-2.0);
          glRotated(270.0,-1.0,0.0,0.0);
          glScaled(3.0,3.0,3.0);

          _model.Render();
          glScaled(0.33,0.33,0.33);
          glRotated(270.0,1.0,0.0,0.0);

          MatFBPearl.Apply();
          glTranslated(2.0,-3.15,-2.2);
          _model = models[10];
          glRotated(90.0,-1.0,0.0,0.0);
          _model.Render();

          for(int i = 0 ; i < 2; i++)
          {
             glTranslated(1.0,0.0,0.0);
            _model.Render();
          }
          glRotated(45.0,1.0,0.0,0.0);
            glTranslated(1.0,0.0,0.0);
           _model.Render();
          glRotated(45.0,-1.0,0.0,0.0);
          for(int i = 0 ; i < 3; i++)
          {
             glTranslated(1.0,0.0,0.0);
            _model.Render();
          }
          glRotated(90.0,1.0,0.0,0.0);
          glTranslated(1.0,0.0,1.0);
          MatFBSilver.Apply();

          for(int i = 0; i < 7; i++)
          {
              if(i%2)
              {
                  _model = models[2];
              }
              else
                {
                 _model = models[14];
              }
              _model.Render();
              glTranslated(0.0,0.0,1.0);
         }
          glDisable(GL_LIGHTING);
          glDisable(GL_LIGHT0);
          glDisable(GL_NORMALIZE);
         }
     if(_homeworkID == 5)
        {
            glewInit();
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);

                //dl->Enable();
                switch (_colorID) {
                case 0:
                {
                    MatFBBrass.Apply();
                }
                break;
                case 1:
                {
                    MatFBGold.Apply();
                }
                break;
                case 2:
                {
                    MatFBSilver.Apply();
                }
                break;
                case 3:
                {
                    MatFBEmerald.Apply();
                }
                break;
                case 4:
                {
                    MatFBPearl.Apply();
                }
                break;
                case 5:
                {
                    MatFBRuby.Apply();
                }
                break;
                case 6:
                {
                    MatFBTurquoise.Apply();
                }
                break;
                }
                _surface->Render();
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
                glDisable(GL_NORMALIZE);



     }

     if(_homeworkID == 7)
     {
         renderArc();
     }
    /* -- SURFACES------
     *

        DirectionalLight *dl = 0;

        HCoordinate3 direction(0.0,0.0,1.0,1.0);
        Color4 ambient(0.4,0.4,0.4,1.0);
        Color4 diffuse(0.8,0.8,0.8,1.0);
        Color4 specular(1.0,1.0,1.0,1.0);

        dl = new DirectionalLight(GL_LIGHT0,direction,ambient,diffuse,specular);

        if(dl)
        {
            dl->Enable();
            MatFBRuby.Apply();
            _surface->Render();
            dl->Disable();
        }

        if(dl)
        {
            delete dl,dl = 0;
        }
        */
        // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
        // i.e., the original model view matrix is restored
        glPopMatrix();


    }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (double)w / (double)h;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        updateGL();
    }

    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            updateGL();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_x(double value)
    {
        if (_trans_x != value)
        {
            _trans_x = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            updateGL();
        }
    }



    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            updateGL();
        }
    }

    void GLWidget::set_d0(int value)
    {
        if(_d0 != value)
        {
            _d0 = value;
            updateGL();
        }
    }

    void GLWidget::set_d1(int value)
    {
        if(_d1 != value)
        {
            _d1 = value;
            updateGL();
        }
    }

    void GLWidget::set_d2(int value)
    {
        if(_d2 != value)
        {
            _d2 = value;
            updateGL();
        }
    }

    void GLWidget::set_homeworkID(int value)
    {

        if(_homeworkID != value)
        {
            _homeworkID = value;
            cout<<endl<<"New value is " << _homeworkID<<endl;
            initializeGL();
            //paintGL();
            updateGL();
        }
    }

    void GLWidget::set_curveID(int value)
    {
        if(_curveID != value)
        {
            _curveID = value;
            cout<<_curveID;
            _pc = curves[_curveID];
             if(!_pc) exit(1);

             GLuint div_point_count = 200;
             GLenum usage_flag = GL_STATIC_DRAW;

             _image_of_pc = nullptr;
             _image_of_pc = _pc->GenerateImage(div_point_count,usage_flag);

             if(!_image_of_pc) exit(1);

             if(!_image_of_pc->UpdateVertexBufferObjects(0.33,usage_flag))
             {
                 cout << "Could not create the vertex buffer object of the parametric curve!" << endl;
             }
            //initializeGL();
            updateGL();
        }
    }



    void GLWidget::set_modelID(int value)
    {
        if(_modelID != value)
        {
            _modelID = value;
            _model = models(value);
            cout<<"Set model to "<<value;
            //initializeGL();
            updateGL();

        }
    }

    void GLWidget::set_colorID(int value)
    {
        if(_colorID != value)
        {
            _colorID = value;
            updateGL();
        }
    }

    void GLWidget::set_polyID(int value)
    {
        if(_polyID != value)
        {
            _polyID = value;
            updateGL();
        }
    }

    void GLWidget::set_surfID(int value)
    {
        if(_surfID != value)
        {
            _surfID = value;
            _parametricsurface = nullptr;
            //_parametricsurface = new (nothrow) ParametricSurface3(_pd,screw::u_min,screw::u_max,screw::v_min,screw::v_max);

            _parametricsurface = surfaces(_surfID);
            GLuint div_point_count = 200;
            GLenum usage_flag = GL_STATIC_DRAW;

            _surface = nullptr;
            _surface = _parametricsurface->GenerateImage(div_point_count,div_point_count,usage_flag);

            _surface->UpdateVertexBufferObjects(usage_flag);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);
            _angle = 0.0;
            updateGL();
        }
    }


    void GLWidget::pSurfaces()
    {

        glewInit();

        TriangularMatrix<ParametricSurface3::PartialDerivative> _pd(2);



        _pd(0,0) = screw::d00;
        _pd(1,0) = screw::d10;
        _pd(1,1) = screw::d01;
        surfaces(0) = nullptr;
        surfaces(0) = new (nothrow) ParametricSurface3(_pd,screw::u_min,screw::u_max,screw::v_min,screw::v_max);

        _pd(0,0) = cylinder::d00;
        _pd(1,0) = cylinder::d10;
        _pd(1,1) = cylinder::d01;
        surfaces(1) = nullptr;
        surfaces(1) = new (nothrow) ParametricSurface3(_pd,cylinder::u_min,cylinder::u_max,cylinder::v_min,cylinder::v_max);

        _pd(0,0) = torus_knot_surface::d00;
        _pd(1,0) = torus_knot_surface::d10;
        _pd(1,1) = torus_knot_surface::d01;
        surfaces(2) = nullptr;
        surfaces(2) = new (nothrow) ParametricSurface3(_pd,torus_knot_surface::u_min,torus_knot_surface::u_max,torus_knot_surface::v_min,torus_knot_surface::v_max);

        _pd(0,0) = sphere::d00;
        _pd(1,0) = sphere::d01;
        _pd(1,1) = sphere::d10;
        surfaces(3) = nullptr;
        surfaces(3) = new (nothrow) ParametricSurface3(_pd,sphere::u_min,sphere::u_max,sphere::v_min,sphere::v_max);

        _pd(0,0) = cone::d00;
        _pd(1,0) = cone::d01;
        _pd(1,1) = cone::d10;
        surfaces(4) = nullptr;
        surfaces(4) = new (nothrow) ParametricSurface3(_pd,cone::u_min,cone::u_max,cone::v_min,cone::v_max);

        _pd(0,0) = parabolic::d00;
        _pd(1,0) = parabolic::d01;
        _pd(1,1) = parabolic::d10;
        surfaces(5) = nullptr;
        surfaces(5) = new (nothrow) ParametricSurface3(_pd,parabolic::u_min,parabolic::u_max,parabolic::v_min,parabolic::v_max);


        _parametricsurface = nullptr;
        //_parametricsurface = new (nothrow) ParametricSurface3(_pd,screw::u_min,screw::u_max,screw::v_min,screw::v_max);

        _parametricsurface = surfaces(0);
        GLuint div_point_count = 200;
        GLenum usage_flag = GL_STATIC_DRAW;

        _surface = nullptr;
        _surface = _parametricsurface->GenerateImage(div_point_count,div_point_count,usage_flag);

        _surface->UpdateVertexBufferObjects(usage_flag);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        _angle = 0.0;

    }

    void GLWidget::pCurves()
    {

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable(GL_DEPTH_TEST);
        glewInit();



        RowMatrix<ParametricCurve3::Derivative>derivative(3);

        derivative(0)=spiral_on_cone::d0;
        derivative(1)=spiral_on_cone::d1;
        derivative(2)=spiral_on_cone::d2;

         _pc = nullptr;
         _pc = new (nothrow) ParametricCurve3(derivative, spiral_on_cone::u_min, spiral_on_cone::u_max);
         curves[0] = _pc;

         derivative(0)=torus_knot::d0;
         derivative(1)=torus_knot::d1;
         derivative(2)=torus_knot::d2;

         _pc = nullptr;
         _pc = new (nothrow) ParametricCurve3(derivative, torus_knot::u_min, torus_knot::u_max);
         curves[1] = _pc;

         derivative(0)=helix::d0;
         derivative(1)=helix::d1;
         derivative(2)=helix::d2;

         _pc = nullptr;
         _pc = new (nothrow) ParametricCurve3(derivative, helix::u_min, helix::u_max);

         curves[2] = _pc;

         derivative(0)=ellipse::d0;
         derivative(1)=ellipse::d1;
         derivative(2)=ellipse::d2;

         _pc = nullptr;
         _pc = new (nothrow) ParametricCurve3(derivative, ellipse::u_min, ellipse::u_max);

         curves[3] = _pc;


         derivative(0)=hypocloid::d0;
         derivative(1)=hypocloid::d1;
         derivative(2)=hypocloid::d2;

         _pc = nullptr;
         _pc = new (nothrow) ParametricCurve3(derivative, hypocloid::u_min, hypocloid::u_max);

         curves[4] = _pc;

         derivative(0)=epicycloid::d0;
         derivative(1)=epicycloid::d1;
         derivative(2)=epicycloid::d2;

         _pc = nullptr;
         _pc = new (nothrow) ParametricCurve3(derivative, epicycloid::u_min, epicycloid::u_max);

         curves[5] = _pc;

         derivative(0)=rose::d0;
         derivative(1)=rose::d1;
         derivative(2)=rose::d2;

         _pc = nullptr;
         _pc = new (nothrow) ParametricCurve3(derivative, rose::u_min, rose::u_max);

         curves[6] = _pc;




         _pc = nullptr;




       if(_homeworkID < 0)
           _homeworkID = 0;

       switch (_curveID) {
       case 0:
           _pc = curves[0];
       break;

       case 1:
           _pc = curves[1];
       break;

       case 2:
           _pc = curves[2];
       break;

       case 3:
           _pc = curves[3];
       break;

       case 4:
           _pc = curves[4];
       break;

       case 5:
           _pc = curves[5];
       break;

       case 6:
           _pc = curves[6];
       break;
       }

        if(_homeworkID == 2)
        {
        if(!_pc) exit(1);

        GLuint div_point_count = 200;
        GLenum usage_flag = GL_STATIC_DRAW;

        _image_of_pc = nullptr;
        _image_of_pc = _pc->GenerateImage(div_point_count,usage_flag);

        if(!_image_of_pc) exit(1);

        if(!_image_of_pc->UpdateVertexBufferObjects(0.33,usage_flag))
        {
            cout << "Could not create the vertex buffer object of the parametric curve!" << endl;
        }
        }

        updateGL();
    }

    void GLWidget::_models()
    {
       // RowMatrix<TriangulatedMesh3> models(17);
        /*
        if(_mouse.LoadFromOFF("Models/mouse.off",true))
            if(_mouse.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {

                //_timer->start();
            }
        */

        glewInit();


        if(models[0].LoadFromOFF("Models/mouse.off",true))
        {
            if(models[0].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }

        glewInit();

        if(models[1].LoadFromOFF("Models/angel.off",true))
        {
            if(models[1].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);

            }
        }
        glewInit();
        if(models[2].LoadFromOFF("Models/cube.off",true))
        {
            if(models[2].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[3].LoadFromOFF("Models/bird.off",true))
        {
            if(models[3].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[4].LoadFromOFF("Models/bug.off",true))
        {
            if(models[4].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[5].LoadFromOFF("Models/cone.off",true))
        {
            if(models[5].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[6].LoadFromOFF("Models/dragon.off",true))
        {
            if(models[6].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[7].LoadFromOFF("Models/elephant.off",true))
        {
            if(models[7].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _timer->start();
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[8].LoadFromOFF("Models/gangster.off",true))
        {
            if(models[8].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[9].LoadFromOFF("Models/goblet.off",true))
        {
            if(models[9].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[10].LoadFromOFF("Models/horse.off",true))
        {
            if(models[10].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[11].LoadFromOFF("Models/icosahedron.off",true))
        {
            if(models[11].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[12].LoadFromOFF("Models/seashell.off",true))
        {
            if(models[12].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[13].LoadFromOFF("Models/space_station.off",true))
        {
            if(models[13].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[14].LoadFromOFF("Models/sphere.off",true))
        {
            if(models[14].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[15].LoadFromOFF("Models/Spot.off",true))
        {
            if(models[15].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }
        glewInit();
        if(models[16].LoadFromOFF("Models/star.off",true))
        {
            if(models[16].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
            {
                _angle = 0.0;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
            }
        }

        _model = models[_modelID];
        cout<<"Model set"<<endl;
    }

    void GLWidget::cCurves()
    {
        /*
        _n = 3;
        _cc = new CyclicCurve3(_n);
        cout<<"\nLine 1311\n";
        if(!_cc)
        {
            cout<<"Error creating cyclic curve!";
        }

        GLdouble step = TWO_PI/ (2*_n + 1);
        for(GLint i= 0; i <= 2 * _n; i++)
        {
            DCoordinate3 &cp = (*_cc)[i];
            GLdouble u = i * step;
            cp[0] = sin(u);
            cp[1] = cos(u);

        }

        _cc->UpdateVertexBufferObjectsOfData();
        _image_of_cc = _cc->GenerateImage(_n,200,GL_STATIC_DRAW);
        _image_of_cc->UpdateVertexBufferObjects(0.5);
        cout<<"end of cCurves()!";
        updateGL();
        */
        _n = 2;
       _cc = new CyclicCurve3(_n);
       if(!_cc)
       {
           cout<<"Error creating cyclic curve!";
       }



       _data_p.ResizeRows(5);

       _data_p[0] = DCoordinate3(-1.0, 1.0, 0.0);
       _data_p[1] = DCoordinate3(1.0, 1.0, 0.0);
       _data_p[2] = DCoordinate3(1.0, 1.0, 1.0);
       _data_p[3] = DCoordinate3(-1.0, -1.0, 0.0);
       _data_p[4] = DCoordinate3(-1.0, -1.0, -1.0);
       GLdouble step = TWO_PI/ (2*_n + 1);
       _knot.ResizeRows(5);

       for(GLint i =0 ;i <= 2 * _n; i++)
       {
           GLdouble u = i * step;
           _knot[i] = u;
       }

       _cc->UpdateDataForInterpolation(_knot,_data_p);
       _cc->UpdateVertexBufferObjectsOfData();

       _image_of_cc = _cc->GenerateImage(_n,200);
       _image_of_cc->UpdateVertexBufferObjects(0.5);


        updateGL();

    }


    void GLWidget::_set_spinboxes(int point)
    {
          emit xcoordhasChanged(_data_p(point).x());
          emit ycoordhasChanged(_data_p(point).y());
          emit zcoordhasChanged(_data_p(point).z());
    }

    void GLWidget::set_current_point(int point)
    {
            cout<<"\n-----\n In set_current_point \n------\n";
            _currentpoint = point;
            cout<<"Current point changed to : "<< point << endl;
            _set_spinboxes(point);


    }

    void GLWidget::_set_data_p_x(double off)
    {
        if(off != _data_p(_currentpoint).x())
        {
            cout<<endl<<"Offsetting "<<_currentpoint<<"'s x with " << off<<endl;
            _data_p(_currentpoint).x() = off;
            _cc->UpdateDataForInterpolation(_knot,_data_p);
            _cc->UpdateVertexBufferObjectsOfData();

            _image_of_cc = _cc->GenerateImage(_n,200);
            _image_of_cc->UpdateVertexBufferObjects(0.33);
            updateGL();
        }
    }

    void GLWidget::_set_data_p_y(double off)
    {
        if(off != _data_p(_currentpoint).y())
        {
            cout<<endl<<"Offsetting "<<_currentpoint<<"'s y with " << off<<endl;

           _data_p(_currentpoint).y() = off;
           _cc->UpdateDataForInterpolation(_knot,_data_p);
           _cc->UpdateVertexBufferObjectsOfData();

           _image_of_cc = _cc->GenerateImage(_n,200);
           _image_of_cc->UpdateVertexBufferObjects(0.33);

           updateGL();
        }
    }

    void GLWidget::_set_data_p_z(double off)
    {
        if(off != _data_p(_currentpoint).z())
        {
            cout<<endl<<"Offsetting "<<_currentpoint<<"'s z with " << off<<endl;

           _data_p(_currentpoint).z() = off;
           _cc->UpdateDataForInterpolation(_knot,_data_p);
           _cc->UpdateVertexBufferObjectsOfData();

           _image_of_cc = _cc->GenerateImage(_n,200);
           _image_of_cc->UpdateVertexBufferObjects(0.33);


           updateGL();
        }

    }

    void GLWidget::rendercCurves()
    {
        if(_cc)
        {
            _cc->RenderData(GL_LINE_LOOP);
        }
    }

    void GLWidget::testMatrices()
    {
        //cout<<"Harba$$" << endl;

        Matrix<int> M(3,5);
        Matrix<int> N(3,5);
        cout<<M<<endl;

        ifstream f("input.txt",ios_base::in);
        ofstream g("output.txt",ios_base::out);

        g << M;
        f >> N;

        cout<<N<<endl;

        RealSquareMatrix A;
        ColumnMatrix<GLdouble> B,X;

        f>>A;
        f>>B;
        cout<<A<<endl<<B;

        if(!A.SolveLinearSystem(B,X))
        {
        throw Exception("Could not solve linear system.");
        }

        cout<<"The solution is: "<<endl<<X<<endl;

        f.close();
        g.close();
    }

    void GLWidget::set_patch_enable(int value)
    {
        if(_patch_status != value)
        {
            _patch_status = value;
            updateGL();
        }
    }

    void GLWidget::set_control_net(int value)
    {
        if(_control_net_status != value)
        {
            _control_net_status = value;
            updateGL();
        }
    }

    void GLWidget::set_uisolines(int value)
    {
        if(_uisolines != value)
        {
              _uisolines = value;
              updateGL();
        }
    }

    void GLWidget::set_visolines(int value)
    {
        if(_visolines != value)
        {
              _visolines = value;
              updateGL();
        }
    }


    void GLWidget::_animate()
    {

            _timer->start();

            GLfloat *vertex = _model.MapVertexBuffer(GL_READ_WRITE);
            GLfloat *normal = _model.MapNormalBuffer(GL_READ_ONLY);

            _angle+=DEG_TO_RADIAN;
            if(_angle >= TWO_PI) _angle-=TWO_PI;

            GLfloat scale = sin(_angle)/3000.0;
            for(GLuint i = 0;i<_model.VertexCount();++i)
            {
                for(GLuint coordinate = 0;coordinate < 3; ++coordinate,++vertex,++normal)
                    *vertex += scale * (*normal);
            }

            _model.UnmapNormalBuffer();
            _model.UnmapVertexBuffer();

            updateGL();

    }

    void GLWidget::_deanimate()
    {
        _timer->stop();
    }

    void GLWidget::testLab3()
    {
        HCoordinate3 h = HCoordinate3(1,1,1,2);
        cout << h;
        HCoordinate3 b = HCoordinate3(1,2,3,1);
        HCoordinate3 a;
        a = h + b;
        cout<<a;
        h+=b;
        cout<<h;
        cout<<_mouse.VertexCount() << " " << _mouse.FaceCount();
    }

    void GLWidget::set_toon_color_1(double value)
    {
        if(_toon_color_1 != value)
        {
            cout<< "ShaderID : "<<_shaderID << endl;
            _toon_color_1 = value;
            if(_shaderID == 2)
            {
                glEnable(GL_BLEND);
                _currentShader.Enable();
                _currentShader.SetUniformVariable4f("default_outline_color",_toon_color_1,_toon_color_2,_toon_color_3,_toon_color_4);


                updateGL();
                glDisable(GL_BLEND);
               // _currentShader.Disable();
            }


        }
    }

    void GLWidget::set_toon_color_2(double value)
    {
        if(_toon_color_2 != value)
        {
            _toon_color_2 = value;
            if(_shaderID == 2)
            {
                 glEnable(GL_BLEND);
                _currentShader.Enable();
                _currentShader.SetUniformVariable4f("default_outline_color",_toon_color_1,_toon_color_2,_toon_color_3,_toon_color_4);


                updateGL();
                glDisable(GL_BLEND);
               // _currentShader.Disable();
            }
        }
    }

    void GLWidget::set_toon_color_3(double value)
    {
        if(_toon_color_3 != value)
        {
            _toon_color_3 = value;
            if(_shaderID == 2)
            {
                 glEnable(GL_BLEND);
                _currentShader.Enable();
                _currentShader.SetUniformVariable4f("default_outline_color",_toon_color_1,_toon_color_2,_toon_color_3,_toon_color_4);


                updateGL();
                glDisable(GL_BLEND);
              //  _currentShader.Disable();
            }
        }
    }

    void GLWidget::set_toon_color_4(double value)
    {
        if(_toon_color_4 != value)
        {
            _toon_color_4 = value;
            if(_shaderID == 2)
            {
                glEnable(GL_BLEND);
                _currentShader.Enable();
                _currentShader.SetUniformVariable4f("default_outline_color",_toon_color_1,_toon_color_2,_toon_color_3,_toon_color_4);


                updateGL();
                glDisable(GL_BLEND);
                //_currentShader.Disable();
            }
        }
    }

    void GLWidget::set_scaling_factor(double value)
    {
        if(_scale_factor != value)
        {
            _scale_factor = value;
            if(_shaderID == 1)
            {
                _currentShader.Enable();
                _currentShader.SetUniformVariable1f("scale_factor",_scale_factor);
                updateGL();
                //_currentShader.Disable();
            }
        }
    }

    void GLWidget::set_smoothing(double value)
    {
        if(_smoothing != value)
        {
            _smoothing = value;
            if(_shaderID == 1)
            {
                _currentShader.Enable();
                _currentShader.SetUniformVariable1f("smoothing",_smoothing);
                updateGL();
              // _currentShader.Disable();
            }
        }
    }

    void GLWidget::set_shading(double value)
    {
        if(_shading != value)
        {
            _shading = value;
            if(_shaderID == 1)
            {
                _currentShader.Enable();
                _currentShader.SetUniformVariable1f("shading",_shading);
                updateGL();
              // _currentShader.Disable();
            }
        }
    }


    void GLWidget::_load_shaders()
    {
        _shaders(0).InstallShaders("Shaders/directional_light.vert",
                                   "Shaders/directional_light.frag",
                                  GL_TRUE);
        _shaders(1).InstallShaders("Shaders/reflection_lines.vert",
                                   "Shaders/reflection_lines.frag",
                                  GL_TRUE);
        _shaders(2).InstallShaders("Shaders/toon.vert",
                                   "Shaders/toon.frag",
                                  GL_TRUE);
        _shaders(3).InstallShaders("Shaders/two_sided_lighting.vert",
                                   "Shaders/two_sided_lighting.frag",
                                  GL_TRUE);
    }
    void GLWidget::set_shader(int value)
    {
        if(value != _shaderID)
        {
            _shaderID = value;
           _currentShader = _shaders(value);
           _currentShader.Enable();

            updateGL();

             //_currentShader.Disable();
        }
    }

    void GLWidget::enable_shader(int value)
    {
        if(value != 0)
        {
            _currentShader.Enable();

        }
        else
        {
            _currentShader.Disable();
        }
         updateGL();


    }

    void GLWidget::renderCyclic()
    {
        set_current_point(0);
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        if(_homeworkID == 6)
        {
            for(GLuint i = 0; i < 2 * _n + 1; i++)
            {
                glVertex3dv(&_data_p[i][0]);

            }
        }

        glEnd();
        glPointSize(1.0);

        if(_cc)
        {
            glColor3f(1.0f,1.0f,1.0f);
            _cc->RenderData(GL_LINE_LOOP);
        }

        if(_image_of_cc)
        {
            glColor3f(1.0f,0.0f,0.0f);
            _image_of_cc->RenderDerivatives(0,GL_LINE_STRIP);
            glPointSize(5.0f);

            if(_d1)
            {
                glColor3f(0.0f,0.5f,0.0f);
                _image_of_cc->RenderDerivatives(1,GL_LINES);
                _image_of_cc->RenderDerivatives(1,GL_POINTS);
            }

            if(_d2)
            {
                glColor3f(0.1f,0.5f,0.9f);
                _image_of_cc->RenderDerivatives(2,GL_LINES);
                _image_of_cc->RenderDerivatives(2,GL_POINTS);
            }
        }
        glPointSize(1.0f);
    }

    void GLWidget::arc()
    {
        _arc = new BiquadraticArcs3();
            GLdouble step = TWO_PI / 4.0;


            _data_p.ResizeRows(4);

            _data_p[0] = DCoordinate3(-1.0, 1.0, 0.0);
            _data_p[3] = DCoordinate3(1.0, 1.0, 0.0);
            _data_p[2] = DCoordinate3(1.0, 1.0, 1.0);
            _data_p[1] = DCoordinate3(-1.0, -1.0, 0.0);
            _knot.ResizeRows(4);

            for(GLuint i = 0; i <= 3.0; i++)
            {
                DCoordinate3 &cp = (*_arc)[i];
                GLdouble u = i * step;
                cp[0] = cos(u);
                cp[1] = sin(u);
            }


            GLuint div_point_count = 200;
            GLenum usage_flag = GL_STATIC_DRAW;

            _arc->UpdateVertexBufferObjectsOfData();

            _image_of_arc = _arc->GenerateImage(3,div_point_count);
            if(!_image_of_arc)
            {
                cout<<"Error no _image_of_cc\n ";
            }
            if(!_image_of_arc->UpdateVertexBufferObjects(1.0,usage_flag))
            {
                cout<<"Cannot create vertex buffer";
            }

    }

    void GLWidget::renderArc()
    {


                glPointSize(1.0);

                if(_arc)
                {
                    glColor3f(1.0f,1.0f,1.0f);
                    _arc->RenderData(GL_LINE_STRIP);
                }

                if(_image_of_arc)
                {
                    glColor3f(1.0f,0.0f,0.0f);
                    _image_of_arc->RenderDerivatives(0,GL_LINE_STRIP);
                    glPointSize(5.0f);

                    if(_d1)
                    {
                        glColor3f(0.0f,0.5f,0.0f);
                        _image_of_arc->RenderDerivatives(1,GL_LINES);
                        _image_of_arc->RenderDerivatives(1,GL_POINTS);
                    }

                    if(_d2)
                    {
                        glColor3f(0.1f,0.5f,0.9f);
                        _image_of_arc->RenderDerivatives(2,GL_LINES);
                        _image_of_arc->RenderDerivatives(2,GL_POINTS);
                    }
                }
                glPointSize(1.0f);
    }

    void GLWidget::set_derivative_scale(int value)
    {
        GLenum usage_flag = GL_STATIC_DRAW;
        GLdouble scale = (GLdouble)value / 100;
        if(_homeworkID == 1 &&  !_image_of_cc->UpdateVertexBufferObjects(scale,usage_flag))
        {
            cout<<"Could not create vertex buffer of cyclic curve!";
        }
        else if(_homeworkID == 2 && !_image_of_pc->UpdateVertexBufferObjects(scale,usage_flag))
        {
            cout<<"Could not create vertex buffer of parametric curve!";
        }
        else if(_homeworkID == 6 && !_image_of_cc->UpdateVertexBufferObjects(scale,usage_flag))
        {
            cout<<"Could not create vertex buffer of interpolated cyclic curve!";
        }
        else if(_homeworkID == 7 && !_image_of_arc->UpdateVertexBufferObjects(scale,usage_flag))
        {
            cout<<"Could not create vertex buffer of arc!";
        }
        updateGL();
    }

    GLWidget::~GLWidget()
    {
        if (_pc) delete _pc;
                _pc = nullptr;

        if (_image_of_pc) delete _image_of_pc;
                _image_of_pc = nullptr;

        if(_parametricsurface)
            delete _parametricsurface,_parametricsurface = nullptr;
        if(_surface)
            delete _surface,_surface = nullptr;

        if(_before_interpolation)
        {
            delete _before_interpolation, _before_interpolation = 0;
        }

        if(_after_interpolation)
        {
            delete _after_interpolation, _after_interpolation = 0;
        }
        if(_arc)
        {
            delete _arc,_arc = 0;
        }
        if (_image_of_arc) delete _image_of_arc;
                        _image_of_arc = nullptr;

    }
}
