#ifndef OURCONTROL_H
#define OURCONTROL_H

#include <stdint.h>
#include <string>
#include <vector>
#include <map>

#define PACKED  __attribute__((__packed__))

typedef unsigned char uchar;

typedef struct PACKED
{
    uint32_t sof;
    uint32_t len;

}our_control_json_header;

#define OUR_JSON_HEADERSIZE sizeof(our_control_json_header)


typedef struct PACKED
{
    uint32_t crc;
    uint32_t end;

}our_control_json_tail;

#define OUR_JSON_TAILSIZE sizeof(our_control_json_tail)

typedef struct
{
    our_control_json_header json_header;
    std::string     json_data;
    our_control_json_tail   json_tail;
}our_control_json_frame;

typedef enum{
    //login,logout
    our_control_cmd_login,                    //系统登陆
    our_control_cmd_logout,                   //系统退出

    //robot status
    our_control_cmd_get_robot_status,         //读取机械臂状态
    our_control_cmd_get_joint_status,         //读取机械臂关节状态
    our_control_cmd_get_controlbox_status,    //读取控制柜状态
    our_control_cmd_get_robot_all_status,     //读取所有状态（美克需求）

    //robot position
    our_control_cmd_get_robot_position,       //读取机械臂当前状态
    our_control_cmd_get_end_speed,            //读取机械臂末端速度

    //featrure
    our_control_cmd_get_feature_list,         //读取平面坐标系列表

    //event
    our_control_cmd_event,                    //机械臂系统事件

    //robot move control
    our_control_cmd_move_j,                   //机械臂关节移动
    our_control_cmd_move_l,                   //机械臂直线运动
    our_control_cmd_move_p,                   //机械臂轨迹运动
    our_control_cmd_move_l_to,                //机械臂保持位姿直线运动到目标位置

    //project control
    our_control_cmd_project_getlist,          //获取ORPE中所有工程列表
    our_control_cmd_project_load,             //设置ORPE当前加载工程
    our_control_cmd_project_control,          //ORPE工程控制（启动，停止，暂停）
    our_control_cmd_project_getstatus,        //获取ORPE工程状态（启动，停止，暂停）

    //enable/disable event
    our_control_cmd_enable_position_event,    //允许ORPE持续返回当前位置（5毫秒一次）
    our_control_cmd_disenable_position_event, //禁止ORPE持续返回当前位置

    //robot control
    our_control_cmd_robot_power_control,      //设置机械臂48V电源状态
    our_control_cmd_robot_brake_control,      //设置机械臂刹车状态
    our_control_cmd_robot_collision_class,    //设置机械臂碰撞等级
    our_control_cmd_robot_enalbe_read_pose,   //设置接口板是否允许读取自身位姿

    //device info
    our_control_cmd_get_device_info,          //读取机械臂设备信息

    //io control
    our_control_cmd_get_io_config,            //获取所有IO设置
    our_control_cmd_get_io_status,            //获取指定IO状态
    our_control_cmd_set_io_status,            //设置指定IO状态

    //coord convert
    our_control_cmd_robot_coord_convert,      //坐标系转换

    //tpc center param
    our_control_cmd_set_robot_tcp_center,     //设置TCP中心
    our_control_cmd_get_robot_tcp_center,     //获取TCP中心

    //teach move
    our_control_cmd_teach_point_move,         //控制机器人沿着试教点运动
    our_control_cmd_teach_joint_move,         //控制机器人轴动

    //armik,armfk
    our_control_cmd_arm_ik,                   //逆解
    our_control_cmd_arm_fk,                   //正解

    //robot init
    our_control_cmd_get_robot_init_status,    //获取机械臂初始化状态

    //robot control
    our_control_cmd_robot_control,            //机械臂控制

    //switch robot run mode
    our_control_cmd_set_robot_mode,           //设置机械臂仿真模式/真实模式
    our_control_cmd_get_robot_mode,           //获取机械臂仿真模式/真实模式

    //command count
    our_control_cmd_count,

    //unknown command
    our_control_unknown_command

}our_control_command;

typedef struct
{
    our_control_command cmd;
    std::string command_str;
}our_json_command;

typedef struct
{
    std::string user_name;
    std::string user_pwd;
}our_control_login;

typedef struct
{
    std::string project_name;
    std::string feature_name;
    float relative_offset_x;
    float relative_offset_y;
    float relative_offset_z;
}our_control_project_load;

typedef enum
{
    project_no_opera,
    project_start,
    project_stop,
    project_pause,
}our_project_control;

typedef struct
{
    std::string project_name;
    std::string descripiton;
}our_project_info;

typedef enum
{
    robot_running,
    robot_stop,
    robot_pause,
    robot_emergency,

    robot_unknown = 9
}our_robot_status;

