#ifndef APPLYFRIEND_H
#define APPLYFRIEND_H

#include <QDialog>
#include "clickedlabel.h"
#include "friendlabel.h"
#include "userdata.h"

namespace Ui {
class ApplyFriend;
}

class ApplyFriend : public QDialog
{
    Q_OBJECT

public:
    explicit ApplyFriend(QWidget *parent = nullptr);
    ~ApplyFriend();
    void InitTipLbs();
    void AddTipLbs(ClickedLabel*, QPoint cur_point, QPoint &next_point, int text_width, int text_height);
    bool eventFilter(QObject *obj, QEvent *event);
    void SetSearchInfo(std::shared_ptr<SearchInfo> si);
private:
    void resetLabels();
    Ui::ApplyFriend *ui;

    QMap<QString, ClickedLabel*> _add_labels;
    std::vector<QString> _add_label_keys;
    QPoint _label_point;

    QMap<QString, FriendLabel*> _friend_labels;
    std::vector<QString> _friend_label_keys;
    void addLabel(QString name);
    std::vector<QString> _tip_data;
    QPoint _tip_cur_point;
    std::shared_ptr<SearchInfo> _si;

private slots:
    //��ʾ����label��ǩ
    void ShowMoreLabel();
    //����label���»س���������ǩ����չʾ��
    void SlotLabelEnter();
    //�����رգ��Ƴ�չʾ�����ѱ�ǩ
    void SlotRemoveFriendLabel(QString);
    //ͨ������tipʵ�����Ӻͼ��ٺ��ѱ�ǩ
    void SlotChangeFriendLabelByTip(QString, ClickLbState);
    //�������ı��仯��ʾ��ͬ��ʾ
    void SlotLabelTextChange(const QString& text);
    //��������������
    void SlotLabelEditFinished();
    //������ǩ��ʾ��ʾ�򣬵�����ʾ�����ݺ����Ӻ��ѱ�ǩ
    void SlotAddFirendLabelByClickTip(QString text);
    //����ȷ�ϻص�
    void SlotApplySure();
    //����ȡ���ص�
    void SlotApplyCancel();
};

#endif // APPLYFRIEND_H
