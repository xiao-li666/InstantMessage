/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedlabel.h>
#include "timerbtn.h"

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QLabel *errTip;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *userLabel;
    QLineEdit *userEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *emailLabel;
    QLineEdit *emailEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    ClickedLabel *passLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *sureLabel;
    QLineEdit *sureEdit;
    ClickedLabel *confirmLabel;
    QHBoxLayout *horizontalLayout_5;
    QLabel *verifyLabel;
    QLineEdit *verifyEdit;
    TimerBtn *getCode;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;
    QSpacerItem *verticalSpacer_3;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_4;
    QLabel *tipLabel;
    QLabel *tipLabel2;
    QSpacerItem *verticalSpacer_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *returnBtn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName(QString::fromUtf8("RegisterDialog"));
        RegisterDialog->resize(400, 640);
        RegisterDialog->setMinimumSize(QSize(400, 640));
        RegisterDialog->setMaximumSize(QSize(400, 640));
        verticalLayout_2 = new QVBoxLayout(RegisterDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(RegisterDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        widget = new QWidget(page);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 25));
        horizontalLayout_8 = new QHBoxLayout(widget);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        errTip = new QLabel(widget);
        errTip->setObjectName(QString::fromUtf8("errTip"));
        errTip->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(errTip);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        horizontalLayout_8->addLayout(horizontalLayout_7);


        verticalLayout_3->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        userLabel = new QLabel(page);
        userLabel->setObjectName(QString::fromUtf8("userLabel"));
        userLabel->setMinimumSize(QSize(0, 25));
        userLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(userLabel);

        userEdit = new QLineEdit(page);
        userEdit->setObjectName(QString::fromUtf8("userEdit"));
        userEdit->setMinimumSize(QSize(0, 25));
        userEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(userEdit);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        emailLabel = new QLabel(page);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));
        emailLabel->setMinimumSize(QSize(0, 25));
        emailLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(emailLabel);

        emailEdit = new QLineEdit(page);
        emailEdit->setObjectName(QString::fromUtf8("emailEdit"));
        emailEdit->setMinimumSize(QSize(0, 25));
        emailEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(emailEdit);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        passwordLabel = new QLabel(page);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setMinimumSize(QSize(0, 25));
        passwordLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(passwordLabel);

        passwordEdit = new QLineEdit(page);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setMinimumSize(QSize(0, 25));
        passwordEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(passwordEdit);

        passLabel = new ClickedLabel(page);
        passLabel->setObjectName(QString::fromUtf8("passLabel"));
        passLabel->setMinimumSize(QSize(20, 20));
        passLabel->setMaximumSize(QSize(20, 20));

        horizontalLayout_3->addWidget(passLabel);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        sureLabel = new QLabel(page);
        sureLabel->setObjectName(QString::fromUtf8("sureLabel"));
        sureLabel->setMinimumSize(QSize(0, 25));
        sureLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(sureLabel);

        sureEdit = new QLineEdit(page);
        sureEdit->setObjectName(QString::fromUtf8("sureEdit"));
        sureEdit->setMinimumSize(QSize(0, 25));
        sureEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(sureEdit);

        confirmLabel = new ClickedLabel(page);
        confirmLabel->setObjectName(QString::fromUtf8("confirmLabel"));
        confirmLabel->setMinimumSize(QSize(20, 20));
        confirmLabel->setMaximumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(confirmLabel);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verifyLabel = new QLabel(page);
        verifyLabel->setObjectName(QString::fromUtf8("verifyLabel"));
        verifyLabel->setMinimumSize(QSize(0, 25));
        verifyLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(verifyLabel);

        verifyEdit = new QLineEdit(page);
        verifyEdit->setObjectName(QString::fromUtf8("verifyEdit"));
        verifyEdit->setMinimumSize(QSize(0, 25));
        verifyEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(verifyEdit);

        getCode = new TimerBtn(page);
        getCode->setObjectName(QString::fromUtf8("getCode"));
        getCode->setMinimumSize(QSize(50, 40));
        getCode->setMaximumSize(QSize(50, 40));
        getCode->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(getCode);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        confirmBtn = new QPushButton(page);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(0, 25));
        confirmBtn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(confirmBtn);

        cancelBtn = new QPushButton(page);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 25));
        cancelBtn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(cancelBtn);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_4 = new QVBoxLayout(page_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        tipLabel = new QLabel(page_2);
        tipLabel->setObjectName(QString::fromUtf8("tipLabel"));
        tipLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(tipLabel);

        tipLabel2 = new QLabel(page_2);
        tipLabel2->setObjectName(QString::fromUtf8("tipLabel2"));
        tipLabel2->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(tipLabel2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        widget_2 = new QWidget(page_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_9 = new QHBoxLayout(widget_2);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        returnBtn = new QPushButton(widget_2);
        returnBtn->setObjectName(QString::fromUtf8("returnBtn"));
        returnBtn->setMinimumSize(QSize(0, 25));
        returnBtn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_9->addWidget(returnBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_4->addWidget(widget_2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(RegisterDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Dialog", nullptr));
        errTip->setText(QString());
        userLabel->setText(QCoreApplication::translate("RegisterDialog", "\347\224\250\346\210\267\357\274\232", nullptr));
        emailLabel->setText(QCoreApplication::translate("RegisterDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        passwordLabel->setText(QCoreApplication::translate("RegisterDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        passLabel->setText(QString());
        sureLabel->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244\357\274\232", nullptr));
        confirmLabel->setText(QString());
        verifyLabel->setText(QCoreApplication::translate("RegisterDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        getCode->setText(QCoreApplication::translate("RegisterDialog", "\350\216\267\345\217\226", nullptr));
        confirmBtn->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244", nullptr));
        cancelBtn->setText(QCoreApplication::translate("RegisterDialog", "\345\217\226\346\266\210", nullptr));
        tipLabel->setText(QCoreApplication::translate("RegisterDialog", "\346\263\250\345\206\214\346\210\220\345\212\237\357\274\2145s\345\220\216\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
        tipLabel2->setText(QCoreApplication::translate("RegisterDialog", "\345\217\257\347\202\271\345\207\273\350\277\224\345\233\236\346\214\211\351\222\256\347\233\264\346\216\245\350\277\224\345\233\236\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        returnBtn->setText(QCoreApplication::translate("RegisterDialog", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
