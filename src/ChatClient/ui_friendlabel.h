/********************************************************************************
** Form generated from reading UI file 'friendlabel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDLABEL_H
#define UI_FRIENDLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <clickedlabel.h>

QT_BEGIN_NAMESPACE

class Ui_FriendLabel
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *tipLb;
    QWidget *closeWid;
    QHBoxLayout *horizontalLayout_2;
    ClickedLabel *closeLb;

    void setupUi(QWidget *FriendLabel)
    {
        if (FriendLabel->objectName().isEmpty())
            FriendLabel->setObjectName(QString::fromUtf8("FriendLabel"));
        FriendLabel->resize(565, 43);
        FriendLabel->setMinimumSize(QSize(0, 43));
        FriendLabel->setMaximumSize(QSize(16777215, 43));
        horizontalLayout = new QHBoxLayout(FriendLabel);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tipLb = new QLabel(FriendLabel);
        tipLb->setObjectName(QString::fromUtf8("tipLb"));

        horizontalLayout->addWidget(tipLb);

        closeWid = new QWidget(FriendLabel);
        closeWid->setObjectName(QString::fromUtf8("closeWid"));
        closeWid->setMinimumSize(QSize(25, 25));
        closeWid->setMaximumSize(QSize(25, 25));
        horizontalLayout_2 = new QHBoxLayout(closeWid);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        closeLb = new ClickedLabel(closeWid);
        closeLb->setObjectName(QString::fromUtf8("closeLb"));
        closeLb->setMinimumSize(QSize(15, 15));
        closeLb->setMaximumSize(QSize(15, 15));

        horizontalLayout_2->addWidget(closeLb);


        horizontalLayout->addWidget(closeWid);


        retranslateUi(FriendLabel);

        QMetaObject::connectSlotsByName(FriendLabel);
    } // setupUi

    void retranslateUi(QWidget *FriendLabel)
    {
        FriendLabel->setWindowTitle(QCoreApplication::translate("FriendLabel", "Form", nullptr));
        tipLb->setText(QCoreApplication::translate("FriendLabel", "TextLabel", nullptr));
        closeLb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendLabel: public Ui_FriendLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDLABEL_H
