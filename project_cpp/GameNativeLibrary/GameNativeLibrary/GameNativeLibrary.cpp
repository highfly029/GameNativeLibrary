#include "GameNativeLibrary.h"
#include "Recast.h"
#include "jni.h"
#include "NavMesh.h"
#include "platform.h"


std::tr1::unordered_map<int, NavMesh*> meshHandlers;

static int navMeshIdIncre = 0;

/*
* Class:     com_highfly029_GameNativeLibrary
* Method:    load
* Signature: (Ljava/lang/String;)I
*/
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_load
(JNIEnv * env, jobject jobj, jstring path)
{
	navMeshIdIncre++;
	int navMeshId = navMeshIdIncre;
	char buf[256];
	buf[255] = 0;
	printf("load mesh");
	const char *str = env->GetStringUTFChars(path, 0);
	snprintf(buf, 255, "%s", str);
	env->ReleaseStringUTFChars(path, str);
	NavMesh* nav = new NavMesh();
	bool suc = nav->create(buf);
	if (!suc) {
		printf("create failed\n");
		delete nav;
		return jint(0);
	}
	else {
		printf("create success\n");
		meshHandlers[navMeshId] = nav;
	}
	return jint(navMeshId);
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