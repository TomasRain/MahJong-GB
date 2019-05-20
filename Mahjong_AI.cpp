#pragma warning(disable:4996)
#define D_SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
/*
#include "tile.h"
#include "shanten.h"
#include "stringify.h"
#include "fan_calculator.h"
#include "MahjongGB/MahjongGB.h"*/
#include <fstream>
#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <limits>
#include <assert.h>
#include <sstream>
#include <cstdlib>
#include "jsoncpp/json.h"
//#define NOMINMAX
//#include <windows.h>


typedef unsigned long DWORD;
void MahjongInit();

//tiles.h


#include <stddef.h>
#include <stdint.h>
#ifdef _MSC_VER  // for MSVC
#define forceinline __forceinline
#elif defined __GNUC__  // for gcc on Linux/Apple OS X
#define forceinline __inline__ __attribute__((always_inline))
#else
#define forceinline inline
#endif
namespace mahjong {

	/**
	* @brief ����ע�����õ���������
	* - ˳�ӣ������У���ɫ��ͬ����������3���ơ�
	* - ���ӣ�������ͬ���ơ�������Ϊ���̣�δ������Ϊ���̡��׳ƿ�����Ҳ����ӣ����������̣������㰵�̡�
	* - ���ӣ�˳�ӺͿ��ӵ�ͳ�ơ��׳�һ�仰��һ���ơ�
	* - ȸͷ������������ʽ�У�������ϵĶ��ӣ�Ҳ�н����ۡ�
	* - �������ͣ�4����1ȸͷ�ĺ�����ʽ��
	* - ������ͣ���4����1ȸͷ�ĺ�����ʽ���ڹ�������У����߶ԡ�ʮ���ۡ�ȫ������������͡�
	* - ���壺Ҳ����ǰ�壬ָ���ԡ������������ܵ�״̬��������ͱ�Ȼ������״̬��������Ȼ�������壬���ᱩ¶�����Ʋ���������͵���Ϣ��
	* - ��¶�����ơ����ơ����Ƶ�ͳ�ƣ�����������ѡ�ִ����������Լ��������ӵ���Ϊ��һ�㲻�������ܣ�Ҳ�����ƣ��׳ƶ��ơ�
	*     ��¶��ʱ��Ҳ�������ܣ���ʱ�����ܳ�Ϊ֮����¶�����ԡ��������ܳ�Ϊ����¶��
	* - ���ƣ��������Ƴ�ȥ�ԡ�������֮����ơ�
	* - ���ƣ��������ƺͳԡ������ܵ��ƣ���ʱ��ָ���ơ�
	* - ���ƣ�ֻ������Ҫ��һ���Ƽ��ܺ��Ƶ�״̬���׳��½С���С��кͣ�������
	* - һ������ָ��һ�ž������Ƶ�״̬��Ҳ��һ������һ�������Դ������ж���������������N������
	* - ���������ﵽ����״̬��Ҫ�Ƶ�������
	* - ��Ч�ƣ���ʹ���������ٵ��ƣ�Ҳ�ƽ����ơ������ơ�
	* - �����ƣ���ʹ��Ч�����ӵ��ơ�ͨ����˵������ʹ����������ơ�
	* - ���ӣ�������ͬ���ơ�ȸͷһ���Ƕ��ӣ������Ӳ�һ����ȸͷ��
	* - ���棺�����У���ɫ��ͬ�������ڵ������ƣ���45m����������ƶ�����˳�ӡ�Ҳ����ͷ��
	* - Ƕ�ţ������У���ɫ��ͬ�������1�������ƣ���57s��ֻ�����м���ƹ���˳�ӣ��м�������Ƴ�ΪǶ�š�
	* - ���ţ�Ҳ���������ڵ������ƣ������ڴ��ڱ߽�λ�ã�ֻ����һ������ܹ���˳�ӣ���12ֻ����3����˳�ӡ�89ֻ����7����˳�ӣ�����3����7���Ϊ���š�
	* - ���ӣ�ָ��һ���ƾ��ܹ���1�����ӵ������ơ�����̬�п��Ӵ��ӣ������ӣ���������ӡ�Ƕ�Ŵ��ӡ����Ŵ��ӡ�
	* - ���ϴ��ӣ������ƹ��ɵĴ��ӡ��������У���Ƕ�š���������ӡ�Ƕ�Ŵ����ӡ����Ŵ����ӵȵ���̬��
	* - �Ե�������ʱ�������ƶ��Ѿ��������ӣ�ʣ�����ԣ�ֻ������һ�Գɿ̼��ɺ��ƣ���ʱ��һ�Գ䵱ȸͷ������������̬�жԵ���Ҳ��˫�������������ơ�
	*/


	/**
	* @addtogroup tile
	* @{
	*/

	/**
	* @brief ��ɫ
	*/
	typedef uint8_t suit_t;

	/**
	* @brief ����
	*/
	typedef uint8_t rank_t;

#define TILE_SUIT_NONE          0  ///< ��Ч
#define TILE_SUIT_CHARACTERS    1  ///< ���ӣ�CHARACTERS��
#define TILE_SUIT_BAMBOO        2  ///< ���ӣ�BAMBOO��
#define TILE_SUIT_DOTS          3  ///< ���ӣ�DOTS��
#define TILE_SUIT_HONORS        4  ///< ���ƣ�HONORS��

	/**
	* @brief ��\n
	* �ڴ�ṹ��
	* - 0-3 4bit �Ƶĵ���
	* - 4-7 4bit �ƵĻ�ɫ
	* �Ϸ�����Ϊ��
	* - 0x11 - 0x19 ���ӣ�CHARACTERS��
	* - 0x21 - 0x29 ���ӣ�BAMBOO��
	* - 0x31 - 0x39 ���ӣ�DOTS��
	* - 0x41 - 0x47 ���ƣ�HONORS��
	*/
	typedef uint8_t tile_t;

	/**
	* @brief ����һ����
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] suit ��ɫ
	* @param [in] rank ����
	* @return tile_t ��
	*/
	static forceinline tile_t make_tile(suit_t suit, rank_t rank) {
		return (((suit & 0xF) << 4) | (rank & 0xF));
	}

	/**
	* @brief ��ȡ�ƵĻ�ɫ
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] tile ��
	* @return suit_t ��ɫ
	*/
	static forceinline suit_t tile_get_suit(tile_t tile) {
		return ((tile >> 4) & 0xF);
	}

	/**
	* @brief ��ȡ�Ƶĵ���
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] tile ��
	* @return rank_t ����
	*/
	static forceinline rank_t tile_get_rank(tile_t tile) {
		return (tile & 0xF);
	}

	/**
	* @brief �����Ƶ�ֵ
	*/
	enum tile_value_t {
		TILE_1m = 0x11, TILE_2m, TILE_3m, TILE_4m, TILE_5m, TILE_6m, TILE_7m, TILE_8m, TILE_9m,
		TILE_1s = 0x21, TILE_2s, TILE_3s, TILE_4s, TILE_5s, TILE_6s, TILE_7s, TILE_8s, TILE_9s,
		TILE_1p = 0x31, TILE_2p, TILE_3p, TILE_4p, TILE_5p, TILE_6p, TILE_7p, TILE_8p, TILE_9p,
		TILE_E = 0x41, TILE_S, TILE_W, TILE_N, TILE_C, TILE_F, TILE_P,
		TILE_TABLE_SIZE
	};

	/**
	* @brief ���кϷ�����
	*/
	static const tile_t all_tiles[] = {
		TILE_1m, TILE_2m, TILE_3m, TILE_4m, TILE_5m, TILE_6m, TILE_7m, TILE_8m, TILE_9m,
		TILE_1s, TILE_2s, TILE_3s, TILE_4s, TILE_5s, TILE_6s, TILE_7s, TILE_8s, TILE_9s,
		TILE_1p, TILE_2p, TILE_3p, TILE_4p, TILE_5p, TILE_6p, TILE_7p, TILE_8p, TILE_9p,
		TILE_E , TILE_S , TILE_W , TILE_N , TILE_C , TILE_F , TILE_P
	};

	/**
	* @brief �Ʊ�����
	*
	* ˵�������ж����ơ��������������㷨�У������Ķ����������ִ洢��ʽ��
	* - һ�������Ʊ���������ʾ������ӵ�е�ö�������ִ洢��ʽ���ŵ����ڵݹ����ʱ��������ֻ��Ҫ�޸ı�����Ӧ�±��ֵ��ȱ����һ���Ƶ�����������ȷ��
	* - ��һ����ֱ�����Ƶ����飬���ִ洢��ʽ���ŵ��Ǻ�����ȷ��һ���Ƶ�������ȱ�����ڵݹ����ʱ�������Ӳ����㣬��Ҫ��������ɾ��Ԫ�ز���
	*/
	typedef uint16_t tile_table_t[TILE_TABLE_SIZE];

#define PACK_TYPE_NONE 0  ///< ��Ч
#define PACK_TYPE_CHOW 1  ///< ˳��
#define PACK_TYPE_PUNG 2  ///< ����
#define PACK_TYPE_KONG 3  ///< ��
#define PACK_TYPE_PAIR 4  ///< ȸͷ

	/**
	* @brief ����
	*  ���ڱ�ʾһ�����ӻ���ȸͷ
	*
	* �ڴ�ṹ��
	* - 0-7 8bit tile �ƣ�����˳�ӣ����ʾ�м������ƣ�����234p����ô��Ϊ3p��
	* - 8-11 4bit type �������ͣ�ʹ��PACK_TYPE_xxx��
	* - 12-15 4bit offer ������Ϣ��ȡֵ��ΧΪ0123\n
	*       0��ʾ���֣���˳�����̡����ܣ�����0��ʾ���֣���˳�����̡����ܣ�
	*
	*       ���������ǿ��Ӻ͸�ʱ��123�ֱ�����ʾ���ϼ�/�Լ�/�¼ҹ���\n
	*       ��������Ϊ˳��ʱ�����ڳ���ֻ�����ϼҹ���������123�ֱ�����ʾ�ڼ������ϼҹ���
	*/
	typedef uint16_t pack_t;

	/**
	* @brief ����һ������
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] offer ������Ϣ
	* @param [in] type ��������
	* @param [in] tile �ƣ�����˳�ӣ�Ϊ�м������ƣ�
	*/
	static forceinline pack_t make_pack(uint8_t offer, uint8_t type, tile_t tile) {
		return (offer << 12 | (type << 8) | tile);
	}

	/**
	* @brief �����Ƿ�Ϊ����
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] pack ����
	* @return bool
	*/
	static forceinline bool is_pack_melded(pack_t pack) {
		return !!((pack >> 12) & 0xF);
	}

	/**
	* @brief ����Ĺ�����Ϣ
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] pack ����
	* @return uint8_t
	*/
	static forceinline uint8_t pack_get_offer(pack_t pack) {
		return ((pack >> 12) & 0xF);
	}

	/**
	* @brief ��ȡ���������
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] pack ����
	* @return uint8_t ��������
	*/
	static forceinline uint8_t pack_get_type(pack_t pack) {
		return ((pack >> 8) & 0xF);
	}

	/**
	* @brief ��ȡ�Ƶĵ���
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] pack ����
	* @return tile_t �ƣ�����˳�ӣ�Ϊ�м������ƣ�
	*/
	static forceinline tile_t pack_get_tile(pack_t pack) {
		return (pack & 0xFF);
	}

	/**
	* @brief ���ƽṹ
	*  ���ƽṹһ�������ʽ��3*��¶��������+������=13
	*/
	struct hand_tiles_t {
		pack_t fixed_packs[5];      ///< ��¶�����飨���ӣ�����������
		intptr_t pack_count;        ///< ��¶�����飨���ӣ�������������
		tile_t standing_tiles[13];  ///< ����
		intptr_t tile_count;        ///< ������
	};


	/**
	* @brief �ж��Ƿ�Ϊ��һɫ������
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] tile ��
	* @return bool
	*/
	static forceinline bool is_green(tile_t tile) {
		// �����������жϣ�23468s������Ϊ��һɫ������
		//return (tile == TILE_2s || tile == TILE_3s || tile == TILE_4s || tile == TILE_6s || tile == TILE_8s || tile == TILE_F);

		// �㷨ԭ��
		// 0x48-0x11=0x37=55�պ���һ��64λ���͵ķ�Χ�ڣ�
		// ��uint64_t��ÿһλ��ʾһ���Ƶı�ǣ����ȵõ�һ��ħ����
		// Ȼ��ÿ�β�����Ӧλ����
		return !!(0x0020000000AE0000ULL & (1ULL << (tile - TILE_1m)));
	}

	/**
	* @brief �ж��Ƿ�Ϊ�Ʋ���������
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] tile ��
	* @return bool
	*/
	static forceinline bool is_reversible(tile_t tile) {
		// �����������жϣ�245689s��1234589p���װ�Ϊ�Ʋ���������
		//return (tile == TILE_2s || tile == TILE_4s || tile == TILE_5s || tile == TILE_6s || tile == TILE_8s || tile == TILE_9s ||
		//    tile == TILE_1p || tile == TILE_2p || tile == TILE_3p || tile == TILE_4p || tile == TILE_5p || tile == TILE_8p || tile == TILE_9p ||
		//    tile == TILE_P);

		// �㷨ԭ��ͬ��һɫ�������жϺ���
		return !!(0x0040019F01BA0000ULL & (1ULL << (tile - TILE_1m)));
	}

	/**
	* @brief �ж��Ƿ�Ϊ�����۾ţ���ͷ�ƣ�
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] tile ��
	* @return bool
	*/
	static forceinline bool is_terminal(tile_t tile) {
		// �����������ж�
		//return (tile == TILE_1m || tile == TILE_9m || tile == TILE_1s || tile == TILE_9s || tile == TILE_1p || tile == TILE_9p);

		// �㷨ԭ���۲������۾ŵĶ�����λ��
		// 0x11��0001 0001
		// 0x19��0001 1001
		// 0x21��0010 0001
		// 0x29��0010 1001
		// 0x31��0011 0001
		// 0x39��0011 1001
		// �����Ƶĵ�4bitֻ�������0001��1001֮�䣬��0111λ�룬ֻ��0001��1001�Ľ��Ϊ1
		// �������Ƶĸ�4bitֻ�������0001��0011֮�䣬��1100λ�룬��ȻΪ0
		// ���ǹ���ħ��0xC7��1100 0111������λ�룬���Ϊ1�ģ���Ϊ�����۾�
		// ȱ�ݣ���4bit�Ĳ������0xB��0xD��0xF�������У���4bit�Ĳ������0x01��0x09��������
		return ((tile & 0xC7) == 1);
	}

	/**
	* @brief �ж��Ƿ�Ϊ����
	* @param [in] tile ��
	* @return bool
	*/
	static forceinline bool is_winds(tile_t tile) {
		return (tile > 0x40 && tile < 0x45);
	}

	/**
	* @brief �ж��Ƿ�Ϊ���ƣ���Ԫ�ƣ�
	* @param [in] tile ��
	* @return bool
	*/
	static forceinline bool is_dragons(tile_t tile) {
		return (tile > 0x44 && tile < 0x48);
	}

	/**
	* @brief �ж��Ƿ�Ϊ����
	* @param [in] tile ��
	* @return bool
	*/
	static forceinline bool is_honor(tile_t tile) {
		return (tile > 0x40 && tile < 0x48);
	}

	/**
	* @brief �ж��Ƿ�Ϊ����
	* @param [in] tile ��
	* @return bool
	*/
	static forceinline bool is_numbered_suit(tile_t tile) {
		if (tile < 0x1A) return (tile > 0x10);
		if (tile < 0x2A) return (tile > 0x20);
		if (tile < 0x3A) return (tile > 0x30);
		return false;
	}

	/**
	* @brief �ж��Ƿ�Ϊ���ƣ����죩
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @see is_numbered_suit
	* @param [in] tile ��
	* @return bool
	*/
	static forceinline bool is_numbered_suit_quick(tile_t tile) {
		// �㷨ԭ������Ϊ0x11-0x19��0x21-0x29��0x31-0x39����0xC0λ�룬���Ϊ0
		return !(tile & 0xC0);
	}

	/**
	* @brief �ж��Ƿ�Ϊ�۾��ƣ����������۾ź����ƣ�
	* @param [in] tile ��
	* @return bool
	*/
	static forceinline bool is_terminal_or_honor(tile_t tile) {
		return is_terminal(tile) || is_honor(tile);
	}

	/**
	* @brief �ж������ƻ�ɫ�Ƿ���ͬ�����죩
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] tile0 ��0
	* @param [in] tile1 ��1
	* @return bool
	*/
	static forceinline bool is_suit_equal_quick(tile_t tile0, tile_t tile1) {
		// �㷨ԭ����4bit��ʾ��ɫ
		return ((tile0 & 0xF0) == (tile1 & 0xF0));
	}

	/**
	* @brief �ж������Ƶ����Ƿ���ͬ�����죩
	*  �������������ĺϷ��ԡ�������벻�Ϸ���ֵ�����޷���֤�Ϸ�����ֵ�ĺϷ���
	* @param [in] tile0 ��0
	* @param [in] tile1 ��1
	* @return bool
	*/
	static forceinline bool is_rank_equal_quick(tile_t tile0, tile_t tile1) {
		// �㷨ԭ����4bit��ʾ��ɫ����4bit����ΪC��Ϊ�˹��˵�����
		return ((tile0 & 0xCF) == (tile1 & 0xCF));
	}

	/**
	* end group
	* @}
	*/



	/**
	* @brief �ַ�����ʽ��
	* - ���ƣ���=m ��=s ��=p����׺ʹ��Сд��ĸ��һ����ͬ��ɫ�����ƿɺϲ�ʹ����һ����׺����123m��678s�ȵȡ�
	* - ���ƣ���������=ESWN���з���=CFP��ʹ�ô�д��ĸ������������ĺ�׺z�������й�ϰ��˳��567zΪ�з��ס�
	* - �ԡ���������Ӣ��[]����ѡ�ö���+���ֱ�ʾ������Դ�����ֵľ���������£�
	*    - �ԣ���ʾ�ڼ����������ϼҴ������[567m,2]��ʾ57���6�򣨵�2�ţ������ڲ�ָ�����ֵģ�Ĭ��Ϊ�Ե�1�š�
	*    - ������ʾ���ļҴ����1Ϊ�ϼң�2Ϊ�Լң�3Ϊ�¼ң���[999s,3]��ʾ���¼ҵ�9�������ڲ�ָ�����ֵģ�Ĭ��Ϊ���ϼҡ�
	*    - �ܣ��������ƣ������ڲ�ָ�����ֵģ�����Ϊ�ǰ��ܡ����磺[SSSS]��ʾ�����ϣ�[8888p,1]��ʾ�����ϼҵ�8����
	* - ����
	*    - [EEEE][CCCC][FFFF][PPPP]NN
	*    - 1112345678999s9s
	*    - [WWWW,1][444s]45m678pFF6m
	*    - [EEEE]288s349pSCFF2p
	*    - [123p,1][345s,2][999s,3]6m6pEW1m
	*    - 356m18s1579pWNFF9p
	*/

	/**
	* @addtogroup stringify
	* @{
	*/

	/**
	* @name error codes
	* @{
	*  �����ƵĴ�����
	*/
#define PARSE_NO_ERROR 0                                ///< �޴���
#define PARSE_ERROR_ILLEGAL_CHARACTER -1                ///< �Ƿ��ַ�
#define PARSE_ERROR_NO_SUFFIX_AFTER_DIGIT -2            ///< ���ֺ���ȱ�ٺ�׺
#define PARSE_ERROR_WRONG_TILES_COUNT_FOR_FIXED_PACK -3 ///< ��¶�������������Ŀ
#define PARSE_ERROR_CANNOT_MAKE_FIXED_PACK -4           ///< �޷���ȷ������¶
#define PARSE_ERROR_TOO_MANY_FIXED_PACKS -5             ///< �����鸱¶��һ���Ϸ��������4��¶��
	/**
	* @}
	*/

	/**
	* @brief ������
	* @param [in] str �ַ���
	* @param [out] tiles ��
	* @param [in] max_cnt �Ƶ��������
	* @retval > 0 ʵ���Ƶ�����
	* @retval == 0 ʧ��
	*/
	intptr_t parse_tiles(const char *str, tile_t *tiles, intptr_t max_cnt);

	/**
	* @brief �ַ���ת��Ϊ���ƽṹ������
	* @param [in] str �ַ���
	* @param [out] hand_tiles ���ƽṹ
	* @param [out] serving_tile �ϵ���
	* @retval PARSE_NO_ERROR �޴���
	* @retval PARSE_ERROR_ILLEGAL_CHARACTER �Ƿ��ַ�
	* @retval PARSE_ERROR_NO_SUFFIX_AFTER_DIGIT ���ֺ���ȱ�ٺ�׺
	* @retval PARSE_ERROR_WRONG_TILES_COUNT_FOR_FIXED_PACK ��¶�������������Ŀ
	* @retval PARSE_ERROR_CANNOT_MAKE_FIXED_PACK �޷���ȷ������¶
	* @retval PARSE_ERROR_TOO_MANY_FIXED_PACKS �����鸱¶��һ���Ϸ��������4��¶��
	*/
	intptr_t string_to_tiles(const char *str, hand_tiles_t *hand_tiles, tile_t *serving_tile);

	/**
	* @brief ��ת��Ϊ�ַ���
	* @param [in] tiles ��
	* @param [in] tile_cnt �Ƶ�����
	* @param [out] str �ַ���
	* @param [in] max_size �ַ�����󳤶�
	* @return intptr_t д����ַ�����
	*/
	intptr_t tiles_to_string(const tile_t *tiles, intptr_t tile_cnt, char *str, intptr_t max_size);

	/**
	* @brief ����ת��Ϊ�ַ���
	* @param [in] packs ����
	* @param [in] pack_cnt ���������
	* @param [out] str �ַ���
	* @param [in] max_size �ַ�����󳤶�
	* @return intptr_t д����ַ�����
	*/
	intptr_t packs_to_string(const pack_t *packs, intptr_t pack_cnt, char *str, intptr_t max_size);

	/**
	* @brief ���ƽṹת��Ϊ�ַ���
	* @param [in] hand_tiles ���ƽṹ
	* @param [out] str �ַ���
	* @param [in] max_size �ַ�����󳤶�
	* @return intptr_t д����ַ�����
	*/
	intptr_t hand_tiles_to_string(const hand_tiles_t *hand_tiles, char *str, intptr_t max_size);

	/**
	* end group
	* @}
	*/



	//fan_calculator.h
#ifndef __MAHJONG_ALGORITHM__FAN_CALCULATOR_H__
#define __MAHJONG_ALGORITHM__FAN_CALCULATOR_H__
#define SUPPORT_CONCEALED_KONG_AND_MELDED_KONG 1  // ֧��������

	/**
	* @addtogroup calculator
	* @{
	*/

	/**
	* @brief ����
	*/
	enum fan_t {
		FAN_NONE = 0,                       ///< ��Ч
		BIG_FOUR_WINDS,                     ///< ����ϲ
		BIG_THREE_DRAGONS,                  ///< ����Ԫ
		ALL_GREEN,                          ///< ��һɫ
		NINE_GATES,                         ///< ��������
		FOUR_KONGS,                         ///< �ĸ�
		SEVEN_SHIFTED_PAIRS,                ///< ���߶�
		THIRTEEN_ORPHANS,                   ///< ʮ����

		ALL_TERMINALS,                      ///< ���۾�
		LITTLE_FOUR_WINDS,                  ///< С��ϲ
		LITTLE_THREE_DRAGONS,               ///< С��Ԫ
		ALL_HONORS,                         ///< ��һɫ
		FOUR_CONCEALED_PUNGS,               ///< �İ���
		PURE_TERMINAL_CHOWS,                ///< һɫ˫����

		QUADRUPLE_CHOW,                     ///< һɫ��ͬ˳
		FOUR_PURE_SHIFTED_PUNGS,            ///< һɫ�Ľڸ�

		FOUR_PURE_SHIFTED_CHOWS,            ///< һɫ�Ĳ���
		THREE_KONGS,                        ///< ����
		ALL_TERMINALS_AND_HONORS,           ///< ���۾�

		SEVEN_PAIRS,                        ///< �߶�
		GREATER_HONORS_AND_KNITTED_TILES,   ///< ���ǲ���
		ALL_EVEN_PUNGS,                     ///< ȫ˫��
		FULL_FLUSH,                         ///< ��һɫ
		PURE_TRIPLE_CHOW,                   ///< һɫ��ͬ˳
		PURE_SHIFTED_PUNGS,                 ///< һɫ���ڸ�
		UPPER_TILES,                        ///< ȫ��
		MIDDLE_TILES,                       ///< ȫ��
		LOWER_TILES,                        ///< ȫС

		PURE_STRAIGHT,                      ///< ����
		THREE_SUITED_TERMINAL_CHOWS,        ///< ��ɫ˫����
		PURE_SHIFTED_CHOWS,                 ///< һɫ������
		ALL_FIVE,                           ///< ȫ����
		TRIPLE_PUNG,                        ///< ��ͬ��
		THREE_CONCEALED_PUNGS,              ///< ������

		LESSER_HONORS_AND_KNITTED_TILES,    ///< ȫ����
		KNITTED_STRAIGHT,                   ///< �����
		UPPER_FOUR,                         ///< ������
		LOWER_FOUR,                         ///< С����
		BIG_THREE_WINDS,                    ///< �����

		MIXED_STRAIGHT,                     ///< ����
		REVERSIBLE_TILES,                   ///< �Ʋ���
		MIXED_TRIPLE_CHOW,                  ///< ��ɫ��ͬ˳
		MIXED_SHIFTED_PUNGS,                ///< ��ɫ���ڸ�
		CHICKEN_HAND,                       ///< �޷���
		LAST_TILE_DRAW,                     ///< ���ֻش�
		LAST_TILE_CLAIM,                    ///< ��������
		OUT_WITH_REPLACEMENT_TILE,          ///< ���Ͽ���
		ROBBING_THE_KONG,                   ///< ���ܺ�

		ALL_PUNGS,                          ///< ������
		HALF_FLUSH,                         ///< ��һɫ
		MIXED_SHIFTED_CHOWS,                ///< ��ɫ������
		ALL_TYPES,                          ///< ������
		MELDED_HAND,                        ///< ȫ����
		TWO_CONCEALED_KONGS,                ///< ˫����
		TWO_DRAGONS_PUNGS,                  ///< ˫����

		OUTSIDE_HAND,                       ///< ȫ����
		FULLY_CONCEALED_HAND,               ///< ������
		TWO_MELDED_KONGS,                   ///< ˫����
		LAST_TILE,                          ///< ������

		DRAGON_PUNG,                        ///< ����
		PREVALENT_WIND,                     ///< Ȧ���
		SEAT_WIND,                          ///< �ŷ��
		CONCEALED_HAND,                     ///< ��ǰ��
		ALL_CHOWS,                          ///< ƽ��
		TILE_HOG,                           ///< �Ĺ�һ
		DOUBLE_PUNG,                        ///< ˫ͬ��
		TWO_CONCEALED_PUNGS,                ///< ˫����
		CONCEALED_KONG,                     ///< ����
		ALL_SIMPLES,                        ///< ����

		PURE_DOUBLE_CHOW,                   ///< һ���
		MIXED_DOUBLE_CHOW,                  ///< ϲ���
		SHORT_STRAIGHT,                     ///< ����
		TWO_TERMINAL_CHOWS,                 ///< ���ٸ�
		PUNG_OF_TERMINALS_OR_HONORS,        ///< �۾ſ�
		MELDED_KONG,                        ///< ����
		ONE_VOIDED_SUIT,                    ///< ȱһ��
		NO_HONORS,                          ///< ����
		EDGE_WAIT,                          ///< ����
		CLOSED_WAIT,                        ///< Ƕ��
		SINGLE_WAIT,                        ///< ������
		SELF_DRAWN,                         ///< ����

		FLOWER_TILES,                       ///< ����

#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
		CONCEALED_KONG_AND_MELDED_KONG,     ///< ������
#endif

		FAN_TABLE_SIZE
	};

	/**
	* @brief �磨������ʾȦ���ŷ磩
	*/
	enum class wind_t {
		EAST, SOUTH, WEST, NORTH
	};

	/**
	* @brief ���Ʊ��
	*/
	typedef uint8_t win_flag_t;

	/**
	* @name win flag
	* @{
	*/
#define WIN_FLAG_DISCARD    0   ///< ���
#define WIN_FLAG_SELF_DRAWN 1   ///< ����
#define WIN_FLAG_4TH_TILE   2   ///< ����
#define WIN_FLAG_ABOUT_KONG 4   ///< ���ڸܣ����ϵ��ʱΪǹ�ܺͣ�����������Ϊ���Ͽ���
#define WIN_FLAG_WALL_LAST  8   ///< ��ǽ���һ�ţ����ϵ��ʱΪ�������£�����������Ϊ���ֻش�
	/**
	* @}
	*/

	/**
	* @name error codes
	* @{
	*/
#define ERROR_WRONG_TILES_COUNT -1              ///< ���������
#define ERROR_TILE_COUNT_GREATER_THAN_4 -2      ///< ĳ���Ƴ��ֳ���4ö
#define ERROR_NOT_WIN -3                        ///< û����
	/**
	* @}
	*/

	/**
	* @brief ����㷬�������Ƿ�Ϸ�
	*
	* @param [in] hand_tiles ����
	* @param [in] win_tile ������
	* @retval 0 �ɹ�
	* @retval ERROR_WRONG_TILES_COUNT ���������
	* @retval ERROR_TILE_COUNT_GREATER_THAN_4 ĳ���Ƴ��ֳ���4ö
	*/
	int check_calculator_input(const hand_tiles_t *hand_tiles, tile_t win_tile);

	/**
	* @brief �㷬����
	*/
	struct calculate_param_t {
		hand_tiles_t hand_tiles;    ///< ����
		tile_t win_tile;            ///< ������
		uint8_t flower_count;       ///< ������
		win_flag_t win_flag;        ///< ���Ʊ��
		wind_t prevalent_wind;      ///< Ȧ��
		wind_t seat_wind;           ///< �ŷ�
	};

	/**
	* @brief ����
	*/
	typedef uint16_t fan_table_t[FAN_TABLE_SIZE];

	/**
	* @brief �㷬
	*
	* @param [in] calculate_param �㷬����
	* @param [out] fan_table ��������ĳ�ַ�ʱ����Ӧ�Ļ�����Ϊ���ַ����ֵĴ���
	* @retval >0 ����
	* @retval ERROR_WRONG_TILES_COUNT ���������
	* @retval ERROR_TILE_COUNT_GREATER_THAN_4 ĳ���Ƴ��ֳ���4ö
	* @retval ERROR_NOT_WIN û����
	*/
	int calculate_fan(const calculate_param_t *calculate_param, fan_table_t *fan_table);

#if 0

	/**
	* @brief ������Ӣ�ģ�
	*/
	static const char *fan_name[] = {
		"None",
		"Big Four Winds", "Big Three Dragons", "All Green", "Nine Gates", "Four Kongs", "Seven Shifted Pairs", "Thirteen Orphans",
		"All Terminals", "Little Four Winds", "Little Three Dragons", "All Honors", "Four Concealed Pungs", "Pure Terminal Chows",
		"Quadruple Chow", "Four Pure Shifted Pungs",
		"Four Pure Shifted Chows", "Three Kongs", "All Terminals and Honors",
		"Seven Pairs", "Greater Honors and Knitted Tiles", "All Even Pungs", "Full Flush", "Pure Triple Chow", "Pure Shifted Pungs", "Upper Tiles", "MiddleGame Tiles", "Lower Tiles",
		"Pure Straight", "Three-Suited Terminal Chows", "Pure Shifted Chows", "All Five", "Triple Pung", "Three Concealed Pungs",
		"Lesser Honors and Knitted Tiles", "Knitted Straight", "Upper Four", "Lower Four", "Big Three Winds",
		"Mixed Straight", "Reversible Tiles", "Mixed Triple Chow", "Mixed Shifted Pungs", "Chicken Hand", "Last Tile Draw", "Last Tile Claim", "Out with Replacement Tile", "Robbing The Kong",
		"All Pungs", "Half Flush", "Mixed Shifted Chows", "All Types", "Melded Hand", "Two Concealed Kongs", "Two Dragons Pungs",
		"Outside Hand", "Fully Concealed Hand", "Two Melded Kongs", "Last Tile",
		"Dragon Pung", "Prevalent Wind", "Seat Wind", "Concealed Hand", "All Chows", "Tile Hog", "Double Pung",
		"Two Concealed Pungs", "Concealed Kong", "All Simples",
		"Pure Double Chow", "Mixed Double Chow", "Short Straight", "Two Terminal Chows", "Pung of Terminals or Honors", "Melded Kong", "One Voided Suit", "No Honors", "Edge Wait", "Closed Wait", "Single Wait", "Self-Drawn",
		"Flower Tiles"
#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
		, "Concealed Kong and Melded Kong"
#endif
	};

#else

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#ifndef __UTF8_TEXT
	// VS2015 GCC4.7 Clang5.0
#if (defined(_MSC_VER) && (_MSC_VER >= 1900)) || (defined(__GNUC__) && ((__GNUC__ << 8 | __GNUC_MINOR__) >= 0x407)) || (defined(__clang__) && (__clang_major__ >= 5))
#define __UTF8_TEXT(quote) u8 ## quote
#else
#define __UTF8_TEXT(quote) quote
#endif
#endif

#ifndef __UTF8
#define __UTF8(quote) __UTF8_TEXT(quote)
#endif

	/**
	* @brief �������������ģ�
	*/
	static const char *fan_name[] = {
		__UTF8("��"),
		__UTF8("����ϲ"), __UTF8("����Ԫ"), __UTF8("��һɫ"), __UTF8("��������"), __UTF8("�ĸ�"), __UTF8("���߶�"), __UTF8("ʮ����"),
		__UTF8("���۾�"), __UTF8("С��ϲ"), __UTF8("С��Ԫ"), __UTF8("��һɫ"), __UTF8("�İ���"), __UTF8("һɫ˫����"),
		__UTF8("һɫ��ͬ˳"), __UTF8("һɫ�Ľڸ�"),
		__UTF8("һɫ�Ĳ���"), __UTF8("����"), __UTF8("���۾�"),
		__UTF8("�߶�"), __UTF8("���ǲ���"), __UTF8("ȫ˫��"), __UTF8("��һɫ"), __UTF8("һɫ��ͬ˳"), __UTF8("һɫ���ڸ�"), __UTF8("ȫ��"), __UTF8("ȫ��"), __UTF8("ȫС"),
		__UTF8("����"), __UTF8("��ɫ˫����"), __UTF8("һɫ������"), __UTF8("ȫ����"), __UTF8("��ͬ��"), __UTF8("������"),
		__UTF8("ȫ����"), __UTF8("�����"), __UTF8("������"), __UTF8("С����"), __UTF8("�����"),
		__UTF8("����"), __UTF8("�Ʋ���"), __UTF8("��ɫ��ͬ˳"), __UTF8("��ɫ���ڸ�"), __UTF8("�޷���"), __UTF8("���ֻش�"), __UTF8("��������"), __UTF8("���Ͽ���"), __UTF8("���ܺ�"),
		__UTF8("������"), __UTF8("��һɫ"), __UTF8("��ɫ������"), __UTF8("������"), __UTF8("ȫ����"), __UTF8("˫����"), __UTF8("˫����"),
		__UTF8("ȫ����"), __UTF8("������"), __UTF8("˫����"), __UTF8("�;���"),
		__UTF8("����"), __UTF8("Ȧ���"), __UTF8("�ŷ��"), __UTF8("��ǰ��"), __UTF8("ƽ��"), __UTF8("�Ĺ�һ"), __UTF8("˫ͬ��"), __UTF8("˫����"), __UTF8("����"), __UTF8("����"),
		__UTF8("һ���"), __UTF8("ϲ���"), __UTF8("����"), __UTF8("���ٸ�"), __UTF8("�۾ſ�"), __UTF8("����"), __UTF8("ȱһ��"), __UTF8("����"), __UTF8("����"), __UTF8("Ƕ��"), __UTF8("������"), __UTF8("����"),
		__UTF8("����")
#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
		, __UTF8("������")
#endif
	};

#endif

