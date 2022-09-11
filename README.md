# CustomRender
### 简介
CostomRender基于C++实现的软光栅化渲染器，主要是用CPU模拟了渲染管线。
引入了QT，为了是使用QT的setPixelColor和读取照片这两个功能，其他例如数学库等均为自己实现。

### 主要实现了以下功能
1. 顶点处理
2. 裁剪(逐边裁剪法)
3. 光栅化
4. 材质映射
5. 光照模型(lambert model,phong model,blinn_phong model)
6. 深度测试
###待实现的功能
1. PBR-BRDF 
2. 抗锯齿(SSAA,MSAA)
3. 延迟光照
4. 性能优化(多线程，SIMD)
### Display

![](/photo/%E7%BA%BF%E6%A1%86.png "线框模型")  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 线框模型
![](/photo/Lamert%20model.png "lambert光照模型")
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; lambert光照模型
![](/photo/Phong%20model.png "Phong光照模型")
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; Phong光照模型
![](/photo/Blinn_phong%20model.png "Blinn_Phong光照模型")
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; Blinn_Phong光照模型
