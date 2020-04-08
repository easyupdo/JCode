// Copyright[2019] <Copyright LSX>

#ifndef LSX_ASES_H_
#define LSX_ASES_H_

#ifdef __cplusplus
extern "C" {
#endif

//启动引擎
//  名称：LsxAsesStart
//  参数：
//     params [in] 传入参数
//     err_code [in/out] 错误代码，成功返回0，否则返回错误代码
//  返回：
//     函数调用成功返回字符串格式引擎句柄，失败返回NULL
const char *LsxAsesStart(const char *params, int *err_code);

//关闭引擎
//  名称：LsxAsesStop
//  参数：
//     engine_id [in] 引擎句柄
//  返回：
//     函数调用成功返回0，失败返回错误代码
int LsxAsesStop(const char *engine_id);

//设置引擎参数
//  名称：LsxAsesSetParam
//  参数：
//      engine_id  [in] 引擎句柄
//      name      [in] 参数名称
//      value     [in] 参数值
//  返回:
//      函数调用成功返回0，失败返回错误代码
int LsxAsesSetParam(const char *engine_id, const char *name, const char *value);

//获取引擎信息
//  名称：LsxAsesGetParam
//  参数：
//      engine_id  [in]     引擎句柄
//      name      [in]     参数名称
//      value     [in/out] 存放数据buffer地址
//      value_len [in/out] 数据buffer长度
//  返回:
//      函数调用成功返回0，失败返回错误代码
int LsxAsesGetParam(const char *engine_id, const char *name, char *value, int *value_len);

//启动一次评测任务
//  名称：LsxAsesSessionBegin
//  参数：
//     params           [in]     传入参数
//     err_code         [in/out] 成功返回0，否则返回错误代码
//  返回：
//     函数调用成功返回字符串格式引擎句柄，失败返回NULL
const char *LsxAsesSessionBegin(const char *engine_id, const char *params, int *err_code);

//设置评测任务参数
//    名称：LsxAsesSessionSetParam
//    参数：
//        session_id    [in]     评测任务句柄
//        name          [in]     参数名
//        value         [in]     参数值
//    返回：
//        函数调用成功返回0，失败返回错误代码
int LsxAsesSessionSetParam(const char *session_id, const char *name, const char *value);

//读入评测数据
//    名称：LsxAsesSessionDataIn
//    参数：
//        session_id    [in]     评测任务句柄
//        data          [in]     数据地址
//        data_len      [in]     数据长度
//        params        [in]     数据格式
//    返回：
//        函数调用成功返回0，失败返回错误代码
int LsxAsesSessionDataIn(const char *session_id, const char *data, int data_len, const char *params);

//读入语音数据
//    名称：LsxAsesSessionSpeechIn
//    参数：
//        session_id    [in]     评测任务句柄
//        speech_data   [in]     数据地址
//        speech_len    [in]     数据长度
//        params        [in]     数据格式
//        vad_status    [in/out] 输出VAD状态
//    返回：
//        函数调用成功返回0，失败返回错误代码
int LsxAsesSessionSpeechIn(const char *session_id, const char *data, int data_len,
                           const char *params, int *vad_status);

//获取评测结果
//  名称：LsxAsesSessionGetResult
//  参数：
//      session_id
//      params
//      result_len
//      err_code
//  返回：
//      函数调用成功返回字符串格式评测任务句柄，失败返回NULL
const char *LsxAsesSessionGetResult(const char *session_id, const char *params, int *result_len, int *err_code);

//关闭评测任务
//  名称：LsxAsesSessionEnd
//  参数：
//     session_id: [in] 引擎句柄
//  返回：
//     函数调用成功返回0，失败返回错误代码
int LsxAsesSessionEnd(const char *session_id);

//获取错误信息
// 名称：LsxAsesGetErrorInfo
// 参数：
//    err_code [in] 错误码
// 返回：
//    错误码对应的错误信息字符串。
const char *LsxAsesGetErrorInfo(int err_code);

//引擎版本号
// 名称：LsxAsesVersion
// 参数：
// 返回：
//    版本号字符串
const char *LsxAsesVersion();
#ifdef __cplusplus
}
#endif
#endif  // LSX_ASES_H_