	/**
	* @brief ��ֵ
	*/
	static const uint16_t fan_value_table[FAN_TABLE_SIZE] = {
		0,
		88, 88, 88, 88, 88, 88, 88,
		64, 64, 64, 64, 64, 64,
		48, 48,
		32, 32, 32,
		24, 24, 24, 24, 24, 24, 24, 24, 24,
		16, 16, 16, 16, 16, 16,
		12, 12, 12, 12, 12,
		8, 8, 8, 8, 8, 8, 8, 8, 8,
		6, 6, 6, 6, 6, 6, 6,
		4, 4, 4, 4,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1
#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
		, 5
#endif
	};

	/**
	* @brief �ж������Ƿ��������
	* ����ǣ����Ȼ���Ǻ;���
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [in] win_tile ������
	* @return bool
	*/
	bool is_standing_tiles_contains_win_tile(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t win_tile);

	/**
	* @brief ͳ�ƺ����ڸ�¶�����г��ֵ�����
	* �������3�ţ����Ȼ�;���
	*
	* @param [in] fixed_packs ��¶����
	* @param [in] fixed_cnt ��¶������
	* @param [in] win_tile ������
	* @return size_t
	*/
	size_t count_win_tile_in_fixed_packs(const pack_t *fixed_packs, intptr_t fixed_cnt, tile_t win_tile);

	/**
	* @brief �жϸ�¶�����Ƿ������
	*
	* @param [in] fixed_packs ��¶����
	* @param [in] fixed_cnt ��¶������
	* @return bool
	*/
	bool is_fixed_packs_contains_kong(const pack_t *fixed_packs, intptr_t fixed_cnt);

	/**
	* end group
	* @}
	*/


#endif

	//shanten.h



	/**
	* @brief ����ת������
	*
	* @param [in] packs ����
	* @param [in] pack_cnt ���������
	* @param [out] tiles ��
	* @param [in] tile_cnt �Ƶ��������
	* @return intptr_t �Ƶ�ʵ������
	*/
	intptr_t packs_to_tiles(const pack_t *packs, intptr_t pack_cnt, tile_t *tiles, intptr_t tile_cnt);

	/**
	* @brief ���ƴ��
	*
	* @param [in] tiles ��
	* @param [in] cnt �Ƶ�����
	* @param [out] cnt_table �Ƶ�������
	*/
	void map_tiles(const tile_t *tiles, intptr_t cnt, tile_table_t *cnt_table);

	/**
	* @brief �����ƴ��
	*
	* @param [in] hand_tiles ����
	* @param [out] cnt_table �Ƶ�������
	* @return bool ���ƽṹ�Ƿ���ȷ�����Ƿ���ϣ���¶����*3+������=13
	*/
	bool map_hand_tiles(const hand_tiles_t *hand_tiles, tile_table_t *cnt_table);

	/**
	* @brief ����ת������
	*
	* @param [in] cnt_table �Ƶ�������
	* @param [out] tiles ��
	* @param [in] max_cnt �Ƶ��������
	* @return intptr_t �Ƶ�ʵ������
	*/
	intptr_t table_to_tiles(const tile_table_t &cnt_table, tile_t *tiles, intptr_t max_cnt);

	/**
	* @brief ��Ч�Ʊ�Ǳ�����
	*/
	typedef bool useful_table_t[TILE_TABLE_SIZE];

	/**
	* @brief ������Ч��ö��
	*
	* @param [in] used_table �Ѿ���ʹ���Ƶ�������
	* @param [in] useful_table ��Ч�Ʊ�Ǳ�
	* @return int ��Ч��ö��
	*/
	int count_useful_tile(const tile_table_t &used_table, const useful_table_t &useful_table);

	/**
	* @addtogroup shanten
	* @{
	*/

	/**
	* @addtogroup basic_form
	* @{
	*/

	/**
	* @brief ��������������
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] useful_table ��Ч�Ʊ�Ǳ���Ϊnull��
	* @return int ������
	*/
	int basic_form_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

	/**
	* @brief ���������Ƿ�����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] waiting_table ���Ʊ�Ǳ���Ϊnull��
	* @return bool �Ƿ�����
	*/
	bool is_basic_form_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

	/**
	* @brief ���������Ƿ����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [in] test_tile ���Ե���
	* @return bool �Ƿ����
	*/
	bool is_basic_form_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

	/**
	* end group
	* @}
	*/

	/**
	* @addtogroup seven_pairs
	* @{
	*/

	/**
	* @brief �߶�������
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] useful_table ��Ч�Ʊ�Ǳ���Ϊnull��
	* @return int ������
	*/
	int seven_pairs_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

	/**
	* @brief �߶��Ƿ�����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] waiting_table ���Ʊ�Ǳ���Ϊnull��
	* @return bool �Ƿ�����
	*/
	bool is_seven_pairs_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

	/**
	* @brief �߶��Ƿ����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [in] test_tile ���Ե���
	* @return bool �Ƿ����
	*/
	bool is_seven_pairs_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

	/**
	* end group
	* @}
	*/

	/**
	* @addtogroup thirteen_orphans
	* @{
	*/

	/**
	* @brief ʮ����������
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] useful_table ��Ч�Ʊ�Ǳ���Ϊnull��
	* @return int ������
	*/
	int thirteen_orphans_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

	/**
	* @brief ʮ�����Ƿ�����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] waiting_table ���Ʊ�Ǳ���Ϊnull��
	* @return bool �Ƿ�����
	*/
	bool is_thirteen_orphans_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

	/**
	* @brief ʮ�����Ƿ����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [in] test_tile ���Ե���
	* @return bool �Ƿ����
	*/
	bool is_thirteen_orphans_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

	/**
	* end group
	* @}
	*/

	/**
	* @addtogroup knitted_straight
	* @{
	*/

	/**
	* @brief �����������
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] useful_table ��Ч�Ʊ�Ǳ���Ϊnull��
	* @return int ������
	*/
	int knitted_straight_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

	/**
	* @brief ������Ƿ�����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] waiting_table ���Ʊ�Ǳ���Ϊnull��
	* @return bool �Ƿ�����
	*/
	bool is_knitted_straight_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

	/**
	* @brief ������Ƿ����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [in] test_tile ���Ե���
	* @return bool �Ƿ����
	*/
	bool is_knitted_straight_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

	/**
	* end group
	* @}
	*/

	/**
	* @addtogroup honors_and_knitted_tiles
	* @{
	*/

	/**
	* @brief ȫ����������
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] useful_table ��Ч�Ʊ�Ǳ���Ϊnull��
	* @return int ������
	*/
	int honors_and_knitted_tiles_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

	/**
	* @brief ȫ�����Ƿ�����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [out] waiting_table ���Ʊ�Ǳ���Ϊnull��
	* @return bool �Ƿ�����
	*/
	bool is_honors_and_knitted_tiles_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

	/**
	* @brief ȫ�����Ƿ����
	*
	* @param [in] standing_tiles ����
	* @param [in] standing_cnt ������
	* @param [in] test_tile ���Ե���
	* @return bool �Ƿ����
	*/
	bool is_honors_and_knitted_tiles_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

	/**
	* end group
	* @}
	*/

	/**
	* end group
	* @}
	*/

	/**
	* @name form flags
	* @{
	*  ����
	*/
#define FORM_FLAG_BASIC_FORM                0x01  ///< ��������
#define FORM_FLAG_SEVEN_PAIRS               0x02  ///< �߶�
#define FORM_FLAG_THIRTEEN_ORPHANS          0x04  ///< ʮ����
#define FORM_FLAG_HONORS_AND_KNITTED_TILES  0x08  ///< ȫ����
#define FORM_FLAG_KNITTED_STRAIGHT          0x10  ///< �����
#define FORM_FLAG_ALL                       0xFF  ///< ȫ������
	/**
	* @}
	*/

	/**
	* @brief ö�ٴ������Ƶļ�������Ϣ
	*/
	struct enum_result_t {
		tile_t discard_tile;                    ///< ��������
		uint8_t form_flag;                      ///< ������ʽ
		int shanten;                            ///< ������
		useful_table_t useful_table;            ///< ��Ч�Ʊ�Ǳ�
	};

	/**
	* @brief ö�ٴ������Ƶļ���ص�����
	*
	* @param [in] context ��enum_discard_tile��������contextԭ������
	* @param [in] result ������
	* @retval true ����ö��
	* @retval false ����ö��
	*/
	typedef bool(*enum_callback_t)(void *context, const enum_result_t *result);

	/**
	* @brief ö�ٴ�������
	*
	* @param [in] hand_tiles ���ƽṹ
	* @param [in] serving_tile ���ƣ���Ϊ0����ʱ���������Ƶ���Ϣ��
	* @param [in] form_flag ������Щ����
	* @param [in] context �û��Զ����������ԭ���ӻص���������
	* @param [in] enum_callback �ص�����
	*/
	void enum_discard_tile(const hand_tiles_t *hand_tiles, tile_t serving_tile, uint8_t form_flag,
		void *context, enum_callback_t enum_callback);





	// ʮ����13����
	static const tile_t standard_thirteen_orphans[13] = {
		TILE_1m, TILE_9m, TILE_1s, TILE_9s, TILE_1p, TILE_9p, TILE_E, TILE_S, TILE_W, TILE_N, TILE_C, TILE_F, TILE_P
	};

	// �����ֻ������6��
	// 147m 258s 369p
	// 147m 369s 258p
	// 258m 147s 369p
	// 258m 369s 147p
	// 369m 147s 258p
	// 369m 258s 147p
	static const tile_t standard_knitted_straight[6][9] = {
		{ TILE_1m, TILE_4m, TILE_7m, TILE_2s, TILE_5s, TILE_8s, TILE_3p, TILE_6p, TILE_9p },
		{ TILE_1m, TILE_4m, TILE_7m, TILE_3s, TILE_6s, TILE_9s, TILE_2p, TILE_5p, TILE_8p },
		{ TILE_2m, TILE_5m, TILE_8m, TILE_1s, TILE_4s, TILE_7s, TILE_3p, TILE_6p, TILE_9p },
		{ TILE_2m, TILE_5m, TILE_8m, TILE_3s, TILE_6s, TILE_9s, TILE_1p, TILE_4p, TILE_7p },
		{ TILE_3m, TILE_6m, TILE_9m, TILE_1s, TILE_4s, TILE_7s, TILE_2p, TILE_5p, TILE_8p },
		{ TILE_3m, TILE_6m, TILE_9m, TILE_2s, TILE_5s, TILE_8s, TILE_1p, TILE_4p, TILE_7p },
	};


	//stringify.cpp

	// ������ʵ�ֺ���
	static intptr_t parse_tiles_impl(const char *str, tile_t *tiles, intptr_t max_cnt, intptr_t *out_tile_cnt) {
		//if (strspn(str, "123456789mpsESWNCFP") != strlen(str)) {
		//    return PARSE_ERROR_ILLEGAL_CHARACTER;
		//}

		intptr_t tile_cnt = 0;

#define SET_SUIT_FOR_NUMBERED(value_)       \
    for (intptr_t i = tile_cnt; i > 0;) {   \
        if (tiles[--i] & 0xF0) break;       \
        tiles[i] |= value_;                 \
        } (void)0

#define SET_SUIT_FOR_HONOR() \
    for (intptr_t i = tile_cnt; i > 0;) {   \
        if (tiles[--i] & 0xF0) break;       \
        if (tiles[i] > 7) return PARSE_ERROR_ILLEGAL_CHARACTER; \
        tiles[i] |= 0x40;                   \
        } (void)0

#define NO_SUFFIX_AFTER_DIGIT() (tile_cnt > 0 && !(tiles[tile_cnt - 1] & 0xF0))
#define CHECK_SUFFIX() if (NO_SUFFIX_AFTER_DIGIT()) return PARSE_ERROR_NO_SUFFIX_AFTER_DIGIT

		const char *p = str;
		for (; tile_cnt < max_cnt && *p != '\0'; ++p) {
			char c = *p;
			switch (c) {
			case '0': tiles[tile_cnt++] = 5; break;
			case '1': tiles[tile_cnt++] = 1; break;
			case '2': tiles[tile_cnt++] = 2; break;
			case '3': tiles[tile_cnt++] = 3; break;
			case '4': tiles[tile_cnt++] = 4; break;
			case '5': tiles[tile_cnt++] = 5; break;
			case '6': tiles[tile_cnt++] = 6; break;
			case '7': tiles[tile_cnt++] = 7; break;
			case '8': tiles[tile_cnt++] = 8; break;
			case '9': tiles[tile_cnt++] = 9; break;
			case 'm': SET_SUIT_FOR_NUMBERED(0x10); break;
			case 's': SET_SUIT_FOR_NUMBERED(0x20); break;
			case 'p': SET_SUIT_FOR_NUMBERED(0x30); break;
			case 'z': SET_SUIT_FOR_HONOR(); break;
			case 'E': CHECK_SUFFIX(); tiles[tile_cnt++] = TILE_E; break;
			case 'S': CHECK_SUFFIX(); tiles[tile_cnt++] = TILE_S; break;
			case 'W': CHECK_SUFFIX(); tiles[tile_cnt++] = TILE_W; break;
			case 'N': CHECK_SUFFIX(); tiles[tile_cnt++] = TILE_N; break;
			case 'C': CHECK_SUFFIX(); tiles[tile_cnt++] = TILE_C; break;
			case 'F': CHECK_SUFFIX(); tiles[tile_cnt++] = TILE_F; break;
			case 'P': CHECK_SUFFIX(); tiles[tile_cnt++] = TILE_P; break;
			default: goto parse_finish;
			}
		}

	parse_finish:
		// һ��������+��׺�����Ѿ�������������ô�����м�һ�������֣�ֱ�ӽ�������ĺ�׺
		if (NO_SUFFIX_AFTER_DIGIT()) {
			const char *p1 = strpbrk(p, "mspz");
			if (p1 == nullptr) {
				return PARSE_ERROR_NO_SUFFIX_AFTER_DIGIT;
			}

			switch (*p1) {
			case 'm': SET_SUIT_FOR_NUMBERED(0x10); break;
			case 's': SET_SUIT_FOR_NUMBERED(0x20); break;
			case 'p': SET_SUIT_FOR_NUMBERED(0x30); break;
			case 'z': SET_SUIT_FOR_HONOR(); break;
			default: return PARSE_ERROR_NO_SUFFIX_AFTER_DIGIT;
			}
			p = p1 + 1;
		}

#undef SET_SUIT_FOR_NUMBERED
#undef SET_SUIT_FOR_HONOR
#undef NO_SUFFIX_AFTER_DIGIT
#undef CHECK_SUFFIX

		if (out_tile_cnt != nullptr) {
			*out_tile_cnt = tile_cnt;
		}
		return static_cast<intptr_t>(p - str);
	}

	// ������
	intptr_t parse_tiles(const char *str, tile_t *tiles, intptr_t max_cnt) {
		intptr_t tile_cnt;
		if (parse_tiles_impl(str, tiles, max_cnt, &tile_cnt) > 0) {
			return tile_cnt;
		}
		return 0;
	}

	// ���ɸ�¶
	static intptr_t make_fixed_pack(const tile_t *tiles, intptr_t tile_cnt, pack_t *pack, uint8_t offer) {
		if (tile_cnt > 0) {
			if (tile_cnt != 3 && tile_cnt != 4) {
				return PARSE_ERROR_WRONG_TILES_COUNT_FOR_FIXED_PACK;
			}
			if (tile_cnt == 3) {
				if (offer == 0) {
					offer = 1;
				}
				if (tiles[0] == tiles[1] && tiles[1] == tiles[2]) {
					*pack = make_pack(offer, PACK_TYPE_PUNG, tiles[0]);
				}
				else {
					if (tiles[0] + 1 == tiles[1] && tiles[1] + 1 == tiles[2]) {
						*pack = make_pack(offer, PACK_TYPE_CHOW, tiles[1]);
					}
					else if (tiles[0] + 1 == tiles[2] && tiles[2] + 1 == tiles[1]) {
						*pack = make_pack(offer, PACK_TYPE_CHOW, tiles[2]);
					}
					else if (tiles[1] + 1 == tiles[0] && tiles[0] + 1 == tiles[2]) {
						*pack = make_pack(offer, PACK_TYPE_CHOW, tiles[0]);
					}
					else if (tiles[1] + 1 == tiles[2] && tiles[2] + 1 == tiles[0]) {
						*pack = make_pack(offer, PACK_TYPE_CHOW, tiles[2]);
					}
					else if (tiles[2] + 1 == tiles[0] && tiles[0] + 1 == tiles[1]) {
						*pack = make_pack(offer, PACK_TYPE_CHOW, tiles[0]);
					}
					else if (tiles[2] + 1 == tiles[1] && tiles[1] + 1 == tiles[0]) {
						*pack = make_pack(offer, PACK_TYPE_CHOW, tiles[1]);
					}
					else {
						return PARSE_ERROR_CANNOT_MAKE_FIXED_PACK;
					}
				}
			}
			else {
				if (tiles[0] != tiles[1] || tiles[1] != tiles[2] || tiles[2] != tiles[3]) {
					return PARSE_ERROR_CANNOT_MAKE_FIXED_PACK;
				}
				*pack = make_pack(offer, PACK_TYPE_KONG, tiles[0]);
			}
			return 1;
		}
		return 0;
	}

	// �ַ���ת��Ϊ���ƽṹ������
	intptr_t string_to_tiles(const char *str, hand_tiles_t *hand_tiles, tile_t *serving_tile) {
		size_t len = strlen(str);
		if (strspn(str, "0123456789mpszESWNCFP,[]") != len) {
			return PARSE_ERROR_ILLEGAL_CHARACTER;
		}

		pack_t packs[4];
		intptr_t pack_cnt = 0;
		bool in_brackets = false;
		tile_t tiles[14];
		intptr_t tile_cnt = 0;
		uint8_t offer = 0;

		const char *p = str;
		while (char c = *p) {
			const char *q;
			switch (c) {
			case ',': {
				if (!in_brackets) {
					return PARSE_ERROR_ILLEGAL_CHARACTER;
				}
				offer = static_cast<uint8_t>(*++p - '0');
				q = ++p;
				break;
			}
			case '[': {
				if (pack_cnt > 4) {
					return PARSE_ERROR_TOO_MANY_FIXED_PACKS;
				}
				q = ++p;
				in_brackets = true;
				offer = 0;
				break;
			}
			case ']': {
				if (!in_brackets) {
					return PARSE_ERROR_ILLEGAL_CHARACTER;
				}
				q = ++p;
				intptr_t ret = make_fixed_pack(tiles, tile_cnt, &packs[pack_cnt], offer);
				if (ret < 0) {
					return ret;
				}
				in_brackets = false;
				++pack_cnt;
				tile_cnt = 0;
				break;
			}
			default: {
				intptr_t ret = parse_tiles_impl(p, tiles, 14, &tile_cnt);
				if (ret < 0) {
					return ret;
				}
				if (ret == 0) {
					return PARSE_ERROR_ILLEGAL_CHARACTER;
				}
				q = p + ret;
				break;
			}
			}
			p = q;
		}

		memcpy(hand_tiles->fixed_packs, packs, pack_cnt * sizeof(pack_t));
		hand_tiles->pack_count = pack_cnt;
		intptr_t max_cnt = 13 - pack_cnt * 3;
		if (tile_cnt > max_cnt) {
			memcpy(hand_tiles->standing_tiles, tiles, max_cnt * sizeof(tile_t));
			hand_tiles->tile_count = max_cnt;
			if (serving_tile != nullptr) {
				*serving_tile = tiles[max_cnt];
			}
		}
		else {
			memcpy(hand_tiles->standing_tiles, tiles, tile_cnt * sizeof(tile_t));
			hand_tiles->tile_count = tile_cnt;
			if (serving_tile != nullptr) {
				*serving_tile = 0;
			}
		}

		return PARSE_NO_ERROR;
	}

	// ��ת��Ϊ�ַ���
	intptr_t tiles_to_string(const tile_t *tiles, intptr_t tile_cnt, char *str, intptr_t max_size) {
		bool tenhon = false;
		char *p = str, *end = str + max_size;

		static const char suffix[] = "mspz";
		static const char honor_text[] = "ESWNCFP";
		suit_t last_suit = 0;
		for (intptr_t i = 0; i < tile_cnt && p < end; ++i) {
			tile_t t = tiles[i];
			suit_t s = tile_get_suit(t);
			rank_t r = tile_get_rank(t);
			if (s == 1 || s == 2 || s == 3) {  // ����
				if (r >= 1 && r <= 9) {  // ��Ч��Χ1-9
					if (last_suit != s && last_suit != 0) {  // ��ɫ���ˣ��Ӻ�׺
						if (last_suit != 4 || tenhon) {
							*p++ = suffix[last_suit - 1];
						}
					}
					if (p < end) {
						*p++ = '0' + r;  // д��һ�������ַ�
					}
					last_suit = s;  // ��¼��ɫ
				}
			}
			else if (s == 4) {  // ����
				if (r >= 1 && r <= 7) {  // ��Ч��Χ1-7
					if (last_suit != s && last_suit != 0) {  // ��ɫ���ˣ��Ӻ�׺
						if (last_suit != 4) {
							*p++ = suffix[last_suit - 1];
						}
					}
					if (p < end) {
						if (tenhon) {  // ���ʽ��׺
							*p++ = '0' + r;  // д��һ�������ַ�
						}
						else {
							*p++ = honor_text[r - 1];  // ֱ��д��������Ӧ��ĸ
						}
						last_suit = s;
					}
				}
			}
		}

		// д����һ��пռ䣬�����׺
		if (p != str && p < end && (last_suit != 4 || tenhon)) {
			*p++ = suffix[last_suit - 1];
		}

		if (p < end) {
			*p = '\0';
		}
		return static_cast<intptr_t>(p - str);
	}

	// ����ת��Ϊ�ַ���
	intptr_t packs_to_string(const pack_t *packs, intptr_t pack_cnt, char *str, intptr_t max_size) {
		char *p = str, *end = str + max_size;
		tile_t temp[4];
		for (intptr_t i = 0; i < pack_cnt && p < end; ++i) {
			pack_t pack = packs[i];
			uint8_t o = pack_get_offer(pack);
			tile_t t = pack_get_tile(pack);
			uint8_t pt = pack_get_type(pack);
			switch (pt) {
			case PACK_TYPE_CHOW:
				if (p >= end) break;
				*p++ = '[';
				temp[0] = static_cast<tile_t>(t - 1); temp[1] = t; temp[2] = static_cast<tile_t>(t + 1);
				p += tiles_to_string(temp, 3, p, static_cast<intptr_t>(end - p));
				if (p >= end) break;
				*p++ = ',';
				if (p >= end) break;
				*p++ = '0' + o;
				if (p >= end) break;
				*p++ = ']';
				break;
			case PACK_TYPE_PUNG:
				if (p >= end) break;
				*p++ = '[';
				temp[0] = t; temp[1] = t; temp[2] = t;
				p += tiles_to_string(temp, 3, p, static_cast<intptr_t>(end - p));
				if (p >= end) break;
				*p++ = ',';
				if (p >= end) break;
				*p++ = '0' + o;
				if (p >= end) break;
				*p++ = ']';
				break;
			case PACK_TYPE_KONG:
				if (p >= end) break;
				*p++ = '[';
				temp[0] = t; temp[1] = t; temp[2] = t; temp[3] = t;
				p += tiles_to_string(temp, 4, p, static_cast<intptr_t>(end - p));
				if (p >= end) break;
				*p++ = ',';
				if (p >= end) break;
				*p++ = '0' + o;
				if (p >= end) break;
				*p++ = ']';

				//if (!is_pack_melded(pack))
				break;
			case PACK_TYPE_PAIR:
				temp[0] = t; temp[1] = t;
				p += tiles_to_string(temp, 2, p, static_cast<intptr_t>(end - p));
				break;
			default: break;
			}
		}

		if (p < end) {
			*p = '\0';
		}
		return static_cast<intptr_t>(p - str);
	}

	// ���ƽṹת��Ϊ�ַ���
	intptr_t hand_tiles_to_string(const hand_tiles_t *hand_tiles, char *str, intptr_t max_size) {
		char *p = str, *end = str + max_size;
		p += packs_to_string(hand_tiles->fixed_packs, hand_tiles->pack_count, str, max_size);
		if (p < end) p += tiles_to_string(hand_tiles->standing_tiles, hand_tiles->tile_count, p, static_cast<intptr_t>(end - p));
		return static_cast<intptr_t>(p - str);
	}



	// ����ת������
	intptr_t packs_to_tiles(const pack_t *packs, intptr_t pack_cnt, tile_t *tiles, intptr_t tile_cnt) {
		if (packs == nullptr || tiles == nullptr) {
			return 0;
		}

		intptr_t cnt = 0;
		for (int i = 0; i < pack_cnt && cnt < tile_cnt; ++i) {
			tile_t tile = pack_get_tile(packs[i]);
			switch (pack_get_type(packs[i])) {
			case PACK_TYPE_CHOW:
				if (cnt < tile_cnt) tiles[cnt++] = static_cast<tile_t>(tile - 1);
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				if (cnt < tile_cnt) tiles[cnt++] = static_cast<tile_t>(tile + 1);
				break;
			case PACK_TYPE_PUNG:
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				break;
			case PACK_TYPE_KONG:
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				break;
			case PACK_TYPE_PAIR:
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				if (cnt < tile_cnt) tiles[cnt++] = tile;
				break;
			default:
				break;
			}
		}
		return cnt;
	}

	// ���ƴ��
	void map_tiles(const tile_t *tiles, intptr_t cnt, tile_table_t *cnt_table) {
		memset(*cnt_table, 0, sizeof(*cnt_table));
		for (intptr_t i = 0; i < cnt; ++i) {
			++(*cnt_table)[tiles[i]];
		}
	}

	// �����ƴ��
	bool map_hand_tiles(const hand_tiles_t *hand_tiles, tile_table_t *cnt_table) {
		// ��ÿһ�鸱¶����3�������㣬��ô������=13
		if (hand_tiles->tile_count <= 0 || hand_tiles->pack_count < 0 || hand_tiles->pack_count > 4
			|| hand_tiles->pack_count * 3 + hand_tiles->tile_count != 13) {
			return false;
		}

		// ����¶�ָ�����
		tile_t tiles[18];
		intptr_t tile_cnt = 0;
		if (hand_tiles->pack_count == 0) {
			memcpy(tiles, hand_tiles->standing_tiles, 13 * sizeof(tile_t));
			tile_cnt = 13;
		}
		else {
			tile_cnt = packs_to_tiles(hand_tiles->fixed_packs, hand_tiles->pack_count, tiles, 18);
			memcpy(tiles + tile_cnt, hand_tiles->standing_tiles, hand_tiles->tile_count * sizeof(tile_t));
			tile_cnt += hand_tiles->tile_count;
		}

		// ���
		map_tiles(tiles, tile_cnt, cnt_table);
		return true;
	}

