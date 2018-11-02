

#include <iostream>    
#include <string>
#include <stack>
using namespace std;

//藏宝图类
class CMap 
{
public:
	CMap();//邻接矩阵的初始化
	void Set();//设置食物、强盗和宝藏的位置
	void DFS(int i, int *visited);//深度优先遍历
	void DFSTraverse();//深度遍历操作
	void DrawGraph();//画图

private:
	int map[8][8];//藏宝图路线的邻接矩阵
	int food;//存储食物位置的下标
	int thief;//存储强盗位置的下标
	int treasure;//存储宝藏位置的下标
	bool findFood;//是否找到食物的标记
	bool findTreasure;//是否找到宝藏的标记
	stack<int> v;//存放遍历过的结点的堆栈
	int path[6];//用于输出最终寻宝路径的数组
	bool again;//判断是否是第二次执行搜索
};

//邻接矩阵的初始化
CMap::CMap()
{
	for (int i = 0; i < 8; i++)//动态生成二维数组（矩阵）
	{
		for (int j = 0; j < 8; j++)
			map[i][j] = 0;//对矩阵初始化
		map[i][i] = 0;//对角线上元素为0，无自回路
	}
	//生成图
	map[0][1] = map[0][2] = 1;
	map[1][2] = map[1][3] = map[1][4] = 1;
	map[2][1] = map[2][4] = map[2][5] = 1;
	map[3][1] = map[3][7] = 1;
	map[4][1] = map[4][2] = map[4][6] = 1;
	map[5][2] = map[5][6] = 1;
	map[6][4] = map[6][7] = 1;

	//是否找到食物和宝藏的标记置为false
	findFood = false;
	findTreasure = false;

	//path初始化为-1
	memset(path, -1, sizeof(path));

	//again初始化为false
	again = false;
}

//画图
void CMap::DrawGraph()
{
	//控制台大小设为66×30
	system("mode con cols=66 lines=30");

	cout << "       ----------------------寻 宝-------------------------  " << endl;
	cout << "       |                   V3                             |  " << endl;
	cout << "       |                 .     .                          |  " << endl;
	cout << "       |               .          .                       |  " << endl;
	cout << "       |             .                .                   |  " << endl;
	cout << "       |           V1                    .                |  " << endl;
	cout << "       |         .  .  .                    .             |  " << endl;
	cout << "       |       .    .   .                      .          |  " << endl;
	cout << "       |     .      .     .                       .       |  " << endl;
	cout << "       |   V0       .       V4  .  .  . V6  .  .  . V7    |  " << endl;
	cout << "       |     .      .      .           .                  |  " << endl;
	cout << "       |       .    .    .           .                    |  " << endl;
	cout << "       |         .  .  .           .                      |  " << endl;
	cout << "       |           V2  .  .  .  V5                        |  " << endl;
	cout << "       ----------------------------------------------------  " << endl << endl;
}

//设置食物、强盗和宝藏的位置
void CMap::Set()
{
	cout << "请输入食物的位置：";
	cin >> food;
	cout << "请输入宝藏的位置：";
	cin >> treasure;
	cout << "请输入强盗的位置：";
	cin >> thief;
	//删除强盗的边
	for (int i = 0; i < 8; i++)
		map[thief][i] = map[i][thief] = 0;
}

//深度优先遍历
void CMap::DFS(int i, int *visited)
{
	visited[i] = 1;

	//判断2个特殊结点
	if (i == food)	findFood = true;
	if (i == treasure)	findTreasure = true;
	//遍历过的顶点进栈
	v.push(i);

	for (int j = 0; j < 8; j++)//j为下一个结点
	{
		if (map[i][j] == 1 && !visited[j])//若i到j有通路且j未被访问
		{
			if (j == 7)//若j为出口
			{
				if (findFood == true && findTreasure == true)//判断是否同时找到了食物和宝藏
				{
					v.push(j);//将出口结点放入堆栈，而后栈内元素倒序存入path数组内
					for (int k = 5; !v.empty(); k--)
					{
						path[k] = v.top();
						v.pop();
					}
					for (int k = 0; k < 6; k++)//输出path数组（path内非-1的值为正序路径）
						if (path[k] != -1)
							cout << path[k] << " ";
					cout << endl;
					getchar(); getchar();
					exit(0);//找到一条通路后，退出程序
				}
				else if(!again){//若第一次到达出口后未同时找到食物和宝藏，修改again
					again = true;
					break;
				}
				else {//若第二次到达出口依然没有同时找到食物和宝藏，886
					cout << "不存在可以同时找到食物和宝藏的通路！886" << endl;
					getchar(); getchar();
					exit(0);//退出
				}
			}
			if(j != 7)//若j为非出口
				DFS(j, visited);   //对未访问的邻接顶点递归调用
		}
	}
	//返回上一级递归时，判断当前结点是否为食物或宝藏，修正标记
	if (i == food)	findFood = false;
	if (i == treasure)	findTreasure = false;
	//由于返回上一级递归，即返回上一个结点，因此需将当前结点出栈
	v.pop();
}

//深度遍历操作
void CMap::DFSTraverse()
{
	int visited[8];
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < 8; i++) 
	{
		if (!visited[i]) //对未访问过的顶点调用DFS
		{
			DFS(i, visited);
		}
	}
	cout << endl << endl;
}

int main()
{
	CMap m;//生成藏宝图对象
	m.DrawGraph();//画藏宝图
	m.Set();//设置食物、宝藏和强盗的位置
	m.DFSTraverse();//输出路径
	return 0;
}