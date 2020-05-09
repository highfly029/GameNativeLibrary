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
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                iter->second->setPrint(bool_isPrint);
            }
        }
    }
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    loadNavMesh
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_highfly029_GameNativeLibrary_loadNavMesh
  (JNIEnv *env, jobject obj, jint mode, jstring name, jstring path)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);

    if (nameStr == "")
    {
        return jboolean(false);
    }

    if (mode == MODE_SOLOMESH)
    {
        map<string, SoloMesh*>::iterator iter = soloMeshMap.find(nameStr);
        if (iter != soloMeshMap.end())
        {
            return jboolean(true);
        }
        SoloMesh* tool = new SoloMesh();
        const char *str2 = env->GetStringUTFChars(path, 0);
        bool isSuccess = tool->loadNavMesh(str2);
        env->ReleaseStringUTFChars(path, str2);
        if (isSuccess)
        {
            soloMeshMap[nameStr] = tool;
            return jboolean(true);
        } else 
        {
            delete tool;
            return jboolean(false);
        } 
    } else if (mode == MODE_TILECACHE)
    {
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);
        if (iter != tempObstacleMap.end())
        {
            return jboolean(true);
        }
        TempObstacle* tool = new TempObstacle();
        const char *str2 = env->GetStringUTFChars(path, 0);
        bool isSuccess = tool->loadNavMesh(str2);
        env->ReleaseStringUTFChars(path, str2);
        if (isSuccess)
        {
            tempObstacleMap[nameStr] = tool;
            return jboolean(true);
        } else 
        {
            delete tool;
            return jboolean(false);
        }         
    }
    
    return jboolean(false);
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    findPathStraight
 * Signature: (ILjava/lang/String;FFFFFF)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_com_highfly029_GameNativeLibrary_findPathStraight
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
                vector<Vector3D> outPaths;
	            int pointNum = soloMesh->findPathStraight(start, end, outPaths);
                if (pointNum > 0)
                {
                    jclass class_arraylist = env->FindClass("java/util/ArrayList");
                    jmethodID arraylist_construct_method = env->GetMethodID(class_arraylist, "<init>", "()V");
                    jobject obj_arraylist = env->NewObject(class_arraylist, arraylist_construct_method, "");

                    jmethodID arraylist_add_method = env->GetMethodID(class_arraylist, "add", "(Ljava/lang/Object;)Z");
                    vector<Vector3D>::iterator iter = outPaths.begin();
                    for (; iter != outPaths.end(); ++iter)
                    {
                        jfloat tmp[3];
                        tmp[0] = iter->x;
                        tmp[1] = iter->y;
                        tmp[2] = iter->z;
                        jfloatArray array = (env)->NewFloatArray(3);
                        env->SetFloatArrayRegion(array, 0, 3, tmp);
                        env->CallBooleanMethod(obj_arraylist, arraylist_add_method, array);
                    }
                    env->DeleteLocalRef(class_arraylist);
                    return obj_arraylist;                    
                }   
            }
        }  
    } else if (mode == MODE_TILECACHE)
    {
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                TempObstacle* tempObstacle = iter->second;
                float start[3];
                start[0] = x1;
                start[1] = y1;
                start[2] = z1;

                float end[3];
                end[0] = x2;
                end[1] = y2;
                end[2] = z2;
                vector<Vector3D> outPaths;
	            int pointNum = tempObstacle->findPathStraight(start, end, outPaths);
                if (pointNum > 0)
                {
                    jclass class_arraylist = env->FindClass("java/util/ArrayList");
                    jmethodID arraylist_construct_method = env->GetMethodID(class_arraylist, "<init>", "()V");
                    jobject obj_arraylist = env->NewObject(class_arraylist, arraylist_construct_method, "");

                    jmethodID arraylist_add_method = env->GetMethodID(class_arraylist, "add", "(Ljava/lang/Object;)Z");
                    vector<Vector3D>::iterator iter = outPaths.begin();
                    for (; iter != outPaths.end(); ++iter)
                    {
                        jfloat tmp[3];
                        tmp[0] = iter->x;
                        tmp[1] = iter->y;
                        tmp[2] = iter->z;
                        jfloatArray array = (env)->NewFloatArray(3);
                        env->SetFloatArrayRegion(array, 0, 3, tmp);
                        env->CallBooleanMethod(obj_arraylist, arraylist_add_method, array);
                    }
                    env->DeleteLocalRef(class_arraylist);
                    return obj_arraylist;                    
                }  
            }
        }        
    }
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
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                TempObstacle* tempObstacle = iter->second;
                float start[3];
                start[0] = x1;
                start[1] = y1;
                start[2] = z1;

                float end[3];
                end[0] = x2;
                end[1] = y2;
                end[2] = z2;
                float hitPoint[3];
	            bool isHit = tempObstacle->raycast(start, end, hitPoint);
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
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                TempObstacle* tempObstacle = iter->second;
                tempObstacleMap.erase(iter);
                delete tempObstacle;
            }
        } 
    }
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    addObstacle
 * Signature: (ILjava/lang/String;FFFFF)I
 */
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_addObstacle
  (JNIEnv *env, jobject obj, jint mode, jstring name, jfloat x, jfloat y, jfloat z, jfloat radius, jfloat height, jboolean isUpdate)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (mode == MODE_TILECACHE)
    {
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                TempObstacle* tempObstacle = iter->second;
                float pos[3];
                pos[0] = x;
                pos[1] = y;
                pos[2] = z;
                int index = tempObstacle->addObstacle(pos, radius, height);
                if (index > -1 && isUpdate == JNI_TRUE)
                {
                    tempObstacle->update();
                }
                
                return jint(index);
            }
        } 
    }
    return jint(-1);
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    addBoxObstacle
 * Signature: (ILjava/lang/String;FFFFFF)I
 */
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_addBoxObstacle__ILjava_lang_String_2FFFFFFZ
  (JNIEnv *env, jobject obj, jint mode, jstring name, jfloat minX, jfloat minY, jfloat minZ, jfloat maxX, jfloat maxY, jfloat maxZ, jboolean isUpdate)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (mode == MODE_TILECACHE)
    {
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                TempObstacle* tempObstacle = iter->second;
                float min[3];
                float max[3];

                min[0] = minX;
                min[1] = minY;
                min[2] = minZ;
                max[0] = maxX;
                max[1] = maxY;
                max[2] = maxZ;
                int index = tempObstacle->addBoxObstacle(min, max);
                if (index > -1 && isUpdate == JNI_TRUE)
                {
                    tempObstacle->update();
                }
                return jint(index);
            }
        } 
    }
    return jint(-1);
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    addBoxObstacle
 * Signature: (ILjava/lang/String;FFFFFFF)I
 */
