/*
 * Serial Assistant Parser
 * 多功能串口调试助手解析程序
 *
 */

#ifndef SAP_H
#define SAP_H

#ifdef __cplusplus
extern "C" {
#endif

/* 相关配置 */
#define MAX_CAMMAND_FUNC_SIZE   9
#define MAX_SWITCH_FUNC_SIZE    4
#define MAX_RECV_BUF            20
#define MAX_SEND_BUF            20
#define MAX_CAMMAND_SIZE        9
#define MAX_SWITCH_SIZE         4
#define MAX_PID_SIZE            6
#define MAX_CUSTOM_ARG_SIZE     10
#define MAX_ARG_WATCH_SIZE      10

#define START_BYTE              0xfe
#define END_BYTE                0xee

enum { Cammand, Switch, PID_Get, CustomGet, PID_Set, CustomSet, ArgWatch};


/* 以下函数由用户实现：
 * 要使本程序正常工作，用户必须定义以下函数：
 *
 * sap_send_byte：
 *     数据发送：发送一个字节到上位机
 *
 * sap_cammand_handler：
 *     当收到一个命令后，用户要做的事
 *     cammand_index： 收到的命令编号
 *     当收到一个命令后，此函数会被解析程序调用
 *     用户可通过cammand_index的值判断到底接收到了哪个命令
 *
 * sap_switch_handler：
 *     当收到一个开关命令后，用户要做的事
 *     switch_index：开关编号
 *     switch_state：开关状态(0：关闭，1：打开)
 *     当收到一个开关命令后，此函数会被解析程序调用
 *     用户可通过switch_index的值判断到底接收到了哪个开关命令
 *     用户可通过switch_state的值判断这个开关的状态
 */
void sap_send_byte(unsigned char byte);
void sap_cammand_handler(int cammand_index);
void sap_switch_handler(int switch_index, int switch_state);


/* 用户通过调用以下函数来配置上位机，使得程序能与上位机正常通信：
 *
 * sap_get_one_byte：
 *  在接收信息里调用来配置接收源，如在串口接收中断里
 *
 * sap_bind_pid:
 *    绑定pid参数，index表示PID编号，剩下的参数是程序里的pid参数的地址
 *    此函数关联了程序里的pid参数和上位机的pid值
 *
 * sap_bind_custom_arg:
 *    绑定自定义参数，index表示参数编号，arg_addr是程序里的相关参数的地址
 *
 * sap_bind_arg_watch：
 *    绑定参数监视，index表示参数编号，arg_addr是程序里的相关参数的地址
 * sap_send_arg_watch：
 *    将绑定的参数发给上位机，在你觉得有必要向上位机更新这个参数的时候调用它
 *    index：参数编号，该参数编号在之前应该和程序里的某个变量绑定（使用sap_bind_arg_watch）
 *
 * sap_send_all_arg_watchs：
 *    将所有绑定的参数发给上位机，在你觉得有必要向上位机更新所有参数的时候调用它
 *    当数据较多时，此函数执行可能会很慢
 */
void sap_get_one_byte(unsigned char byte);
void sap_bind_pid(int index, float *kp_addr, float *ki_addr, float *kd_addr);
void sap_bind_custom_arg(int index, float *arg_addr);
void sap_bind_arg_watch(int index, float *arg_addr);
void sap_send_arg_watch(int index);
void sap_send_all_arg_watchs(void);


/* 以下函数是提供给上位机程序使用的函数，用户程序不需要使用这些函数
 *
 */
#ifdef IN_UPCOMP
void sap_send_cammad(int cammadindex);
void sap_send_switch(int switch_index, int switch_state);
void sap_send_arg(int cmd_type, int index);
void sap_send_request(int request_type, int index);
void sap_get_send_data_frame(unsigned char *frame, int len);
void sap_get_recv_data_frame(unsigned char *frame, int len);
void sap_send_pid(int index);
#endif

#ifdef __cplusplus
}
#endif

#endif /* SERIAL_ASSISTANT_PARSE_H */
