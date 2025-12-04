/********************************************************************************
** Form generated from reading UI file 'findfaileddlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDFAILEDDLG_H
#define UI_FINDFAILEDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickbtn.h"

QT_BEGIN_NAMESPACE

class Ui_FindFailedDlg
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *failTip;
    QLabel *failTip2;
    QWidget *widget;
    ClickBtn *failSureBtn;

    void setupUi(QDialog *FindFailedDlg)
    {
        if (FindFailedDlg->objectName().isEmpty())
            FindFailedDlg->setObjectName(QString::fromUtf8("FindFailedDlg"));
        FindFailedDlg->resize(386, 462);
        verticalLayout = new QVBoxLayout(FindFailedDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        failTip = new QLabel(FindFailedDlg);
        failTip->setObjectName(QString::fromUtf8("failTip"));
        failTip->setMinimumSize(QSize(0, 25));
        failTip->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(failTip);

        failTip2 = new QLabel(FindFailedDlg);
        failTip2->setObjectName(QString::fromUtf8("failTip2"));
        failTip2->setMinimumSize(QSize(0, 25));
        failTip2->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(failTip2);

        widget = new QWidget(FindFailedDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        failSureBtn = new ClickBtn(widget);
        failSureBtn->setObjectName(QString::fromUtf8("failSureBtn"));
        failSureBtn->setGeometry(QRect(130, 160, 100, 30));
        failSureBtn->setMinimumSize(QSize(100, 30));
        failSureBtn->setMaximumSize(QSize(100, 30));

        verticalLayout->addWidget(widget);


        retranslateUi(FindFailedDlg);

        QMetaObject::connectSlotsByName(FindFailedDlg);
    } // setupUi

    void retranslateUi(QDialog *FindFailedDlg)
    {
        FindFailedDlg->setWindowTitle(QCoreApplication::translate("FindFailedDlg", "Dialog", nullptr));
        failTip->setText(QCoreApplication::translate("FindFailedDlg", "\346\227\240\346\263\225\346\211\276\345\210\260\350\257\245\347\224\250\346\210\267", nullptr));
        failTip2->setText(QCoreApplication::translate("FindFailedDlg", "\350\257\267\346\243\200\346\237\245\344\275\240\345\241\253\345\206\231\347\232\204\350\264\246\345\217\267\346\230\257\345\220\246\346\255\243\347\241\256", nullptr));
        failSureBtn->setText(QCoreApplication::translate("FindFailedDlg", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindFailedDlg: public Ui_FindFailedDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDFAILEDDLG_H
