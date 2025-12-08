/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <applyfriendpage.h>
#include <chatpage.h>
#include <contactuserlist.h>
#include <customizeedit.h>
#include <friendinfopage.h>
#include <searchlist.h>
#include <statewidget.h>
#include "chatuserlist.h"
#include "clickbtn.h"

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *side_bar_widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *sideHeadLabel;
    StateWidget *sideChatLabel;
    StateWidget *sideContactLabel;
    QSpacerItem *verticalSpacer;
    QWidget *chat_user_widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *searchWidget;
    QHBoxLayout *horizontalLayout_2;
    CustomizeEdit *searchEdit;
    QSpacerItem *horizontalSpacer;
    ClickBtn *addBtn;
    ChatUserList *chatUserList;
    SearchList *searchUserList;
    ContactUserList *conUserList;
    QStackedWidget *stackedWidget;
    ChatPage *chatPage;
    ApplyFriendPage *friendApplyPage;
    FriendInfoPage *friendInfoPage;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName(QString::fromUtf8("ChatDialog"));
        ChatDialog->resize(1140, 900);
        ChatDialog->setMinimumSize(QSize(30, 30));
        ChatDialog->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(ChatDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        side_bar_widget = new QWidget(ChatDialog);
        side_bar_widget->setObjectName(QString::fromUtf8("side_bar_widget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(side_bar_widget->sizePolicy().hasHeightForWidth());
        side_bar_widget->setSizePolicy(sizePolicy);
        side_bar_widget->setMinimumSize(QSize(56, 0));
        side_bar_widget->setMaximumSize(QSize(56, 16777215));
        verticalLayout = new QVBoxLayout(side_bar_widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(10, 30, 0, 0);
        widget = new QWidget(side_bar_widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(30);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, -1, 0, 0);
        sideHeadLabel = new QLabel(widget);
        sideHeadLabel->setObjectName(QString::fromUtf8("sideHeadLabel"));
        sideHeadLabel->setMinimumSize(QSize(35, 35));
        sideHeadLabel->setMaximumSize(QSize(35, 35));

        verticalLayout_3->addWidget(sideHeadLabel);

        sideChatLabel = new StateWidget(widget);
        sideChatLabel->setObjectName(QString::fromUtf8("sideChatLabel"));
        sideChatLabel->setMinimumSize(QSize(30, 30));
        sideChatLabel->setMaximumSize(QSize(30, 30));

        verticalLayout_3->addWidget(sideChatLabel);

        sideContactLabel = new StateWidget(widget);
        sideContactLabel->setObjectName(QString::fromUtf8("sideContactLabel"));
        sideContactLabel->setMinimumSize(QSize(30, 30));
        sideContactLabel->setMaximumSize(QSize(30, 30));

        verticalLayout_3->addWidget(sideContactLabel);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(side_bar_widget);

        chat_user_widget = new QWidget(ChatDialog);
        chat_user_widget->setObjectName(QString::fromUtf8("chat_user_widget"));
        chat_user_widget->setMaximumSize(QSize(250, 16777215));
        verticalLayout_2 = new QVBoxLayout(chat_user_widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        searchWidget = new QWidget(chat_user_widget);
        searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        searchWidget->setMinimumSize(QSize(0, 60));
        searchWidget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_2 = new QHBoxLayout(searchWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, 9, 9, 9);
        searchEdit = new CustomizeEdit(searchWidget);
        searchEdit->setObjectName(QString::fromUtf8("searchEdit"));

        horizontalLayout_2->addWidget(searchEdit);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        addBtn = new ClickBtn(searchWidget);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));
        addBtn->setMinimumSize(QSize(24, 24));
        addBtn->setMaximumSize(QSize(24, 24));

        horizontalLayout_2->addWidget(addBtn);


        verticalLayout_2->addWidget(searchWidget);

        chatUserList = new ChatUserList(chat_user_widget);
        chatUserList->setObjectName(QString::fromUtf8("chatUserList"));

        verticalLayout_2->addWidget(chatUserList);

        searchUserList = new SearchList(chat_user_widget);
        searchUserList->setObjectName(QString::fromUtf8("searchUserList"));

        verticalLayout_2->addWidget(searchUserList);

        conUserList = new ContactUserList(chat_user_widget);
        conUserList->setObjectName(QString::fromUtf8("conUserList"));

        verticalLayout_2->addWidget(conUserList);


        horizontalLayout->addWidget(chat_user_widget);

        stackedWidget = new QStackedWidget(ChatDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        chatPage = new ChatPage();
        chatPage->setObjectName(QString::fromUtf8("chatPage"));
        stackedWidget->addWidget(chatPage);
        friendApplyPage = new ApplyFriendPage();
        friendApplyPage->setObjectName(QString::fromUtf8("friendApplyPage"));
        stackedWidget->addWidget(friendApplyPage);
        friendInfoPage = new FriendInfoPage();
        friendInfoPage->setObjectName(QString::fromUtf8("friendInfoPage"));
        stackedWidget->addWidget(friendInfoPage);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(ChatDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QCoreApplication::translate("ChatDialog", "Dialog", nullptr));
        sideHeadLabel->setText(QString());
        addBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
