#include "MainWindow.h"

namespace cagd
{
    MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    {
        setupUi(this);

    /*

      the structure of the main window's central widget

     *---------------------------------------------------*
     |                 central widget                    |
     |                                                   |
     |  *---------------------------*-----------------*  |
     |  |     rendering context     |   scroll area   |  |
     |  |       OpenGL widget       | *-------------* |  |
     |  |                           | | side widget | |  |
     |  |                           | |             | |  |
     |  |                           | |             | |  |
     |  |                           | *-------------* |  |
     |  *---------------------------*-----------------*  |
     |                                                   |
     *---------------------------------------------------*

    */
        _side_widget = new SideWidget(this);

        _scroll_area = new QScrollArea(this);
        _scroll_area->setWidget(_side_widget);
        _scroll_area->setSizePolicy(_side_widget->sizePolicy());
        _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        _gl_widget = new GLWidget(this);

        centralWidget()->setLayout(new QHBoxLayout());
        centralWidget()->layout()->addWidget(_gl_widget);
        centralWidget()->layout()->addWidget(_scroll_area);

        // creating a signal slot mechanism between the rendering context and the side widget
        connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
        connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
        connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

        connect(_side_widget->data_p_combo_box,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_current_point(int)));
        // Interpolating sliders
       // connect(_side_widget->off_x_slider,SIGNAL(valueChanged(double)),_gl_widget,SLOT(_set_data_p_x(double)));
        connect(_side_widget->data_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(_set_data_p_x(double)));
        connect(_side_widget->data_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(_set_data_p_y(double)));
        connect(_side_widget->data_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(_set_data_p_z(double)));

        connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

        connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
        connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
        connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));

        connect(_side_widget->hwComboBox,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_homeworkID(int)));

        connect(_side_widget->cb0,SIGNAL(stateChanged(int)),_gl_widget,SLOT(set_d0(int)));
        connect(_side_widget->cb1,SIGNAL(stateChanged(int)),_gl_widget,SLOT(set_d1(int)));
        connect(_side_widget->cb2,SIGNAL(stateChanged(int)),_gl_widget,SLOT(set_d2(int)));


        connect(_side_widget->curve_box,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_curveID(int)));
        connect(_side_widget->model_box,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_modelID(int)));
        connect(_side_widget->colorcb,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_colorID(int)));
        connect(_side_widget->cblines,SIGNAL(stateChanged(int)),_gl_widget,SLOT(set_polyID(int)));
        connect(_side_widget->colorcb_2,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_colorID(int)));
        connect(_side_widget->surfacecb,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_surfID(int)));

        // connect(_side_widget->cbanimate,SIGNAL(stateChanged(int)),_gl_widget,SLOT(_animate()));
        // connect(_side_widget->cbnoani,SIGNAL(stateChanged(int)),_gl_widget,SLOT(_deanimate()));
        connect(_side_widget->aniBut,SIGNAL(clicked(bool)),_gl_widget,SLOT(_animate()));
        connect(_side_widget->deaniBut,SIGNAL(clicked(bool)),_gl_widget,SLOT(_deanimate()));

        /* _data_p_x+1 */
        // connect(_side_widget->bt)

        /* Shader */
        connect(_side_widget->shader_checkb,SIGNAL(stateChanged(int)),_gl_widget,SLOT(enable_shader(int)));
        connect(_side_widget->shader_comboBox,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_shader(int)));

        /* unifrom set */
        connect(_side_widget->tooncolorcb1,SIGNAL(valueChanged(double)),_gl_widget,SLOT(set_toon_color_1(double)));
        connect(_side_widget->tooncolorcb2,SIGNAL(valueChanged(double)),_gl_widget,SLOT(set_toon_color_2(double)));
        connect(_side_widget->tooncolorcb3,SIGNAL(valueChanged(double)),_gl_widget,SLOT(set_toon_color_3(double)));
        connect(_side_widget->tooncolorcb4,SIGNAL(valueChanged(double)),_gl_widget,SLOT(set_toon_color_4(double)));

        connect(_side_widget->reflectionscalingsb,SIGNAL(valueChanged(double)),_gl_widget,SLOT(set_scaling_factor(double)));
        connect(_side_widget->reflectionsmoothingsb,SIGNAL(valueChanged(double)),_gl_widget,SLOT(set_smoothing(double)));
        connect(_side_widget->reflectionshadingsb,SIGNAL(valueChanged(double)),_gl_widget,SLOT(set_shading(double)));

        connect(_gl_widget,SIGNAL(xcoordhasChanged(double)),_side_widget->data_x_spin_box,SLOT(setValue(double)));
        connect(_gl_widget,SIGNAL(ycoordhasChanged(double)),_side_widget->data_y_spin_box,SLOT(setValue(double)));
        connect(_gl_widget,SIGNAL(zcoordhasChanged(double)),_side_widget->data_z_spin_box,SLOT(setValue(double)));

        /* Patch */

        connect(_side_widget->patch_cb,SIGNAL(stateChanged(int)),_gl_widget,SLOT(set_patch_enable(int)));
        connect(_side_widget->net_cb,SIGNAL(stateChanged(int)),_gl_widget,SLOT(set_control_net(int)));

        connect(_side_widget->uiso_cb,SIGNAL(stateChanged(int)),_gl_widget,SLOT(set_uisolines(int)));
        connect(_side_widget->viso_cb,SIGNAL(stateChanged(int)),_gl_widget,SLOT(set_visolines(int)));

        connect(_side_widget->derivate_slider,SIGNAL(valueChanged(int)), _gl_widget,SLOT(set_derivative_scale(int)));



    }

    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}
