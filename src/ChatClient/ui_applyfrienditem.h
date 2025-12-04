/********************************************************************************
** Form generated from reading UI file 'applyfrienditem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLYFRIENDITEM_H
#define UI_APPLYFRIENDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickbtn.h"

QT_BEGIN_NAMESPACE

class Ui_ApplyFriendItem
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *iconlb;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *userNameLabel;
    QLabel *userChatLabel;
    QSpacerItem *horizontalSpacer_3;
    ClickBtn *addBtn;
    QLabel *alreadyAddLabel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ApplyFriendItem)
    {
        if (ApplyFriendItem->objectName().isEmpty())
            ApplyFriendItem->setObjectName(QString::fromUtf8("ApplyFriendItem"));
        ApplyFriendItem->resize(521, 80);
        ApplyFriendItem->setMaximumSize(QSize(16777215, 80));
        horizontalLayout = new QHBoxLayout(ApplyFriendItem);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        iconlb = new QLabel(ApplyFriendItem);
        iconlb->setObjectName(QString::fromUtf8("iconlb"));
        iconlb->setMinimumSize(QSize(45, 45));
        iconlb->setMaximumSize(QSize(45, 45));

        horizontalLayout->addWidget(iconlb);

        widget = new QWidget(ApplyFriendItem);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 2, -1, 2);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(11, 2, -1, 2);
        userNameLabel = new QLabel(widget_2);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));
        userNameLabel->setMinimumSize(QSize(100, 30));
        userNameLabel->setMaximumSize(QSize(200, 30));

        verticalLayout->addWidget(userNameLabel);

        userChatLabel = new QLabel(widget_2);
        userChatLabel->setObjectName(QString::fromUtf8("userChatLabel"));
        userChatLabel->setMinimumSize(QSize(100, 30));
        userChatLabel->setMaximumSize(QSize(200, 30));

        verticalLayout->addWidget(userChatLabel);


        horizontalLayout_2->addWidget(widget_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        addBtn = new ClickBtn(widget);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));
        addBtn->setMinimumSize(QSize(80, 30));
        addBtn->setMaximumSize(QSize(80, 30));

        horizontalLayout_2->addWidget(addBtn);

        alreadyAddLabel = new QLabel(widget);
        alreadyAddLabel->setObjectName(QString::fromUtf8("alreadyAddLabel"));
        alreadyAddLabel->setMinimumSize(QSize(40, 0));

        horizontalLayout_2->addWidget(alreadyAddLabel);

        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout->addWidget(widget);


        retranslateUi(ApplyFriendItem);

        QMetaObject::connectSlotsByName(ApplyFriendItem);
    } // setupUi

    void retranslateUi(QWidget *ApplyFriendItem)
    {
        ApplyFriendItem->setWindowTitle(QCoreApplication::translate("ApplyFriendItem", "Form", nullptr));
        iconlb->setText(QString());
        userNameLabel->setText(QString());
        userChatLabel->setText(QString());
        addBtn->setText(QCoreApplication::translate("ApplyFriendItem", "\346\267\273\345\212\240", nullptr));
        alreadyAddLabel->setText(QCoreApplication::translate("ApplyFriendItem", "\345\267\262\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplyFriendItem: public Ui_ApplyFriendItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLYFRIENDITEM_H
