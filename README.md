# CustomRender
### 简介
CostomRender基于C++实现的软光栅化渲染器，主要是用CPU模拟了渲染管线。
引入了QT，为了是使用QT的setPixelColor和读取照片这两个功能，其他例如数学库等均为自己实现。

### 主要实现了以下功能
1. 顶点处理
2. 裁剪(逐边裁剪法)
3. 光栅化
4. 材质映射
5. 基本的光照模型(lambert model,phong model,blinn_phong model)
6. 深度测试
### 待实现的功能
1. PBR-BRDF 
2. 抗锯齿(SSAA,MSAA)
3. 延迟光照
4. 性能优化
5. 基本的图形创建与渲染(平面，圆，球，立方体，环，圆锥，圆柱，半球，管道)
6. 基本的图形创建与渲染支持(OBJ,FBX)
7. 基本的骨骼动画计算和渲染
8. 基本的地形渲染和高度判定
9. 基本的屏幕后处理(灰图，模糊，马赛克，BLOOM)
10. 基本的摄像机处理(拉进拉远，旋转，平移)
11. 基本的RenderTarget摄像机和深度摄像机，支持深度图和一些镜面效果
12. 基本的可组装式代码生成Shader
### Display

#####  线框模型
![](/photo/%E7%BA%BF%E6%A1%86.png "线框模型")  

***
#####  lambert光照模型
![](/photo/Lamert%20model.png "lambert光照模型")

***

#####  Phong光照模型
![](/photo/Phong%20model.png "Phong光照模型")

***

##### Blinn_Phong光照模型
![](/photo/Blinn_phong%20model.png "Blinn_Phong光照模型")
