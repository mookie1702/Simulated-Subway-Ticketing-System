#include <stdio.h>			// 引用标准输入输出头文件
#include <cstdio>
#include <stdlib.h>			// 引用标准函数库头文件
#include <cstdlib>
#include <time.h>			// 引用时间函数库头文件
#include <math.h>			// 引用数学函数库头文件
#include <string.h>			// 引用字符函数库头文件
#include <easyx.h>			// 引用图形函数库头文件
#include <conio.h>
/* 引用头文件 */

constexpr auto N = 131;		// 五条地铁线路车站总数
constexpr auto NAME = 15;	// 名字字符串最长长度
/* 定义宏常量 */

typedef struct station
{
	char name[NAME];
	char cname[NAME];
	int line;
	int number;
	int x;
	int y;
	int ma;
}STATION;
/* 定义车站结构体数据: 车站英文名,车站中文名,所在几号线,位于该线的第几个站台,该站在地图上的 x坐标,该站在地图上的 y坐标,该站的编码 */

int ticket(STATION station[], int start_line, int start_number, int end_line, int end_number);
/******************************
定义函数
函数功能：		计算两个站点的车票单价；
函数调用参数：	车站结构体数组(STATION)，起始站的线号(int)，起始站所在的站台号(int)，终点站的线号(int)，终点站所在的站台号(int)；
函数返回值：	本次乘车的车票单价(int)；
******************************/

