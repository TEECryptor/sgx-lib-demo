# Intel SGX 可信库开发和调用实例

## 简介
- 本项目包含两个可信库项目(lib-a和lib-b)和一个可信服务项目(example)，用来展示如何开发SGX可信库、以及如何使用可信库。

### 项目目录
|---3rdparty : lib-a和lib-b两个项目的安装输出目录，自动生成。
|
|
|---example : 测试用可信服务项目目录
|    |
|    |---App : 非可信代码目录
|    |
|    |---cmake : SGX编译脚本目录，请勿修改
|    |
|    |---Enclave : 可信代码目录
|
|---lib-a : 单可信库项目目录，该项目编译后只输出一个可信库文件libsgx-lib-a_t.a
|    |
|    |---cmake : SGX编译脚本目录，请勿修改
|    |
|    |---trusted : 可信代码目录
|
|---lib-b : 双可信库项目目录，该项目编译后输出两个可信库文件libsgx-lib-b_t.a和libsgx-lib-b_u.a
|    |
|    |---cmake : SGX编译脚本目录，请勿修改
|    |
|    |---trusted : 非可信代码目录
|    |
|    |---untrusted : 可信代码目录

## 编译

### 编译可信库lib-a
- 切换到项目目录，创建编译目录

```
    $ cd ./lib-a
    $ mkdir build
```
- 编译

```
    $ cmake ..
    $ make & make install
```
- 执行成功后，输出文件会自动安装到目录：./3rdparty/sgx-lib-a

### 编译可信库lib-b

- 切换到项目目录，创建编译目录

```
    $ cd ./lib-b
    $ mkdir build
```
- 编译

```
    $ cmake ..
    $ make & make install
```
- 执行成功后，输出文件会自动安装到目录：./3rdparty/sgx-lib-b

### 编译测试工程example

- 切换到项目目录，创建编译目录

```
    $ cd ./example
    $ mkdir build
```
- 编译

```
    $ cmake ..
    $ make
```
- 运行

```
    $ ./App/example ./Enclave/enclave.signed.so 
```
- 输出如下信息，则说明程序运行成功！
```
    Enclave is initialized!
    ecall_test_libA(): 1 + 2 = 3

    B_func_sum()-->x: 1, y: 2
    B::sum()-->x: 1, y: 2
    ecall_test_libB(): 1 + 2 = 3
```

## 总结

### 只有一个可信库时
- SGX可信库工程可以只输出一个库文件，如libsgx-lib-a_t.a；
- 使用该可信库时，可按如下操作：
    - 在Enclave代码中include对应的头文件；
    - 在Enclave的编译脚本中link对应的a文件。

### 有一个可信库和一个非可信库时 
- SGX可信库工程也可以输出两个库文件，如libsgx-lib-b_t.a和libsgx-lib-b_u.a，这是因为有些功能需要通过OCALL调用在非可信代码中实现。
- 使用该可信库时，可按如下操作：
    - 在Enclave的EDL文件中import该库的EDL文件；
    - 分别在App代码和Enclave代码中include对应的头文件(如果非可信部分也有头文件的话)；
    - 分别在App和Enclave的编译脚本中link对应的库文件。

