#include <bits/stdc++.h>

using namespace std;
vector<tuple<int, int, int>>	get_dist_map(vector<vector<bool>> south_wall, vector<vector<bool>> east_wall, int H, int W, int i0);
vector<int>			get_crops_in_term(vector<tuple<int, int, int>> sd_list, int ini_term, int fin_term);
vector<int>			get_crops_in_term_thres(vector<tuple<int, int, int>> sd_list, int ini_term, int fin_term, int least_term);
vector<tuple<int, int, int, int>>	cat_result(vector<tuple<int, int, int, int>> dest, vector<tuple<int, int, int, int>> src);
vector<tuple<int, int, int, int>>	term_method(vector<tuple<int, int, int>> sd_list, vector<tuple<int, int, int>> dist_list, int ini_term, int fin_term);
vector<tuple<int, int, int, int>>	high_score_method(vector<tuple<int, int, int>> sd_list, vector<tuple<int, int, int>> dist_list, int ini_term, int fin_term, int thres);

int	main(void)
{
	// START import params
	int			T, H, W, i0, K;
	cin >> T >> H >> W >> i0;
	string	tmp_line;
	vector<vector<bool>>	south_wall(H - 1, vector<bool>(W));
	vector<vector<bool>>	east_wall(H, vector<bool>(W - 1));
	for (int i=0; i<H-1; i++) {
		cin >> tmp_line;
		for (int j=0; j<W; j++) south_wall[i][j] = tmp_line[j] - '0';
	}
	for (int i=0; i<H; i++) {
		cin >> tmp_line;
		for (int j=0; j<W-1; j++) east_wall[i][j] = tmp_line[j] - '0';
	}
	cin >> K;
	vector<tuple<int, int, int>>	sd_list(K);
	map<int, pair<int, int>>			sd_map;
	for (int i=0; i<K; i++)
	{
		get<0>(sd_list[i]) = i + 1;
		cin >> get<1>(sd_list[i]) >> get<2>(sd_list[i]);
		sd_map[i + 1] = pair(get<1>(sd_list[i]), get<2>(sd_list[i]));
	}
	vector<tuple<int, int, int, int>>	result;
	// END import params

	auto dist_list = get_dist_map(south_wall, east_wall, H, W, i0);
	sort(dist_list.begin(), dist_list.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) > get<2>(b); });
	vector<tuple<int, int, int>> tmp_dist_list;

	// most far area and most late harvest
	// sort(dist_list.begin(), dist_list.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) > get<2>(b); });
	// sort(sd_list.begin(), sd_list.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) > get<2>(b); });
	// cout << min(dist_list.size(), sd_list.size()) << endl;
	// for (int i=0; i<sd_list.size() && i<dist_list.size(); i++)
	// 	cout << get<0>(sd_list[i]) << ' ' << get<0>(dist_list[i]) << ' ' << get<1>(dist_list[i]) << ' ' << '1' << endl;


	// most near and most early harvest
	// sort(dist_list.begin(), dist_list.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) < get<2>(b); });
	// sort(sd_list.begin(), sd_list.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) < get<2>(b); });
	// cout << min(dist_list.size(), sd_list.size()) << endl;
	// for (int i=0; i<sd_list.size() && i<dist_list.size(); i++)
	// 	cout << get<0>(sd_list[i]) << ' ' << get<0>(dist_list[i]) << ' ' << get<1>(dist_list[i]) << ' ' << '1' << endl;

	// high-score-crops only
	// result = cat_result(result, high_score_method(sd_list, dist_list, 0, T, T * 0.9));

	// int	ini_res_len = result.size();
	// if (!result.empty())
	// 	sort(result.begin(), result.end(), [](const tuple<int, int, int, int> &a, const tuple<int, int, int, int> &b){ return get<2>(a) >= get<2>(b); });
	// int	pre = 0;
	// int now = 0;
	// for (int i=0; i<ini_res_len; i++)
	// {
	// 	if (i > 0) pre = sd_map[get<0>(result[i - 1])].second;
	// 	now = sd_map[get<0>(result[i])].second;
	// 	tmp_dist_list.clear();
	// 	for (auto it=dist_list.begin() + ini_res_len - i; it!=dist_list.end(); it++)
	// 		tmp_dist_list.emplace_back(*it);
	// 	result = cat_result(result, term_method(sd_list, tmp_dist_list, pre, now));
	// }
	// result = cat_result(result, term_method(sd_list, dist_list, now, T));

	// term method
	for (auto it=dist_list.begin() + result.size(); it!=dist_list.end(); it++)
		tmp_dist_list.emplace_back(*it);
	result = cat_result(result, term_method(sd_list, tmp_dist_list, 0, earliest));
	result = cat_result(result, term_method(sd_list, dist_list, latest, T));

	cout << result.size() << endl;
	for (int i=0; i<result.size(); i++) cout << get<0>(result[i]) << ' ' << get<1>(result[i]) << ' ' << get<2>(result[i]) << ' ' << get<3>(result[i]) << endl;

	return (0);
}

