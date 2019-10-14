## 环境要求

在使用 Alibaba Cloud SDK for C++ 前，确保您已经：

* 注册了阿里云账号并获取了访问密钥（AccessKey）。

> **说明：** 为了保证您的账号安全，建议您使用RAM账号来访问阿里云服务。阿里云账号对拥有的资源有全部权限。RAM账号由阿里云账号授权创建，仅有对特定资源限定的操作权限。详情[参见RAM](https://help.aliyun.com/document_detail/28647.html)。


* 安装支持 C++ 11 或更高版本的编译器：
	* Windows: Visual Studio 2015 或以上版本
	* Linux: GCC 4.9 或以上版本

* 安装 CMake 3.0 或以上版本
* 建议 4G 或以上内存

### Linux

要在 Linux 平台进行编译, 您必须安装依赖的外部库文件 libcurl、libopenssl、libuuid、libjsoncpp, 通常情况下，系统的包管理器中的会有提供。
注意，jsoncpp如果包找不到，可以直接在3rdparty中使用jsoncpp的源码安装。
例如：在基于 Redhat / Fedora 的系统上安装这些软件包

```bash
sudo dnf install libcurl-devel openssl-devel libuuid-devel libjsoncpp-devel
```

在基于 Debian/Ubuntu 的系统
```bash
sudo apt-get install libcurl4-openssl-dev libssl-dev uuid-dev libjsoncpp-dev
```

在安装依赖库后执行以下命令编译并安装：

手动编译安装
```bash
  mkdir sdk_build
  cd sdk_build
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr ..
  make
  sudo make install
```

或者通过 `easyinstall.sh`一键式安装

```bash
  sudo sh easyinstall.sh
```

**Alibaba Cloud SDK for C++ 将被安装在 `/usr`.**


### Windows

通过 cmake 生成 Visual Studio 解决方案:

在 aliyun-openapi-cpp-sdk 下创建 sdk_build 目录

打开 cmake-ui 选择源代码目录和构建目录，点击 `配置(configure)` 和 `生成(generate)` 构建 VS 解决方案。

进入 sdk_build 目录使用 Visual Studio 打开 alibabacloud-sdk.sln 解决方案。

选择构建 `Release` 输出，并打开配置管理器勾选 `INSTALL`。

构建 -> 生成解决方案。

或者您也可以使用 VS 的开发人员命令提示符，执行以下命令编译并安装：

```
msbuild ALL_BUILD.vcxproj
msbuild INSTALL.vcxproj
```

**Alibaba Cloud SDK for C++ 将安装在 `C:\Program File (x86)\alibabacloud-sdk` 目录**

**注意：请以管理员身份运行 Visual Studio，否则无法安装 SDK**

## 快速使用(KMS Decrypt接口的例子在examples下面，查看README编译kms示例)

在调用 Alibaba Cloud SDK for C++ 时，您首先需要配置预处理器定义 ALIBABACLOUD_SHARED 以引用阿里云 C++ SDK 的共享库，然后通过创建 Client 实例提供身份验证，并指定云服务的地域，然后发送API请求。

以下代码展示了如何调用 DescribeInstancesAPI 查询指定地域所有 ECS 实例的详细信息。

> **说明：** 您需要替换示例中的 your-region-id、your-access-key-id 和 your-access-key-secret 的值。

```
#include <iostream>
#include <alibabacloud/core/AlibabaCloud.h>
#include <alibabacloud/ecs/EcsClient.h>

using namespace AlibabaCloud;
using namespace AlibabaCloud::Ecs;

int main(int argc, char** argv) {
  // 初始化 SDK
  AlibabaCloud::InitializeSdk();

  // 配置 ecs 实例
  ClientConfiguration configuration("<your-region-id>");
  EcsClient client("<your-access-key-id>", "<your-access-key-secret>", configuration);

  // 创建API请求并设置参数
  Model::DescribeInstancesRequest request;
  request.setPageSize(10);

  auto outcome = client.describeInstances(request);
  if (!outcome.isSuccess()) {
    // 异常处理
    std::cout << outcome.error().errorCode() << std::endl;
    AlibabaCloud::ShutdownSdk();
    return -1;
  }

  std::cout << "totalCount: " << outcome.result().getTotalCount() << std::endl;

  // 关闭 SDK
  AlibabaCloud::ShutdownSdk();
  return 0;
}
```

复制上述文件到 ecs_test.cc。

Linux 下

```bash
~$ g++ -o ecstest ecs_test.cc --std=c++11 -lalibabacloud-sdk-core -l alibabacloud-sdk-ecs
~$ ./ecstest
# 结果或错误返回将在此展示
~$
```

## Timeout 设置

CPP SDK 使用 libcurl 作为底层 HTTP 传输库。

- 下面两个参数用来传递超时参数到 libcurl。

 - `connectTimeout`: 连接超时设置。 [参考](https://curl.haxx.se/libcurl/c/CURLOPT_CONNECTTIMEOUT_MS.html).

 - `readTimeout`: 传输超时设置。[参考](https://curl.haxx.se/libcurl/c/CURLOPT_TIMEOUT_MS.html)

- 默认值

  - connectTimeout: 5000ms

  - readTimeout: 10000ms

- 可以在创建 Client 或者发 Requst 设置超时参数。

-  Requst 设置优先级高于 Client 设置。

- 输入 0 或者 -1 到 `setConnectTimeout` 和 `setReadTimeout` 可以禁用此功能。

下面代码是设置超时参数的例子，由于 Request 优先级高于 Client，所以最终 `ConnectTimeout` 为 `1000ms`， `readTimeout` 为 `6000ms`。

```cpp
#include <iostream>
#include <alibabacloud/core/AlibabaCloud.h>
#include <alibabacloud/ecs/EcsClient.h>

using namespace AlibabaCloud;
using namespace AlibabaCloud::Ecs;

int main(int argc, char** argv) {
  // Initialize the SDK
  AlibabaCloud::InitializeSdk();

  // Configure the ECS instance
  ClientConfiguration configuration("<your-region-id>");
  // specify timeout when create client.
  configuration.setConnectTimeout(1500);
  configuration.setReadTimeout(4000);

  EcsClient client("<your-access-key-id>", "<your-access-key-secret>", configuration);

  // Create an API request and set parameters
  Model::DescribeInstancesRequest request;
  request.setPageSize(10);
  // specify timeout when request
  request.setConnectTimeout(1000);
  request.setReadTimeout(6000);

  auto outcome = client.describeInstances(request);
  if (!outcome.isSuccess()) {
    // Handle exceptions
    std::cout << outcome.error().errorCode() << std::endl;
    AlibabaCloud::ShutdownSdk();
    return -1;
  }

  std::cout << "totalCount: " << outcome.result().getTotalCount() << std::endl;

  // Close the SDK
  AlibabaCloud::ShutdownSdk();
  return 0;
}

```


**更多 [例程](https://github.com/aliyun/aliyun-openapi-cpp-sdk/tree/master/examples)**

## 问题
[提交 Issue](https://github.com/aliyun/aliyun-openapi-cpp-sdk/issues/new/choose), 不符合指南的问题可能会立即关闭。

## 发行说明
每个版本的详细更改记录在[发行说明](CHANGELOG)中。

## 贡献
提交 Pull Request 之前请阅读[贡献指南](CONTRIBUTING.md)。

## 许可证
[Apache-2.0](http://www.apache.org/licenses/LICENSE-2.0)

版权所有 1999-2019 阿里巴巴集团
