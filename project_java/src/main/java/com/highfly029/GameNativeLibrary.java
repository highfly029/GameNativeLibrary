package com.highfly029;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;

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
            System.out.println("libUrl="+libUrl);
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
            System.out.println("load GameNativeLibrary.jar success path="+f.getAbsolutePath());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static native String testJni(String name);

    public static void main(String[] args) {
        String name = "jni";
        String text = testJni(name);
        System.out.println("text=" + text);
    }
}
