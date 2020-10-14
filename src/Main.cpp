#include "Platform/Platform.hpp"
#include <SFML\Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

#ifndef render_header
	#define render_header
void render(int);
#endif
#ifndef calcH_header
	#define calcH_header
int calcH(int, int, int, int);
#endif
#ifndef backTrack_header
	#define backTrack_header
void backTrack(int, int, bool);
#endif
#ifndef clear_header
	#define clear_header
void clear();
#endif
#ifndef reset_header
	#define reset_header
void reset(int, int, int, int);
#endif
#ifndef clearYellow_header
	#define clearYellow_header
void clearYellow();
#endif
#ifndef dfs_header
	#define dfs_header
void dfs(int, int, int, int, int, int, bool&);
#endif
#ifndef bfs_header
	#define bfs_header
void bfs(int, int, int, int);
#endif
#ifndef bibfs_header
	#define bibfs_header
void bibfs(int, int, int, int);
#endif
#ifndef bestFirstSearch_header
	#define bestFirstSearch_header
void bestFirstSearch(int, int, int, int);
#endif
#ifndef dijkstra_header
	#define dijkstra_header
void dijkstra(int, int, int, int);
#endif
#ifndef aStar_header
	#define aStar_header
void aStar(int, int, int, int);
#endif

const int sz = 30, ver = 33, hor = 62, tot = 8; // ver -> height of the screen, hor -> width of the screen ,thus ver*hor nodes
const int maxx = 5050;
const int vx = sz * hor, vy = sz * ver;
const int backtrackingSleepingTime = 8;
const int dfsSleepingTime = 12;
const int bfsSleepingTime = 3;
const int bibfsSleepingTime = 5;
const int bestFirstSearchSleepingTime = 12;
const int dijkstraSleepingTime = 3;
const int aStarSleepingTime = 9;

	// change sleepingTime to increase/decrease the speed of the visualization of an algorithm or backtracking the path

sf::RenderWindow window(sf::VideoMode(vx, vy), "Algorithm Visualizer", sf::Style::Default);
sf::RectangleShape player(sf::Vector2f(sz, sz));

vector<pair<int, int>> dir = { { 1, 0 }, { 0, 1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, 0 }, { -1, -1 }, { 0, -1 } };
bool visited[ver + 10][hor + 10], visited2[ver + 10][hor + 10], exists[ver + 10][hor + 10];
int col[ver + 10][hor + 10], pi[ver + 10][hor + 10], pj[ver + 10][hor + 10], pi2[ver + 10][hor + 10], pj2[ver + 10][hor + 10], dist[ver + 10][hor + 10], g[ver + 10][hor + 10], h[ver + 10][hor + 10];
vector<pair<int, int>> openList;

void render(int sleepingTime)
{
	for (int i = 0; i < ver; ++i)
		for (int j = 0; j < hor; ++j)
		{
			switch (col[i][j])
			{
				case 1: player.setFillColor(sf::Color::Cyan); break;
				case 3: player.setFillColor(sf::Color::Red); break;
				case 4: player.setFillColor(sf::Color::Yellow); break;
				case 5: player.setFillColor(sf::Color::Green); break;
				case 6: player.setFillColor(sf::Color::Blue); break;
				case 7: player.setFillColor(sf::Color::Magenta); break;
				default: player.setFillColor(sf::Color::Black);
			}
			player.setPosition(j * sz, i * sz);
			window.draw(player);
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				if (evnt.type == evnt.Closed)
					window.close();
			}
		}
	window.display();
	Sleep(sleepingTime);
	sleepingTime++;
}
class cmp
{
public:
	bool operator()(const pair<int, int>& p1, const pair<int, int>& p2)
	{
		return dist[p1.first][p1.second] > dist[p2.first][p2.second];
	}
};
class cmp2
{
public:
	bool operator()(const pair<int, int>& p1, const pair<int, int>& p2)
	{
		int f1 = g[p1.first][p1.second] + h[p1.first][p1.second];
		int f2 = g[p2.first][p2.second] + h[p2.first][p2.second];
		return f1 > f2;
	}
};