int main()
{
	initgraph(1024, 768);						// 绘图窗口初始化,创建绘图窗口,大小为1024x768像素
	ExMessage mouse;								// 定义鼠标消息
	int choice = 0;								// 定义用户的选择
	int ticket_number = 0;						// 定义用户填入的所购票数
	int start, end;								// 定义起点站，终点站
	int start_line = 0, start_number = 0;		// 定义用户选择起始站的线号和车站号
	int end_line = 0, end_number = 0;			// 定义用户选择终点站的线号和车站号
	int time = 0;								// 定义延时变量
	int i = 0, j = 0;							// 定义循环语句变量
	int ticket_price = 0;						// 定义车票单价
	int ticket_totalprice = 0;					// 定义车票总价
	int money = 0;								// 定义乘客投入钱币数
	int change = 0;								// 定义机器找零数
	int station_find = 0;						// 定义要查询的车站号
	TCHAR price[NAME],line1[NAME],number1[NAME];// 定义记录弹窗的字符串数组
	char ticketnumber[10];
	char pay[10];
	char stationfind[10];
	LOGFONT word;								// 定义字体

/* 定义车站结构体数组，并将其初始化 */
	STATION  station[N] = 
	{{"luohu",		"罗湖站"	,1,1,845,573,0},
	{"guomao",		"国贸站"	,1,2,845,527,1},
	{"laojie",		"老街站"	,1,3,845,442,2},
	{"dajuyuan",	"大剧院站"	,1,4,809,480,3},
	{"kexueguan",	"科学馆站"	,1,5,772,518,4},
	{"huaqianglu",	"华强路站"	,1,6,724,518,5},
	{"gangxia",		"岗厦站"	,1,7,677,518,6},
	{"hzzhongxin",	"会展中心站",1,8,616,518,7},
	{"gwgongyuan",	"购物公园站",1,9,582,518,8},
	{"xiangmihu",	"香蜜湖站"	,1,10,523,518,9},
	{"chegongm",	"车公庙站"	,1,11,486,518,10},
	{"zuzilin",		"竹子林站"	,1,12,451,518,11},
	{"qiaochengdong","侨城东站"	,1,13,415,518,12},
	{"huaqiaocheng","华侨城站"	,1,14,379,518,13},
	{"shijiezhic",	"世界之窗站",1,15,331,518,14},
	{"baishizhou",	"白石洲站"	,1,16,308,518,15},
	{"gaoxinyuan",	"高新园站"	,1,17,281,518,16},
	{"shenda",		"深大站"	,1,18,253,518,17},
	{"taoyuan",		"桃园站"	,1,19,226,518,18},
	{"daxin",		"大新站"	,1,20,196,518,19},
	{"liyumen",		"鲤鱼门站"	,1,21,170,518,20},
	{"qianhaiwuan",	"前海湾站"	,1,22,122,518,21},
	{"xinan",		"新安站"	,1,23,122,492,22},
	{"baoanzx",		"宝安中心站",1,24,122,463,23},
	{"baoti",		"宝体站"	,1,25,122,434,24},
	{"pinzhou",		"坪洲站"	,1,26,122,402,25},
	{"xixiang",		"西乡站"	,1,27,122,371,26},
	{"gushu",		"固戍站"	,1,28,122,339,27},
	{"hourui",		"后瑞站"	,1,29,122,309,28},
	{"jichangd",	"机场东站"	,1,30,122,277,29},
	{"chiwuan",		"赤湾站"	,2,1,85,755,30},
	{"shekoug",		"蛇口港站"	,2,2,105,735,31},
	{"haishang",	"海上世界站",2,3,126,715,32},
	{"shuiwan",		"水湾站"	,2,4,148,693,33},
	{"dongjiaot",	"东角头站"	,2,5,172,672,34},
	{"wuanxia",		"湾厦站"	,2,6,194,650,35},
	{"haiyue",		"海月站"	,2,7,215,630,36},
	{"dengliang",	"登良站"	,2,8,237,608,37},
	{"houhai",		"后海站"	,2,9,260,587,38},
	{"keyuan",		"科苑站"	,2,10,282,566,39},
	{"hongshuw",	"红树湾站"	,2,11,305,545,40},
	{"shijiezhic",	"世界之窗站",2,12,331,518,41},
	{"qiaochengb",	"侨城北站"	,2,13,333,480,42},
	{"shenkang",	"深康站"	,2,14,361,480,43},
	{"antuoshan",	"安托山站"	,2,15,391,480,44},
	{"qiaoxiang",	"侨香站"	,2,16,422,480,45},
	{"xiangmi",		"香蜜站"	,2,17,452,480,46},
	{"xiangmeib",	"香梅北站"	,2,18,482,480,47},
	{"jingtian",	"景田站"	,2,19,512,480,48},
	{"lianhuax",	"莲花西站"	,2,20,544,480,49},
	{"futian",		"福田站"	,2,21,582,480,50},
	{"shiminzx",	"市民中心站",2,22,617,480,51},
	{"gangxiab",	"岗厦北站"	,2,23,670,480,52},
	{"huaqiangb",	"华强北站"	,2,24,719,480,53},
	{"yannan",		"燕南站"	,2,25,764,480,54},
	{"dajuyuan",	"大剧院站"	,2,26,810,480,55},
	{"hubei",		"湖贝站"	,2,27,869,480,56},
	{"huangbl",		"黄贝岭站"	,2,28,912,480,57},
	{"xinxiu",		"新秀站"	,2,29,963,480,58},
	{"yitian",		"益田站"	,3,1,582,589,59},
	{"shixia",		"石厦站"	,3,2,582,565,60},
	{"gwgongyuan",	"购物公园站",3,3,582,518,61},
	{"futian",		"福田站"	,3,4,582,480,62},
	{"shaoniang",	"少年宫站"	,3,5,617,442,63},
	{"lianhuac",	"莲花村站"	,3,6,656,442,64},
	{"huaxin",		"华新站"	,3,7,702,442,65},
	{"tongxinl",	"通新岭站"	,3,8,747,442,66},
	{"honglin",		"红岭站"	,3,9,791,442,67},
	{"laojie",		"老街站"	,3,10,842,442,68},
	{"shaibu",		"晒布站"	,3,11,842,420,69},
	{"cuizu	",		"翠竹站"	,3,12,842,397,70},
	{"tianbei",		"田贝站"	,3,13,842,375,71},
	{"shuibei",		"水贝站"	,3,14,842,353,72},
	{"caopu",		"草埔站"	,3,15,842,332,73},
	{"buji",		"布吉站"	,3,16,842,308,74},
	{"mujinwuan",	"木棉湾站"	,3,17,842,273,75},
	{"dafen",		"大芬站"	,3,18,842,243,76},
	{"danzutou",	"丹竹头站"	,3,19,842,213,77},
	{"liuyue",		"六约站"	,3,20,842,183,78},
	{"tangkang",	"塘坑站"	,3,21,842,154,79},
	{"henggang",	"横岗站"	,3,22,842,98,80},
	{"yonghu",		"永湖站"	,3,23,842,97,81},
	{"heao",		"荷坳站"	,3,24,872,97,82},
	{"dayun",		"大运站"	,3,25,902,97,83},
	{"ailian",		"爱联站"	,3,26,934,97,84},
	{"jixiang",		"吉祥站"	,3,27,965,97,85},
	{"longchenggc",	"龙城广场站",3,28,996,97,86},
	{"nanlian",		"南联站"	,3,29,127,97,87},
	{"shuanglo",	"双龙站"	,3,30,158,97,88},
	{"futiankan",	"福田口岸站",4,1,617,588,89},
	{"fumin",		"福民站"	,4,2,617,565,90},
	{"hzzhongxin",	"会展中心站",4,3,617,518,91},
	{"shiminzx",	"市民中心站",4,4,617,480,92},
	{"shaoniang",	"少年宫站"	,4,5,617,440,93},
	{"lianhuab",	"莲花北站"	,4,6,617,416,94},
	{"shangmeil",	"上梅林站"	,4,7,617,389,95},
	{"minyue",		"民乐站"	,4,8,617,364,96},
	{"baishil""",	"白石龙站"	,4,9,617,341,97},
	{"shenzhenb",	"深圳北站"	,4,10,617,308,98},
	{"hongshan",	"红山站"	,4,11,617,266,99},
	{"shangtang",	"上塘站"	,4,12,617,226,100},
	{"longsheng",	"龙胜站"	,4,13,617,184,101},
	{"longhua",		"龙华站"	,4,14,617,142,102},
	{"qinghu",		"清湖站"	,4,15,617,100,103},
	{"qianhaiwuan",	"前海湾站"	,5,1,123,517,104},
	{"linhai",		"临海站"	,5,2,60,517,105},
	{"baohua",		"宝华站"	,5,3,88,492,106},
	{"baoanzx",		"宝安中心站",5,4,122,463,107},
	{"fanshen",		"翻身站"	,5,5,184,412,108},
	{"lingzhi",		"灵芝站"	,5,6,247,360,109},
	{"honglangb",	"洪浪北站"	,5,7,309,308,110},
	{"xingdong",	"兴东站"	,5,8,347,308,111},
	{"liuxiand",	"留仙洞站"	,5,9,390,308,112},
	{"xili",		"西丽站"	,5,10,430,308,113},
	{"daxuech",		"大学城站"	,5,11,471,308,114},
	{"tanglang",	"塘朗站"	,5,12,517,308,115},
	{"changlingp",	"长岭陂站"	,5,13,557,308,116},
	{"shenzhenb",	"深圳北站"	,5,14,617,308,117},
	{"minzhi",		"民治站"	,5,15,647,308,118},
	{"wuhe",		"五和站"	,5,16,676,308,119},
	{"bantian",		"坂田站"	,5,17,705,308,120},
	{"yangmei",		"杨美站"	,5,18,733,308,121},
	{"shangshuij",	"上水径站"	,5,19,761,308,122},
	{"xiashuij",	"下水径站"	,5,20,789,308,123},
	{"changlong",	"长龙站"	,5,21,817,308,124},
	{"buji",		"布吉站"	,5,22,842,308,125},
	{"baigelon",	"百鸽笼站"	,5,23,912,365,126},
	{"buxin",		"布心站"	,5,24,912,395,127},
	{"taian",		"布心站"	,5,25,912,424,128},
	{"yijing",		"怡景站"	,5,26,912,455,129},
	{"huangbl",		"黄贝岭站"	,5,27,912,480,130},
	};

/* 欢迎界面 */
	loadimage(NULL, _T("image/欢迎界面.jpg"));
	_getch();			// 按任意键继续
	cleardevice();		// 清除屏幕内容

/* 系统说明界面 */
	loadimage(NULL, _T("image/系统说明界面.jpg"));
	/* 点击指定区域继续 */
	while (true)
	{
		mouse = getmessage();			// 获取鼠标消息
		if(mouse.message == WM_LBUTTONDOWN)
		{
			if ((718 <= mouse.x) & (949 >= mouse.x) & (614 <= mouse.y) & (676 >= mouse.y))
				break;
		}
	}

/* 主菜单界面 */
MAIN:
	initgraph(1024, 768);
	loadimage(NULL, _T("image/主菜单界面.jpg"));
	/* 将用户选择的起始站和终点站的信息清零 */
	start_line = 0, start_number = 0;
	end_line = 0, end_number = 0;
	/* 通过鼠标点击的区域确定用户的选择 */
	while (true)
	{
		mouse = getmessage();
		if( mouse.message == WM_LBUTTONDOWN)
		{
			if (( 360 <= mouse.x )&( 661 >= mouse.x )&( 343 <= mouse.y )&( 419 >= mouse.y ))
			{
				choice = 1;
				break;
			}
			else if (( 360 <= mouse.x )&( 661 >= mouse.x )&( 424 <= mouse.y )&( 492 >= mouse.y ))
			{
				choice = 2;
				break;
			}
			else if (( 360 <= mouse.x )&( 661 >= mouse.x )&( 502 <= mouse.y)&( 562 >= mouse.y ))
			{
				choice = 3;
				break;
			}
		}
	}
	cleardevice();				

/* 三个选项界面 */
	switch (choice)
	{
		/* 购票界面 */
		case 1:
PERCHASE:
			Resize(NULL, 1428, 805);
			loadimage(NULL, _T("image/购票界面.jpg"));
			/* 确定起点站，终点站 */
			while (true)
			{
				mouse = getmessage();
				if (mouse.message == WM_LBUTTONDOWN)
				{
					/* 返回主菜单 */
					if ((109 <= mouse.x) & (341 >= mouse.x) & (622 <= mouse.y) & (735 >= mouse.y))
					{
						cleardevice();
						goto MAIN;
					}
					/* 选择起点站 */
					else if ((975 <= mouse.x) & (1362 >= mouse.x) & (458 <= mouse.y) & (507 >= mouse.y))
					{
						Resize(NULL, 1080, 810);
						loadimage(NULL, _T("image/深圳地铁_返回.jpg"));
						start_line = 0, start_number = 0;
						while (true)
						{
							mouse = getmessage();
							if (mouse.message == WM_LBUTTONDOWN)
							{
								/* 返回 */
								if ((940 <= mouse.x) & (1060 >= mouse.x) & (621 <= mouse.y) & (682 >= mouse.y))
								{
									cleardevice();
									goto PERCHASE;
								}
								/* 通过点击确定起点站 */
								for (i = 0; i < 131 ; i++ )
								{
									if ((fabs(mouse.x - station[i].x) <= 5) & (fabs(mouse.y - station[i].y)) <= 5)
									{
										start_line = station[i].line;
										start_number = station[i].number;
										start = i;
										goto PERCHASE;
									}
								}
							}
						}
					}
					/* 选择终点站 */
					else if ((975 <= mouse.x) & (1362 >= mouse.x) & (558 <= mouse.y) & (607 >= mouse.y))
					{
						Resize(NULL, 1080, 810);
						loadimage(NULL, _T("image/深圳地铁_返回.jpg"));
						end_line = 0, end_number = 0;
						while (true)
						{
							mouse = getmessage();
							if (mouse.message == WM_LBUTTONDOWN)
							{
								for (i = 0; i < 131; i++)
								{
									/* 返回 */
									if ((940 <= mouse.x) & (1060 >= mouse.x) & (621 <= mouse.y) & (682 >= mouse.y))
									{
										cleardevice();
										goto PERCHASE;
									}
									/* 通过点击确定终点站 */
									if ((fabs(mouse.x - station[i].x) <= 5) & (fabs(mouse.y - station[i].y)) <= 5)
									{
										end_line = station[i].line;
										end_number = station[i].number;
										end = i;
										goto PERCHASE;
									}
								}
							}
						}
					}
					/* 点击确认 */
					else if ((675 <= mouse.x) & (1210 >= mouse.x) & (641 <= mouse.y) & (700 >= mouse.y))
					{
						gettextstyle(&word);
						word.lfHeight = 40;							// 设置字体高度为 40
						_tcscpy_s(word.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
						word.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿 
						settextstyle(&word);
						/* 确定用户选择了起始站 */
						if (start_line == 0)
						{
							MessageBox(NULL, _T("抱歉，您还没有选择起点站！"), _T("错误"), MB_OK);
							goto PERCHASE;
						}
						/* 确定用户选择了终点站 */
						if (end_line == 0)
						{
							MessageBox(NULL, _T("抱歉，您还没有选择终点站！"), _T("错误"), MB_OK); for (time = 1; time <= 1000000000; time++);
							goto PERCHASE;
						}
						break;
					}
				}
			}
			cleardevice();

			/* 确定票数和票价界面 */
			Resize(NULL, 1024, 768);
			loadimage(NULL, _T("image/确定票数和票价界面.jpg"));
			ticket_price = ticket(station, start_line, start_number, end_line, end_number);
			_stprintf_s(price,_T("%d"),ticket_price);
			setbkmode(OPAQUE);
			setbkcolor(RGB(255, 255, 255));				// 设置文字背景颜色为白色
			settextcolor(RGB(0, 0, 0));					// 设置文字颜色为黑色
			gettextstyle(&word);
			word.lfHeight = 60;							// 设置字体高度为 60
			settextstyle(&word);
			outtextxy(640, 101, price);
			outtextxy(200,240 , station[start].cname);
			outtextxy(640,240 , station[end].cname);
BACK:
			while (true)
			{
				mouse = getmessage();
				if (mouse.message == WM_LBUTTONDOWN)
				{
					/* 返回主菜单 */
					if ((77 <= mouse.x) & (359 >= mouse.x) & (528 <= mouse.y) & (598 >= mouse.y))
					{
						cleardevice();
						goto MAIN;
					}
					/* 输入票数，显示车票总价 */
					if ((665 <= mouse.x) & (942 >= mouse.x) & (532 <= mouse.y) & (598 >= mouse.y))
					{
						i = InputBox(ticketnumber, 3, _T("请输入票数："), _T("输入票数"), NULL, 0, 0, false);
						if (false == i)
						{
							goto BACK;
						}
						ticket_number = atoi(ticketnumber);
						if (ticket_number < 0 )
						{
							MessageBox(NULL, _T("输入错误，请重新输入"), _T("错误"), MB_OK);
							goto BACK;
						}
						ticket_totalprice = ticket_number * ticket_price;
						_stprintf_s(price, _T("%d"), ticket_totalprice);
						loadimage(NULL, _T("image/确定票数和票价界面1.jpg"));
						outtextxy(640, 101, price);
						while (true)
						{
							mouse = getmessage();
							if (mouse.message == WM_LBUTTONDOWN)
							{
								if ((77 <= mouse.x) & (359 >= mouse.x) & (528 <= mouse.y) & (598 >= mouse.y))
								{
									cleardevice();
									goto MAIN;
								}
								if ((665 <= mouse.x) & (942 >= mouse.x) & (532 <= mouse.y) & (598 >= mouse.y))
								{
									break;
								}
							}
						}
						break;
					}
				}
			}

			/* 投币找零界面 */
			initgraph(1024, 768);
BACK1:
			loadimage(NULL, _T("image/投币找零界面.jpg"));
			while (true)
			{
				mouse = getmessage();
				if (mouse.message == WM_LBUTTONDOWN)
				{
					/* 返回主菜单 */
					if ((117 <= mouse.x) & (346 >= mouse.x) & (528 <= mouse.y) & (597 >= mouse.y))
					{
						cleardevice();
						goto MAIN;
					}
					/* 确认购买 */
					if ((684 <= mouse.x) & (944 >= mouse.x) & (528 <= mouse.y) & (611 >= mouse.y))
					{
						i = InputBox(pay, 10, _T("请输入已经投入（元）："), _T("输入已投入钱数"), NULL, 0, 0, false);
						if (false == i)
						{
							goto BACK1;
						}
						money = atoi(pay);
						if (money < ticket_totalprice)
						{
							MessageBox(NULL, _T("抱歉，您的钱币不足！"), _T("错误"), MB_OK);
							goto BACK1;
						}
						if (money >= ticket_totalprice)
						{
							change = money - ticket_totalprice;
							_stprintf_s(price, _T("%d"), change);
							loadimage(NULL, _T("image/找零.jpg"));
							setbkmode(OPAQUE);
							setbkcolor(RGB(255, 255, 255));				// 设置文字背景颜色为白色
							settextcolor(RGB(0, 0, 0));					// 设置文字颜色为黑色
							gettextstyle(&word);
							word.lfHeight = 60;							// 设置字体高度为 60
							_tcscpy_s(word.lfFaceName, _T("黑体"));	
							word.lfQuality = ANTIALIASED_QUALITY;
							settextstyle(&word);
							outtextxy(615, 90, price);
							while (true)
							{
								mouse = getmessage();
								if (mouse.message == WM_LBUTTONDOWN)
								{
									if ((665 <= mouse.x) & (942 >= mouse.x) & (532 <= mouse.y) & (598 >= mouse.y))
									{
										cleardevice();
										goto MAIN;
									}
								}
							}
						}
					}
				}
			}
			goto MAIN;

		/* 地图查询界面 */
		case 2:
			Resize(NULL, 1080, 810);
			loadimage(NULL, _T("image/深圳地铁_查询.jpg"));
			/* 按编码查询车站 */
BACK2:
			while (true)
			{
				mouse = getmessage();
				if (mouse.message == WM_LBUTTONDOWN)
				{
					if ((904 <= mouse.x) & (1062 >= mouse.x) & (641 <= mouse.y) & (691 >= mouse.y))
					{
						i = InputBox(stationfind, 10, _T("请输入您想查询的站点（0至130）："), _T("查询站点"), NULL, 0, 0, false);
						if (false == i)
						{
							goto BACK2;
						}
						station_find = atoi(stationfind);
						if (station_find < 0 || station_find > 130)
						{
							MessageBox(NULL, _T("输入错误，请输入0至130中的一个数"), _T("错误"), MB_OK);
							goto BACK2;
						}
						for (i = 0; i < N; i++)
						{
							if (station[i].ma == station_find)
							{
								j = i;
								break;
							}
						}
						Resize(NULL, 1024, 768);
						loadimage(NULL, _T("image/查询1.jpg"));
						_stprintf_s(line1, _T("%d"), station[j].line);
						_stprintf_s(number1, _T("%d"), station[j].number);

						setbkmode(OPAQUE);
						setbkcolor(RGB(255, 255, 255));	
						settextcolor(RGB(0, 0, 0));	
						gettextstyle(&word);
						word.lfHeight = 60;	
						_tcscpy_s(word.lfFaceName, _T("黑体"));	
						word.lfQuality = ANTIALIASED_QUALITY;
						settextstyle(&word);

						outtextxy(445, 244, station[j].cname);
						outtextxy(247, 392, line1);
						outtextxy(582, 395, number1);
						while (true)
						{
							mouse = getmessage();
							if (mouse.message == WM_LBUTTONDOWN)
							{
								if ((665 <= mouse.x) & (942 >= mouse.x) & (532 <= mouse.y) & (598 >= mouse.y))
								{
									cleardevice();
									break;
								}
							}
						}
						break;
					}
				}
			}
			/* 接下来的操作界面 */
			initgraph(1024, 768);
			loadimage(NULL, _T("image/接下来的操作界面.jpg"));
			while (true)
			{
				mouse = getmessage();
				if (mouse.message == WM_LBUTTONDOWN)
				{
					/* 返回主菜单 */
					if ((114 <= mouse.x) & (365 >= mouse.x) & (517 <= mouse.y) & (588 >= mouse.y))
					{
						cleardevice();
						goto MAIN;
					}
					/* 进入购票界面 */
					if ((685 <= mouse.x) & (933 >= mouse.x) & (517 <= mouse.y) & (596 >= mouse.y))
					{
						cleardevice();
						goto PERCHASE;
					}
				}
			}
		/* 退出程序 */
		case 3:
			exit(0);
	}
}

int ticket(STATION station[], int start_line, int start_number, int end_line, int end_number)
{
	int i, j, k = 0, h = 0;
	int number = 0;			// 定义起点站与终点站之间的站数
	/* 假设两个站在同一号线上 */
	if (start_line == end_line)
	{
		number =fabs(start_number - end_number);
		return number;
	}
	/* 假设两个站在不同的线上 */
	else
	{
		for (i = 0;i < N ; i++)
		{
			for (j = 0;j < N ; j++)
			{
				if (strcmp(station[i].name, station[j].name) == 0 && station[i].line == start_line && station[j].line == end_line)
				{
					k = station[i].number;
					h = station[j].number;
					 number = fabs(k - start_number) + fabs(h - end_number);
					return number;
				}
			}
		}
	}
}
