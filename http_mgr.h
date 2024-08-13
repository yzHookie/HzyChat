#ifndef HTTP_MGR_H
#define HTTP_MGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include "global.h"
/******************************************************************************
 *
 * @file       http_mgr.h
 * @brief      http 单例类
 *
 * @author     hzy
 * @date       2024/08/13
 * @history
 *****************************************************************************/
// note: crtp
class HttpMgr : public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    HttpMgr();
    ~HttpMgr();
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
private:
    friend class Singleton<HttpMgr>;
    QNetworkAccessManager manager_;
};

#endif // HTTP_MGR_H
