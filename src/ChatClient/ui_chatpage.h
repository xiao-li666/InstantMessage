/********************************************************************************
** Form generated from reading UI file 'chatpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATPAGE_H
#define UI_CHATPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <chatview.h>
#include <clickedlabel.h>
#include <messagetextedit.h>
#include "clickbtn.h"

QT_BEGIN_NAMESPACE

class Ui_ChatPage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *chat_data_widget;
    QVBoxLayout *verticalLayout_4;
    QWidget *titleWidget;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *titleLabel;
    ChatView *chatDataList;
    QWidget *toolWidget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    ClickedLabel *emoLabel;
    QSpacerItem *horizontalSpacer_4;
    ClickedLabel *fileLabel;
    QSpacerItem *horizontalSpacer_3;
    MessageTextEdit *chatEdit;
    QWidget *sendWid;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    ClickBtn *recvBtn;
    QSpacerItem *horizontalSpacer_7;
    ClickBtn *sendBtn;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *ChatPage)
    {
        if (ChatPage->objectName().isEmpty())
            ChatPage->setObjectName(QString::fromUtf8("ChatPage"));
        ChatPage->resize(805, 639);
        verticalLayout = new QVBoxLayout(ChatPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        chat_data_widget = new QWidget(ChatPage);
        chat_data_widget->setObjectName(QString::fromUtf8("chat_data_widget"));
        verticalLayout_4 = new QVBoxLayout(chat_data_widget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(chat_data_widget);
        titleWidget->setObjectName(QString::fromUtf8("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 60));
        titleWidget->setMaximumSize(QSize(16777215, 60));
        verticalLayout_5 = new QVBoxLayout(titleWidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, 2, 2, 2);
        widget_2 = new QWidget(titleWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 2, 2, 2);
        titleLabel = new QLabel(widget_2);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));

        horizontalLayout_3->addWidget(titleLabel);


        verticalLayout_5->addWidget(widget_2);


        verticalLayout_4->addWidget(titleWidget);

        chatDataList = new ChatView(chat_data_widget);
        chatDataList->setObjectName(QString::fromUtf8("chatDataList"));

        verticalLayout_4->addWidget(chatDataList);

        toolWidget = new QWidget(chat_data_widget);
        toolWidget->setObjectName(QString::fromUtf8("toolWidget"));
        toolWidget->setMinimumSize(QSize(0, 60));
        toolWidget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_4 = new QHBoxLayout(toolWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        emoLabel = new ClickedLabel(toolWidget);
        emoLabel->setObjectName(QString::fromUtf8("emoLabel"));
        emoLabel->setMinimumSize(QSize(25, 25));
        emoLabel->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(emoLabel);

        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        fileLabel = new ClickedLabel(toolWidget);
        fileLabel->setObjectName(QString::fromUtf8("fileLabel"));
        fileLabel->setMinimumSize(QSize(25, 25));
        fileLabel->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(fileLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_4->addWidget(toolWidget);

        chatEdit = new MessageTextEdit(chat_data_widget);
        chatEdit->setObjectName(QString::fromUtf8("chatEdit"));
        chatEdit->setMaximumSize(QSize(16777215, 150));

        verticalLayout_4->addWidget(chatEdit);

        sendWid = new QWidget(chat_data_widget);
        sendWid->setObjectName(QString::fromUtf8("sendWid"));
        sendWid->setMinimumSize(QSize(0, 60));
        sendWid->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_5 = new QHBoxLayout(sendWid);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        recvBtn = new ClickBtn(sendWid);
        recvBtn->setObjectName(QString::fromUtf8("recvBtn"));
        recvBtn->setMinimumSize(QSize(100, 30));
        recvBtn->setMaximumSize(QSize(100, 30));

        horizontalLayout_5->addWidget(recvBtn);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        sendBtn = new ClickBtn(sendWid);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));
        sendBtn->setMinimumSize(QSize(100, 30));
        sendBtn->setMaximumSize(QSize(100, 30));
        sendBtn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(sendBtn);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout_4->addWidget(sendWid);


        verticalLayout->addWidget(chat_data_widget);


        retranslateUi(ChatPage);

        QMetaObject::connectSlotsByName(ChatPage);
    } // setupUi

    void retranslateUi(QWidget *ChatPage)
    {
        ChatPage->setWindowTitle(QCoreApplication::translate("ChatPage", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("ChatPage", "\351\270\240\351\255\201", nullptr));
        emoLabel->setText(QString());
        fileLabel->setText(QString());
        recvBtn->setText(QCoreApplication::translate("ChatPage", "\346\216\245\346\224\266", nullptr));
        sendBtn->setText(QCoreApplication::translate("ChatPage", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatPage: public Ui_ChatPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATPAGE_H
