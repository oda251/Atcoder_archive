#include <bits/stdc++.h>
#define HERE cout << "HERE" << endl
#define HOOK cout << "HOOK" << endl
#define SAYHO cout << "HO" << endl

using namespace std;
vector<tuple<int, int, int, int>>	solve(vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list, vector<tuple<int, int, int>> &sd_list, const vector<tuple<int, int, int>> &map_arr, const int t, const map<int, pair<int, int>> sd_map);
vector<tuple<int, int, int>>			get_dist_empty_map(const vector<vector<pair<bool, bool>>> &wall_list, const int i0, const vector<vector<int>> &map_d);
int		get_min_puttable_d(const int dest_h, const int dest_w, const vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list);
void	harvest(vector<vector<int>> &map_d, const int t);
void	remove_crops(vector<tuple<int, int, int>> &sd_list, const int t);
bool	is_ignorable(const int dest_h, const int dest_w, const vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list, vector<pair<int, int>> &seen);
int		select_crop(vector<tuple<int, int, int>> &sd_list, const int t, const int min_d);
void	cout_score(vector<tuple<int, int, int, int>> result, map<int, pair<int, int>> sd_map);

int	culc_crop_score(int s, int d, int t)
{
	int	score;

	score = ((d - s) * 3) - (s - t) * 2;
	return (score);
}

int	main(void)
{
	// START import params
	int			T, H, W, i0, K;
	cin >> T >> H >> W >> i0;
	string	tmp_line;
	vector<vector<pair<bool, bool>>>	wall_list(H, vector<pair<bool, bool>>(W, {1, 1}));
	for (int i=0; i<H-1; i++) {
		cin >> tmp_line;
		for (int j=0; j<W; j++) wall_list[i][j].first = tmp_line[j] - '0';
	}
	for (int i=0; i<H; i++) {
		cin >> tmp_line;
		for (int j=0; j<W-1; j++) wall_list[i][j].second = tmp_line[j] - '0';
	}
	cin >> K;
	// 0: cropID 1: S 2: D
	vector<tuple<int, int, int>>	sd_list(K);
	map<int, pair<int, int>>			sd_map;
	for (int i=0; i<K; i++)
	{
		get<0>(sd_list[i]) = i + 1;
		cin >> get<1>(sd_list[i]) >> get<2>(sd_list[i]);
		sd_map[i + 1] = pair(get<1>(sd_list[i]), get<2>(sd_list[i]));
	}
	// END import params

	vector<tuple<int, int, int, int>>	result;
	vector<tuple<int, int, int, int>>	tmp_res;

	vector<tuple<int, int, int>>	map_arr;
	vector<vector<int>>	map_d(H, vector<int>(W, -2));
	for (int t=1; t<=T; t++)
	{
		remove_crops(sd_list, t);
		map_arr = get_dist_empty_map(wall_list, i0, map_d);
		tmp_res = solve(map_d, wall_list, sd_list, map_arr, t, sd_map);
		if (!tmp_res.empty()) result.insert(result.end(), tmp_res.begin(), tmp_res.end());
		harvest(map_d, t);
	}

	cout << result.size() << endl;
	for (int i=0; i<result.size(); i++) cout << get<0>(result[i]) << ' ' << get<1>(result[i]) << ' ' << get<2>(result[i]) << ' ' << get<3>(result[i]) << endl;

	return (0);
}

vector<tuple<int, int, int, int>>	solve(vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list, vector<tuple<int, int, int>> &sd_list, const vector<tuple<int, int, int>> &map_arr, const int t, const map<int, pair<int, int>> sd_map)
{
	vector<tuple<int, int, int, int>>	result;
	int	min_d;
	int	crop_id;

	for (auto &it : map_arr)
	{
		crop_id = 0;
		min_d = get_min_puttable_d(get<0>(it), get<1>(it), map_d, wall_list);
		crop_id = select_crop(sd_list, t, min_d);
		if (crop_id)
		{
			result.emplace_back(crop_id, get<0>(it), get<1>(it), t);
			map_d[get<0>(it)][get<1>(it)] = sd_map.at(crop_id).second;
		}
		else map_d[get<0>(it)][get<1>(it)] = -1;
	}
	return (result);
}