	// ����ת������
	intptr_t table_to_tiles(const tile_table_t &cnt_table, tile_t *tiles, intptr_t max_cnt) {
		intptr_t cnt = 0;
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			for (int n = 0; n < cnt_table[t]; ++n) {
				*tiles++ = t;
				++cnt;
				if (cnt == max_cnt) {
					return max_cnt;
				}
			}
		}
		return cnt;
	}

	// ������Ч��ö��
	int count_useful_tile(const tile_table_t &used_table, const useful_table_t &useful_table) {
		int cnt = 0;
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (useful_table[t]) {
				cnt += 4 - used_table[t];
			}
		}
		return cnt;
	}

	namespace {

		// ·����Ԫ����Ԫ�����ӡ�ȸͷ�����ӵ����࣬������ĺ�
		// ��8λ��ʾ���ͣ���8λ��ʾ��
		// ����˳�Ӻ�˳�Ӵ��ӣ���ָ������С��һ���ƣ�
		// ������˳��123���У���Ϊ1�����������45���У���Ϊ4���ȵ�
		typedef uint16_t path_unit_t;

#define UNIT_TYPE_CHOW 1                // ˳��
#define UNIT_TYPE_PUNG 2                // ����
#define UNIT_TYPE_PAIR 4                // ȸͷ
#define UNIT_TYPE_CHOW_OPEN_END 5       // ������߱��Ŵ���
#define UNIT_TYPE_CHOW_CLOSED 6         // Ƕ�Ŵ���
#define UNIT_TYPE_INCOMPLETE_PUNG 7     // ���Ӵ���

#define MAKE_UNIT(type_, tile_) static_cast<path_unit_t>(((type_) << 8) | (tile_))
#define UNIT_TYPE(unit_) (((unit_) >> 8) & 0xFF)
#define UNIT_TILE(unit_) ((unit_) & 0xFF)

#define MAX_STATE 512
#define UNIT_SIZE 7

		// һ��·��
		struct work_path_t {
			path_unit_t units[UNIT_SIZE];  // 14/2=7���7������
			uint16_t depth;  // ��ǰ·�����
		};

		// ��ǰ����״̬
		struct work_state_t {
			work_path_t paths[MAX_STATE];  // ����·��
			intptr_t count;  // ·������
		};
	}

	// ·���Ƿ�������
	static bool is_basic_form_branch_exist(const intptr_t fixed_cnt, const work_path_t *work_path, const work_state_t *work_state) {
		if (work_state->count <= 0 || work_path->depth == 0) {
			return false;
		}

		// depth������Ϣ�����԰�stl����endӦ��Ҫ+1
		const uint16_t depth = static_cast<uint16_t>(work_path->depth + 1);

		// std::includesҪ�����򣬵��ֲ����ƻ���ǰ����
		work_path_t temp;
		std::copy(&work_path->units[fixed_cnt], &work_path->units[depth], &temp.units[fixed_cnt]);
		std::sort(&temp.units[fixed_cnt], &temp.units[depth]);

		return std::any_of(&work_state->paths[0], &work_state->paths[work_state->count],
			[&temp, fixed_cnt, depth](const work_path_t &path) {
			return std::includes(&path.units[fixed_cnt], &path.units[path.depth], &temp.units[fixed_cnt], &temp.units[depth]);
		});
	}

	// ����·��
	static void save_work_path(const intptr_t fixed_cnt, const work_path_t *work_path, work_state_t *work_state) {
		if (work_state->count < MAX_STATE) {
			work_path_t &path = work_state->paths[work_state->count++];
			path.depth = work_path->depth;
			std::copy(&work_path->units[fixed_cnt], &work_path->units[work_path->depth], &path.units[fixed_cnt]);

			// ����Ƿ��ظ�·��ʱ��std::includesҪ�������������ｫ������
			std::sort(&path.units[fixed_cnt], &path.units[path.depth]);
		}
		else {
			assert(0 && "too many state!");
		}
	}

	// �ݹ�����������������
	// ����˵����
	//   cnt_table�Ʊ�
	//   has_pair�Ƿ���ȸͷ
	//   pack_cnt��ɵ�������
	//   incomplete_cnt������
	// �����������Ϊ�Ż������õģ�
	// work_path���浱ǰ���ڼ����·����
	// work_state�����������Ѿ��������·����
	// ��0��fixed_cnt�������ǲ�ʹ�õģ���Щ�������˸�¶������
	static int basic_form_shanten_recursively(tile_table_t &cnt_table, const bool has_pair, const unsigned pack_cnt, const unsigned incomplete_cnt,
		const intptr_t fixed_cnt, work_path_t *work_path, work_state_t *work_state) {
		if (pack_cnt == 4) {  // �Ѿ���4������
			return has_pair ? -1 : 0;  // �����ȸͷ������ˣ������ȸͷ����������
		}

		int max_ret;  // ��ǰ״̬�ܷ��ص����������

					  // �㷨˵����
					  // ȱ�ٵ�������=4-��ɵ�������
					  // ȱ�ٵĴ�����=ȱ�ٵ�������-���еĴ�����
					  // ��ʽ�ϲ���ȱ�ٵĴ�����=4-��ɵ�������-���еĴ�����
		int incomplete_need = 4 - pack_cnt - incomplete_cnt;
		if (incomplete_need > 0) {  // ����Ҫ���ӵ����
									// ��ȸͷʱ��������=���еĴ�����+ȱ�ٵĴ�����*2-1
									// ��ȸͷʱ��������=���еĴ�����+ȱ�ٵĴ�����*2
			max_ret = incomplete_cnt + incomplete_need * 2 - (has_pair ? 1 : 0);
		}
		else {  // �������˵����
				// ��ȸͷʱ��������=3-��ɵ�������
				// ��ȸͷʱ��������=4-��ɵ�������
			max_ret = (has_pair ? 3 : 4) - pack_cnt;
		}

		// ��ǰ·�����
		const unsigned depth = pack_cnt + incomplete_cnt + has_pair;
		work_path->depth = static_cast<uint16_t>(depth);

		int result = max_ret;

		if (pack_cnt + incomplete_cnt > 4) {  // ���ӳ���
			save_work_path(fixed_cnt, work_path, work_state);
			return max_ret;
		}

		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] < 1) {
				continue;
			}

			// ȸͷ
			if (!has_pair && cnt_table[t] > 1) {
				work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_PAIR, t);  // ��¼ȸͷ
				if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
					// ����ȸͷ���ݹ�
					cnt_table[t] -= 2;
					int ret = basic_form_shanten_recursively(cnt_table, true, pack_cnt, incomplete_cnt,
						fixed_cnt, work_path, work_state);
					result = std::min(ret, result);
					// ��ԭ
					cnt_table[t] += 2;
				}
			}

			// ����
			if (cnt_table[t] > 2) {
				work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_PUNG, t);  // ��¼����
				if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
					// ����������ӣ��ݹ�
					cnt_table[t] -= 3;
					int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt + 1, incomplete_cnt,
						fixed_cnt, work_path, work_state);
					result = std::min(ret, result);
					// ��ԭ
					cnt_table[t] += 3;
				}
			}

			// ˳�ӣ�ֻ�������ƣ�
			bool is_numbered = is_numbered_suit(t);
			// ˳��t t+1 t+2����Ȼt������8�����ϵ�����
			if (is_numbered && tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
				work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_CHOW, t);  // ��¼˳��
				if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
					// ��������˳�ӣ��ݹ�
					--cnt_table[t];
					--cnt_table[t + 1];
					--cnt_table[t + 2];
					int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt + 1, incomplete_cnt,
						fixed_cnt, work_path, work_state);
					result = std::min(ret, result);
					// ��ԭ
					++cnt_table[t];
					++cnt_table[t + 1];
					++cnt_table[t + 2];
				}
			}

			// ����Ѿ�ͨ������ȸͷ/���ӽ��������������ٰ����Ӽ�����������϶��������
			if (result < max_ret) {
				continue;
			}

			// ���Ӵ���
			if (cnt_table[t] > 1) {
				work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_INCOMPLETE_PUNG, t);  // ��¼���Ӵ���
				if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
					// �������Ӵ��ӣ��ݹ�
					cnt_table[t] -= 2;
					int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt, incomplete_cnt + 1,
						fixed_cnt, work_path, work_state);
					result = std::min(ret, result);
					// ��ԭ
					cnt_table[t] += 2;
				}
			}

			// ˳�Ӵ��ӣ�ֻ�������ƣ�
			if (is_numbered) {
				// ������߱��Ŵ���t t+1����Ȼt������9�����ϵ�����
				if (tile_get_rank(t) < 9 && cnt_table[t + 1]) {  // ������߱���
					work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_CHOW_OPEN_END, t);  // ��¼������߱��Ŵ���
					if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
						// �������ӣ��ݹ�
						--cnt_table[t];
						--cnt_table[t + 1];
						int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt, incomplete_cnt + 1,
							fixed_cnt, work_path, work_state);
						result = std::min(ret, result);
						// ��ԭ
						++cnt_table[t];
						++cnt_table[t + 1];
					}
				}
				// Ƕ�Ŵ���t t+2����Ȼt������8�����ϵ�����
				if (tile_get_rank(t) < 8 && cnt_table[t + 2]) {  // Ƕ��
					work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_CHOW_CLOSED, t);  // ��¼Ƕ�Ŵ���
					if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
						// �������ӣ��ݹ�
						--cnt_table[t];
						--cnt_table[t + 2];
						int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt, incomplete_cnt + 1,
							fixed_cnt, work_path, work_state);
						result = std::min(ret, result);
						// ��ԭ
						++cnt_table[t];
						++cnt_table[t + 2];
					}
				}
			}
		}

		if (result == max_ret) {
			save_work_path(fixed_cnt, work_path, work_state);
		}

		return result;
	}

	// �����Ƿ��д���
	static bool numbered_tile_has_neighbor(const tile_table_t &cnt_table, tile_t t) {
		rank_t r = tile_get_rank(t);
		if (r < 9) { if (cnt_table[t + 1]) return true; }
		if (r < 8) { if (cnt_table[t + 2]) return true; }
		if (r > 1) { if (cnt_table[t - 1]) return true; }
		if (r > 2) { if (cnt_table[t - 2]) return true; }
		return false;
	}

	// �Ա��Ϊ���������������������
	static int basic_form_shanten_from_table(tile_table_t &cnt_table, intptr_t fixed_cnt, useful_table_t *useful_table) {
		// ����������
		work_path_t work_path;
		work_state_t work_state;
		work_state.count = 0;
		int result = basic_form_shanten_recursively(cnt_table, false, static_cast<uint16_t>(fixed_cnt), 0,
			fixed_cnt, &work_path, &work_state);

		if (useful_table == nullptr) {
			return result;
		}

		// ������е��ƣ���ȡ�ܼ�������������
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] == 4 && result > 0) {
				continue;
			}

			if (cnt_table[t] == 0) {
				// �����������ƺͲ����ŵ����ƣ���Щ�ƶ��޷�����������
				if (is_honor(t) || !numbered_tile_has_neighbor(cnt_table, t)) {
					continue;
				}
			}

			++cnt_table[t];
			work_state.count = 0;
			int temp = basic_form_shanten_recursively(cnt_table, false, static_cast<uint16_t>(fixed_cnt), 0,
				fixed_cnt, &work_path, &work_state);
			if (temp < result) {
				(*useful_table)[t] = true;  // ���Ϊ��Ч��
			}
			--cnt_table[t];
		}

		return result;
	}

	// ��������������
	int basic_form_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
		if (standing_tiles == nullptr || (standing_cnt != 13
			&& standing_cnt != 10 && standing_cnt != 7 && standing_cnt != 4 && standing_cnt != 1)) {
			return std::numeric_limits<int>::max();
		}

		// �����Ƶ�������д��
		tile_table_t cnt_table;
		map_tiles(standing_tiles, standing_cnt, &cnt_table);

		if (useful_table != nullptr) {
			memset(*useful_table, 0, sizeof(*useful_table));
		}
		return basic_form_shanten_from_table(cnt_table, (13 - standing_cnt) / 3, useful_table);
	}

	// ���������ж�1���Ƿ�����
	static bool is_basic_form_wait_1(tile_table_t &cnt_table, useful_table_t *waiting_table) {
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] != 1) {
				continue;
			}

			// ������
			cnt_table[t] = 0;
			if (std::all_of(std::begin(cnt_table), std::end(cnt_table), [](int n) { return n == 0; })) {
				cnt_table[t] = 1;
				if (waiting_table != nullptr) {  // ����Ҫ��ȡ�����ţ������ֱ�ӷ���
					(*waiting_table)[t] = true;
				}
				return true;
			}
			cnt_table[t] = 1;
		}

		return false;
	}

	// ���������ж�2���Ƿ�����
	static bool is_basic_form_wait_2(const tile_table_t &cnt_table, useful_table_t *waiting_table) {
		bool ret = false;
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] < 1) {
				continue;
			}
			if (cnt_table[t] > 1) {
				if (waiting_table != nullptr) {  // ��ȡ������
					(*waiting_table)[t] = true;  // �Ե�
					ret = true;
					continue;
				}
				else {  // ����Ҫ��ȡ�����ţ������ֱ�ӷ���
					return true;
				}
			}
			if (is_numbered_suit_quick(t)) {  // ���ƴ���
				rank_t r = tile_get_rank(t);
				if (r > 1 && cnt_table[t - 1]) {  // ������߱���
					if (waiting_table != nullptr) {  // ��ȡ������
						if (r < 9) (*waiting_table)[t + 1] = true;
						if (r > 2) (*waiting_table)[t - 2] = true;
						ret = true;
						continue;
					}
					else {  // ����Ҫ��ȡ�����ţ������ֱ�ӷ���
						return true;
					}
				}
				if (r > 2 && cnt_table[t - 2]) {  // Ƕ��
					if (waiting_table != nullptr) {  // ��ȡ������
						(*waiting_table)[t - 1] = true;
						ret = true;
						continue;
					}
					else {  // ����Ҫ��ȡ�����ţ������ֱ�ӷ���
						return true;
					}
				}
			}
		}
		return ret;
	}

	// ���������ж�4���Ƿ�����
	static bool is_basic_form_wait_4(tile_table_t &cnt_table, useful_table_t *waiting_table) {
		bool ret = false;
		// ����ȸͷ
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] < 2) {
				continue;
			}
			// ����ȸͷ���ݹ�
			cnt_table[t] -= 2;
			if (is_basic_form_wait_2(cnt_table, waiting_table)) {
				ret = true;
			}
			// ��ԭ
			cnt_table[t] += 2;
			if (ret && waiting_table == nullptr) {  // ����Ҫ��ȡ�����ţ������ֱ�ӽ����ݹ�
				return true;
			}
		}

		return ret;
	}

	// �ݹ������������Ƿ�����
	static bool is_basic_form_wait_recursively(tile_table_t &cnt_table, intptr_t left_cnt, useful_table_t *waiting_table) {
		if (left_cnt == 1) {
			return is_basic_form_wait_1(cnt_table, waiting_table);
		}

		bool ret = false;
		if (left_cnt == 4) {
			ret = is_basic_form_wait_4(cnt_table, waiting_table);
			if (ret && waiting_table == nullptr) {  // ����Ҫ��ȡ�����ţ������ֱ�ӽ����ݹ�
				return true;
			}
		}

		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] < 1) {
				continue;
			}

			// ����
			if (cnt_table[t] > 2) {
				// ����������ӣ��ݹ�
				cnt_table[t] -= 3;
				if (is_basic_form_wait_recursively(cnt_table, left_cnt - 3, waiting_table)) {
					ret = true;
				}
				// ��ԭ
				cnt_table[t] += 3;
				if (ret && waiting_table == nullptr) {  // ����Ҫ��ȡ�����ţ������ֱ�ӽ����ݹ�
					return true;
				}
			}

			// ˳�ӣ�ֻ�������ƣ�
			if (is_numbered_suit(t)) {
				// ˳��t t+1 t+2����Ȼt������8�����ϵ�����
				if (tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
					// ��������˳�ӣ��ݹ�
					--cnt_table[t];
					--cnt_table[t + 1];
					--cnt_table[t + 2];
					if (is_basic_form_wait_recursively(cnt_table, left_cnt - 3, waiting_table)) {
						ret = true;
					}
					// ��ԭ
					++cnt_table[t];
					++cnt_table[t + 1];
					++cnt_table[t + 2];
					if (ret && waiting_table == nullptr) {  // ����Ҫ��ȡ�����ţ������ֱ�ӽ����ݹ�
						return true;
					}
				}
			}
		}

		return ret;
	}

	// ���������Ƿ�����
	// ����֮���Բ���ֱ�ӵ������������㺯�����ж��䷵��ֵΪ0�ķ�ʽ
	// ����Ϊǰ�߻��������ӣ���������ں����ж�����û��Ҫ�ģ����Ե���дһ�׸����߼�
	bool is_basic_form_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
		// �����Ƶ�������д��
		tile_table_t cnt_table;
		map_tiles(standing_tiles, standing_cnt, &cnt_table);

		if (waiting_table != nullptr) {
			memset(*waiting_table, 0, sizeof(*waiting_table));
		}
		return is_basic_form_wait_recursively(cnt_table, standing_cnt, waiting_table);
	}

	// ��������2���ܷ����
	static bool is_basic_form_win_2(const tile_table_t &cnt_table) {
		// �ҵ�δʹ�õ���
		typedef std::remove_all_extents<tile_table_t>::type table_elem_t;
		const table_elem_t *it = std::find_if(std::begin(cnt_table), std::end(cnt_table), [](table_elem_t n) { return n > 0; });
		// ��������������2
		if (it == std::end(cnt_table) || *it != 2) {
			return false;
		}
		// ��������δʹ�õ���
		return std::none_of(it + 1, std::end(cnt_table), [](int n) { return n > 0; });
	}

	// �ݹ������������Ƿ����
	// ����֮���Բ���ֱ�ӵ������������㺯�����ж��䷵��ֵΪ-1�ķ�ʽ��
	// ����Ϊǰ�߻��������ӣ���������ں����ж�����û��Ҫ�ģ����Ե���дһ�׸����߼�
	static bool is_basic_form_win_recursively(tile_table_t &cnt_table, intptr_t left_cnt) {
		if (left_cnt == 2) {
			return is_basic_form_win_2(cnt_table);
		}

		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] < 1) {
				continue;
			}

			// ����
			if (cnt_table[t] > 2) {
				// ����������ӣ��ݹ�
				cnt_table[t] -= 3;
				bool ret = is_basic_form_win_recursively(cnt_table, left_cnt - 3);
				// ��ԭ
				cnt_table[t] += 3;
				if (ret) {
					return true;
				}
			}

			// ˳�ӣ�ֻ�������ƣ�
			if (is_numbered_suit(t)) {
				// ˳��t t+1 t+2����Ȼt������8�����ϵ�����
				if (tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
					// ��������˳�ӣ��ݹ�
					--cnt_table[t];
					--cnt_table[t + 1];
					--cnt_table[t + 2];
					bool ret = is_basic_form_win_recursively(cnt_table, left_cnt - 3);
					// ��ԭ
					++cnt_table[t];
					++cnt_table[t + 1];
					++cnt_table[t + 2];
					if (ret) {
						return true;
					}
				}
			}
		}

		return false;
	}

	// ���������Ƿ����
	bool is_basic_form_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
		// �����Ƶ�������д��
		tile_table_t cnt_table;
		map_tiles(standing_tiles, standing_cnt, &cnt_table);
		++cnt_table[test_tile];  // ��Ӳ��Ե���
		return is_basic_form_win_recursively(cnt_table, standing_cnt + 1);
	}

	//-------------------------------- �߶� --------------------------------

	// �߶�������
	int seven_pairs_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
		if (standing_tiles == nullptr || standing_cnt != 13) {
			return std::numeric_limits<int>::max();
		}

		// ���Ƶ�������д����ͳ�ƶ�����
		int pair_cnt = 0;
		tile_table_t cnt_table = { 0 };
		for (intptr_t i = 0; i < standing_cnt; ++i) {
			tile_t tile = standing_tiles[i];
			++cnt_table[tile];
			if (cnt_table[tile] == 2) {
				++pair_cnt;
				cnt_table[tile] = 0;
			}
		}

		// ��Ч��
		if (useful_table != nullptr) {
			std::transform(std::begin(cnt_table), std::end(cnt_table), std::begin(*useful_table), [](int n) { return n != 0; });
		}
		return 6 - pair_cnt;
	}

	// �߶��Ƿ�����
	bool is_seven_pairs_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
		// ֱ�Ӽ�������������������Ϊ0��Ϊ����
		if (waiting_table == nullptr) {
			return (0 == seven_pairs_shanten(standing_tiles, standing_cnt, nullptr));
		}

		useful_table_t useful_table;
		if (0 == seven_pairs_shanten(standing_tiles, standing_cnt, &useful_table)) {
			memcpy(*waiting_table, useful_table, sizeof(*waiting_table));
			return true;
		}
		return false;
	}

	// �߶��Ƿ����
	bool is_seven_pairs_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
		useful_table_t useful_table;
		return (0 == seven_pairs_shanten(standing_tiles, standing_cnt, &useful_table)
			&& useful_table[test_tile]);
	}

	//-------------------------------- ʮ���� --------------------------------

	// ʮ����������
	int thirteen_orphans_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
		if (standing_tiles == nullptr || standing_cnt != 13) {
			return std::numeric_limits<int>::max();
		}

		// ���Ƶ�������д��
		tile_table_t cnt_table;
		map_tiles(standing_tiles, standing_cnt, &cnt_table);

		bool has_pair = false;
		int cnt = 0;
		for (int i = 0; i < 13; ++i) {
			int n = cnt_table[standard_thirteen_orphans[i]];
			if (n > 0) {
				++cnt;  // �۾��Ƶ�����
				if (n > 1) {
					has_pair = true;  // �۾��ƶ���
				}
			}
		}

		// ���ж���ʱ��������Ϊ��12-�۾��Ƶ�����
		// ��û�ж���ʱ��������Ϊ��13-�۾��Ƶ�����
		int ret = has_pair ? 12 - cnt : 13 - cnt;

		if (useful_table != nullptr) {
			// �ȱ�����е��۾���Ϊ��Ч��
			memset(*useful_table, 0, sizeof(*useful_table));
			std::for_each(std::begin(standard_thirteen_orphans), std::end(standard_thirteen_orphans),
				[useful_table](tile_t t) {
				(*useful_table)[t] = true;
			});

			// ���ж���ʱ�����е��۾��ƶ�����Ҫ��
			if (has_pair) {
				for (int i = 0; i < 13; ++i) {
					tile_t t = standard_thirteen_orphans[i];
					int n = cnt_table[t];
					if (n > 0) {
						(*useful_table)[t] = false;
					}
				}
			}
		}

		return ret;
	}

	// ʮ�����Ƿ�����
	bool is_thirteen_orphans_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
		// ֱ�Ӽ�������������������Ϊ0��Ϊ����
		if (waiting_table == nullptr) {
			return (0 == thirteen_orphans_shanten(standing_tiles, standing_cnt, nullptr));
		}

		useful_table_t useful_table;
		if (0 == thirteen_orphans_shanten(standing_tiles, standing_cnt, &useful_table)) {
			memcpy(*waiting_table, useful_table, sizeof(*waiting_table));
			return true;
		}
		return false;
	}

	// ʮ�����Ƿ����
	bool is_thirteen_orphans_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
		useful_table_t useful_table;
		return (0 == thirteen_orphans_shanten(standing_tiles, standing_cnt, &useful_table)
			&& useful_table[test_tile]);
	}

	//-------------------------------- �������+����+ȸͷ������ --------------------------------

	// �Ա��Ϊ��������������Ƿ�����
	static bool is_knitted_straight_wait_from_table(const tile_table_t &cnt_table, intptr_t left_cnt, useful_table_t *waiting_table) {
		// ƥ�������
		const tile_t(*matched_seq)[9] = nullptr;
		tile_t missing_tiles[9];
		int missing_cnt = 0;
		for (int i = 0; i < 6; ++i) {  // ������������
			missing_cnt = 0;
			for (int k = 0; k < 9; ++k) {
				tile_t t = standard_knitted_straight[i][k];
				if (cnt_table[t] == 0) {  // ȱʧ��
					missing_tiles[missing_cnt++] = t;
				}
			}
			if (missing_cnt < 2) {  // ȱ2�Ż����ϵĿ϶�û��
				matched_seq = &standard_knitted_straight[i];
				break;
			}
		}

		if (matched_seq == nullptr || missing_cnt > 2) {
			return false;
		}

		// �޳������
		tile_table_t temp_table;
		memcpy(&temp_table, &cnt_table, sizeof(temp_table));
		for (int i = 0; i < 9; ++i) {
			tile_t t = (*matched_seq)[i];
			if (temp_table[t]) {
				--temp_table[t];
			}
		}

		if (missing_cnt == 1) {  // ���ȱһ�ţ���ô��ȥ�����֮�����Ӧ�������״̬��������
			if (left_cnt == 10) {
				if (is_basic_form_win_recursively(temp_table, 2)) {
					if (waiting_table != nullptr) {  // ��ȡ�����ţ��������ȱ��һ��
						(*waiting_table)[missing_tiles[0]] = true;
					}
					return true;
				}
			}
			else {
				if (is_basic_form_win_recursively(temp_table, 5)) {
					if (waiting_table != nullptr) {  // ��ȡ�����ţ��������ȱ��һ��
						(*waiting_table)[missing_tiles[0]] = true;
					}
					return true;
				}
			}
		}
		else if (missing_cnt == 0) {  // �����������ˣ���ô��ȥ�����֮�����Ҫ�����������Ʋ�����
			if (left_cnt == 10) {
				return is_basic_form_wait_1(temp_table, waiting_table);
			}
			else {
				return is_basic_form_wait_recursively(temp_table, 4, waiting_table);
			}
		}

		return false;
	}

	// �������Ͱ����������������������ڼ��������� ��ͬ˳ �����������ӵķ����������Ƶ�������
	static int basic_form_shanten_specified(const tile_table_t &cnt_table, const tile_t *main_tiles, int main_cnt,
		intptr_t fixed_cnt, useful_table_t *useful_table) {

		tile_table_t temp_table;
		memcpy(&temp_table, &cnt_table, sizeof(temp_table));
		int exist_cnt = 0;

		// ͳ����������
		for (int i = 0; i < main_cnt; ++i) {
			tile_t t = main_tiles[i];
			int n = cnt_table[t];
			if (n > 0) {  // �У�����֮
				++exist_cnt;
				--temp_table[t];
			}
		}

		// ��¼��Ч��
		if (useful_table != nullptr) {
			memset(*useful_table, 0, sizeof(*useful_table));

			// ͳ������ȱʧ����
			for (int i = 0; i < main_cnt; ++i) {
				tile_t t = main_tiles[i];
				int n = cnt_table[t];
				if (n <= 0) {
					(*useful_table)[t] = true;
				}
			}
		}

		// �����Ƶ�������
		int result = basic_form_shanten_from_table(temp_table, fixed_cnt + main_cnt / 3, useful_table);

		// ������=����ȱ�ٵ�����+�����Ƶ�������
		return (main_cnt - exist_cnt) + result;
	}

	// �����������
	int knitted_straight_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
		if (standing_tiles == nullptr || (standing_cnt != 13 && standing_cnt != 10)) {
			return std::numeric_limits<int>::max();
		}

		// ���
		tile_table_t cnt_table;
		map_tiles(standing_tiles, standing_cnt, &cnt_table);

		int ret = std::numeric_limits<int>::max();

		// ��Ҫ��ȡ��Ч��ʱ��������������ͬʱ�ͻ�ȡ��Ч����
		if (useful_table != nullptr) {
			memset(*useful_table, 0, sizeof(*useful_table));

			useful_table_t temp_table;

			// 6��������ֱ����
			for (int i = 0; i < 6; ++i) {
				int fixed_cnt = (13 - static_cast<int>(standing_cnt)) / 3;
				int st = basic_form_shanten_specified(cnt_table, standard_knitted_straight[i], 9, fixed_cnt, &temp_table);
				if (st < ret) {  // ������С�ģ�ֱ�Ӹ�������
					ret = st;
					memcpy(*useful_table, temp_table, sizeof(*useful_table));  // ֱ�Ӹ���ԭ������Ч������
				}
				else if (st == ret) {  // ���ֲ�ͬ����������������ȵĻ���ֱ�Ӻϲ���Ч��
					std::transform(std::begin(*useful_table), std::end(*useful_table), std::begin(temp_table),
						std::begin(*useful_table), [](bool u, bool t) { return u || t; });
				}
			}
		}
		else {
			// 6��������ֱ����
			for (int i = 0; i < 6; ++i) {
				int fixed_cnt = (13 - static_cast<int>(standing_cnt)) / 3;
				int st = basic_form_shanten_specified(cnt_table, standard_knitted_straight[i], 9, fixed_cnt, nullptr);
				if (st < ret) {
					ret = st;
				}
			}
		}

		return ret;
	}

	// ������Ƿ�����
	bool is_knitted_straight_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
		if (standing_tiles == nullptr || (standing_cnt != 13 && standing_cnt != 10)) {
			return false;
		}

		// �����Ƶ�������д��
		tile_table_t cnt_table;
		map_tiles(standing_tiles, standing_cnt, &cnt_table);

		return is_knitted_straight_wait_from_table(cnt_table, standing_cnt, waiting_table);
	}

	// ������Ƿ����
	bool is_knitted_straight_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
		useful_table_t waiting_table;
		return (is_knitted_straight_wait(standing_tiles, standing_cnt, &waiting_table)
			&& waiting_table[test_tile]);
	}

	//-------------------------------- ȫ����/���ǲ��� --------------------------------

	// 1���������ȫ����������
	static int honors_and_knitted_tiles_shanten_1(const tile_t *standing_tiles, intptr_t standing_cnt, int which_seq, useful_table_t *useful_table) {
		if (standing_tiles == nullptr || standing_cnt != 13) {
			return std::numeric_limits<int>::max();
		}

		// ���Ƶ�������д��
		tile_table_t cnt_table;
		map_tiles(standing_tiles, standing_cnt, &cnt_table);

		int cnt = 0;

		// ͳ����������ֵ�����
		for (int i = 0; i < 9; ++i) {
			tile_t t = standard_knitted_straight[which_seq][i];
			int n = cnt_table[t];
			if (n > 0) {  // �У����Ӽ���
				++cnt;
			}
		}

		// ͳ������
		for (int i = 6; i < 13; ++i) {
			tile_t t = standard_thirteen_orphans[i];
			int n = cnt_table[t];
			if (n > 0) {  // �У����Ӽ���
				++cnt;
			}
		}

		// ��¼��Ч��
		if (useful_table != nullptr) {
			memset(*useful_table, 0, sizeof(*useful_table));

			// ͳ�����������ȱʧ������
			for (int i = 0; i < 9; ++i) {
				tile_t t = standard_knitted_straight[which_seq][i];
				int n = cnt_table[t];
				if (n <= 0) {
					(*useful_table)[t] = true;
				}
			}

			// ͳ��ȱʧ������
			for (int i = 6; i < 13; ++i) {
				tile_t t = standard_thirteen_orphans[i];
				int n = cnt_table[t];
				if (n <= 0) {
					(*useful_table)[t] = true;
				}
			}
		}

		// ������=13-�������͵ļ���
		return 13 - cnt;
	}

	// ȫ����������
	int honors_and_knitted_tiles_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
		int ret = std::numeric_limits<int>::max();

		// ��Ҫ��ȡ��Ч��ʱ��������������ͬʱ�ͻ�ȡ��Ч����
		if (useful_table != nullptr) {
			memset(*useful_table, 0, sizeof(*useful_table));

			useful_table_t temp_table;

			// 6��������ֱ����
			for (int i = 0; i < 6; ++i) {
				int st = honors_and_knitted_tiles_shanten_1(standing_tiles, standing_cnt, i, &temp_table);
				if (st < ret) {  // ������С�ģ�ֱ�Ӹ�������
					ret = st;
					memcpy(*useful_table, temp_table, sizeof(*useful_table));  // ֱ�Ӹ���ԭ������Ч������
				}
				else if (st == ret) {  // ���ֲ�ͬ����������������ȵĻ���ֱ�Ӻϲ���Ч��
					std::transform(std::begin(*useful_table), std::end(*useful_table), std::begin(temp_table),
						std::begin(*useful_table), [](bool u, bool t) { return u || t; });
				}
			}
		}
		else {
			// 6��������ֱ����
			for (int i = 0; i < 6; ++i) {
				int st = honors_and_knitted_tiles_shanten_1(standing_tiles, standing_cnt, i, nullptr);
				if (st < ret) {
					ret = st;
				}
			}
		}
		return ret;
	}

	// ȫ�����Ƿ�����
	bool is_honors_and_knitted_tiles_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
		// ֱ�Ӽ�������������������Ϊ0��Ϊ����
		if (waiting_table == nullptr) {
			return (0 == honors_and_knitted_tiles_shanten(standing_tiles, standing_cnt, nullptr));
		}

		useful_table_t useful_table;
		if (0 == honors_and_knitted_tiles_shanten(standing_tiles, standing_cnt, &useful_table)) {
			memcpy(*waiting_table, useful_table, sizeof(*waiting_table));
			return true;
		}
		return false;
	}

	// ȫ�����Ƿ����
	bool is_honors_and_knitted_tiles_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
		useful_table_t useful_table;
		if (0 == honors_and_knitted_tiles_shanten(standing_tiles, standing_cnt, &useful_table)) {
			return useful_table[test_tile];
		}
		return false;
	}

	//-------------------------------- ö�ٴ��� --------------------------------

	// ö�ٴ�������1��
	static bool enum_discard_tile_1(const hand_tiles_t *hand_tiles, tile_t discard_tile, uint8_t form_flag,
		void *context, enum_callback_t enum_callback) {
		enum_result_t result;
		result.discard_tile = discard_tile;
		result.form_flag = FORM_FLAG_BASIC_FORM;
		result.shanten = basic_form_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
		if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0���������Ҵ����������Ч�ƣ�������Ϊ����
			result.shanten = -1;
		}
		if (!enum_callback(context, &result)) {
			return false;
		}

		// ������13��ʱ������Ҫ�����������
		if (hand_tiles->tile_count == 13) {
			if (form_flag | FORM_FLAG_SEVEN_PAIRS) {
				result.form_flag = FORM_FLAG_SEVEN_PAIRS;
				result.shanten = seven_pairs_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
				if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0���������Ҵ����������Ч�ƣ�������Ϊ����
					result.shanten = -1;
				}
				if (!enum_callback(context, &result)) {
					return false;
				}
			}

			if (form_flag | FORM_FLAG_THIRTEEN_ORPHANS) {
				result.form_flag = FORM_FLAG_THIRTEEN_ORPHANS;
				result.shanten = thirteen_orphans_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
				if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0���������Ҵ����������Ч�ƣ�������Ϊ����
					result.shanten = -1;
				}
				if (!enum_callback(context, &result)) {
					return false;
				}
			}

			if (form_flag | FORM_FLAG_HONORS_AND_KNITTED_TILES) {
				result.form_flag = FORM_FLAG_HONORS_AND_KNITTED_TILES;
				result.shanten = honors_and_knitted_tiles_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
				if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0���������Ҵ����������Ч�ƣ�������Ϊ����
					result.shanten = -1;
				}
				if (!enum_callback(context, &result)) {
					return false;
				}
			}
		}

		// ������13�Ż���10��ʱ������Ҫ���������
		if (hand_tiles->tile_count == 13 || hand_tiles->tile_count == 10) {
			if (form_flag | FORM_FLAG_KNITTED_STRAIGHT) {
				result.form_flag = FORM_FLAG_KNITTED_STRAIGHT;
				result.shanten = knitted_straight_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
				if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0���������Ҵ����������Ч�ƣ�������Ϊ����
					result.shanten = -1;
				}
				if (!enum_callback(context, &result)) {
					return false;
				}
			}
		}

		return true;
	}

	// ö�ٴ�������
	void enum_discard_tile(const hand_tiles_t *hand_tiles, tile_t serving_tile, uint8_t form_flag,
		void *context, enum_callback_t enum_callback) {
		// �ȼ������е�
		if (!enum_discard_tile_1(hand_tiles, serving_tile, form_flag, context, enum_callback)) {
			return;
		}

		if (serving_tile == 0) {
			return;
		}

		// �����ƴ��
		tile_table_t cnt_table;
		map_tiles(hand_tiles->standing_tiles, hand_tiles->tile_count, &cnt_table);

		// ����һ������
		hand_tiles_t temp;
		memcpy(&temp, hand_tiles, sizeof(temp));

		// ���γ��Դ����е�����
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] && t != serving_tile && cnt_table[serving_tile] < 4) {
				--cnt_table[t];  // ��������
				++cnt_table[serving_tile];  // ��������

											// ��tableת������
				table_to_tiles(cnt_table, temp.standing_tiles, temp.tile_count);

				// ����
				if (!enum_discard_tile_1(&temp, t, form_flag, context, enum_callback)) {
					return;
				}

				// ��ԭ
				--cnt_table[serving_tile];
				++cnt_table[t];
			}
		}
	}




#define MAX_DIVISION_CNT 20  // һ�������Ҳû��20�ֻ��ְɣ�������
#if 0
#define LOG(fmt_, ...) printf(fmt_, ##__VA_ARGS__)
#else
#define LOG(...) do { } while (0)
#endif
	//#define STRICT_98_RULE

#if 0  // Debug
	extern intptr_t packs_to_string(const pack_t *packs, intptr_t pack_cnt, char *str, intptr_t max_size);
