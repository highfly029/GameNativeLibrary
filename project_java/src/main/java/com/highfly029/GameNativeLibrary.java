package com.highfly029;

/**
 * @ClassName GameNativeLibrary
 * @Description GameNativeLibrary
 * @Author liyunpeng
 * @Date 2019/9/12 18:37
 **/
public class GameNativeLibrary {
    static {
        System.out.println(System.getProperty("user.dir"));//user.dir指定了当前的路径
        String path = System.getProperty("user.dir") + "\\src\\main\\java\\";
        System.load(path + "GameNativeLibrary.dll");
    }

    public static native String testJni(String name);

    public static void main(String[] args) {
        String name = "jni";
        String text = testJni(name);
        System.out.println("text=" + text);
    }
}
