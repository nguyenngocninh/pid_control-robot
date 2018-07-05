#include <iostream>
using namespace std;
int n, m, id[40], ans, cnt[40];
bool teach[40][40], conflict[40][40];
int min(int a, int b)
{
	if (a > b)
		return b;
		return a;
}
int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}
bool check(int x, int k) {
	if (teach[x][k] == 1) {
		for (int i = 1; i < k; i++) {
			if (id[i] == x && conflict[i][k]) return false;
		}
		return true;
	}
	return false;
}

int calcDiffLoad() {
	for (int i = 1; i <= m; i++) cnt[i] = 0;
	int vmin = 1e9, vmax = -1e9;
	for (int i = 1; i <= n; i++) {
		cnt[id[i]]++;
	}
	for (int i = 1; i <= m; i++) {
		vmin = min(vmin, cnt[i]);
		vmax = max(vmax, cnt[i]);
	}
	return vmax - vmin;

}
void sulution()
{
	for (int i = 1; i <= n; i++)
	{
		cout << "The course "<<i<<" is taught by teacher "<<id[i]<<endl;
	}
	cout << endl;
}
void Try(int k) {
	if (k == n + 1) {

		ans = min(ans, calcDiffLoad());
		sulution();
	
	}
	for (int i = 1; i <= m; i++) {
		if (check(i, k)) {
			id[k] = i;
			Try(k + 1);
		}
	}
}
int main() {
	cin >> m >> n;
	for (int i = 1; i <= m; i++) {
		int k, u;
		cin >> k;
		while (k--) {
			cin >> u;
			teach[i][u] = 1;
		}
	}
	int k;
	cin >> k;
	for (int u, v, i = 1; i <= k; i++) {
		cin >> u >> v;
		conflict[u][v] = conflict[v][u] = 1;
	}
	ans = 1e9;
	Try(1);
	cout << ans<<endl;
	system("pause");
	return 0;
}