#endif

	//-------------------------------- ���� --------------------------------

	namespace {

		// ����
		struct division_t {
			pack_t packs[5];  // ���顣4����1ȸͷ����5��
		};

		// ���ֽ��
		struct division_result_t {
			division_t divisions[MAX_DIVISION_CNT];  // ÿһ�ֻ���
			intptr_t count;  // ���ַ�ʽ����
		};
	}

	// �ݹ黮���㷨�����һ������ӻ���
	static void divide_tail_add_division(intptr_t fixed_cnt, const division_t *work_division, division_result_t *result) {
		// ����һ�ݵ�ǰ�Ļ��ֳ��������ӣ��������ֵ�����
		// ���ﲻ��ֱ����work_division->packs�����򣬷�����ƻ��ݹ���������
		division_t temp;
		memcpy(&temp, work_division, sizeof(temp));
		std::sort(temp.packs + fixed_cnt, temp.packs + 4);

		// ������ֻ����Ƿ��Ѿ�������
		if (std::none_of(&result->divisions[0], &result->divisions[result->count],
			[&temp, fixed_cnt](const division_t &od) {
			return std::equal(&od.packs[fixed_cnt], &od.packs[4], &temp.packs[fixed_cnt]);
		})) {
			// д�뻮�ֽ����
			memcpy(&result->divisions[result->count], &temp, sizeof(temp));
			++result->count;
		}
		else {
			LOG("same case");
		}
	}

	// �ݹ黮�ֵ����һ��
	static bool divide_tail(tile_table_t &cnt_table, intptr_t fixed_cnt, division_t *work_division, division_result_t *result) {
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] < 2) {
				continue;
			}

			cnt_table[t] -= 2;  // ����
								// ������ȫ��ʹ�����
			if (std::all_of(std::begin(cnt_table), std::end(cnt_table), [](int n) { return n == 0; })) {
				cnt_table[t] += 2;  // ��ԭ

									// ��2����Ϊȸͷ
				work_division->packs[4] = make_pack(0, PACK_TYPE_PAIR, t);
				divide_tail_add_division(fixed_cnt, work_division, result);  // ��¼
				return true;
			}
			cnt_table[t] += 2;  // ��ԭ
		}

		return false;
	}

	// �ж�һ�����ַ�֧�Ƿ�����
	static bool is_division_branch_exist(intptr_t fixed_cnt, intptr_t step, const division_t *work_division, const division_result_t *result) {
		// û�л���ʱ���Լ����ֲ���С��3ʱ������⣬��Ϊ����Ҫ��3���ݹ�Ż������ͬ����
		if (result->count <= 0 || step < 3) {
			return false;
		}

		// std::includesҪ������
		// ���ﲻ��ֱ����work_division->packs�����򣬷�����ƻ��ݹ���������
		division_t temp;
		memcpy(&temp.packs[fixed_cnt], &work_division->packs[fixed_cnt], step * sizeof(pack_t));
		std::sort(&temp.packs[fixed_cnt], &temp.packs[fixed_cnt + step]);

		// ֻ��Ҫ�Ƚ������Ƿ��ظ���֧��ȸͷ������Ƚϣ������±���4
		return std::any_of(&result->divisions[0], &result->divisions[result->count],
			[&temp, fixed_cnt, step](const division_t &od) {
			return std::includes(&od.packs[fixed_cnt], &od.packs[4], &temp.packs[fixed_cnt], &temp.packs[fixed_cnt + step]);
		});
	}

	// �ݹ黮��
	static bool divide_recursively(tile_table_t &cnt_table, intptr_t fixed_cnt, intptr_t step, division_t *work_division, division_result_t *result) {
		const intptr_t idx = step + fixed_cnt;
		if (idx == 4) {  // 4�����Ӷ�����
			return divide_tail(cnt_table, fixed_cnt, work_division, result);
		}

		bool ret = false;

		// ���Ʊ��ű�����
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] < 1) {
				continue;
			}

			// ����
			if (cnt_table[t] > 2) {
				work_division->packs[idx] = make_pack(0, PACK_TYPE_PUNG, t);  // ��¼����
				if (!is_division_branch_exist(fixed_cnt, step + 1, work_division, result)) {
					// ����������ӣ��ݹ�
					cnt_table[t] -= 3;
					if (divide_recursively(cnt_table, fixed_cnt, step + 1, work_division, result)) {
						ret = true;
					}
					// ��ԭ
					cnt_table[t] += 3;
				}
			}

			// ˳�ӣ�ֻ�������ƣ�
			if (is_numbered_suit(t)) {
				if (tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
					work_division->packs[idx] = make_pack(0, PACK_TYPE_CHOW, static_cast<tile_t>(t + 1));  // ��¼˳��
					if (!is_division_branch_exist(fixed_cnt, step + 1, work_division, result)) {
						// ��������˳�ӣ��ݹ�
						--cnt_table[t];
						--cnt_table[t + 1];
						--cnt_table[t + 2];
						if (divide_recursively(cnt_table, fixed_cnt, step + 1, work_division, result)) {
							ret = true;
						}
						// ��ԭ
						++cnt_table[t];
						++cnt_table[t + 1];
						++cnt_table[t + 2];
					}
				}
			}
		}

		return ret;
	}

	// ����һ����
	static bool divide_win_hand(const tile_t *standing_tiles, const pack_t *fixed_packs, intptr_t fixed_cnt, division_result_t *result) {
		intptr_t standing_cnt = 14 - fixed_cnt * 3;

		// �����Ƶ�������д��
		tile_table_t cnt_table;
		map_tiles(standing_tiles, standing_cnt, &cnt_table);

		result->count = 0;

		// ���Ƹ�¶������
		division_t work_division;
		memcpy(work_division.packs, fixed_packs, fixed_cnt * sizeof(pack_t));
		return divide_recursively(cnt_table, fixed_cnt, 0, &work_division, result);
	}

	//-------------------------------- �㷬 --------------------------------

	// 4�����1
	static forceinline bool is_four_shifted_1(rank_t r0, rank_t r1, rank_t r2, rank_t r3) {
		return (r0 + 1 == r1 && r1 + 1 == r2 && r2 + 1 == r3);
	}

	// 4�����2
	static forceinline bool is_four_shifted_2(rank_t r0, rank_t r1, rank_t r2, rank_t r3) {
		return (r0 + 2 == r1 && r1 + 2 == r2 && r2 + 2 == r3);
	}

	// 3�����1
	static forceinline bool is_shifted_1(rank_t r0, rank_t r1, rank_t r2) {
		return (r0 + 1 == r1 && r1 + 1 == r2);
	}

	// 3�����2
	static forceinline bool is_shifted_2(rank_t r0, rank_t r1, rank_t r2) {
		return (r0 + 2 == r1 && r1 + 2 == r2);
	}

	// ��ɫ
	static forceinline bool is_mixed(suit_t s0, suit_t s1, suit_t s2) {
		return (s0 != s1 && s0 != s2 && s1 != s2);
	}

	// 3�����1����
	static forceinline bool is_shifted_1_unordered(rank_t r0, rank_t r1, rank_t r2) {
		return is_shifted_1(r1, r0, r2) || is_shifted_1(r2, r0, r1) || is_shifted_1(r0, r1, r2)
			|| is_shifted_1(r2, r1, r0) || is_shifted_1(r0, r2, r1) || is_shifted_1(r1, r2, r0);
	}

	// 4��˳�ӵķ�
	static fan_t get_4_chows_fan(tile_t t0, tile_t t1, tile_t t2, tile_t t3) {
		// ������Ƶ��˳��

		// һɫ�Ĳ���
		if (is_four_shifted_2(t0, t1, t2, t3) || is_four_shifted_1(t0, t1, t2, t3)) {
			return FOUR_PURE_SHIFTED_CHOWS;
		}
		// һɫ��ͬ˳
		if (t0 == t1 && t0 == t2 && t0 == t3) {
			return QUADRUPLE_CHOW;
		}
		// ���϶�û��
		return FAN_NONE;
	}

	// 3��˳�ӵķ�
	static fan_t get_3_chows_fan(tile_t t0, tile_t t1, tile_t t2) {
		suit_t s0 = tile_get_suit(t0);
		suit_t s1 = tile_get_suit(t1);
		suit_t s2 = tile_get_suit(t2);

		rank_t r0 = tile_get_rank(t0);
		rank_t r1 = tile_get_rank(t1);
		rank_t r2 = tile_get_rank(t2);

		// ������Ƶ��˳��

		if (is_mixed(s0, s1, s2)) {  // ��ɫ
									 // ��ɫ������
			if (is_shifted_1_unordered(r1, r0, r2)) {
				return MIXED_SHIFTED_CHOWS;
			}
			// ��ɫ��ͬ˳
			if (r0 == r1 && r1 == r2) {
				return MIXED_TRIPLE_CHOW;
			}
			// ����
			if ((r0 == 2 && r1 == 5 && r2 == 8) || (r0 == 2 && r1 == 8 && r2 == 5)
				|| (r0 == 5 && r1 == 2 && r2 == 8) || (r0 == 5 && r1 == 8 && r2 == 2)
				|| (r0 == 8 && r1 == 2 && r2 == 5) || (r0 == 8 && r1 == 5 && r2 == 2)) {
				return MIXED_STRAIGHT;
			}
		}
		else {  // һɫ
				// ����
			if (t0 + 3 == t1 && t1 + 3 == t2) {
				return PURE_STRAIGHT;
			}
			// һɫ������
			if (is_shifted_2(t0, t1, t2) || is_shifted_1(t0, t1, t2)) {
				return PURE_SHIFTED_CHOWS;
			}
			// һɫ��ͬ˳
			if (t0 == t1 && t0 == t2) {
				return PURE_TRIPLE_CHOW;
			}
		}
		// ���϶�û��
		return FAN_NONE;
	}

	// 2��˳�ӵķ�
	static fan_t get_2_chows_fan_unordered(tile_t t0, tile_t t1) {
		// ������Ƶ��˳��

		if (!is_suit_equal_quick(t0, t1)) {  // ��ɫ
											 // ϲ���
			if (is_rank_equal_quick(t0, t1)) {
				return MIXED_DOUBLE_CHOW;
			}
		}
		else {  // һɫ
				// ����
			if (t0 + 3 == t1 || t1 + 3 == t0) {
				return SHORT_STRAIGHT;
			}
			// ���ٸ�
			rank_t r0 = tile_get_rank(t0);
			rank_t r1 = tile_get_rank(t1);
			if ((r0 == 2 && r1 == 8) || (r0 == 8 && r1 == 2)) {
				return TWO_TERMINAL_CHOWS;
			}
			// һ���
			if (t0 == t1) {
				return PURE_DOUBLE_CHOW;
			}
		}
		// ���϶�û��
		return FAN_NONE;
	}

	// 4����ӵķ�
	static fan_t get_4_pungs_fan(tile_t t0, tile_t t1, tile_t t2, tile_t t3) {
		// һɫ�Ľڸ�
		if (is_numbered_suit_quick(t0) && t0 + 1 == t1 && t1 + 1 == t2 && t2 + 1 == t3) {
			return FOUR_PURE_SHIFTED_PUNGS;
		}
		// ����ϲ
		if (t0 == TILE_E && t1 == TILE_S && t2 == TILE_W && t3 == TILE_N) {
			return BIG_FOUR_WINDS;
		}
		// ���϶�û��
		return FAN_NONE;
	}

	// 3����ӵķ�
	static fan_t get_3_pungs_fan(tile_t t0, tile_t t1, tile_t t2) {
		// ������Ƶ��˳��

		if (is_numbered_suit_quick(t0) && is_numbered_suit_quick(t1) && is_numbered_suit_quick(t2)) {  // ����
			suit_t s0 = tile_get_suit(t0);
			suit_t s1 = tile_get_suit(t1);
			suit_t s2 = tile_get_suit(t2);

			rank_t r0 = tile_get_rank(t0);
			rank_t r1 = tile_get_rank(t1);
			rank_t r2 = tile_get_rank(t2);

			if (is_mixed(s0, s1, s2)) {  // ��ɫ
										 // ��ɫ���ڸ�
				if (is_shifted_1_unordered(r1, r0, r2)) {
					return MIXED_SHIFTED_PUNGS;
				}
				// ��ͬ��
				if (r0 == r1 && r1 == r2) {
					return TRIPLE_PUNG;
				}
			}
			else {
				// һɫ���ڸ�
				if (t0 + 1 == t1 && t1 + 1 == t2) {
					return PURE_SHIFTED_PUNGS;
				}
			}
		}
		else {
			// �����
			if ((t0 == TILE_E && t1 == TILE_S && t2 == TILE_W)
				|| (t0 == TILE_E && t1 == TILE_S && t2 == TILE_N)
				|| (t0 == TILE_E && t1 == TILE_W && t2 == TILE_N)
				|| (t0 == TILE_S && t1 == TILE_W && t2 == TILE_N)) {
				return BIG_THREE_WINDS;
			}
			// ����Ԫ
			if (t0 == TILE_C && t1 == TILE_F && t2 == TILE_P) {
				return BIG_THREE_DRAGONS;
			}
		}

		// ���϶�û��
		return FAN_NONE;
	}

	// 2����ӵķ�
	static fan_t get_2_pungs_fan_unordered(tile_t t0, tile_t t1) {
		// ������Ƶ��˳��
		if (is_numbered_suit_quick(t0) && is_numbered_suit_quick(t1)) {  // ����
																		 // ˫ͬ��
			if (is_rank_equal_quick(t0, t1)) {
				return DOUBLE_PUNG;
			}
		}
		else {
			// ˫����
			if (is_dragons(t0) && is_dragons(t1)) {
				return TWO_DRAGONS_PUNGS;
			}
		}
		// ���϶�û��
		return FAN_NONE;
	}

	// 1����ӵķ�
	static fan_t get_1_pung_fan(tile_t mid_tile) {
		// ����
		if (is_dragons(mid_tile)) {
			return DRAGON_PUNG;
		}
		// �۾ſ�
		if (is_terminal(mid_tile) || is_winds(mid_tile)) {
			return PUNG_OF_TERMINALS_OR_HONORS;
		}
		// ���϶�û��
		return FAN_NONE;
	}

	// ����3��˳�ӵķ���ʱ�����µĵ�4��˳�������1��
	static fan_t get_1_chow_extra_fan(tile_t tile0, tile_t tile1, tile_t tile2, tile_t tile_extra) {
		fan_t fan0 = get_2_chows_fan_unordered(tile0, tile_extra);
		fan_t fan1 = get_2_chows_fan_unordered(tile1, tile_extra);
		fan_t fan2 = get_2_chows_fan_unordered(tile2, tile_extra);

		// ������˳�򷵻�
		// һ���
		if (fan0 == PURE_DOUBLE_CHOW || fan1 == PURE_DOUBLE_CHOW || fan2 == PURE_DOUBLE_CHOW) {
			return PURE_DOUBLE_CHOW;
		}
		// ϲ���
		if (fan0 == MIXED_DOUBLE_CHOW || fan1 == MIXED_DOUBLE_CHOW || fan2 == MIXED_DOUBLE_CHOW) {
			return MIXED_DOUBLE_CHOW;
		}
		// ����
		if (fan0 == SHORT_STRAIGHT || fan1 == SHORT_STRAIGHT || fan2 == SHORT_STRAIGHT) {
			return SHORT_STRAIGHT;
		}
		// ���ٸ�
		if (fan0 == TWO_TERMINAL_CHOWS || fan1 == TWO_TERMINAL_CHOWS || fan2 == TWO_TERMINAL_CHOWS) {
			return TWO_TERMINAL_CHOWS;
		}

		return FAN_NONE;
	}

	// ����һ��ԭ��
	// �������δ��Ϲ���һ���ƣ�ֻ��ͬ����Ϲ�����Ӧ��һ��������һ��
	//
	// ������ͬԭ��
	// ���Ѿ��Ϲ�ĳһ���ֵ��ƣ�������ͬ����һ���������ͬ�ķ��ּƷ�
	//
	// ��������һ��ԭ��234567s234567p��ֻ�ܼ�Ϊ��ϲ���*2 ����*1�����ߡ�ϲ���*1 ����*2���������ǡ�ϲ���*2 ����*2��
	// �����������㣬234s223344567p��ֻ�ܼ�Ϊ����һ��ߡ�ϲ��ꡢ�������������ǡ�ϲ���*2��������
	//
	// ֱ�Ӱ�������д�������ͼ���㷨��̫������
	// �����㴦����ͳ���ж��ٷ���������ʱ�����������Ŀʱ�����ظ��Ŀ�ʼ����
	static void exclusionary_rule(const fan_t *all_fans, long fan_cnt, long max_cnt, fan_table_t &fan_table) {
		// ͳ���ж��ٷ�
		uint16_t table[4] = { 0 };
		long cnt = 0;
		for (long i = 0; i < fan_cnt; ++i) {
			if (all_fans[i] != FAN_NONE) {
				++cnt;
				++table[all_fans[i] - PURE_DOUBLE_CHOW];
			}
		}

		// ������ʱ�����ظ��Ŀ�ʼ����
		int limit_cnt = 1;
		// ��һ��������ʣ��1���ڶ�������ʣ��0
		while (cnt > max_cnt && limit_cnt >= 0) {
			int idx = 4;  // �����ٸ���ʼ����
			while (cnt > max_cnt && idx-- > 0) {
				while (static_cast<int>(table[idx]) > limit_cnt && cnt > max_cnt) {
					--table[idx];
					--cnt;
				}
			}
			--limit_cnt;
		}

		fan_table[PURE_DOUBLE_CHOW] = table[0];
		fan_table[MIXED_DOUBLE_CHOW] = table[1];
		fan_table[SHORT_STRAIGHT] = table[2];
		fan_table[TWO_TERMINAL_CHOWS] = table[3];
	}

	// 4��˳���㷬
	static void calculate_4_chows(const tile_t(&mid_tiles)[4], fan_table_t &fan_table) {
		fan_t fan;
		// ����4��˳�ӵķ���ʱ�����ټ����������
		if ((fan = get_4_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
			fan_table[fan] = 1;
			return;
		}

		// 3��˳���ж�
		// 012����3��˳�ӵķ���
		if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
			fan_table[fan] = 1;
			// �������4��˳�ӹ��ɵķ�
			if ((fan = get_1_chow_extra_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
				fan_table[fan] = 1;
			}
			return;
		}
		// 013����3��˳�ӵķ���
		else if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[3])) != FAN_NONE) {
			fan_table[fan] = 1;
			// �������4��˳�ӹ��ɵķ�
			if ((fan = get_1_chow_extra_fan(mid_tiles[0], mid_tiles[1], mid_tiles[3], mid_tiles[2])) != FAN_NONE) {
				fan_table[fan] = 1;
			}
			return;
		}
		// 023����3��˳�ӵķ���
		else if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
			fan_table[fan] = 1;
			// �������4��˳�ӹ��ɵķ�
			if ((fan = get_1_chow_extra_fan(mid_tiles[0], mid_tiles[2], mid_tiles[3], mid_tiles[1])) != FAN_NONE) {
				fan_table[fan] = 1;
			}
			return;
		}
		// 123����3��˳�ӵķ���
		else if ((fan = get_3_chows_fan(mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
			fan_table[fan] = 1;
			// �������4��˳�ӹ��ɵķ�
			if ((fan = get_1_chow_extra_fan(mid_tiles[1], mid_tiles[2], mid_tiles[3], mid_tiles[0])) != FAN_NONE) {
				fan_table[fan] = 1;
			}
			return;
		}

		// ������3��˳�ӵķ���ʱ��4��˳�����3��
		fan_t all_fans[6] = {
			get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[1]),
			get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[2]),
			get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[3]),
			get_2_chows_fan_unordered(mid_tiles[1], mid_tiles[2]),
			get_2_chows_fan_unordered(mid_tiles[1], mid_tiles[3]),
			get_2_chows_fan_unordered(mid_tiles[2], mid_tiles[3])
		};

		int max_cnt = 3;

		// 0������3��˳�����κι�ϵ
		if (all_fans[0] == FAN_NONE && all_fans[1] == FAN_NONE && all_fans[2] == FAN_NONE) {
			--max_cnt;
		}

		// 1������3��˳�����κι�ϵ
		if (all_fans[0] == FAN_NONE && all_fans[3] == FAN_NONE && all_fans[4] == FAN_NONE) {
			--max_cnt;
		}

		// 2������3��˳�����κι�ϵ
		if (all_fans[1] == FAN_NONE && all_fans[3] == FAN_NONE && all_fans[5] == FAN_NONE) {
			--max_cnt;
		}

		// 3������3��˳�����κι�ϵ
		if (all_fans[2] == FAN_NONE && all_fans[4] == FAN_NONE && all_fans[5] == FAN_NONE) {
			--max_cnt;
		}

		if (max_cnt > 0) {
			exclusionary_rule(all_fans, 6, max_cnt, fan_table);
		}
	}

	// 3��˳���㷬
	static void calculate_3_chows(const tile_t(&mid_tiles)[3], fan_table_t &fan_table) {
		fan_t fan;

		// ����3��˳�ӵķ���ʱ�����ټ��������
		if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
			fan_table[fan] = 1;
			return;
		}

		// ��������������ʱ��3��˳�����2��
		fan_t all_fans[3] = {
			get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[1]),
			get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[2]),
			get_2_chows_fan_unordered(mid_tiles[1], mid_tiles[2])
		};
		exclusionary_rule(all_fans, 3, 2, fan_table);
	}

	// 2��˳���㷬
	static void calculate_2_chows_unordered(const tile_t(&mid_tiles)[2], fan_table_t &fan_table) {
		fan_t fan;
		if ((fan = get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[1])) != FAN_NONE) {
			++fan_table[fan];
		}
	}

	// ���ӣ��ܣ��㷬
	static void calculate_kongs(const pack_t *pung_packs, intptr_t pung_cnt, fan_table_t &fan_table) {
		// ͳ������ ���� ���� ����
		int melded_kong_cnt = 0;
		int concealed_kong_cnt = 0;
		int concealed_pung_cnt = 0;
		for (intptr_t i = 0; i < pung_cnt; ++i) {
			if (is_pack_melded(pung_packs[i])) {
				if (pack_get_type(pung_packs[i]) == PACK_TYPE_KONG) {
					++melded_kong_cnt;
				}
			}
			else {
				if (pack_get_type(pung_packs[i]) == PACK_TYPE_KONG) {
					++concealed_kong_cnt;
				}
				else {
					++concealed_pung_cnt;
				}
			}
		}

		// ����
		// ����
		// ���� ���� ���� ���� -> ����+˫����+������
		// ���� ���� ���� ���� -> ����+˫����+������
		// ���� ���� ���� ���� -> ����+������+������
		// ���� ���� ���� ���� -> ����+������+������
		// ���� ���� ���� ���� -> ����+�İ���
		//
		// �ĸ�
		// ���� ���� ���� ���� -> �ĸ�
		// ���� ���� ���� ���� -> �ĸ�+˫����
		// ���� ���� ���� ���� -> �ĸ�+������
		// ���� ���� ���� ���� -> �ĸ�+�İ���
		//

		int kong_cnt = melded_kong_cnt + concealed_kong_cnt;
		switch (kong_cnt) {
		case 0:  // 0����
			switch (concealed_pung_cnt) {  // ���̵ĸ���
			case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
			case 3: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
			case 4: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
			default: break;
			}
			break;
		case 1:  // 1����
			if (melded_kong_cnt == 1) {  // ����
				fan_table[MELDED_KONG] = 1;
				switch (concealed_pung_cnt) {  // ���̵ĸ���
				case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
				case 3: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
				default: break;
				}
			}
			else {  // ����
				fan_table[CONCEALED_KONG] = 1;
				switch (concealed_pung_cnt) {  // ���̵ĸ���
				case 1: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
				case 2: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
				case 3: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
				default: break;
				}
			}
			break;
		case 2:  // 2����
			switch (concealed_kong_cnt) {
			case 0:  // ˫����
				fan_table[TWO_MELDED_KONGS] = 1;
				switch (concealed_pung_cnt) {  // ���̵ĸ���
				case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
				default: break;
				}
				break;
			case 1:  // ������
#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
				fan_table[CONCEALED_KONG_AND_MELDED_KONG] = 1;
#else
				fan_table[MELDED_KONG] = 1;
				fan_table[CONCEALED_KONG] = 1;
#endif
				switch (concealed_pung_cnt) {  // ���̵ĸ���
				case 1: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
				case 2: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
				default: break;
				}
				break;
			case 2:  // ˫����
				fan_table[TWO_CONCEALED_KONGS] = 1;
				switch (concealed_pung_cnt) {  // ���̵ĸ���
				case 1: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
				case 2: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
				default: break;
				}
				break;
			default:
				break;
			}
			break;
		case 3:  // 3����
			fan_table[THREE_KONGS] = 1;
			switch (concealed_kong_cnt) {  // ���̵ĸ���
			case 0:  // 3����
				break;
			case 1:  // 1����2����
				if (concealed_pung_cnt > 0) {
					fan_table[TWO_CONCEALED_PUNGS] = 1;
				}
				break;
			case 2:  // 2����1����
				if (concealed_pung_cnt == 0) {
					fan_table[TWO_CONCEALED_PUNGS] = 1;
				}
				else {
					fan_table[THREE_CONCEALED_PUNGS] = 1;
				}
				break;
			case 3:  // 3����
				if (concealed_pung_cnt == 0) {
					fan_table[THREE_CONCEALED_PUNGS] = 1;
				}
				else {
					fan_table[FOUR_CONCEALED_PUNGS] = 1;
				}
				break;
			default:
				break;
			}
			break;
		case 4:  // 4����
			fan_table[FOUR_KONGS] = 1;
			switch (concealed_kong_cnt) {
			case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
			case 3: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
			case 4: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
			default: break;
			}
			break;
		default:
			break;
		}

		// �ĸܺ��İ��̲��������ͣ������ȼ��������͵ķ�
		if (pung_cnt == 4) {
			if (fan_table[FOUR_KONGS] == 0 && fan_table[FOUR_CONCEALED_PUNGS] == 0) {
				fan_table[ALL_PUNGS] = 1;
			}
		}

		// ������ӵķ������̡��۾ſ̣�
		for (intptr_t i = 0; i < pung_cnt; ++i) {
			fan_t fan = get_1_pung_fan(pack_get_tile(pung_packs[i]));
			if (fan != FAN_NONE) {
				++fan_table[fan];
			}
		}
	}

	// 4������㷬
	static void calculate_4_pungs(const tile_t(&mid_tiles)[4], fan_table_t &fan_table) {
		fan_t fan;
		// ����4����ӵķ���ʱ�����ټ����������
		if ((fan = get_4_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
			fan_table[fan] = 1;
			return;
		}

		// 3������ж�
		bool _3_pungs_has_fan = false;
		int free_pack_idx = -1;  // δʹ�õ�1�����
								 // 012����3����ӵķ���
		if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
			fan_table[fan] = 1;
			free_pack_idx = 3;
			_3_pungs_has_fan = true;
		}
		// 013����3����ӵķ���
		else if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[3])) != FAN_NONE) {
			fan_table[fan] = 1;
			free_pack_idx = 2;
			_3_pungs_has_fan = true;
		}
		// 023����3����ӵķ���
		else if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
			fan_table[fan] = 1;
			free_pack_idx = 1;
			_3_pungs_has_fan = true;
		}
		// 123����3����ӵķ���
		else if ((fan = get_3_pungs_fan(mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
			fan_table[fan] = 1;
			free_pack_idx = 0;
			_3_pungs_has_fan = true;
		}

		// ����3����ӵķ���ʱ�����µĵ�4�����ֻ�����һ��
		if (_3_pungs_has_fan) {
			for (int i = 0; i < 4; ++i) {
				if (i == free_pack_idx) {
					continue;
				}
				// ������δʹ�õ�������Ӳ��Է���
				if ((fan = get_2_pungs_fan_unordered(mid_tiles[i], mid_tiles[free_pack_idx])) != FAN_NONE) {
					++fan_table[fan];
					break;
				}
			}
			return;
		}

		// ������3����ӵķ���ʱ���������㷬��
		if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[1])) != FAN_NONE) {
			++fan_table[fan];
		}
		if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[2])) != FAN_NONE) {
			++fan_table[fan];
		}
		if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[3])) != FAN_NONE) {
			++fan_table[fan];
		}
		if ((fan = get_2_pungs_fan_unordered(mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
			++fan_table[fan];
		}
		if ((fan = get_2_pungs_fan_unordered(mid_tiles[1], mid_tiles[3])) != FAN_NONE) {
			++fan_table[fan];
		}
		if ((fan = get_2_pungs_fan_unordered(mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
			++fan_table[fan];
		}
	}

	// 3������㷬
	static void calculate_3_pungs(const tile_t(&mid_tiles)[3], fan_table_t &fan_table) {
		fan_t fan;

		// ����3����ӵķ��֣����ڸ� ��ͬ�� ����� ����Ԫ��ʱ�����ټ��������
		if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
			fan_table[fan] = 1;
			return;
		}

		// ������3����ӵķ���ʱ���������㷬��
		if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[1])) != FAN_NONE) {
			++fan_table[fan];
		}
		if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[2])) != FAN_NONE) {
			++fan_table[fan];
		}
		if ((fan = get_2_pungs_fan_unordered(mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
			++fan_table[fan];
		}
	}

	// 2������㷬
	static void calculate_2_pungs_unordered(const tile_t(&mid_tiles)[2], fan_table_t &fan_table) {
		fan_t fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[1]);
		if (fan != FAN_NONE) {
			++fan_table[fan];
		}
	}

	// ��������
	static bool is_nine_gates(const tile_t *tiles) {
		// �����Ƶ�������д��
		tile_table_t cnt_table;
		map_tiles(tiles, 13, &cnt_table);

		// 1��9����ö��2~8��һö
		return (cnt_table[0x11] == 3 && cnt_table[0x19] == 3 && std::all_of(cnt_table + 0x12, cnt_table + 0x19, [](int n) { return n == 1; }))
			|| (cnt_table[0x21] == 3 && cnt_table[0x29] == 3 && std::all_of(cnt_table + 0x22, cnt_table + 0x29, [](int n) { return n == 1; }))
			|| (cnt_table[0x31] == 3 && cnt_table[0x39] == 3 && std::all_of(cnt_table + 0x32, cnt_table + 0x39, [](int n) { return n == 1; }));
	}

	// һɫ˫����
	static bool is_pure_terminal_chows(const pack_t(&chow_packs)[4], pack_t pair_pack) {
		if (tile_get_rank(pack_get_tile(pair_pack)) != 5) {  // 5��ȸͷ
			return false;
		}

		int _123_cnt = 0, _789_cnt = 0;
		suit_t pair_suit = tile_get_suit(pack_get_tile(pair_pack));
		for (int i = 0; i < 4; ++i) {
			suit_t suit = tile_get_suit(pack_get_tile(chow_packs[i]));
			if (suit != pair_suit) {  // ��ɫ��ȸͷ��ͬ
				return false;
			}
			rank_t rank = tile_get_rank(pack_get_tile(chow_packs[i]));
			switch (rank) {
			case 2: ++_123_cnt; break;
			case 8: ++_789_cnt; break;
			default: return false;
			}
		}
		return (_123_cnt == 2 && _789_cnt == 2);  // 123��789��2��
	}

	// ��ɫ˫����
	static bool is_three_suited_terminal_chows(const pack_t(&chow_packs)[4], pack_t pair_pack) {
		if (tile_get_rank(pack_get_tile(pair_pack)) != 5) {  // 5��ȸͷ
			return false;
		}

		int _123_suit_table[4] = { 0 };
		int _789_suit_table[4] = { 0 };
		suit_t pair_suit = tile_get_suit(pack_get_tile(pair_pack));
		for (int i = 0; i < 4; ++i) {
			suit_t suit = tile_get_suit(pack_get_tile(chow_packs[i]));
			if (suit == pair_suit) {  // ��ɫ��ȸͷ����ͬ
				return false;
			}
			rank_t rank = tile_get_rank(pack_get_tile(chow_packs[i]));
			switch (rank) {
			case 2: ++_123_suit_table[suit]; break;
			case 8: ++_789_suit_table[suit]; break;
			default: return false;
			}
		}

		// ��ȸͷ��ɫ��ͬ����ɫ123��789��һ��
		switch (pair_suit) {
		case 1: return (_123_suit_table[2] && _123_suit_table[3] && _789_suit_table[2] && _789_suit_table[3]);
		case 2: return (_123_suit_table[1] && _123_suit_table[3] && _789_suit_table[1] && _789_suit_table[3]);
		case 3: return (_123_suit_table[1] && _123_suit_table[2] && _789_suit_table[1] && _789_suit_table[2]);
		default: return false;
		}
	}

	// ���ݺ��Ʒ�ʽ���������漰���֣������ˡ�ȫ����
	static void adjust_by_self_drawn(const pack_t(&packs)[5], intptr_t fixed_cnt, bool self_drawn, fan_table_t &fan_table) {
		ptrdiff_t melded_cnt = std::count_if(&packs[0], &packs[fixed_cnt], &is_pack_melded);  // ����¶������

		switch (melded_cnt) {
		case 0:  // 0�����ģ�����Ϊ�����ˣ����Ϊ��ǰ��
			fan_table[self_drawn ? FULLY_CONCEALED_HAND : CONCEALED_HAND] = 1;
			break;
		case 4:
			// 4�����ģ������������������Ϊȫ����
			fan_table[self_drawn ? SELF_DRAWN : MELDED_HAND] = 1;
			break;
		default:
			if (self_drawn) {
				fan_table[SELF_DRAWN] = 1;
			}
			break;
		}
	}

	// ����ȸͷ���������漰���֣�ƽ�͡�С��Ԫ��С��ϲ
	static void adjust_by_pair_tile(tile_t pair_tile, intptr_t chow_cnt, fan_table_t &fan_table) {
		if (chow_cnt == 4) {  // 4�鶼��˳��
			if (is_numbered_suit_quick(pair_tile)) {  // ����ȸͷ
				fan_table[ALL_CHOWS] = 1;  // ƽ��
			}
			return;
		}

		// ��˫���̵Ļ����ϣ����ȸͷ�Ǽ��ƣ�������ΪС��Ԫ
		if (fan_table[TWO_DRAGONS_PUNGS]) {
			if (is_dragons(pair_tile)) {
				fan_table[LITTLE_THREE_DRAGONS] = 1;
				fan_table[TWO_DRAGONS_PUNGS] = 0;
			}
			return;
		}
		// ������̵Ļ����ϣ����ȸͷ�Ƿ��ƣ�������ΪС��ϲ
		if (fan_table[BIG_THREE_WINDS]) {
			if (is_winds(pair_tile)) {
				fan_table[LITTLE_FOUR_WINDS] = 1;
				fan_table[BIG_THREE_WINDS] = 0;
			}
			return;
		}
	}

	// ���ݻ�ɫ���������漰���֣����֡�ȱһ�š���һɫ����һɫ��������
	static void adjust_by_suits(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {
		// ���������Щ��ɫ����bit����
		uint8_t suit_flag = 0;
		for (intptr_t i = 0; i < tile_cnt; ++i) {
			suit_flag |= (1 << tile_get_suit(tiles[i]));
		}

		// 1111 0001
		if (!(suit_flag & 0xF1U)) {
			fan_table[NO_HONORS] = 1;  // ����
		}

		// 1110 0011
		if (!(suit_flag & 0xE3U)) {
			++fan_table[ONE_VOIDED_SUIT];  // ȱһ�ţ���
		}
		// 1110 0101
		if (!(suit_flag & 0xE5U)) {
			++fan_table[ONE_VOIDED_SUIT];  // ȱһ�ţ�����
		}
		// 1110 1001
		if (!(suit_flag & 0xE9U)) {
			++fan_table[ONE_VOIDED_SUIT];  // ȱһ�ţ�����
		}

		// ��ȱ2��ʱ���������ֺ����֣�����Ϊ��һɫ����һɫ
		if (fan_table[ONE_VOIDED_SUIT] == 2) {
			fan_table[ONE_VOIDED_SUIT] = 0;
			fan_table[suit_flag & 0xF1U ? HALF_FLUSH : FULL_FLUSH] = 1;
		}

		// 0001 1110
		if (suit_flag == 0x1EU) {  // �������ƺ����ƶ���
			if (std::any_of(tiles, tiles + tile_cnt, &is_winds)
				&& std::any_of(tiles, tiles + tile_cnt, &is_dragons)) {
				fan_table[ALL_TYPES] = 1;  // ������
			}
		}
	}

	// �������Ƶķ�Χ���������漰���֣������塢С���塢ȫ��ȫ�С�ȫС
	static void adjust_by_rank_range(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {
#ifdef STRICT_98_RULE
		if (fan_table[SEVEN_PAIRS]) {
			return;  // �ϸ�98������߶Բ�֧�ֵ�����Щ
		}
#endif

		// ���������Щ��
		uint16_t rank_flag = 0;
		for (intptr_t i = 0; i < tile_cnt; ++i) {
			if (!is_numbered_suit_quick(tiles[i])) {
				return;
			}
			rank_flag |= (1 << tile_get_rank(tiles[i]));
		}

		// 1111 1111 1110 0001
		// ����Ƿ�ֻ����1234
		if (!(rank_flag & 0xFFE1)) {
			// ����4ΪС���壬����ΪȫС
			fan_table[rank_flag & 0x0010 ? LOWER_FOUR : LOWER_TILES] = 1;
			return;
		}
		// 1111 1100 0011 1111
		// ����Ƿ�ֻ����6789
		if (!(rank_flag & 0xFC3F)) {
			// ����6Ϊ�����壬����Ϊȫ��
			fan_table[rank_flag & 0x0040 ? UPPER_FOUR : UPPER_TILES] = 1;
			return;
		}
		// 1111 1111 1000 1111
		// ����Ƿ�ֻ����456
		if (!(rank_flag & 0xFF8F)) {
			// ȫ��
			fan_table[MIDDLE_TILES] = 1;
		}
	}

	// ���������������������漰���֣�ȫ���ۡ�ȫ���塢ȫ˫��
	static void adjust_by_packs_traits(const pack_t(&packs)[5], fan_table_t &fan_table) {
		// ͳ�ư�������19�����ơ�5��˫���Ƶ�����
		int terminal_pack = 0;
		int honor_pack = 0;
		int _5_pack = 0;
		int even_pack = 0;
		for (int i = 0; i < 5; ++i) {
			tile_t tile = pack_get_tile(packs[i]);
			if (is_numbered_suit_quick(tile)) {  // ����
				rank_t rank = tile_get_rank(tile);
				if (pack_get_type(packs[i]) == PACK_TYPE_CHOW) {  // ˳��
					switch (rank) {
					case 2: case 8: ++terminal_pack; break;  // ����19
					case 4: case 5: case 6: ++_5_pack; break;  // ����
					default: break;
					}
				}
				else {  // ���ӻ�ȸͷ
					switch (rank) {
					case 1: case 9: ++terminal_pack; break;  // ����19
					case 5: ++_5_pack; break;  // ����
					case 2: case 4: case 6: case 8: ++even_pack; break;  // ˫��
					default: break;
					}
				}
			}
			else {
				++honor_pack;  // ����
			}
		}

		// 5���ƶ���������19�����ƣ�����ʱ��Ϊȫ����
		if (terminal_pack + honor_pack == 5) {
			fan_table[OUTSIDE_HAND] = 1;
			return;
		}
		// ȫ����
		if (_5_pack == 5) {
			fan_table[ALL_FIVE] = 1;
			return;
		}
		// ȫ˫��
		if (even_pack == 5) {
			fan_table[ALL_EVEN_PUNGS] = 1;
		}
	}

	// ���������Ե��������漰���֣����ۡ��Ʋ�������һɫ����һɫ�����۾š����۾�
	static void adjust_by_tiles_traits(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {
		// ����
		if (std::none_of(tiles, tiles + tile_cnt, &is_terminal_or_honor)) {
			fan_table[ALL_SIMPLES] = 1;
		}

		// �Ʋ���
		if (std::all_of(tiles, tiles + tile_cnt, &is_reversible)) {
			fan_table[REVERSIBLE_TILES] = 1;
		}

#ifdef STRICT_98_RULE
		if (fan_table[SEVEN_PAIRS]) {
			return;  // �ϸ�98������߶Բ�֧����һɫ����һɫ�����۾š����۾�
		}
#endif

		// ��һɫ
		if (std::all_of(tiles, tiles + tile_cnt, &is_green)) {
			fan_table[ALL_GREEN] = 1;
		}

		// ��������˾�û��Ҫ�����һɫ�����۾š����۾���
		if (fan_table[ALL_SIMPLES] != 0) {
			return;
		}

		// ��һɫ
		if (std::all_of(tiles, tiles + tile_cnt, &is_honor)) {
			fan_table[ALL_HONORS] = 1;
			return;
		}
		// ���۾�
		if (std::all_of(tiles, tiles + tile_cnt, &is_terminal)) {
			fan_table[ALL_TERMINALS] = 1;
			return;
		}
		// ���۾�
		if (std::all_of(tiles, tiles + tile_cnt, &is_terminal_or_honor)) {
			fan_table[ALL_TERMINALS_AND_HONORS] = 1;
		}
	}

	// �Ĺ�һ����
	static void adjust_by_tiles_hog(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {
		intptr_t kong_cnt = tile_cnt - 14;  // ��׼����14�ţ�������ž�˵���м�����
		tile_table_t cnt_table;
		map_tiles(tiles, tile_cnt, &cnt_table);
		// �ж������Ѿ���ȥ4�ŵ��Ƽ�ȥ�ܵ���������Ϊ�Ĺ�һ������
		intptr_t _4_cnt = std::count(std::begin(cnt_table), std::end(cnt_table), 4);
		fan_table[TILE_HOG] = static_cast<uint8_t>(_4_cnt - kong_cnt);
	}

	// �������Ʒ�ʽ���������漰���֣����š�Ƕ�š�������
	static void adjust_by_waiting_form(const pack_t *concealed_packs, intptr_t pack_cnt, const tile_t *standing_tiles, intptr_t standing_cnt,
		tile_t win_tile, fan_table_t &fan_table) {
		// ȫ���˺��ĸܲ��Ƶ�������Ҳ�������б��š�Ƕ��
		if (fan_table[MELDED_HAND] || fan_table[FOUR_KONGS]) {
			return;
		}

		useful_table_t waiting_table;  // ���Ʊ�Ǳ�
		if (!is_basic_form_wait(standing_tiles, standing_cnt, &waiting_table)) {
			return;
		}

		if (pack_cnt == 5) {  // ����״̬
							  // �ж��Ƿ�Ϊ�߶�����
			useful_table_t temp_table;
			if (is_seven_pairs_wait(standing_tiles, standing_cnt, &temp_table)) {
				// �ϲ����Ʊ�Ǳ�
				std::transform(std::begin(temp_table), std::end(temp_table), std::begin(waiting_table),
					std::begin(waiting_table), [](bool w, bool t) { return w || t; });
			}
		}

		// ͳ����������������������1�ţ����Ʊ��š�Ƕ�š�������
		if (1 != std::count(std::begin(waiting_table), std::end(waiting_table), true)) {
			return;
		}

		// ��1�ŵ�������������Ŵ���ʲôλ��
		// ����0x01 Ƕ��0x02 ������0x04
		uint8_t pos_flag = 0;

		for (intptr_t i = 0; i < pack_cnt; ++i) {
			switch (pack_get_type(concealed_packs[i])) {
			case PACK_TYPE_CHOW: {
				tile_t mid_tile = pack_get_tile(concealed_packs[i]);
				if (mid_tile == win_tile) {
					pos_flag |= 0x02U;  // Ƕ��
				}
				else if (mid_tile + 1 == win_tile || mid_tile - 1 == win_tile) {
					pos_flag |= 0x01U;  // ����
				}
				break;
			}
			case PACK_TYPE_PAIR: {
				tile_t mid_tile = pack_get_tile(concealed_packs[i]);
				if (mid_tile == win_tile) {
					pos_flag |= 0x04U;  // ������
				}
				break;
			}
			default:
				break;
			}
		}

		// �����ֿ��ܴ���ʱ��ֻ�ܼ�����һ��
		if (pos_flag & 0x01U) {
			fan_table[EDGE_WAIT] = 1;
		}
		else if (pos_flag & 0x02U) {
			fan_table[CLOSED_WAIT] = 1;
		}
		else if (pos_flag & 0x04U) {
			fan_table[SINGLE_WAIT] = 1;
		}
	}

	// ���ݷ���������漰���֣�Ȧ��̡��ŷ��
	static void adjust_by_winds(tile_t tile, wind_t prevalent_wind, wind_t seat_wind, fan_table_t &fan_table) {
		rank_t delta = tile - TILE_E;
		if (delta == static_cast<int>(prevalent_wind) - static_cast<int>(wind_t::EAST)) {
			fan_table[PREVALENT_WIND] = 1;
		}
		if (delta == static_cast<int>(seat_wind) - static_cast<int>(wind_t::EAST)) {
			fan_table[SEAT_WIND] = 1;
		}
	}

	// ͳһ����һЩ���Ƶ�
	static void adjust_fan_table(fan_table_t &fan_table, bool prevalent_eq_seat) {
		// ����ϲ��������̡������͡�Ȧ��̡��ŷ�̡��۾ſ�
		if (fan_table[BIG_FOUR_WINDS]) {
			fan_table[BIG_THREE_WINDS] = 0;
			fan_table[ALL_PUNGS] = 0;
			fan_table[PREVALENT_WIND] = 0;
			fan_table[SEAT_WIND] = 0;
			fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
		}
		// ����Ԫ����˫���̡����̣��ϸ�98���򲻼�ȱһ�ţ�
		if (fan_table[BIG_THREE_DRAGONS]) {
			fan_table[TWO_DRAGONS_PUNGS] = 0;
			fan_table[DRAGON_PUNG] = 0;
#ifdef STRICT_98_RULE
			fan_table[ONE_VOIDED_SUIT] = 0;
#endif
		}
		// ��һɫ���ƻ�һɫ��ȱһ��
		if (fan_table[ALL_GREEN]) {
			fan_table[HALF_FLUSH] = 0;
			fan_table[ONE_VOIDED_SUIT] = 0;
		}
		// �������Ʋ�����һɫ����ǰ�塢ȱһ�š����֣�����1���۾ſ̣��Ѳ���������Ϊ����
		if (fan_table[NINE_GATES]) {
			fan_table[FULL_FLUSH] = 0;
			fan_table[CONCEALED_HAND] = 0;
			--fan_table[PUNG_OF_TERMINALS_OR_HONORS];
			fan_table[ONE_VOIDED_SUIT] = 0;
			fan_table[NO_HONORS] = 0;
			if (fan_table[FULLY_CONCEALED_HAND]) {
				fan_table[FULLY_CONCEALED_HAND] = 0;
				fan_table[SELF_DRAWN] = 1;
			}
		}
		// �ĸܲ��Ƶ�����
		if (fan_table[FOUR_KONGS]) {
			fan_table[SINGLE_WAIT] = 0;
		}
		// ���߶Բ����߶ԡ���һɫ����ǰ�塢ȱһ�š�����
		if (fan_table[SEVEN_SHIFTED_PAIRS]) {
			fan_table[SEVEN_PAIRS] = 0;
			fan_table[FULL_FLUSH] = 0;
			fan_table[CONCEALED_HAND] = 0;
			fan_table[ONE_VOIDED_SUIT] = 0;
			fan_table[NO_HONORS] = 0;
		}
		// ʮ���۲��������롢��ǰ�塢������
		if (fan_table[THIRTEEN_ORPHANS]) {
			fan_table[ALL_TYPES] = 0;
			fan_table[CONCEALED_HAND] = 0;
			fan_table[SINGLE_WAIT] = 0;
		}

		// ���۾Ų��ƻ��۾š���������ȫ���ۡ��۾ſ̡����֣��ϸ�98���򲻼�˫ͬ�̡�������ͬ�̣�
		if (fan_table[ALL_TERMINALS]) {
			fan_table[ALL_TERMINALS_AND_HONORS] = 0;
			fan_table[ALL_PUNGS] = 0;
			fan_table[OUTSIDE_HAND] = 0;
			fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
			fan_table[NO_HONORS] = 0;
			fan_table[DOUBLE_PUNG] = 0;  // ͨ�мƷ�����˫ͬ��
#ifdef STRICT_98_RULE
			fan_table[TRIPLE_PUNG] = 0;
			fan_table[DOUBLE_PUNG] = 0;
#endif
		}

		// С��ϲ���������
		if (fan_table[LITTLE_FOUR_WINDS]) {
			fan_table[BIG_THREE_WINDS] = 0;
			// С��ϲ�ĵ������������19�Ŀ��ӣ����ǻ��۾ţ�����Ǽ���������һɫ�������ֶ��ǲ����۾ſ̵�
			// �����˳�ӻ���2-8�Ŀ��ӣ��򲻴��ڶ�����۾ſ�
			// �������ｫ�۾ſ���Ϊ0
			fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
		}

		// С��Ԫ����˫���̡����̣��ϸ�98���򲻼�ȱһ�ţ�
		if (fan_table[LITTLE_THREE_DRAGONS]) {
			fan_table[TWO_DRAGONS_PUNGS] = 0;
			fan_table[DRAGON_PUNG] = 0;
#ifdef STRICT_98_RULE
			fan_table[ONE_VOIDED_SUIT] = 0;
#endif
		}

		// ��һɫ���ƻ��۾š���������ȫ���ۡ��۾ſ̡�ȱһ��
		if (fan_table[ALL_HONORS]) {
			fan_table[ALL_TERMINALS_AND_HONORS] = 0;
			fan_table[ALL_PUNGS] = 0;
			fan_table[OUTSIDE_HAND] = 0;
			fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
			fan_table[ONE_VOIDED_SUIT] = 0;
		}
		// �İ��̲��������͡���ǰ�壬�Ѳ���������Ϊ����
		if (fan_table[FOUR_CONCEALED_PUNGS]) {
			fan_table[ALL_PUNGS] = 0;
			fan_table[CONCEALED_HAND] = 0;
			if (fan_table[FULLY_CONCEALED_HAND]) {
				fan_table[FULLY_CONCEALED_HAND] = 0;
				fan_table[SELF_DRAWN] = 1;
			}
		}
		// һɫ˫���᲻���߶ԡ���һɫ��ƽ�͡�һ��ߡ����ٸ���ȱһ�š�����
		if (fan_table[PURE_TERMINAL_CHOWS]) {
			fan_table[SEVEN_PAIRS] = 0;
			fan_table[FULL_FLUSH] = 0;
			fan_table[ALL_CHOWS] = 0;
			fan_table[PURE_DOUBLE_CHOW] = 0;
			fan_table[TWO_TERMINAL_CHOWS] = 0;
			fan_table[ONE_VOIDED_SUIT] = 0;
			fan_table[NO_HONORS] = 0;
		}

		// һɫ��ͬ˳����һɫ��ͬ˳��һ��ߡ��Ĺ�һ���ϸ�98���򲻼�ȱһ�ţ�
		if (fan_table[QUADRUPLE_CHOW]) {
			fan_table[PURE_SHIFTED_PUNGS] = 0;
			fan_table[TILE_HOG] = 0;
			fan_table[PURE_DOUBLE_CHOW] = 0;
#ifdef STRICT_98_RULE
			fan_table[ONE_VOIDED_SUIT] = 0;
#endif
		}
		// һɫ�Ľڸ߲���һɫ���ڸߡ������ͣ��ϸ�98���򲻼�ȱһ�ţ�
		if (fan_table[FOUR_PURE_SHIFTED_PUNGS]) {
			fan_table[PURE_TRIPLE_CHOW] = 0;
			fan_table[ALL_PUNGS] = 0;
#ifdef STRICT_98_RULE
			fan_table[ONE_VOIDED_SUIT] = 0;
#endif
		}

		// һɫ�Ĳ��߲���һɫ�����ߡ����ٸ����������ϸ�98���򲻼�ȱһ�ţ�
		if (fan_table[FOUR_PURE_SHIFTED_CHOWS]) {
			fan_table[PURE_SHIFTED_CHOWS] = 0;
			fan_table[TWO_TERMINAL_CHOWS] = 0;
			fan_table[SHORT_STRAIGHT] = 0;
#ifdef STRICT_98_RULE
			fan_table[ONE_VOIDED_SUIT] = 0;
#endif
		}

		// ���۾Ų��������͡�ȫ���ۡ��۾ſ�
		if (fan_table[ALL_TERMINALS_AND_HONORS]) {
			fan_table[ALL_PUNGS] = 0;
			fan_table[OUTSIDE_HAND] = 0;
			fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
		}

		// �߶Բ�����ǰ�塢������
		if (fan_table[SEVEN_PAIRS]) {
			fan_table[CONCEALED_HAND] = 0;
			fan_table[SINGLE_WAIT] = 0;
		}
		// ���ǲ������������롢��ǰ��
		if (fan_table[GREATER_HONORS_AND_KNITTED_TILES]) {
			fan_table[ALL_TYPES] = 0;
			fan_table[CONCEALED_HAND] = 0;
		}
		// ȫ˫�̲��������������ۡ�����
		if (fan_table[ALL_EVEN_PUNGS]) {
			fan_table[ALL_PUNGS] = 0;
			fan_table[ALL_SIMPLES] = 0;
			fan_table[NO_HONORS] = 0;
		}
		// ��һɫ����ȱһ�š�����
		if (fan_table[FULL_FLUSH]) {
			fan_table[ONE_VOIDED_SUIT] = 0;
			fan_table[NO_HONORS] = 0;
		}
		// һɫ��ͬ˳����һɫ���ڸߡ�һ���
		if (fan_table[PURE_TRIPLE_CHOW]) {
			fan_table[PURE_SHIFTED_PUNGS] = 0;
			fan_table[PURE_DOUBLE_CHOW] = 0;
		}
		// һɫ���ڸ߲���һɫ��ͬ˳
		if (fan_table[PURE_SHIFTED_PUNGS]) {
			fan_table[PURE_TRIPLE_CHOW] = 0;
		}
		// ȫ�󲻼ƴ����塢����
		if (fan_table[UPPER_TILES]) {
			fan_table[UPPER_FOUR] = 0;
			fan_table[NO_HONORS] = 0;
		}
		// ȫ�в��ƶ���
		if (fan_table[MIDDLE_TILES]) {
			fan_table[ALL_SIMPLES] = 0;
			fan_table[NO_HONORS] = 0;
		}
		// ȫС����С���塢����
		if (fan_table[LOWER_TILES]) {
			fan_table[LOWER_FOUR] = 0;
			fan_table[NO_HONORS] = 0;
		}

		// ��ɫ˫���᲻��ƽ�͡����֡�ϲ��ꡢ���ٸ�
		if (fan_table[THREE_SUITED_TERMINAL_CHOWS]) {
			fan_table[ALL_CHOWS] = 0;
			fan_table[NO_HONORS] = 0;
			fan_table[MIXED_DOUBLE_CHOW] = 0;
			fan_table[TWO_TERMINAL_CHOWS] = 0;
		}
		// ȫ���岻�ƶ��ۡ�����
		if (fan_table[ALL_FIVE]) {
			fan_table[ALL_SIMPLES] = 0;
			fan_table[NO_HONORS] = 0;
		}

		// ���ǲ������������롢��ǰ��
		if (fan_table[LESSER_HONORS_AND_KNITTED_TILES]) {
			fan_table[ALL_TYPES] = 0;
			fan_table[CONCEALED_HAND] = 0;
		}
		// �����岻������
		if (fan_table[UPPER_FOUR]) {
			fan_table[NO_HONORS] = 0;
		}
		// С���岻������
		if (fan_table[LOWER_FOUR]) {
			fan_table[NO_HONORS] = 0;
		}
		// ������ڲ����ټ��۾ſ̣��ϸ�98���򲻼�ȱһ�ţ�
		if (fan_table[BIG_THREE_WINDS]) {
			// ���������һɫ����۾ţ���Ҫ��ȥ3���۾ſ�
			if (!fan_table[ALL_HONORS] && !fan_table[ALL_TERMINALS_AND_HONORS]) {
				assert(fan_table[PUNG_OF_TERMINALS_OR_HONORS] >= 3);
				fan_table[PUNG_OF_TERMINALS_OR_HONORS] -= 3;
			}
#ifdef STRICT_98_RULE
			fan_table[ONE_VOIDED_SUIT] = 0;
#endif
		}

		// �Ʋ�������ȱһ��
		if (fan_table[REVERSIBLE_TILES]) {
			fan_table[ONE_VOIDED_SUIT] = 0;
		}
		// ���ֻش���������
		if (fan_table[LAST_TILE_DRAW]) {
			fan_table[SELF_DRAWN] = 0;
		}
		// ���Ͽ�����������
		if (fan_table[OUT_WITH_REPLACEMENT_TILE]) {
			fan_table[SELF_DRAWN] = 0;
		}
		// ���ܺͲ��ƺ;���
		if (fan_table[ROBBING_THE_KONG]) {
			fan_table[LAST_TILE] = 0;
		}
		// ˫���ܲ��ư���
		if (fan_table[TWO_CONCEALED_KONGS]) {
			fan_table[CONCEALED_KONG] = 0;
		}

		// ��һɫ����ȱһ��
		if (fan_table[HALF_FLUSH]) {
			fan_table[ONE_VOIDED_SUIT] = 0;
		}
		// ȫ���˲��Ƶ�����
		if (fan_table[MELDED_HAND]) {
			fan_table[SINGLE_WAIT] = 0;
		}
		// ˫���̲��Ƽ���
		if (fan_table[TWO_DRAGONS_PUNGS]) {
			fan_table[DRAGON_PUNG] = 0;
		}

		// �����˲�������
		if (fan_table[FULLY_CONCEALED_HAND]) {
			fan_table[SELF_DRAWN] = 0;
		}
		// ˫���ܲ�������
		if (fan_table[TWO_MELDED_KONGS]) {
			fan_table[MELDED_KONG] = 0;
		}

		// Ȧ����Լ������۾ſ�
		if (fan_table[PREVALENT_WIND]) {
			// �����������̡�С��ϲ����һɫ�����۾ţ���Ҫ��ȥ1���۾ſ�
			if (!fan_table[BIG_THREE_WINDS] && !fan_table[LITTLE_FOUR_WINDS]
				&& !fan_table[ALL_HONORS] && !fan_table[ALL_TERMINALS_AND_HONORS]) {
				assert(fan_table[PUNG_OF_TERMINALS_OR_HONORS] > 0);
				--fan_table[PUNG_OF_TERMINALS_OR_HONORS];
			}
		}
		// �ŷ���Լ������۾ſ�
		if (fan_table[SEAT_WIND]) {
			// ���Ȧ�����ŷ粻��ͬ�����Ҳ�������̡�С��ϲ����һɫ�����۾ţ���Ҫ��ȥ1���۾ſ�
			if (!prevalent_eq_seat && !fan_table[BIG_THREE_WINDS] && !fan_table[LITTLE_FOUR_WINDS]
				&& !fan_table[ALL_HONORS] && !fan_table[ALL_TERMINALS_AND_HONORS]) {
				assert(fan_table[PUNG_OF_TERMINALS_OR_HONORS] > 0);
				--fan_table[PUNG_OF_TERMINALS_OR_HONORS];
			}
		}
		// ƽ�Ͳ�������
		if (fan_table[ALL_CHOWS]) {
			fan_table[NO_HONORS] = 0;
		}
		// ���۲�������
		if (fan_table[ALL_SIMPLES]) {
			fan_table[NO_HONORS] = 0;
		}
	}

	// ���ݺ��Ʊ�ǵ��������漰���֣��;��š����ֻش����������¡�����
	static void adjust_by_win_flag(win_flag_t win_flag, fan_table_t &fan_table) {
		if (win_flag & WIN_FLAG_4TH_TILE) {
			fan_table[LAST_TILE] = 1;
		}
		if (win_flag & WIN_FLAG_WALL_LAST) {
			fan_table[win_flag & WIN_FLAG_SELF_DRAWN ? LAST_TILE_DRAW : LAST_TILE_CLAIM] = 1;
		}
		if (win_flag & WIN_FLAG_ABOUT_KONG) {
			fan_table[win_flag & WIN_FLAG_SELF_DRAWN ? OUT_WITH_REPLACEMENT_TILE : ROBBING_THE_KONG] = 1;
		}
		if (win_flag & WIN_FLAG_SELF_DRAWN) {
			fan_table[SELF_DRAWN] = 1;
		}
	}

	// ���������㷬
	static void calculate_basic_form_fan(const pack_t(&packs)[5], const calculate_param_t *calculate_param, fan_table_t &fan_table) {
		pack_t pair_pack = 0;
		pack_t chow_packs[4];
		pack_t pung_packs[4];
		intptr_t chow_cnt = 0;
		intptr_t pung_cnt = 0;
		for (int i = 0; i < 5; ++i) {
			switch (pack_get_type(packs[i])) {
			case PACK_TYPE_CHOW: chow_packs[chow_cnt++] = packs[i]; break;
			case PACK_TYPE_PUNG:
			case PACK_TYPE_KONG: pung_packs[pung_cnt++] = packs[i]; break;
			case PACK_TYPE_PAIR: pair_pack = packs[i]; break;
			default: assert(0); return;
			}
		}

		if (pair_pack == 0 || chow_cnt + pung_cnt != 4) {
			return;
		}

		tile_t win_tile = calculate_param->win_tile;
		win_flag_t win_flag = calculate_param->win_flag;

		// ���ݺ��Ʊ�ǵ��������漰���֣��;��š����ֻش����������¡�����
		adjust_by_win_flag(win_flag, fan_table);

		// ��͵����ţ�������ܽ���Ϊ˳���е�һ�ţ���ô�������Ϊ���ӣ�������������Ϊ����
		if ((win_flag & WIN_FLAG_SELF_DRAWN) == 0) {
			// ���Ʋ��ܽ���Ϊ˳���е�һ��
			if (std::none_of(chow_packs, chow_packs + chow_cnt, [win_tile](pack_t chow_pack) {
				tile_t tile = pack_get_tile(chow_pack);
				return !is_pack_melded(chow_pack)
					&& (tile - 1 == win_tile || tile == win_tile || tile + 1 == win_tile);
			})) {
				for (intptr_t i = 0; i < pung_cnt; ++i) {
					if (pack_get_tile(pung_packs[i]) == win_tile && !is_pack_melded(pung_packs[i])) {
						pung_packs[i] |= (1 << 12);  // ���Ϊ����¶
					}
				}
			}
		}

		if (pung_cnt > 0) { // �п���
			calculate_kongs(pung_packs, pung_cnt, fan_table);
		}

		switch (chow_cnt) {
		case 4: {  // 4��˳��
				   // �����ɫ/һɫ˫����
			if (is_three_suited_terminal_chows(chow_packs, pair_pack)) {
				fan_table[THREE_SUITED_TERMINAL_CHOWS] = 1;
				break;
			}
			if (is_pure_terminal_chows(chow_packs, pair_pack)) {
				fan_table[PURE_TERMINAL_CHOWS] = 1;
				break;
			}

			tile_t mid_tiles[4];
			mid_tiles[0] = pack_get_tile(chow_packs[0]);
			mid_tiles[1] = pack_get_tile(chow_packs[1]);
			mid_tiles[2] = pack_get_tile(chow_packs[2]);
			mid_tiles[3] = pack_get_tile(chow_packs[3]);
			std::sort(std::begin(mid_tiles), std::end(mid_tiles));

			calculate_4_chows(mid_tiles, fan_table);
			break;
		}
		case 3: {  // 3��˳��+1�����
			tile_t mid_tiles[3];
			mid_tiles[0] = pack_get_tile(chow_packs[0]);
			mid_tiles[1] = pack_get_tile(chow_packs[1]);
			mid_tiles[2] = pack_get_tile(chow_packs[2]);
			std::sort(std::begin(mid_tiles), std::end(mid_tiles));

			calculate_3_chows(mid_tiles, fan_table);
			break;
		}
		case 2: {  // 2��˳��+2�����
			tile_t mid_tiles_chow[2];
			mid_tiles_chow[0] = pack_get_tile(chow_packs[0]);
			mid_tiles_chow[1] = pack_get_tile(chow_packs[1]);

			tile_t mid_tiles_pung[2];
			mid_tiles_pung[0] = pack_get_tile(pung_packs[0]);
			mid_tiles_pung[1] = pack_get_tile(pung_packs[1]);

			calculate_2_chows_unordered(mid_tiles_chow, fan_table);
			calculate_2_pungs_unordered(mid_tiles_pung, fan_table);
			break;
		}
		case 1: {  // 1��˳��+3�����
			tile_t mid_tiles[3];
			mid_tiles[0] = pack_get_tile(pung_packs[0]);
			mid_tiles[1] = pack_get_tile(pung_packs[1]);
			mid_tiles[2] = pack_get_tile(pung_packs[2]);
			std::sort(std::begin(mid_tiles), std::end(mid_tiles));

			calculate_3_pungs(mid_tiles, fan_table);
			break;
		}
		case 0: {  // 4�����
			tile_t mid_tiles[4];
			mid_tiles[0] = pack_get_tile(pung_packs[0]);
			mid_tiles[1] = pack_get_tile(pung_packs[1]);
			mid_tiles[2] = pack_get_tile(pung_packs[2]);
			mid_tiles[3] = pack_get_tile(pung_packs[3]);
			std::sort(std::begin(mid_tiles), std::end(mid_tiles));

			calculate_4_pungs(mid_tiles, fan_table);
			break;
		}
		default:
			break;
		}

		intptr_t fixed_cnt = calculate_param->hand_tiles.pack_count;
		const tile_t *standing_tiles = calculate_param->hand_tiles.standing_tiles;
		intptr_t standing_cnt = calculate_param->hand_tiles.tile_count;
		wind_t prevalent_wind = calculate_param->prevalent_wind;
		wind_t seat_wind = calculate_param->seat_wind;

		// ��������
		if (standing_cnt == 13) {
			if (is_nine_gates(standing_tiles)) {
				fan_table[NINE_GATES] = 1;
			}
		}

		// ���ݺ��Ʒ�ʽ���������漰���֣������ˡ�ȫ����
		adjust_by_self_drawn(packs, fixed_cnt, (win_flag & WIN_FLAG_SELF_DRAWN) != 0, fan_table);
		// ����ȸͷ���������漰���֣�ƽ�͡�С��Ԫ��С��ϲ
		adjust_by_pair_tile(pack_get_tile(pair_pack), chow_cnt, fan_table);
		// ���������������������漰���֣�ȫ���ۡ�ȫ���塢ȫ˫��
		adjust_by_packs_traits(packs, fan_table);

		tile_t tiles[18];
		memcpy(tiles, standing_tiles, standing_cnt * sizeof(tile_t));
		intptr_t tile_cnt = packs_to_tiles(packs, fixed_cnt, &tiles[standing_cnt], 18 - standing_cnt);
		tile_cnt += standing_cnt;
		tiles[tile_cnt++] = win_tile;

		// ���ݻ�ɫ���������漰���֣����֡�ȱһ�š���һɫ����һɫ��������
		adjust_by_suits(tiles, tile_cnt, fan_table);
		// ���������Ե��������漰���֣����ۡ��Ʋ�������һɫ����һɫ�����۾š����۾�
		adjust_by_tiles_traits(tiles, tile_cnt, fan_table);
		// �������Ƶķ�Χ���������漰���֣������塢С���塢ȫ��ȫ�С�ȫС
		adjust_by_rank_range(tiles, tile_cnt, fan_table);
		// �Ĺ�һ����
		adjust_by_tiles_hog(tiles, tile_cnt, fan_table);
		// �������Ʒ�ʽ���������漰���֣����š�Ƕ�š�������
		adjust_by_waiting_form(packs + fixed_cnt, 5 - fixed_cnt, standing_tiles, standing_cnt, win_tile, fan_table);

		// ���ݷ���������漰���֣�Ȧ��̡��ŷ��
		for (intptr_t i = 0; i < pung_cnt; ++i) {
			adjust_by_winds(pack_get_tile(pung_packs[i]), prevalent_wind, seat_wind, fan_table);
		}

		// ͳһ����һЩ���Ƶ�
		adjust_fan_table(fan_table, prevalent_wind == seat_wind);

		// ���ʲô����û�У����Ϊ�޷���
		if (std::all_of(std::begin(fan_table), std::end(fan_table), [](uint8_t p) { return p == 0; })) {
			fan_table[CHICKEN_HAND] = 1;
		}
	}

	// �������+����+ȸͷ�������㷬
	static bool calculate_knitted_straight_fan(const calculate_param_t *calculate_param, fan_table_t &fan_table) {
		const hand_tiles_t *hand_tiles = &calculate_param->hand_tiles;
		tile_t win_tile = calculate_param->win_tile;
		win_flag_t win_flag = calculate_param->win_flag;
		wind_t prevalent_wind = calculate_param->prevalent_wind;
		wind_t seat_wind = calculate_param->seat_wind;

		intptr_t fixed_cnt = hand_tiles->pack_count;
		if (fixed_cnt > 1) {
			return false;
		}

		const pack_t *fixed_packs = hand_tiles->fixed_packs;
		intptr_t standing_cnt = hand_tiles->tile_count;

		// �����ƺͺ��Ƶ�������д��
		tile_table_t cnt_table;
		map_tiles(hand_tiles->standing_tiles, standing_cnt, &cnt_table);
		++cnt_table[win_tile];

		// ƥ�������
		const tile_t(*matched_seq)[9] = std::find_if(&standard_knitted_straight[0], &standard_knitted_straight[6],
			[&cnt_table](const tile_t(&seq)[9]) {
			return std::all_of(std::begin(seq), std::end(seq), [&cnt_table](tile_t t) { return cnt_table[t] > 0; });
		});

		if (matched_seq == &standard_knitted_straight[6]) {
			return false;
		}

		// �޳������
		std::for_each(std::begin(*matched_seq), std::end(*matched_seq), [&cnt_table](tile_t t) { --cnt_table[t]; });

		// ���������ͻ���
		division_result_t result;
		result.count = 0;
		division_t work_division;
		memset(&work_division, 0, sizeof(work_division));

		// �˴��߼�Ϊ���������9���Ƶ������Ѿ���ɵ�3�����ӣ��ճ�0 1 2�±괦��3��
		// �����4���Ǹ�¶�ģ���������±�3��
		// Ȼ�󰴻������ʹӴ�fixed_cnt + 3��ʼ�ݹ�
		// ���ֺ�Ľ�����±�3��Ϊ���������ӣ��±�4��Ϊȸͷ
		if (fixed_cnt == 1) {
			work_division.packs[3] = fixed_packs[0];
		}
		divide_recursively(cnt_table, fixed_cnt + 3, 0, &work_division, &result);
		if (result.count != 1) {
			return false;
		}

		const pack_t *packs = result.divisions[0].packs;  // packs��0 1 2�±궼��û�õ�

														  // ��Ƿ�
		fan_table[KNITTED_STRAIGHT] = 1;  // �����
		if (pack_get_type(packs[3]) == PACK_TYPE_CHOW) {  // ��4����˳��
			if (is_numbered_suit_quick(pack_get_tile(packs[4]))) {
				fan_table[ALL_CHOWS] = 1;  // ȸͷ������ʱ��Ϊƽ��
			}
		}
		else {
			calculate_kongs(&packs[3], 1, fan_table);

			// ���ݷ���������漰���֣�Ȧ��̡��ŷ��
			adjust_by_winds(pack_get_tile(packs[3]), prevalent_wind, seat_wind, fan_table);
		}

		adjust_by_win_flag(win_flag, fan_table);
		// ��ǰ�壨���ܲ�Ӱ�죩
		if (fixed_cnt == 0 || (pack_get_type(packs[3]) == PACK_TYPE_KONG && !is_pack_melded(packs[3]))) {
			if (win_flag & WIN_FLAG_SELF_DRAWN) {
				fan_table[FULLY_CONCEALED_HAND] = 1;
			}
			else {
				fan_table[CONCEALED_HAND] = 1;
			}
		}

		// ��ԭ��
		tile_t tiles[15];  // ���������Ϊ�ܣ��������Ϊ15��
		memcpy(tiles, matched_seq, sizeof(*matched_seq));  // ������Ĳ���
		intptr_t tile_cnt = packs_to_tiles(&packs[3], 2, tiles + 9, 6);  // һ������+һ��ȸͷ ���6����
		tile_cnt += 9;

		// ���ݻ�ɫ���������漰���֣����֡�ȱһ�š���һɫ����һɫ��������
		adjust_by_suits(tiles, tile_cnt, fan_table);
		// �����Լ��������Ͳ���Ҫ�����ˣ���������Ĵ��ھ��Բ����ܴ���ȫ���ۡ�ȫ���塢ȫ˫�̣����ۡ��Ʋ�������һɫ����һɫ�����۾š����۾�
		// �Ĺ�һ����
		adjust_by_tiles_hog(tiles, tile_cnt, fan_table);

		// ���������������Χ���ƣ����Ʊ��š�Ƕ�š�������
		if (std::none_of(std::begin(*matched_seq), std::end(*matched_seq), [win_tile](tile_t t) { return t == win_tile; })) {
			if (fixed_cnt == 0) {  // ��������п��ܴ��ڱ��š�Ƕ�š�������
								   // ����ȥ������Ĳ��ָֻ�����
				--cnt_table[win_tile];
				tile_t temp[4];
				intptr_t cnt = table_to_tiles(cnt_table, temp, 4);

				// �������Ʒ�ʽ���������漰���֣����š�Ƕ�š�������
				adjust_by_waiting_form(packs + 3, 2, temp, cnt, win_tile, fan_table);
			}
			else {
				// ������״̬������Ʋ����������Χ�ڣ���Ȼ�ǵ�����
				fan_table[SINGLE_WAIT] = 1;
			}
		}

		// ͳһ����һЩ���Ƶ�
		adjust_fan_table(fan_table, prevalent_wind == seat_wind);
		return true;
	}

	// ʮ����
	static forceinline bool is_thirteen_orphans(const tile_t(&tiles)[14]) {
		return std::all_of(std::begin(tiles), std::end(tiles), &is_terminal_or_honor)
			&& std::includes(std::begin(tiles), std::end(tiles),
				std::begin(standard_thirteen_orphans), std::end(standard_thirteen_orphans));
	}

	// ȫ����/���ǲ����㷬
	static bool calculate_honors_and_knitted_tiles(const tile_t(&standing_tiles)[14], fan_table_t &fan_table) {
		const tile_t *honor_begin = std::find_if(std::begin(standing_tiles), std::end(standing_tiles), &is_honor);
		int numbered_cnt = static_cast<int>(honor_begin - standing_tiles);
		// ������������9����С��7��Ȼ��������ȫ����
		if (numbered_cnt > 9 || numbered_cnt < 7) {
			return false;
		}

		// ƥ�������
		if (std::none_of(&standard_knitted_straight[0], &standard_knitted_straight[6],
			[&standing_tiles, honor_begin](const tile_t(&seq)[9]) {
			return std::includes(std::begin(seq), std::end(seq), std::begin(standing_tiles), honor_begin);
		})) {
			return false;
		}

		if (numbered_cnt == 7 && std::equal(std::begin(standard_thirteen_orphans) + 6, std::end(standard_thirteen_orphans), standing_tiles + 7)) {
			// ���������룬Ϊ���ǲ���
			fan_table[GREATER_HONORS_AND_KNITTED_TILES] = 1;
			return true;
		}
		else if (std::includes(std::begin(standard_thirteen_orphans) + 6, std::end(standard_thirteen_orphans), honor_begin, std::end(standing_tiles))) {
			// ȫ����
			fan_table[LESSER_HONORS_AND_KNITTED_TILES] = 1;
			if (numbered_cnt == 9) {  // ��9�����ƣ�Ϊ���������ȫ����
				fan_table[KNITTED_STRAIGHT] = 1;
			}
			return true;
		}

		return false;
	}

	// ��������㷬
	static bool calculate_special_form_fan(const tile_t(&standing_tiles)[14], win_flag_t win_flag, fan_table_t &fan_table) {
		// �߶�
		if (standing_tiles[0] == standing_tiles[1]
			&& standing_tiles[2] == standing_tiles[3]
			&& standing_tiles[4] == standing_tiles[5]
			&& standing_tiles[6] == standing_tiles[7]
			&& standing_tiles[8] == standing_tiles[9]
			&& standing_tiles[10] == standing_tiles[11]
			&& standing_tiles[12] == standing_tiles[13]) {

			if (is_numbered_suit_quick(standing_tiles[0])
				&& standing_tiles[0] + 1 == standing_tiles[2]
				&& standing_tiles[2] + 1 == standing_tiles[4]
				&& standing_tiles[4] + 1 == standing_tiles[6]
				&& standing_tiles[6] + 1 == standing_tiles[8]
				&& standing_tiles[8] + 1 == standing_tiles[10]
				&& standing_tiles[10] + 1 == standing_tiles[12]) {
				// ���߶�
				fan_table[SEVEN_SHIFTED_PAIRS] = 1;
				adjust_by_tiles_traits(standing_tiles, 14, fan_table);
			}
			else {
				// ��ͨ�߶�
				fan_table[SEVEN_PAIRS] = 1;

				// ���ݻ�ɫ���������漰���֣����֡�ȱһ�š���һɫ����һɫ��������
				adjust_by_suits(standing_tiles, 14, fan_table);
				// ���������Ե��������漰���֣����ۡ��Ʋ�������һɫ����һɫ�����۾š����۾�
				adjust_by_tiles_traits(standing_tiles, 14, fan_table);
				// �������Ƶķ�Χ���������漰���֣������塢С���塢ȫ��ȫ�С�ȫС
				adjust_by_rank_range(standing_tiles, 14, fan_table);
				// �Ĺ�һ����
				adjust_by_tiles_hog(standing_tiles, 14, fan_table);
			}
		}
		// ʮ����
		else if (is_thirteen_orphans(standing_tiles)) {
			fan_table[THIRTEEN_ORPHANS] = 1;
		}
		// ȫ����/���ǲ���
		else if (calculate_honors_and_knitted_tiles(standing_tiles, fan_table)) {
		}
		else {
			return false;
		}

		adjust_by_win_flag(win_flag, fan_table);
		// ���ݷ������û��Ҫ�ˣ���Щ������Ͷ�û�����ӣ�������Ȧ��̡��ŷ��
		// ͳһ����һЩ���Ƶ�
		adjust_fan_table(fan_table, false);
		return true;
	}

	// �ӷ�����㷬��
	static int get_fan_by_table(const fan_table_t &fan_table) {
		int fan = 0;
		for (int i = 1; i < FAN_TABLE_SIZE; ++i) {
			if (fan_table[i] == 0) {
				continue;
			}
			fan += fan_value_table[i] * fan_table[i];
#if 0  // Debug
			if (fan_table[i] == 1) {
				LOG("%s %hu\n", fan_name[i], fan_value_table[i]);
			}
			else {
				LOG("%s %hu*%hu\n", fan_name[i], fan_value_table[i], fan_table[i]);
			}
#endif
		}
		return fan;
	}

	// �ж������Ƿ��������
	bool is_standing_tiles_contains_win_tile(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t win_tile) {
		return std::any_of(standing_tiles, standing_tiles + standing_cnt,
			[win_tile](tile_t tile) { return tile == win_tile; });
	}

	// ͳ�ƺ����ڸ�¶�����г��ֵ�����
	size_t count_win_tile_in_fixed_packs(const pack_t *fixed_packs, intptr_t fixed_cnt, tile_t win_tile) {
		tile_table_t cnt_table = { 0 };
		for (intptr_t i = 0; i < fixed_cnt; ++i) {
			pack_t pack = fixed_packs[i];
			tile_t tile = pack_get_tile(pack);
			switch (pack_get_type(pack)) {
			case PACK_TYPE_CHOW: ++cnt_table[tile - 1]; ++cnt_table[tile]; ++cnt_table[tile + 1]; break;
			case PACK_TYPE_PUNG: cnt_table[tile] += 3; break;
			case PACK_TYPE_KONG: cnt_table[tile] += 4; break;
			default: break;
			}
		}
		return cnt_table[win_tile];
	}

	// �жϸ�¶�����Ƿ������
	bool is_fixed_packs_contains_kong(const pack_t *fixed_packs, intptr_t fixed_cnt) {
		return std::any_of(fixed_packs, fixed_packs + fixed_cnt,
			[](pack_t pack) { return pack_get_type(pack) == PACK_TYPE_KONG; });
	}

	// ����㷬�������Ƿ�Ϸ�
	int check_calculator_input(const hand_tiles_t *hand_tiles, tile_t win_tile) {
		// ���
		tile_table_t cnt_table;
		if (!map_hand_tiles(hand_tiles, &cnt_table)) {
			return ERROR_WRONG_TILES_COUNT;
		}
		if (win_tile != 0) {
			++cnt_table[win_tile];
		}

		// ���ĳ���Ƴ���4
		if (std::any_of(std::begin(cnt_table), std::end(cnt_table), [](int cnt) { return cnt > 4; })) {
			return ERROR_TILE_COUNT_GREATER_THAN_4;
		}

		return 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// �㷬
	//
	int calculate_fan(const calculate_param_t *calculate_param, fan_table_t *fan_table) {
		const hand_tiles_t *hand_tiles = &calculate_param->hand_tiles;
		tile_t win_tile = calculate_param->win_tile;
		win_flag_t win_flag = calculate_param->win_flag;

		if (int ret = check_calculator_input(hand_tiles, win_tile)) {
			return ret;
		}

		intptr_t fixed_cnt = hand_tiles->pack_count;
		intptr_t standing_cnt = hand_tiles->tile_count;

		// У�����Ʊ��
		// ������ư������ƣ����Ȼ���Ǻ;���
		const bool standing_tiles_contains_win_tile = is_standing_tiles_contains_win_tile(hand_tiles->standing_tiles, standing_cnt, win_tile);
		if (standing_tiles_contains_win_tile) {
			win_flag &= ~WIN_FLAG_4TH_TILE;
		}

		// ��������ڸ�¶�г���3�ţ����ȻΪ�;���
		const size_t win_tile_in_fixed_packs = count_win_tile_in_fixed_packs(hand_tiles->fixed_packs, fixed_cnt, win_tile);
		if (3 == win_tile_in_fixed_packs) {
			win_flag |= WIN_FLAG_4TH_TILE;
		}

		// ���Ӹܱ��
		if (win_flag & WIN_FLAG_ABOUT_KONG) {
			if (win_flag & WIN_FLAG_SELF_DRAWN) {  // ����
												   // �������û�иܣ����Ȼ���Ǹ��Ͽ���
				if (!is_fixed_packs_contains_kong(hand_tiles->fixed_packs, fixed_cnt)) {
					win_flag &= ~WIN_FLAG_ABOUT_KONG;
				}
			}
			else {  // ���
					// ������������Ʒ�Χ�ڳ��ֹ������Ȼ�������ܺ�
				if (win_tile_in_fixed_packs > 0 || standing_tiles_contains_win_tile) {
					win_flag &= ~WIN_FLAG_ABOUT_KONG;
				}
			}
		}

		// �ϲ���������ƣ����������Ϊ14��
		tile_t standing_tiles[14];
		memcpy(standing_tiles, hand_tiles->standing_tiles, standing_cnt * sizeof(tile_t));
		standing_tiles[standing_cnt] = win_tile;
		std::sort(standing_tiles, standing_tiles + standing_cnt + 1);

		// ��󷬱��
		int max_fan = 0;
		const fan_table_t *selected_fan_table = nullptr;

		// ������͵ķ�
		fan_table_t special_fan_table = { 0 };

		// ���жϸ����������
		if (fixed_cnt == 0) {  // ����״̬���п����ǻ������������
			if (calculate_knitted_straight_fan(calculate_param, special_fan_table)) {
				max_fan = get_fan_by_table(special_fan_table);
				selected_fan_table = &special_fan_table;
				LOG("fan = %d\n\n", max_fan);
			}
			else if (calculate_special_form_fan(standing_tiles, win_flag, special_fan_table)) {
				max_fan = get_fan_by_table(special_fan_table);
				selected_fan_table = &special_fan_table;
				LOG("fan = %d\n\n", max_fan);
			}
		}
		else if (fixed_cnt == 1) {  // 1��¶״̬���п����ǻ������������
			if (calculate_knitted_straight_fan(calculate_param, special_fan_table)) {
				max_fan = get_fan_by_table(special_fan_table);
				selected_fan_table = &special_fan_table;
				LOG("fan = %d\n\n", max_fan);
			}
		}

		// �޷�����������ͻ���Ϊ�߶�
		// �߶�ҲҪ���������ͻ��֣���Ϊ��������£��������͵ķ��ᳬ���߶Եķ�
		if (selected_fan_table == nullptr || special_fan_table[SEVEN_PAIRS] == 1) {
			// ����
			division_result_t result;
			if (divide_win_hand(standing_tiles, hand_tiles->fixed_packs, fixed_cnt, &result)) {
				fan_table_t fan_tables[MAX_DIVISION_CNT] = { { 0 } };

				// �������ֻ��ַ�ʽ���ֱ��㷬���ҳ����ķ��Ļ��ַ�ʽ
				for (intptr_t i = 0; i < result.count; ++i) {
#if 0  // Debug
					char str[64];
					packs_to_string(result.divisions[i].packs, 5, str, sizeof(str));
					puts(str);
#endif
					calculate_basic_form_fan(result.divisions[i].packs, calculate_param, fan_tables[i]);
					int current_fan = get_fan_by_table(fan_tables[i]);
					if (current_fan > max_fan) {
						max_fan = current_fan;
						selected_fan_table = &fan_tables[i];
					}
					LOG("fan = %d\n\n", current_fan);
				}
			}
		}

		if (selected_fan_table == nullptr) {
			return ERROR_NOT_WIN;
		}

		// �ӻ���
		max_fan += calculate_param->flower_count;

		if (fan_table != nullptr) {
			memcpy(*fan_table, *selected_fan_table, sizeof(*fan_table));
			(*fan_table)[FLOWER_TILES] = calculate_param->flower_count;
		}

		return max_fan;
	}

}




using namespace mahjong;


using namespace std;

static unordered_map<string, mahjong::tile_t> str2tile;

vector<pair<int, string> > MahjongFanCalculator(
	vector<pair<string, pair<string, int> > > pack,
	vector<string> hand,
	string winTile,
	int flowerCount,
	bool isZIMO,
	bool isJUEZHANG,
	bool isGANG,
	bool isLAST,
	int menFeng,
	int quanFeng)
{
	vector<pair<int, string>> ans;
	mahjong::calculate_param_t calculate_param;
	mahjong::fan_table_t fan_table;
	memset(&calculate_param, 0, sizeof(mahjong::calculate_param_t));
	memset(&fan_table, 0, sizeof(mahjong::fan_table_t));
	calculate_param.hand_tiles.tile_count = hand.size();
	for (unsigned int i = 0; i < hand.size(); i++) {
		if (str2tile.find(hand[i]) == str2tile.end()) {
			throw string("ERROE_WRONG_TILE_CODE");
		}
		calculate_param.hand_tiles.standing_tiles[i] = str2tile[hand[i]];
	}
	calculate_param.hand_tiles.pack_count = pack.size();
	for (unsigned int i = 0; i < pack.size(); i++) {
		pair<string, pair<string, int>> &sPack = pack[i];
		mahjong::pack_t &dPack = calculate_param.hand_tiles.fixed_packs[i];
		if (sPack.first == "PENG") {
			dPack = mahjong::make_pack(sPack.second.second, PACK_TYPE_PUNG, str2tile[sPack.second.first]);
		}
		else if (sPack.first == "GANG") {
			dPack = mahjong::make_pack(sPack.second.second, PACK_TYPE_KONG, str2tile[sPack.second.first]);
		}
		else if (sPack.first == "CHI") {
			dPack = mahjong::make_pack(sPack.second.second, PACK_TYPE_CHOW, str2tile[sPack.second.first]);
		}
		else {
			throw string("ERROE_WRONG_PACK_CODE");
		}
	}
	calculate_param.win_tile = str2tile[winTile];
	calculate_param.flower_count = flowerCount;
	if (isZIMO) {
		calculate_param.win_flag |= WIN_FLAG_SELF_DRAWN;
	}
	if (isLAST) {
		calculate_param.win_flag |= WIN_FLAG_WALL_LAST;
	}
	if (isJUEZHANG) {
		calculate_param.win_flag |= WIN_FLAG_4TH_TILE;
	}
	if (isGANG) {
		calculate_param.win_flag |= WIN_FLAG_ABOUT_KONG;
	}
	calculate_param.prevalent_wind = (mahjong::wind_t)quanFeng;
	calculate_param.seat_wind = (mahjong::wind_t)menFeng;
	int re = mahjong::calculate_fan(&calculate_param, &fan_table);
	if (re == -1) {
		throw string("ERROR_WRONG_TILES_COUNT");
	}
	else if (re == -2) {
		throw string("ERROR_TILE_COUNT_GREATER_THAN_4");
	}
	else if (re == -3) {
		throw string("ERROR_NOT_WIN");
	}
	for (int i = 0; i < mahjong::FAN_TABLE_SIZE; i++) {
		if (fan_table[i] > 0) {
			ans.push_back(make_pair(fan_table[i] * mahjong::fan_value_table[i], mahjong::fan_name[i]));
		}
	}
	return ans;
}

void MahjongInit()
{
	for (int i = 1; i <= 9; i++) {
		str2tile["W" + to_string(i)] = mahjong::make_tile(TILE_SUIT_CHARACTERS, i);
		str2tile["B" + to_string(i)] = mahjong::make_tile(TILE_SUIT_DOTS, i);
		str2tile["T" + to_string(i)] = mahjong::make_tile(TILE_SUIT_BAMBOO, i);
	}
	for (int i = 1; i <= 4; i++) {
		str2tile["F" + to_string((i))] = mahjong::make_tile(TILE_SUIT_HONORS, i);
	}
	for (int i = 1; i <= 3; i++) {
		str2tile["J" + to_string((i))] = mahjong::make_tile(TILE_SUIT_HONORS, i + 4);
	}
}


#define TIMES 10000
#define CP 50

tile_t paichi[4 * 34];
tile_t ceshi[4 * 34];
tile_table_t all;//��ǰ�ƾ����Ѿ����ֳ����ƣ����Լ���ʣ�µ��Ƶ����������ǲ������Լ����ƣ�������
tile_table_t hand;//��ǰ����
useful_table_t wait, test;
hand_tiles_t myHand, temp;
int iflis;//��¼�Ƿ��Ѿ�ѡ��һ���ƴ��
int myID, UpPlayer, DownPlayer, CrossPlayer, lastPlayer;//��¼�ҵ�ID���ϼ�ID���¼�ID���Լ�ID����һ�����Ƶ����
bool ifUpPlayer;//��¼�Ƿ�Ϊ�ϼҳ��ƣ������ж��ܲ��ܳ�
int currentQuan;//��¼��ǰ�ķ�Ȧ
string lastcard;//��¼��һ����
string lastact;//��¼��һ�������������ж�����֮���
string drawcard;//��¼������������
int S;
DWORD TIME;
tile_t wind, wind_s;
tile_table_t my;
int value[72];
string action[5];//��¼�����ܡ��ԵĲ������ַ���
string	action_tile[5];//��¼��Ӧ�����Ĺؼ���
int action_player[5];//��¼��Ӧ��������Դ
int action_cnt = 0;
int flowerCnt = 0;//������
bool flowerOnGang = false;
int leftTile = 144 - 13 * 4;//��¼�ƾ��ϻ�ʣ��������
string int2tile(tile_t k);

/*
*һ������Ԥ����ֵ���
*���¼ң���ò����¼ҳ���
*	��¼�¼ҽ�5�ֳ���ʲô�ƣ����Խ��и��磬��ֹ����ƣ�ͬʱ�ʵ����������ܳԵ��Ƶĸ��ʴ�С
*
*���ϼң��ж��ϼҲ�Ҫʲô�ƣ������ܵ�������Ҫ��������ȥ�գ��и���ĳ�������
*/
tile_table_t enemyPlayTiles[4];//��¼ÿ���˴���Щʲô��
float tileScore[75];//��ÿ���ƴ��
const int EndGame = 24;
const int MiddleGame = 36;
const int FrontGame = 52;

//��ȫ�ƹ���
void safeTile() {

	//���ڶ��������з��ף�ֻҪ�Ѿ��������������ϣ���û��Σ��ϵ���������˲���������
	//�����ǰ1/3�֣���һ����-4��Σ�շ֣���������-2��Σ�շ֣����Ϊ�о֣���һ����-12��Σ�գ���������-8��Σ�շ֣�����ں��̣���һ����-18��Σ�շ֣�����-15��Σ�շ�
	for (int i = 65; i < 72; ++i) {
		int t = all[i] - hand[i];
		if (t >= 2) tileScore[i] = 0;
		if (t == 1) {
			if (leftTile >= MiddleGame)
				tileScore[i] -= 1;
			else if (leftTile >= EndGame)
				tileScore[i] -= 4;
			else tileScore[i] -= 7;
		}
		else {
			if (leftTile >= MiddleGame)
				tileScore[i] -= 2;
			else if (leftTile >= EndGame)
				tileScore[i] -= 6;
			//else tileScore[i] -= 9;
		}
	}

	//�������ƣ�����ȫ�����ơ����Ƽ��ʵĹ���
	//�����Ѿ������������ϵ��ƣ�ͬ���ǲ��������ƵĿ����Ե�
	//�����߼з��򣺶���POXOP���ƣ����O���ֵĶ࣬��X���ֵ��٣���X���Ƶļ����ر�����P����Ҳ�ܶ࣬��ô���Ƶļ���Ҳ����Ӧ������
	//���ڱ��ţ�XOP�����X�����٣����O���Ķ࣬��ôX���ļ����ر�����P����Ҳ��Խ϶࣬X���Ƶļ���Ҳ��Խϴ�
	for (int k = 17; k < 50; k += 16) {
		//���жϱ���1��9
		int t1, t2, t3, t4, t5;
		//�ж�1
		t1 = all[k] - hand[k];
		//���������1��
		if (t1 == 1) {
			t2 = all[k + 1] - hand[k + 1];
			t3 = all[k + 2] - hand[k + 2];
			int a[2] = { 0 };
			switch (t2) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 1;
				else if (leftTile >= EndGame) a[0] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 3;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 6;
				else if (leftTile >= EndGame) a[0] -= 8;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 10;
				else if (leftTile >= EndGame) a[0] -= 13;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 12;
				else if (leftTile >= EndGame) a[0] -= 15;
				break;
			default:break;
			}
			switch (t3) {
			case 0:
				if (leftTile >= MiddleGame) a[1] -= 1;
				else if (leftTile >= EndGame) a[1] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[1] -= 2;
				else if (leftTile >= EndGame) a[1] -= 3;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[1] -= 3;
				else if (leftTile >= EndGame) a[1] -= 4;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[1] -= 5;
				else if (leftTile >= EndGame) a[1] -= 6;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[1] -= 6;
				else if (leftTile >= EndGame) a[1] -= 7;
				break;
			default:break;
			}
			for (int i = 0; i < 2; ++i)
				tileScore[k] += a[i];
		}
		//���1�Ŷ�û�г���
		else if (t1 == 0) {
			t2 = all[k + 1] - hand[k + 1];
			t3 = all[k + 2] - hand[k + 2];
			int a[2] = { 0 };
			switch (t2) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 3;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 5;
				else if (leftTile >= EndGame) a[0] -= 6;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 7;
				else if (leftTile >= EndGame) a[0] -= 9;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 10;
				else if (leftTile >= EndGame) a[0] -= 12;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 13;
				else if (leftTile >= EndGame) a[0] -= 16;
				break;
			default:break;
			}
			switch (t3) {
			case 0:
				if (leftTile >= MiddleGame) a[1] -= 2;
				else if (leftTile >= EndGame) a[1] -= 3;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[1] -= 4;
				else if (leftTile >= EndGame) a[1] -= 5;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[1] -= 6;
				else if (leftTile >= EndGame) a[1] -= 8;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[1] -= 10;
				else if (leftTile >= EndGame) a[1] -= 12;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[1] -= 13;
				else if (leftTile >= EndGame) a[1] -= 14;
				break;
			default:break;
			}
			for (int i = 0; i < 2; ++i)
				tileScore[k] += a[i];
		}

		//�ж�9
		k += 8;
		t1 = all[k] - hand[k];
		//���������1��
		if (t1 == 1) {
			t2 = all[k - 1] - hand[k - 1];
			t3 = all[k - 2] - hand[k - 2];
			int a[2] = { 0 };
			switch (t2) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 1;
				else if (leftTile >= EndGame) a[0] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 3;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 6;
				else if (leftTile >= EndGame) a[0] -= 8;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 10;
				else if (leftTile >= EndGame) a[0] -= 13;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 12;
				else if (leftTile >= EndGame) a[0] -= 15;
				break;
			default:break;
			}
			switch (t3) {
			case 0:
				if (leftTile >= MiddleGame) a[1] -= 1;
				else if (leftTile >= EndGame) a[1] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[1] -= 2;
				else if (leftTile >= EndGame) a[1] -= 3;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[1] -= 3;
				else if (leftTile >= EndGame) a[1] -= 4;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[1] -= 5;
				else if (leftTile >= EndGame) a[1] -= 6;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[1] -= 6;
				else if (leftTile >= EndGame) a[1] -= 7;
				break;
			default:break;
			}
			for (int i = 0; i < 2; ++i)
				tileScore[k] += a[i];
		}
		//���1�Ŷ�û�г���
		else if (t1 == 0) {
			t2 = all[k - 1] - hand[k - 1];
			t3 = all[k - 2] - hand[k - 2];
			int a[2] = { 0 };
			switch (t2) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 3;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 5;
				else if (leftTile >= EndGame) a[0] -= 6;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 7;
				else if (leftTile >= EndGame) a[0] -= 9;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 10;
				else if (leftTile >= EndGame) a[0] -= 12;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 13;
				else if (leftTile >= EndGame) a[0] -= 16;
				break;
			default:break;
			}
			switch (t3) {
			case 0:
				if (leftTile >= MiddleGame) a[1] -= 2;
				else if (leftTile >= EndGame) a[1] -= 3;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[1] -= 4;
				else if (leftTile >= EndGame) a[1] -= 5;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[1] -= 6;
				else if (leftTile >= EndGame) a[1] -= 8;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[1] -= 10;
				else if (leftTile >= EndGame) a[1] -= 12;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[1] -= 13;
				else if (leftTile >= EndGame) a[1] -= 14;
				break;
			default:break;
			}
			for (int i = 0; i < 2; ++i)
				tileScore[k] += a[i];
		}
		k -= 8;

		//�ж�2��8
		//�ж�2
		++k;
		t1 = all[k] - hand[k];
		//���������1��
		if (t1 == 1) {
			t2 = all[k + 1] - hand[k + 1];
			t3 = all[k + 2] - hand[k + 2];
			t4 = all[k - 1] - hand[k - 1];
			int a[2] = { 0 };
			switch (t2) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 1;
				else if (leftTile >= EndGame) a[0] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 3;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 6;
				else if (leftTile >= EndGame) a[0] -= 8;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 10;
				else if (leftTile >= EndGame) a[0] -= 13;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 12;
				else if (leftTile >= EndGame) a[0] -= 15;
				break;
			default:break;
			}
			switch (t3) {
			case 0:
				if (leftTile >= MiddleGame) a[1] -= 1;
				else if (leftTile >= EndGame) a[1] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[1] -= 2;
				else if (leftTile >= EndGame) a[1] -= 3;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[1] -= 3;
				else if (leftTile >= EndGame) a[1] -= 4;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[1] -= 5;
				else if (leftTile >= EndGame) a[1] -= 6;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[1] -= 6;
				else if (leftTile >= EndGame) a[1] -= 7;
				break;
			default:break;
			}
			switch (t4) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 1;
				else if (leftTile >= EndGame) a[0] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 3;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 6;
				else if (leftTile >= EndGame) a[0] -= 8;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 10;
				else if (leftTile >= EndGame) a[0] -= 13;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 12;
				else if (leftTile >= EndGame) a[0] -= 15;
				break;
			default:break;
			}
			for (int i = 0; i < 2; ++i)
				tileScore[k] += a[i];
		}
		//���1�Ŷ�û�г���
		else if (t1 == 0) {
			t2 = all[k + 1] - hand[k + 1];
			t3 = all[k - 2] - hand[k - 2];
			t4 = all[k - 1] - hand[k - 1];
			int a[2] = { 0 };
			switch (t2) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 3;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 5;
				else if (leftTile >= EndGame) a[0] -= 6;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 7;
				else if (leftTile >= EndGame) a[0] -= 9;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 10;
				else if (leftTile >= EndGame) a[0] -= 12;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 13;
				else if (leftTile >= EndGame) a[0] -= 16;
				break;
			default:break;
			}
			switch (t3) {
			case 0:
				if (leftTile >= MiddleGame) a[1] -= 2;
				else if (leftTile >= EndGame) a[1] -= 3;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[1] -= 4;
				else if (leftTile >= EndGame) a[1] -= 5;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[1] -= 6;
				else if (leftTile >= EndGame) a[1] -= 8;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[1] -= 10;
				else if (leftTile >= EndGame) a[1] -= 12;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[1] -= 13;
				else if (leftTile >= EndGame) a[1] -= 14;
				break;
			default:break;
			}
			switch (t4) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 3;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 5;
				else if (leftTile >= EndGame) a[0] -= 6;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 7;
				else if (leftTile >= EndGame) a[0] -= 9;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 10;
				else if (leftTile >= EndGame) a[0] -= 12;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 13;
				else if (leftTile >= EndGame) a[0] -= 16;
				break;
			default:break;
			}
			for (int i = 0; i < 2; ++i)
				tileScore[k] += a[i];
		}
		--k;

		//�ж�8
		k += 7;
		t1 = all[k] - hand[k];
		//���������1��
		if (t1 == 1) {
			t2 = all[k + 1] - hand[k + 1];
			t3 = all[k + 2] - hand[k + 2];
			t4 = all[k - 1] - hand[k - 1];
			int a[2] = { 0 };
			switch (t2) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 1;
				else if (leftTile >= EndGame) a[0] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 2;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 6;
				else if (leftTile >= EndGame) a[0] -= 8;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 11;
				else if (leftTile >= EndGame) a[0] -= 15;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 14;
				else if (leftTile >= EndGame) a[0] -= 19;
				break;
			default:break;
			}
			switch (t4) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 1;
				else if (leftTile >= EndGame) a[0] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 2;
				else if (leftTile >= EndGame) a[0] -= 4;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 6;
				else if (leftTile >= EndGame) a[0] -= 8;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 11;
				else if (leftTile >= EndGame) a[0] -= 15;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 14;
				else if (leftTile >= EndGame) a[0] -= 19;
				break;
			default:break;
			}
			switch (t3) {
			case 0:
				if (leftTile >= MiddleGame) a[1] -= 1;
				else if (leftTile >= EndGame) a[1] -= 2;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[1] -= 2;
				else if (leftTile >= EndGame) a[1] -= 3;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[1] -= 4;
				else if (leftTile >= EndGame) a[1] -= 5;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[1] -= 6;
				else if (leftTile >= EndGame) a[1] -= 7;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[1] -= 8;
				else if (leftTile >= EndGame) a[1] -= 9;
				break;
			default:break;
			}
			for (int i = 0; i < 2; ++i)
				tileScore[k] += a[i];
		}
		//���1�Ŷ�û�г���
		else if (t1 == 0) {
			t2 = all[k + 1] - hand[k + 1];
			t3 = all[k + 2] - hand[k + 2];
			t4 = all[k - 1] - hand[k - 1];
			int a[2] = { 0 };
			switch (t2) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 2;
				else if (leftTile >= EndGame) a[0] -= 3;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 4;
				else if (leftTile >= EndGame) a[0] -= 6;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 7;
				else if (leftTile >= EndGame) a[0] -= 9;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 12;
				else if (leftTile >= EndGame) a[0] -= 15;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 17;
				else if (leftTile >= EndGame) a[0] -= 20;
				break;
			default:break;
			}
			switch (t4) {
			case 0:
				if (leftTile >= MiddleGame) a[0] -= 2;
				else if (leftTile >= EndGame) a[0] -= 3;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[0] -= 4;
				else if (leftTile >= EndGame) a[0] -= 6;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[0] -= 7;
				else if (leftTile >= EndGame) a[0] -= 9;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[0] -= 12;
				else if (leftTile >= EndGame) a[0] -= 15;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[0] -= 17;
				else if (leftTile >= EndGame) a[0] -= 20;
				break;
			default:break;
			}
			switch (t3) {
			case 0:
				if (leftTile >= MiddleGame) a[1] -= 2;
				else if (leftTile >= EndGame) a[1] -= 3;
				break;
			case 1:
				if (leftTile >= MiddleGame) a[1] -= 4;
				else if (leftTile >= EndGame) a[1] -= 5;
				break;
			case 2:
				if (leftTile >= MiddleGame) a[1] -= 6;
				else if (leftTile >= EndGame) a[1] -= 9;
				break;
			case 3:
				if (leftTile >= MiddleGame) a[1] -= 11;
				else if (leftTile >= EndGame) a[1] -= 13;
				break;
			case 4:
				if (leftTile >= MiddleGame) a[1] -= 14;
				else if (leftTile >= EndGame) a[1] -= 16;
				break;
			default:break;
			}
			for (int i = 0; i < 2; ++i)
				tileScore[k] += a[i];
		}
		k -= 7;

		int tmp = k;
		k += 2;
		for (; k < tmp + 7; ++k) {
			t1 = all[k] - hand[k];
			//���������1��
			if (t1 == 1) {
				t2 = all[k + 1] - hand[k + 1];
				t3 = all[k + 2] - hand[k + 2];
				t4 = all[k - 1] - hand[k - 1];
				int a[2] = { 0 };
				switch (t2) {
				case 0:
					if (leftTile >= MiddleGame) a[0] -= 1;
					else if (leftTile >= EndGame) a[0] -= 2;
					break;
				case 1:
					if (leftTile >= MiddleGame) a[0] -= 3;
					else if (leftTile >= EndGame) a[0] -= 4;
					break;
				case 2:
					if (leftTile >= MiddleGame) a[0] -= 6;
					else if (leftTile >= EndGame) a[0] -= 8;
					break;
				case 3:
					if (leftTile >= MiddleGame) a[0] -= 10;
					else if (leftTile >= EndGame) a[0] -= 13;
					break;
				case 4:
					if (leftTile >= MiddleGame) a[0] -= 12;
					else if (leftTile >= EndGame) a[0] -= 15;
					break;
				default:break;
				}
				switch (t3) {
				case 0:
					if (leftTile >= MiddleGame) a[1] -= 1;
					else if (leftTile >= EndGame) a[1] -= 2;
					break;
				case 1:
					if (leftTile >= MiddleGame) a[1] -= 2;
					else if (leftTile >= EndGame) a[1] -= 3;
					break;
				case 2:
					if (leftTile >= MiddleGame) a[1] -= 3;
					else if (leftTile >= EndGame) a[1] -= 4;
					break;
				case 3:
					if (leftTile >= MiddleGame) a[1] -= 5;
					else if (leftTile >= EndGame) a[1] -= 6;
					break;
				case 4:
					if (leftTile >= MiddleGame) a[1] -= 6;
					else if (leftTile >= EndGame) a[1] -= 7;
					break;
				default:break;
				}
				switch (t4) {
				case 0:
					if (leftTile >= MiddleGame) a[0] -= 1;
					else if (leftTile >= EndGame) a[0] -= 2;
					break;
				case 1:
					if (leftTile >= MiddleGame) a[0] -= 3;
					else if (leftTile >= EndGame) a[0] -= 4;
					break;
				case 2:
					if (leftTile >= MiddleGame) a[0] -= 6;
					else if (leftTile >= EndGame) a[0] -= 8;
					break;
				case 3:
					if (leftTile >= MiddleGame) a[0] -= 10;
					else if (leftTile >= EndGame) a[0] -= 13;
					break;
				case 4:
					if (leftTile >= MiddleGame) a[0] -= 12;
					else if (leftTile >= EndGame) a[0] -= 15;
					break;
				default:break;
				}
				switch (t5) {
				case 0:
					if (leftTile >= MiddleGame) a[1] -= 1;
					else if (leftTile >= EndGame) a[1] -= 2;
					break;
				case 1:
					if (leftTile >= MiddleGame) a[1] -= 2;
					else if (leftTile >= EndGame) a[1] -= 3;
					break;
				case 2:
					if (leftTile >= MiddleGame) a[1] -= 3;
					else if (leftTile >= EndGame) a[1] -= 4;
					break;
				case 3:
					if (leftTile >= MiddleGame) a[1] -= 5;
					else if (leftTile >= EndGame) a[1] -= 6;
					break;
				case 4:
					if (leftTile >= MiddleGame) a[1] -= 6;
					else if (leftTile >= EndGame) a[1] -= 7;
					break;
				default:break;
				}
				for (int i = 0; i < 2; ++i)
					tileScore[k] += a[i];
			}
			//���1�Ŷ�û�г���
			else if (t1 == 0) {
				t2 = all[k + 1] - hand[k + 1];
				t3 = all[k + 2] - hand[k + 2];
				t4 = all[k - 1] - hand[k - 1];
				t5 = all[k - 2] - hand[k - 2];
				int a[2] = { 0 };
				switch (t2) {
				case 0:
					if (leftTile >= MiddleGame) a[0] -= 2;
					else if (leftTile >= EndGame) a[0] -= 3;
					break;
				case 1:
					if (leftTile >= MiddleGame) a[0] -= 4;
					else if (leftTile >= EndGame) a[0] -= 6;
					break;
				case 2:
					if (leftTile >= MiddleGame) a[0] -= 7;
					else if (leftTile >= EndGame) a[0] -= 9;
					break;
				case 3:
					if (leftTile >= MiddleGame) a[0] -= 12;
					else if (leftTile >= EndGame) a[0] -= 15;
					break;
				case 4:
					if (leftTile >= MiddleGame) a[0] -= 17;
					else if (leftTile >= EndGame) a[0] -= 20;
					break;
				default:break;
				}
				switch (t4) {
				case 0:
					if (leftTile >= MiddleGame) a[0] -= 2;
					else if (leftTile >= EndGame) a[0] -= 3;
					break;
				case 1:
					if (leftTile >= MiddleGame) a[0] -= 4;
					else if (leftTile >= EndGame) a[0] -= 6;
					break;
				case 2:
					if (leftTile >= MiddleGame) a[0] -= 7;
					else if (leftTile >= EndGame) a[0] -= 9;
					break;
				case 3:
					if (leftTile >= MiddleGame) a[0] -= 12;
					else if (leftTile >= EndGame) a[0] -= 15;
					break;
				case 4:
					if (leftTile >= MiddleGame) a[0] -= 17;
					else if (leftTile >= EndGame) a[0] -= 20;
					break;
				default:break;
				}
				switch (t3) {
				case 0:
					if (leftTile >= MiddleGame) a[1] -= 2;
					else if (leftTile >= EndGame) a[1] -= 3;
					break;
				case 1:
					if (leftTile >= MiddleGame) a[1] -= 4;
					else if (leftTile >= EndGame) a[1] -= 5;
					break;
				case 2:
					if (leftTile >= MiddleGame) a[1] -= 6;
					else if (leftTile >= EndGame) a[1] -= 9;
					break;
				case 3:
					if (leftTile >= MiddleGame) a[1] -= 11;
					else if (leftTile >= EndGame) a[1] -= 13;
					break;
				case 4:
					if (leftTile >= MiddleGame) a[1] -= 14;
					else if (leftTile >= EndGame) a[1] -= 16;
					break;
				default:break;
				}
				switch (t5) {
				case 0:
					if (leftTile >= MiddleGame) a[1] -= 2;
					else if (leftTile >= EndGame) a[1] -= 3;
					break;
				case 1:
					if (leftTile >= MiddleGame) a[1] -= 4;
					else if (leftTile >= EndGame) a[1] -= 5;
					break;
				case 2:
					if (leftTile >= MiddleGame) a[1] -= 6;
					else if (leftTile >= EndGame) a[1] -= 9;
					break;
				case 3:
					if (leftTile >= MiddleGame) a[1] -= 11;
					else if (leftTile >= EndGame) a[1] -= 13;
					break;
				case 4:
					if (leftTile >= MiddleGame) a[1] -= 14;
					else if (leftTile >= EndGame) a[1] -= 16;
					break;
				default:break;
				}
				for (int i = 0; i < 2; ++i)
					tileScore[k] += a[i];
			}
		}
		k = tmp;
	}

	//�����Ƕ����¼ҵĶ�������Ҫ�������Ƕ�����ԵĶ���ӳ�
	//���ǲ��������ԣ���������
	/*int tmpUpTiles[72];//��ȥ�¼Ҵ����֮����¼�ÿ�������Ŀ�����
	for (int i = 17; i < 72; ++i)
	tmpUpTiles[i] = 4 - (all[i] - enemyPlayTiles[DownPlayer][i]);*/
	//XOOY�����X��Ķ࣬��ô��Y�Ŀ�����Ҳ��Խ�С������Ϊ�ǰ�ȫ��
	for (int k = 17; k < 50; k += 16) {
		for (int i = 0; i < 9; ++i) {
			if (!enemyPlayTiles[DownPlayer][k + i]) continue;
			tileScore[k + i] += 2 * enemyPlayTiles[DownPlayer][k + i];
			if (i > 2)
				tileScore[k + i - 3] += enemyPlayTiles[DownPlayer][k + i];
			if (i < 6)
				tileScore[k + i + 3] += enemyPlayTiles[DownPlayer][k + i];
		}
	}

	/*for (int i = 17; i < 72; ++i) {
	cout << "tileScore " << int2tile(i) << ": " << tileScore[i] << endl;
	}*/

	//�Լ�̫Զ�ˣ������õ���������
}

