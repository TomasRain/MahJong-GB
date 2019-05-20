#include "tile.h"
#include "shanten.h"
#include "stringify.h"
#include "fan_calculator.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <limits>
#include <assert.h>

#pragma warning(disable:4996)


using namespace mahjong;
using namespace std;

#define TIMES 1005
#define CP 50


tile_t paichi[4 * 34];
tile_t ceshi[4 * 34];
tile_table_t all;
tile_table_t hand;
useful_table_t wait, test;
hand_tiles_t temp;
int iflis;

void test_wait(const char *str) {
    hand_tiles_t hand_tiles;
    string_to_tiles(str, &hand_tiles, nullptr);

    std::cout << "----------------" << std::endl;
    puts(str);
    bool is_wait = false;
    useful_table_t table/* = { false }*/;

    if (hand_tiles.tile_count == 13) {
        if (is_thirteen_orphans_wait(hand_tiles.standing_tiles, 13, &table)) {
            is_wait = true;
            printf("thirteen orphans");
        }
        else if (is_honors_and_knitted_tiles_wait(hand_tiles.standing_tiles, 13, &table)) {
            is_wait = true;
            printf("honors and knitted tiles");
        }
        else if (is_seven_pairs_wait(hand_tiles.standing_tiles, 13, &table)) {
            is_wait = true;
            printf("seven pairs");
        }
        else if (is_knitted_straight_wait(hand_tiles.standing_tiles, 13, &table)) {
            is_wait = true;
            printf("knitted straight in basic form");
        }
    }
    else if (hand_tiles.tile_count == 10) {
        if (is_knitted_straight_wait(hand_tiles.standing_tiles, 10, &table)) {
            is_wait = true;
            printf("knitted straight in basic form");
        }
    }

    if (!is_wait && is_basic_form_wait(hand_tiles.standing_tiles, hand_tiles.tile_count, &table)) {
        is_wait = true;
        printf("basic form");
    }

    if (is_wait) {
        puts(" waiting:");
        char buf[64];
        for (tile_t t = TILE_1m; t < TILE_TABLE_SIZE; ++t) {
            if (table[t]) {
                tiles_to_string(&t, 1, buf, sizeof(buf));
                printf("%s ", buf);
            }
        }
    }
    else {
        puts("not wait!");
    }
    puts("");
}


void test_points(const char *str, win_flag_t win_flag, wind_t prevalent_wind, wind_t seat_wind) {
    calculate_param_t param;

    long ret = string_to_tiles(str, &param.hand_tiles, &param.win_tile);
    if (ret != PARSE_NO_ERROR) {
        printf("error at line %d error = %ld\n", __LINE__, ret);
        return;
    }

    fan_table_t fan_table/* = { 0 }*/;
    puts("----------------");
    puts(str);

    param.flower_count = 0;

    param.win_flag = win_flag;
    param.prevalent_wind = prevalent_wind;
    param.seat_wind = seat_wind;
    int points = calculate_fan(&param, &fan_table);

    printf("max points = %d\n\n", points);
    if (points < 0) {
        return;
    }

    for (int i = 1; i < FLOWER_TILES; ++i) {
        if (fan_table[i] == 0) {
            continue;
        }
        if (fan_table[i] == 1) {
            printf("%s %d\n", fan_name[i], fan_value_table[i]);
        }
        else {
            printf("%s %d*%hd\n", fan_name[i], fan_value_table[i], fan_table[i]);
        }
    }
}


