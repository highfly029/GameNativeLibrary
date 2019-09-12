package com.highfly029;

/**
 * @ClassName GameNativeLibrary
 * @Description GameNativeLibrary
 * @Author liyunpeng
 * @Date 2019/9/12 18:37
 **/
public class GameNativeLibrary {
    static {
        String path = "D:\\project\\GameNativeLibrary\\project_java\\src\\main\\java\\";
        System.load(path + "GameNativeLibrary.dll");
    }

    public static native String testJni(String name);

    public static void main(String[] args) {
        String name = "jni";
        String text = testJni(name);
        System.out.println("text=" + text);
    }
}
