/********************************************************************************
** Form generated from reading UI file 'loadingdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGDLG_H
#define UI_LOADINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoadingDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *loadingLabel;

    void setupUi(QDialog *LoadingDlg)
    {
        if (LoadingDlg->objectName().isEmpty())
            LoadingDlg->setObjectName(QString::fromUtf8("LoadingDlg"));
        LoadingDlg->resize(100, 100);
        LoadingDlg->setMaximumSize(QSize(100, 100));
        verticalLayout = new QVBoxLayout(LoadingDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        loadingLabel = new QLabel(LoadingDlg);
        loadingLabel->setObjectName(QString::fromUtf8("loadingLabel"));
        loadingLabel->setMaximumSize(QSize(100, 100));

        verticalLayout->addWidget(loadingLabel);


        retranslateUi(LoadingDlg);

        QMetaObject::connectSlotsByName(LoadingDlg);
    } // setupUi

    void retranslateUi(QDialog *LoadingDlg)
    {
        LoadingDlg->setWindowTitle(QCoreApplication::translate("LoadingDlg", "Dialog", nullptr));
        loadingLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoadingDlg: public Ui_LoadingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGDLG_H
