#include <jni.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "ql_log.h"
#define FILE_NAME_LEN (64)
#include <linux/gpio.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_gps_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_gps_myapplication_MainActivity_setPermission(JNIEnv *env, jobject /* thiz */) {
    int result = 0;

    // Check if we have root access

   /*result = system("system/xbin/su");
    if (result != 0) {
        LOGE("Root access is not available");
        return -1;
    }*/

    // Execute commands with root privileges

    int ret,fd;

    system("su");

    system("su")

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0) {
        LOGE("Failed to open export file");
        return -1;
    }

    ret = write(fd, "1149", strlen("1149"));
    if (ret < 0) {
        LOGE("Failed to write to export file");
        close(fd);
        return -1;
    }

    fd = open("/sys/class/gpio/gpio1149/direction", O_RDWR);
    if (fd < 0) {
        LOGE("Failed to open direction file");
        close(fd);
        return -1;
    }

    ret = write(fd, "out", strlen("out"));
    if (ret < 0) {
        LOGE("Failed to write to direction file");
        close(fd);
        return -1;
    }

    ret = write(fd, "1", strlen("1"));
    if (ret < 0) {
        LOGE("Failed to write to value file");
        close(fd);
        return -1;
    }





    close(fd);


    //system("/system/xbin/setenforce 0");
    //system("echo 1149 > /sys/class/gpio/export");






   /*
    const char* commands[] = {
            "setenforce 0",
            "echo 1149 > /sys/class/gpio/export",
            "chmod 666 /sys/class/gpio/gpio1149/direction",
            "chmod 666 /sys/class/gpio/gpio1149/value",
            "echo out > /sys/class/gpio/gpio1149/direction"
    };



    LOGE("Executing commands with root privileges");

    for (const auto& cmd : commands) {
        LOGE("Executing command: %s", cmd);
        result = system(cmd);
        LOGE("Executing command: %s", result);
        if (result != 0) {
            LOGE("Failed to execute command: %s", cmd);
            return -1;
        }
    }*/

    return 0;
}

    /*int fd = -1;
    char filename[FILE_NAME_LEN];
    memset(filename,0,sizeof(filename));
    sprintf(filename,"su");
    sprintf(filename,"setenforce 0");
    //export pin 1149
    sprintf(filename,"echo 1149 > /sys/class/gpio/export");
    //chmod 666 /sys/class/gpio/gpio1149
    sprintf(filename,"chmod 666 /sys/class/gpio/gpio1149/direction");
    sprintf(filename,"chmod 666 /sys/class/gpio/gpio1149/value");
    sprintf(filename,"echo out > /sys/class/gpio/gpio1149/direction");

    close(fd);



    return 0;*/





extern "C"
JNIEXPORT jint JNICALL
Java_com_gps_myapplication_MainActivity_getGPIOValue(JNIEnv *env, jobject thiz, jint gpio_num){
    // TODO: implement readGPIOValue()
    int fd = -1;
    char fileName[FILE_NAME_LEN];
    memset(fileName,0,sizeof(fileName));
    sprintf(fileName,"/sys/class/gpio/gpio%d/value",gpio_num);
    fd= open(fileName,O_RDONLY|O_NONBLOCK);
    if(fd<0){
        LOGE("open %s error.",fileName);
        return -1;
    }
    char buf[1];
    int len = read(fd,buf,1);

    if(len!=1){
        LOGE("read %s error.",fileName);
        close(fd);
        return -1;
    }
    close(fd);
    return buf[0]=='1'?1:0;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_gps_myapplication_MainActivity_setGPIOValue(JNIEnv *env, jobject thiz, jint gpio_num,
                                                     jint value){
    // TODO: implement setGPIOValue()
    int fd=-1;
    char fileName[FILE_NAME_LEN];
    memset(fileName,0,sizeof(fileName));
    sprintf(fileName,"/sys/class/gpio/gpio%d/value",gpio_num);
    fd = open(fileName,O_RDWR|O_NONBLOCK);
    if(fd<0){
        LOGE("open %s error.",fileName);
        return -1;
    }
    char buf[1];
    buf[0] = 0==value?'0':'1';
    int len = write(fd,buf,1);
    if(1!=len){
        LOGE("write %s error",fileName);
        close(fd);
        return -1;
    }
    close(fd);
    return 0;

}
