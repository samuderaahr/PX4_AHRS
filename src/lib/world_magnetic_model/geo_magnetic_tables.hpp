/****************************************************************************
 *
 *   Copyright (c) 2020-2021 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// *INDENT-OFF*
// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2022.4219,
static constexpr const int16_t declination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ {  25990, 24245, 22499, 20754, 19009, 17263, 15518, 13773, 12027, 10282,  8537,  6791,  5046,  3301,  1556,  -190, -1935, -3680, -5426, -7171, -8916,-10661,-12407,-14152,-15897,-17643,-19388,-21133,-22879,-24624,-26370,-28115,-29860, 31226, 29481, 27735, 25990, },
	/* LAT: -80 */ {  22557, 20425, 18484, 16709, 15069, 13530, 12066, 10654,  9279,  7929,  6597,  5278,  3969,  2664,  1357,    38, -1303, -2675, -4084, -5536, -7030, -8566,-10143,-11762,-13426,-15144,-16929,-18801,-20783,-22901,-25175,-27609,-30178, 30014, 27395, 24888, 22557, },
	/* LAT: -70 */ {  14975, 13577, 12452, 11491, 10623,  9792,  8951,  8064,  7111,  6092,  5022,  3929,  2844,  1788,   766,  -244, -1281, -2386, -3586, -4885, -6264, -7694, -9141,-10583,-12009,-13424,-14852,-16337,-17960,-19872,-22389,-26183, 30730, 24152, 19624, 16847, 14975, },
	/* LAT: -60 */ {   8411,  8167,  7888,  7616,  7364,  7112,  6805,  6373,  5759,  4940,  3940,  2828,  1708,   679,  -203,  -962, -1691, -2513, -3515, -4710, -6039, -7408, -8729, -9939,-11004,-11904,-12620,-13115,-13287,-12838,-10739, -3518,  4884,  7640,  8415,  8544,  8411, },
	/* LAT: -50 */ {   5478,  5515,  5460,  5373,  5300,  5264,  5231,  5105,  4762,  4101,  3092,  1820,   478,  -703, -1576, -2142, -2540, -2979, -3662, -4673, -5915, -7191, -8332, -9235, -9835,-10076, -9883, -9128, -7621, -5261, -2357,   391,  2500,  3924,  4799,  5273,  5478, },
	/* LAT: -40 */ {   3949,  4042,  4051,  4008,  3949,  3916,  3922,  3912,  3740,  3207,  2186,   746,  -819, -2135, -3001, -3454, -3639, -3700, -3867, -4433, -5407, -6483, -7369, -7910, -8019, -7644, -6756, -5373, -3662, -1959,  -498,   723,  1766,  2631,  3287,  3718,  3949, },
	/* LAT: -30 */ {   2979,  3065,  3097,  3084,  3027,  2949,  2890,  2857,  2731,  2255,  1222,  -295, -1903, -3159, -3901, -4249, -4330, -4122, -3689, -3464, -3824, -4571, -5270, -5622, -5499, -4914, -3955, -2749, -1540,  -595,    83,   683,  1306,  1909,  2418,  2780,  2979, },
	/* LAT: -20 */ {   2336,  2383,  2402,  2405,  2364,  2271,  2165,  2089,  1944,  1450,   397, -1090, -2570, -3633, -4169, -4288, -4087, -3532, -2671, -1872, -1592, -1945, -2594, -3065, -3103, -2745, -2111, -1294,  -518,   -28,   234,   536,   976,  1454,  1876,  2183,  2336, },
	/* LAT: -10 */ {   1943,  1937,  1917,  1916,  1889,  1806,  1697,  1607,  1423,   874,  -185, -1562, -2836, -3668, -3939, -3714, -3141, -2361, -1515,  -759,  -292,  -323,  -791, -1298, -1512, -1423, -1110,  -611,  -114,   127,   176,   336,   707,  1144,  1537,  1824,  1943, },
	/* LAT:   0 */ {   1730,  1697,  1642,  1635,  1625,  1558,  1454,  1342,  1089,   469,  -570, -1796, -2852, -3442, -3444, -2947, -2181, -1399,  -746,  -209,   205,   318,    41,  -376,  -632,  -688,  -590,  -328,   -38,    51,    -9,    79,   420,   862,  1281,  1601,  1730, },
	/* LAT:  10 */ {   1594,  1602,  1561,  1579,  1606,  1558,  1438,  1253,   878,   161,  -859, -1935, -2764, -3106, -2906, -2302, -1526,  -814,  -298,    84,   410,   560,   399,    77,  -158,  -266,  -289,  -209,  -104,  -146,  -285,  -259,    42,   496,   977,  1384,  1594, },
	/* LAT:  20 */ {   1411,  1560,  1622,  1715,  1802,  1783,  1630,  1329,   785,   -70, -1113, -2065, -2664, -2777, -2452, -1852, -1141,  -491,   -30,   281,   540,   687,   597,   354,   154,    36,   -56,  -120,  -200,  -390,  -627,  -686,  -452,    -5,   536,  1054,  1411, },
	/* LAT:  30 */ {   1111,  1478,  1738,  1963,  2123,  2135,  1949,  1528,   801,  -227, -1345, -2224, -2642, -2583, -2186, -1608,  -952,  -334,   130,   436,   668,   816,   796,   648,   498,   373,   216,     5,  -278,  -652, -1021, -1181, -1022,  -596,   -20,   589,  1111, },
	/* LAT:  40 */ {    754,  1341,  1835,  2228,  2478,  2522,  2308,  1776,   866,  -361, -1601, -2470, -2794, -2644, -2200, -1608,  -955,  -325,   187,   552,   824,  1023,  1118,  1108,  1031,   883,   614,   204,  -335,  -941, -1463, -1708, -1592, -1176,  -578,    95,   754, },
	/* LAT:  50 */ {    465,  1212,  1894,  2451,  2818,  2925,  2697,  2044,   904,  -593, -2018, -2936, -3233, -3043, -2554, -1908, -1198,  -499,   118,   625,  1044,  1401,  1682,  1853,  1872,  1685,  1241,   533,  -361, -1264, -1944, -2231, -2107, -1666, -1031,  -299,   465, },
	/* LAT:  60 */ {    271,  1124,  1930,  2625,  3130,  3344,  3131,  2320,   806, -1154, -2874, -3857, -4112, -3852, -3280, -2534, -1707,  -866,   -56,   696,  1389,  2021,  2565,  2962,  3122,  2937,  2299,  1183,  -231, -1552, -2422, -2732, -2568, -2074, -1380,  -579,   271, },
	/* LAT:  70 */ {     39,   975,  1873,  2673,  3288,  3583,  3332,  2198,   -39, -2755, -4710, -5537, -5547, -5063, -4293, -3357, -2331, -1264,  -188,   873,  1899,  2866,  3735,  4444,  4892,  4926,  4319,  2849,   656, -1453, -2754, -3199, -3040, -2508, -1758,  -888,    39, },
	/* LAT:  80 */ {   -657,   266,  1119,  1811,  2196,  2014,   818, -1786, -4993, -7115, -7869, -7741, -7113, -6196, -5104, -3905, -2638, -1331,    -5,  1323,  2638,  3921,  5149,  6289,  7286,  8047,  8392,  7952,  6034,  2270, -1332, -3056, -3426, -3101, -2427, -1579,  -657, },
	/* LAT:  90 */ { -29886,-28141,-26395,-24650,-22905,-21159,-19414,-17669,-15923,-14178,-12433,-10688, -8943, -7197, -5452, -3707, -1962,  -217,  1528,  3274,  5019,  6764,  8509, 10255, 12000, 13745, 15491, 17236, 18982, 20727, 22473, 24218, 25964, 27709, 29455, 31200,-29886, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2022.4219,
static constexpr const int16_t inclination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ { -12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572,-12572, },
	/* LAT: -80 */ { -13657,-13524,-13363,-13183,-12989,-12787,-12583,-12383,-12192,-12015,-11858,-11724,-11614,-11528,-11464,-11423,-11403,-11405,-11433,-11487,-11570,-11685,-11829,-12003,-12201,-12418,-12647,-12880,-13108,-13321,-13507,-13657,-13762,-13813,-13810,-13756,-13657, },
	/* LAT: -70 */ { -14106,-13787,-13468,-13145,-12813,-12469,-12114,-11756,-11413,-11104,-10851,-10667,-10555,-10502,-10488,-10492,-10499,-10509,-10532,-10588,-10696,-10870,-11116,-11431,-11803,-12221,-12668,-13133,-13599,-14051,-14469,-14814,-15004,-14950,-14720,-14422,-14106, },
	/* LAT: -60 */ { -13519,-13165,-12827,-12494,-12151,-11779,-11364,-10909,-10441,-10010, -9680, -9503, -9500, -9636, -9840,-10033,-10159,-10203,-10191,-10177,-10224,-10382,-10670,-11078,-11576,-12132,-12718,-13314,-13902,-14464,-14961,-15251,-15075,-14691,-14285,-13892,-13519, },
	/* LAT: -50 */ { -12496,-12154,-11823,-11501,-11178,-10831,-10432, -9961, -9431, -8909, -8518, -8391, -8591, -9051, -9615,-10127,-10488,-10652,-10623,-10472,-10330,-10334,-10554,-10969,-11511,-12103,-12689,-13228,-13675,-13973,-14081,-14008,-13805,-13521,-13193,-12846,-12496, },
	/* LAT: -40 */ { -11240,-10892,-10545,-10200, -9860, -9522, -9161, -8735, -8214, -7649, -7222, -7178, -7636, -8459, -9380,-10210,-10870,-11306,-11448,-11282,-10940,-10668,-10659,-10939,-11400,-11905,-12351,-12674,-12833,-12838,-12748,-12611,-12432,-12200,-11914,-11586,-11240, },
	/* LAT: -30 */ {  -9602, -9224, -8845, -8455, -8063, -7687, -7330, -6939, -6426, -5814, -5361, -5442, -6209, -7410, -8661, -9757,-10672,-11383,-11784,-11776,-11406,-10899,-10564,-10563,-10814,-11135,-11392,-11505,-11443,-11268,-11093,-10959,-10813,-10606,-10324, -9979, -9602, },
	/* LAT: -20 */ {  -7371, -6932, -6516, -6088, -5644, -5213, -4822, -4408, -3842, -3156, -2707, -2965, -4074, -5685, -7313, -8683, -9750,-10527,-10967,-11003,-10641,-10027, -9469, -9224, -9272, -9435, -9576, -9594, -9422, -9150, -8956, -8869, -8765, -8557, -8241, -7829, -7371, },
	/* LAT: -10 */ {  -4415, -3881, -3428, -2992, -2535, -2084, -1670, -1215,  -587,   117,   480,    55, -1273, -3189, -5164, -6774, -7871, -8506, -8772, -8710, -8302, -7618, -6954, -6608, -6569, -6662, -6779, -6803, -6615, -6319, -6165, -6174, -6134, -5918, -5534, -5007, -4415, },
	/* LAT:   0 */ {   -906,  -285,   179,   581,   999,  1415,  1806,  2250,  2836,  3414,  3617,  3122,  1828,   -81, -2125, -3776, -4785, -5215, -5274, -5104, -4664, -3948, -3243, -2872, -2812, -2881, -3006, -3080, -2950, -2715, -2660, -2804, -2867, -2680, -2256, -1627,  -906, },
	/* LAT:  10 */ {   2561,  3186,  3618,  3959,  4313,  4680,  5033,  5421,  5873,  6244,  6281,  5793,  4712,  3147,  1457,    82,  -724,  -972,  -881,  -645,  -234,   404,  1037,  1374,  1437,  1392,  1292,  1200,  1243,  1346,  1270,  1003,   812,   884,  1236,  1838,  2561, },
	/* LAT:  20 */ {   5416,  5943,  6321,  6616,  6929,  7273,  7616,  7964,  8298,  8499,  8412,  7950,  7116,  6020,  4895,  3987,  3457,  3338,  3488,  3731,  4062,  4527,  4987,  5242,  5298,  5281,  5232,  5175,  5164,  5146,  4972,  4639,  4342,  4252,  4424,  4846,  5416, },
	/* LAT:  30 */ {   7569,  7941,  8258,  8540,  8849,  9196,  9554,  9896, 10173, 10287, 10143,  9722,  9094,  8383,  7722,  7211,  6920,  6878,  7020,  7231,  7477,  7776,  8064,  8238,  8295,  8308,  8310,  8301,  8278,  8196,  7974,  7622,  7267,  7047,  7031,  7225,  7569, },
	/* LAT:  40 */ {   9266,  9486,  9742, 10027, 10354, 10715, 11083, 11423, 11675, 11758, 11609, 11249, 10776, 10303,  9907,  9624,  9474,  9470,  9580,  9742,  9917, 10101, 10272, 10397, 10475, 10535, 10590, 10623, 10607, 10497, 10256,  9906,  9539,  9254,  9111,  9123,  9266, },
	/* LAT:  50 */ {  10802, 10923, 11124, 11394, 11717, 12071, 12426, 12743, 12965, 13025, 12886, 12588, 12224, 11878, 11603, 11416, 11323, 11319, 11386, 11488, 11602, 11718, 11834, 11950, 12068, 12190, 12303, 12376, 12367, 12242, 11997, 11669, 11330, 11045, 10855, 10775, 10802, },
	/* LAT:  60 */ {  12319, 12392, 12542, 12761, 13031, 13332, 13634, 13901, 14077, 14105, 13969, 13720, 13431, 13160, 12939, 12782, 12691, 12660, 12675, 12723, 12790, 12875, 12981, 13113, 13272, 13448, 13612, 13722, 13728, 13608, 13384, 13105, 12826, 12589, 12419, 12328, 12319, },
	/* LAT:  70 */ {  13758, 13801, 13896, 14038, 14218, 14422, 14630, 14812, 14916, 14897, 14759, 14558, 14340, 14136, 13962, 13827, 13733, 13678, 13659, 13672, 13714, 13785, 13889, 14025, 14191, 14378, 14562, 14703, 14750, 14678, 14517, 14319, 14124, 13959, 13839, 13771, 13758, },
	/* LAT:  80 */ {  14998, 15010, 15048, 15108, 15184, 15270, 15349, 15394, 15376, 15297, 15184, 15060, 14937, 14823, 14723, 14641, 14579, 14539, 14520, 14524, 14550, 14599, 14671, 14763, 14875, 15001, 15136, 15269, 15376, 15420, 15382, 15296, 15200, 15116, 15052, 15012, 14998, },
	/* LAT:  90 */ {  15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, 15395, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2022.4219,
static constexpr const int16_t strength_table[19][37] {
	//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
	/* LAT: -90 */ {  5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, 5452, },
	/* LAT: -80 */ {  6058, 5995, 5916, 5824, 5721, 5610, 5492, 5370, 5248, 5128, 5014, 4908, 4815, 4735, 4672, 4627, 4602, 4600, 4622, 4668, 4738, 4832, 4946, 5078, 5222, 5371, 5521, 5664, 5795, 5909, 6002, 6071, 6115, 6135, 6130, 6104, 6058, },
	/* LAT: -70 */ {  6303, 6170, 6020, 5855, 5677, 5485, 5280, 5065, 4846, 4630, 4428, 4245, 4087, 3956, 3852, 3776, 3728, 3716, 3744, 3820, 3948, 4128, 4356, 4624, 4919, 5226, 5529, 5813, 6063, 6267, 6418, 6514, 6556, 6548, 6499, 6415, 6303, },
	/* LAT: -60 */ {  6188, 5996, 5795, 5586, 5368, 5133, 4877, 4598, 4306, 4016, 3749, 3522, 3342, 3207, 3108, 3035, 2984, 2964, 2990, 3080, 3248, 3500, 3826, 4212, 4634, 5068, 5489, 5873, 6198, 6447, 6610, 6689, 6691, 6628, 6515, 6364, 6188, },
	/* LAT: -50 */ {  5845, 5615, 5383, 5153, 4921, 4676, 4405, 4102, 3774, 3442, 3140, 2899, 2738, 2646, 2598, 2564, 2530, 2504, 2509, 2581, 2754, 3043, 3439, 3910, 4417, 4922, 5398, 5816, 6156, 6397, 6536, 6577, 6534, 6424, 6263, 6065, 5845, },
	/* LAT: -40 */ {  5394, 5148, 4904, 4664, 4430, 4193, 3938, 3655, 3341, 3014, 2716, 2493, 2375, 2349, 2368, 2390, 2395, 2383, 2371, 2399, 2529, 2803, 3220, 3733, 4280, 4804, 5272, 5660, 5953, 6140, 6229, 6232, 6162, 6032, 5851, 5633, 5394, },
	/* LAT: -30 */ {  4879, 4638, 4400, 4165, 3939, 3720, 3502, 3270, 3015, 2740, 2482, 2299, 2228, 2253, 2320, 2391, 2457, 2507, 2530, 2542, 2609, 2806, 3167, 3655, 4186, 4683, 5102, 5419, 5623, 5722, 5749, 5722, 5643, 5511, 5331, 5115, 4879, },
	/* LAT: -20 */ {  4321, 4109, 3901, 3696, 3500, 3317, 3149, 2985, 2808, 2610, 2419, 2285, 2243, 2286, 2375, 2486, 2614, 2742, 2832, 2868, 2893, 2988, 3226, 3610, 4059, 4486, 4835, 5071, 5176, 5184, 5154, 5107, 5025, 4897, 4731, 4534, 4321, },
	/* LAT: -10 */ {  3790, 3630, 3477, 3331, 3195, 3075, 2972, 2880, 2783, 2669, 2547, 2447, 2401, 2425, 2510, 2639, 2795, 2954, 3078, 3141, 3156, 3182, 3304, 3555, 3881, 4203, 4468, 4631, 4667, 4615, 4547, 4483, 4395, 4270, 4121, 3958, 3790, },
	/* LAT:   0 */ {  3412, 3319, 3236, 3163, 3108, 3070, 3044, 3025, 3001, 2954, 2875, 2780, 2699, 2667, 2708, 2811, 2943, 3079, 3194, 3270, 3301, 3323, 3397, 3553, 3762, 3975, 4155, 4262, 4268, 4201, 4113, 4021, 3909, 3777, 3643, 3520, 3412, },
	/* LAT:  10 */ {  3283, 3252, 3232, 3228, 3253, 3300, 3356, 3410, 3445, 3436, 3367, 3252, 3125, 3030, 3003, 3043, 3124, 3222, 3323, 3408, 3472, 3534, 3621, 3739, 3874, 4012, 4132, 4203, 4205, 4144, 4034, 3891, 3729, 3570, 3435, 3338, 3283, },
	/* LAT:  20 */ {  3399, 3403, 3429, 3483, 3575, 3697, 3826, 3943, 4025, 4037, 3964, 3822, 3655, 3514, 3438, 3425, 3460, 3532, 3628, 3725, 3816, 3914, 4025, 4136, 4245, 4356, 4458, 4524, 4535, 4477, 4340, 4138, 3911, 3702, 3539, 3438, 3399, },
	/* LAT:  30 */ {  3723, 3730, 3785, 3885, 4028, 4199, 4375, 4531, 4640, 4667, 4594, 4438, 4249, 4084, 3978, 3931, 3934, 3985, 4071, 4169, 4266, 4372, 4488, 4606, 4725, 4852, 4972, 5059, 5085, 5028, 4872, 4633, 4359, 4104, 3905, 3777, 3723, },
	/* LAT:  40 */ {  4222, 4221, 4286, 4410, 4578, 4765, 4949, 5105, 5210, 5236, 5168, 5019, 4832, 4657, 4528, 4452, 4426, 4448, 4508, 4587, 4673, 4770, 4885, 5018, 5169, 5331, 5482, 5592, 5631, 5578, 5422, 5185, 4911, 4651, 4441, 4296, 4222, },
	/* LAT:  50 */ {  4832, 4825, 4881, 4992, 5138, 5298, 5448, 5569, 5642, 5651, 5588, 5461, 5298, 5134, 4996, 4898, 4843, 4831, 4855, 4905, 4974, 5065, 5184, 5333, 5509, 5693, 5859, 5978, 6022, 5978, 5848, 5652, 5427, 5211, 5031, 4902, 4832, },
	/* LAT:  60 */ {  5392, 5380, 5409, 5472, 5558, 5652, 5739, 5805, 5838, 5829, 5775, 5681, 5560, 5431, 5312, 5216, 5149, 5115, 5113, 5140, 5196, 5282, 5400, 5547, 5714, 5882, 6030, 6134, 6178, 6156, 6074, 5947, 5801, 5658, 5536, 5445, 5392, },
	/* LAT:  70 */ {  5726, 5706, 5704, 5716, 5738, 5765, 5788, 5803, 5802, 5783, 5743, 5686, 5615, 5539, 5465, 5401, 5353, 5325, 5320, 5340, 5384, 5454, 5545, 5654, 5771, 5886, 5985, 6058, 6097, 6101, 6072, 6018, 5951, 5881, 5816, 5763, 5726, },
	/* LAT:  80 */ {  5789, 5772, 5758, 5746, 5736, 5726, 5716, 5705, 5690, 5671, 5649, 5624, 5597, 5569, 5545, 5524, 5510, 5505, 5510, 5525, 5551, 5586, 5629, 5676, 5726, 5774, 5817, 5851, 5876, 5889, 5891, 5884, 5870, 5851, 5830, 5809, 5789, },
	/* LAT:  90 */ {  5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, 5681, },
};