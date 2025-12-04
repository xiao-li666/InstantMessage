/********************************************************************************
** Form generated from reading UI file 'chatuserwid.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATUSERWID_H
#define UI_CHATUSERWID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatUserWid
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *iconWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *iconLabel;
    QWidget *userInfoWidget;
    QVBoxLayout *verticalLayout;
    QLabel *userNameLabel;
    QLabel *userChatLabel;
    QWidget *timeWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *timeLabel;

    void setupUi(QWidget *ChatUserWid)
    {
        if (ChatUserWid->objectName().isEmpty())
            ChatUserWid->setObjectName(QString::fromUtf8("ChatUserWid"));
        ChatUserWid->resize(519, 70);
        ChatUserWid->setMinimumSize(QSize(0, 70));
        ChatUserWid->setMaximumSize(QSize(16777215, 70));
        horizontalLayout = new QHBoxLayout(ChatUserWid);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 2, 6, 2);
        iconWidget = new QWidget(ChatUserWid);
        iconWidget->setObjectName(QString::fromUtf8("iconWidget"));
        iconWidget->setMinimumSize(QSize(50, 50));
        iconWidget->setMaximumSize(QSize(50, 50));
        horizontalLayout_2 = new QHBoxLayout(iconWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        iconLabel = new QLabel(iconWidget);
        iconLabel->setObjectName(QString::fromUtf8("iconLabel"));
        iconLabel->setMinimumSize(QSize(45, 45));
        iconLabel->setMaximumSize(QSize(45, 45));

        horizontalLayout_2->addWidget(iconLabel);


        horizontalLayout->addWidget(iconWidget);

        userInfoWidget = new QWidget(ChatUserWid);
        userInfoWidget->setObjectName(QString::fromUtf8("userInfoWidget"));
        verticalLayout = new QVBoxLayout(userInfoWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        userNameLabel = new QLabel(userInfoWidget);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));

        verticalLayout->addWidget(userNameLabel);

        userChatLabel = new QLabel(userInfoWidget);
        userChatLabel->setObjectName(QString::fromUtf8("userChatLabel"));

        verticalLayout->addWidget(userChatLabel);


        horizontalLayout->addWidget(userInfoWidget);

        timeWidget = new QWidget(ChatUserWid);
        timeWidget->setObjectName(QString::fromUtf8("timeWidget"));
        timeWidget->setMinimumSize(QSize(50, 50));
        timeWidget->setMaximumSize(QSize(50, 50));
        horizontalLayout_3 = new QHBoxLayout(timeWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        timeLabel = new QLabel(timeWidget);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setMinimumSize(QSize(48, 48));
        timeLabel->setMaximumSize(QSize(48, 48));
        timeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(timeLabel);


        horizontalLayout->addWidget(timeWidget);


        retranslateUi(ChatUserWid);

        QMetaObject::connectSlotsByName(ChatUserWid);
    } // setupUi

    void retranslateUi(QWidget *ChatUserWid)
    {
        ChatUserWid->setWindowTitle(QCoreApplication::translate("ChatUserWid", "Form", nullptr));
        iconLabel->setText(QString());
        userNameLabel->setText(QCoreApplication::translate("ChatUserWid", "\351\270\240\351\255\201", nullptr));
        userChatLabel->setText(QCoreApplication::translate("ChatUserWid", "helloworld", nullptr));
        timeLabel->setText(QCoreApplication::translate("ChatUserWid", "00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatUserWid: public Ui_ChatUserWid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATUSERWID_H
