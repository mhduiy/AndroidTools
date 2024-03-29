# AndroidTools
## 简介

AndroidTools是一个基于ADB(Android Debug Bridge)开发而成的工具，可以通过有线或者无线模式调试管理安卓设备，实现很多高级功能，因为现在HarmonyOS和Xiaomi Hyper OS都还基于或部分基于AOSP，所以本工具还能够部分支持这两种设备。

#### 注意事项

需要在手机打开开发者模式中的USB调试方可使用
部分手机需要打开USB调试（安全设置）才可使用全部功能

#### 计划重绘控件

- [x] MNotificationBox 通知控件
- [x] MLineEdit  编辑框
- [x] MTabSwitchButton  分页按钮
- [x] MButton  按钮
- [x] MSwitchButton  开关按钮
- [x] MProgressBar  进度条
- [ ] MSidebar  侧边栏
- [ ] MTitleBar  标题栏
- [ ] MDialog  对话框
- [ ] MColorLabel 带背景颜色的标签
- [ ] MListView  列表控件
- [ ] MBlurEffectWidget  实时模糊窗体
- [ ] MLineChart 折线图表
- [ ] MFrame  带动画，带背景色的窗体框架

## 特性和功能设计

#### 特性介绍：
1.	AndroidTools将使用Qt编写，使用开源ADB工具，利用Qt跨平台的特性，该工具可在Windows+Linux双端运行【MacOS尚未调研，理论上也会支持】
2.	使用原生Qt库，但是Qt的默认控件比较丑，计划重写大部分使用到的原生QtWidgets控件，并添加原生Qt控件不支持的动画效果，实现跨平台的样式统一和美观。
3.	不仅支持有线连接设备，还支持无线连接设备，并且可记忆已经连接的设备，跟随ADB版本，可支持最新的连接特性【比如设备码连接】

#### 功能介绍：

目前初步设想，将支持以下功能
1.	设备基本信息监控：包括电池，内存，CPU，GPU等实时信息，安卓版本，屏幕，系统等固定信息。【后续计划支持帧率统计，类似与perfdog的性能监测功能，并提供性能检测报告。该功能前期没有充分调研，可能无法实现，尽力而为】
2.	设备控制功能：在PC上实现对手机模拟按键点击，模拟操作，模拟设备环境，文本输入，分辨率&DPI的修改，脚本执行，电量伪装。
3.	软件管理：顾名思义，实现对手机软件的管理，得益于ADB的权限较高，可卸载手机无法卸载和部分系统软件，除此之外，可以实现冻结软件，清除数据，提取软件，或者向设备发送PC上的安装包到手机进行安装
4.	刷机工具：可实现快捷刷机功能，可指定分区刷写镜像，指定分区清除数据，临时启动boot，除此之外，还提供常见刷机包链接跳转功能，卡刷包线刷包一键解压（支持解压payload.img镜像文件）【后续计划支持卡刷包转换为线刷包，已有存在的工具可以支持】
5.	设备镜像：可实时监看手机屏幕，屏幕截图，屏幕录制【后续计划支持屏幕模拟点击，可直接在工具上操作手机】
6.	终端：比较简单，可以在这里快速对设备执行ADB命令

## License

See the [LICENSE](LICENSE) file for license rights and limitations (Apache 2.0).
