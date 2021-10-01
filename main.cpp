#include <stdio.h>			// ���ñ�׼�������ͷ�ļ�
#include <cstdio>
#include <stdlib.h>			// ���ñ�׼������ͷ�ļ�
#include <cstdlib>
#include <time.h>			// ����ʱ�亯����ͷ�ļ�
#include <math.h>			// ������ѧ������ͷ�ļ�
#include <string.h>			// �����ַ�������ͷ�ļ�
#include <easyx.h>			// ����ͼ�κ�����ͷ�ļ�
#include <conio.h>
/* ����ͷ�ļ� */

constexpr auto N = 131;		// ����������·��վ����
constexpr auto NAME = 15;	// �����ַ��������
/* ����곣�� */

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
/* ���峵վ�ṹ������: ��վӢ����,��վ������,���ڼ�����,λ�ڸ��ߵĵڼ���վ̨,��վ�ڵ�ͼ�ϵ� x����,��վ�ڵ�ͼ�ϵ� y����,��վ�ı��� */

int ticket(STATION station[], int start_line, int start_number, int end_line, int end_number);
/******************************
���庯��
�������ܣ�		��������վ��ĳ�Ʊ���ۣ�
�������ò�����	��վ�ṹ������(STATION)����ʼվ���ߺ�(int)����ʼվ���ڵ�վ̨��(int)���յ�վ���ߺ�(int)���յ�վ���ڵ�վ̨��(int)��
��������ֵ��	���γ˳��ĳ�Ʊ����(int)��
******************************/