vector<tuple<int, int, int, int>>	high_score_method(vector<tuple<int, int, int>> sd_list, vector<tuple<int, int, int>> dist_list, int ini_term, int fin_term, int thres)
{
	vector<tuple<int, int, int, int>>	result;

	sort(sd_list.begin(), sd_list.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) > get<2>(b); });
	vector<int>	high_score_crops = get_crops_in_term_thres(sd_list, 0, fin_term, thres);
	for (int i=0; i<high_score_crops.size() && i<dist_list.size(); i++)
		result.emplace_back(tuple(get<0>(sd_list[high_score_crops[i]]), get<0>(dist_list[i]), get<1>(dist_list[i]), ini_term + 1));
	return (result);
}

vector<tuple<int, int, int, int>>	term_method(vector<tuple<int, int, int>> sd_list, vector<tuple<int, int, int>> dist_list, int ini_term, int fin_term)
{
	int							term = 20;
	vector<int>			crops_in_term;
	vector<tuple<int, int, int, int>>	result;

	sort(dist_list.begin(), dist_list.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) < get<2>(b); });
	sort(sd_list.begin(), sd_list.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b){ return get<2>(a) < get<2>(b); });
	for (int i=0; ini_term+(i*term)<fin_term; i++)
	{
		crops_in_term = get_crops_in_term(sd_list, ini_term+ (i * term), min(ini_term + ((i + 1) * term), fin_term));
		for (int j=0; j<crops_in_term.size() && j<dist_list.size(); j++)
			result.emplace_back(tuple(get<0>(sd_list[crops_in_term[j]]), get<0>(dist_list[j]), get<1>(dist_list[j]), ini_term + i * term + 1));
	}
	return (result);
}

vector<int>	get_crops_in_term(vector<tuple<int, int, int>> sd_list, int ini_term, int fin_term)
{
	vector<int>	dest;

	for (int i=0; i<sd_list.size() && get<2>(sd_list[i]) < fin_term; i++)
	{
		if (get<1>(sd_list[i]) <= ini_term) continue ;
		dest.emplace_back(i);
	}
	return (dest);
}

vector<int>	get_crops_in_term_thres(vector<tuple<int, int, int>> sd_list, int ini_term, int fin_term, int least_term)
{
	vector<int>	dest;

	for (int i=0; i<sd_list.size(); i++)
		if (get<1>(sd_list[i]) >= ini_term && get<2>(sd_list[i]) < fin_term && get<2>(sd_list[i]) - get<1>(sd_list[i]) > least_term) dest.emplace_back(i);
	return (dest);
}

vector<tuple<int, int, int>>	get_dist_map(vector<vector<bool>> south_wall, vector<vector<bool>> east_wall, int H, int W, int i0)
{
	vector<tuple<int, int, int>>	dest;
	vector<vector<int>>						dist_map(H, vector<int>(W, -1));
	vector<pair<int, int>>				to_see;
	pair<int, int>								tmp_coord;
	int	tmp_dist;
	int	tmp_i;

	to_see.emplace_back(i0, 0);
	dist_map[i0][0] = 1;
	while (!to_see.empty())
	{
		tmp_dist = 100;
		for (int i=0; 0 <= i && i < to_see.size(); i++)
		{
			if (tmp_dist > dist_map[to_see[i].first][to_see[i].second])
			{
				tmp_coord = to_see[i];
				tmp_dist = dist_map[to_see[i].first][to_see[i].second];
				tmp_i = i;
			}
		}
		to_see.erase(to_see.begin() + tmp_i);
		if (tmp_coord.first - 1 >= 0 && !south_wall[tmp_coord.first - 1][tmp_coord.second] && dist_map[tmp_coord.first - 1][tmp_coord.second] == -1)
		{
			dist_map[tmp_coord.first - 1][tmp_coord.second] = tmp_dist + 1;
			to_see.emplace_back(tmp_coord.first - 1, tmp_coord.second);
		}
		if (tmp_coord.second - 1 >= 0 && !east_wall[tmp_coord.first][tmp_coord.second - 1] && dist_map[tmp_coord.first][tmp_coord.second - 1] == -1)
		{
			dist_map[tmp_coord.first][tmp_coord.second - 1] = tmp_dist + 1;
			to_see.emplace_back(tmp_coord.first, tmp_coord.second - 1);
		}
		if (tmp_coord.first + 1 < H && !south_wall[tmp_coord.first][tmp_coord.second] && dist_map[tmp_coord.first + 1][tmp_coord.second] == -1)
		{
			dist_map[tmp_coord.first + 1][tmp_coord.second] = tmp_dist + 1;
			to_see.emplace_back(tmp_coord.first + 1, tmp_coord.second);
		}
		if (tmp_coord.second + 1 < W && !east_wall[tmp_coord.first][tmp_coord.second] && dist_map[tmp_coord.first][tmp_coord.second + 1] == -1)
		{
			dist_map[tmp_coord.first][tmp_coord.second + 1] = tmp_dist + 1;
			to_see.emplace_back(tmp_coord.first, tmp_coord.second + 1);
		}
	}
	for (int i=0; i<H; i++)
		for (int j=0; j<W; j++) dest.emplace_back(i, j, dist_map[i][j]);
	return (dest);
}

vector<tuple<int, int, int, int>>	cat_result(vector<tuple<int, int, int, int>> dest, vector<tuple<int, int, int, int>> src)
{
	dest.insert(dest.end(), src.begin(), src.end());
	return (dest);
}