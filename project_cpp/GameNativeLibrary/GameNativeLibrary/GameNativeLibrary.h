/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jni.h"
/* Header for class com_highfly029_GameNativeLibrary */

#ifndef _Included_com_highfly029_GameNativeLibrary
#define _Included_com_highfly029_GameNativeLibrary
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    load
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_load
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    load2
 * Signature: (Ljava/lang/String;[B)I
 */
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_load2
  (JNIEnv *, jobject, jstring, jbyteArray);

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    find
 * Signature: (IFFFFFF)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_com_highfly029_GameNativeLibrary_find
  (JNIEnv *, jobject, jint, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    rayCast
 * Signature: (IFFFFFF)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_com_highfly029_GameNativeLibrary_rayCast
  (JNIEnv *, jobject, jint, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    release
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_release
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
