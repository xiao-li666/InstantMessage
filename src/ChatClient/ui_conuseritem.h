/********************************************************************************
** Form generated from reading UI file 'conuseritem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONUSERITEM_H
#define UI_CONUSERITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConUserItem
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QLabel *iconLabel;
    QLabel *redPoint;
    QLabel *userNameLabel;

    void setupUi(QWidget *ConUserItem)
    {
        if (ConUserItem->objectName().isEmpty())
            ConUserItem->setObjectName(QString::fromUtf8("ConUserItem"));
        ConUserItem->resize(400, 70);
        ConUserItem->setMinimumSize(QSize(0, 70));
        ConUserItem->setMaximumSize(QSize(16777215, 70));
        horizontalLayout = new QHBoxLayout(ConUserItem);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 2, -1, 2);
        widget = new QWidget(ConUserItem);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(60, 60));
        widget->setMaximumSize(QSize(60, 60));
        iconLabel = new QLabel(widget);
        iconLabel->setObjectName(QString::fromUtf8("iconLabel"));
        iconLabel->setGeometry(QRect(0, 10, 45, 45));
        iconLabel->setMinimumSize(QSize(45, 45));
        iconLabel->setMaximumSize(QSize(45, 45));
        redPoint = new QLabel(widget);
        redPoint->setObjectName(QString::fromUtf8("redPoint"));
        redPoint->setGeometry(QRect(27, 2, 30, 30));
        redPoint->setMinimumSize(QSize(30, 30));
        redPoint->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(widget);

        userNameLabel = new QLabel(ConUserItem);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));

        horizontalLayout->addWidget(userNameLabel);


        retranslateUi(ConUserItem);

        QMetaObject::connectSlotsByName(ConUserItem);
    } // setupUi

    void retranslateUi(QWidget *ConUserItem)
    {
        ConUserItem->setWindowTitle(QCoreApplication::translate("ConUserItem", "Form", nullptr));
        iconLabel->setText(QString());
        redPoint->setText(QString());
        userNameLabel->setText(QCoreApplication::translate("ConUserItem", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConUserItem: public Ui_ConUserItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONUSERITEM_H
