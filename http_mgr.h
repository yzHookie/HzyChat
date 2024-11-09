#ifndef HTTP_MGR_H
#define HTTP_MGR_H

/******************************************************************************
 *
 * @file       http_mgr.h
 * @brief      http管理类
 *
 * @author     hzy
 * @date       2024/11/09
 * @history
 *****************************************************************************/
#include "singleton.h"
#include "global.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

// CRTP
class HttpMgr : public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr> {
    Q_OBJECT

public:
    ~HttpMgr() = default;

    /**
     * @brief 发送 http 请求
     * @param url
     * @param json 发送的内容
     * @param req_id 请求的类型
     * @param mod 属于哪个功能模块
     */
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private:
    friend class Singleton<HttpMgr>;
    // 单例的构造函数要私有
    HttpMgr();

    QNetworkAccessManager manager_;
private slots:
    /**
     * @brief 发送请求后回包的结果槽函数
     * @param id 请求的类型
     * @param res 返回的结果
     * @param err 错误类型
     * @param mod 属于哪个功能模块
     */
    void SlotHttpFinish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    /**
     * @brief 发送请求后回包的结果信号
     * @param id 请求的类型
     * @param res 返回的结果
     * @param err 错误类型
     * @param mod 属于哪个功能模块
     */
    void SigHttpFinish(ReqId id, QString res, ErrorCodes err, Modules mod);
    // 是注册模块回包的结果信号
    void SigReqModFinish(ReqId id, QString res, ErrorCodes err);

};

#endif // HTTP_MGR_H