class cmp3
{
public:
	bool operator()(const pair<int, int>& p1, const pair<int, int>& p2)
	{
		return h[p1.first][p1.second] > h[p2.first][p2.second];
	}
};

int calcH(int x1, int y1, int x2, int y2)
{
	return max(max(x1, x2) - min(x1, x2), max(y1, y2) - min(y1, y2));
}

void backTrack(int ei, int ej, bool bi)
{
	bool ok1 = false, ok2 = true;
	int pari, parj, pari2, parj2, npari, nparj, npari2, nparj2;
	pari = ei, parj = parj2 = ej;
	pari2 = -1;
	if (bi)
	{
		ok2 = false;
		pari2 = ei;
		col[ei][ej] = 4;
		render(backtrackingSleepingTime);
	}
	while (true)
	{
		if (pari != -1)
		{
			col[pari][parj] = 4;
			render(backtrackingSleepingTime);
			npari = pi[pari][parj], nparj = pj[pari][parj];
			pari = npari, parj = nparj;
		}
		else
			ok1 = true;
		if (pari2 != -1)
		{
			col[pari2][parj2] = 4;
			render(backtrackingSleepingTime);
			npari2 = pi2[pari2][parj2], nparj2 = pj2[pari2][parj2];
			pari2 = npari2, parj2 = nparj2;
		}
		else
			ok2 = true;
		if (ok1 && ok2)
			break;
	}
}

void clear()
{
	for (int i = 0; i < ver; ++i)
		for (int j = 0; j < hor; ++j)
			if (col[i][j] == 1)
				col[i][j] = 0;
}

void reset(int si, int sj, int ei, int ej)
{
	memset(visited, false, sizeof(visited));
	memset(visited2, false, sizeof(visited2));
	memset(exists, false, sizeof(exists));
	memset(pi, -1, sizeof(pi));
	memset(pj, -1, sizeof(pj));
	memset(pi2, -1, sizeof(pi2));
	memset(pj2, -1, sizeof(pj2));
	for (int i = 0; i < ver; ++i)
		for (int j = 0; j < hor; ++j)
			dist[i][j] = g[i][j] = h[i][j] = maxx;
	openList.clear();
	col[si][sj] = 5;
	col[ei][ej] = 6;
	render(0);
}

void clearYellow()
{
	for (int i = 0; i < ver; ++i)
		for (int j = 0; j < hor; ++j)
			if (col[i][j] == 4)
				col[i][j] = 0;
	render(0);
}

void dfs(int i, int j, int si, int sj, int ei, int ej, bool& done)
{
	visited[i][j] = true;
	if (!((i == si && j == sj) || (i == ei && j == ej)))
		col[i][j] = 1;
	render(dfsSleepingTime);
	if (i == ei && j == ej)
	{
		clear();
		col[ei][ej] = 4;
		done = true;
		return;
	}
	for (int z = 0; z < 8; ++z)
	{
		int ni = i + dir[z].first;
		int nj = j + dir[z].second;
		if (ni >= 0 && ni < ver && nj >= 0 && nj < hor && col[ni][nj] != 3 && !visited[ni][nj])
		{
			pi[ni][nj] = i, pj[ni][nj] = j;
			dfs(ni, nj, si, sj, ei, ej, done);
			if (done)
				return;
		}
	}
	if (!(i == si && j == sj))
		col[i][j] = 2;
	render(dfsSleepingTime);
}

void bfs(int si, int sj, int ei, int ej)
{
	queue<pair<int, int>> q;
	visited[si][sj] = true;
	q.push({ si, sj });
	while (!q.empty())
	{
		auto f = q.front();
		q.pop();
		if (!((f.first == si && f.second == sj) || (f.first == ei && f.second == ej)))
		{
			col[f.first][f.second] = 1;
			render(bfsSleepingTime);
		}
		if (f.first == ei && f.second == ej)
		{
			clear();
			backTrack(ei, ej, false);
			return;
		}
		for (int z = 0; z < 8; ++z)
		{
			int ni = f.first + dir[z].first;
			int nj = f.second + dir[z].second;
			if (ni >= 0 && ni < ver && nj >= 0 && nj < hor && col[ni][nj] != 3 && !visited[ni][nj])
			{
				visited[ni][nj] = true;
				pi[ni][nj] = f.first, pj[ni][nj] = f.second;
				q.push({ ni, nj });
			}
		}
	}
	clear();
	render(bfsSleepingTime);
}

