- 首先读入图像并利用inrange函数对图像进行二值化,在PS中查看对应颜色的hsv,发现h,s在整张图像中都为零,即只关心灰度即可,为精确界定阈值,使用trackbar函数对两个阈值进行可视化调整



- 再下来进行腐蚀,同样的,利用trackbar对核的size进行可视化调整 



- 然后使用findcontours配合boudingRect对目标区域进行框选,但总是误识别到黑色缝隙,对此在图像中部建立一个ROI,ROI的坐标来源自第一次识别边框中,框住整个白色区域的面积较大的矩形块



- 接下来再次使用一遍findcontous和boundingRect,并利用矩形面积大小,滤掉图中误识别的矩形,结果如下 



![image.png](https://i.loli.net/2019/11/28/B9DYxmpUVjel3hz.png)

 

 

 

 

 

 

 

 