//ofstream file;

void chanceTile() {
	//�����Ƕ����ϼҵĹ��ƣ��ϼҴ�ʲô���͵��ƣ��Ҿ;;���������Щ�������������ԡ����ļ��ʻ����
	float rate1, rate2;
	if (leftTile >= FrontGame)
		rate1 = 10, rate2 = 7.5;
	else if (leftTile >= MiddleGame)
		rate1 = 2, rate2 = 1.5;
	else if (leftTile >= EndGame)
		rate1 = -1.8, rate2 = -0.95;//�����˺��̵�ʱ��Ϊ�˱�֤�����ڣ����ϼҴ�����ͬ����
	else rate1 = -2.7, rate2 = -1.8;
	for (int k = 17; k < 50; k += 16) {
		for (int i = 0; i < 9; ++i) {
			if (!enemyPlayTiles[UpPlayer][k + i]) continue;
			tileScore[k + i] -= rate1 * enemyPlayTiles[UpPlayer][k + i];
			if (i > 0)
				tileScore[k + i - 1] -= rate2 * enemyPlayTiles[UpPlayer][k + i];
			if (i < 8)
				tileScore[k + i + 1] -= enemyPlayTiles[UpPlayer][k + i];
		}
	}
}

void predictTile(int player) {
	float tempTiles[75] = { 0 };
	for (int i = 17; i < 72; ++i)
		tempTiles[i] = all[i] - enemyPlayTiles[player][i];//��¼���˸����֮�������Щ��

	//tempTiles��player������Ƶ�����
	//�������ƣ�����ԭ��Ϊ�����һ����ӵ�е��Ƹ��ʼ��룬�����������������ֱ����Ϊ0
	for (int k = 17; k < 50; k += 16) {
		float rate1 = 1, rate2 = 1;
		for (int i = 0; i < 8; ++i) {
			if (enemyPlayTiles[player][k + i] == 1) {
				tempTiles[k + i] /= 2;
				rate1 = 0.95, rate2 = 0.87;
			}
			else if (enemyPlayTiles[player][k + i] >= 2) {
				tempTiles[k + i] = 0;
				rate1 = 0.90, rate2 = 0.84;
			}
			for (int t = 1; t <= 2; ++t) {
				tempTiles[k + i + t] *= rate1;
				tempTiles[k + i - t] *= rate2;
			}
			if (player == DownPlayer)
				tileScore[k + i] += 0.8*enemyPlayTiles[player][k + i];
		}
	}

	/*file << player << endl;
	for (int i = 17; i < 72; ++i) {
		file << int2tile(i) << ": " << tempTiles[i] << endl;
	}*/
	for (int k = 17; k < 50; k += 16) {
		for (int i = 0; i < 8; ++i) {
			int m = k + i;
			tileScore[m] -= tempTiles[m] * 2.5;//���ܱ����ļ�¼
			if (player == DownPlayer) {
				tileScore[m] -= tempTiles[m - 1] * tempTiles[m + 1] * 0.7;//�Եĸ���
				tileScore[m] -= tempTiles[m - 2] * tempTiles[m - 1] * 0.7;
				tileScore[m] -= tempTiles[m + 2] * tempTiles[m + 1] * 0.7;
			}
		}
	}

	for (int i = 65; i < 72; ++i) 
		if (enemyPlayTiles[i] == 0) tileScore[i] -= (100 - leftTile)*0.08;

	if (player == UpPlayer)
		chanceTile();
}