int main()
{
	initgraph(1024, 768);						// ��ͼ���ڳ�ʼ��,������ͼ����,��СΪ1024x768����
	MOUSEMSG mouse;								// ���������Ϣ
	int choice = 0;								// �����û���ѡ��
	int ticket_number = 0;						// �����û����������Ʊ��
	int start, end;								// �������վ���յ�վ
	int start_line = 0, start_number = 0;		// �����û�ѡ����ʼվ���ߺźͳ�վ��
	int end_line = 0, end_number = 0;			// �����û�ѡ���յ�վ���ߺźͳ�վ��
	int time = 0;								// ������ʱ����
	int i = 0, j = 0;							// ����ѭ��������
	int ticket_price = 0;						// ���峵Ʊ����
	int ticket_totalprice = 0;					// ���峵Ʊ�ܼ�
	int money = 0;								// ����˿�Ͷ��Ǯ����
	int change = 0;								// �������������
	int station_find = 0;						// ����Ҫ��ѯ�ĳ�վ��
	TCHAR price[NAME],line1[NAME],number1[NAME];// �����¼�������ַ�������
	char ticketnumber[10];
	char pay[10];
	char stationfind[10];
	LOGFONT word;								// ��������

/* ���峵վ�ṹ�����飬�������ʼ�� */
	STATION  station[N] = 
	{{"luohu",		"�޺�վ"	,1,1,845,573,0},
	{"guomao",		"��óվ"	,1,2,845,527,1},
	{"laojie",		"�Ͻ�վ"	,1,3,845,442,2},
	{"dajuyuan",	"���Ժվ"	,1,4,809,480,3},
	{"kexueguan",	"��ѧ��վ"	,1,5,772,518,4},
	{"huaqianglu",	"��ǿ·վ"	,1,6,724,518,5},
	{"gangxia",		"����վ"	,1,7,677,518,6},
	{"hzzhongxin",	"��չ����վ",1,8,616,518,7},
	{"gwgongyuan",	"���﹫԰վ",1,9,582,518,8},
	{"xiangmihu",	"���ۺ�վ"	,1,10,523,518,9},
	{"chegongm",	"������վ"	,1,11,486,518,10},
	{"zuzilin",		"������վ"	,1,12,451,518,11},
	{"qiaochengdong","�ȳǶ�վ"	,1,13,415,518,12},
	{"huaqiaocheng","���ȳ�վ"	,1,14,379,518,13},
	{"shijiezhic",	"����֮��վ",1,15,331,518,14},
	{"baishizhou",	"��ʯ��վ"	,1,16,308,518,15},
	{"gaoxinyuan",	"����԰վ"	,1,17,281,518,16},
	{"shenda",		"���վ"	,1,18,253,518,17},
	{"taoyuan",		"��԰վ"	,1,19,226,518,18},
	{"daxin",		"����վ"	,1,20,196,518,19},
	{"liyumen",		"������վ"	,1,21,170,518,20},
	{"qianhaiwuan",	"ǰ����վ"	,1,22,122,518,21},
	{"xinan",		"�°�վ"	,1,23,122,492,22},
	{"baoanzx",		"��������վ",1,24,122,463,23},
	{"baoti",		"����վ"	,1,25,122,434,24},
	{"pinzhou",		"ƺ��վ"	,1,26,122,402,25},
	{"xixiang",		"����վ"	,1,27,122,371,26},
	{"gushu",		"����վ"	,1,28,122,339,27},
	{"hourui",		"����վ"	,1,29,122,309,28},
	{"jichangd",	"������վ"	,1,30,122,277,29},
	{"chiwuan",		"����վ"	,2,1,85,755,30},
	{"shekoug",		"�߿ڸ�վ"	,2,2,105,735,31},
	{"haishang",	"��������վ",2,3,126,715,32},
	{"shuiwan",		"ˮ��վ"	,2,4,148,693,33},
	{"dongjiaot",	"����ͷվ"	,2,5,172,672,34},
	{"wuanxia",		"����վ"	,2,6,194,650,35},
	{"haiyue",		"����վ"	,2,7,215,630,36},
	{"dengliang",	"����վ"	,2,8,237,608,37},
	{"houhai",		"��վ"	,2,9,260,587,38},
	{"keyuan",		"��Էվ"	,2,10,282,566,39},
	{"hongshuw",	"������վ"	,2,11,305,545,40},
	{"shijiezhic",	"����֮��վ",2,12,331,518,41},
	{"qiaochengb",	"�ȳǱ�վ"	,2,13,333,480,42},
	{"shenkang",	"�վ"	,2,14,361,480,43},
	{"antuoshan",	"����ɽվ"	,2,15,391,480,44},
	{"qiaoxiang",	"����վ"	,2,16,422,480,45},
	{"xiangmi",		"����վ"	,2,17,452,480,46},
	{"xiangmeib",	"��÷��վ"	,2,18,482,480,47},
	{"jingtian",	"����վ"	,2,19,512,480,48},
	{"lianhuax",	"������վ"	,2,20,544,480,49},
	{"futian",		"����վ"	,2,21,582,480,50},
	{"shiminzx",	"��������վ",2,22,617,480,51},
	{"gangxiab",	"���ñ�վ"	,2,23,670,480,52},
	{"huaqiangb",	"��ǿ��վ"	,2,24,719,480,53},
	{"yannan",		"����վ"	,2,25,764,480,54},
	{"dajuyuan",	"���Ժվ"	,2,26,810,480,55},
	{"hubei",		"����վ"	,2,27,869,480,56},
	{"huangbl",		"�Ʊ���վ"	,2,28,912,480,57},
	{"xinxiu",		"����վ"	,2,29,963,480,58},
	{"yitian",		"����վ"	,3,1,582,589,59},
	{"shixia",		"ʯ��վ"	,3,2,582,565,60},
	{"gwgongyuan",	"���﹫԰վ",3,3,582,518,61},
	{"futian",		"����վ"	,3,4,582,480,62},
	{"shaoniang",	"���깬վ"	,3,5,617,442,63},
	{"lianhuac",	"������վ"	,3,6,656,442,64},
	{"huaxin",		"����վ"	,3,7,702,442,65},
	{"tongxinl",	"ͨ����վ"	,3,8,747,442,66},
	{"honglin",		"����վ"	,3,9,791,442,67},
	{"laojie",		"�Ͻ�վ"	,3,10,842,442,68},
	{"shaibu",		"ɹ��վ"	,3,11,842,420,69},
	{"cuizu	",		"����վ"	,3,12,842,397,70},
	{"tianbei",		"�ﱴվ"	,3,13,842,375,71},
	{"shuibei",		"ˮ��վ"	,3,14,842,353,72},
	{"caopu",		"����վ"	,3,15,842,332,73},
	{"buji",		"����վ"	,3,16,842,308,74},
	{"mujinwuan",	"ľ����վ"	,3,17,842,273,75},
	{"dafen",		"���վ"	,3,18,842,243,76},
	{"danzutou",	"����ͷվ"	,3,19,842,213,77},
	{"liuyue",		"��Լվ"	,3,20,842,183,78},
	{"tangkang",	"����վ"	,3,21,842,154,79},
	{"henggang",	"���վ"	,3,22,842,98,80},
	{"yonghu",		"����վ"	,3,23,842,97,81},
	{"heao",		"����վ"	,3,24,872,97,82},
	{"dayun",		"����վ"	,3,25,902,97,83},
	{"ailian",		"����վ"	,3,26,934,97,84},
	{"jixiang",		"����վ"	,3,27,965,97,85},
	{"longchenggc",	"���ǹ㳡վ",3,28,996,97,86},
	{"nanlian",		"����վ"	,3,29,127,97,87},
	{"shuanglo",	"˫��վ"	,3,30,158,97,88},
	{"futiankan",	"����ڰ�վ",4,1,617,588,89},
	{"fumin",		"����վ"	,4,2,617,565,90},
	{"hzzhongxin",	"��չ����վ",4,3,617,518,91},
	{"shiminzx",	"��������վ",4,4,617,480,92},
	{"shaoniang",	"���깬վ"	,4,5,617,440,93},
	{"lianhuab",	"������վ"	,4,6,617,416,94},
	{"shangmeil",	"��÷��վ"	,4,7,617,389,95},
	{"minyue",		"����վ"	,4,8,617,364,96},
	{"baishil""",	"��ʯ��վ"	,4,9,617,341,97},
	{"shenzhenb",	"���ڱ�վ"	,4,10,617,308,98},
	{"hongshan",	"��ɽվ"	,4,11,617,266,99},
	{"shangtang",	"����վ"	,4,12,617,226,100},
	{"longsheng",	"��ʤվ"	,4,13,617,184,101},
	{"longhua",		"����վ"	,4,14,617,142,102},
	{"qinghu",		"���վ"	,4,15,617,100,103},
	{"qianhaiwuan",	"ǰ����վ"	,5,1,123,517,104},
	{"linhai",		"�ٺ�վ"	,5,2,60,517,105},
	{"baohua",		"����վ"	,5,3,88,492,106},
	{"baoanzx",		"��������վ",5,4,122,463,107},
	{"fanshen",		"����վ"	,5,5,184,412,108},
	{"lingzhi",		"��֥վ"	,5,6,247,360,109},
	{"honglangb",	"���˱�վ"	,5,7,309,308,110},
	{"xingdong",	"�˶�վ"	,5,8,347,308,111},
	{"liuxiand",	"���ɶ�վ"	,5,9,390,308,112},
	{"xili",		"����վ"	,5,10,430,308,113},
	{"daxuech",		"��ѧ��վ"	,5,11,471,308,114},
	{"tanglang",	"����վ"	,5,12,517,308,115},
	{"changlingp",	"������վ"	,5,13,557,308,116},
	{"shenzhenb",	"���ڱ�վ"	,5,14,617,308,117},
	{"minzhi",		"����վ"	,5,15,647,308,118},
	{"wuhe",		"���վ"	,5,16,676,308,119},
	{"bantian",		"����վ"	,5,17,705,308,120},
	{"yangmei",		"����վ"	,5,18,733,308,121},
	{"shangshuij",	"��ˮ��վ"	,5,19,761,308,122},
	{"xiashuij",	"��ˮ��վ"	,5,20,789,308,123},
	{"changlong",	"����վ"	,5,21,817,308,124},
	{"buji",		"����վ"	,5,22,842,308,125},
	{"baigelon",	"�ٸ���վ"	,5,23,912,365,126},
	{"buxin",		"����վ"	,5,24,912,395,127},
	{"taian",		"����վ"	,5,25,912,424,128},
	{"yijing",		"����վ"	,5,26,912,455,129},
	{"huangbl",		"�Ʊ���վ"	,5,27,912,480,130},
	};

/* ��ӭ���� */
	loadimage(NULL, _T("��ӭ����.jpg"));
	_getch();			// �����������
	cleardevice();		// �����Ļ����

/* ϵͳ˵������ */
	loadimage(NULL, _T("ϵͳ˵������.jpg"));
	/* ���ָ��������� */
	while (true)
	{
		mouse = GetMouseMsg();			// ��ȡ�����Ϣ
		if(mouse.uMsg == WM_LBUTTONDOWN)
		{
			if ((718 <= mouse.x) & (949 >= mouse.x) & (614 <= mouse.y) & (676 >= mouse.y))
				break;
		}
	}

/* ���˵����� */
MAIN:
	initgraph(1024, 768);
	loadimage(NULL, _T("���˵�����.jpg"));
	/* ���û�ѡ�����ʼվ���յ�վ����Ϣ���� */
	start_line = 0, start_number = 0;
	end_line = 0, end_number = 0;
	/* ͨ�������������ȷ���û���ѡ�� */
	while (true)
	{
		mouse = GetMouseMsg();
		if( mouse.uMsg == WM_LBUTTONDOWN)
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

/* ����ѡ����� */
	switch (choice)
	{
		/* ��Ʊ���� */
		case 1:
PERCHASE:
			Resize(NULL, 1428, 805);
			loadimage(NULL, _T("��Ʊ����.jpg"));
			/* ȷ�����վ���յ�վ */
			while (true)
			{
				mouse = GetMouseMsg();
				if (mouse.uMsg == WM_LBUTTONDOWN)
				{
					/* �������˵� */
					if ((109 <= mouse.x) & (341 >= mouse.x) & (622 <= mouse.y) & (735 >= mouse.y))
					{
						cleardevice();
						goto MAIN;
					}
					/* ѡ�����վ */
					else if ((975 <= mouse.x) & (1362 >= mouse.x) & (458 <= mouse.y) & (507 >= mouse.y))
					{
						Resize(NULL, 1080, 810);
						loadimage(NULL, _T("���ڵ���_����.jpg"));
						start_line = 0, start_number = 0;
						while (true)
						{
							mouse = GetMouseMsg();
							if (mouse.uMsg == WM_LBUTTONDOWN)
							{
								/* ���� */
								if ((940 <= mouse.x) & (1060 >= mouse.x) & (621 <= mouse.y) & (682 >= mouse.y))
								{
									cleardevice();
									goto PERCHASE;
								}
								/* ͨ�����ȷ�����վ */
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
					/* ѡ���յ�վ */
					else if ((975 <= mouse.x) & (1362 >= mouse.x) & (558 <= mouse.y) & (607 >= mouse.y))
					{
						Resize(NULL, 1080, 810);
						loadimage(NULL, _T("���ڵ���_����.jpg"));
						end_line = 0, end_number = 0;
						while (true)
						{
							mouse = GetMouseMsg();
							if (mouse.uMsg == WM_LBUTTONDOWN)
							{
								for (i = 0; i < 131; i++)
								{
									/* ���� */
									if ((940 <= mouse.x) & (1060 >= mouse.x) & (621 <= mouse.y) & (682 >= mouse.y))
									{
										cleardevice();
										goto PERCHASE;
									}
									/* ͨ�����ȷ���յ�վ */
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
					/* ���ȷ�� */
					else if ((675 <= mouse.x) & (1210 >= mouse.x) & (641 <= mouse.y) & (700 >= mouse.y))
					{
						gettextstyle(&word);
						word.lfHeight = 40;							// ��������߶�Ϊ 40
						_tcscpy_s(word.lfFaceName, _T("����"));		// ��������Ϊ�����塱
						word.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ����� 
						settextstyle(&word);
						/* ȷ���û�ѡ������ʼվ */
						if (start_line == 0)
						{
							MessageBox(NULL, _T("��Ǹ������û��ѡ�����վ��"), _T("����"), MB_OK);
							goto PERCHASE;
						}
						/* ȷ���û�ѡ�����յ�վ */
						if (end_line == 0)
						{
							MessageBox(NULL, _T("��Ǹ������û��ѡ���յ�վ��"), _T("����"), MB_OK); for (time = 1; time <= 1000000000; time++);
							goto PERCHASE;
						}
						break;
					}
				}
			}
			cleardevice();

			/* ȷ��Ʊ����Ʊ�۽��� */
			Resize(NULL, 1024, 768);
			loadimage(NULL, _T("ȷ��Ʊ����Ʊ�۽���.jpg"));
			ticket_price = ticket(station, start_line, start_number, end_line, end_number);
			_stprintf_s(price,_T("%d"),ticket_price);
			setbkmode(OPAQUE);
			setbkcolor(RGB(255, 255, 255));				// �������ֱ�����ɫΪ��ɫ
			settextcolor(RGB(0, 0, 0));					// ����������ɫΪ��ɫ
			gettextstyle(&word);
			word.lfHeight = 60;							// ��������߶�Ϊ 60
			settextstyle(&word);
			outtextxy(640, 101, price);
			outtextxy(200,240 , station[start].cname);
			outtextxy(640,240 , station[end].cname);
BACK:
			while (true)
			{
				mouse = GetMouseMsg();
				if (mouse.uMsg == WM_LBUTTONDOWN)
				{
					/* �������˵� */
					if ((77 <= mouse.x) & (359 >= mouse.x) & (528 <= mouse.y) & (598 >= mouse.y))
					{
						cleardevice();
						goto MAIN;
					}
					/* ����Ʊ������ʾ��Ʊ�ܼ� */
					if ((665 <= mouse.x) & (942 >= mouse.x) & (532 <= mouse.y) & (598 >= mouse.y))
					{
						i = InputBox(ticketnumber, 3, _T("������Ʊ����"), _T("����Ʊ��"), NULL, 0, 0, false);
						if (false == i)
						{
							goto BACK;
						}
						ticket_number = atoi(ticketnumber);
						if (ticket_number < 0 )
						{
							MessageBox(NULL, _T("�����������������"), _T("����"), MB_OK);
							goto BACK;
						}
						ticket_totalprice = ticket_number * ticket_price;
						_stprintf_s(price, _T("%d"), ticket_totalprice);
						loadimage(NULL, _T("ȷ��Ʊ����Ʊ�۽���1.jpg"));
						outtextxy(640, 101, price);
						while (true)
						{
							mouse = GetMouseMsg();
							if (mouse.uMsg == WM_LBUTTONDOWN)
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

			/* Ͷ��������� */
			initgraph(1024, 768);
BACK1:
			loadimage(NULL, _T("Ͷ���������.jpg"));
			while (true)
			{
				mouse = GetMouseMsg();
				if (mouse.uMsg == WM_LBUTTONDOWN)
				{
					/* �������˵� */
					if ((117 <= mouse.x) & (346 >= mouse.x) & (528 <= mouse.y) & (597 >= mouse.y))
					{
						cleardevice();
						goto MAIN;
					}
					/* ȷ�Ϲ��� */
					if ((684 <= mouse.x) & (944 >= mouse.x) & (528 <= mouse.y) & (611 >= mouse.y))
					{
						i = InputBox(pay, 10, _T("�������Ѿ�Ͷ�루Ԫ����"), _T("������Ͷ��Ǯ��"), NULL, 0, 0, false);
						if (false == i)
						{
							goto BACK1;
						}
						money = atoi(pay);
						if (money < ticket_totalprice)
						{
							MessageBox(NULL, _T("��Ǹ������Ǯ�Ҳ��㣡"), _T("����"), MB_OK);
							goto BACK1;
						}
						if (money >= ticket_totalprice)
						{
							change = money - ticket_totalprice;
							_stprintf_s(price, _T("%d"), change);
							loadimage(NULL, _T("����.jpg"));
							setbkmode(OPAQUE);
							setbkcolor(RGB(255, 255, 255));				// �������ֱ�����ɫΪ��ɫ
							settextcolor(RGB(0, 0, 0));					// ����������ɫΪ��ɫ
							gettextstyle(&word);
							word.lfHeight = 60;							// ��������߶�Ϊ 60
							_tcscpy_s(word.lfFaceName, _T("����"));	
							word.lfQuality = ANTIALIASED_QUALITY;
							settextstyle(&word);
							outtextxy(615, 90, price);
							while (true)
							{
								mouse = GetMouseMsg();
								if (mouse.uMsg == WM_LBUTTONDOWN)
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

		/* ��ͼ��ѯ���� */
		case 2:
			Resize(NULL, 1080, 810);
			loadimage(NULL, _T("���ڵ���_��ѯ.jpg"));
			/* �������ѯ��վ */
BACK2:
			while (true)
			{
				mouse = GetMouseMsg();
				if (mouse.uMsg == WM_LBUTTONDOWN)
				{
					if ((904 <= mouse.x) & (1062 >= mouse.x) & (641 <= mouse.y) & (691 >= mouse.y))
					{
						i = InputBox(stationfind, 10, _T("�����������ѯ��վ�㣨0��130����"), _T("��ѯվ��"), NULL, 0, 0, false);
						if (false == i)
						{
							goto BACK2;
						}
						station_find = atoi(stationfind);
						if (station_find < 0 || station_find > 130)
						{
							MessageBox(NULL, _T("�������������0��130�е�һ����"), _T("����"), MB_OK);
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
						loadimage(NULL, _T("��ѯ1.jpg"));
						_stprintf_s(line1, _T("%d"), station[j].line);
						_stprintf_s(number1, _T("%d"), station[j].number);

						setbkmode(OPAQUE);
						setbkcolor(RGB(255, 255, 255));	
						settextcolor(RGB(0, 0, 0));	
						gettextstyle(&word);
						word.lfHeight = 60;	
						_tcscpy_s(word.lfFaceName, _T("����"));	
						word.lfQuality = ANTIALIASED_QUALITY;
						settextstyle(&word);

						outtextxy(445, 244, station[j].cname);
						outtextxy(247, 392, line1);
						outtextxy(582, 395, number1);
						while (true)
						{
							mouse = GetMouseMsg();
							if (mouse.uMsg == WM_LBUTTONDOWN)
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
			/* �������Ĳ������� */
			initgraph(1024, 768);
			loadimage(NULL, _T("�������Ĳ�������.jpg"));
			while (true)
			{
				mouse = GetMouseMsg();
				if (mouse.uMsg == WM_LBUTTONDOWN)
				{
					/* �������˵� */
					if ((114 <= mouse.x) & (365 >= mouse.x) & (517 <= mouse.y) & (588 >= mouse.y))
					{
						cleardevice();
						goto MAIN;
					}
					/* ���빺Ʊ���� */
					if ((685 <= mouse.x) & (933 >= mouse.x) & (517 <= mouse.y) & (596 >= mouse.y))
					{
						cleardevice();
						goto PERCHASE;
					}
				}
			}
		/* �˳����� */
		case 3:
			exit(0);
	}
}

int ticket(STATION station[], int start_line, int start_number, int end_line, int end_number)
{
	int i, j, k = 0, h = 0;
	int number = 0;			// �������վ���յ�վ֮���վ��
	/* ��������վ��ͬһ������ */
	if (start_line == end_line)
	{
		number =fabs(start_number - end_number);
		return number;
	}
	/* ��������վ�ڲ�ͬ������ */
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
