# 1、screen_touch_check说明

一个简易的屏幕触控检测程序，使用Qt实现

# 2、Qt环境

**Based on Qt 6.4.1 (MSVC 2019, x86_64)**

# 3、如何使用

程序运行期间，记录鼠标或触控点击事件，并进行标记。

自动对触发时间、标记坐标、触发次数进行记录，保存在执行目录“**check_info.txt**”中。

程序运行时覆盖当前屏幕（包括底部任务栏）。目前只支持一块屏幕。

程序打开后点击Esc按键可直接退出程序，或调用任务管理器等方法也可以切出程序。

# 4、后续功能

1、增加运行界面，可导入文件进行坐标解析并复原其情况。

2、关闭程序后跳转到主界面，可进行其他选择。

3、保存当前次的标记图片。