void test_shanten(const char *str) {
    hand_tiles_t hand_tiles;
    long ret = string_to_tiles(str, &hand_tiles, nullptr);
    if (ret != 0) {
        printf("error at line %d error = %ld\n", __LINE__, ret);
        return;
    }

    char buf[20];
    ret = hand_tiles_to_string(&hand_tiles, buf, sizeof(buf));
    puts(buf);

    auto display = [](const hand_tiles_t *hand_tiles, useful_table_t &useful_table) {
        char buf[64];
        for (tile_t t = TILE_1m; t < TILE_TABLE_SIZE; ++t) {
            if (useful_table[t]) {
                tiles_to_string(&t, 1, buf, sizeof(buf));
                printf("%s ", buf);
            }
        }

        tile_table_t cnt_table;
        map_hand_tiles(hand_tiles, &cnt_table);

        printf("%d枚", count_useful_tile(cnt_table, useful_table));
    };

    puts(str);
    useful_table_t useful_table/* = {false}*/;
    int ret0;
    ret0 = thirteen_orphans_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("131=== %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);
    puts("\n");

    ret0 = seven_pairs_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("7d=== %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);
    puts("\n");

    ret0 = honors_and_knitted_tiles_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("honors and knitted tiles  %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);
    puts("\n");

    ret0 = knitted_straight_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("knitted straight in basic form %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);
    puts("\n");

    ret0 = basic_form_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("basic form %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);
    puts("\n");
}

//判断是否听牌
int if_wait(hand_tiles_t &t, tile_table_t &cnt, useful_table_t &useful)
{
	bool is_wait = false;
	//如果是立牌是13张
	if (t.tile_count == 13) {
		//十三幺
		if (is_thirteen_orphans_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
		//全不靠
		else if (is_honors_and_knitted_tiles_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
		//七对
		else if (is_seven_pairs_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
		//组合龙
		else if (is_knitted_straight_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
	}
	else if (t.tile_count == 10) {
		//组合龙
		if (is_knitted_straight_wait(t.standing_tiles, 10, &useful)) {
			is_wait = true;
		}
	}

	//基本户
	if (!is_wait && is_basic_form_wait(t.standing_tiles, t.tile_count, &useful)) 
		is_wait = true;

	//计算有效牌的数量
	if (is_wait) {
		int num = 0;
		for (tile_t t = TILE_1m; t < TILE_TABLE_SIZE; ++t) {
			if (useful[t] && cnt[t])
				num += cnt[t];
		}
		return num;
	}

	//如果返回0，则代表没有听牌或者有效牌为0
	return 0;
}

//根据当前可能组成顺子，刻子的可能性进行估值
void evaluate(int kind, int pos, int &maxn)
{
	//如果已经判断到东南西北中发白了
	if (kind == 4)
	{
		int score = 0;
		for (tile_t i = 16; i < 72; ++i) {
			if (hand[i])
			{
				//单张？
				score -= hand[i] * 1000;
				//why？
				if (hand[i] >= 3)
					return;
				//如果是字牌
				if (i < 64)
				{
					if (hand[i] == 1)
					{
						//有多大的几率组成顺子
						//在这儿不考虑刻子了吗？
						if (hand[i - 1] > 0)
							score += 10 * (4 - all[i - 2]);
						if (hand[i + 1] > 0)
							score += 10 * (4 - all[i + 2]);
						if (hand[i - 2] > 0)
							score += 10 * (4 - all[i - 1]);
						if (hand[i + 2] > 0)
							score += 10 * (4 - all[i + 1]);
						score += 20 - all[i - 1] - all[i + 1] - all[i] - all[i + 2] - all[i - 2];
					}
					if (hand[i] == 2)
					{
						if (hand[i - 1] > 0)
							score += 10 * (4 - all[i - 2]);
						if (hand[i + 1] > 0)
							score += 10 * (4 - all[i + 2]);
						score += 56 - all[i - 1] - all[i + 1] - all[i] * 10 - all[i + 2] - all[i - 2];
						if (hand[i - 2] > 0)
							score += 10 * (4 - all[i - 1]);
						if (hand[i + 2] > 0)
							score += 10 * (4 - all[i + 1]);
						score += 20;
					}
				}
				//东南西北中发白
				else
				{
					//只有刻子有意义
					if (hand[i] == 1)
						score += 4 - all[i];
					else
						score += 80 - all[i] * 10;
					if (hand[i] == 3)
						score += 3000;
				}
			}
		}
		maxn = max(maxn, score);
		return;
	}
	
	//确定在手牌中的位置
	int t = kind * 16 + pos;

	//刻子
	if (hand[t] >= 3)
	{
		hand[t] -= 3;
		//如果是第9张，调到下一类
		if (pos == 9)
			evaluate(kind + 1, 1, maxn);
		else
			evaluate(kind, pos + 1, maxn);
		hand[t] += 3;
	}

	//顺子
	//有没有考虑过：W1W1W2W2W3这种情况？
	if (hand[t] && hand[t + 1] && hand[t + 2])
	{
		--hand[t]; --hand[t + 1]; --hand[t + 2];
		if (pos == 9)
			evaluate(kind + 1, 1, maxn);
		else
			evaluate(kind, pos + 1, maxn);
		++hand[t]; ++hand[t + 1]; ++hand[t + 2];
	}

	//nothing
	if (pos == 9)
		evaluate(kind + 1, 1, maxn);
	else
		evaluate(kind, pos + 1, maxn);
}


void show(tile_table_t &ta)
{
	for (int i = 1; i <= 3; ++i)
	{
		for (int j = 1; j <= 9; ++j)
			printf("%d ", ta[i * 16 + j]);
		printf("\n");
	}
	for (int j = 1; j <= 7; ++j)
		printf("%d ", ta[64 + j]);
	printf("\n");
}


void init(tile_table_t &ta)
{
	int cnt = 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 9; ++j)
		{
			all[i * 16 + j] = 0;
			hand[i * 16 + j] = 0;
			wait[i * 16 + j] = false;
			for (int k = 0; k < 4; ++k)
				paichi[cnt++] = i * 16 + j;
		}
	for (int j = 1; j <= 7; ++j)
	{
		all[64 + j] = 0;
		hand[64 + j] = 0;
		wait[64 + j] = false;
		for (int k = 0; k < 4; ++k)
			paichi[cnt++] = 64 + j;
	}
	srand((unsigned)time(NULL));
	random_shuffle(paichi, paichi + 34 * 4);
}

int chi(tile_t pai)
{
	useful_table_t test;
	temp.tile_count = 0;
	int max;
	for (intptr_t j = 17; j < 72; ++j)
		if (hand[j])
			for (int k = 0; k < hand[j]; ++k)
				temp.standing_tiles[temp.tile_count++] = j;
	max = if_wait(temp, all, test) * 1000;
	if (max == 0)
	{
		max = -10000000;
		evaluate(1, 1, max);
	}
	int da = 0;
	if (hand[pai - 1] && hand[pai - 2])
	{
		--hand[pai - 1]; --hand[pai - 2];
		temp.fixed_packs[temp.pack_count++] = make_pack(3, PACK_TYPE_CHOW, pai - 1);
		for (intptr_t i = 17; i < 72; ++i)
			if (hand[i])
			{
				--hand[i];
				temp.tile_count = 0;
				for (intptr_t j = 17; j < 72; ++j)
					if (hand[j])
						for (int k = 0; k < hand[j]; ++k)
							temp.standing_tiles[temp.tile_count++] = j;
				int res;
				if (res = if_wait(temp, all, test))
				{
					if (res * 1000 > max)
					{
						max = res * 1000;
						memcpy(wait, test, sizeof(useful_table_t));
						iflis = 1;
						da = (i << 2) | 1;
					}
				}
				else
				{
					res = -10000000;
					evaluate(1, 1, res);
					if (res > max)
					{
						max = res;
						da = (i << 2) | 1;
					}
				}
				++hand[i];
			}
		temp.pack_count--;
		++hand[pai - 1]; ++hand[pai - 2];
	}
	if (hand[pai - 1] && hand[pai + 1])
	{
		--hand[pai - 1]; --hand[pai + 1];
		temp.fixed_packs[temp.pack_count++] = make_pack(2, PACK_TYPE_CHOW, pai);
		for (intptr_t i = 17; i < 72; ++i)
			if (hand[i])
			{
				--hand[i];
				temp.tile_count = 0;
				for (intptr_t j = 17; j < 72; ++j)
					if (hand[j])
						for (int k = 0; k < hand[j]; ++k)
							temp.standing_tiles[temp.tile_count++] = j;
				int res;
				if (res = if_wait(temp, all, test))
				{
					if (res * 1000 > max)
					{
						max = res * 1000;
						memcpy(wait, test, sizeof(useful_table_t));
						da = (i << 2) | 2;
						iflis = 1;
					}
				}
				else
				{
					res = -10000000;
					evaluate(1, 1, res);
					if (res > max)
					{
						max = res;
						da = (i << 2) | 2;
					}
				}
				++hand[i];
			}
		temp.pack_count--;
		++hand[pai - 1]; ++hand[pai + 1];
	}
	if (hand[pai + 1] && hand[pai + 2])
	{
		--hand[pai + 1]; --hand[pai + 2];
		temp.fixed_packs[temp.pack_count++] = make_pack(1, PACK_TYPE_CHOW, pai + 1);
		for (intptr_t i = 17; i < 72; ++i)
			if (hand[i])
			{
				--hand[i];
				temp.tile_count = 0;
				for (intptr_t j = 17; j < 72; ++j)
					if (hand[j])
						for (int k = 0; k < hand[j]; ++k)
							temp.standing_tiles[temp.tile_count++] = j;
				int res;
				if (res = if_wait(temp, all, test))
				{
					if (res * 1000 > max)
					{
						max = res * 1000;
						memcpy(wait, test, sizeof(useful_table_t));
						da = (i << 2) | 3;
						iflis = 1;
					}
				}
				else
				{
					res = -10000000;
					evaluate(1, 1, res);
					if (res > max)
					{
						max = res;
						da = (i << 2) | 3;
					}
				}
				++hand[i];
			}
		temp.pack_count--;
		++hand[pai + 1]; ++hand[pai + 2];
	}
	if (da > 0)
	{
		//printf("before chi:    da: %x\n", da);
		//show(hand);
		if ((da & 3) == 1)
			temp.fixed_packs[temp.pack_count++] = make_pack(3, PACK_TYPE_CHOW, pai - 1), --hand[pai-1], --hand[pai-2];
		if ((da & 3) == 2)
			temp.fixed_packs[temp.pack_count++] = make_pack(2, PACK_TYPE_CHOW, pai), --hand[pai - 1], --hand[pai + 1];
		if ((da & 3) == 3)
			temp.fixed_packs[temp.pack_count++] = make_pack(1, PACK_TYPE_CHOW, pai + 1), --hand[pai + 1], --hand[pai + 2];
		--hand[da >> 2];
		//show(hand);
		//printf("get : %x\n", (int)pai);
		//printf("CHI:\n");
		//system("pause");
	}
	return da >> 2;
}

int peng(tile_t pai, int player)
{
	useful_table_t test;
	int max;
	temp.tile_count = 0;
	for (intptr_t j = 17; j < 72; ++j)
		if (hand[j])
			for (int k = 0; k < hand[j]; ++k)
				temp.standing_tiles[temp.tile_count++] = j;
	max = if_wait(temp, all, test) * 1000;
	if (max == 0)
	{
		max = -10000000;
		evaluate(1, 1, max);
	}
	int da = 0;
	//能不能碰牌
	if (hand[pai] == 2)
	{
		hand[pai] -= 2;
		//记录副露信息，碰牌
		temp.fixed_packs[temp.pack_count++] = make_pack(player, PACK_TYPE_PUNG, pai);
		//碰牌之后应该打那张牌
		for (intptr_t i = 17; i < 72; ++i) {
			if (hand[i])
			{
				--hand[i];
				temp.tile_count = 0;
				for (intptr_t j = 17; j < 72; ++j)
					if (hand[j])
						for (int k = 0; k < hand[j]; ++k)
							temp.standing_tiles[temp.tile_count++] = j;
				int res;
				if (res = if_wait(temp, all, test))
				{
					if (res * 1000 > max)
					{
						max = res * 1000;
						memcpy(wait, test, sizeof(useful_table_t));
						da = i;
						iflis = 1;
					}
				}
				else
				{
					res = -10000000;
					evaluate(1, 1, res);
					if (res > max)
					{
						max = res;
						da = i;
					}
				}
				++hand[i];
			}
		}
		//这是啥？
		if (da == 0)
		{
			temp.pack_count--;
			hand[pai] += 2;
			return 0;
		}
		hand[da];
		return da;
	}

	//杠牌
	if (hand[pai] == 3)
	{
		hand[pai] -= 3;
		temp.tile_count = 0;
		for (intptr_t j = 17; j < 72; ++j)
			if (hand[j])
				for (int k = 0; k < hand[j]; ++k)
					temp.standing_tiles[temp.tile_count++] = j;
		int res;
		//记录杠牌副露
		temp.fixed_packs[temp.pack_count++] = make_pack(player, PACK_TYPE_KONG, pai);
		if (res = if_wait(temp, all, test))
		{
			if (res * 1000 > max)
			{
				max = res * 1000;
				memcpy(wait, test, sizeof(useful_table_t));
				da = 1;
			}
		}
		else
		{
			res = -10000000;
			evaluate(1, 1, res);
			if (res > max)
				max = res, da = 1;
		}
		if (da == 0)
		{
			--temp.pack_count;
			hand[pai] += 3;
			return 0;
		}
		return 100;
	}
	return 0;
}

void moda(tile_t *paichi, int &pos)
{
	++hand[paichi[pos]]; ++all[paichi[pos++]];
	int max = -10000000;
	tile_t best;
	for (intptr_t i = 17; i < 72; ++i)
		if (hand[i])
		{
			--hand[i];
			temp.tile_count = 0;
			for (intptr_t j = 17; j < 72; ++j)
				if (hand[j])
					for (int k = 0; k < hand[j]; ++k)
						temp.standing_tiles[temp.tile_count++] = j;
			int res;
			if (res = if_wait(temp, all, test))
			{
				if (res * 1000 > max)
				{
					max = res * 1000;
					memcpy(wait, test, sizeof(useful_table_t));
					best = i;
					iflis = 1;
				}
			}
			else
			{
				res = -10000000;
				evaluate(1, 1, res);
				if (res > max)
				{
					max = res;
					best = i;
				}
			}
			++hand[i];
		}
	--hand[best];
}

int simulate(tile_t *paichi, int n)
{
	int pos = 0;
	n -= 4;//why?
	while (true && pos < n)
	{
		++all[paichi[pos]];
		//如果可以杠
		if (peng(paichi[pos++], 3) == 100)
			moda(paichi, pos);
		//如果已经做出打牌的决策
		if (iflis > 0)
			return pos;
		++all[paichi[pos]];
		if (peng(paichi[pos++], 2) == 100)
			moda(paichi, pos);
		if (iflis > 0)
			return pos;
		++all[paichi[pos]];
		if (chi(paichi[pos]) == 0)
			if (peng(paichi[pos++], 1) == 100)
				moda(paichi, pos);
		if (iflis > 0)
			return pos;
		moda(paichi, pos);
		if (iflis > 0)
			return pos;
	}
	return 200;
}

int S;

tile_t decide()
{
	int cnt[15], score[15], tiles[15], num = -1, maxn = 0;
	int T = 0;
	//ceshi中的牌应该是牌局中每张牌所剩的最大值
	//字牌
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 9; ++j)
			for (int k = 0; k < 4 - all[i * 16 - 4]; ++k)
				ceshi[T++] = i * 16 + j;
	//东南西北中发白
	for (int j = 1; j <= 7; ++j)
		for (int k = 0; k < 4 - all[64 + j]; ++k)
			ceshi[T++] = 64 + j;
	
	tile_t ret = 0;
	tile_table_t tmp, alltmp;
	//N：副露的面子数
	intptr_t N = temp.pack_count;

	memcpy(tmp, hand, sizeof(tmp));
	memset(score, 0, sizeof(score));
	memcpy(alltmp, all, sizeof(tmp));
	memset(cnt, 0, sizeof(cnt));

	for (intptr_t i = 17; i < 72; ++i) {
		//模拟打出每一张牌
		if (hand[i])
		{
			--hand[i];
			tiles[++num] = i;
			temp.tile_count = 0;
			for (intptr_t j = 17; j < 72; ++j)
				if (hand[j])
					for (int k = 0; k < hand[j]; ++k)
						temp.standing_tiles[temp.tile_count++] = j;
			int res;
			//计算有效牌的数量
			if (res = if_wait(temp, all, test))
				if (res > maxn)
					maxn = res, ret = i;
			++hand[i];
		}
	}

	if (maxn > 0)
	{
		//返回有效牌数量 * 1000
		S = 1000 * maxn;
		return ret;
	}

	//如果没有听牌
	for (int i = 0; i <= num; ++i)
	{
		++cnt[i];
		//随机模拟打一张牌
		--hand[tiles[i]];
		iflis = 0;
		random_shuffle(ceshi, ceshi +  T);
		score[i] -= simulate(ceshi, T);
		memcpy(hand, tmp, sizeof(tmp));
		memcpy(all, alltmp, sizeof(alltmp));
		temp.pack_count = N;
	}

	//monte carlo search
	for (int t = num; t <= TIMES; ++t)
	{
		double max = -1e20;
		int sti;
		for (int i = 0; i <= num; ++i)
		{
			double val = (double)score[i] / (double)cnt[i] + CP * sqrt(2 * log(t) / cnt[i]);
			if (val > max)
				max = val, sti = i;
		}
		++cnt[sti];
		--hand[tiles[sti]];
		iflis = 0;
		random_shuffle(ceshi, ceshi + T);
		score[sti] -= simulate(ceshi, T);
		temp.pack_count = N;
		memcpy(hand, tmp, sizeof(tmp));
		memcpy(all, alltmp, sizeof(alltmp));
	}
	ret = 0;
	for (int i = 1; i <= num; ++i)
		if (score[i] * cnt[ret] > score[ret] * cnt[i])
			ret = i;
	S = score[ret] / cnt[ret];
	return tiles[ret];
}


int chisti(tile_t pai)
{
	int T = 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 9; ++j)
			for (int k = 0; k < 4 - all[i * 16 - 4]; ++k)
				ceshi[T++] = i * 16 + j;
	for (int j = 1; j <= 7; ++j)
		for (int k = 0; k < 4 - all[64 + j]; ++k)
			ceshi[T++] = 64 + j;
	useful_table_t test;
	tile_table_t tmp, alltmp;
	intptr_t N = temp.pack_count;
	memcpy(tmp, hand, sizeof(tmp));
	memcpy(alltmp, all, sizeof(tmp));
	int max = 0;
	temp.tile_count = 0;
	for (intptr_t j = 17; j < 72; ++j)
		if (hand[j])
			for (int k = 0; k < hand[j]; ++k)
				temp.standing_tiles[temp.tile_count++] = j;
	if (max = if_wait(temp, all, test))
		max = max * 1000;
	else
	{
		for (int i = 0; i < TIMES; ++i)
		{
			iflis = 0;
			random_shuffle(ceshi, ceshi + T);
			max -= simulate(ceshi, T);
			temp.pack_count = N;
			memcpy(hand, tmp, sizeof(tmp));
			memcpy(all, alltmp, sizeof(alltmp));
		}
		max /= TIMES;
	}
	int da = 0;
	if (hand[pai - 1] && hand[pai - 2])
	{
		--hand[pai - 1]; --hand[pai - 2];
		temp.fixed_packs[temp.pack_count++] = make_pack(3, PACK_TYPE_CHOW, pai - 1);
		tile_t ret = decide();
		if (S > max)
			max = S, da = (ret << 2) | 1;
		temp.pack_count--;
		++hand[pai - 1]; ++hand[pai - 2];
	}
	if (hand[pai - 1] && hand[pai + 1])
	{
		--hand[pai - 1]; --hand[pai + 1];
		temp.fixed_packs[temp.pack_count++] = make_pack(2, PACK_TYPE_CHOW, pai);
		tile_t ret = decide();
		if (S > max)
			max = S, da = (ret << 2) | 2;
		temp.pack_count--;
		++hand[pai - 1]; ++hand[pai + 1];
	}
	if (hand[pai + 1] && hand[pai + 2])
	{
		--hand[pai + 1]; --hand[pai + 2];
		temp.fixed_packs[temp.pack_count++] = make_pack(1, PACK_TYPE_CHOW, pai + 1);
		tile_t ret = decide();
		if (S > max)
			max = S, da = (ret << 2) | 3;
		temp.pack_count--;
		++hand[pai + 1]; ++hand[pai + 2];
	}
	if (da > 0)
	{
		if (max > 0)
			S = 1000;
		printf("before chi:    da: %x\n", da);
		show(hand);
		if ((da & 3) == 1)
			temp.fixed_packs[temp.pack_count++] = make_pack(3, PACK_TYPE_CHOW, pai - 1), --hand[pai - 1], --hand[pai - 2];
		if ((da & 3) == 2)
			temp.fixed_packs[temp.pack_count++] = make_pack(2, PACK_TYPE_CHOW, pai), --hand[pai - 1], --hand[pai + 1];
		if ((da & 3) == 3)
			temp.fixed_packs[temp.pack_count++] = make_pack(1, PACK_TYPE_CHOW, pai + 1), --hand[pai + 1], --hand[pai + 2];
		--hand[da >> 2];
		show(hand);
		printf("get : %x\n", (int)pai);
		printf("CHI:\n");
		system("pause");
	}
	return da >> 2;
}

int pengsti(tile_t pai, int player)
{
	int T = 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 9; ++j)
			for (int k = 0; k < 4 - all[i * 16 - 4]; ++k)
				ceshi[T++] = i * 16 + j;
	for (int j = 1; j <= 7; ++j)
		for (int k = 0; k < 4 - all[64 + j]; ++k)
			ceshi[T++] = 64 + j;
	useful_table_t test;
	tile_table_t tmp, alltmp;
	intptr_t N = temp.pack_count;
	memcpy(tmp, hand, sizeof(tmp));
	memcpy(alltmp, all, sizeof(tmp));
	int max = 0;
	temp.tile_count = 0;
	for (intptr_t j = 17; j < 72; ++j)
		if (hand[j])
			for (int k = 0; k < hand[j]; ++k)
				temp.standing_tiles[temp.tile_count++] = j;
	if (max = if_wait(temp, all, test))
		max = max * 1000;
	else
	{
		for (int i = 0; i < TIMES; ++i)
		{
			iflis = 0;
			random_shuffle(ceshi, ceshi + T);
			max -= simulate(ceshi, T);
			temp.pack_count = N;
			memcpy(hand, tmp, sizeof(tmp));
			memcpy(all, alltmp, sizeof(alltmp));
		}
		max /= TIMES;
	}
	
	int da = 0;
	if (hand[pai] >= 2)
	{
		hand[pai] -= 2;
		temp.fixed_packs[temp.pack_count++] = make_pack(player, PACK_TYPE_PUNG, pai);
		tile_t ret = decide();
		if (S > max)
			max = S, da = ret;
		if (da == 0)
		{
			temp.pack_count--;
			hand[pai] += 2;
			return 0;
		}
		S = max;
		--hand[da];
		return da;
	}
	if (hand[pai] == 3)
	{
		hand[pai] -= 3;
		temp.tile_count = 0;
		for (intptr_t j = 17; j < 72; ++j)
			if (hand[j])
				for (int k = 0; k < hand[j]; ++k)
					temp.standing_tiles[temp.tile_count++] = j;
		int res;
		temp.fixed_packs[temp.pack_count++] = make_pack(player, PACK_TYPE_KONG, pai);
		if (res = if_wait(temp, all, test))
		{
			if (res * 1000 > max)
			{
				max = res * 1000;
				memcpy(wait, test, sizeof(useful_table_t));
				da = 1;
			}
		}
		else
		{
			res = 0;
			temp.tile_count = 0;
			for (intptr_t j = 17; j < 72; ++j)
				if (hand[j])
					for (int k = 0; k < hand[j]; ++k)
						temp.standing_tiles[temp.tile_count++] = j;
			if (res = if_wait(temp, all, test))
				if (res > max)
					res = res * 1000, da = 1;
				else
				{
					for (int i = 0; i < TIMES; ++i)
					{
						iflis = 0;
						random_shuffle(ceshi, ceshi + T);
						res -= simulate(ceshi, T);
						temp.pack_count = N;
						memcpy(hand, tmp, sizeof(tmp));
						memcpy(all, alltmp, sizeof(alltmp));
					}
					res /= TIMES;
					if (res > max)
						da = 1;
				}
		}
		if (!da)
		{
			--temp.pack_count;
			hand[pai] += 3;
			return 0;
		}
		return 100;
	}
	return 0;
}

bool testhu(tile_t pai)
{
	useful_table_t test;
	temp.tile_count = 0;
	for (intptr_t j = 17; j < 72; ++j)
		if (hand[j])
			for (int k = 0; k < hand[j]; ++k)
				temp.standing_tiles[temp.tile_count++] = j;
	if_wait(temp, all, test);
	if (test[pai])
		return true;
	return false;
}


int main(int argc, const char *argv[]) 
{
	init(all);
	for (int i = 0; i < 13; ++i)
		++hand[paichi[i]], ++all[paichi[i]];
	int c = 13;
	int ting = 13, enterting = 1;
	temp.pack_count = 0;
	while (true && c < 34 * 4)
	{
		show(hand);
		printf("\nget : %x\n", (int)paichi[c]);
		system("pause");
		//根据来牌判断是否胡牌
		if (testhu(paichi[c]))
		{
			printf("After %d :ting\n", ting);
			printf("After %d :hule\n", c);
			system("pause");
			return 0;
		}
		//更新手牌
		++hand[paichi[c]]; ++all[paichi[c++]];

		if (enterting)
			++ting;

		tile_t best = decide();
		if (S > 0)
			enterting = 0;
		printf("\n discard: %x\n", (int)best);
		--hand[best];
		if (testhu(paichi[c]))
		{
			printf("After %d :ting\n", ting);
			printf("After %d :hule\n", c);
			system("pause");
			return 0;
		}
		if (enterting)
			++ting;
		++all[paichi[c]];
		if (pengsti(paichi[c++], 3) == 100)
		{
			++hand[paichi[c]]; ++all[paichi[c++]];
			tile_t best = decide();
			printf("\n discard: %x\n", (int)best);
			--hand[best];
		}
		if (S > 0)
			enterting = 0;
		if (testhu(paichi[c]))
		{
			printf("After %d :ting\n", ting);
			printf("After %d :hule\n", c);
			system("pause");
			return 0;
		}
		if (enterting)
			++ting;
		++all[paichi[c]];
		if (pengsti(paichi[c++], 2) == 100)
		{
			++hand[paichi[c]]; ++all[paichi[c++]];
			tile_t best = decide();
			printf("\n discard: %x\n", (int)best);
			--hand[best];
		}
		if (S > 0)
			enterting = 0;
		if (testhu(paichi[c]))
		{
			printf("After %d :ting\n", ting);
			printf("After %d :hule\n", c);
			system("pause");
			return 0;
		}
		if (enterting)
			++ting;
		++all[paichi[c]];
		if (chisti(paichi[c]) == 0)
			if (peng(paichi[c++], 1) == 100)
			{
				++hand[paichi[c]]; ++all[paichi[c++]];
				tile_t best = decide();
				printf("\n discard: %x\n", (int)best);
				--hand[best];
			}
		if (S > 0)
			enterting = 0;
	}
    return 0;
}

#include "stringify.cpp"
#include "shanten.cpp"
#include "fan_calculator.cpp"
