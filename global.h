#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
enum ReqId {
    ID_GET_VARIFY_CODE = 1001, // 获取验证码
    ID_REQ_USER = 1002, // 注册用户
};

enum Modules {
    REGISTERMOD = 0, // 注册模块
};

enum ErrorCodes {
    SUCCESS = 0,
    ERR_JSON = 1,
    ERR_NETWORK = 2,
};

extern QString gate_url_prefix;

#endif // GLOBAL_H