int	select_crop(vector<tuple<int, int, int>> &sd_list, const int t, const int min_d)
{
	int	res_id = 0;
	int	res_score = INT_MIN;
	int	tmp_score;
	auto	itr = sd_list.begin();

	for (auto it=sd_list.begin(); it!=sd_list.end(); it++)
	{
		if (get<2>(*it) < min_d) continue ;
		tmp_score = culc_crop_score(get<1>(*it), get<2>(*it), t);
		if (tmp_score > res_score)
		{
			itr = it;
			res_id = get<0>(*it);
			res_score = tmp_score;
		}
	}
	if (itr != sd_list.end())
		sd_list.erase(itr);
	return (res_id);
}

int	get_min_puttable_d(const int dest_h, const int dest_w, const vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list)
{
	int	result = 100;
	vector<pair<int, int>>	targets;
	vector<pair<int, int>>	seen;
	vector<pair<int, int>>	ini_seen = {{dest_h, dest_w}};

	if (dest_h - 1 >= 0 && !wall_list[dest_h - 1][dest_w].first)
	{
		seen = ini_seen;
		if (map_d[dest_h - 1][dest_w] != -2 && !is_ignorable(dest_h - 1, dest_w, map_d, wall_list, seen))
			result = min(result, map_d[dest_h - 1][dest_w]);
	}
	if (dest_h + 1 < 20 && !wall_list[dest_h][dest_w].first)
	{
		seen = ini_seen;
		if (map_d[dest_h + 1][dest_w] != -2 && !is_ignorable(dest_h + 1, dest_w, map_d, wall_list, seen))
			result = min(result, map_d[dest_h + 1][dest_w]);
	}
	if (dest_w - 1 >= 0 && !wall_list[dest_h][dest_w - 1].second)
	{
		seen = ini_seen;
		if (map_d[dest_h][dest_w - 1] != -2 && !is_ignorable(dest_h, dest_w - 1, map_d, wall_list, seen))
			result = min(result, map_d[dest_h][dest_w - 1]);
	}
	if (dest_w + 1 < 20 && !wall_list[dest_h][dest_w].second)
	{
		seen = ini_seen;
		if (map_d[dest_h][dest_w + 1] != -2 && !is_ignorable(dest_h, dest_w + 1, map_d, wall_list, seen))
			result = min(result, map_d[dest_h][dest_w + 1]);
	}
	return (result);
}

bool	is_ignorable(const int dest_h, const int dest_w, const vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list, vector<pair<int, int>> &seen)
{
	seen.emplace_back(dest_h, dest_w);
	if ((dest_h - 1) >= 0 && !wall_list[dest_h - 1][dest_w].first && find(seen.begin(), seen.end(), pair(dest_h - 1, dest_w)) == seen.end())
	{
		if (map_d[dest_h - 1][dest_w] == -2) return (true);
		else if (map_d[dest_h - 1][dest_w] <= map_d[dest_h][dest_w])
			if (is_ignorable(dest_h - 1, dest_w, map_d, wall_list, seen)) return (true);
	}
	if (dest_h + 1 < 20 && !wall_list[dest_h][dest_w].first && find(seen.begin(), seen.end(), pair(dest_h + 1, dest_w)) == seen.end())
	{
		if (map_d[dest_h + 1][dest_w] == -2) return (true);
		else if (map_d[dest_h + 1][dest_w] <= map_d[dest_h][dest_w])
			if (is_ignorable(dest_h + 1, dest_w, map_d, wall_list, seen)) return (true);
	}
	if (dest_w - 1 >= 0 && !wall_list[dest_h][dest_w - 1].second && find(seen.begin(), seen.end(), pair(dest_h, dest_w - 1)) == seen.end())
	{
		if (map_d[dest_h][dest_w - 1] == -2) return (true);
		else if (map_d[dest_h][dest_w - 1] <= map_d[dest_h][dest_w])
			if (is_ignorable(dest_h, dest_w - 1, map_d, wall_list, seen)) return (true);
	}
	if (dest_w + 1 < 20 && !wall_list[dest_h][dest_w].second && find(seen.begin(), seen.end(), pair(dest_h, dest_w + 1)) == seen.end())
	{
		if (map_d[dest_h][dest_w + 1] == -2) return (true);
		else if (map_d[dest_h][dest_w + 1] <= map_d[dest_h][dest_w])
			if (is_ignorable(dest_h, dest_w + 1, map_d, wall_list, seen)) return (true);
	}
	return (false);
}

