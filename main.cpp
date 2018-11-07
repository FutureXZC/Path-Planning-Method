/*
	Author��Xiang
	Data��2018/11/1
	Description���ر�ͼѰ��·���滮
*/

#include <iostream>    
#include <string>
#include <stack>
using namespace std;

#define INFTY 32767

/*
* @brief	�ر�ͼ��
*/
class CMap 
{
public:
	CMap();//�ر�ͼ�ڽӾ�������ر�ǳ�ʼ��
	void Set();//����ʳ�ǿ���ͱ��ص�λ��
	void DFS(int i, int *visited);//������ȱ�������Ѱ����·��
	void DFSTraverse();//��ȱ�������
	void DrawGraph();//��ͼ
	int Choose(int *d, bool *s);
	void Dijkstra(int u, int v);
private:
	int map[8][8];//�ر�ͼ·�ߵ��ڽӾ���
	int food;//�洢ʳ��λ�õ��±�
	int thief;//�洢ǿ��λ�õ��±�
	int treasure;//�洢����λ�õ��±�
	bool findFood;//�Ƿ��ҵ�ʳ��ı��
	bool findTreasure;//�Ƿ��ҵ����صı��
	stack<int> v;//��ű������Ľ��Ķ�ջ
	int path[15];//�����������Ѱ��·��������
	bool again;//�ж��Ƿ��ǵڶ���ִ������
	int step;//����
	int last[15];//�洢��һ�����
};

/*
* @brief	�ر�ͼ�ڽӾ�������ر�ǳ�ʼ��
*/
CMap::CMap()
{
	//��ʼ��ͼ
	memset(map, 0, sizeof(map));
	map[0][1] = map[0][2] = 1;
	map[1][0] = map[1][2] = map[1][3] = map[1][4] = 1;
	map[2][0] = map[2][1] = map[2][4] = map[2][5] = 1;
	map[3][1] = map[3][7] = 1;
	map[4][1] = map[4][2] = map[4][6] = 1;
	map[5][2] = map[5][6] = 1;
	map[6][4] = map[6][5] = map[6][7] = 1;

	//�Ƿ��ҵ�ʳ��ͱ��صı����Ϊfalse
	findFood = false;
	findTreasure = false;

	//path��ʼ��Ϊ-1
	memset(path, -1, sizeof(path));

	//again��ʼ��Ϊfalse
	again = false;

	//��ʼ��step��last
	step = -1;
	memset(last, -1, sizeof(last));
}

