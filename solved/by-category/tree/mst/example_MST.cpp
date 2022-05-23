#include<iostream>
#include<queue>
#include<utility>
using namespace std;
typedef pair<int, pair<int, int>> E;
priority_queue<E,vector<E>,greater<E>> e;
int par[10001] = {};
int find(int here)
{
	if (here == par[here])return here;
	return par[here] = find(par[here]);
}
void merge(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x == y)
		return;
	par[x] = y;
}
int main()
{
	int n, m;
	cin >> n >> m;
	for (size_t i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		e.push(E(c, { a,b }));
	}//-->간선 정보 입력
	for (size_t i = 1; i <= n; i++)
	{
		par[i] = i;
	}//덩어리끼리 그룹만든다
	long long int ans = 0;
	while (!e.empty())
	{
		E temp = e.top();//길이가 가장 짧은 간선을 꺼낸다
		e.pop();
		pair<int, int> v = temp.second;
		if (find(v.first) == find(v.second))
			//다음 temp 간선을 스패닝 트리에 넣을경우 사이클이 발생하는 조건. (둘다 스패닝 트리에 있으면 둘을 잇는 간선은 사이클을 만들수 밖에 없다)
			continue;
		else
		{//temp 간선이 사이클을 만들지 않고 최소길이라 채택되는경우
			ans += temp.first;
			merge(v.first, v.second);
		}
	}
	cout << ans;
}
