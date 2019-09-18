package com.highfly029;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;
import java.util.List;

/**
 * @ClassName GameNativeLibrary
 * @Description GameNativeLibrary
 * @Author liyunpeng
 * @Date 2019/9/12 18:37
 **/
public class GameNativeLibrary {
    static {
        try {
            boolean isWindows = System.getProperty("os.name", "").toLowerCase().contains("windows");
            String libName = "GameNativeLibrary";
            String suffix = "";
            if (isWindows) {
                suffix += ".dll";
            } else {
                suffix += ".so";
            }

            URL libUrl = Thread.currentThread().getContextClassLoader().getResource(libName + suffix);
            URLConnection resConn = libUrl.openConnection();
            resConn.setUseCaches(false);
            InputStream inputStream = resConn.getInputStream();
            if (inputStream == null) {
                System.out.println("cant find GameNativeLibrary.jar");
            }
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int n;
            while (-1 != (n = inputStream.read(buffer))) {
                out.write(buffer, 0, n);
            }

            File f = File.createTempFile(libName, suffix);
            FileOutputStream fileOutputStream = new FileOutputStream(f);
            fileOutputStream.write(out.toByteArray());
            fileOutputStream.close();
            System.load(f.getAbsolutePath());
            System.out.println("load GameNativeLibrary.jar success ");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // ------------------------------------
    // start : RegisterNatives方式

    /*
     * 加载地图方式1
     *
     * 参数: path : 地图文件的路径
     *
     * 返回值 int, navMeshId, 为0或负数表示加载失败，为正数表示加载成功，后续寻路时传入此id为参数
     *
     */
    public native int load(String path);

    /*
     * 加载地图方式2
     *
     * 参数：meshName, 地图名：要求不重复
     *
     * 参数: meshData, 地图数据
     *
     * 返回值 int, navMeshId, 为0或负数表示加载失败，为正数表示加载成功，后续寻路时传入此id为参数
     *
     */
    public native int load2(String meshName, byte[] meshData);

    // 寻路
    // 返回路径点列表，注意，查找不到时，会返回null，或list.size==0
    public native List<float[]> find(int navmeshId, float x1, float y1, float z1, float x2, float y2, float z2);

    // rayCast
    // 返回路径点列表，注意，查找不到时，会返回null，或list.size==0
    public native List<float[]> rayCast(int navmeshId, float x1, float y1, float z1, float x2, float y2, float z2);


    // 释放加载的地图数据
    public native int release(int navmeshId);

    // end
    // -------------------------------------

    public static void main(String[] args)
    {
        GameNativeLibrary gameNativeLibrary = new GameNativeLibrary();
        int meshId = gameNativeLibrary.load("srv_CAIBakedNavmesh.navmesh");
        if (meshId <= 0) {
            System.out.println("加载地图数据失败");
        }

        float[] start = new float[3];
        start[0] = 1.727072f;
        start[1] = 3.570761f;
        start[2] = 30.0069f;

        float[] end = new float[3];
        end[0] = 32.76521f;
        end[1] = 2.299392f;
        end[2] = -5.955514f;

        List<float[]> list = gameNativeLibrary.find(meshId, start[0], start[1], start[2], end[0], end[1], end[2]);

        for (float[] f : list) {
            System.out.println(f[0] + " " + f[1] + " " + f[2]);
        }
    }
}
