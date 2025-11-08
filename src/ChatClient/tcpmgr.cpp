#include "tcpmgr.h"
#include "usermgr.h"
TcpMgr::~TcpMgr(){

}

TcpMgr::TcpMgr():_host(""),_port(0),_b_recv_pending(false),_message_id(0),_message_len(0)
{
    //监听连接
    QObject::connect(&_socket, &QTcpSocket::connected, this, [&](){
        qDebug() << "Connected to server";
        emit sig_con_success(true);
    });
    //监听读事件
    connect(&_socket, &QTcpSocket::readyRead,this,[&](){
        //当数据可读时读出所有数据，加到缓冲区
        _buffer.append(_socket.readAll());
        QDataStream stream(&_buffer, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_15);

        forever{
            //先解析头部
            if(!_b_recv_pending){
                //sizeof(quint16)为2字节，这里就表示整个头部为4字节
                if(_buffer.size() < static_cast<int>(sizeof(quint16)*2)){
                    return;
                }
                //读取消息ID和消息长度，但不存_buffer中删除
                stream >> _message_id >> _message_len;

                //将前四个字节移除
                _buffer = _buffer.mid(sizeof(quint16)*2);

                qDebug() << "message id is " << _message_id << " message length is " << _message_len;

            }

            if(_buffer.size() < _message_len){
                //如果剩余长度不足消息体的长度，则下一次不用解析头部
                _b_recv_pending = true;
                return;
            }
            _b_recv_pending = false;
            //读出消息体
            QByteArray messageBody = _buffer.mid(0,_message_len);
            qDebug() << "recv message is "<<messageBody;
            //前_message_len已经读取了，执行下面则是从_message_len开始截取到末尾又存在_buffer中，实现保存后面的数据而丢弃前_message_len个字节的数据
            _buffer = _buffer.mid(_message_len);
            handleMsg(ReqId(_message_id),_message_len,messageBody);
        }
    });
    //错误打印
    connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),this,[&](QAbstractSocket::SocketError socketerror){
        Q_UNUSED(socketerror)
        qDebug() << "Error is "<<_socket.errorString();
    });

    //处理连接断开
    connect(&_socket, &QTcpSocket::disconnected, this, [&](){
        qDebug() << "connect was disconnected";
    });
    //
    connect(this, &TcpMgr::sig_send_data, this, &TcpMgr::slot_send_data);
    InitHandlers();
}

void TcpMgr::InitHandlers()
{
    _handlers.insert(ID_CHAT_LOGIN_RSP,[this](ReqId id, int len, QByteArray data){
        Q_UNUSED(len);
        qDebug() << "handle id is "<< id << " data is " << data;
        //
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if(jsonDoc.isNull()){
            qDebug() << "failed to create QjsonDocument";
            return;
        }
        QJsonObject jsonObj = jsonDoc.object();
        if(!jsonObj.contains("error")){
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Login failed, err is json Prase err" << err;
            emit sig_login_failed(err);
        }
        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::SUCCESS){
            qDebug() << "Login failed, err is " << err;
            emit sig_login_failed(err);
            return;
        }
        UserMgr::GetInstance()->SetName(jsonObj["name"].toString());
        UserMgr::GetInstance()->SetToken(jsonObj["token"].toString());
        UserMgr::GetInstance()->SetUid(jsonObj["uid"].toInt());
        emit sig_switch_chatdlg();
    });
}

void TcpMgr::handleMsg(ReqId id, int len, QByteArray data)
{
    auto find_iter = _handlers.find(id);
    if(find_iter == _handlers.end()){
        qDebug() << "not found id [" << id << "] to handle";
        return;
    }
    find_iter.value()(id, len, data);
}

void TcpMgr::slot_tcp_connect(ServerInfo si)
{
    qDebug() << "Recv tcp connect";
    //尝试连接服务器
    qDebug() << "connecting to server";

    _host = si.Host;
    _port = static_cast<int>(si.Port.toUInt());

    //连接服务器
    _socket.connectToHost(_host, _port);
}

void TcpMgr::slot_send_data(ReqId reqId, QString data)
{
    uint16_t id = reqId;

    QByteArray dataArray = data.toUtf8();

    //计算长度，使用网络字节序转换
    quint16 len = static_cast<quint16>(data.length());

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setByteOrder(QDataStream::BigEndian);

    //先写入id和长度
    out << id << len;
    //添加字符串数据
    block.append(data);
    //发送数据
    _socket.write(block);
}























