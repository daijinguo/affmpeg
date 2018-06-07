
## jniLibs
jniLibs 下存放的 so 文件是使用 ndk 编译 src/main/cpp 下代码时需要链接的库文件。
最终这些so文件会被拷贝到编译打包前的 lib 文件夹下。

如果是简单的需要应用到so文件与不必参与编译,那么可以将这些文件法国之在 libs 文件夹下即可

## cmake 或 ndk-build 编译
本工程使用了 cmake 和 ndk-build 的两种方式进行编译.
具体使用暗中方式只需要修改
``` gradle
android {
    ......
    externalNativeBuild {
        //cmake {
        //    path "CMakeLists.txt"
        //}

        ndkBuild {
            path "src/main/cpp/Android.mk"
        }
     }
}
```

## ABI 问题
abi 内容定义在
```gradle
android {
    ......
    defaultConfig {
        ......
        externalNativeBuild {
            // ## cmake build ##
            //cmake {
            //    cppFlags "-frtti -fexceptions"
            //    //arguments "-DANDROID_ARM_NEON=TRUE", "-DANDROID_TOOLCHAIN=gcc"
            //}
        }

        ndk {
            abiFilters 'armeabi'
            //abiFilters 'armeabi', 'armeabi-v7a', 'arm64-v8a'
            //toolchain "clang"
        }
    }
}
```

在 ndk 下定义了 ABI 信息, 本工程指定的是 armeabi。 另外如果使用 ndk-build 编译的话, Application.mk 文件
中定义的基本上不起作用.

+ 出现的一些问题：  
例如先定义了 armeabi 和 armeabi-v7a，然后某种原因不使用了 armeabi-v7a，
将 armeabi-v7a 从例如本工程的 jniLibs 删除了。 然后使用 ./gradlew clean 时发现存在问题的(可能是AS的 bug)。  
解决方法：删除 .externalNativeBuild 文件

