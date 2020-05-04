#include "com_highfly029_GameNativeLibrary.h"
#include "SoloMesh.h"
#include "TempObstacle.h"
#include <map>  //注意，STL头文件没有扩展名.h
#include <string>
using namespace std;

static const int MODE_SOLOMESH = 1;
static const int MODE_TILECACHE = 2;

map<string, SoloMesh*> soloMeshMap;
map<string, TempObstacle*> tempObstacleMap;
/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    setPrint
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_highfly029_GameNativeLibrary_setPrint
  (JNIEnv *env, jobject obj, jint mode, jstring name, jboolean isPrint)
{
    unsigned char bool_isPrint = isPrint;
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (mode == MODE_SOLOMESH)
    {
        map<string, SoloMesh*>::iterator iter = soloMeshMap.find(nameStr);
        if (iter != soloMeshMap.end())
        {
            if (iter->second != NULL)
            {
                iter->second->setPrint(bool_isPrint);
            }
            
        }
            
    } else if (mode == MODE_TILECACHE)
    {
        
    }
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    loadNavMesh
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_highfly029_GameNativeLibrary_loadNavMesh
  (JNIEnv *env, jobject obj, jint mode, jstring path, jstring name)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (nameStr == "")
    {
        return jint(-1);
    }

    if (mode == MODE_SOLOMESH)
    {
        map<string, SoloMesh*>::iterator iter = soloMeshMap.find(nameStr);
        if (iter != soloMeshMap.end())
        {
            return true;
        }
        SoloMesh* tool = new SoloMesh();
        bool isSuccess = tool->loadNavMesh(nameStr.c_str());
        if (isSuccess)
        {
            soloMeshMap[nameStr] = tool;
            return true;
        } else 
        {
            return false;
        }
        
    } else if (mode == MODE_TILECACHE)
    {
        
    }
    
    return false;
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    findPathStraight
 * Signature: (ILjava/lang/String;FFFFFF)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_com_highfly029_GameNativeLibrary_findPathStraight
  (JNIEnv *env, jobject obj, jint mode, jstring name, jfloat x1, jfloat y1, jfloat z1, jfloat x2, jfloat y2, jfloat z2)
{
    return NULL;
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    raycast
 * Signature: (ILjava/lang/String;FFFFFF)[F
 */
JNIEXPORT jfloatArray JNICALL Java_com_highfly029_GameNativeLibrary_raycast
  (JNIEnv *env, jobject obj, jint mode, jstring name, jfloat x1, jfloat y1, jfloat z1, jfloat x2, jfloat y2, jfloat z2)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (mode == MODE_SOLOMESH)
    {
        map<string, SoloMesh*>::iterator iter = soloMeshMap.find(nameStr);
        if (iter != soloMeshMap.end())
        {
            if (iter->second != NULL)
            {
                SoloMesh* soloMesh = iter->second;
                float start[3];
                start[0] = x1;
                start[1] = y1;
                start[2] = z1;

                float end[3];
                end[0] = x2;
                end[1] = y2;
                end[2] = z2;
                float hitPoint[3];
	            bool isHit = soloMesh->raycast(start, end, hitPoint);
                if (isHit)
                {
                    jfloat tmp[3];
                    tmp[0] = hitPoint[0];
                    tmp[1] = hitPoint[1];
                    tmp[2] = hitPoint[2];
                    jfloatArray array = (env)->NewFloatArray(3);
                    env->SetFloatArrayRegion(array, 0, 3, tmp);
                    return array;
                }
                
            }
        }  
    } else if (mode == MODE_TILECACHE)
    {
        
    }
    return NULL;
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    release
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_com_highfly029_GameNativeLibrary_release
  (JNIEnv *env, jobject obj, jint mode, jstring name)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (mode == MODE_SOLOMESH)
    {
        map<string, SoloMesh*>::iterator iter = soloMeshMap.find(nameStr);
        if (iter != soloMeshMap.end())
        {
            if (iter->second != NULL)
            {
                SoloMesh* soloMesh = iter->second;
                soloMeshMap.erase(iter);
                delete soloMesh;
            }
        }
            
    } else if (mode == MODE_TILECACHE)
    {
        
    }
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    addObstacle
 * Signature: (ILjava/lang/String;FFFFF)I
 */
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_addObstacle
  (JNIEnv *env, jobject obj, jint mode, jstring name, jfloat x, jfloat y, jfloat z, jfloat radius, jfloat height)
{
    return 0;
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    addBoxObstacle
 * Signature: (ILjava/lang/String;FFFFFF)I
 */
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_addBoxObstacle__ILjava_lang_String_2FFFFFF
  (JNIEnv *env, jobject obj, jint mode, jstring name, jfloat minX, jfloat minY, jfloat minZ, jfloat maxX, jfloat maxY, jfloat maxZ)
{
    return 0;
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    addBoxObstacle
 * Signature: (ILjava/lang/String;FFFFFFF)I
 */
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_addBoxObstacle__ILjava_lang_String_2FFFFFFF
  (JNIEnv *env, jobject obj, jint mode, jstring name, jfloat centerX, jfloat centerY, jfloat centerZ, jfloat halfExtentsX, jfloat halfExtentsY, jfloat halfExtentsZ, jfloat yRadians)
{
    return 0;
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    removeOneObstacle
 * Signature: (ILjava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_highfly029_GameNativeLibrary_removeOneObstacle
  (JNIEnv *env, jobject obj, jint mode, jstring name, jint index)
{
    return 0;
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    removeAllObstacle
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_highfly029_GameNativeLibrary_removeAllObstacle
  (JNIEnv *env, jobject obj, jint mode, jstring name)
{

}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    update
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_highfly029_GameNativeLibrary_update
  (JNIEnv *env, jobject obj, jint mode, jstring name)
{

}
