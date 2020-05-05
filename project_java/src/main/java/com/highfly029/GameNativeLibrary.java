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
            boolean isLinux = System.getProperty("os.name").startsWith("Linux");
            boolean isMac = System.getProperty("os.name").startsWith("Mac");
            String libName = "GameNativeLibrary";
            String suffix = "";
            if (isWindows) {
                suffix += ".dll";
            } else if (isLinux) {
                suffix += ".so";
            } else if (isMac){
                suffix += ".dylib";
                libName = "lib"+libName;
            }

            if (!suffix.equals("")) {
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
                System.out.println("load GameNativeLibrary.jar success! path=" + f.getAbsolutePath());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 设置是否打印底层日志
     * @param mode
     * @param name
     */
    public native void setPrint(int mode, String name, boolean isPrint);
    /**
     * 加载
     * @param mode 1静态阻挡  2动态阻挡
     * @param name
     * @param path 阻挡文件路径
     * @return 是否加载成功
     */
    public native boolean loadNavMesh(int mode, String name, String path);

    /**
     * 寻路
     * @param mode
     * @param name
     * @param x1
     * @param y1
     * @param z1
     * @param x2
     * @param y2
     * @param z2
     * @return 路径点list 查找不到时，会返回null，或list.size==0
     */
    public native List<float[]> findPathStraight(int mode, String name, float x1, float y1, float z1, float x2, float y2, float z2);

    /**
     * 射线检测
     * @param mode
     * @param name
     * @param x1
     * @param y1
     * @param z1
     * @param x2
     * @param y2
     * @param z2
     * @return
     */
    public native float[] raycast(int mode, String name, float x1, float y1, float z1, float x2, float y2, float z2);

    /**
     * 释放阻挡数据
     * @param mode
     * @param name
     * @return
     */
    public native void release(int mode, String name);

    /** 增加动态阻挡 **/
    public native int addObstacle(int mode, String name, float x, float y, float z, float radius, float height);
    public native int addBoxObstacle(int mode, String name, float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
    public native int addBoxObstacle(int mode, String name, float centerX, float centerY, float centerZ, float halfExtentsX, float halfExtentsY, float halfExtentsZ, float yRadians);

    /**
     * 删除一个动态阻挡
     * @param mode
     * @param name
     * @param index
     * @return
     */
    public native boolean removeOneObstacle(int mode, String name, int index);

    /**
     * 删除全部动态阻挡
     * @param mode
     * @param name
     */
    public native void removeAllObstacle(int mode, String name);

    /**
     * 更新
     * @param mode
     * @param name
     */
    public native void update(int mode, String name);



    public static void main(String[] args) throws InterruptedException {
//        testSoloMesh();
        testTempObstacle();
    }

    private static void testTempObstacle() {
        GameNativeLibrary gameNativeLibrary = new GameNativeLibrary();
        String path;
        if (GameNativeLibrary.class.getResource("/") != null) {
            path = GameNativeLibrary.class.getResource("/").getPath() + "all_tiles_tilecache.bin";
        } else {
            path = System.getProperty("user.dir") + File.separator + "all_tiles_tilecache.bin";
        }
        System.out.println("path=" + path);

        String name = "second";
        boolean isSuccess = gameNativeLibrary.loadNavMesh(2, name, path);
        gameNativeLibrary.setPrint(2, name, true);
        System.out.println(isSuccess);
        float[] r1 = new float[3];
        float[] r2 = new float[3];
        r1[0] = -1.0f;
        r1[1] = 1.0f;
        r1[2] = 1.0f;

        r2[0] = -200.0f;
        r2[1] = 1.0f;
        r2[2] = 400.0f;
        float[] result = gameNativeLibrary.raycast(2, name, r1[0], r1[1], r1[2], r2[0], r2[1], r2[2]);
        if (result != null) {
            System.out.println("hit " + result[0] + " " + result[1] + " " + result[2]);
        } else {
            System.out.println("not hit");
        }
        float[] start = new float[3];
        float[] end = new float[3];

        start[0] = -1.0f;
        start[1] = 1.0f;
        start[2] = 1.0f;

        end[0] = -500.0f;
        end[1] = 1.0f;
        end[2] = 200.0f;

        List<float[]> findResult = gameNativeLibrary.findPathStraight(2, name, start[0], start[1], start[2], end[0], end[1], end[2]);
        if (findResult != null && findResult.size() > 0) {
            for (float[] f : findResult) {
                System.out.println("findPoint " + f[0] + " " + f[1] + " " + f[2]);
            }
        }
        System.out.println("动态阻挡测试");
        r1[0] = -10.0f;
        r1[1] = 1.0f;
        r1[2] = 350.0f;

        r2[0] = -400.0f;
        r2[1] = 1.0f;
        r2[2] = 350.0f;
        result = gameNativeLibrary.raycast(2, name, r1[0], r1[1], r1[2], r2[0], r2[1], r2[2]);
        if (result != null) {
            System.out.println("hit " + result[0] + " " + result[1] + " " + result[2]);
        } else {
            System.out.println("not hit");
        }
        float[] boxMin = new float[3];
        float[] boxMax = new float[3];
        boxMin[0] = -50.0f;
        boxMin[1] = 0.0f;
        boxMin[2] = 340.0f;
        float width = 14.0f;
        float length = 14.0f;
        int len = 2;
        int[] array = new int[len];
        for (int i = 0; i < len; i++)
        {
            boxMax[0] = boxMin[0] + length;
            boxMax[1] = boxMin[1] + 10;
            boxMax[2] = boxMin[2] + width;
            int idx = gameNativeLibrary.addBoxObstacle(2, name,boxMin[0],boxMin[1],boxMin[2],boxMax[0],boxMax[1],boxMax[2]);
            array[i] = idx;
            gameNativeLibrary.update(2, name);
            result = gameNativeLibrary.raycast(2, name, r1[0], r1[1], r1[2], r2[0], r2[1], r2[2]);

            if (result != null) {
                System.out.println("hit " + result[0] + " " + result[1] + " " + result[2]);
            } else {
                System.out.println("not hit");
            }

            boxMin[0] = boxMax[0];
            boxMin[1] = boxMax[1];
            boxMin[2] = boxMax[2];
        }
        System.out.println("==============");
        boolean isRemoveAll = true;
        if (!isRemoveAll) {
            for (int i = 0; i < len; i++) {
                int idx = array[i];
                boolean isRe = gameNativeLibrary.removeOneObstacle(2, name, idx);
                System.out.println("isRe=" + isRe);
                gameNativeLibrary.update(2, name);
                result = gameNativeLibrary.raycast(2, name, r1[0], r1[1], r1[2], r2[0], r2[1], r2[2]);

                if (result != null) {
                    System.out.println("hit " + result[0] + " " + result[1] + " " + result[2]);
                } else {
                    System.out.println("not hit");
                }
            }
        } else {
            System.out.println("removeAllObstacle");
            gameNativeLibrary.removeAllObstacle(2, name);
            gameNativeLibrary.update(2, name);
            result = gameNativeLibrary.raycast(2, name, r1[0], r1[1], r1[2], r2[0], r2[1], r2[2]);

            if (result != null) {
                System.out.println("hit " + result[0] + " " + result[1] + " " + result[2]);
            } else {
                System.out.println("not hit");
            }
        }
        gameNativeLibrary.release(2, name);
    }

    private static void testSoloMesh() {
        GameNativeLibrary gameNativeLibrary = new GameNativeLibrary();
        String path;
        if (GameNativeLibrary.class.getResource("/")!= null) {
            path = GameNativeLibrary.class.getResource("/").getPath() + "all_tiles_tilecache.bin";
        } else {
            path = System.getProperty("user.dir") + File.separator + "all_tiles_tilecache.bin";
        }
        System.out.println("path=" + path);

        String name = "first";
        boolean isSuccess = gameNativeLibrary.loadNavMesh(1, name, path);
        gameNativeLibrary.setPrint(1, name, true);
        System.out.println(isSuccess);
        float[] r1 = new float[3];
        float[] r2 = new float[3];
        r1[0] = -1.0f;
        r1[1] = 1.0f;
        r1[2] = 1.0f;

        r2[0] = -200.0f;
        r2[1] = 1.0f;
        r2[2] = 400.0f;
        float[] result = gameNativeLibrary.raycast(1, name, r1[0], r1[1], r1[2], r2[0], r2[1], r2[2]);
        if (result != null) {
            System.out.println(result[0] + " " + result[1] + " " + result[2]);
        } else {
            System.out.println("not hit");
        }
        float[] start = new float[3];
        float[] end = new float[3];

        start[0] = -1.0f;
        start[1] = 1.0f;
        start[2] = 1.0f;

        end[0] = -500.0f;
        end[1] = 1.0f;
        end[2] = 200.0f;

        List<float[]> findResult = gameNativeLibrary.findPathStraight(1, name, start[0], start[1], start[2], end[0], end[1], end[2]);
        if (findResult != null && findResult.size() > 0) {
            for (float[] f : findResult) {
                System.out.println("findPoint " + f[0] + " " + f[1] + " " + f[2]);
            }
        }
        gameNativeLibrary.release(1, name);
    }
}
