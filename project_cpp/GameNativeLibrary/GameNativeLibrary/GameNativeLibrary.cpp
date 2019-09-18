#include "GameNativeLibrary.h"
#include "Recast.h"
#include "jni.h"
#include "NavMesh.h"
#include "platform.h"

/*
* Class:     com_highfly029_GameNativeLibrary
* Method:    load
* Signature: (Ljava/lang/String;)I
*/
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_load
(JNIEnv *, jobject, jstring)
{
	printf("Java_com_highfly029_GameNativeLibrary_load");
	return 0;
}

/*
* Class:     com_highfly029_GameNativeLibrary
* Method:    load2
* Signature: (Ljava/lang/String;[B)I
*/
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_load2
(JNIEnv *, jobject, jstring, jbyteArray)
{
	printf("Java_com_highfly029_GameNativeLibrary_load2");
	return 0;
}

/*
* Class:     com_highfly029_GameNativeLibrary
* Method:    find
* Signature: (IFFFFFF)Ljava/util/List;
*/
JNIEXPORT jobject JNICALL Java_com_highfly029_GameNativeLibrary_find
(JNIEnv *, jobject, jint, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat)
{
	printf("Java_com_highfly029_GameNativeLibrary_find");
	return NULL;
}

/*
* Class:     com_highfly029_GameNativeLibrary
* Method:    rayCast
* Signature: (IFFFFFF)Ljava/util/List;
*/
JNIEXPORT jobject JNICALL Java_com_highfly029_GameNativeLibrary_rayCast
(JNIEnv *, jobject, jint, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat)
{
	printf("Java_com_highfly029_GameNativeLibrary_rayCast");
	return NULL;
}

/*
* Class:     com_highfly029_GameNativeLibrary
* Method:    release
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_release
(JNIEnv *, jobject, jint)
{
	printf("Java_com_highfly029_GameNativeLibrary_release");
	return 0;
}