void bibfs(int si, int sj, int ei, int ej)
{
	queue<pair<int, int>> sourceQueue, destinationQueue;
	sourceQueue.push({ si, sj });
	destinationQueue.push({ ei, ej });
	visited[si][sj] = visited2[ei][ej] = true;
	while (!sourceQueue.empty() && !destinationQueue.empty())
	{
		auto f1 = sourceQueue.front();
		auto f2 = destinationQueue.front();
		sourceQueue.pop();
		destinationQueue.pop();
		if (!((f1.first == si && f1.second == sj) || (f1.first == ei && f1.second == ej)))
			col[f1.first][f1.second] = 1;
		if (!((f2.first == si && f2.second == sj) || (f2.first == ei && f2.second == ej)))
			col[f2.first][f2.second] = 1;
		render(bibfsSleepingTime);
		for (int z = 0; z < 8; ++z)
		{
			int ni = f1.first + dir[z].first;
			int nj = f1.second + dir[z].second;
			if (ni >= 0 && ni < ver && nj >= 0 && nj < hor && col[ni][nj] != 3 && !visited[ni][nj])
			{
				visited[ni][nj] = true;
				pi[ni][nj] = f1.first, pj[ni][nj] = f1.second;
				if (visited2[ni][nj])
				{
					clear();
					backTrack(ni, nj, true);
					return;
				}
				sourceQueue.push({ ni, nj });
			}
			ni = f2.first + dir[z].first;
			nj = f2.second + dir[z].second;
			if (ni >= 0 && ni < ver && nj >= 0 && nj < hor && col[ni][nj] != 3 && !visited2[ni][nj])
			{
				visited2[ni][nj] = true;
				pi2[ni][nj] = f2.first, pj2[ni][nj] = f2.second;
				if (visited[ni][nj])
				{
					clear();
					backTrack(ni, nj, true);
					return;
				}
				destinationQueue.push({ ni, nj });
			}
		}
	}
	clear();
}

void bestFirstSearch(int si, int sj, int ei, int ej)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp3> openList;
	h[si][sj] = 0;
	h[ver][hor] = INT_MAX;
	exists[si][sj] = true;
	openList.push({ si, sj });
	while (!openList.empty())
	{
		auto p = openList.top();
		openList.pop();
		if (p.first == ei && p.second == ej)
		{
			clear();
			backTrack(ei, ej, false);
			return;
		}
		if (!((p.first == si && p.second == sj)))
		{
			col[p.first][p.second] = 1;
			render(bestFirstSearchSleepingTime);
		}
		for (int z = 0; z < 8; ++z)
		{
			int ni = p.first + dir[z].first;
			int nj = p.second + dir[z].second;
			if (ni >= 0 && ni < ver && nj >= 0 && nj < hor && col[ni][nj] != 3 && !exists[ni][nj])
			{
				exists[ni][nj] = true;
				h[ni][nj] = calcH(ni, nj, ei, ej);
				pi[ni][nj] = p.first;
				pj[ni][nj] = p.second;
				openList.push({ ni, nj });
			}
		}
		openList.push({ ver, hor });
	}
	clear();
}