typedef enum
{
    robot_project_ready = 0,
    robot_project_running,
    robot_project_step_running,
    robot_project_suspend
}our_project_status;

typedef struct
{
    double pos[3];       //x,y,z coodinate
    double ori[4];       //w,x,y,z
    double joint_pos[6]; //joint1~6 angle
}our_robot_road_point;

typedef struct
{
    our_robot_status robot_status;
    our_robot_road_point pos_on_base_coord;
    our_robot_road_point pos_on_tool_coord;
    our_robot_road_point pos_on_user_coord;
}our_control_robot_status;


typedef enum
{
    no_convert,
    base_to_user,
    user_to_base,
}coord_convert_type;

typedef struct
{
    coord_convert_type convert_type;

    double tcp[3];//x,y,z tool offset;

    our_robot_road_point plane_points[3];

    //source_point
    our_robot_road_point source_point;

    //target_point
    our_robot_road_point target_point;

    bool orientation_used;

}our_control_coord_convert;


typedef enum {
    our_feature_base = 0,
    our_feature_end,
    our_feature_user
}our_feature_type;


typedef struct{
    std::string feature_name;
    our_robot_road_point plane[3];
}our_control_feature;


typedef enum
{
    our_move_mode_j = 1,
    our_move_mode_l,
    our_move_mode_p,
    our_move_unknown_mode
}our_move_mode_type;


typedef enum
{
    arc = 0,
    circular,
    cartesian_cubicspline,
    cartesian_ubsplineintp,
    cartesian_movep,
    jiont_cubicspline = 20,
    joint_ubsplineintp,
    track_mode_count = 6

}our_move_track_type;

typedef struct{
    double max_velc_jc;
    double max_acc_jc;
    bool scurve;
    our_move_mode_type move_mode;
    our_move_track_type move_track;
    bool tool_track;
    bool relative_move;
    our_feature_type user_coord;
    float relative_position[3];
    float tcp[3];
    double blend_radius;
    our_control_feature feature;

}robot_move_profile;

typedef enum{
    move_x,
    move_y,
    move_z,
    rotate_x,
    rotate_y,
    rotate_z
}robot_moveway;

typedef enum{
    real_coord = 0x01,
    word_coord = 0x02,
    base_coord = 0x03
}robot_coord_type;

typedef struct{
    robot_coord_type coordinage;
    robot_moveway move_code;
    int speed;
    double move_step;
}robot_teach_point_move;

typedef struct{
    bool dir;
    int joint_id;
    int speed;
    double joint_step; //default=1000
}robot_teach_joint_move;



typedef enum
{
    our_control_ok,
    our_control_json_error
}our_control_command_result;

typedef struct
{
    our_control_command response_command;
    std::string error_msg;
    uint8_t error_code;
}json_cmd_response;

typedef struct
{
    int len;
    uchar *buf;
}our_com_frame;


/**
 * event define
 */
typedef enum{
    robot_event_current_pos,
    robot_event_soft_emergency,
    robot_event_collision,
    robot_event_over_speed,
    robot_event_force_control,
    robot_event_joint_error,
    robot_event_at_track_target_pos,
    robot_event_mounting_pose_changed,
    robot_event_project_status_changed,

    //event count
    robot_event_count,

    //unknown event
    robot_event_unknown
}our_control_event;

typedef struct
{
    our_control_event event_id;
    std::string desc;
}our_event;

typedef enum
{
    io_bus_type_plc,
    io_bus_type_tool,
    io_bus_type_board,
    io_bus_type_modbus
}our_contorl_io_type;

typedef enum
{
    io_mode_do,
    io_mode_di,
    io_mode_ao,
    io_mode_ai
}our_contorl_io_mode;

typedef struct
{
    our_contorl_io_type io_type;
    our_contorl_io_mode io_mode;
    int io_index;
}our_contorl_io_config;

typedef struct
{
    our_contorl_io_type  io_type;
    our_contorl_io_mode  io_mode;
    int      io_index;
    double   io_value;
}our_control_io_status;

typedef struct
{
    int     joint_id;
    float   joint_voltage;
    float   joint_current;
    float   joint_temperature;
}our_control_joint_status;

typedef struct
{
    //硬件版本 (u16)(100)
    unsigned short hw_version;
    //固件版本 (u16)((15<<9)|(5<<5)|(13)) 表示：2015年5月13日
    unsigned short sw_version;
}our_control_joint_version;

typedef struct
{
    //设备型号、芯片型号：上位机主站：0x01  接口板0x02
    unsigned char type;
    //设备版本号，V1.0
    std::string revision;
    //厂家ID，"OUR "的ASCII码0x4F 55 52 00
    std::string manu_id;
    //机械臂类型
    std::string joint_type;
    //机械臂关节及工具端信息
    our_control_joint_version joint_ver[7];
    //设备描述字符串以0x00结束
    std::string desc;

}our_control_robot_device_info;

