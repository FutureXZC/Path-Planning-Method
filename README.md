# B6寻宝路径规划

## 内容和要求
&emsp;&emsp;有一幅如图所示的藏宝图，请设计算法要求从入口到出口，必须经过“食品”和“宝藏”的地方，不得经过“强盗”的地方。  
![藏宝图](/images/map.png)  
 
## 实现的功能
&emsp;&emsp;(1) 在主界面，程序使用“ASCII艺术”画出该藏宝图的图形结构。  
&emsp;&emsp;(2) 支持任意指定食品、宝藏、强盗的位置，算法均能正确运行。  
&emsp;&emsp;(3) 寻宝者可以回头。  
&emsp;&emsp;(4) 正确输出题目要求的寻宝路径，从V0口进，V7口出。  


## 核心算法
&emsp;&emsp;深度优先遍历（DFS），迪杰斯特拉算法

## 实例输入与输出
```
       ----------------------寻 宝-------------------------
       |                   V3                             |
       |                 .     .                          |
       |               .          .                       |
       |             .                .                   |
       |           V1                    .                |
       |         .  .  .                    .             |
       |       .    .   .                      .          |
       |     .      .     .                       .       |
       |   V0       .       V4  .  .  . V6  .  .  . V7    |
       |     .      .      .           .                  |
       |       .    .    .           .                    |
       |         .  .  .           .                      |
       |           V2  .  .  .  V5                        |
       ----------------------------------------------------

请输入食物的位置：3
请输入宝藏的位置：6
请输入强盗的位置：4
0 1 2 5 6 5 2 1 3 7
```