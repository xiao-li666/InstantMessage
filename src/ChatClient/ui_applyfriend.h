/********************************************************************************
** Form generated from reading UI file 'applyfriend.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLYFRIEND_H
#define UI_APPLYFRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedoncelabel.h>
#include <customizeedit.h>
#include "clickbtn.h"

QT_BEGIN_NAMESPACE

class Ui_ApplyFriend
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollContent;
    QVBoxLayout *verticalLayout_2;
    QLabel *applyLabel;
    QWidget *applyWid;
    QVBoxLayout *verticalLayout_3;
    QFrame *line;
    QLabel *label;
    CustomizeEdit *nameEdit;
    QLabel *label_2;
    CustomizeEdit *backEdit;
    QLabel *label_3;
    QWidget *lbGroupWid;
    QVBoxLayout *verticalLayout_4;
    QWidget *gridWidget;
    CustomizeEdit *lbEdit;
    QWidget *inputWidget;
    QVBoxLayout *verticalLayout_5;
    ClickedOnceLabel *tipLb;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *labelList;
    QWidget *moreLabelWid;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_3;
    ClickedOnceLabel *moreLabel;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer;
    QWidget *applySureWid;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    ClickBtn *sureBtn;
    QSpacerItem *horizontalSpacer_3;
    ClickBtn *cancelBtn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *ApplyFriend)
    {
        if (ApplyFriend->objectName().isEmpty())
            ApplyFriend->setObjectName(QString::fromUtf8("ApplyFriend"));
        ApplyFriend->resize(361, 621);
        ApplyFriend->setMinimumSize(QSize(361, 621));
        ApplyFriend->setMaximumSize(QSize(361, 621));
        verticalLayout = new QVBoxLayout(ApplyFriend);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(ApplyFriend);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(0, 500));
        scrollArea->setWidgetResizable(true);
        scrollContent = new QWidget();
        scrollContent->setObjectName(QString::fromUtf8("scrollContent"));
        scrollContent->setGeometry(QRect(0, 0, 359, 498));
        verticalLayout_2 = new QVBoxLayout(scrollContent);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 11, 0, 11);
        applyLabel = new QLabel(scrollContent);
        applyLabel->setObjectName(QString::fromUtf8("applyLabel"));
        applyLabel->setMinimumSize(QSize(0, 25));
        applyLabel->setMaximumSize(QSize(16777215, 25));
        applyLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(applyLabel);

        applyWid = new QWidget(scrollContent);
        applyWid->setObjectName(QString::fromUtf8("applyWid"));
        verticalLayout_3 = new QVBoxLayout(applyWid);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        line = new QFrame(applyWid);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        label = new QLabel(applyWid);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 25));
        label->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(label);

        nameEdit = new CustomizeEdit(applyWid);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setMinimumSize(QSize(0, 35));
        nameEdit->setMaximumSize(QSize(16777215, 35));

        verticalLayout_3->addWidget(nameEdit);

        label_2 = new QLabel(applyWid);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 25));
        label_2->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(label_2);

        backEdit = new CustomizeEdit(applyWid);
        backEdit->setObjectName(QString::fromUtf8("backEdit"));
        backEdit->setMinimumSize(QSize(0, 35));
        backEdit->setMaximumSize(QSize(16777215, 35));

        verticalLayout_3->addWidget(backEdit);

        label_3 = new QLabel(applyWid);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 25));
        label_3->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(label_3);

        lbGroupWid = new QWidget(applyWid);
        lbGroupWid->setObjectName(QString::fromUtf8("lbGroupWid"));
        lbGroupWid->setMinimumSize(QSize(0, 50));
        verticalLayout_4 = new QVBoxLayout(lbGroupWid);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        gridWidget = new QWidget(lbGroupWid);
        gridWidget->setObjectName(QString::fromUtf8("gridWidget"));
        gridWidget->setMinimumSize(QSize(0, 40));
        gridWidget->setMaximumSize(QSize(16777215, 40));
        lbEdit = new CustomizeEdit(gridWidget);
        lbEdit->setObjectName(QString::fromUtf8("lbEdit"));
        lbEdit->setGeometry(QRect(2, 2, 108, 35));
        lbEdit->setMaximumSize(QSize(16777215, 35));

        verticalLayout_4->addWidget(gridWidget);

        inputWidget = new QWidget(lbGroupWid);
        inputWidget->setObjectName(QString::fromUtf8("inputWidget"));
        inputWidget->setMinimumSize(QSize(0, 35));
        inputWidget->setMaximumSize(QSize(16777215, 35));
        verticalLayout_5 = new QVBoxLayout(inputWidget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        tipLb = new ClickedOnceLabel(inputWidget);
        tipLb->setObjectName(QString::fromUtf8("tipLb"));

        verticalLayout_5->addWidget(tipLb);


        verticalLayout_4->addWidget(inputWidget);


        verticalLayout_3->addWidget(lbGroupWid);

        widget = new QWidget(applyWid);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 60));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelList = new QWidget(widget);
        labelList->setObjectName(QString::fromUtf8("labelList"));
        labelList->setMinimumSize(QSize(287, 50));
        labelList->setMaximumSize(QSize(287, 16777215));

        horizontalLayout_2->addWidget(labelList);

        moreLabelWid = new QWidget(widget);
        moreLabelWid->setObjectName(QString::fromUtf8("moreLabelWid"));
        moreLabelWid->setMinimumSize(QSize(30, 0));
        moreLabelWid->setMaximumSize(QSize(30, 16777215));
        verticalLayout_6 = new QVBoxLayout(moreLabelWid);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        moreLabel = new ClickedOnceLabel(moreLabelWid);
        moreLabel->setObjectName(QString::fromUtf8("moreLabel"));
        moreLabel->setMinimumSize(QSize(25, 25));
        moreLabel->setMaximumSize(QSize(25, 25));

        verticalLayout_6->addWidget(moreLabel);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);


        horizontalLayout_2->addWidget(moreLabelWid);


        verticalLayout_3->addWidget(widget);


        verticalLayout_2->addWidget(applyWid);

        scrollArea->setWidget(scrollContent);

        verticalLayout->addWidget(scrollArea);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        applySureWid = new QWidget(ApplyFriend);
        applySureWid->setObjectName(QString::fromUtf8("applySureWid"));
        applySureWid->setMinimumSize(QSize(0, 50));
        horizontalLayout = new QHBoxLayout(applySureWid);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        sureBtn = new ClickBtn(applySureWid);
        sureBtn->setObjectName(QString::fromUtf8("sureBtn"));
        sureBtn->setMinimumSize(QSize(100, 30));
        sureBtn->setMaximumSize(QSize(100, 30));

        horizontalLayout->addWidget(sureBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        cancelBtn = new ClickBtn(applySureWid);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(100, 30));
        cancelBtn->setMaximumSize(QSize(100, 30));

        horizontalLayout->addWidget(cancelBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(applySureWid);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(ApplyFriend);

        QMetaObject::connectSlotsByName(ApplyFriend);
    } // setupUi

    void retranslateUi(QDialog *ApplyFriend)
    {
        ApplyFriend->setWindowTitle(QCoreApplication::translate("ApplyFriend", "Dialog", nullptr));
        applyLabel->setText(QCoreApplication::translate("ApplyFriend", "\347\224\263\350\257\267\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        label->setText(QCoreApplication::translate("ApplyFriend", "\345\217\221\351\200\201\346\267\273\345\212\240\345\245\275\345\217\213\347\224\263\350\257\267:", nullptr));
        label_2->setText(QCoreApplication::translate("ApplyFriend", "\345\244\207\346\263\250\345\220\215:", nullptr));
        label_3->setText(QCoreApplication::translate("ApplyFriend", "\346\240\207\347\255\276", nullptr));
        tipLb->setText(QCoreApplication::translate("ApplyFriend", "TextLabel", nullptr));
        moreLabel->setText(QString());
        sureBtn->setText(QCoreApplication::translate("ApplyFriend", "\347\241\256\350\256\244", nullptr));
        cancelBtn->setText(QCoreApplication::translate("ApplyFriend", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplyFriend: public Ui_ApplyFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLYFRIEND_H
