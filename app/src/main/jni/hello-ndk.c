#include <jni.h>
#include <string.h>
//导入日志头文件
#include <android/log.h>
//修改日志tag中的值
#define LOG_TAG "ndk"

#include <unistd.h>
#include <sys/system_properties.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <stdlib.h>


//日志显示的等级
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

/**
 * env代表Java虚拟机，instance代表当前调用此方法的Java对象
 */
JNIEXPORT jstring JNICALL
Java_ndk_com_example_apple_hellondk_MainActivity_strFromNdk(JNIEnv *env, jobject instance) {
    int i;
    char sdkVersion[PROP_VALUE_MAX] = "0";
    __system_property_get("ro.build.version.sdk", sdkVersion);//获取运行环境sdk版本号
    LOGD(sdkVersion);
    i = fork();
    if (i) {
        LOGD("log from c code in parent");
        return (*env)->NewStringUTF(env,
                                    "Hello from JNI !  Compiled with ABI . By XDD from parent");
    } else {
        LOGD("log from c code in child");
        return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI . By XDD from child");

    }

}


JNIEXPORT jstring JNICALL
Java_ndk_com_example_apple_hellondk_MainActivity_passStr(JNIEnv *env, jobject instance,
                                                         jstring javastr_) {
    const char *javastr = (*env)->GetStringUTFChars(env, javastr_, 0);

    // TODO

    char *append = " Modify By Ndk";
    (*env)->ReleaseStringUTFChars(env, javastr_, javastr);
    jstring returnValue = (*env)->NewStringUTF(env, strcat(javastr, append));//拼接字符串

    return returnValue;
}

JNIEXPORT jint JNICALL
Java_ndk_com_example_apple_hellondk_MainActivity_add(JNIEnv *env, jobject instance, jint x,
                                                     jint y) {
//打印 java 传递过来的 jstring ;
    LOGD("log from c code ");
    LOGD("x= %ld", x);
    LOGD("y= %ld", y);
    LOGD("sum= %ld", x + y);
    return x + y;

}

//C代码实现回调需要三个步骤：首先要要获取到 某个对象 , 然后获取对象里面的方法  ,最后 调用这个方法  /
JNIEXPORT void JNICALL
//1.调用java中的无参helloFromJava方法
Java_ndk_com_example_apple_hellondk_MainActivity_callCode(JNIEnv *env, jobject instance) {
// 获取到DataProvider对象
    char *classname = "ndk/com/example/apple/hellondk/MainActivity";
    jclass dpclazz = (*env)->FindClass(env, classname);
    if (dpclazz == 0) {
        LOGD("not find class!");
    } else
        LOGD("find class");
    //第三个参数 和第四个参数 是方法的签名,第三个参数是方法名  , 第四个参数是根据返回值和参数生成的
    //获取到DataProvider要调用的方法
    jmethodID methodID = (*env)->GetMethodID(env, dpclazz, "helloFromJava", "()V");
    if (methodID == 0) {
        LOGD("not find method!");
    } else
        LOGD("find method");
    //调用这个方法
    (*env)->CallVoidMethod(env, instance, methodID);

}

// 2.调用java中的printString方法传递一个字符串
JNIEXPORT void JNICALL
Java_ndk_com_example_apple_hellondk_MainActivity_callCode1(JNIEnv *env, jobject instance) {

    // 获取到DataProvider对象
    char *classname = "ndk/com/example/apple/hellondk/MainActivity";
    jclass dpclazz = (*env)->FindClass(env, classname);
    if (dpclazz == 0) {
        LOGD("not find class!");
    } else
        LOGD("find class");
    // 获取到要调用的method
    jmethodID methodID = (*env)->GetMethodID(env, dpclazz, "printString", "(Ljava/lang/String;)V");
    if (methodID == 0) {
        LOGD("not find method!");
    } else
        LOGD("find method");

    //调用这个方法
    (*env)->CallVoidMethod(env, instance, methodID, (*env)->NewStringUTF(env, "haha"));

}

// 3. 调用java中的add方法 , 传递两个参数 jint x,y
JNIEXPORT void JNICALL
Java_ndk_com_example_apple_hellondk_MainActivity_callCode2(JNIEnv *env, jobject instance) {

    char *classname = "ndk/com/example/apple/hellondk/MainActivity";
    jclass dpclazz = (*env)->FindClass(env, classname);
    jmethodID methodID = (*env)->GetMethodID(env, dpclazz, "add", "(II)I");
    (*env)->CallIntMethod(env, instance, methodID, 3l, 4l);
}

JNIEXPORT void JNICALL
Java_ndk_com_example_apple_hellondk_MainActivity_fillUser(JNIEnv *env, jobject instance,
                                                          jobject user) {
    jclass cls = (*env)->GetObjectClass(env, user);
    jfieldID name = (*env)->GetFieldID(env, cls, "name", "Ljava/lang/String;");
    jstring username = (*env)->NewStringUTF(env, "XDD");
    (*env)->SetObjectField(env, user, name, username);

    jfieldID age = (*env)->GetFieldID(env, cls, "age", "I");
    (*env)->SetIntField(env, user, age, 15);

    char *classname = "ndk/com/example/apple/hellondk/MainActivity";
    jclass dpclazz = (*env)->FindClass(env, classname);
    if (dpclazz == 0) {
        LOGD("not find class!");
    } else
        LOGD("find class");
    jmethodID methodID = (*env)->GetMethodID(env, dpclazz, "notifyOk", "()V");
    if (methodID == 0) {
        LOGD("not find method!");
    } else
        LOGD("find method");
    (*env)->CallVoidMethod(env, instance, methodID);
}

JNIEXPORT void JNICALL
Java_ndk_com_example_apple_hellondk_MainActivity_callCode3(JNIEnv *env, jobject instance) {
    // 通过异常类的完全限定名，获取其对应的jclass对象
    jclass callJniExceptionClass = (*env)->FindClass(env,
                                                     "ndk/com/example/apple/hellondk/CallJniException");
// 判断某个条件，如果需要抛出异常则抛出
    if (1) {
        (*env)->ThrowNew(env, callJniExceptionClass, "Oh,Gosh! I'm crushed!! Help Me !!! ");
        return;
    }

}