JNIEXPORT jint JNICALL Java_com_highfly029_GameNativeLibrary_addBoxObstacle__ILjava_lang_String_2FFFFFFFZ
  (JNIEnv *env, jobject obj, jint mode, jstring name, jfloat centerX, jfloat centerY, jfloat centerZ, jfloat halfExtentsX, jfloat halfExtentsY, jfloat halfExtentsZ, jfloat yRadians, jboolean isUpdate)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (mode == MODE_TILECACHE)
    {
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                TempObstacle* tempObstacle = iter->second;
                float center[3];
                float halfExtents[3];

                center[0] = centerX;
                center[1] = centerY;
                center[2] = centerZ;
                halfExtents[0] = halfExtentsX;
                halfExtents[1] = halfExtentsY;
                halfExtents[2] = halfExtentsZ;
                int index = tempObstacle->addBoxObstacle(center, halfExtents, yRadians);
                if (index > -1 && isUpdate == JNI_TRUE)
                {
                    tempObstacle->update();
                }
                return jint(index);
            }
        } 
    }
    return jint(-1);
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    removeOneObstacle
 * Signature: (ILjava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_highfly029_GameNativeLibrary_removeOneObstacle
  (JNIEnv *env, jobject obj, jint mode, jstring name, jint index, jboolean isUpdate)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (mode == MODE_TILECACHE)
    {
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                TempObstacle* tempObstacle = iter->second;
                bool result = tempObstacle->removeOneObstacle(index);
                if (result && isUpdate == JNI_TRUE)
                {
                    tempObstacle->update();
                }
                return jboolean(result);
            }
        } 
    }
    return jboolean(false);
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    removeAllObstacle
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_highfly029_GameNativeLibrary_removeAllObstacle
  (JNIEnv *env, jobject obj, jint mode, jstring name, jboolean isUpdate)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (mode == MODE_TILECACHE)
    {
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                TempObstacle* tempObstacle = iter->second;
                tempObstacle->removeAllObstacle();
                if (isUpdate == JNI_TRUE)
                {
                    tempObstacle->update();
                }
            }
        } 
    }
}

/*
 * Class:     com_highfly029_GameNativeLibrary
 * Method:    update
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_highfly029_GameNativeLibrary_update
  (JNIEnv *env, jobject obj, jint mode, jstring name)
{
    const char *str = env->GetStringUTFChars(name, 0);
    string nameStr = string(str);
    env->ReleaseStringUTFChars(name, str);
    if (mode == MODE_TILECACHE)
    {
        map<string, TempObstacle*>::iterator iter = tempObstacleMap.find(nameStr);        
        if (iter != tempObstacleMap.end())
        {
            if (iter->second != NULL)
            {
                TempObstacle* tempObstacle = iter->second;
                tempObstacle->update();
            }
        } 
    }
}
