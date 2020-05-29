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
    QWidget *Various;
    QCheckBox *cb0;
    QCheckBox *cb1;
    QCheckBox *cb2;
    QCheckBox *uiso_cb;
    QCheckBox *viso_cb;
    QCheckBox *net_cb;
    QCheckBox *patch_cb;
    QWidget *tab;
    QDoubleSpinBox *reflectionscalingsb;
    QDoubleSpinBox *tooncolorcb2;
    QLabel *label_20;
    QLabel *label_22;
    QDoubleSpinBox *tooncolorcb3;
    QLabel *label_21;
    QDoubleSpinBox *tooncolorcb4;
    QLabel *label_19;
    QLabel *label_24;
    QDoubleSpinBox *tooncolorcb1;
    QLabel *label_23;
    QComboBox *shader_comboBox;
    QDoubleSpinBox *reflectionsmoothingsb;
    QDoubleSpinBox *reflectionshadingsb;
    QCheckBox *shader_checkb;
    QLabel *label_18;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QPushButton *addArc;
    QComboBox *arcColorBox;
    QLabel *label_9;
    QLabel *label_10;
    QComboBox *deleteArcBox;
    QPushButton *deleteArc;
    QLabel *label_11;
    QComboBox *selectArc1;
    QLabel *label_13;
    QComboBox *selectArc2;
    QLabel *label_12;
    QComboBox *arcMaterial;
    QLabel *label_14;
    QLabel *label_15;
    QComboBox *directionArc1;
    QComboBox *directionArc2;
    QComboBox *vertexArc1;
    QComboBox *vertexArc2;
    QLabel *label_16;
    QComboBox *operationBox;
    QPushButton *doArcOperation;
    QWidget *tab_5;
    QComboBox *selectDirection1;
    QLabel *label_17;
    QPushButton *addPatch;
    QPushButton *deletePatch;
    QComboBox *patchColorBox;
    QComboBox *deletePatchBox;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QComboBox *selectPatch2;
    QComboBox *selectPatch1;
    QPushButton *doPatchOperation;
    QComboBox *selectPatchVertex2;
    QComboBox *selectPatchMaterial;
    QComboBox *patchOperation;
    QComboBox *selectPatchVertex1;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_39;
    QComboBox *selectDirection2;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QString::fromUtf8("SideWidget"));
        SideWidget->resize(298, 775);
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
        layoutWidget->setGeometry(QRect(3, 21, 261, 231));
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
        tabWidget->setGeometry(QRect(10, 280, 261, 181));
        Various = new QWidget();
        Various->setObjectName(QString::fromUtf8("Various"));
        cb0 = new QCheckBox(Various);
        cb0->setObjectName(QString::fromUtf8("cb0"));
        cb0->setGeometry(QRect(10, 0, 121, 21));
        cb1 = new QCheckBox(Various);
        cb1->setObjectName(QString::fromUtf8("cb1"));
        cb1->setGeometry(QRect(10, 20, 121, 31));
        cb2 = new QCheckBox(Various);
        cb2->setObjectName(QString::fromUtf8("cb2"));
        cb2->setGeometry(QRect(10, 50, 121, 21));
        uiso_cb = new QCheckBox(Various);
        uiso_cb->setObjectName(QString::fromUtf8("uiso_cb"));
        uiso_cb->setGeometry(QRect(150, 0, 71, 21));
        viso_cb = new QCheckBox(Various);
        viso_cb->setObjectName(QString::fromUtf8("viso_cb"));
        viso_cb->setGeometry(QRect(150, 30, 70, 17));
        net_cb = new QCheckBox(Various);
        net_cb->setObjectName(QString::fromUtf8("net_cb"));
        net_cb->setGeometry(QRect(150, 50, 91, 31));
        net_cb->setChecked(true);
        patch_cb = new QCheckBox(Various);
        patch_cb->setObjectName(QString::fromUtf8("patch_cb"));
        patch_cb->setGeometry(QRect(150, 80, 70, 17));
        patch_cb->setChecked(true);
        tabWidget->addTab(Various, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        reflectionscalingsb = new QDoubleSpinBox(tab);
        reflectionscalingsb->setObjectName(QString::fromUtf8("reflectionscalingsb"));
        reflectionscalingsb->setGeometry(QRect(10, 120, 61, 22));
        reflectionscalingsb->setMaximum(100.000000000000000);
        reflectionscalingsb->setSingleStep(0.500000000000000);
        tooncolorcb2 = new QDoubleSpinBox(tab);
        tooncolorcb2->setObjectName(QString::fromUtf8("tooncolorcb2"));
        tooncolorcb2->setGeometry(QRect(70, 70, 51, 22));
        tooncolorcb2->setMaximum(1.000000000000000);
        tooncolorcb2->setSingleStep(0.100000000000000);
        label_20 = new QLabel(tab);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(150, 50, 16, 16));
        label_22 = new QLabel(tab);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(10, 100, 61, 16));
        tooncolorcb3 = new QDoubleSpinBox(tab);
        tooncolorcb3->setObjectName(QString::fromUtf8("tooncolorcb3"));
        tooncolorcb3->setGeometry(QRect(130, 70, 51, 22));
        tooncolorcb3->setMaximum(1.000000000000000);
        tooncolorcb3->setSingleStep(0.100000000000000);
        label_21 = new QLabel(tab);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(210, 50, 16, 16));
        tooncolorcb4 = new QDoubleSpinBox(tab);
        tooncolorcb4->setObjectName(QString::fromUtf8("tooncolorcb4"));
        tooncolorcb4->setGeometry(QRect(190, 70, 51, 22));
        tooncolorcb4->setMaximum(1.000000000000000);
        tooncolorcb4->setSingleStep(0.100000000000000);
        label_19 = new QLabel(tab);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(90, 50, 16, 16));
        label_24 = new QLabel(tab);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(190, 100, 47, 13));
        tooncolorcb1 = new QDoubleSpinBox(tab);
        tooncolorcb1->setObjectName(QString::fromUtf8("tooncolorcb1"));
        tooncolorcb1->setGeometry(QRect(10, 70, 51, 22));
        tooncolorcb1->setMaximum(1.000000000000000);
        tooncolorcb1->setSingleStep(0.100000000000000);
        label_23 = new QLabel(tab);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(100, 100, 51, 16));
        shader_comboBox = new QComboBox(tab);
        shader_comboBox->setObjectName(QString::fromUtf8("shader_comboBox"));
        shader_comboBox->setGeometry(QRect(100, 20, 111, 22));
        reflectionsmoothingsb = new QDoubleSpinBox(tab);
        reflectionsmoothingsb->setObjectName(QString::fromUtf8("reflectionsmoothingsb"));
        reflectionsmoothingsb->setGeometry(QRect(100, 120, 51, 22));
        reflectionsmoothingsb->setMaximum(100.000000000000000);
        reflectionsmoothingsb->setSingleStep(0.500000000000000);
        reflectionshadingsb = new QDoubleSpinBox(tab);
        reflectionshadingsb->setObjectName(QString::fromUtf8("reflectionshadingsb"));
        reflectionshadingsb->setGeometry(QRect(190, 120, 51, 22));
        reflectionshadingsb->setMaximum(100.000000000000000);
        reflectionshadingsb->setSingleStep(0.500000000000000);
        shader_checkb = new QCheckBox(tab);
        shader_checkb->setObjectName(QString::fromUtf8("shader_checkb"));
        shader_checkb->setGeometry(QRect(10, 20, 70, 17));
        label_18 = new QLabel(tab);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(30, 50, 16, 16));
        tabWidget->addTab(tab, QString());
        tabWidget_2 = new QTabWidget(SideWidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(10, 470, 271, 301));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        addArc = new QPushButton(tab_3);
        addArc->setObjectName(QString::fromUtf8("addArc"));
        addArc->setGeometry(QRect(180, 10, 75, 23));
        arcColorBox = new QComboBox(tab_3);
        arcColorBox->setObjectName(QString::fromUtf8("arcColorBox"));
        arcColorBox->setGeometry(QRect(70, 10, 81, 22));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(0, 10, 61, 21));
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(tab_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 40, 61, 21));
        label_10->setAlignment(Qt::AlignCenter);
        deleteArcBox = new QComboBox(tab_3);
        deleteArcBox->setObjectName(QString::fromUtf8("deleteArcBox"));
        deleteArcBox->setGeometry(QRect(70, 40, 81, 22));
        deleteArc = new QPushButton(tab_3);
        deleteArc->setObjectName(QString::fromUtf8("deleteArc"));
        deleteArc->setGeometry(QRect(180, 40, 75, 23));
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 80, 91, 21));
        label_11->setAlignment(Qt::AlignCenter);
        selectArc1 = new QComboBox(tab_3);
        selectArc1->setObjectName(QString::fromUtf8("selectArc1"));
        selectArc1->setGeometry(QRect(100, 80, 71, 22));
        label_13 = new QLabel(tab_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(0, 110, 91, 21));
        label_13->setAlignment(Qt::AlignCenter);
        selectArc2 = new QComboBox(tab_3);
        selectArc2->setObjectName(QString::fromUtf8("selectArc2"));
        selectArc2->setGeometry(QRect(100, 110, 71, 22));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(0, 140, 81, 21));
        label_12->setAlignment(Qt::AlignCenter);
        arcMaterial = new QComboBox(tab_3);
        arcMaterial->addItem(QString());
        arcMaterial->addItem(QString());
        arcMaterial->addItem(QString());
        arcMaterial->addItem(QString());
        arcMaterial->addItem(QString());
        arcMaterial->addItem(QString());
        arcMaterial->addItem(QString());
        arcMaterial->setObjectName(QString::fromUtf8("arcMaterial"));
        arcMaterial->setGeometry(QRect(100, 140, 71, 22));
        label_14 = new QLabel(tab_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(0, 170, 81, 21));
        label_14->setAlignment(Qt::AlignCenter);
        label_15 = new QLabel(tab_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(0, 200, 81, 21));
        label_15->setAlignment(Qt::AlignCenter);
        directionArc1 = new QComboBox(tab_3);
        directionArc1->addItem(QString());
        directionArc1->addItem(QString());
        directionArc1->setObjectName(QString::fromUtf8("directionArc1"));
        directionArc1->setGeometry(QRect(180, 80, 71, 22));
        directionArc2 = new QComboBox(tab_3);
        directionArc2->addItem(QString());
        directionArc2->addItem(QString());
        directionArc2->setObjectName(QString::fromUtf8("directionArc2"));
        directionArc2->setGeometry(QRect(180, 110, 71, 22));
        vertexArc1 = new QComboBox(tab_3);
        vertexArc1->setObjectName(QString::fromUtf8("vertexArc1"));
        vertexArc1->setGeometry(QRect(100, 170, 71, 22));
        vertexArc2 = new QComboBox(tab_3);
        vertexArc2->setObjectName(QString::fromUtf8("vertexArc2"));
        vertexArc2->setGeometry(QRect(100, 200, 71, 22));
        label_16 = new QLabel(tab_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(0, 230, 81, 21));
        label_16->setAlignment(Qt::AlignCenter);
        operationBox = new QComboBox(tab_3);
        operationBox->addItem(QString());
        operationBox->addItem(QString());
        operationBox->addItem(QString());
        operationBox->addItem(QString());
        operationBox->addItem(QString());
        operationBox->setObjectName(QString::fromUtf8("operationBox"));
        operationBox->setGeometry(QRect(90, 230, 91, 22));
        doArcOperation = new QPushButton(tab_3);
        doArcOperation->setObjectName(QString::fromUtf8("doArcOperation"));
        doArcOperation->setGeometry(QRect(194, 230, 61, 23));
        tabWidget_2->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        selectDirection1 = new QComboBox(tab_5);
        selectDirection1->addItem(QString());
        selectDirection1->addItem(QString());
        selectDirection1->addItem(QString());
        selectDirection1->addItem(QString());
        selectDirection1->addItem(QString());
        selectDirection1->addItem(QString());
        selectDirection1->addItem(QString());
        selectDirection1->addItem(QString());
        selectDirection1->setObjectName(QString::fromUtf8("selectDirection1"));
        selectDirection1->setGeometry(QRect(180, 80, 71, 22));
        label_17 = new QLabel(tab_5);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(0, 40, 61, 21));
        label_17->setAlignment(Qt::AlignCenter);
        addPatch = new QPushButton(tab_5);
        addPatch->setObjectName(QString::fromUtf8("addPatch"));
        addPatch->setGeometry(QRect(180, 10, 75, 23));
        deletePatch = new QPushButton(tab_5);
        deletePatch->setObjectName(QString::fromUtf8("deletePatch"));
        deletePatch->setGeometry(QRect(180, 40, 75, 23));
        patchColorBox = new QComboBox(tab_5);
        patchColorBox->addItem(QString());
        patchColorBox->addItem(QString());
        patchColorBox->addItem(QString());
        patchColorBox->addItem(QString());
        patchColorBox->addItem(QString());
        patchColorBox->addItem(QString());
        patchColorBox->setObjectName(QString::fromUtf8("patchColorBox"));
        patchColorBox->setGeometry(QRect(70, 10, 81, 22));
        deletePatchBox = new QComboBox(tab_5);
        deletePatchBox->setObjectName(QString::fromUtf8("deletePatchBox"));
        deletePatchBox->setGeometry(QRect(70, 40, 81, 22));
        label_32 = new QLabel(tab_5);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(0, 10, 61, 21));
        label_32->setAlignment(Qt::AlignCenter);
        label_33 = new QLabel(tab_5);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(0, 80, 101, 21));
        label_33->setAlignment(Qt::AlignCenter);
        label_34 = new QLabel(tab_5);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(0, 110, 101, 21));
        label_34->setAlignment(Qt::AlignCenter);
        selectPatch2 = new QComboBox(tab_5);
        selectPatch2->setObjectName(QString::fromUtf8("selectPatch2"));
        selectPatch2->setGeometry(QRect(100, 110, 71, 22));
        selectPatch1 = new QComboBox(tab_5);
        selectPatch1->setObjectName(QString::fromUtf8("selectPatch1"));
        selectPatch1->setGeometry(QRect(100, 80, 71, 22));
        doPatchOperation = new QPushButton(tab_5);
        doPatchOperation->setObjectName(QString::fromUtf8("doPatchOperation"));
        doPatchOperation->setGeometry(QRect(194, 230, 61, 23));
        selectPatchVertex2 = new QComboBox(tab_5);
        selectPatchVertex2->setObjectName(QString::fromUtf8("selectPatchVertex2"));
        selectPatchVertex2->setGeometry(QRect(100, 200, 71, 22));
        selectPatchMaterial = new QComboBox(tab_5);
        selectPatchMaterial->addItem(QString());
        selectPatchMaterial->addItem(QString());
        selectPatchMaterial->addItem(QString());
        selectPatchMaterial->addItem(QString());
        selectPatchMaterial->addItem(QString());
        selectPatchMaterial->addItem(QString());
        selectPatchMaterial->addItem(QString());
        selectPatchMaterial->setObjectName(QString::fromUtf8("selectPatchMaterial"));
        selectPatchMaterial->setGeometry(QRect(100, 140, 71, 22));
        patchOperation = new QComboBox(tab_5);
        patchOperation->addItem(QString());
        patchOperation->addItem(QString());
        patchOperation->addItem(QString());
        patchOperation->addItem(QString());
        patchOperation->addItem(QString());
        patchOperation->setObjectName(QString::fromUtf8("patchOperation"));
        patchOperation->setGeometry(QRect(90, 230, 91, 22));
        selectPatchVertex1 = new QComboBox(tab_5);
        selectPatchVertex1->setObjectName(QString::fromUtf8("selectPatchVertex1"));
        selectPatchVertex1->setGeometry(QRect(100, 170, 71, 22));
        label_35 = new QLabel(tab_5);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(0, 170, 91, 21));
        label_35->setAlignment(Qt::AlignCenter);
        label_36 = new QLabel(tab_5);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(0, 230, 81, 21));
        label_36->setAlignment(Qt::AlignCenter);
        label_37 = new QLabel(tab_5);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(0, 140, 81, 21));
        label_37->setAlignment(Qt::AlignCenter);
        label_39 = new QLabel(tab_5);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(0, 200, 91, 21));
        label_39->setAlignment(Qt::AlignCenter);
        selectDirection2 = new QComboBox(tab_5);
        selectDirection2->addItem(QString());
        selectDirection2->addItem(QString());
        selectDirection2->addItem(QString());
        selectDirection2->addItem(QString());
        selectDirection2->addItem(QString());
        selectDirection2->addItem(QString());
        selectDirection2->addItem(QString());
        selectDirection2->addItem(QString());
        selectDirection2->setObjectName(QString::fromUtf8("selectDirection2"));
        selectDirection2->setGeometry(QRect(180, 110, 71, 22));
        tabWidget_2->addTab(tab_5, QString());
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

        tabWidget->setCurrentIndex(1);
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
        label_8->setText(QCoreApplication::translate("SideWidget", "Homework", nullptr));
        cb0->setText(QCoreApplication::translate("SideWidget", "Show 0th derivative", nullptr));
        cb1->setText(QCoreApplication::translate("SideWidget", "Show 1st derivative", nullptr));
        cb2->setText(QCoreApplication::translate("SideWidget", "Show 2nd derivative", nullptr));
        uiso_cb->setText(QCoreApplication::translate("SideWidget", "U-Isolines", nullptr));
        viso_cb->setText(QCoreApplication::translate("SideWidget", "V-Isolines", nullptr));
        net_cb->setText(QCoreApplication::translate("SideWidget", "Control net", nullptr));
        patch_cb->setText(QCoreApplication::translate("SideWidget", "Patch", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Various), QCoreApplication::translate("SideWidget", "Various", nullptr));
        label_20->setText(QCoreApplication::translate("SideWidget", "B", nullptr));
        label_22->setText(QCoreApplication::translate("SideWidget", "Scale Factor", nullptr));
        label_21->setText(QCoreApplication::translate("SideWidget", "A", nullptr));
        label_19->setText(QCoreApplication::translate("SideWidget", "G", nullptr));
        label_24->setText(QCoreApplication::translate("SideWidget", "Shading", nullptr));
        label_23->setText(QCoreApplication::translate("SideWidget", "Smoothing", nullptr));
        shader_checkb->setText(QCoreApplication::translate("SideWidget", "Shaders", nullptr));
        label_18->setText(QCoreApplication::translate("SideWidget", "R", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SideWidget", "Shaders", nullptr));
        addArc->setText(QCoreApplication::translate("SideWidget", "Add arc", nullptr));
        label_9->setText(QCoreApplication::translate("SideWidget", "Color", nullptr));
        label_10->setText(QCoreApplication::translate("SideWidget", "Select arc", nullptr));
        deleteArc->setText(QCoreApplication::translate("SideWidget", "Delete arc", nullptr));
        label_11->setText(QCoreApplication::translate("SideWidget", "Select arc 1 / Dir.", nullptr));
        label_13->setText(QCoreApplication::translate("SideWidget", "Select arc 2 / Dir.", nullptr));
        label_12->setText(QCoreApplication::translate("SideWidget", "Material", nullptr));
        arcMaterial->setItemText(0, QCoreApplication::translate("SideWidget", "Brass", nullptr));
        arcMaterial->setItemText(1, QCoreApplication::translate("SideWidget", "Gold", nullptr));
        arcMaterial->setItemText(2, QCoreApplication::translate("SideWidget", "Silver", nullptr));
        arcMaterial->setItemText(3, QCoreApplication::translate("SideWidget", "Emerald", nullptr));
        arcMaterial->setItemText(4, QCoreApplication::translate("SideWidget", "Pearl", nullptr));
        arcMaterial->setItemText(5, QCoreApplication::translate("SideWidget", "Ruby", nullptr));
        arcMaterial->setItemText(6, QCoreApplication::translate("SideWidget", "Turquoise", nullptr));

        label_14->setText(QCoreApplication::translate("SideWidget", "Vertex of arc 1", nullptr));
        label_15->setText(QCoreApplication::translate("SideWidget", "Vertex of arc 2", nullptr));
        directionArc1->setItemText(0, QCoreApplication::translate("SideWidget", "Left", nullptr));
        directionArc1->setItemText(1, QCoreApplication::translate("SideWidget", "Right", nullptr));

        directionArc2->setItemText(0, QCoreApplication::translate("SideWidget", "Left", nullptr));
        directionArc2->setItemText(1, QCoreApplication::translate("SideWidget", "Right", nullptr));

        label_16->setText(QCoreApplication::translate("SideWidget", "Operation", nullptr));
        operationBox->setItemText(0, QCoreApplication::translate("SideWidget", "Move vertex", nullptr));
        operationBox->setItemText(1, QCoreApplication::translate("SideWidget", "Shift arc", nullptr));
        operationBox->setItemText(2, QCoreApplication::translate("SideWidget", "Continue existing", nullptr));
        operationBox->setItemText(3, QCoreApplication::translate("SideWidget", "Join existing", nullptr));
        operationBox->setItemText(4, QCoreApplication::translate("SideWidget", "Merge existing", nullptr));

        doArcOperation->setText(QCoreApplication::translate("SideWidget", "Go!", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("SideWidget", "Arcs", nullptr));
        selectDirection1->setItemText(0, QCoreApplication::translate("SideWidget", "North", nullptr));
        selectDirection1->setItemText(1, QCoreApplication::translate("SideWidget", "Northwest", nullptr));
        selectDirection1->setItemText(2, QCoreApplication::translate("SideWidget", "West", nullptr));
        selectDirection1->setItemText(3, QCoreApplication::translate("SideWidget", "Southwest", nullptr));
        selectDirection1->setItemText(4, QCoreApplication::translate("SideWidget", "South", nullptr));
        selectDirection1->setItemText(5, QCoreApplication::translate("SideWidget", "Southeast", nullptr));
        selectDirection1->setItemText(6, QCoreApplication::translate("SideWidget", "East", nullptr));
        selectDirection1->setItemText(7, QCoreApplication::translate("SideWidget", "Northeast", nullptr));

        label_17->setText(QCoreApplication::translate("SideWidget", "Select patch", nullptr));
        addPatch->setText(QCoreApplication::translate("SideWidget", "Add patch", nullptr));
        deletePatch->setText(QCoreApplication::translate("SideWidget", "Delete patch", nullptr));
        patchColorBox->setItemText(0, QCoreApplication::translate("SideWidget", "Red", nullptr));
        patchColorBox->setItemText(1, QCoreApplication::translate("SideWidget", "Green", nullptr));
        patchColorBox->setItemText(2, QCoreApplication::translate("SideWidget", "Blue", nullptr));
        patchColorBox->setItemText(3, QCoreApplication::translate("SideWidget", "Yellow", nullptr));
        patchColorBox->setItemText(4, QCoreApplication::translate("SideWidget", "Magenta", nullptr));
        patchColorBox->setItemText(5, QCoreApplication::translate("SideWidget", "Cyan", nullptr));

        label_32->setText(QCoreApplication::translate("SideWidget", "Color", nullptr));
        label_33->setText(QCoreApplication::translate("SideWidget", "Select patch 1 / Dir.", nullptr));
        label_34->setText(QCoreApplication::translate("SideWidget", "Select patch 2 / Dir.", nullptr));
        doPatchOperation->setText(QCoreApplication::translate("SideWidget", "Go!", nullptr));
        selectPatchMaterial->setItemText(0, QCoreApplication::translate("SideWidget", "Brass", nullptr));
        selectPatchMaterial->setItemText(1, QCoreApplication::translate("SideWidget", "Gold", nullptr));
        selectPatchMaterial->setItemText(2, QCoreApplication::translate("SideWidget", "Silver", nullptr));
        selectPatchMaterial->setItemText(3, QCoreApplication::translate("SideWidget", "Emerald", nullptr));
        selectPatchMaterial->setItemText(4, QCoreApplication::translate("SideWidget", "Pearl", nullptr));
        selectPatchMaterial->setItemText(5, QCoreApplication::translate("SideWidget", "Ruby", nullptr));
        selectPatchMaterial->setItemText(6, QCoreApplication::translate("SideWidget", "Turquoise", nullptr));

        patchOperation->setItemText(0, QCoreApplication::translate("SideWidget", "Move vertex", nullptr));
        patchOperation->setItemText(1, QCoreApplication::translate("SideWidget", "Shift patch", nullptr));
        patchOperation->setItemText(2, QCoreApplication::translate("SideWidget", "Continue existing", nullptr));
        patchOperation->setItemText(3, QCoreApplication::translate("SideWidget", "Join existing", nullptr));
        patchOperation->setItemText(4, QCoreApplication::translate("SideWidget", "Merge existing", nullptr));

        label_35->setText(QCoreApplication::translate("SideWidget", "Vertex of patch 1", nullptr));
        label_36->setText(QCoreApplication::translate("SideWidget", "Operation", nullptr));
        label_37->setText(QCoreApplication::translate("SideWidget", "Material", nullptr));
        label_39->setText(QCoreApplication::translate("SideWidget", "Vertex of patch 2", nullptr));
        selectDirection2->setItemText(0, QCoreApplication::translate("SideWidget", "North", nullptr));
        selectDirection2->setItemText(1, QCoreApplication::translate("SideWidget", "Northwest", nullptr));
        selectDirection2->setItemText(2, QCoreApplication::translate("SideWidget", "West", nullptr));
        selectDirection2->setItemText(3, QCoreApplication::translate("SideWidget", "Southwest", nullptr));
        selectDirection2->setItemText(4, QCoreApplication::translate("SideWidget", "South", nullptr));
        selectDirection2->setItemText(5, QCoreApplication::translate("SideWidget", "Southeast", nullptr));
        selectDirection2->setItemText(6, QCoreApplication::translate("SideWidget", "East", nullptr));
        selectDirection2->setItemText(7, QCoreApplication::translate("SideWidget", "Northeast", nullptr));

        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QCoreApplication::translate("SideWidget", "Patches", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H