typedef struct
{
    //机械臂48V电源当前电流
    float power_current;
    //机械臂48V电源当前电压
    float power_voltage;
    //机械臂48V电源状态（开、关）
    bool  power_status;
    //控制箱温度
    char  controller_temp;
    //控制箱湿度
    uchar controller_humidity;
    //远程关机信号
    bool  remote_halt;
    //机械臂软急停
    bool  soft_emergency;
    //远程急停信号
    bool  remote_emergency;
    //碰撞检测位
    bool  robot_collision;
    //机械臂进入力控模式标志位
    bool  force_control_mode;
    //刹车状态
    bool brake_stuats;
    //末端速度
    float end_speed;
    //最大加速度
    int max_acc;
    //位姿读取使能位
    bool enble_read_pose;
    //安装位置状态
    bool mounting_pose_changed;
    //磁编码器错误状态
    bool encoder_error_status;
}our_control_robot_system_status;

typedef std::map<int, our_com_frame*> OUR_CLENT_MAP;


typedef struct
{
    //TCP距离中心点距离X（单位，毫米）
    float x;
    //TCP距离中心点距离Y（单位，毫米）
    float y;
    //TCP距离中心点距离Z（单位，毫米）
    float z;
    //TCP负载重量（单位，公斤）
    float payload;

}our_control_tpc_center;

typedef struct
{
    our_control_tpc_center runtime;  //运行时负载
    our_control_tpc_center manual;   //手动时负载
}our_control_tcp_center_param;

typedef enum{
    robot_release                   = 0, //释放刹车
    robot_brake                     = 1, //刹车
    overspeed_warning               = 2, //拖动示教速度过快报警
    overspeed_recover               = 3, //解除拖动过速报警
    disable_force_control           = 4, //失能力控
    enable_force_control            = 5, //使能力控
    orpe_open                       = 6, //打开上位机软件
    erpe_close                      = 7, //关闭上位机软件
    enable_read_pose                = 8, //打开读取位姿
    disable_read_pose               = 9, //关闭读取位姿
    mounting_pose_changed           = 10,//安装位置已改变
    mounting_pose_unchanged         = 11,//安装位置未改变
    enable_static_collision_detect  = 12,//打开静止碰撞检测
    disable_static_collision_detect = 13 //关闭静止碰撞检测
}our_control_robot_command;

typedef enum {
    no_error      = 0, //无错误
    over_voltage  = 1, //过压
    under_voltage = 2, //欠压
    over_temp     = 3, //过温
    canbus_error  = 4  //CAN总线错误
}our_control_robot_tool_status;

typedef struct
{
    unsigned short current1;
    unsigned short current2;
    unsigned short current3;
    unsigned short current4;
}our_control_joint_collision_current;

typedef struct
{
    our_control_joint_collision_current joint1;
    our_control_joint_collision_current joint2;
    our_control_joint_collision_current joint3;
    our_control_joint_collision_current joint4;
    our_control_joint_collision_current joint5;
    our_control_joint_collision_current joint6;
    uchar collision_class;

}our_control_robot_collision_param;


typedef enum{
    robot_mode_simulator, //机械臂仿真模式
    robot_mode_real,       //机械臂真实模式
    robot_mode_unknow
}our_control_robot_mode;



typedef enum{
    state_ready,                  //ready
    state_connect_interfaceboard, //正在链接接口板
    state_init_ok,                //初始化成功
    state_init_failed,            //链接接口板失败，请检查接口板RJ45链接线是否链接正常
}our_control_init_status;



#define RESPONSE_COMMAND     "response_command"
#define RESPONSE_ERROR_CODE  "error_code"
#define RESPONSE_ERROR_MSG   "error_msg"

#define TCP_MESSAGE_SOF_BYTE 4                //MESSAGE_SOF
#define TCP_MESSAGE_DATA_LEN_BYTE 4           //MESSAGE_DATA_LEN
#define TCP_MESSAGE_DATA_MAX_BYTE (1024*1024) //MESSAGE_DATA
#define TCP_MESSAGE_CRC_BYTE 4                //CRC
#define TCP_MESSAGE_END_BYTE 4                //MESSAGE_END
#define TCP_MESSAGE_PACKAGE_BYTE   (TCP_MESSAGE_SOF_BYTE+TCP_MESSAGE_DATA_LEN_BYTE+TCP_MESSAGE_DATA_MAX_BYTE+TCP_MESSAGE_CRC_BYTE+TCP_MESSAGE_END_BYTE)

#define TCP_MESSAGE_BYTE (4*1024)


#endif // OURCONTROL_H
