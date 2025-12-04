/********************************************************************************
** Form generated from reading UI file 'resetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETDIALOG_H
#define UI_RESETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ResetDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *errTip;
    QHBoxLayout *horizontalLayout_5;
    QLabel *userLabel;
    QLineEdit *userLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *emailLabel;
    QLineEdit *emailEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *varifyLabel;
    QLineEdit *varifyEdit;
    QPushButton *varifyBtn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *newPasslabel;
    QLineEdit *newPassEdit;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *ResetDialog)
    {
        if (ResetDialog->objectName().isEmpty())
            ResetDialog->setObjectName(QString::fromUtf8("ResetDialog"));
        ResetDialog->resize(400, 640);
        ResetDialog->setMinimumSize(QSize(400, 640));
        ResetDialog->setMaximumSize(QSize(400, 640));
        verticalLayout = new QVBoxLayout(ResetDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 10, -1, 10);
        errTip = new QLabel(ResetDialog);
        errTip->setObjectName(QString::fromUtf8("errTip"));
        errTip->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(errTip);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 10, -1, 10);
        userLabel = new QLabel(ResetDialog);
        userLabel->setObjectName(QString::fromUtf8("userLabel"));
        userLabel->setMinimumSize(QSize(50, 20));
        userLabel->setMaximumSize(QSize(50, 20));

        horizontalLayout_5->addWidget(userLabel);

        userLineEdit = new QLineEdit(ResetDialog);
        userLineEdit->setObjectName(QString::fromUtf8("userLineEdit"));
        userLineEdit->setMinimumSize(QSize(0, 30));
        userLineEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_5->addWidget(userLineEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 10, -1, 10);
        emailLabel = new QLabel(ResetDialog);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));
        emailLabel->setMinimumSize(QSize(50, 30));
        emailLabel->setMaximumSize(QSize(50, 30));

        horizontalLayout_4->addWidget(emailLabel);

        emailEdit = new QLineEdit(ResetDialog);
        emailEdit->setObjectName(QString::fromUtf8("emailEdit"));
        emailEdit->setMinimumSize(QSize(0, 30));
        emailEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_4->addWidget(emailEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 10, -1, 10);
        varifyLabel = new QLabel(ResetDialog);
        varifyLabel->setObjectName(QString::fromUtf8("varifyLabel"));
        varifyLabel->setMinimumSize(QSize(50, 30));
        varifyLabel->setMaximumSize(QSize(50, 30));

        horizontalLayout_3->addWidget(varifyLabel);

        varifyEdit = new QLineEdit(ResetDialog);
        varifyEdit->setObjectName(QString::fromUtf8("varifyEdit"));
        varifyEdit->setMinimumSize(QSize(0, 30));
        varifyEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_3->addWidget(varifyEdit);

        varifyBtn = new QPushButton(ResetDialog);
        varifyBtn->setObjectName(QString::fromUtf8("varifyBtn"));
        varifyBtn->setMinimumSize(QSize(50, 30));
        varifyBtn->setMaximumSize(QSize(50, 30));

        horizontalLayout_3->addWidget(varifyBtn);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 10, -1, 10);
        newPasslabel = new QLabel(ResetDialog);
        newPasslabel->setObjectName(QString::fromUtf8("newPasslabel"));
        newPasslabel->setMinimumSize(QSize(50, 30));
        newPasslabel->setMaximumSize(QSize(50, 30));

        horizontalLayout_2->addWidget(newPasslabel);

        newPassEdit = new QLineEdit(ResetDialog);
        newPassEdit->setObjectName(QString::fromUtf8("newPassEdit"));
        newPassEdit->setMinimumSize(QSize(0, 30));
        newPassEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(newPassEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 10, -1, 10);
        confirmBtn = new QPushButton(ResetDialog);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(0, 30));
        confirmBtn->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(confirmBtn);

        cancelBtn = new QPushButton(ResetDialog);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 30));
        cancelBtn->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(cancelBtn);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(ResetDialog);

        QMetaObject::connectSlotsByName(ResetDialog);
    } // setupUi

    void retranslateUi(QDialog *ResetDialog)
    {
        ResetDialog->setWindowTitle(QCoreApplication::translate("ResetDialog", "Dialog", nullptr));
        errTip->setText(QCoreApplication::translate("ResetDialog", "\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        userLabel->setText(QCoreApplication::translate("ResetDialog", "\347\224\250\346\210\267\345\220\215:", nullptr));
        emailLabel->setText(QCoreApplication::translate("ResetDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        varifyLabel->setText(QCoreApplication::translate("ResetDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        varifyBtn->setText(QCoreApplication::translate("ResetDialog", "\350\216\267\345\217\226", nullptr));
        newPasslabel->setText(QCoreApplication::translate("ResetDialog", "\346\226\260\345\257\206\347\240\201", nullptr));
        confirmBtn->setText(QCoreApplication::translate("ResetDialog", "\347\241\256\350\256\244", nullptr));
        cancelBtn->setText(QCoreApplication::translate("ResetDialog", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResetDialog: public Ui_ResetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETDIALOG_H
