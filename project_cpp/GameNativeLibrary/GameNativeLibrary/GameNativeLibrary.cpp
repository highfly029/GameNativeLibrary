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
(JNIEnv * env, jobject jObj, jstring, jbyteArray jbyteArray)
{
	navMeshIdIncre++;
	int navMeshId = navMeshIdIncre;

	jbyte* olddata = (jbyte*)env->GetByteArrayElements(jbyteArray, 0);

	jsize length = env->GetArrayLength(jbyteArray);
	NavMesh* nav = new NavMesh();
	bool suc = nav->create_core((uint8*)olddata, length);


	if (!suc) {
		printf("create failed\n");
		delete nav;
		return jint(0);
	}
	else {
		printf("create success\n");
		meshHandlers[navMeshId] = nav;
	}


	env->ReleaseByteArrayElements(jbyteArray, olddata, 0);
	return jint(navMeshId);
}

/*
* Class:     com_highfly029_GameNativeLibrary
* Method:    find
* Signature: (IFFFFFF)Ljava/util/List;
*/
JNIEXPORT jobject JNICALL Java_com_highfly029_GameNativeLibrary_find
(JNIEnv * env, jobject jobj, jint navMeshId, jfloat x1, jfloat y1, jfloat z1, jfloat x2, jfloat y2, jfloat z2)
{
	std::tr1::unordered_map<int, NavMesh*>::iterator iter = meshHandlers.find(navMeshId);
	if (iter == meshHandlers.end())
	{
		return NULL;
	}
	NavMesh* nav = iter->second;

	float start[3];
	start[0] = x1;
	start[1] = y1;
	start[2] = z1;

	float end[3];
	end[0] = x2;
	end[1] = y2;
	end[2] = z2;


	std::vector<Position3D> outPaths;

	int ret = nav->findStraightPath(start, end, outPaths);

	if (ret > 0) {
		jclass class_arraylist = env->FindClass("java/util/ArrayList");
		jmethodID hashmap_construct_method = env->GetMethodID(class_arraylist, "<init>", "()V");
		jobject obj_hashmap = env->NewObject(class_arraylist, hashmap_construct_method, "");

		jmethodID arraylist_add_method = env->GetMethodID(class_arraylist, "add", "(Ljava/lang/Object;)Z");
		int m = 0;
		std::vector<Position3D>::iterator iter = outPaths.begin();
		for (; iter != outPaths.end(); ++iter)
		{
			jfloat tmp[3];
			tmp[0] = iter->x;
			tmp[1] = iter->y;
			tmp[2] = iter->z;
			jfloatArray args = (env)->NewFloatArray(3);
			env->SetFloatArrayRegion(args, 0, 3, tmp);

			env->CallBooleanMethod(obj_hashmap, arraylist_add_method, args);

			m++;
		}

		return obj_hashmap;
	}

	return NULL;
}

/*
* Class:     com_highfly029_GameNativeLibrary
* Method:    rayCast
* Signature: (IFFFFFF)Ljava/util/List;
*/
JNIEXPORT jobject JNICALL Java_com_highfly029_GameNativeLibrary_rayCast
(JNIEnv * env, jobject jobj, jint navMeshId, jfloat x1, jfloat y1, jfloat z1, jfloat x2, jfloat y2, jfloat z2)
{
	std::tr1::unordered_map<int, NavMesh*>::iterator iter = meshHandlers.find(navMeshId);
	if (iter == meshHandlers.end())
	{
		return NULL;
	}
	NavMesh* nav = iter->second;

	float start[3];
	start[0] = x1;
	start[1] = y1;
	start[2] = z1;

	float end[3];
	end[0] = x2;
	end[1] = y2;
	end[2] = z2;


	std::vector<Position3D> hitPoints;

	int ret = nav->raycast(start, end, hitPoints);

	if (ret == 1) {
		jclass class_arraylist = env->FindClass("java/util/ArrayList");
		jmethodID hashmap_construct_method = env->GetMethodID(class_arraylist, "<init>", "()V");
		jobject obj_hashmap = env->NewObject(class_arraylist, hashmap_construct_method, "");

		jmethodID arraylist_add_method = env->GetMethodID(class_arraylist, "add", "(Ljava/lang/Object;)Z");
		int m = 0;
		std::vector<Position3D>::iterator iter = hitPoints.begin();
		for (; iter != hitPoints.end(); ++iter)
		{
			jfloat tmp[3];
			tmp[0] = iter->x;
			tmp[1] = iter->y;
			tmp[2] = iter->z;
			jfloatArray args = (env)->NewFloatArray(3);
			env->SetFloatArrayRegion(args, 0, 3, tmp);

			env->CallBooleanMethod(obj_hashmap, arraylist_add_method, args);

			m++;
		}

		return obj_hashmap;
	}

	return NULL;
}

/*
* Class:     com_highfly029_GameNativeLibrary
* Method:    release
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_release
(JNIEnv *, jobject, jint navMeshId)
{
	std::tr1::unordered_map<int, NavMesh*>::iterator iter = meshHandlers.find(navMeshId);
	if (iter != meshHandlers.end())
	{
		NavMesh* navMesh = iter->second;
		meshHandlers.erase(iter);
		delete navMesh;
	}
	return 0;
}