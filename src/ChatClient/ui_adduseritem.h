/********************************************************************************
** Form generated from reading UI file 'adduseritem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDUSERITEM_H
#define UI_ADDUSERITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddUserItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *addTip;
    QLabel *messageTip;
    QLabel *rightTip;

    void setupUi(QWidget *AddUserItem)
    {
        if (AddUserItem->objectName().isEmpty())
            AddUserItem->setObjectName(QString::fromUtf8("AddUserItem"));
        AddUserItem->resize(250, 70);
        AddUserItem->setMinimumSize(QSize(250, 70));
        AddUserItem->setMaximumSize(QSize(250, 70));
        horizontalLayout = new QHBoxLayout(AddUserItem);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addTip = new QLabel(AddUserItem);
        addTip->setObjectName(QString::fromUtf8("addTip"));
        addTip->setMinimumSize(QSize(40, 40));
        addTip->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(addTip);

        messageTip = new QLabel(AddUserItem);
        messageTip->setObjectName(QString::fromUtf8("messageTip"));

        horizontalLayout->addWidget(messageTip);

        rightTip = new QLabel(AddUserItem);
        rightTip->setObjectName(QString::fromUtf8("rightTip"));
        rightTip->setMinimumSize(QSize(30, 30));
        rightTip->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(rightTip);


        retranslateUi(AddUserItem);

        QMetaObject::connectSlotsByName(AddUserItem);
    } // setupUi

    void retranslateUi(QWidget *AddUserItem)
    {
        AddUserItem->setWindowTitle(QCoreApplication::translate("AddUserItem", "Form", nullptr));
        addTip->setText(QString());
        messageTip->setText(QCoreApplication::translate("AddUserItem", "\346\237\245\346\211\276 uid/nick", nullptr));
        rightTip->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AddUserItem: public Ui_AddUserItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDUSERITEM_H
