#include <QApplication>
#include <QTextCodec>

#include <QDebug>

#include "AppConfig.h"
#include "MainWindow.h"

#undef main
int main(int argc, char *argv[])
{
//    bool userSoftWareOpenGL = false; //使用软件模拟openGL

//    for (int i=0;i<argc;i++)
//    {
//        QString str = QString(argv[i]);

//        if (str == "usesoftopengl")
//        {
//            userSoftWareOpenGL = true;
//        }
//        else if (str == "harddecoder")
//        {
//            AppConfig::gVideoHardDecoder = true;
//        }
//        qDebug()<<__FUNCTION__<<argv[i]<<str;
//    }

//    if (userSoftWareOpenGL)
//    {
//        qDebug()<<__FUNCTION__<<"\n\n !!! userSoftWareOpenGL !!! \n\n";
//        ///没有安装显卡驱动的系统需要使用软件模拟的openGL，一般是linux系统下会存在这种情况
//        QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
//    }
//    else
//    {
//#if defined(WIN32)
//        QCoreApplication::setAttribute(Qt::AA_UseOpenGLES); //解决windows下使用独立显卡的时候 切换全屏 闪烁问题
//#else

//#endif
//    }

    QApplication a(argc, argv);  // 初始化Qt应用程序
    //  举例 ./myprogram arg1 arg2 arg3
   // 在这个例子中，./myprogram 是程序的名称，arg1、arg2 和 arg3 是传递给程序的参数。这些参数会被存储在 argv 数组中，而参数的数量则会被存储在 argc 变量中。

    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(codec); // 设置GBK文本编解码器用于本地化

    AppConfig::InitAllDataPath(); //初始化一些变量和路径信息
    AppConfig::loadConfigInfoFromFile();// 从文件加载配置信息
     // 写入日志并包含应用程序版本信息
    AppConfig::WriteLog(QString( "\n #############\n Version = %1 \n ##############").arg(AppConfig::VERSION_NAME));

    MainWindow w;
    w.show();

    return a.exec();
}

