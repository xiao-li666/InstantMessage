/********************************************************************************
** Form generated from reading UI file 'findsuccessdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDSUCCESSDLG_H
#define UI_FINDSUCCESSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickbtn.h"

QT_BEGIN_NAMESPACE

class Ui_FindSuccessDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *headLabel;
    QLabel *nameLabel;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    ClickBtn *addFriendBtn;

    void setupUi(QDialog *FindSuccessDlg)
    {
        if (FindSuccessDlg->objectName().isEmpty())
            FindSuccessDlg->setObjectName(QString::fromUtf8("FindSuccessDlg"));
        FindSuccessDlg->resize(280, 190);
        FindSuccessDlg->setMinimumSize(QSize(280, 190));
        FindSuccessDlg->setMaximumSize(QSize(280, 190));
        verticalLayout = new QVBoxLayout(FindSuccessDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(FindSuccessDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        headLabel = new QLabel(widget);
        headLabel->setObjectName(QString::fromUtf8("headLabel"));
        headLabel->setMinimumSize(QSize(50, 50));
        headLabel->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(headLabel);

        nameLabel = new QLabel(widget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setMinimumSize(QSize(0, 0));
        nameLabel->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(nameLabel);

        horizontalSpacer = new QSpacerItem(169, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(FindSuccessDlg);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addFriendBtn = new ClickBtn(widget_2);
        addFriendBtn->setObjectName(QString::fromUtf8("addFriendBtn"));
        addFriendBtn->setMinimumSize(QSize(120, 35));
        addFriendBtn->setMaximumSize(QSize(120, 35));

        horizontalLayout_2->addWidget(addFriendBtn);


        verticalLayout->addWidget(widget_2);


        retranslateUi(FindSuccessDlg);

        QMetaObject::connectSlotsByName(FindSuccessDlg);
    } // setupUi

    void retranslateUi(QDialog *FindSuccessDlg)
    {
        FindSuccessDlg->setWindowTitle(QCoreApplication::translate("FindSuccessDlg", "Dialog", nullptr));
        headLabel->setText(QString());
        nameLabel->setText(QString());
        addFriendBtn->setText(QCoreApplication::translate("FindSuccessDlg", "\346\267\273\345\212\240\345\210\260\351\200\232\350\256\257\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindSuccessDlg: public Ui_FindSuccessDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDSUCCESSDLG_H
