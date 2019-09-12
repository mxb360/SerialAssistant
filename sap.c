#include "sap.h"

/* 解析数据时会遇到的类型和数据结构 */
typedef struct pid_t { float *kp, *ki, *kd; } pid_t;

static unsigned char recv_buf[MAX_RECV_BUF];
static unsigned char send_buf[MAX_SEND_BUF];
static int frame_index = -1;
static int data_count;

static pid_t pids[MAX_PID_SIZE];
static float *custom_args[MAX_CUSTOM_ARG_SIZE];
static float *arg_watchs[MAX_ARG_WATCH_SIZE];

static void sap_parse(void);
static void send_array(unsigned char *arr, int len);

#ifndef IN_UPCOMP
void sap_send_arg(int cmd_type, int index);
void sap_send_pid(int index);
#endif

/* 数据帧解析 */
static void sap_parse(void)
{
    int index;
    int switch_state;

    switch (recv_buf[2])
    {

    /* 命令 */
    case Cammand:
        index = recv_buf[3];
        if (index >= MAX_CAMMAND_SIZE)
            break;
        sap_cammand_handler(index);
        break;

    /* 开关 */
    case Switch:
        index = recv_buf[3];
        switch_state = recv_buf[4];
        if (index >= MAX_SWITCH_SIZE || switch_state > 1)
            break;
        sap_switch_handler(index, switch_state);
        break;

    /* 获取PID */
    case PID_Get:
        index = recv_buf[3];
        if (index >= MAX_PID_SIZE)
            break;
        sap_send_pid(index);
        break;

    /* 获取自定义参数 */
    case CustomGet:
        index = recv_buf[3];
        if (index >= MAX_CUSTOM_ARG_SIZE)
            break;
        sap_send_arg(CustomSet, index);
        break;

    /* 设置PID参数 */
    case PID_Set:
        index = recv_buf[3];
        if (index >= MAX_PID_SIZE)
            break;
        *pids[index].kp = *(float *)(void *)&recv_buf[4];
        *pids[index].ki = *(float *)(void *)&recv_buf[8];
        *pids[index].kd = *(float *)(void *)&recv_buf[12];
        break;

    /* 设置自定义参数 */
    case CustomSet:
        index = recv_buf[3];
        if (index >= MAX_CUSTOM_ARG_SIZE)
            break;
        *custom_args[index] = *(float *)(void *)&recv_buf[4];
        break;

    /* 参数监视 */
    case ArgWatch:
        break;

    default:
        break;
    }
}

/* 发送数组 */
static void send_array(unsigned char *arr, int len)
{
    int i;
    for (i = 0; i < len; i++)
        sap_send_byte(arr[i]);
#ifdef IN_UPCOMP
    sap_get_send_data_frame(arr, len);
#endif
}

/* 发送pid信息 */
void sap_send_pid(int index)
{
    if (!pids[index].kp || !pids[index].ki || !pids[index].kd)
        return;

    send_buf[0] = START_BYTE;
    send_buf[1] = 14;
    send_buf[2] = PID_Set;
    send_buf[3] = (unsigned char)index;
    for (int i = 0; i < 3; i++)
    {
        // 找到与三个pid值绑定的变量的地址，并按照4个字节复制
        unsigned char *p = (unsigned char *)(*((float **)(pids + index) + i));

        for (int j = 0; j < 4; j++)
            send_buf[4 + i*4 + j] = p[j];
    }
    send_buf[16] = END_BYTE;
    send_array(send_buf, 17);
}

/* 发送参数信息 */
void sap_send_arg(int cmd_type, int index)
{
    if ((cmd_type == CustomSet &&!custom_args[index]) ||
        (cmd_type == ArgWatch &&!arg_watchs[index]))
        return;

    send_buf[0] = START_BYTE;
    send_buf[1] = 6;
    send_buf[2] = (unsigned char)cmd_type;
    send_buf[3] = (unsigned char)index;

    if (cmd_type == CustomSet)
    {
        unsigned char *p = (unsigned char *)(*(float **)(custom_args + index));
        for (int i = 0; i < 4; i++)
            send_buf[4 + i] = p[i];
    }
    else if (cmd_type == ArgWatch)
    {
        unsigned char *p = (unsigned char *)(*(float **)(arg_watchs + index));
        for (int i = 0; i < 4; i++)
            send_buf[4 + i] = p[i];
    }
    send_buf[8] = END_BYTE;
    send_array(send_buf, 9);
}

/* 按字节解析 */
void sap_get_one_byte(unsigned char byte)
{
    if (frame_index < 0 && byte == START_BYTE)
        frame_index = 0;
    else if (frame_index < 0)
        return;

    recv_buf[frame_index++] = byte;

    if (frame_index == 2)
        data_count = byte;

    if (frame_index == data_count + 3 && byte != END_BYTE)
    {
        frame_index = -1;
        return;
    }

    if (byte == END_BYTE)
    {
        sap_parse();
#ifdef IN_UPCOMP
        sap_get_recv_data_frame(recv_buf, frame_index);
#endif
        frame_index = -1;
    }
}

/* 绑定pid */
void sap_bind_pid(int index, float *kp_addr, float *ki_addr, float *kd_addr)
{
    if (index < MAX_PID_SIZE)
    {
        pids[index].kp = kp_addr;
        pids[index].ki = ki_addr;
        pids[index].kd = kd_addr;
    }
}

/* 绑定自定义信息 */
void sap_bind_custom_arg(int index, float *arg_addr)
{
    if (index < MAX_CUSTOM_ARG_SIZE)
        custom_args[index] = arg_addr;
}

/* 绑定参数监视 */
void sap_bind_arg_watch(int index, float *arg_addr)
{
    if (index < MAX_ARG_WATCH_SIZE)
        arg_watchs[index] = arg_addr;
}

/* 发送监视的参数 */
void sap_send_arg_watch(int index)
{
    sap_send_arg(ArgWatch, index);
}

/* 发送所有的监视参数 */
void sap_send_all_arg_watchs(void)
{
    int i;
    for (i = 0; i < MAX_ARG_WATCH_SIZE; i++)
        sap_send_arg(ArgWatch, i);
}

#ifdef IN_UPCOMP

/* 发送命令 */
void sap_send_cammad(int cammad_index)
{
    sap_send_request(Cammand, cammad_index);
}

/* 发送开关命令 */
void sap_send_switch(int switch_index, int switch_state)
{
    send_buf[0] = START_BYTE;
    send_buf[1] = 3;
    send_buf[2] = Switch;
    send_buf[3] = (unsigned char)switch_index;
    send_buf[4] = (unsigned char)switch_state;
    send_buf[5] = END_BYTE;
    send_array(send_buf, 6);
}

/* 发送请求 */
void sap_send_request(int request_type, int index)
{
    send_buf[0] = START_BYTE;
    send_buf[1] = 2;
    send_buf[2] = (unsigned char)request_type;
    send_buf[3] = (unsigned char)index;
    send_buf[4] = END_BYTE;
    send_array(send_buf, 5);
}

#endif