void dijkstra(int si, int sj, int ei, int ej)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
	dist[si][sj] = 0;
	dist[ver][hor] = INT_MAX;
	exists[si][sj] = true;
	pq.push({ si, sj });
	while (!pq.empty())
	{
		auto mn = pq.top();
		pq.pop();
		if (mn.first == ei && mn.second == ej)
		{
			clear();
			backTrack(ei, ej, false);
			return;
		}
		else if (!(mn.first == si && mn.second == sj))
			col[mn.first][mn.second] = 1;
		visited[mn.first][mn.second] = true;
		render(dijkstraSleepingTime);
		for (int z = 0; z < 8; ++z)
		{
			int ni = mn.first + dir[z].first;
			int nj = mn.second + dir[z].second;
			if (ni >= 0 && ni < ver && nj >= 0 && nj < hor && col[ni][nj] != 3 && !visited[ni][nj]
				&& dist[mn.first][mn.second] + 1 < dist[ni][nj])
			{
				dist[ni][nj] = dist[mn.first][mn.second] + 1;
				pi[ni][nj] = mn.first;
				pj[ni][nj] = mn.second;
				if (!exists[ni][nj])
				{
					pq.push({ ni, nj });
					exists[ni][nj] = true;
				}
			}
		}
		pq.push({ ver, hor });
	}
}

void aStar(int si, int sj, int ei, int ej)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp2> openList;
	g[si][sj] = h[si][sj] = 0;
	g[ver][hor] = INT_MAX >> 1, h[ver][hor] = INT_MAX >> 1;
	exists[si][sj] = true;
	openList.push({ si, sj });
	while (!openList.empty())
	{
		auto p = openList.top();
		openList.pop();
		if (p.first == ei && p.second == ej)
		{
			clear();
			backTrack(ei, ej, false);
			return;
		}
		if (!(p.first == si && p.second == sj))
		{
			col[p.first][p.second] = 1;
			render(aStarSleepingTime);
		}
		for (int z = 0; z < 8; ++z)
		{
			int ni = p.first + dir[z].first;
			int nj = p.second + dir[z].second;
			if (ni >= 0 && ni < ver && nj >= 0 && nj < hor && col[ni][nj] != 3 && g[p.first][p.second] + 1 < g[ni][nj])
			{
				g[ni][nj] = g[p.first][p.second] + 1;
				h[ni][nj] = calcH(ni, nj, ei, ej);
				pi[ni][nj] = p.first;
				pj[ni][nj] = p.second;
				if (!exists[ni][nj])
				{
					openList.push({ ni, nj });
					exists[ni][nj] = true;
				}
			}
		}
		openList.push({ ver, hor });
	}
	clear();
}

int main()
{
	player.setFillColor(sf::Color::Black);
	player.setOutlineColor(sf::Color::White);
	player.setOutlineThickness(1);
	memset(visited, false, sizeof(visited));
	memset(col, 0, sizeof(col));
	int si = -1, sj = -1, ei = -1, ej = -1;
	bool ok = true;
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
				window.close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && ok)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			int i = mousePos.y / sz, j = mousePos.x / sz;
			if (si == -1)
				si = i, sj = j, col[i][j] = 5;
			else if (ei == -1 && !(i == si && j == sj))
				ei = i, ej = j, col[i][j] = 6;
			else if (!((i == si && j == sj) || (i == ei && j == ej)))
				col[i][j] = 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && ei != -1) // D -> DFS
		{
			ok = false;
			bool bol = false;
			clearYellow();
			reset(si, sj, ei, ej);
			dfs(si, sj, si, sj, ei, ej, bol);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) && ei != -1) // B -> BFS
		{
			ok = false;
			clearYellow();
			reset(si, sj, ei, ej);
			bfs(si, sj, ei, ej);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I) && ei != -1) // I -> BIBFS
		{
			ok = false;
			clearYellow();
			reset(si, sj, ei, ej);
			bibfs(si, sj, ei, ej);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) && ei != -1) // T -> Best First Search
		{
			ok = false;
			clearYellow();
			reset(si, sj, ei, ej);
			bestFirstSearch(si, sj, ei, ej);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && ei != -1) // J -> DIJKSTRA
		{
			ok = false;
			clearYellow();
			reset(si, sj, ei, ej);
			dijkstra(si, sj, ei, ej);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && ei != -1) // A -> A*
		{
			ok = false;
			clearYellow();
			reset(si, sj, ei, ej);
			aStar(si, sj, ei, ej);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) // R -> RESET GRID
		{
			ok = true;
			memset(col, 0, sizeof(col));
			si = -1, sj = -1, ei = -1, ej = -1;
		}
		render(0);
	}
	return 0;
}
