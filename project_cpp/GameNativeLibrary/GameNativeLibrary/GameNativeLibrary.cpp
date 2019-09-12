// project_cpp.cpp : ���� DLL Ӧ�ó���ĵ���������
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
    printf("Java Str:%x %s %d %d\n", c_str, c_str, strlen(c_str), isCopy);
    sprintf_s(buff, "hello %s", c_str);
    env->ReleaseStringUTFChars(j_str, c_str);
    return env->NewStringUTF(buff);
}