#include "socket.c"
#include <unistd.h>
#include <sys/param.h>
#include <rpc/types.h>
#include <getopt.h>
#include <strings.h>
#include <time.h>
#include <signal.h>

//統計的壓力測試最終結果表示
volatile int timerexpired = 0;
int speed = 0;
int failed = 0;
int bytes = 0;

#define METHOD_GET 0
#define METHOD_HEAD 1
#define METHOD_OPTIONS 2
#define METHOD_TRACE 3

#define PROGRAM_VERSION "1.0"

int method = METHOD_GET
int clients = 1;            //默認支模你一個服務端
int force = 0;              //默認需要等待服務器響應
int force_reload = 0;       //失败时重新请求
int proxyport = 80;         //默认访问服务端口号为80
char *proxyhost = NULL;     //默认无代理服务器
int benchtime = 30;

//globals 版本号
int http10 = 1;             //0:- http/0.9, 1:- http/1.0, 2:-http/1.1


int mypipe[2];
char host[MAXHOSTNAMELEN];
#define REQUEST_SIZE 2048
char request[REQUEST_SIZE];

//函数声明
static void benchcore(const char* host, const int port, const char *request)
static int bench(void)
static void build_request(const char *url)

//用法与各种参数详细含义
static void usage(void){
    fprintf(stderr,
    "webbench [option]... URL\n"
    "   -f|--force                  Don't wait for replay from server.\n"
    "   -r|--reload                 Send reload request - Pragma: no-cache.\n"
    "   -t|--time <sec>             Run benchmark for <sec> seconds. Default 30.\n"
    "   -p|--proxy <server:port>    Use proxy server for request.\n"
    "   -c|--client <n>             Run <n> HTTP clients at once. Default one."
    "   -9|--http09                 Use HTTP/0.9 style request.\n"
    "   -1|--http10                 Use HTTP/1.0 protocol.\n"
    "   -2|--http11                 Use HTTP/1.1 protocol.\n"
    "   --get                       Use GET request method.\n"
    "   --head                      Use HEAD request method.\n"
    "   --options                   Use OPTIONS request method.\n"
    "   --trace                     Use TRACE request method.\n"
    "   -?|-h|--help                This information.\n"    
    "   -V|--version                Display program version.\n"
    );   
}；
//结构体数组:每一个元素格式为：{长选项，选项后是否带有参数，int*指针（为NULL),对应短选项或不为NULL，将第四个参数值给第三个参数值}
static const struct option long_options[]={
    {"force", no_argument, &force, 1},
    {"reload", no_argument, &force_reload, 1},
    {"time", required_argument, NULL, 't'},
    {"help", no_argument, NULL, '?'},
    {"http09", no_argument, NULL, '9'},
    {"http10", no_argument, NULL, '1'},
    {"http11", no_argument, NULL, '2'},
    {"get", no_argument, &method, METHOD_GET},
    {"head", no_argument, &method, METHOD_HEAD},
    {"options", no_argument, &method, METHOD_OPTIONS},
    {"trace", no_argument, &method, METHOD_TRACE},
    {"version", no_argument, NULL, 'V'},
    {"proxy", required_argument, NULL, 'p'},
    {"clients", required_argument, NULL, 'c'},
    {NULL, 0, NULL, 0}
};
int main(int argc, char const *argv[])
{
    int opt = 0;
    int options_index = 0;
    char *tmp = NULL;


    //一.检验命令行参数
    //1.不带选项是直接输出用法help信息
    if(argc == 1){
        usage();
        return 2;
    }
    //2.带选项是则解析命令行参数并根据传入选项进行相关设置

    //getopt_long 为命令行解析的库函数，根据argc来寻找（argc, "912Vfrt:p:c:?h")这两个字符串匹配的选项，
    //如果是段选项，则直接返回这个选项给opt
    //如果市场选项，则到option long_options[]结构体数组中寻找匹配其长选项，返回其对应的段选项给opt,
    //若其第三个参数不为NULL,将第四个参数值给第三个参数，并返回0给opt

    //此函数自带全局变量：
    //optarg:只想选项后的参数： -t 100, 指向100;
    //optind: 当前访问到的argv索引值
    //opterr: 其值非零时，代表有无效选项，缺少参数，输出错误信息
    //optopt: 发现无选项是，函数返回“？ / :", 将其值设为无效选项字符
    while((opt = getopt_long(argc, argv, "912Vfrt:p:c:?h", long_options/*结构体数组指针*/, &options_index)) != EOF)
    {
        switch(opt)     //根据返回值判断用户传入的参数进行相关设置
        {
            case 0  : break;
            case 'f': force = 1;break;          //force=1代表不等待服务器相应
            case 'r': force_reload = 1;break;   //发送重新加载请求
            
            case '9': http10 = 0;break;
            case '1': http10 = 1;break;
            case '2': http10 = 2;break;
            case 'V':
                    printf(PROGRAM_VERSION"\n");
                    exit(0);
            case 't':
                    benchtime = atoi(optarg);
            case 'c':
                    clients = atoi(optarg);
            case 'p':
                    tmp = strrchr(optarg, ':');
                    proxyhost = optarg;

                    if(tmp == NULL){
                        break;
                    }
                    if(tmp == optarg){
                        fprint(stderr, "Error in option --proxy %s: Missing hostname.\n", optarg);
                        return 2;
                    }
                    if(tmp == optarg + strlen(optarg) - 1) //: 号在末位， 缺少端口号
                    {
                        fprint(stderr, "Error in option --proxy %s Port number is missing.\n", optarg);
                        return 2;
                    }

                    *tmp = '\0';

                    proxyport = atoi(tmp+1);

                    break;
            case ':':
            case 'h':
            case '?':usage();return 2;break;
        }
    }


    
    return 0;
}
