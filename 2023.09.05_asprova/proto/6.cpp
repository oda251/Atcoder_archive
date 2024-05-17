#include <bits/stdc++.h>
#define HERE cout << "HERE" << endl
#define HOOK cout << "HOOK" << endl
#define SAYHO cout << "HO" << endl
#define MAX_R 3
using namespace std;

struct t_result
{
	int	score = 0;
	vector<tuple<int, int, int, int>>	val;
};
struct t_sub
{
	int	score = 0;
	vector<tuple<int, int, int, int>>	val;
	vector<tuple<int, int, int>>			sd;
	vector<vector<int>>								map;
	
	t_sub(const vector<vector<int>> &map_d, const vector<tuple<int, int, int>> &sd_list) {
		map = map_d;
		sd = sd_list;
	}
};

t_result	solve(vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list, vector<tuple<int, int, int>> &sd_list, const vector<tuple<int, int, int>> &map_arr, const int t, const map<int, pair<int, int>> &sd_map, const int max_rand);
vector<tuple<int, int, int>>			get_dist_empty_map(const vector<vector<pair<bool, bool>>> &wall_list, const int i0, const vector<vector<int>> &map_d);
int		get_max_puttable_d(const int dest_h, const int dest_w, const vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list);
void	harvest(vector<vector<int>> &map_d, const int t);
bool	is_ignorable(const int dest_h, const int dest_w, const vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list, vector<pair<int, int>> &seen);
int		select_crop(vector<tuple<int, int, int>> &sd_list, const int t, const int max_d, const int dist);
int		cout_score(vector<tuple<int, int, int, int>> result, map<int, pair<int, int>> sd_map);
void	get_ini_result(const vector<vector<pair<bool, bool>>> &wall_list, const int i0, vector<vector<int>> &map_d, vector<tuple<int, int, int>> &sd_list, vector<tuple<int, int, int, int>> &result, const int t, int &score);

double	culc_crop_score(int s, double d, int t, double dist)
{
	double	score = 0;

	// score = (d - s) - (s - t) * (s - t) / 3 - (d - t - dist * 2 / 3) * (d - t - dist * 2 / 3) / 40;
	// score = (d - s) * 1 - (s - t) * (s - t) * 10 - (d - t - dist * 2 / 3) * (d - t - dist * 2 / 3) / 60;
	score = (d - s) - (s - t) * (s - t) * 40;

	return (score);
}

int	select_crop(vector<tuple<int, int, int>> &sd_list, const int t, const int max_d, const int dist, const int max_rand)
{
	int	res_id = 0;
	double	min_score;
	double	tmp_score;
	vector<pair<vector<tuple<int, int, int>>::iterator, double>>	picked;
	int	selected = -1;

	for (auto it=sd_list.begin(); it!=sd_list.end(); it++)
	{
		if (get<2>(*it) > max_d || get<1>(*it) - t > 2) continue ;
		tmp_score = culc_crop_score(get<1>(*it), get<2>(*it), t, dist);
		if (picked.size() < max_rand)
		{
			if (picked.empty())
			{
			picked.emplace_back(it, tmp_score);
			min_score = tmp_score;
			}
			else
			{
				picked.emplace_back(it, tmp_score);
				min_score = min(min_score, tmp_score);
			}
		}
		else if (tmp_score > min_score)
		{
			picked.erase(find_if(picked.begin(), picked.end(), [min_score](auto &p){ return p.second == min_score; }));
			picked.emplace_back(it, tmp_score);
			min_score = (*min_element(picked.begin(), picked.end(), [](auto &a, auto &b){ return a.second < b.second; })).second;
		}
	}
	if (!picked.empty())
	{
		random_device	rd;
		mt19937				gen(rd());
		uniform_int_distribution<int>	distr(0, picked.size() - 1);
		selected = distr(gen);
		res_id = get<0>(*(picked[selected].first));
		sd_list.erase(picked[selected].first);
	}
	return (res_id);
}

