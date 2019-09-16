// project_cpp.cpp : 定义 DLL 应用程序的导出函数。
//

#include "GameNativeLibrary.h"
#include "jni.h"
#include <iostream>

using namespace std;

JNIEXPORT jstring JNICALL Java_com_highfly029_GameNativeLibrary_testJni
  (JNIEnv *env, jclass cls, jstring j_str)
{
	cout << "Hello Jni" << endl;
	const char *c_str = NULL;
    char buff[128] = { 0 };
    jboolean isCopy;
    c_str = env->GetStringUTFChars(j_str, &isCopy);
    if (c_str == NULL)
    {
        printf("out of memory.\n");
        return NULL;
    }
    env->ReleaseStringUTFChars(j_str, c_str);
    return env->NewStringUTF(buff);
}