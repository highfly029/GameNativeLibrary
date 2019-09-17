// project_cpp.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "GameNativeLibrary.h"
#include "jni.h"
#include <iostream>

using namespace std;

JNIEXPORT jstring JNICALL Java_com_highfly029_GameNativeLibrary_testJni
  (JNIEnv *env, jclass cls, jstring contentStr)
{
	/**
	//��ȡ�ַ���ָ�룬����ʹ��ָ�룬����ʹ��char strContent[],��ΪGetStringUTFChars()����ֵΪconst char *;
	const char *strContent = env->GetStringUTFChars(contentStr, JNI_FALSE);

	char str[] = ", welcome to jni world��";

	//�ַ���ƴ��,ʵ��strContent+str1,��Ϊstrcat�ĵ�һ����������Ϊ��const����(�ɱ�)�����Բ���ֱ��ʹ��strcat()
	//����һ���µ��ַ���ָ��
	char *strTemp = (char *)malloc(strlen(strContent) + strlen(str) + 1);
	//�����������ַ���ָ��
	strcpy(strTemp, strContent);
	//ƴ��str1��strTemp
	strcat(strTemp, str);
	//����һ��utf��jstring
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