void	solve_sub(vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list, vector<tuple<int, int, int>> &sd_list, int &t, const map<int, pair<int, int>> &sd_map, const int i0, t_result &result)
{
	t_sub			high_score(map_d, sd_list);
	t_result	tmp_res;
	vector<tuple<int, int, int>>	map_arr;
	int	tmp_t;
	int	round = ((t / 10) + 1) * 10;
	// int	round = 100;

	tmp_t = t;
	while (tmp_t <= round)
	{
		high_score.sd.erase(remove_if(high_score.sd.begin(), high_score.sd.end(), [tmp_t](const auto &tp){ return get<1>(tp) == tmp_t - 1; }), high_score.sd.end());
		map_arr = get_dist_empty_map(wall_list, i0, high_score.map);
		tmp_res = solve(high_score.map, wall_list, high_score.sd, map_arr, tmp_t, sd_map, 1);
		if (tmp_res.score) high_score.val.insert(high_score.val.end(), tmp_res.val.begin(), tmp_res.val.end());
		high_score.score += tmp_res.score;
		harvest(high_score.map, tmp_t);
		tmp_t++;
	}
	if (t < 70) {
	for (int i=0; i<3; i++)
	{
		t_sub			sub(map_d, sd_list);
		tmp_t = t;
		while (tmp_t <= round)
		{
			sub.sd.erase(remove_if(sub.sd.begin(), sub.sd.end(), [tmp_t](const auto &tp){ return get<1>(tp) == tmp_t - 1; }), sub.sd.end());
			map_arr = get_dist_empty_map(wall_list, i0, sub.map);
			tmp_res = solve(sub.map, wall_list, sub.sd, map_arr, tmp_t, sd_map, MAX_R);
			if (tmp_res.score) sub.val.insert(sub.val.end(), tmp_res.val.begin(), tmp_res.val.end());
			sub.score += tmp_res.score;
			harvest(sub.map, tmp_t);
			tmp_t++;
		}
		if (sub.score > high_score.score)
		{
			high_score = sub;
		}
	}
	}

	map_d = high_score.map;
	sd_list = high_score.sd;
	t = tmp_t;
	result.score += high_score.score;
	result.val.insert(result.val.end(), high_score.val.begin(), high_score.val.end());
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

	t_result	result;
	t_result	tmp_res;
	vector<tuple<int, int, int>>			map_arr;
	vector<vector<int>>								map_d(H, vector<int>(W, -2));

	get_ini_result(wall_list, i0, map_d, sd_list, result.val, 1, result.score);
	int t = 2;
	while (t <= 100)
	{
		// cout << t << ": " << count_if(sd_list.begin(), sd_list.end(), [t](auto &tp){ return get<1>(tp) == t || get<1>(tp) == t + 1 ;}) << endl;
		solve_sub(map_d, wall_list, sd_list, t, sd_map, i0, result);
	}
	cout << result.score * 25 << endl;
	cout << result.val.size() << endl;
	for (int i=0; i<result.val.size(); i++) cout << get<0>(result.val[i]) << ' ' << get<1>(result.val[i]) << ' ' << get<2>(result.val[i]) << ' ' << get<3>(result.val[i]) << endl;

	return (0);
}

vector<tuple<int, int, int>>	get_candidate_crops(vector<tuple<int, int, int>> &sd_list, int areas)
{
	map<int, vector<tuple<int, int, int>>>	tmp_list;
	vector<tuple<int, int, int>>	result;
	int	max_key;
	int	count = 0;

	sort(sd_list.begin(), sd_list.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) < get<2>(b); });
	for (auto &tp : sd_list)
	{
		if (count <= 400) max_key = max(max_key, get<1>(tp));
		if (get<1>(tp) <= max_key)
		{
			tmp_list[get<1>(tp)].emplace_back(tp);
			count++;
		}
	}
	for (auto &[k, v] : tmp_list)
	{
		if (areas) sort(v.begin(), v.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) - get<1>(a) > get<2>(b) - get<1>(a); });
		if (v.size() > areas) v.erase(v.begin() + areas, v.end());
		result.insert(result.end(), v.begin(), v.end());
		areas -= v.size();
	}
	sort(result.begin(), result.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) > get<2>(b); });
	return (result);
}

void	get_ini_result(const vector<vector<pair<bool, bool>>> &wall_list, const int i0, vector<vector<int>> &map_d, vector<tuple<int, int, int>> &sd_list, vector<tuple<int, int, int, int>> &result, const int t, int &score)
{
	vector<tuple<int, int, int>>	map_arr;
	vector<tuple<int, int, int>>	selected_crops;

	map_arr = get_dist_empty_map(wall_list, i0, map_d);
	selected_crops = get_candidate_crops(sd_list, map_arr.size());
	for (int i=0; i<selected_crops.size() && i<map_arr.size(); i++)
	{
		score += get<2>(selected_crops[i]) - get<1>(selected_crops[i]) + 1;
		result.emplace_back(get<0>(selected_crops[i]), get<0>(*(map_arr.begin() + i)), get<1>(*(map_arr.begin() + i)), t);
		sd_list.erase(find(sd_list.begin(), sd_list.end(), selected_crops[i]));
		map_d[get<0>(*(map_arr.begin() + i))][get<1>(*(map_arr.begin() + i))] = get<2>(selected_crops[i]);
	}
}

t_result	solve(vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list, vector<tuple<int, int, int>> &sd_list, const vector<tuple<int, int, int>> &map_arr, const int t, const map<int, pair<int, int>> &sd_map, const int max_rand)
{
	t_result	result;
	int	max_d;
	int	crop_id;

	for (auto &it : map_arr)
	{
		crop_id = 0;
		max_d = get_max_puttable_d(get<0>(it), get<1>(it), map_d, wall_list);
		crop_id = select_crop(sd_list, t, max_d, get<2>(it), max_rand);
		if (crop_id)
		{
			result.score += sd_map.at(crop_id).second - sd_map.at(crop_id).first + 1;
			result.val.emplace_back(crop_id, get<0>(it), get<1>(it), t);
			map_d[get<0>(it)][get<1>(it)] = sd_map.at(crop_id).second;
		}
		else map_d[get<0>(it)][get<1>(it)] = -1;
	}
	return (result);
}

int	get_max_puttable_d(const int dest_h, const int dest_w, const vector<vector<int>> &map_d, const vector<vector<pair<bool, bool>>> &wall_list)
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
	int	tmp_i = 0;

	to_see.emplace_back(i0, 0);
	dest[{i0, 0}] = 1;
	while (!to_see.empty())
	{
		tmp_dist = INT_MAX;
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

int	cout_score(vector<tuple<int, int, int, int>> result, map<int, pair<int, int>> sd_map)
{
	int	count = 0;
	int	crop_id;

	for (auto &tp : result)
	{
		crop_id = get<0>(tp);
		count += sd_map.at(crop_id).second - sd_map.at(crop_id).first + 1;
	}
	count *= 25;
	return (count);
}