vector<tuple<int, int, int>>	get_dist_empty_map(const vector<vector<pair<bool, bool>>> &wall_list, const int i0, const vector<vector<int>> &map_d)
{
	map<pair<int, int>, int>	dest;
	vector<tuple<int, int, int>>	result;
	vector<pair<int, int>>		to_see;
	pair<int, int>						tmp_coord;
	int	tmp_dist;
	int	tmp_i;

	to_see.emplace_back(i0, 0);
	dest[{i0, 0}] = 1;
	while (!to_see.empty())
	{
		tmp_dist = 100;
		for (int i=0; 0 <= i && i < to_see.size(); i++)
		{
			if (tmp_dist > dest[to_see[i]])
			{
				tmp_coord = to_see[i];
				tmp_dist = dest[to_see[i]];
				tmp_i = i;
			}
		}
		to_see.erase(to_see.begin() + tmp_i);
		if (tmp_coord.first - 1 >= 0 && !wall_list[tmp_coord.first - 1][tmp_coord.second].first && dest.find(pair(tmp_coord.first - 1, tmp_coord.second)) == dest.end() && map_d[tmp_coord.first - 1][tmp_coord.second] == -2)
		{
			dest[{tmp_coord.first - 1, tmp_coord.second}] = tmp_dist + 1;
			to_see.emplace_back(tmp_coord.first - 1, tmp_coord.second);
		}
		if (tmp_coord.second - 1 >= 0 && !wall_list[tmp_coord.first][tmp_coord.second - 1].second && dest.find(pair(tmp_coord.first, tmp_coord.second - 1)) == dest.end() && map_d[tmp_coord.first][tmp_coord.second - 1] == -2)
		{
			dest[{tmp_coord.first, tmp_coord.second - 1}] = tmp_dist + 1;
			to_see.emplace_back(tmp_coord.first, tmp_coord.second - 1);
		}
		if (tmp_coord.first + 1 < 20 && !wall_list[tmp_coord.first][tmp_coord.second].first && dest.find(pair(tmp_coord.first + 1, tmp_coord.second)) == dest.end() && map_d[tmp_coord.first + 1][tmp_coord.second] == -2)
		{
			dest[{tmp_coord.first + 1, tmp_coord.second}] = tmp_dist + 1;
			to_see.emplace_back(tmp_coord.first + 1, tmp_coord.second);
		}
		if (tmp_coord.second + 1 < 20 && !wall_list[tmp_coord.first][tmp_coord.second].second && dest.find(pair(tmp_coord.first, tmp_coord.second + 1)) == dest.end() && map_d[tmp_coord.first][tmp_coord.second + 1] == -2)
		{
			dest[{tmp_coord.first, tmp_coord.second + 1}] = tmp_dist + 1;
			to_see.emplace_back(tmp_coord.first, tmp_coord.second + 1);
		}
	}
	for (const auto &[key, value] : dest)
		if (map_d[key.first][key.second] == -2) result.emplace_back(key.first, key.second, value);
	sort(result.begin(), result.end(), [](const auto &a, const auto &b){ return get<2>(a) > get<2>(b); });
	return (result);
}

void	harvest(vector<vector<int>> &map_d, const int t)
{
	for (int i=0; i<map_d.size(); i++)
	{
		for (int j=0; j<map_d[0].size(); j++)
			if (map_d[i][j] == t || map_d[i][j] == - 1) map_d[i][j] = -2;
	}
}

void	remove_crops(vector<tuple<int, int, int>> &sd_list, const int t)
{
	sd_list.erase(remove_if(sd_list.begin(), sd_list.end(), [t](const auto &tp){ return get<1>(tp) < t; }), sd_list.end());
}

void	cout_score(vector<tuple<int, int, int, int>> result, map<int, pair<int, int>> sd_map)
{
	int	count = 0;
	int	crop_id;

	for (auto &tp : result)
	{
		crop_id = get<0>(tp);
		count += sd_map.at(crop_id).second - sd_map.at(crop_id).first + 1;
	}
	count *= 25;
	cout << "score:" << count << endl;
}