/*
* @brief	��ͼ
*/
void CMap::DrawGraph()
{
	//����̨��С��Ϊ66��30
	system("mode con cols=66 lines=30");

	cout << "       ----------------------Ѱ ��-------------------------  " << endl;
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

/*
* @brief	����ʳ�ǿ���ͱ��ص�λ��
*/
void CMap::Set()
{
	cout << "������ʳ���λ�ã�";
	cin >> food;
	cout << "�����뱦�ص�λ�ã�";
	cin >> treasure;
	cout << "������ǿ����λ�ã�";
	cin >> thief;
}

/*
* @brief	������ȱ�����Ѱ���Ƿ�����ܹ�Ѱ���ɹ���·�����������������·����������ʾ������
*/
void CMap::DFS(int i, int *visited)
{
	visited[i] = 1;
	step++;//��ǰ������1
	last[step] = i;//��¼Ϊǰһ�����

	//�ж�3��������
	if (i == food)	findFood = true;
	if (i == treasure)	findTreasure = true;
	//������ǿ������·��ͨ��ɾ��ǿ���ıߣ��Ժ�Ҳ����������
	if (i == thief)
	{
		for (int i = 0; i < 8; i++)
			map[thief][i] = map[i][thief] = 0;
		step--;//����ǰһ�����
		return;
	}
	//�������Ķ����ջ
	v.push(i);

	for (int j = 0; j < 8; j++)//jΪ��һ�����
	{
		if (map[i][j] == 1 && !visited[j])//��i��j��ͨ·��jδ������
		{
			if (j == 7)//��jΪ����
			{
				if (findFood == true && findTreasure == true)//�ж��Ƿ�ͬʱ�ҵ���ʳ��ͱ���
				{
					v.push(j);//�����ڽ������ջ������ջ��Ԫ�ص������path������
					for (int k = 14; !v.empty(); k--)
					{
						path[k] = v.top();
						v.pop();
					}
					for (int k = 0; k < 15; k++)//���path���飨path�ڷ�-1��ֵΪ����·����
						if (path[k] != -1)
							cout << path[k] << " ";
					cout << endl;
					getchar(); getchar();
					exit(0);//�ҵ�һ��ͨ·���˳�����
				}
				else if (!again) {//����һ�ε�����ں�δͬʱ�ҵ�ʳ��ͱ��أ��޸�again
					again = true;
					break;
				}
			}
			if (j != 7)//��j�ǳ���
			{

				DFS(j, visited);   //��δ���ʵ��ڽӶ���ݹ����
			}
		}
	}
	//���ڷ�����һ���ݹ飬��������һ����㣬��ӵ�·����ջ
	step--;
	v.push(last[step]);
}

/* 
* @brief	������ȱ�������
*/
void CMap::DFSTraverse()
{
	int visited[8];
	memset(visited, 0, sizeof(visited));
	//����㿪ʼ����DFS��ֻ����һ�Σ���ֹǿ������ĳһ��·ʱ��̽����ƾ�ա���Խ��
	DFS(0, visited);
	//��������û���ҵ�·��������������ڿ��Գɹ�Ѱ����·��
	cout << "û��Ѱ����ιǿ��ȥ��~~~" << endl;
	getchar(); getchar();
	exit(0);//�˳�
}

/*
* @brief	ѡȡ��ǰ���·�����±�
* @param	d	��¼��Դ��u������i�ĵ�ǰ���·������
* @param	s	��¼��Դ��u������i��·���Ƿ��Ѿ�ȷ��
*/
int CMap::Choose(int *d, bool *s)
{
	int i, minpos;//d�����·�����±�
	int min;
	min = INFTY;
	minpos = -1;//��ʼ���±�Ϊ-1
	for (i = 1; i < 64; i++)
		if (d[i] < min && !s[i])
		{
			min = d[i];
			minpos = i;
		}
	return minpos;//�����±�λ��
}

/*
* @brief	�Ͻ�˹�����㷨������ӵ�ǰ�㵽���ڵ����·��
* @param	u	Դ��
* @param	v	�յ�
*/
void CMap::Dijkstra(int u, int v)
{
	int i, j, k;//�������
	bool s[64];//s[i]��¼��Դ��u������i��·���Ƿ��Ѿ�ȷ��
	int d[64];//d[i]��¼��Դ��u������i�ĵ�ǰ���·�����ȣ�������
	int path[64];//path[i]��¼��Դ��u������i�ĵ�ǰ���·���϶���i��ֱ��ǰ����������
	memset(s, false, sizeof(s));

	for (i = 0; i < 64; i++)//��ʼ��
	{
		if (this->map[u][i])
			d[i] = this->map[u][i];
		else
			d[i] = INFTY;
		if (i != u && d[i] < INFTY)
			path[i] = u;
		else
			path[i] = -1;
	}
	s[u] = true;  d[u] = 0;//����uΪԴ��

	for (i = 1; i < 63; i++)
	{
		k = Choose(d, s);
		s[k] = true;//k���뵽s��
		for (j = 0; j < 64; j++)//����d��path
			if (!s[j] && this->map[k][j] && d[k] + this->map[k][j] < d[j])
			{
				d[j] = d[k] + this->map[k][j];
				path[j] = k;
			}
	}
}

int main()
{
	CMap m;//���ɲر�ͼ����
	m.DrawGraph();//���ر�ͼ
	m.Set();//����ʳ����غ�ǿ����λ��
	m.DFSTraverse();//���·��
	return 0;
}