//�ж��Ƿ�����
int if_wait(hand_tiles_t &t, tile_table_t &cnt, useful_table_t &useful)
{
	bool is_wait = false;
	//�����������13��
	if (t.tile_count == 13) {
		//ʮ����
		if (is_thirteen_orphans_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
		//ȫ����
		else if (is_honors_and_knitted_tiles_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
		//�߶�
		else if (is_seven_pairs_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
		//�����
		else if (is_knitted_straight_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
	}
	else if (t.tile_count == 10) {
		//�����
		if (is_knitted_straight_wait(t.standing_tiles, 10, &useful)) {
			is_wait = true;
		}
	}

	//������
	if (!is_wait && is_basic_form_wait(t.standing_tiles, t.tile_count, &useful))
		is_wait = true;

	//������Ч�Ƶ�����
	if (is_wait) {
		int num = 0;
		for (tile_t t = TILE_1m; t < TILE_TABLE_SIZE; ++t) {
			if (useful[t] && cnt[t] != 4)
				num += 4 - cnt[t];
		}
		return num;
	}

	//�������0�������û�����ƻ�����Ч��Ϊ0
	return 0;
}

int tile2int(string tile) {
	int t = 0, bias = -1;
	switch (tile[0]) {
	case'W':
		t = 1; break;
	case'B':
		t = 2; break;
	case'T':
		t = 3; break;
	case'F':
		t = 4; break;
	case'J':
		t = 4; bias = 4 + tile[1] - '0'; break;
	case'H':
		t = 0; break;
	default:break;
	}
	if (bias == -1) bias = tile[1] - '0';
	//cout << "t:" << t << ", bias: " << bias << endl;
	return (t << 4) + bias;
}

string int2tile(tile_t k) {
	string type;
	if (k <= 16)
		type = "H";
	else if (k <= 32)
		type = "W";
	else if (k <= 48)
		type = "B";
	else if (k <= 64)
		type = "T";
	else if (k <= 68)
		type = "F";
	else type = "J";
	k = k % 16;
	if (type == "J")
		k -= 4;
	type += k + '0';
	//cout << "type: " << type << endl;
	return type;
}

//�����Ƶ�״̬
void changeTileState(tile_table_t &tiles, string tile, int num) {
	int k = tile2int(tile);
	tiles[k] += num;
}

int testhunew(tile_t pai, bool isZIMO, bool isJUEZHANG, bool isGANG, bool isLAST)
{
	//useful_table_t test;
	//myHand.tile_count = 0;
	//for (intptr_t j = 17; j < 72; ++j)
	//if (hand[j])
	//for (int k = 0; k < hand[j]; ++k)
	//myHand.standing_tiles[myHand.tile_count++] = j;
	//if_wait(myHand, all, test);
	//if (!test[pai])
	//return false;

	//cout << "test all:" << endl;
	//for (int i = 1; i < 72; ++i) {
	//cout << int2tile(i) << ": " << all[i] << endl;
	//}
	/*ofstream file;
	file.open("Fancal.txt", ios::out);

	file << "isZIMO: " << isZIMO << " isJUEZHANG: " << isJUEZHANG << " isGANG: " << isGANG << " isLAST: " << isLAST << endl;
	file << "flowercnt: " << flowerCnt << endl;*/
	//myHand.tile_count = 0;
	//for (intptr_t j = 17; j < 72; ++j)
	//if (hand[j])
	//for (int k = 0; k < hand[j]; ++k)
	//myHand.standing_tiles[myHand.tile_count++] = j;
	vector<pair<string, pair<string, int> > > pack;//��¼��¶����
	vector<string> handStr;//����
	string winTile = int2tile(pai);
	//file << "winTile: " << winTile << endl;
	//��¼��¶
	for (int i = 0; i < myHand.pack_count; ++i) {
		pack.push_back(make_pair(action[i], make_pair(action_tile[i], action_player[i])));
		//file << action[i] << " " << action_tile[i] << " " << action_player[i] << endl;
	}
	//��¼����
	for (int i = 0; i < myHand.tile_count; ++i) {
		handStr.push_back(int2tile(myHand.standing_tiles[i]));
		//file << int2tile(myHand.standing_tiles[i]) << " ";
	}
	//file << endl;
	vector<pair<int, string> > fan = MahjongFanCalculator(pack, handStr, winTile, flowerCnt,
		isZIMO, isJUEZHANG, isGANG, isLAST, myID, currentQuan);
	int Fan = 0;
	for (int i = 0; i < fan.size(); ++i) {
		Fan += fan[i].first;
		//file << fan[i].first << " " << fan[i].second << endl;
	}
	//file << "Fan: " << Fan << endl;

	return Fan;
}

int if_waitnew(hand_tiles_t &t, tile_table_t &cnt, useful_table_t &useful)
{
	bool is_wait = false;
	//�����������13��
	if (t.tile_count == 13) {
		//ʮ����
		if (is_thirteen_orphans_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
		//ȫ����
		else if (is_honors_and_knitted_tiles_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
		//�߶�
		else if (is_seven_pairs_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
		//�����
		else if (is_knitted_straight_wait(t.standing_tiles, 13, &useful)) {
			is_wait = true;
		}
	}
	else if (t.tile_count == 10) {
		//�����
		if (is_knitted_straight_wait(t.standing_tiles, 10, &useful)) {
			is_wait = true;
		}
	}

	//������
	if (!is_wait && is_basic_form_wait(t.standing_tiles, t.tile_count, &useful))
		is_wait = true;

	//������Ч�Ƶ�����
	if (is_wait) {
		int num = 0;
		for (tile_t i = TILE_1m; i < TILE_TABLE_SIZE; ++i) {
			if (useful[i] && cnt[i] != 4)
			{
				bool isJUEZHANG = (all[i] - hand[i]) == 3 ? true : false;
				int FAN = testhunew(i, false, isJUEZHANG, false, false);
				if (FAN == 7)
					num += (4 - cnt[i]) * 10;
				else if (FAN > 7)
					num += 100 * (4 - cnt[i]);
				else num += 4 - cnt[i];
			}
		}
		return num;
	}
	//�������0�������û�����ƻ�����Ч��Ϊ0
	return 0;
}

unsigned long GetTickCount()
{
	time_t tt = time(NULL);
	tm* t = localtime(&tt);
	return t->tm_sec * 1000;
	/*struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);*/
}

unsigned char quanbukao[6][9] = { { 17,20,23,34,37,40,51,54,57 },{ 17,20,23,50,53,56,35,38,41 },{ 33,36,39,18,21,24,51,54,57 },
{ 33,36,39,50,53,56,19,22,25 },{ 49,52,55,18,21,24,35,38,41 },{ 49,52,55,34,37,40,19,22,25 } };

unsigned char thirteenyao[13] = { 17,25,33,41,49,57,65,66,67,68,69,70,71 };

unsigned char sanse[6][3] = { { 16,32,48 },{ 16,48,32 },{ 32,16,48 },{ 32,48,16 },{ 48,16,32 },{ 48,32,16 } };

int WCP;

void evaluateN()
{
	WCP = 1;

	//��Ҫ��
#pragma region qingyaojiu



	int t = my[17] + my[25] + my[33] + my[41] + my[49] + my[57];
	if (t > 9)
	{
		t = (t - 9) * (t - 9) * 10;
		value[17] += t;
		value[25] += t;
		value[33] += t;
		value[41] += t;
		value[49] += t;
		value[57] += t;
	}
#pragma endregion

	//ʮ����
#pragma region thirteenyao
	t = 0;
	for (int i = 0; i < 13; ++i)
		if (my[thirteenyao[i]])
			++t;
	if (t > 8 && myHand.pack_count == 0)
	{
		WCP = 0;
		if (t > 10)
		{
			for (int i = 0; i < 13; ++i)
				if (my[thirteenyao[i]] == 1)
					value[thirteenyao[i]] += 200;
		}
		for (int i = 0; i < 13; ++i)
			if (my[thirteenyao[i]] == 1)
				value[thirteenyao[i]] += 50;
	}
#pragma endregion

	//С��Ԫ ��һɫ
#pragma region ziyise
	t = my[65] + my[66] + my[67] + my[68] + my[69] + my[70] + my[71];
	if (t > 9)
	{
		t = (t - 9) * (t - 9) * 10;
		value[65] += t;
		value[66] += t;
		value[67] += t;
		value[68] += t;
		value[69] += t;
		value[70] += t;
		value[71] += t;
	}
#pragma endregion

	//������ ����
#pragma region pengpenghe
	t = 0;
	for (int i = 17; i < 72; ++i)
		if (my[i] == 2)
			t += 2;
		else if (my[i] >= 3)
			t += 4;
	if (t > 6)
	{
		for (int i = 17; i < 72; ++i)
			if (my[i] >= 2)
				value[i] += (t - 6) * 10;
			else
				value[i] -= (t - 6) * 10;
	}
#pragma endregion

	//ȫ����

#pragma region quan bu kao
	if (myHand.pack_count == 0)
	{
		t = 0;
		for (int i = 65; i < 72; ++i)
			if (my[i])
				++t;
		int q = 0, tmp, p;
		for (int i = 0; i < 6; ++i)
		{
			tmp = 0;
			for (int j = 0; j < 9; ++j)
				if (my[quanbukao[i][j]])
					++tmp;
			if (tmp > q)
			{
				q = tmp;
				p = i;
			}
		}
		//if (t + q > 7)
		//{

		if (t + q > 9)
		{
			WCP = 0;
			for (int i = 65; i < 72; ++i)
				if (my[quanbukao[p][i]] == 1)
					value[quanbukao[p][1]] += 200;
			for (int i = 0; i < 9; ++i)
				if (my[quanbukao[p][i]] == 1)
					value[quanbukao[p][i]] += 200;
		}
		//for (int i = 65; i < 72; ++i)
		//	if (my[quanbukao[p][i]] == 1)
		//		value[quanbukao[p][1]] += 50;
		//for (int i = 0; i < 9; ++i)
		//	if (my[quanbukao[p][i]] == 1)
		//		value[quanbukao[p][i]] += 50;
		//}
	}
#pragma endregion

	//��һɫ  ȱһ�� ��һɫ
#pragma region quemen



	t = 0;
	for (int i = 17; i < 26; ++i)
		t += my[i];
	if (t <= 2)
	{
		for (int i = 17; i < 26; ++i)
			value[i] -= (3 - t) * 20;
	}
	if (t > 8)
	{
		for (int i = 17; i < 26; ++i)
			value[i] += (t - 8) * 10;
		for (int i = 33; i < 71; ++i)
			value[i] -= (t - 8) * 10;
	}
	for (int i = 33; i < 42; ++i)
		t += my[i];
	if (t <= 3)
	{
		t = 10 * (3 - t);
		for (int i = 17; i < 42; ++i)
			value[i] -= t;
	}
	t = 0;
	for (int i = 33; i < 42; ++i)
		t += my[i];
	if (t <= 2)
	{
		for (int i = 33; i < 42; ++i)
			value[i] -= (3 - t) * 20;
	}
	if (t > 8)
	{
		for (int i = 33; i < 42; ++i)
			value[i] += (t - 8) * 20;
		for (int i = 17; i < 71; ++i)
			value[i] -= (t - 8) * 10;
	}
	for (int i = 49; i < 58; ++i)
		t += my[i];
	if (t <= 3)
	{
		t = 10 * (3 - t);
		for (int i = 33; i < 58; ++i)
			value[i] -= t;
	}
	t = 0;
	for (int i = 49; i < 58; ++i)
		t += my[i];
	if (t <= 2)
	{
		for (int i = 49; i < 58; ++i)
			value[i] -= (3 - t) * 20;
	}
	if (t > 8)
	{
		for (int i = 49; i < 58; ++i)
			value[i] += (t - 8) * 20;
		for (int i = 17; i < 71; ++i)
			value[i] -= (t - 8) * 10;
	}
	for (int i = 17; i < 26; ++i)
		t += my[i];
	if (t <= 3)
	{
		t = 10 * (3 - t);
		for (int i = 17; i < 26; ++i)
			value[i] -= t;
		for (int i = 49; i < 58; ++i)
			value[i] -= t;
	}
#pragma endregion



	//��ɫ���ڸ�
#pragma region sansesanjiegao
	t = 0;
	int q = 0, tmp, p;

	for (int i = 1; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			tmp = 0;
			if (my[sanse[j][0] + i] && my[sanse[j][0] + i] <= 2)
				++tmp;
			if (my[sanse[j][0] + i + 1] && my[sanse[j][0] + i + 1] <= 2)
				++tmp;
			if (my[sanse[j][0] + i + 2] && my[sanse[j][0] + i + 2] <= 2)
				++tmp;
			if (my[sanse[j][1] + i + 1] && my[sanse[j][1] + i + 1] <= 2)
				++tmp;
			if (my[sanse[j][1] + i + 2] && my[sanse[j][1] + i + 2] <= 2)
				++tmp;
			if (my[sanse[j][1] + i + 3] && my[sanse[j][1] + i + 3] <= 2)
				++tmp;
			if (my[sanse[j][2] + i + 2] && my[sanse[j][2] + i + 2] <= 2)
				++tmp;
			if (my[sanse[j][2] + i + 3] && my[sanse[j][2] + i + 3] <= 2)
				++tmp;
			if (my[sanse[j][2] + i + 4] && my[sanse[j][2] + i + 4] <= 2)
				++tmp;
			if (tmp > t)
			{
				t = tmp;
				q = i;
				p = j;
			}
		}
	}
	if (t >= 7)
	{
		value[sanse[p][0] + q] += 50;
		value[sanse[p][0] + q + 1] += 50;
		value[sanse[p][0] + q + 2] += 50;
		value[sanse[p][1] + q + 1] += 50;
		value[sanse[p][1] + q + 2] += 50;
		value[sanse[p][1] + q + 3] += 50;
		value[sanse[p][2] + q + 2] += 50;
		value[sanse[p][2] + q + 3] += 50;
		value[sanse[p][2] + q + 4] += 50;
	}
#pragma endregion



	//��ɫ��ͬ˳
#pragma region sansesantongshun
	t = 0;
	q = 0, tmp, p;

	for (int i = 1; i <= 7; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			tmp = 0;
			if (my[sanse[j][0] + i] && my[sanse[j][0] + i] <= 2)
				++tmp;
			if (my[sanse[j][0] + i + 1] && my[sanse[j][0] + i + 1] <= 2)
				++tmp;
			if (my[sanse[j][0] + i + 2] && my[sanse[j][0] + i + 2] <= 2)
				++tmp;
			if (my[sanse[j][1] + i] && my[sanse[j][1] + i] <= 2)
				++tmp;
			if (my[sanse[j][1] + i + 1] && my[sanse[j][1] + i + 1] <= 2)
				++tmp;
			if (my[sanse[j][1] + i + 2] && my[sanse[j][1] + i + 2] <= 2)
				++tmp;
			if (my[sanse[j][2] + i] && my[sanse[j][2] + i] <= 2)
				++tmp;
			if (my[sanse[j][2] + i + 1] && my[sanse[j][2] + i + 1] <= 2)
				++tmp;
			if (my[sanse[j][2] + i + 2] && my[sanse[j][2] + i + 2] <= 2)
				++tmp;
			if (tmp > t)
			{
				t = tmp;
				q = i;
				p = j;
			}
		}
	}
	if (t >= 7)
	{
		value[sanse[p][0] + q] += 50;
		value[sanse[p][0] + q + 1] += 50;
		value[sanse[p][0] + q + 2] += 50;
		value[sanse[p][1] + q] += 50;
		value[sanse[p][1] + q + 1] += 50;
		value[sanse[p][1] + q + 2] += 50;
		value[sanse[p][2] + q] += 50;
		value[sanse[p][2] + q + 1] += 50;
		value[sanse[p][2] + q + 2] += 50;
	}
#pragma endregion

	//�߶�
#pragma region sevenpairs
	if (myHand.pack_count == 0)
	{
		t = 0;
		for (int i = 17; i < 72; ++i)
			if (my[i] >= 2)
				++t;
		if (t >= 5)
		{
			for (int i = 17; i < 72; ++i)
				if (my[i] == 2)
					value[i] += 100;
		}
	}
#pragma endregion



	//һɫ���ڸ�
#pragma region yisesanjiegao



	for (int i = 17; i < 55; ++i)
	{
		if ((i & 0xf) > 5)
			continue;
		t = 0;
		if (my[i] == 1)
			t += 2;
		if (my[i + 1] == 1)
			t += 2;
		if (my[i + 1] == 2)
			t += 4;
		if (my[i + 2] == 1)
			t += 1;
		if (my[i + 2] == 2)
			t += 3;
		if (my[i + 2] == 3)
			t += 5;
		if (my[i + 3] == 1)
			t += 2;
		if (my[i + 3] == 2)
			t += 4;
		if (my[i + 4] == 2)
			t += 2;
		for (int j = 0; j < temp.pack_count; ++j)
			if ((temp.fixed_packs[j] & 0xff) == i + 2 && (((temp.fixed_packs[j] >> 8) & 0xf) & (PACK_TYPE_PUNG | PACK_TYPE_KONG)))
				t = 0;
		if (t > 12)
		{
			t = (t - 12) * 10;
			value[i] += t;
			value[i + 1] += t;
			value[i + 2] += t;
			value[i + 3] += t;
			value[i + 4] += t;
		}
	}

	for (int i = 17; i < 55; ++i)
	{
		if ((i & 0xf) > 3)
			continue;
		t = 0;
		if (my[i] == 1)
			t += 2;
		if (my[i + 1] == 1)
			t += 2;
		if (my[i + 2] == 1)
			t += 1;
		if (my[i + 2] == 2)
			t += 3;
		if (my[i + 3] == 1)
			t += 2;
		if (my[i + 4] == 1)
			t += 1;
		if (my[i + 4] == 2)
			t += 3;
		if (my[i + 5] == 1)
			t += 2;
		if (my[i + 6] == 1)
			t += 2;
		if (t > 12)
		{
			t = (t - 12) * 10;
			value[i] += t;
			value[i + 1] += t;
			value[i + 2] += t;
			value[i + 3] += t;
			value[i + 4] += t;
		}
	}


#pragma endregion

	//ALL BIG ALL MID ALL SMALL
#pragma region all b m s

	t = my[17] + my[18] + my[19] + my[33] + my[34] + my[35] + my[49] + my[50] + my[51];
	for (int j = 0; j < temp.pack_count; ++j)
		if ((temp.fixed_packs[j] & 0xf) != 2 && (((temp.fixed_packs[j] >> 8) & 0xf) == PACK_TYPE_CHOW))
			t = 0;
	if (t > 9)
	{
		for (int i = 17; i < 72; ++i)
			value[i] -= 5 * (t - 9);
		value[17] += 10 * (t - 9);
		value[18] += 10 * (t - 9);
		value[19] += 10 * (t - 9);
		value[33] += 10 * (t - 9);
		value[34] += 10 * (t - 9);
		value[35] += 10 * (t - 9);
		value[49] += 10 * (t - 9);
		value[50] += 10 * (t - 9);
		value[51] += 10 * (t - 9);
	}
	t = my[20] + my[21] + my[22] + my[36] + my[37] + my[38] + my[52] + my[53] + my[54];
	for (int j = 0; j < temp.pack_count; ++j)
		if ((temp.fixed_packs[j] & 0xf) != 5 && (((temp.fixed_packs[j] >> 8) & 0xf) == PACK_TYPE_CHOW))
			t = 0;
	if (t > 9)
	{
		for (int i = 17; i < 72; ++i)
			value[i] -= 5 * (t - 9);
		value[20] += 10 * (t - 9);
		value[21] += 10 * (t - 9);
		value[22] += 10 * (t - 9);
		value[36] += 10 * (t - 9);
		value[37] += 10 * (t - 9);
		value[38] += 10 * (t - 9);
		value[52] += 10 * (t - 9);
		value[53] += 10 * (t - 9);
		value[54] += 10 * (t - 9);
	}
	t = my[23] + my[24] + my[25] + my[39] + my[40] + my[41] + my[55] + my[56] + my[57];
	for (int j = 0; j < temp.pack_count; ++j)
		if ((temp.fixed_packs[j] & 0xf) != 8 && (((temp.fixed_packs[j] >> 8) & 0xf) == PACK_TYPE_CHOW))
			t = 0;
	if (t > 9)
	{
		for (int i = 17; i < 72; ++i)
			value[i] -= 5 * (t - 9);
		value[23] += 10 * (t - 9);
		value[24] += 10 * (t - 9);
		value[25] += 10 * (t - 9);
		value[39] += 10 * (t - 9);
		value[40] += 10 * (t - 9);
		value[41] += 10 * (t - 9);
		value[55] += 10 * (t - 9);
		value[56] += 10 * (t - 9);
		value[57] += 10 * (t - 9);
	}
#pragma endregion

	//>5  <5
#pragma region cmp5

	t = my[22] + my[23] + my[24] + my[25] + my[38] + my[39] + my[40] + my[41] + my[54] + my[55] + my[56] + my[57];
	for (int j = 0; j < temp.pack_count; ++j)
		if ((temp.fixed_packs[j] & 0xf) <= 5)
			t = 0;
	if (t > 9)
	{
		for (int i = 17; i < 72; ++i)
			value[i] -= 10 * (t - 9);
		value[22] += 10 * (t - 9);
		value[23] += 10 * (t - 9);
		value[24] += 10 * (t - 9);
		value[25] += 10 * (t - 9);
		value[39] += 10 * (t - 9);
		value[40] += 10 * (t - 9);
		value[41] += 10 * (t - 9);
		value[55] += 10 * (t - 9);
		value[56] += 10 * (t - 9);
		value[57] += 10 * (t - 9);
	}
	t = my[20] + my[17] + my[18] + my[19] + my[33] + my[34] + my[35] + my[36] + my[49] + my[50] + my[51] + my[52];
	for (int j = 0; j < temp.pack_count; ++j)
		if ((temp.fixed_packs[j] & 0xf) >= 5)
			t = 0;
	if (t > 9)
	{
		for (int i = 17; i < 72; ++i)
			value[i] -= 4 * (t - 9);
		value[17] += 10 * (t - 9);
		value[18] += 10 * (t - 9);
		value[19] += 10 * (t - 9);
		value[20] += 10 * (t - 9);
		value[33] += 10 * (t - 9);
		value[34] += 10 * (t - 9);
		value[35] += 10 * (t - 9);
		value[36] += 10 * (t - 9);
		value[49] += 10 * (t - 9);
		value[50] += 10 * (t - 9);
		value[51] += 10 * (t - 9);
		value[52] += 10 * (t - 9);
	}
#pragma endregion

	//���� �����
#pragma region dragons


	int f = 17, m = 20, e = 23;
	t = 0;
	if (my[f] && my[f] <= 2)
		++t;
	if (my[f + 1] && my[f + 1] <= 2)
		++t;
	if (my[f + 2] && my[f + 2] <= 2)
		++t;
	if (my[m] && my[m] <= 2)
		++t;
	if (my[m + 1] && my[m + 1] <= 2)
		++t;
	if (my[m + 2] && my[m + 2] <= 2)
		++t;
	if (my[e] && my[e] <= 2)
		++t;
	if (my[e + 1] && my[e + 1] <= 2)
		++t;
	if (my[e + 2] && my[e + 2] <= 2)
		++t;
	if (t > 6)
	{
		t = (t - 6) * 10;
		value[f] += t;
		value[f + 1] += t;
		value[f + 2] += t;
		value[m] += t;
		value[m + 1] += t;
		value[m + 2] += t;
		value[e] += t;
		value[e + 1] += t;
		value[e + 2] += t;
	}
	f = 33, m = 36, e = 39;
	t = 0;
	if (my[f] && my[f] <= 2)
		++t;
	if (my[f + 1] && my[f + 1] <= 2)
		++t;
	if (my[f + 2] && my[f + 2] <= 2)
		++t;
	if (my[m] && my[m] <= 2)
		++t;
	if (my[m + 1] && my[m + 1] <= 2)
		++t;
	if (my[m + 2] && my[m + 2] <= 2)
		++t;
	if (my[e] && my[e] <= 2)
		++t;
	if (my[e + 1] && my[e + 1] <= 2)
		++t;
	if (my[e + 2] && my[e + 2] <= 2)
		++t;
	if (t > 6)
	{
		t = (t - 6) * 10;
		value[f] += t;
		value[f + 1] += t;
		value[f + 2] += t;
		value[m] += t;
		value[m + 1] += t;
		value[m + 2] += t;
		value[e] += t;
		value[e + 1] += t;
		value[e + 2] += t;
	}
	f = 49, m = 52, e = 55;
	t = 0;
	if (my[f] && my[f] <= 2)
		++t;
	if (my[f + 1] && my[f + 1] <= 2)
		++t;
	if (my[f + 2] && my[f + 2] <= 2)
		++t;
	if (my[m] && my[m] <= 2)
		++t;
	if (my[m + 1] && my[m + 1] <= 2)
		++t;
	if (my[m + 2] && my[m + 2] <= 2)
		++t;
	if (my[e] && my[e] <= 2)
		++t;
	if (my[e + 1] && my[e + 1] <= 2)
		++t;
	if (my[e + 2] && my[e + 2] <= 2)
		++t;
	if (t > 6)
	{
		t = (t - 6) * 10;
		value[f] += t;
		value[f + 1] += t;
		value[f + 2] += t;
		value[m] += t;
		value[m + 1] += t;
		value[m + 2] += t;
		value[e] += t;
		value[e + 1] += t;
		value[e + 2] += t;
	}
	f = 33, m = 20, e = 55;
	t = 0;
	if (my[f] && my[f] <= 2)
		++t;
	if (my[f + 1] && my[f + 1] <= 2)
		++t;
	if (my[f + 2] && my[f + 2] <= 2)
		++t;
	if (my[m] && my[m] <= 2)
		++t;
	if (my[m + 1] && my[m + 1] <= 2)
		++t;
	if (my[m + 2] && my[m + 2] <= 2)
		++t;
	if (my[e] && my[e] <= 2)
		++t;
	if (my[e + 1] && my[e + 1] <= 2)
		++t;
	if (my[e + 2] && my[e + 2] <= 2)
		++t;
	if (t > 6)
	{
		t = (t - 6) * 10;
		value[f] += t;
		value[f + 1] += t;
		value[f + 2] += t;
		value[m] += t;
		value[m + 1] += t;
		value[m + 2] += t;
		value[e] += t;
		value[e + 1] += t;
		value[e + 2] += t;
	}
	f = 17, m = 36, e = 55;
	t = 0;
	if (my[f] && my[f] <= 2)
		++t;
	if (my[f + 1] && my[f + 1] <= 2)
		++t;
	if (my[f + 2] && my[f + 2] <= 2)
		++t;
	if (my[m] && my[m] <= 2)
		++t;
	if (my[m + 1] && my[m + 1] <= 2)
		++t;
	if (my[m + 2] && my[m + 2] <= 2)
		++t;
	if (my[e] && my[e] <= 2)
		++t;
	if (my[e + 1] && my[e + 1] <= 2)
		++t;
	if (my[e + 2] && my[e + 2] <= 2)
		++t;
	if (t > 6)
	{
		t = (t - 6) * 10;
		value[f] += t;
		value[f + 1] += t;
		value[f + 2] += t;
		value[m] += t;
		value[m + 1] += t;
		value[m + 2] += t;
		value[e] += t;
		value[e + 1] += t;
		value[e + 2] += t;
	}
	f = 49, m = 36, e = 23;
	t = 0;
	if (my[f] && my[f] <= 2)
		++t;
	if (my[f + 1] && my[f + 1] <= 2)
		++t;
	if (my[f + 2] && my[f + 2] <= 2)
		++t;
	if (my[m] && my[m] <= 2)
		++t;
	if (my[m + 1] && my[m + 1] <= 2)
		++t;
	if (my[m + 2] && my[m + 2] <= 2)
		++t;
	if (my[e] && my[e] <= 2)
		++t;
	if (my[e + 1] && my[e + 1] <= 2)
		++t;
	if (my[e + 2] && my[e + 2] <= 2)
		++t;
	if (t > 6)
	{
		t = (t - 6) * 10;
		value[f] += t;
		value[f + 1] += t;
		value[f + 2] += t;
		value[m] += t;
		value[m + 1] += t;
		value[m + 2] += t;
		value[e] += t;
		value[e + 1] += t;
		value[e + 2] += t;
	}
	f = 33, m = 52, e = 23;
	t = 0;
	if (my[f] && my[f] <= 2)
		++t;
	if (my[f + 1] && my[f + 1] <= 2)
		++t;
	if (my[f + 2] && my[f + 2] <= 2)
		++t;
	if (my[m] && my[m] <= 2)
		++t;
	if (my[m + 1] && my[m + 1] <= 2)
		++t;
	if (my[m + 2] && my[m + 2] <= 2)
		++t;
	if (my[e] && my[e] <= 2)
		++t;
	if (my[e + 1] && my[e + 1] <= 2)
		++t;
	if (my[e + 2] && my[e + 2] <= 2)
		++t;
	if (t > 6)
	{
		t = (t - 6) * 10;
		value[f] += t;
		value[f + 1] += t;
		value[f + 2] += t;
		value[m] += t;
		value[m + 1] += t;
		value[m + 2] += t;
		value[e] += t;
		value[e + 1] += t;
		value[e + 2] += t;
	}
	f = 17, m = 52, e = 39;
	t = 0;
	if (my[f] && my[f] <= 2)
		++t;
	if (my[f + 1] && my[f + 1] <= 2)
		++t;
	if (my[f + 2] && my[f + 2] <= 2)
		++t;
	if (my[m] && my[m] <= 2)
		++t;
	if (my[m + 1] && my[m + 1] <= 2)
		++t;
	if (my[m + 2] && my[m + 2] <= 2)
		++t;
	if (my[e] && my[e] <= 2)
		++t;
	if (my[e + 1] && my[e + 1] <= 2)
		++t;
	if (my[e + 2] && my[e + 2] <= 2)
		++t;
	if (t > 6)
	{
		t = (t - 6) * 10;
		value[f] += t;
		value[f + 1] += t;
		value[f + 2] += t;
		value[m] += t;
		value[m + 1] += t;
		value[m + 2] += t;
		value[e] += t;
		value[e + 1] += t;
		value[e + 2] += t;
	}
	f = 49, m = 20, e = 39;
	t = 0;
	if (my[f] && my[f] <= 2)
		++t;
	if (my[f + 1] && my[f + 1] <= 2)
		++t;
	if (my[f + 2] && my[f + 2] <= 2)
		++t;
	if (my[m] && my[m] <= 2)
		++t;
	if (my[m + 1] && my[m + 1] <= 2)
		++t;
	if (my[m + 2] && my[m + 2] <= 2)
		++t;
	if (my[e] && my[e] <= 2)
		++t;
	if (my[e + 1] && my[e + 1] <= 2)
		++t;
	if (my[e + 2] && my[e + 2] <= 2)
		++t;
	if (t > 6)
	{
		t = (t - 6) * 10;
		value[f] += t;
		value[f + 1] += t;
		value[f + 2] += t;
		value[m] += t;
		value[m + 1] += t;
		value[m + 2] += t;
		value[e] += t;
		value[e + 1] += t;
		value[e + 2] += t;
	}
#pragma endregion

	//jianke
	if (my[69] == 2)
		value[69] += 20;
	if (my[70] == 2)
		value[70] += 20;
	if (my[71] == 2)
		value[71] += 20;

	//menfengke
	if (my[wind] == 1)
		value[wind] += 1;
	if (my[wind] == 2)
		value[wind] += 20;
	if (my[wind_s] == 1)
		value[wind_s] += 2;
	if (my[wind_s] == 2)
		value[wind_s] += 20;

	//duanyao
	t = my[17] + my[25] + my[33] + my[41] + my[49] + my[57] + my[65] + my[66] + my[67] + my[68] + my[69] + my[70] + my[71];
	if (t < 3)
	{
		t = (3 - t) * 5;
		my[17] -= t;
		my[25] -= t;
		my[33] -= t;
		my[41] -= t;
		my[49] -= t;
		my[57] -= t;
		my[65] -= t;
		my[66] -= t;
		my[67] -= t;
		my[68] -= t;
		my[69] -= t;
		my[70] -= t;
		my[71] -= t;
	}


	//duizijiacheng
	for (int i = 17; i < 72; ++i)
		if (hand[i] >= 2 && all[i])
			value[i] += 10;

	//���ųͷ�
	for (int i = 17; i<58; ++i)
		if (my[i] == 1 && !my[i + 1] && !my[i + 2] && !my[i - 1] && !my[i - 2])
			value[i] -= 50;

	for (int i = 65; i<72; ++i)
		if (my[i] == 1)
			value[i] -= 50;
}


void evaluatenew()
{
	memset(value, 0, sizeof(value));
	memcpy(my, hand, sizeof(hand));
	for (int i = 0; i < myHand.pack_count; ++i)
		if (((myHand.fixed_packs[i] >> 8) & 0xf) == PACK_TYPE_CHOW)
			++my[myHand.fixed_packs[i] & 0xff], ++my[1 + (myHand.fixed_packs[i] & 0xff)], ++my[-1 + (myHand.fixed_packs[i] & 0xff)];
		else
			my[myHand.fixed_packs[i] & 0xff] += 3;
	evaluateN();
}


//���ݵ�ǰ�������˳�ӣ����ӵĿ����Խ��й�ֵ
void evaluate(int kind, int pos, int &maxn)
{
	//����Ѿ��жϵ����������з�����
	if (kind == 4)
	{
		int score = 0;
		for (tile_t i = 16; i < 72; ++i) {
			if (hand[i])
			{
				//û����ɾ��ӿ��ֵ��Ƽ���
				score -= hand[i] * 1000;
				//�������Ų�����
				//if (hand[i] >= 3)
				//return;
				//���������
				if (i < 64)
				{
					if (hand[i] == 1)
					{
						//�ж��ļ������˳��
						//����������ǿ�������
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
				//���������з���
				else
				{
					//ֻ�п���������
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

	//ȷ���������е�λ��
	int t = kind * 16 + pos;



	//˳��
	//��û�п��ǹ���W1W1W2W2W3���������
	if (hand[t] && hand[t + 1] && hand[t + 2])
	{
		--hand[t]; --hand[t + 1]; --hand[t + 2];
		if (pos == 9)
			evaluate(kind + 1, 1, maxn);
		else
			evaluate(kind, pos + 1, maxn);
		++hand[t]; ++hand[t + 1]; ++hand[t + 2];
	}

	//����
	if (hand[t] >= 3)
	{
		hand[t] -= 3;
		//����ǵ�9�ţ�������һ��
		if (pos == 9)
			evaluate(kind + 1, 1, maxn);
		else
			evaluate(kind, pos + 1, maxn);
		hand[t] += 3;
		return;
	}

	//nothing
	if (pos == 9)
		evaluate(kind + 1, 1, maxn);
	else
		evaluate(kind, pos + 1, maxn);
}

int chi(tile_t pai)
{
	if (pai > 64)
		return 0;
	useful_table_t test;
	myHand.tile_count = 0;
	int max;
	max = -10000000;
	evaluate(1, 1, max);
	int da = 0;
	if (hand[pai - 1] && hand[pai - 2])
	{
		--hand[pai - 1]; --hand[pai - 2];
		myHand.fixed_packs[myHand.pack_count++] = make_pack(3, PACK_TYPE_CHOW, pai - 1);
		for (intptr_t i = 17; i < 72; ++i) {
			if (hand[i])
			{
				--hand[i];
				myHand.tile_count = 0;
				for (intptr_t j = 17; j < 72; ++j)
					if (hand[j])
						for (int k = 0; k < hand[j]; ++k)
							myHand.standing_tiles[myHand.tile_count++] = j;
				int res = if_wait(myHand, all, test);
				if (res)
				{
					iflis = 1;
					return 1;
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
		}
		myHand.pack_count--;
		++hand[pai - 1]; ++hand[pai - 2];
	}
	if (hand[pai - 1] && hand[pai + 1])
	{
		--hand[pai - 1]; --hand[pai + 1];
		myHand.fixed_packs[myHand.pack_count++] = make_pack(2, PACK_TYPE_CHOW, pai);
		for (intptr_t i = 17; i < 72; ++i) {
			if (hand[i])
			{
				--hand[i];
				myHand.tile_count = 0;
				for (intptr_t j = 17; j < 72; ++j)
					if (hand[j])
						for (int k = 0; k < hand[j]; ++k)
							myHand.standing_tiles[myHand.tile_count++] = j;
				int res = if_wait(myHand, all, test);
				if (res)
				{
					iflis = 1;
					return 1;
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
		}
		myHand.pack_count--;
		++hand[pai - 1]; ++hand[pai + 1];
	}
	if (hand[pai + 1] && hand[pai + 2])
	{
		--hand[pai + 1]; --hand[pai + 2];
		myHand.fixed_packs[myHand.pack_count++] = make_pack(1, PACK_TYPE_CHOW, pai + 1);
		for (intptr_t i = 17; i < 72; ++i) {
			if (hand[i])
			{
				--hand[i];
				myHand.tile_count = 0;
				for (intptr_t j = 17; j < 72; ++j)
					if (hand[j])
						for (int k = 0; k < hand[j]; ++k)
							myHand.standing_tiles[myHand.tile_count++] = j;
				int res = if_wait(myHand, all, test);
				if (res)
				{
					iflis = 1;
					return 1;
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
		}
		myHand.pack_count--;
		++hand[pai + 1]; ++hand[pai + 2];
	}
	if (da > 0)
	{
		//printf("before chi:    da: %x\n", da);
		//show(hand);
		if ((da & 3) == 1)
			myHand.fixed_packs[myHand.pack_count++] = make_pack(3, PACK_TYPE_CHOW, pai - 1), --hand[pai - 1], --hand[pai - 2];
		else if ((da & 3) == 2)
			myHand.fixed_packs[myHand.pack_count++] = make_pack(2, PACK_TYPE_CHOW, pai), --hand[pai - 1], --hand[pai + 1];
		else if ((da & 3) == 3)
			myHand.fixed_packs[myHand.pack_count++] = make_pack(1, PACK_TYPE_CHOW, pai + 1), --hand[pai + 1], --hand[pai + 2];
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
	max = -10000000;
	evaluate(1, 1, max);
	int da = 0;
	//�ܲ�������
	//����ط��ܲ��ܸĳɡ�2�������ƺ͸��Ƶ����չ�ֵ��һ���Աȣ�
	if (hand[pai] == 2)
	{
		hand[pai] -= 2;
		//��¼��¶��Ϣ������
		myHand.fixed_packs[myHand.pack_count++] = make_pack(player, PACK_TYPE_PUNG, pai);
		//����֮��Ӧ�ô�������
		for (intptr_t i = 17; i < 72; ++i) {
			if (hand[i])
			{
				--hand[i];
				myHand.tile_count = 0;
				for (intptr_t j = 17; j < 72; ++j)
					if (hand[j])
						for (int k = 0; k < hand[j]; ++k)
							myHand.standing_tiles[myHand.tile_count++] = j;
				int res = if_wait(myHand, all, test);
				if (res)
				{
					iflis = 1;
					return 1;
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
		//����ɶ��
		if (da == 0)
		{
			myHand.pack_count--;
			hand[pai] += 2;
			return 0;
		}
		--hand[da];
		return da;
	}

	//����
	/*
	if (hand[pai] == 3)
	{
	hand[pai] -= 3;
	myHand.tile_count = 0;
	for (intptr_t j = 17; j < 72; ++j)
	if (hand[j])
	for (int k = 0; k < hand[j]; ++k)
	myHand.standing_tiles[myHand.tile_count++] = j;

	//��¼���Ƹ�¶
	myHand.fixed_packs[myHand.pack_count++] = make_pack(player, PACK_TYPE_KONG, pai);
	int res = if_wait(myHand, all, test);
	if (res)
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
	--myHand.pack_count;
	hand[pai] += 3;
	return 0;
	}
	return 100;
	}
	*/
	return 0;
}


void moda(tile_t *paichi, int &pos)
{
	++hand[paichi[pos]]; ++all[paichi[pos]];
	int max = -100000000;
	tile_t best = paichi[pos++];
	for (intptr_t i = 17; i < 72; ++i)
		if (hand[i])
		{
			--hand[i];
			myHand.tile_count = 0;
			for (intptr_t j = 17; j < 72; ++j)
				if (hand[j])
					for (int k = 0; k < hand[j]; ++k)
						myHand.standing_tiles[myHand.tile_count++] = j;
			int res = if_wait(myHand, all, test);
			if (res > 0)
			{
				iflis = 1;
				return;
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

//����ģ��
int simulate(tile_t *paichi, int n)
{
	int pos = 0;
	n -= 4;
	while (true && pos < n)
	{
		++all[paichi[pos]];
		//������Ը�
		peng(paichi[pos++], 3);
		//����Ѿ��������Ƶľ���
		if (iflis > 0)
			return pos;
		++all[paichi[pos]];
		peng(paichi[pos++], 2);
		//moda(paichi, pos);
		if (iflis > 0)
			return pos;
		++all[paichi[pos]];
		if (chi(paichi[pos]) == 0)
			peng(paichi[pos++], 1);
		if (iflis > 0)
			return pos;
		moda(paichi, pos);
		if (iflis > 0)
			return pos;
	}
	return 200;
}

tile_t decide()
{
	int cnt[15], score[15], tiles[15], num = -1, maxn = 0;
	int T = 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 9; ++j)
			for (int k = 0; k < 4 - all[i * 16 + j]; ++k)
				ceshi[T++] = i * 16 + j;
	for (int j = 1; j <= 7; ++j)
		for (int k = 0; k < 4 - all[64 + j]; ++k)
			ceshi[T++] = 64 + j;
	tile_t ret = 0;
	tile_table_t tmp, alltmp;
	intptr_t N = myHand.pack_count;
	memcpy(tmp, hand, sizeof(tmp));
	memset(score, 0, sizeof(score));
	memcpy(alltmp, all, sizeof(tmp));
	memset(cnt, 0, sizeof(cnt));
	for (intptr_t i = 17; i < 72; ++i) {
		if (hand[i])
		{
			--hand[i];
			tiles[++num] = i;//�᲻��û�п��Ǹ�����Ӱ��
			myHand.tile_count = 0;
			for (intptr_t j = 17; j < 72; ++j)
				if (hand[j])
					for (int k = 0; k < hand[j]; ++k)
						myHand.standing_tiles[myHand.tile_count++] = j;
			int res = if_waitnew(myHand, all, test);
			if (res)
				if (res > maxn)
					maxn = res, ret = i;
			++hand[i];
		}
	}
	if (maxn > 0)
	{
		S = maxn;
		return ret;
	}
	for (int i = 0; i <= num; ++i)
	{
		++cnt[i];
		--hand[tiles[i]];
		iflis = 0;
		random_shuffle(ceshi, ceshi + T);
		score[i] -= simulate(ceshi, T);
		memcpy(hand, tmp, sizeof(tmp));
		memcpy(all, alltmp, sizeof(alltmp));
		myHand.pack_count = N;
	}
	evaluatenew();
	int t = num + 1;
	DWORD start_time = GetTickCount();
	while (GetTickCount() - start_time < TIME)
	{
		double max = -1e20;
		int sti;
		for (int i = 0; i <= num; ++i)
		{
			double val = (double)score[i] / (double)cnt[i] + CP * sqrt(2 * log(t) / cnt[i]);
			if (val > max)
				max = val, sti = i;
		}
		++t;
		++cnt[sti];
		--hand[tiles[sti]];
		iflis = 0;
		random_shuffle(ceshi, ceshi + T);
		score[sti] -= simulate(ceshi, T);
		myHand.pack_count = N;
		memcpy(hand, tmp, sizeof(tmp));
		memcpy(all, alltmp, sizeof(alltmp));
	}
	int alltimes = 0;
	for (int i = 0; i <= num; ++i)
		alltimes += score[i];
	alltimes = alltimes / t;
	ret = 0;
	double best = (double)score[0] / (double)cnt[0];
	if (alltimes < -20)
		best -= 0.3*value[tiles[0]];
	else
		best -= 0.1*value[tiles[0]];
	if (leftTile <= EndGame)
		best += 0.07*((float)tileScore[tiles[0]]);
	else if (leftTile <= MiddleGame) best += 0.04*((float)tileScore[tiles[0]]);
	else best += 0.016*((float)tileScore[tiles[0]]);
	for (int i = 1; i <= num; ++i)
	{
		double temp = (double)score[i] / (double)cnt[i];
		if (alltimes < -20)
			temp -= 0.3*value[tiles[i]];
		else
			temp -= 0.1*value[tiles[i]];
		if (leftTile <= EndGame)
			temp += 0.07*((float)tileScore[tiles[i]]);
		else if (leftTile <= MiddleGame) temp += 0.04*((float)tileScore[tiles[i]]);
		else temp += 0.016*((float)tileScore[tiles[i]]);
		if (temp > best)
		{
			best = temp;
			ret = i;
		}
	}
	S = score[ret] / cnt[ret];
	return tiles[ret];
}


int decidenew(tile_t pai)
{
	bool GANG = false;




	for (int i = 0; i < myHand.pack_count; ++i)
		if ((myHand.fixed_packs[i] & 0xff) == pai && ((myHand.fixed_packs[i] >> 8) & 0xf) == PACK_TYPE_PUNG)
		{
			return 128;
		}
	for (int pai = 17; pai < 72; ++pai)
		if (hand[pai] == 4)
		{
			int res = -10000000;
			hand[pai] = 0;
			evaluate(1, 1, res);
			hand[pai] = 4;
			for (int i = 17; i < 72; ++i)
				if (hand[i])
				{
					--hand[i];
					int T = -10000000;
					evaluate(1, 1, T);
					if (T < res + 1000)
					{
						GANG = true;
						break;
					}
					++hand[i];
				}
			if (GANG)
				return 256 | pai;
		}


	/*int T = 0;
	for (int i = 1; i <= 3; ++i)
	for (int j = 1; j <= 9; ++j)
	for (int k = 0; k < 4 - all[i * 16 + j]; ++k)
	ceshi[T++] = i * 16 + j;
	for (int j = 1; j <= 7; ++j)
	for (int k = 0; k < 4 - all[64 + j]; ++k)
	ceshi[T++] = 64 + j;
	if (T > 70)
	{
	for (int i = 1; i <= 7; ++i)
	if (hand[64 + i] == 1)
	return 64 + i;
	if (hand[17] == 1 && hand[18] == 0 && hand[19] == 0)
	return 17;
	if (hand[25] == 1 && hand[24] == 0 && hand[23] == 0)
	return 25;
	if (hand[33] == 1 && hand[34] == 0 && hand[35] == 0)
	return 33;
	if (hand[41] == 1 && hand[40] == 0 && hand[39] == 0)
	return 41;
	if (hand[49] == 1 && hand[50] == 0 && hand[51] == 0)
	return 49;
	if (hand[57] == 1 && hand[56] == 0 && hand[55] == 0)
	return 57;
	if (hand[17] == 0 && hand[18] == 1 && hand[19] == 0 && hand[20] == 0)
	return 18;
	if (hand[25] == 0 && hand[24] == 1 && hand[23] == 0 && hand[22] == 0)
	return 24;
	if (hand[33] == 0 && hand[34] == 1 && hand[35] == 0 && hand[36] == 0)
	return 34;
	if (hand[41] == 0 && hand[40] == 1 && hand[39] == 0 && hand[38] == 0)
	return 40;
	if (hand[49] == 0 && hand[50] == 1 && hand[51] == 0 && hand[52] == 0)
	return 50;
	if (hand[57] == 0 && hand[56] == 1 && hand[55] == 0 && hand[54] == 0)
	return 56;
	for (int i = 19; i <= 56; ++i)
	if (hand[i] == 1 && hand[i - 1] == 0 && hand[i - 2] == 0 && hand[i + 1] == 0 && hand[i + 2] == 0)
	return i;
	}*/



	//cout << "hello" << endl;
	TIME = 800;
	return decide();
}


int chisti(tile_t pai, int &mark)
{
	evaluatenew();
	if (!WCP)
		return 0;
	int T = 0;
	if (pai<17 || pai > 57)
		return 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 9; ++j)
			for (int k = 0; k < 4 - all[i * 16 + j]; ++k)
				ceshi[T++] = i * 16 + j;
	for (int j = 1; j <= 7; ++j)
		for (int k = 0; k < 4 - all[64 + j]; ++k)
			ceshi[T++] = 64 + j;
	useful_table_t test;
	tile_table_t tmp, alltmp;
	intptr_t N = myHand.pack_count;
	memcpy(tmp, hand, sizeof(tmp));
	memcpy(alltmp, all, sizeof(tmp));
	myHand.tile_count = 0;
	for (intptr_t j = 17; j < 72; ++j)
		if (hand[j])
			for (int k = 0; k < hand[j]; ++k)
				myHand.standing_tiles[myHand.tile_count++] = j;
	int max = if_waitnew(myHand, all, test);
	if (max)
	{
		if (max < 100 && myHand.tile_count <= 7)
			max = -10000000;
	}
	else
	{
		int c = 0;
		DWORD start_time = GetTickCount();
		while (GetTickCount() - start_time < 75)
		{
			++c;
			iflis = 0;
			random_shuffle(ceshi, ceshi + T);
			max -= simulate(ceshi, T);
			myHand.pack_count = N;
			memcpy(hand, tmp, sizeof(tmp));
			memcpy(all, alltmp, sizeof(alltmp));
		}
		max /= c;
	}
	action[myHand.pack_count] = "CHI";
	int da = 0;
	TIME = 250;
	if (hand[pai - 1] && hand[pai - 2])
	{
		--hand[pai - 1]; --hand[pai - 2];
		mark = -2;
		action_tile[myHand.pack_count] = int2tile(pai - 1);
		myHand.fixed_packs[myHand.pack_count++] = make_pack(3, PACK_TYPE_CHOW, pai - 1);
		tile_t ret = decide();
		if (S > max)
			max = S, da = (ret << 2) | 1;
		myHand.pack_count--;
		++hand[pai - 1]; ++hand[pai - 2];
	}
	if (hand[pai - 1] && hand[pai + 1])
	{
		--hand[pai - 1]; --hand[pai + 1];
		mark = -2;
		action_tile[myHand.pack_count] = int2tile(pai);
		myHand.fixed_packs[myHand.pack_count++] = make_pack(2, PACK_TYPE_CHOW, pai);
		tile_t ret = decide();
		if (S > max)
			max = S, da = (ret << 2) | 2;
		myHand.pack_count--;
		++hand[pai - 1]; ++hand[pai + 1];
	}
	if (hand[pai + 1] && hand[pai + 2])
	{
		--hand[pai + 1]; --hand[pai + 2];
		mark = -2;
		action_tile[myHand.pack_count] = int2tile(pai + 1);
		myHand.fixed_packs[myHand.pack_count++] = make_pack(1, PACK_TYPE_CHOW, pai + 1);
		tile_t ret = decide();
		if (S > max)
			max = S, da = (ret << 2) | 3;
		myHand.pack_count--;
		++hand[pai + 1]; ++hand[pai + 2];
	}
	if (da > 0)
	{
		if (max > 0)
			S = 1000;
		//printf("before chi:    da: %x\n", da);
		//show(hand);
		if ((da & 3) == 1) {
			myHand.fixed_packs[myHand.pack_count++] = make_pack(3, PACK_TYPE_CHOW, pai - 1), --hand[pai - 1], --hand[pai - 2];
			mark = 1;
		}
		if ((da & 3) == 2) {
			myHand.fixed_packs[myHand.pack_count++] = make_pack(2, PACK_TYPE_CHOW, pai), --hand[pai - 1], --hand[pai + 1];
			mark = 2;
		}
		if ((da & 3) == 3) {
			myHand.fixed_packs[myHand.pack_count++] = make_pack(1, PACK_TYPE_CHOW, pai + 1), --hand[pai + 1], --hand[pai + 2];
			mark = 3;
		}
		--hand[da >> 2];
		//show(hand);
		//printf("get : %x\n", (int)pai);
		//printf("CHI:\n");
		//system("pause");
	}
	//--myHand.pack_count;
	return da >> 2;
}

int pengsti(tile_t pai, int player)
{
	evaluatenew();
	if (!WCP)
		return 0;
	int T = 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 9; ++j)
			for (int k = 0; k < 4 - all[i * 16 + j]; ++k)
				ceshi[T++] = i * 16 + j;
	for (int j = 1; j <= 7; ++j)
		for (int k = 0; k < 4 - all[64 + j]; ++k)
			ceshi[T++] = 64 + j;
	useful_table_t test;
	tile_table_t tmp, alltmp;
	intptr_t N = myHand.pack_count;
	memcpy(tmp, hand, sizeof(tmp));
	memcpy(alltmp, all, sizeof(tmp));
	myHand.tile_count = 0;
	for (intptr_t j = 17; j < 72; ++j)
		if (hand[j])
			for (int k = 0; k < hand[j]; ++k)
				myHand.standing_tiles[myHand.tile_count++] = j;
	int max = if_waitnew(myHand, all, test);

	if (max)
	{
		if (max < 100 && myHand.tile_count <= 7)
			max = -10000000;
	}
	else
	{
		int c = 0;
		DWORD start_time = GetTickCount();
		while (GetTickCount() - start_time < 75)
		{
			++c;
			iflis = 0;
			random_shuffle(ceshi, ceshi + T);
			max -= simulate(ceshi, T);
			myHand.pack_count = N;
			memcpy(hand, tmp, sizeof(tmp));
			memcpy(all, alltmp, sizeof(alltmp));
		}
		max /= c;
	}

	int da = 0;
	TIME = 700;
	if (hand[pai] == 2)
	{
		hand[pai] -= 2;
		myHand.fixed_packs[myHand.pack_count] = make_pack(player, PACK_TYPE_PUNG, pai);
		action_tile[myHand.pack_count] = int2tile(pai);
		action[myHand.pack_count++] = "PENG";
		tile_t ret = decide();
		//if (pai > 64)
		//return ret;
		if (S > max)
			max = S, da = ret;
		if (da == 0)
		{
			myHand.pack_count--;
			hand[pai] += 2;
			return 0;
		}
		S = max;
		--hand[da];
		return da;
	}
	if (hand[pai] == 3)
	{
		int no = -1000000, yes = -1000000;
		evaluate(1, 1, no);
		hand[pai] -= 3;
		evaluate(1, 1, yes);
		if (yes > no - 1000)
			return 100;
	}
	return 0;
}
//��ʼ����ǰ״̬
void init()
{
	//int cnt = 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 9; ++j)
		{
			all[i * 16 + j] = 0;
			hand[i * 16 + j] = 0;
			wait[i * 16 + j] = false;
			/*for (int k = 0; k < 4; ++k)
			paichi[cnt++] = i * 16 + j;*/
		}
	for (int j = 1; j <= 7; ++j)
	{
		all[64 + j] = 0;
		hand[64 + j] = 0;
		wait[64 + j] = false;
		/*for (int k = 0; k < 4; ++k)
		paichi[cnt++] = 64 + j;*/
	}
	//srand((unsigned)time(NULL));
	//random_shuffle(paichi, paichi + 34 * 4);
}



//���Ƶ��ַ�����ʾת�������

//�жϵ�ǰ�Ƿ����
/*
*@param
pack:��ҵ����ƣ�ÿ���һ��stringΪ"PENG" "GANG" "CHI" ����֮һ���ڶ���stringΪ�ƴ��루���Ʊ�ʾ�м��ƴ��룩��
������int������ʱ��ʾ�ϼҡ��Լҡ��¼ҹ��ƣ���ʱ123��ʾ�ڼ������ϼҹ��ơ�
hand:��ҵİ��ƣ�stringΪ�ƴ���
winTile:�͵������ƴ���
flowerCount:������
isZIMO:�Ƿ�Ϊ��������
isJUEZHANG:�Ƿ�Ϊ�;���
isGANG:���ڸܣ����ϵ��ʱΪǹ�ܺͣ�����������Ϊ���Ͽ���
isLast:�Ƿ�Ϊ��ǽ���һ�ţ���������Ϊ���ֻش�������Ϊ��������
menFeng:�ŷ磬0123��ʾ��������
quanFeng:Ȧ�磬0123��ʾ��������
��������vector��ÿ��int��ʾ���������Ϊ�ܷ�����string��ÿ�����ε�����
*
*/
bool testhu(tile_t pai, bool isZIMO, bool isJUEZHANG, bool isGANG, bool isLAST)
{
	useful_table_t test;
	myHand.tile_count = 0;
	for (intptr_t j = 17; j < 72; ++j)
		if (hand[j])
			for (int k = 0; k < hand[j]; ++k)
				myHand.standing_tiles[myHand.tile_count++] = j;
	if_wait(myHand, all, test);
	if (!test[pai])
		return false;

	cout << "test all:" << endl;
	for (int i = 1; i < 72; ++i) {
	//cout << int2tile(i) << ": " << all[i] << endl;
	}
	ofstream file;
	file.open("Fancal.txt", ios::out);

	file << "isZIMO: " << isZIMO << " isJUEZHANG: " << isJUEZHANG << " isGANG: " << isGANG << " isLAST: " << isLAST << endl;
	file << "flowercnt: " << flowerCnt << endl;
	//myHand.tile_count = 0;
	//for (intptr_t j = 17; j < 72; ++j)
	//if (hand[j])
	//for (int k = 0; k < hand[j]; ++k)
	//myHand.standing_tiles[myHand.tile_count++] = j;
	vector<pair<string, pair<string, int> > > pack;//��¼��¶����
	vector<string> handStr;//����
	string winTile = int2tile(pai);
	file << "winTile: " << winTile << endl;
	//��¼��¶
	for (int i = 0; i < action_cnt; ++i) {
		pack.push_back(make_pair(action[i], make_pair(action_tile[i], action_player[i])));
		file << action[i] << " " << action_tile[i] << " " << action_player[i] << endl;
	}
	//��¼����
	for (int i = 0; i < myHand.tile_count; ++i) {
		handStr.push_back(int2tile(myHand.standing_tiles[i]));
		file << int2tile(myHand.standing_tiles[i]) << " ";
	}
	file << endl;
	vector<pair<int, string> > fan = MahjongFanCalculator(pack, handStr, winTile, flowerCnt,
		isZIMO, isJUEZHANG, isGANG, isLAST, myID, currentQuan);
	int Fan = 0;
	for (int i = 0; i < fan.size(); ++i) {
		Fan += fan[i].first;
		file << fan[i].first << " " << fan[i].second << endl;
	}
	file << "Fan: " << Fan << endl;

	if (Fan >= 8) return true;

	return false;
}
/*
bool ifneg() {
for (int i = 0; i < 72; ++i)
if (hand[i] > 500)
return true;
return false;
}
*/
int main(int argc, const char *argv[])
{
	srand(time(0));
	//file.open("predict.txt", ios::out);
	// ����JSON
	string str;
	getline(cin, str);
	Json::Reader reader;
	Json::Value input;
	reader.parse(str, input);

	init();
	MahjongInit();
	int ting = 13, enterting = 1;

	// �����Լ��յ���������Լ���������������ָ�״̬
	int turnID = input["requests"].size();
	for (int ii = 0; ii < turnID; ii++)
	{
		istringstream in(input["requests"][ii].asString()),
			out(input["responses"][ii].asString());
		string act = "";

		int type, who;
		string card, what;
		// �����Ϣ����
		in >> type;
		string tmp;
		int playerID;
		switch (type)
		{
		case 0:
			// ��֪���
			in >> myID; //��¼�ҵ���Һ���
			UpPlayer = (myID - 1 + 4) % 4;//����ϼҵı��
			DownPlayer = (myID + 1 + 4) % 4;//�¼�
			CrossPlayer = (myID + 2 + 4) % 4;//�Լ�
										  //��֪��Ȧ
			in >> currentQuan;
			wind = 65 + currentQuan;
			wind_s = 65 + myID;
			// responseһ����PASS�����ÿ���
			break;
		case 1:
			// ��֪����
			//����ÿ����ҵĻ�������
			int hua[4];
			for (int i = 0; i < 4; ++i) {
				in >> hua[i];
				leftTile -= hua[i];
			}
			//�����ҵ�����
			for (int j = 0; j < 13; j++) {
				in >> tmp;
				changeTileState(hand, tmp, 1);
				changeTileState(all, tmp, 1);
			}
			//��������Ϊ13����¶����Ϊ0
			myHand.tile_count = 13;
			myHand.pack_count = 0;
			//��¼����
			flowerCnt = hua[myID];
			//���»��Ƶ�����
			for (int i = 0; i < hua[myID]; ++i) {
				in >> tmp;
				changeTileState(hand, tmp, 1);
				changeTileState(all, tmp, 1);
			}
			//cardCount = 13;
			// responseһ����PASS�����ÿ���
			break;
		case 2:
			// ���ƣ���������
			--leftTile;
			in >> tmp;
			changeTileState(hand, tmp, 1);
			changeTileState(all, tmp, 1);
			/*if (ifneg()) {
			cout << "1699" << endl;
			system("pause");
			}*/
			drawcard = tmp;
			//cout << tmp << endl;
			lastcard = tmp;//��¼��������һ������Ϊ�˰��ܲ���
			lastact = "DRAW";//��¼��һ������
			if (lastact == "GANG"&&lastPlayer == myID)
				flowerOnGang = true;
			else flowerOnGang = false;
			break;
		case 3:
			//����
			in >> playerID;//��ȡ���ID
			in >> act;//BUHUA������
					  //��ȡ������������
			if (act == "BUHUA") {
				--leftTile;
				in >> tmp;
				//����all��Ϣ
				changeTileState(all, tmp, 1);
				/*if (ifneg()) {
				cout << "1718" << endl;
				system("pause");
				}*/
				if (playerID == myID) {
					flowerOnGang = false;
					changeTileState(hand, tmp, 1);
					++flowerCnt;
				}
			}
			else if (act == "DRAW") {
				--leftTile;
			}
			//��Ҵ���
			else if (act == "PLAY") {
				in >> tmp;
				if (playerID == myID) {
					changeTileState(hand, tmp, -1);
					/*if (ifneg()) {
					cout << "1736" << endl;
					system("pause");
					}*/
					flowerOnGang = false;
				}
				else {
					changeTileState(all, tmp, 1);
					changeTileState(enemyPlayTiles[playerID], tmp, 1);//��¼��Ҵ���
				}
				lastcard = tmp;//��¼���һ����
				ifUpPlayer = UpPlayer == playerID ? true : false;//�ж��Ƿ�Ϊ�ϼҳ���
			}
			//����
			else if (act == "PENG") {
				in >> tmp;//���������
				if (playerID == myID) {
					flowerOnGang = false;


					action_player[action_cnt] = (myID - lastPlayer + 4) % 4;//��¼���ϼһ����¼һ��ǶԼң��ֱ���3,2,1
					action[action_cnt] = "PENG";
					action_tile[action_cnt] = lastcard;
					++action_cnt;
					int pai = tile2int(lastcard);
					//��¼������Ϣ
					myHand.fixed_packs[myHand.pack_count++] = make_pack(myID, PACK_TYPE_PUNG, pai);
					changeTileState(hand, lastcard, -2);//��������֮�����������
														/*if (ifneg()) {
														cout << "1761" << endl;
														system("pause");
														}*/
					myHand.tile_count -= 2;//������������
					lastcard = tmp;
					changeTileState(hand, tmp, -1);
				}
				else {
					//�����ϻغ���Ҵ��Ƶ���Ϣ�Ѿ�������һ��all���������ֻ����2��
					changeTileState(all, lastcard, 2);
					changeTileState(enemyPlayTiles[playerID], lastcard, 2);//�൱�ڴ��ȥ��������
					lastcard = tmp;
					changeTileState(all, lastcard, 1);
					changeTileState(enemyPlayTiles[playerID], lastcard, 1);
				}
			}
			//��
			else if (act == "CHI") {
				in >> tmp;//�м���
				if (playerID == myID) {
					flowerOnGang = false;
					//action_player[action_cnt] = lastPlayer;
					action[action_cnt] = "CHI";
					action_tile[action_cnt] = tmp;//��¼�м���
												  //++action_cnt;
					int pai = tile2int(tmp);
					int lastpai = tile2int(lastcard);
					//�����Լ����Ƶ�״̬
					if (lastpai == pai) {
						action_player[action_cnt] = 2;
						changeTileState(hand, int2tile(pai - 1), -1);
						changeTileState(hand, int2tile(pai + 1), -1);
					}
					else if (lastpai < pai) {
						action_player[action_cnt] = 1;
						changeTileState(hand, int2tile(pai), -1);
						changeTileState(hand, int2tile(pai + 1), -1);
					}
					else if (lastpai > pai) {
						action_player[action_cnt] = 3;
						changeTileState(hand, int2tile(pai - 1), -1);
						changeTileState(hand, int2tile(pai), -1);
					}
					/*if (ifneg()) {
					cout << "1803" << endl;
					system("pause");
					}*/
					++action_cnt;
					myHand.fixed_packs[myHand.pack_count++] = make_pack(myID, PACK_TYPE_CHOW, pai);
					myHand.tile_count -= 2;//������������
					in >> lastcard;//�����������
					changeTileState(hand, lastcard, -1);
				}
				else {
					if (tmp != lastcard) {
						changeTileState(all, tmp, 1);
						changeTileState(enemyPlayTiles[playerID], tmp, 1);
					}
					tmp[1] -= 1;
					if (tmp != lastcard) {
						changeTileState(all, tmp, 1);
						changeTileState(enemyPlayTiles[playerID], tmp, 1);
					}
					tmp[1] += 2;
					if (tmp != lastcard) {
						changeTileState(all, tmp, 1);
						changeTileState(enemyPlayTiles[playerID], tmp, 1);
					}
					in >> lastcard;
					changeTileState(all, lastcard, 1);
					changeTileState(enemyPlayTiles[playerID], tmp, 1);
				}
			}
			//�ܣ����ܺ�����
			else if (act == "GANG") {
				//����ǰ���
				if (lastact == "DRAW") {
					if (playerID == myID) {
						flowerOnGang = true;
						action_player[action_cnt] = 0;//��¼���ϼһ����¼һ��ǶԼ�
						action[action_cnt] = "GANG";
						action_tile[action_cnt] = lastcard;
						++action_cnt;
						int pai = tile2int(drawcard);
						//��¼���Ƹ�¶

						myHand.fixed_packs[myHand.pack_count++] = make_pack(myID, PACK_TYPE_KONG, pai);
						myHand.tile_count -= 4;//������������
						changeTileState(hand, drawcard, -4);
						/*if (ifneg()) {
						cout << "1838" << endl;
						system("pause");
						}*/
					}
				}
				//���������
				else {
					if (playerID == myID) {
						flowerOnGang = true;
						action_player[action_cnt] = (myID - lastPlayer + 4) % 4;//��¼���ϼһ����¼һ��ǶԼ�
						action[action_cnt] = "GANG";
						action_tile[action_cnt] = lastcard;
						++action_cnt;
						int pai = tile2int(lastcard);
						//cout << "lastcard:" << lastcard << endl;
						//cout << pai << endl;
						//��¼���Ƹ�¶
						myHand.fixed_packs[myHand.pack_count++] = make_pack(myID, PACK_TYPE_KONG, pai);
						myHand.tile_count -= 3;
						/*for (int i = 0; i < 72; ++i)
						cout << hand[i] << " ";
						cout << endl;*/
						changeTileState(hand, lastcard, -3);
						/*if (ifneg()) {
						cout << "1857" << endl;
						for (int i = 0; i < 72; ++i)
						cout << hand[i] << " ";
						cout << endl;
						system("pause");
						}*/
					}
					else {
						//���������ƽ׶��Ѿ��ж�������ֻ�ı�3��
						changeTileState(all, lastcard, 3);
						changeTileState(enemyPlayTiles[playerID], lastcard, 3);//�൱�ڴ��ȥ��1����
					}
				}
			}
			//����
			else if (act == "BUGANG") {
				in >> tmp;
				if (playerID == myID) {
					flowerOnGang = true;
					int pai = tile2int(tmp);
					int T = make_pack(myID, PACK_TYPE_PUNG, pai);
					int i;
					for (i = 0; i < myHand.pack_count; ++i)
						if (T == myHand.fixed_packs[i])
							break;
					myHand.fixed_packs[i] = make_pack(myID, PACK_TYPE_KONG, pai);
					changeTileState(hand, tmp, -1);
					//���Ķ�����Ϣ
					for (int i = 0; i < action_cnt; ++i) {
						if (action[i] == "PENG"&&action_tile[i] == tmp) {
							action[i] = "GANG";
							action_player[i] = 0;
							break;
						}
					}
					//����Ҫ�ı�����״̬
					/*if (ifneg()) {
					cout << "1881" << endl;
					system("pause");
					}*/
				}
				else {
					changeTileState(all, tmp, 1);
					changeTileState(enemyPlayTiles[playerID], tmp, 1);//�൱�ڴ��ȥ��һ����
				}
			}
			lastPlayer = playerID;//��¼��һ�����������
			ifUpPlayer = UpPlayer == playerID ? true : false;//�ж��Ƿ�Ϊ�ϼҳ���
			lastact = act;//��¼��һ������
			break;
		}
	}

	//if (leftTile >= FrontGame)
		//chanceTile();
	//if (leftTile <= MiddleGame)
		//safeTile();

	for (int i = 0; i < 4; ++i)
		if (i != myID)
			predictTile(i);//Ԥ���������

	// �����Լ����غ�����
	istringstream in(input["requests"][turnID - 1].asString());
	int type, who;
	string act, card, temp, myAction = "PASS", tmp;
	in >> type;
	if (type == 2) {
		//�ֵ��Ҵ���
		//������4�ֲ�����PLAY���ƣ�GANG���ƣ�BUGANG���ܣ�HU����
		//֮ǰ�Ĳ���һ��������
		int pai = tile2int(drawcard);
		//cout << "drawcard:" << drawcard << endl;
		/*for (int i = 0; i < 72; ++i)
		cout << hand[i] << "";
		cout << endl;
		cout << "Pai: " << pai << endl;*/

		//���������ж��Ƿ����
		bool isZIMO = lastact == "DRAW" ? true : false;
		bool isJUEZHANG = (all[pai] - hand[pai]) == 3 ? true : false;//һ������������������
		bool isLAST = leftTile == 0 ? true : false;
		changeTileState(hand, drawcard, -1);
		if (testhu(pai, isZIMO, isJUEZHANG, flowerOnGang, isLAST)) {
			myAction = "HU";
		}
		else {
			changeTileState(hand, drawcard, 1);

			if (enterting)
				++ting;

			int best = decidenew(pai);
			if (S > 0)
				enterting = 0;

			if (best == 128)
				myAction = "BUGANG";
			else if (best > 256)
			{
				myAction = "GANG ";
				myAction += int2tile((tile_t)(best & 0xff));
			}
			else if (best < 100)
			{
				myAction = "PLAY ";//����ط������⣬��֪���ǲ��Ǹܻ��߲���
				myAction += int2tile(best);
			}
		}
	}
	else if (type == 3 || type == 5 || type == 6 || type == 7) {
		//�����Ǳ��˴����ҽ��еĲ�����������PENG����CHI�ԣ�GANG�ܣ�HU����
		if ((lastact == "PLAY" || lastact == "PENG" || lastact == "CHI") && lastPlayer != myID) {
			int pai = tile2int(lastcard);
			bool isZIMO = false;
			bool isJUEZHANG = (all[pai] - hand[pai]) == 4 ? true : false;//һ������������������
			bool isLAST = leftTile == 0 ? true : false;
			bool isGANG = false;
			if (testhu(pai, isZIMO, isJUEZHANG, isGANG, isLAST)) {
				myAction = "HU";
			}
			else {
				//�������⣬����ǳԺ�������û�н��бȽ�
				int mark = -1, best;
				if (ifUpPlayer && ((best = chisti(pai, mark)) != 0)) {
					myAction = "CHI ";
					if (mark == 1)
						myAction += int2tile(pai - 1);
					else if (mark == 2)
						myAction += int2tile(pai);
					else myAction += int2tile(pai + 1);
					myAction += " ";
					myAction += int2tile(best);
				}

				if (mark == -1)
					best = pengsti(pai, lastPlayer);
				if (best && mark == -1) {
					if (best == 100)
						myAction = "GANG";
					else {
						myAction = "PENG ";
						myAction += int2tile(best);
					}
				}

			}
		}

	}
	else if (type == 9) {
		//�����ǿ��Խ������ܺ��ģ���ʱ��ֱ��PASS��
		if (lastact == "BUGANG"&&lastPlayer != myID&&testhu(tile2int(lastcard), false, false, true, false)) {
			myAction = "HU";
		}
	}
	// ��������ֻ��PASS

	// �������JSON
	Json::Value ret;
	ret["response"] = myAction;
	ret["data"] = "";
	Json::FastWriter writer;
	std::cout << writer.write(ret) << endl;
	system("pause");
	return 0;
}