#include "http_mgr.h"
#include <QNetworkReply>

HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::SigHttpFinish, this, &HttpMgr::SlotHttpFinish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod) {
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest requset(url);
    requset.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    requset.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    QNetworkReply* reply = manager_.post(requset, data);
    connect(reply, &QNetworkReply::finished, [self = shared_from_this(), reply, req_id, mod]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            emit self->SigHttpFinish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }

        QString res = reply->readAll();
        emit self->SigHttpFinish(req_id, res, ErrorCodes::SUCCESS, mod);
    });
}

void HttpMgr::SlotHttpFinish(ReqId id, QString res, ErrorCodes err, Modules mod) {
    if (mod == Modules::REGISTERMOD) {
        // 发送信号通知指定模块 http 的响应
        emit SigReqModFinish(id, res, err);
    }
}
