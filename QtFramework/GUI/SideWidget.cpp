#include "SideWidget.h"

namespace cagd
{
    SideWidget::SideWidget(QWidget *parent): QWidget(parent)
    {
        setupUi(this);

        QPalette p = rotate_x_slider->palette();

        p.setColor(QPalette::Highlight, QColor(255,50,10).lighter());

        rotate_x_slider->setPalette(p);

        p = rotate_y_slider->palette();

        p.setColor(QPalette::Highlight, QColor(50,255,10).lighter());

        rotate_y_slider->setPalette(p);

        hwComboBox->addItem("0 - Patch");
        hwComboBox->addItem("1 - Cyclic Curve");
        hwComboBox->addItem("2 - Parametric Curves ");
        hwComboBox->addItem("3 - Models");
        hwComboBox->addItem("3 - Playground");
        hwComboBox->addItem("3 - Surfaces");
        hwComboBox->addItem("4 - Interpolating Cyclic Curve");
        hwComboBox->addItem("5 - Arc");

        curve_box->addItem("Spiral on cone");
        curve_box->addItem("Torus Knot");
        curve_box->addItem("Helix");
        curve_box->addItem("Ellipse");
        curve_box->addItem("Hipocycloid");
        curve_box->addItem("Epicycloid");
        curve_box->addItem("Rose");

        cb0->setCheckState(Qt::Checked);
        cb1->setCheckState(Qt::Checked);
        cb2->setCheckState(Qt::Checked);

        model_box->addItem("Mouse");
        model_box->addItem("Angel");
        model_box->addItem("Cube");

        model_box->addItem("Bird");
        model_box->addItem("Bug");
        model_box->addItem("Cone");

        model_box->addItem("Dragon");
        model_box->addItem("Elephant");
        model_box->addItem("Gangster");

        model_box->addItem("Goblet");
        model_box->addItem("Horse");
        model_box->addItem("Icosahedron");

        model_box->addItem("Seashell");
        model_box->addItem("Space Station");
        model_box->addItem("Sphere");

        model_box->addItem("Sphot");
        model_box->addItem("Star");

        colorcb->addItem("Brass");
        colorcb->addItem("Gold");
        colorcb->addItem("Silver");
        colorcb->addItem("Emerald");
        colorcb->addItem("Pearl");
        colorcb->addItem("Ruby");
        colorcb->addItem("Turqoise");

        colorcb_2->addItem("Brass");
        colorcb_2->addItem("Gold");
        colorcb_2->addItem("Silver");
        colorcb_2->addItem("Emerald");
        colorcb_2->addItem("Pearl");
        colorcb_2->addItem("Ruby");
        colorcb_2->addItem("Turqoise");

        surfacecb->addItem("Screw");
        surfacecb->addItem("Cylinder");
        surfacecb->addItem("Torus");
        surfacecb->addItem("Sphere");
        surfacecb->addItem("Cone");
        surfacecb->addItem("Parabolic");

        data_p_combo_box->addItem("0");
        data_p_combo_box->addItem("1");
        data_p_combo_box->addItem("2");
        data_p_combo_box->addItem("3");
        data_p_combo_box->addItem("4");

        shader_comboBox->addItem("Directional Light");
        shader_comboBox->addItem("Reflection_lines");
        shader_comboBox->addItem("Toon");
        shader_comboBox->addItem("Two sided lighting");
    }
}
