// project_cpp.cpp : 定义 DLL 应用程序的导出函数。
//

#include "GameNativeLibrary.h"
#include "jni.h"
#include <iostream>

using namespace std;

JNIEXPORT jstring JNICALL Java_com_highfly029_GameNativeLibrary_testJni
  (JNIEnv *env, jclass cls, jstring contentStr)
{
	/**
	//获取字符串指针，必须使用指针，不能使用char strContent[],因为GetStringUTFChars()返回值为const char *;
	const char *strContent = env->GetStringUTFChars(contentStr, JNI_FALSE);

	char str[] = ", welcome to jni world！";

	//字符串拼接,实现strContent+str1,因为strcat的第一个参数必须为非const类型(可变)，所以不能直接使用strcat()
	//创建一个新的字符串指针
	char *strTemp = (char *)malloc(strlen(strContent) + strlen(str) + 1);
	//拷贝常量到字符串指针
	strcpy(strTemp, strContent);
	//拼接str1到strTemp
	strcat(strTemp, str);
	//返回一个utf的jstring
	return env->NewStringUTF(strTemp);
	*/
	return env->NewStringUTF("testJni in cpp with linux");
}

JNIEXPORT void JNICALL Java_com_highfly029_GameNativeLibrary_testReturnVoid
(JNIEnv *, jclass)
{
	cout << "test return void" << endl;
}

JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_testGetInt
(JNIEnv *env, jobject obj, jint jint)
{
	int a = jint + 1;
	return a;
}
