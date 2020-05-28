/********************************************************************************
** Form generated from reading UI file 'SideWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEWIDGET_H
#define UI_SIDEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideWidget
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *rotate_x_slider;
    QLabel *label_2;
    QSlider *rotate_y_slider;
    QLabel *label_3;
    QSlider *rotate_z_slider;
    QLabel *label_4;
    QDoubleSpinBox *zoom_factor_spin_box;
    QLabel *label_5;
    QDoubleSpinBox *trans_x_spin_box;
    QLabel *label_6;
    QDoubleSpinBox *trans_y_spin_box;
    QLabel *label_7;
    QDoubleSpinBox *trans_z_spin_box;
    QComboBox *hwComboBox;
    QLabel *label_8;
    QTabWidget *tabWidget;
    QWidget *curves;
    QCheckBox *cb0;
    QCheckBox *cb1;
    QCheckBox *cb2;
    QComboBox *curve_box;
    QLabel *label_9;
    QSlider *derivate_slider;
    QWidget *models;
    QComboBox *model_box;
    QLabel *label_10;
    QLabel *label_11;
    QComboBox *colorcb;
    QCheckBox *cblines;
    QPushButton *deaniBut;
    QPushButton *aniBut;
    QWidget *surfaces;
    QComboBox *surfacecb;
    QLabel *label_12;
    QComboBox *colorcb_2;
    QLabel *label_13;
    QWidget *tab_3;
    QCheckBox *patch_cb;
    QCheckBox *net_cb;
    QCheckBox *uiso_cb;
    QCheckBox *viso_cb;
    QTabWidget *tabWidget_2;
    QWidget *tab;
    QLabel *label_14;
    QComboBox *data_p_combo_box;
    QDoubleSpinBox *data_z_spin_box;
    QDoubleSpinBox *data_y_spin_box;
    QDoubleSpinBox *data_x_spin_box;
    QLabel *label_17;
    QLabel *label_15;
    QLabel *label_16;
    QWidget *tab_2;
    QCheckBox *shader_checkb;
    QDoubleSpinBox *tooncolorcb2;
    QDoubleSpinBox *tooncolorcb1;
    QDoubleSpinBox *tooncolorcb3;
    QComboBox *shader_comboBox;
    QDoubleSpinBox *tooncolorcb4;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QDoubleSpinBox *reflectionscalingsb;
    QDoubleSpinBox *reflectionsmoothingsb;
    QDoubleSpinBox *reflectionshadingsb;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QString::fromUtf8("SideWidget"));
        SideWidget->resize(298, 701);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideWidget->sizePolicy().hasHeightForWidth());
        SideWidget->setSizePolicy(sizePolicy);
        SideWidget->setMinimumSize(QSize(269, 0));
        groupBox = new QGroupBox(SideWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 271, 261));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 21, 261, 261));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rotate_x_slider = new QSlider(layoutWidget);
        rotate_x_slider->setObjectName(QString::fromUtf8("rotate_x_slider"));
        rotate_x_slider->setMinimum(-180);
        rotate_x_slider->setMaximum(180);
        rotate_x_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, rotate_x_slider);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        rotate_y_slider = new QSlider(layoutWidget);
        rotate_y_slider->setObjectName(QString::fromUtf8("rotate_y_slider"));
        rotate_y_slider->setMinimum(-180);
        rotate_y_slider->setMaximum(180);
        rotate_y_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, rotate_y_slider);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rotate_z_slider = new QSlider(layoutWidget);
        rotate_z_slider->setObjectName(QString::fromUtf8("rotate_z_slider"));
        rotate_z_slider->setMinimum(-180);
        rotate_z_slider->setMaximum(180);
        rotate_z_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, rotate_z_slider);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        zoom_factor_spin_box = new QDoubleSpinBox(layoutWidget);
        zoom_factor_spin_box->setObjectName(QString::fromUtf8("zoom_factor_spin_box"));
        zoom_factor_spin_box->setDecimals(5);
        zoom_factor_spin_box->setMinimum(0.000100000000000);
        zoom_factor_spin_box->setMaximum(10000.000000000000000);
        zoom_factor_spin_box->setSingleStep(0.100000000000000);
        zoom_factor_spin_box->setValue(1.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, zoom_factor_spin_box);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        trans_x_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_x_spin_box->setObjectName(QString::fromUtf8("trans_x_spin_box"));
        trans_x_spin_box->setMinimum(-100.000000000000000);
        trans_x_spin_box->setMaximum(100.000000000000000);
        trans_x_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(4, QFormLayout::FieldRole, trans_x_spin_box);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        trans_y_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_y_spin_box->setObjectName(QString::fromUtf8("trans_y_spin_box"));
        trans_y_spin_box->setMinimum(-100.000000000000000);
        trans_y_spin_box->setMaximum(100.000000000000000);
        trans_y_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, trans_y_spin_box);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        trans_z_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_z_spin_box->setObjectName(QString::fromUtf8("trans_z_spin_box"));
        trans_z_spin_box->setMinimum(-100.000000000000000);
        trans_z_spin_box->setMaximum(100.000000000000000);
        trans_z_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(6, QFormLayout::FieldRole, trans_z_spin_box);

        hwComboBox = new QComboBox(layoutWidget);
        hwComboBox->setObjectName(QString::fromUtf8("hwComboBox"));

        formLayout->setWidget(7, QFormLayout::FieldRole, hwComboBox);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_8);

        tabWidget = new QTabWidget(SideWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(10, 280, 261, 141));
        curves = new QWidget();
        curves->setObjectName(QString::fromUtf8("curves"));
        cb0 = new QCheckBox(curves);
        cb0->setObjectName(QString::fromUtf8("cb0"));
        cb0->setGeometry(QRect(10, 0, 70, 17));
        cb1 = new QCheckBox(curves);
        cb1->setObjectName(QString::fromUtf8("cb1"));
        cb1->setGeometry(QRect(10, 20, 70, 17));
        cb2 = new QCheckBox(curves);
        cb2->setObjectName(QString::fromUtf8("cb2"));
        cb2->setGeometry(QRect(10, 40, 70, 17));
        curve_box = new QComboBox(curves);
        curve_box->setObjectName(QString::fromUtf8("curve_box"));
        curve_box->setGeometry(QRect(80, 40, 151, 21));
        label_9 = new QLabel(curves);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(120, 10, 91, 16));
        derivate_slider = new QSlider(curves);
        derivate_slider->setObjectName(QString::fromUtf8("derivate_slider"));
        derivate_slider->setGeometry(QRect(80, 80, 160, 22));
        derivate_slider->setSliderPosition(99);
        derivate_slider->setOrientation(Qt::Horizontal);
        tabWidget->addTab(curves, QString());
        models = new QWidget();
        models->setObjectName(QString::fromUtf8("models"));
        model_box = new QComboBox(models);
        model_box->setObjectName(QString::fromUtf8("model_box"));
        model_box->setGeometry(QRect(70, 60, 171, 22));
        label_10 = new QLabel(models);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 60, 47, 13));
        label_11 = new QLabel(models);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 90, 47, 13));
        colorcb = new QComboBox(models);
        colorcb->setObjectName(QString::fromUtf8("colorcb"));
        colorcb->setGeometry(QRect(70, 90, 171, 22));
        cblines = new QCheckBox(models);
        cblines->setObjectName(QString::fromUtf8("cblines"));
        cblines->setGeometry(QRect(190, 20, 70, 17));
        deaniBut = new QPushButton(models);
        deaniBut->setObjectName(QString::fromUtf8("deaniBut"));
        deaniBut->setGeometry(QRect(100, 20, 75, 23));
        aniBut = new QPushButton(models);
        aniBut->setObjectName(QString::fromUtf8("aniBut"));
        aniBut->setGeometry(QRect(10, 20, 75, 23));
        tabWidget->addTab(models, QString());
        surfaces = new QWidget();
        surfaces->setObjectName(QString::fromUtf8("surfaces"));
        surfacecb = new QComboBox(surfaces);
        surfacecb->setObjectName(QString::fromUtf8("surfacecb"));
        surfacecb->setGeometry(QRect(90, 20, 121, 22));
        label_12 = new QLabel(surfaces);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 20, 47, 13));
        colorcb_2 = new QComboBox(surfaces);
        colorcb_2->setObjectName(QString::fromUtf8("colorcb_2"));
        colorcb_2->setGeometry(QRect(90, 60, 121, 22));
        label_13 = new QLabel(surfaces);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 60, 47, 13));
        tabWidget->addTab(surfaces, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        patch_cb = new QCheckBox(tab_3);
        patch_cb->setObjectName(QString::fromUtf8("patch_cb"));
        patch_cb->setGeometry(QRect(10, 10, 70, 17));
        patch_cb->setChecked(true);
        net_cb = new QCheckBox(tab_3);
        net_cb->setObjectName(QString::fromUtf8("net_cb"));
        net_cb->setGeometry(QRect(10, 40, 81, 17));
        net_cb->setChecked(true);
        uiso_cb = new QCheckBox(tab_3);
        uiso_cb->setObjectName(QString::fromUtf8("uiso_cb"));
        uiso_cb->setGeometry(QRect(110, 10, 70, 17));
        viso_cb = new QCheckBox(tab_3);
        viso_cb->setObjectName(QString::fromUtf8("viso_cb"));
        viso_cb->setGeometry(QRect(110, 40, 70, 17));
        tabWidget->addTab(tab_3, QString());
        tabWidget_2 = new QTabWidget(SideWidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(10, 440, 261, 221));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_14 = new QLabel(tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 10, 61, 20));
        data_p_combo_box = new QComboBox(tab);
        data_p_combo_box->setObjectName(QString::fromUtf8("data_p_combo_box"));
        data_p_combo_box->setGeometry(QRect(110, 10, 69, 22));
        data_z_spin_box = new QDoubleSpinBox(tab);
        data_z_spin_box->setObjectName(QString::fromUtf8("data_z_spin_box"));
        data_z_spin_box->setGeometry(QRect(90, 150, 111, 22));
        data_z_spin_box->setMinimum(-5.000000000000000);
        data_z_spin_box->setMaximum(5.000000000000000);
        data_z_spin_box->setSingleStep(0.500000000000000);
        data_y_spin_box = new QDoubleSpinBox(tab);
        data_y_spin_box->setObjectName(QString::fromUtf8("data_y_spin_box"));
        data_y_spin_box->setGeometry(QRect(90, 110, 111, 22));
        data_y_spin_box->setMinimum(-5.000000000000000);
        data_y_spin_box->setMaximum(5.000000000000000);
        data_y_spin_box->setSingleStep(0.500000000000000);
        data_x_spin_box = new QDoubleSpinBox(tab);
        data_x_spin_box->setObjectName(QString::fromUtf8("data_x_spin_box"));
        data_x_spin_box->setGeometry(QRect(90, 70, 111, 22));
        data_x_spin_box->setMinimum(-5.000000000000000);
        data_x_spin_box->setMaximum(5.000000000000000);
        data_x_spin_box->setSingleStep(0.500000000000000);
        label_17 = new QLabel(tab);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 150, 47, 13));
        label_15 = new QLabel(tab);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 80, 47, 13));
        label_16 = new QLabel(tab);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 110, 47, 13));
        tabWidget_2->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        shader_checkb = new QCheckBox(tab_2);
        shader_checkb->setObjectName(QString::fromUtf8("shader_checkb"));
        shader_checkb->setGeometry(QRect(0, 10, 70, 17));
        tooncolorcb2 = new QDoubleSpinBox(tab_2);
        tooncolorcb2->setObjectName(QString::fromUtf8("tooncolorcb2"));
        tooncolorcb2->setGeometry(QRect(60, 90, 51, 22));
        tooncolorcb2->setMaximum(1.000000000000000);
        tooncolorcb2->setSingleStep(0.100000000000000);
        tooncolorcb1 = new QDoubleSpinBox(tab_2);
        tooncolorcb1->setObjectName(QString::fromUtf8("tooncolorcb1"));
        tooncolorcb1->setGeometry(QRect(0, 90, 51, 22));
        tooncolorcb1->setMaximum(1.000000000000000);
        tooncolorcb1->setSingleStep(0.100000000000000);
        tooncolorcb3 = new QDoubleSpinBox(tab_2);
        tooncolorcb3->setObjectName(QString::fromUtf8("tooncolorcb3"));
        tooncolorcb3->setGeometry(QRect(120, 90, 51, 22));
        tooncolorcb3->setMaximum(1.000000000000000);
        tooncolorcb3->setSingleStep(0.100000000000000);
        shader_comboBox = new QComboBox(tab_2);
        shader_comboBox->setObjectName(QString::fromUtf8("shader_comboBox"));
        shader_comboBox->setGeometry(QRect(90, 10, 111, 22));
        tooncolorcb4 = new QDoubleSpinBox(tab_2);
        tooncolorcb4->setObjectName(QString::fromUtf8("tooncolorcb4"));
        tooncolorcb4->setGeometry(QRect(180, 90, 51, 22));
        tooncolorcb4->setMaximum(1.000000000000000);
        tooncolorcb4->setSingleStep(0.100000000000000);
        label_18 = new QLabel(tab_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(20, 70, 16, 16));
        label_19 = new QLabel(tab_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(80, 70, 16, 16));
        label_20 = new QLabel(tab_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(140, 70, 16, 16));
        label_21 = new QLabel(tab_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(200, 70, 16, 16));
        reflectionscalingsb = new QDoubleSpinBox(tab_2);
        reflectionscalingsb->setObjectName(QString::fromUtf8("reflectionscalingsb"));
        reflectionscalingsb->setGeometry(QRect(0, 160, 61, 22));
        reflectionscalingsb->setMaximum(100.000000000000000);
        reflectionscalingsb->setSingleStep(0.500000000000000);
        reflectionsmoothingsb = new QDoubleSpinBox(tab_2);
        reflectionsmoothingsb->setObjectName(QString::fromUtf8("reflectionsmoothingsb"));
        reflectionsmoothingsb->setGeometry(QRect(90, 160, 51, 22));
        reflectionsmoothingsb->setMaximum(100.000000000000000);
        reflectionsmoothingsb->setSingleStep(0.500000000000000);
        reflectionshadingsb = new QDoubleSpinBox(tab_2);
        reflectionshadingsb->setObjectName(QString::fromUtf8("reflectionshadingsb"));
        reflectionshadingsb->setGeometry(QRect(180, 160, 51, 22));
        reflectionshadingsb->setMaximum(100.000000000000000);
        reflectionshadingsb->setSingleStep(0.500000000000000);
        label_22 = new QLabel(tab_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(0, 140, 61, 16));
        label_23 = new QLabel(tab_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(90, 140, 51, 16));
        label_24 = new QLabel(tab_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(180, 140, 47, 13));
        tabWidget_2->addTab(tab_2, QString());
#if QT_CONFIG(shortcut)
        label->setBuddy(rotate_x_slider);
        label_2->setBuddy(rotate_y_slider);
        label_3->setBuddy(rotate_z_slider);
        label_4->setBuddy(zoom_factor_spin_box);
        label_5->setBuddy(trans_x_spin_box);
        label_6->setBuddy(trans_y_spin_box);
        label_7->setBuddy(trans_z_spin_box);
        label_8->setBuddy(hwComboBox);
#endif // QT_CONFIG(shortcut)

        retranslateUi(SideWidget);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SideWidget);
    } // setupUi

    void retranslateUi(QWidget *SideWidget)
    {
        SideWidget->setWindowTitle(QCoreApplication::translate("SideWidget", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SideWidget", "Transformations", nullptr));
        label->setText(QCoreApplication::translate("SideWidget", "Rotate around x", nullptr));
        label_2->setText(QCoreApplication::translate("SideWidget", "Rotate around y", nullptr));
        label_3->setText(QCoreApplication::translate("SideWidget", "Rotate around z", nullptr));
        label_4->setText(QCoreApplication::translate("SideWidget", "Zoom factor", nullptr));
#if QT_CONFIG(tooltip)
        zoom_factor_spin_box->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("SideWidget", "Translate along x", nullptr));
        label_6->setText(QCoreApplication::translate("SideWidget", "Translate along y", nullptr));
        label_7->setText(QCoreApplication::translate("SideWidget", "Translate along z", nullptr));
        label_8->setText(QCoreApplication::translate("SideWidget", "homework", nullptr));
        cb0->setText(QCoreApplication::translate("SideWidget", "d0", nullptr));
        cb1->setText(QCoreApplication::translate("SideWidget", "d1", nullptr));
        cb2->setText(QCoreApplication::translate("SideWidget", "d2", nullptr));
        label_9->setText(QCoreApplication::translate("SideWidget", "Curve", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(curves), QCoreApplication::translate("SideWidget", "Curves", nullptr));
        label_10->setText(QCoreApplication::translate("SideWidget", "Model", nullptr));
        label_11->setText(QCoreApplication::translate("SideWidget", "Color", nullptr));
        cblines->setText(QCoreApplication::translate("SideWidget", "Lines", nullptr));
        deaniBut->setText(QCoreApplication::translate("SideWidget", "Deanimate", nullptr));
        aniBut->setText(QCoreApplication::translate("SideWidget", "Animate", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(models), QCoreApplication::translate("SideWidget", "Models", nullptr));
        label_12->setText(QCoreApplication::translate("SideWidget", "Surface", nullptr));
        label_13->setText(QCoreApplication::translate("SideWidget", "Color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(surfaces), QCoreApplication::translate("SideWidget", "Surfaces", nullptr));
        patch_cb->setText(QCoreApplication::translate("SideWidget", "Patch", nullptr));
        net_cb->setText(QCoreApplication::translate("SideWidget", "Control net", nullptr));
        uiso_cb->setText(QCoreApplication::translate("SideWidget", "U-Isolines", nullptr));
        viso_cb->setText(QCoreApplication::translate("SideWidget", "V-Isolines", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("SideWidget", "Patch", nullptr));
        label_14->setText(QCoreApplication::translate("SideWidget", "Select Point", nullptr));
        label_17->setText(QCoreApplication::translate("SideWidget", "Z offset", nullptr));
        label_15->setText(QCoreApplication::translate("SideWidget", "X offset", nullptr));
        label_16->setText(QCoreApplication::translate("SideWidget", "Y offset", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QCoreApplication::translate("SideWidget", "Interpolating", nullptr));
        shader_checkb->setText(QCoreApplication::translate("SideWidget", "Shaders", nullptr));
        label_18->setText(QCoreApplication::translate("SideWidget", "R", nullptr));
        label_19->setText(QCoreApplication::translate("SideWidget", "G", nullptr));
        label_20->setText(QCoreApplication::translate("SideWidget", "B", nullptr));
        label_21->setText(QCoreApplication::translate("SideWidget", "A", nullptr));
        label_22->setText(QCoreApplication::translate("SideWidget", "Scale Factor", nullptr));
        label_23->setText(QCoreApplication::translate("SideWidget", "Smoothing", nullptr));
        label_24->setText(QCoreApplication::translate("SideWidget", "Shading", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QCoreApplication::translate("SideWidget", "Shaders", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H
