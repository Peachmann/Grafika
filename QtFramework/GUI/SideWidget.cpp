#include "SideWidget.h"
#include <iostream>

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
        hwComboBox->addItem("1 - Arc");
        hwComboBox->addItem("2 - Curve testing");
        hwComboBox->addItem("3 - Surface testing");
        hwComboBox->addItem("3 - Patch testing");

        cb0->setCheckState(Qt::Checked);
        cb1->setCheckState(Qt::Checked);
        cb2->setCheckState(Qt::Checked);

        shader_comboBox->addItem("Directional Light");
        shader_comboBox->addItem("Reflection_lines");
        shader_comboBox->addItem("Toon");
        shader_comboBox->addItem("Two sided lighting");

        arcColorBox->addItem("Red");
        arcColorBox->addItem("Green");
        arcColorBox->addItem("Blue");
        arcColorBox->addItem("Yellow");
        arcColorBox->addItem("Magenta");
        arcColorBox->addItem("Cyan");
    }
}
