

#include"f_dec.h"
extern TIME* TIM;
extern Admlocation;
extern Administrator;

void menu_sta(user_manage* usm,room_manage* rom,acc_data* data,Reserve_manage* Res,DATA_BASE* base,DATE* dat)
{
	char select = -1;
	int i = 0;
	while(select)
	{
		sta(usm, rom, data, Res, base, dat);
		printf(divider);
		printf(WHITE_TEXT"                           欢迎 %s 以下为 %s 日的数据\n",usm->user[Admlocation].name,base->data[i].ymd);
		printf(divider);
		printf(">>>>>当日营业额 :%d\n", base->data[i].turnover);
		printf("\n");
		printf(divider);
		printf(">>>>>当日客户数量 :%d\n", base->data[i].total_number);
		printf(">>>>>当日共有%d名男性用户 %d名女性用户\n", base->data[i].number_male, base->data[i].number_female);
		printf(">>>>>当日有%d位未成年人 %d位成年人 %d位老年人\n", base->data[i].number_minor, base->data[i].number_adult, base->data[i].number_old);
		printf("\n");
		printf(divider);
		printf(">>>>>当日客房订购数据    入住率:%d%%\n",base->data[i].occ_rate);
		printf("%-12s\t%-8s\t%-8s\t%-12s\n","订购者", "房间类型", "订购数量", "订购时间");
		for (int j = 0;j <= base->data[i].sz;j++)
		{
			printf("%-12s\t%-8s\t%-8d\t%-12s\n", base->data[i].data_room[j].name,
										 base->data[i].data_room[j].type,
										 base->data[i].data_room[j].number,
										 base->data[i].data_room[j].hms);
		}
		printf("\n");
		menu_analyse(base, i);

		select = _getch();
		switch (select)
		{
		case 77:
			system("cls");
			if (i < base->sz)
			{
				i++;
			}
			break;
		case 75:
			system("cls");
			if (i > 0)
			{
				i--;
			}
			break;

		case RETURN:
			select = 0;
			system("cls");
			break;
		default:
			system("cls");
		}
	}

}


void menu_analyse(DATA_BASE* base,const int i)
{
	printf(divider);
	if (base->data[i].number_male > base->data[i].number_female)
	{
		printf("                        >>>>>>>>当日男性入住率高<<<<<<<<\n");//如果男的大于女的
		printf("当客房的单日男性入住率高时，可能说明以下几个可能的情况：\n1. 商务差旅和会议：高男性入住率可能反映了商务差旅和会议的需求较高。商务旅行和会议通常吸引了大量的男性客户，他们可能在当日有商务旅行或会议安排。\n2. 旅游和观光：高男性入住率也可能与旅游和观光有关。目的地可能更受男性游客的喜爱，例如探险旅行、户外活动或体育赛事等。\n3. 商务活动和展览：高男性入住率也可能与商务活动和展览有关。行业的商务活动、展览和会议吸引了大量的男性从业人员和参与者。\n");
		printf("当客房的单日男性入住率较高时，可以考虑以下策略来满足男性客人的需求：\n设施和服务：了解男性客人的偏好和需求，提供符合他们兴趣爱好的设施和服务。例如，增加健身房设备、提供男士洗浴用品、安排运动活动或推出男性专属套餐等。\n营销和宣传：针对男性客人制定相关的营销策略，通过各种途径宣传酒店在设施和服务方面的优势，吸引更多男性客人选择入住。可以在线上平台、社交媒体以及相关线下渠道进行宣传推广。\n合作伙伴关系：与相关的合作伙伴建立合作关系，例如与当地高尔夫球场、汽车俱乐部、商务中心等合作，提供特别优惠或增值服务，吸引更多男性客人入住。\n个性化服务：提供个性化的服务，例如为男性客人定制特殊的床上用品、提供报纸杂志、提供男性健康指南等，让他们感到被关注和重视。\n培训员工：确保员工具备良好的服务技能和对男性客人需求的了解，提供专业、周到的服务，给予男性客人良好的入住体验。\n");
	}
	else if (base->data[i].number_male < base->data[i].number_female)
	{
		printf("                        >>>>>>>>当日女性入住率高<<<<<<<<\n");  //女的小于男的
		printf("客房当日女性入住率高可能说明以下情况之一：\n1.商务旅行：女性在商务旅行中的比例增加，近期女性在专业领域中的活动增多。\n2.旅游：女性在旅游中的比例也有所增加，近期可能是旅游旺季。\n3.女性市场：酒店近期针对女性市场推出了特别的服务或产品，吸引了更多女性入住。\n");
		printf("当客房的当日女性入住率较高时，以下是几种策略可以考虑来满足女性客人的需求：\n安全和隐私：女性客人通常对安全和隐私非常关注。酒店可以加强安全措施，例如增加安保人员、安装监控设备等，确保女性客人在酒店内部和周边环境感到安全。此外，在房间内提供安全设备，如门锁、保险柜等，以增加女性客人的安全感。\n房间设施：为女性客人提供符合她们需求的房间设施。例如，提供化妆镜、吹风机、浴袍、美容用品等，以满足她们的美容和护理需求。另外，提供衣架、衣物熨烫设备等，方便女性客人整理衣物。\n健康和舒适：女性客人对健康和舒适的要求通常较高。酒店可以提供优质的床上用品，如舒适的床垫、枕头选择等，确保她们有一个良好的睡眠体验。此外，提供健身房、水疗中心、瑜伽室等设施，满足女性客人关注健康和放松的需求。\n活动和体验：根据女性客人的兴趣爱好，提供相应的活动和体验。例如，组织烹饪课程、艺术和手工艺工作坊、瑜伽或健身课程等，让女性客人可以参与其中，增加她们的入住乐趣。\n员工培训：确保员工接受适当的培训，了解并尊重女性客人的需求和偏好。员工应具备良好的沟通技巧，提供专业、友好和周到的服务，让女性客人感受到关怀和尊重。\n");
	}
	else
	{
		printf("                        >>>>>>当日男女入住率无差<<<<<<<<\n"); //相等
		printf("基本处于正常状态\n");
	}
	int max = Max(base->data[i].number_minor, base->data[i].number_adult, base->data[i].number_old);
	if (base->data[i].number_minor == max && base->data[i].number_adult == max && base->data[i].number_old == max)
	{
		printf("                        >>>>酒店各年龄段的入住率相等<<<<\n"); //如果老年人与成年与未成年都是最大值
		printf("酒店各年龄段的入住率相等，可能说明以下情况之一：\n1.广泛吸引力：酒店可能具有广泛的吸引力，能够满足不同年龄段客人的需求。它可能提供了适合不同年龄段客人的设施、服务和活动，从而吸引了各个年龄段的人入住。\n2.目标市场均衡：酒店可能有一个均衡的目标市场，不偏向特定年龄段的客人。这意味着酒店的市场定位和宣传可能针对各个年龄段的客人，以确保他们都能找到适合自己的理想住宿。\n3.口碑传播：酒店可能在口碑上表现出色，得到了不同年龄段客人的积极推荐。这可能是因为酒店提供了高质量的服务、舒适的环境和良好的客户体验，从而吸引了各个年龄段的客人。\n");
	}
	else if (base->data[i].number_minor == max && base->data[i].number_adult == max && base->data[i].number_old != max)
	{
		printf("                        >>>>>>酒店老年人入住率较低<<<<<<\n"); //未成年和成年是最大值
		printf("如果酒店的未成年和成年入住率高于老年入住率，可以考虑以下策略来满足不同年龄段客人的需求：\n家庭友好设施：针对未成年客人，提供家庭友好设施和服务，例如儿童游乐区、儿童餐单、亲子活动等，吸引更多家庭选择入住。同时，加强宣传这些家庭友好设施，以吸引更多家庭客户。\n娱乐和活动：针对成年客人，提供丰富多样的娱乐和活动选择，如夜间酒吧、主题派对、文化艺术活动等，以满足他们的娱乐需求，吸引更多成年客人入住。\n老年客人关怀：对老年客人提供关怀和服务，如提供便利设施、康体活动、健康餐点选择等，让他们感受到被尊重和关爱，增加老年客人的满意度和忠诚度。\n定制化服务：根据不同年龄段客人的需求和偏好，提供定制化的服务。例如，为未成年客人提供安全监护服务，为成年客人提供定制化的旅游路线和活动推荐，为老年客人提供贴心的照顾和服务。\n员工培训：确保员工具备应对不同年龄段客人的专业知识和服务技能，能够提供针对性的服务，让每位客人都感受到关怀和尊重。\n");
	}
	else if (base->data[i].number_minor == max && base->data[i].number_adult != max && base->data[i].number_old == max)
	{
		printf("                        >>>>>>酒店青年人入住率较低<<<<<<\n"); //未成年和老年是最大值
		printf("异常情况，请及时关注酒店情况");
		printf("可以考虑以下策略来提高成年客人的入住率：\n宣传和推广：加强宣传和推广酒店的特色服务和设施，尤其是面向成年客人的服务和活动。例如，开展主题活动、推广会议宴会服务、与商旅公司合作等，以吸引更多成年客人入住。\n增加娱乐设施：针对成年客人的娱乐需求，增加适合他们的娱乐设施，如健身房、桑拿、SPA、游泳池等，提供多元化的娱乐选择，吸引更多成年客人入住。\n提供定制化服务：了解成年客人的需求和偏好，提供个性化的服务和定制化的服务套餐，以满足他们的需求和期望。例如，提供商务服务、私人管家服务、高级客房等，提升成年客人的入住体验和满意度。\n提高服务质量：提高员工的服务质量和专业能力，使他们能够更好地为成年客人提供优质的服务和关怀。此外，加强客户反馈机制，及时收集和处理客人反馈，改进服务质量。\n价格优惠：考虑为成年客人提供一些价格上的优惠，如提供套餐、促销活动等，增加成年客人的入住率。\n");
	}
	else if (base->data[i].number_minor != max && base->data[i].number_adult == max && base->data[i].number_old == max)
	{
		printf("                        >>>>>酒店成年和老年入住率高<<<<<\n"); //成年和老年是最大值
		printf("酒店未成年入住率较低，可以考虑以下策略来提高未成年客人的入住率：\n家庭友好设施：在酒店内提供家庭友好设施，如儿童游乐区、儿童餐单、亲子活动等，以吸引更多家庭选择入住。通过提供适合未成年客人的设施和服务，增加未成年客人及其家长的满意度。\n举办家庭活动：定期举办面向家庭的活动，如亲子DIY工坊、主题派对、亲子运动会等，为家庭客户提供更多的活动选择，吸引更多未成年客人入住。\n优惠政策：考虑制定针对家庭客户的价格优惠政策，如免费或折扣的儿童入住政策、家庭套餐等，增加家庭客户选择该酒店的意愿。\n提供安全保障：家长通常非常关注未成年子女的安全问题，因此酒店需要提供安全保障措施，如监控设施、儿童房间门锁、紧急救援计划等，让家长放心选择入住。\n合作推广：与儿童教育机构、亲子社群等合作，共同举办活动或推广，扩大酒店在未成年客户中的知名度和影响力。\n");
	}
	else if (base->data[i].number_minor == max && base->data[i].number_adult != max && base->data[i].number_old != max)
	{
		printf("                        >>>>>>酒店未成年入住率较高<<<<<<\n"); //只有未成年最大
		printf("酒店未成年入住率已经很高，可以考虑以下措施来进一步提高未成年客人的满意度：\n提供更多个性化服务：针对不同年龄段和性别的未成年客人提供更多个性化服务，如提供儿童游戏设施、儿童专属餐单、青少年健身房等，以满足他们的需求和喜好。\n增加亲子活动：在酒店内增加更多面向家庭和未成年客人的亲子活动，如亲子DIY、亲子运动会等，增强未成年客人与家长之间的亲密度和黏着度。\n优化房型布局：在酒店内优化房型布局，提供更多适合家庭入住的房型，如家庭套房、相邻房间等，以满足家庭客户的需求。\n增加安全保障：针对未成年客人的安全保障措施需要进一步加强，如增加监控设施、加强安全巡查等，保证未成年客人的安全和健康。\n加强服务质量：酒店需要加强员工的服务质量和专业能力，提供更为优质的服务，并及时处理未成年客人的投诉和建议，以反馈和回应未成年客人的需求。\n");
	}
	else if (base->data[i].number_minor != max && base->data[i].number_adult == max && base->data[i].number_old != max)
	{
		printf("                        >>>>>>酒店青年人入住率较高<<<<<<\n"); //只有成年最大
		printf("酒店青年入住率较高，可以考虑以下策略来满足他们的需求，提高他们的入住体验：\n提供便捷的网络服务：青年客人普遍对网络服务要求较高，酒店需要提供稳定快速的Wi - Fi网络和多种设备的连接支持，以满足他们的各种需求。\n增加社交活动：针对青年客人的需求，酒店可以增加更多面向年轻人的社交活动，如主题派对、音乐会、文化沙龙等，提供一个社交互动的平台。\n推广周边旅游资源：通过推广周边的旅游资源和特色文化，吸引青年客人的兴趣，同时提供相关的旅游服务，如租车、导游服务等，增强客人的满意度。\n增加健身、娱乐设施：青年客人喜欢健身和娱乐活动，酒店可以增加健身房、游泳池、电影院等娱乐设施，以吸引青年客人选择入住。\n增加个性化服务：酒店可以根据青年客人的不同需求，提供个性化的服务和产品，如早餐口味、房间装修、床垫硬度等，以满足他们的不同需求。\n");
	}
	else if (base->data[i].number_minor != max && base->data[i].number_adult != max && base->data[i].number_old == max)
	{
		printf("                        >>>>>>酒店老年人入住率较高<<<<<<\n"); //只有老年最大
		printf("酒店老年入住率较高，可以考虑以下策略来满足他们的需求，提高他们的入住体验：\n提供舒适便捷的设施：老年客人对酒店的设施和环境要求较高，酒店需要提供方便舒适的客房设施，如易于进出的电梯、无障碍设施、安全扶手等，以满足老年客人的需求。\n关注健康与安全：老年客人关注健康和安全问题，酒店可以提供医疗服务、健康咨询、安全巡查等，确保老年客人的身体健康和安全。\n增加社交活动：老年客人喜欢参加社交活动，酒店可以组织丰富多样的社交活动，如茶话会、文艺表演、康体运动等，提供一个交流互动的平台。\n提供贴心服务：酒店员工需要提供温暖、亲切的服务，耐心倾听并满足老年客人的需求，如提供助行器、照顾行李、提供定制化的餐点等，让老年客人感受到宾至如归的待遇。\n提供便利的交通和出行服务：老年客人通常需要额外的交通和出行支持，酒店可以提供接送服务、租车服务等，方便他们的出行安排。\n");
	}

	if (base->data[i].occ_rate > 70)
	{
		printf("                        >>>>>>>>>酒店入住率较高<<<<<<<<\n");//入住率＞70
		printf("酒店客房得到了充分利用，反映出市场对酒店的需求旺盛\n");
		printf("酒店可以采取以下措施：\n提高价格：如果入住率很高，酒店可以适度提高房间价格，以增加收益。\n保持服务质量：高入住率不能让酒店松懈对服务质量的要求，要确保客人满意度和忠诚度。\n扩大市场份额：可考虑扩大酒店规模、增加客房数量，以满足更多客人的需求。\n");
	}
	else if (base->data[i].occ_rate > 60)
	{
		printf("                        >>>>>>>>>酒店入住率一般<<<<<<<<\n");//60<入住率＞70
		printf("酒店客房利用率较低，可能存在一些问题，如市场竞争激烈、服务质量差、价格不合理等。\n");
		printf("调整价格策略：可以考虑降低价格，吸引更多客人入住，但需要注意避免过度降价导致损失。\n优化营销策略：通过广告宣传、促销活动等提高酒店知名度，吸引更多客人。\n完善服务质量：重视客户反馈，加强服务培训，提升服务质量，增加客人的满意度和口碑。\n");
	}
	else
	{
		printf("                        >>>>>>>>>酒店入住率较低<<<<<<<<\n");

		printf("将会面临以下困难：\n收入减少：低入住率直接导致收入减少，影响酒店的经营业绩。\n成本增加：即使入住率低，酒店仍需维持基本服务和设施，这会导致成本增加。\n员工流失：低入住率可能导致员工数量过剩，而员工流失会带来很多额外的成本和人力资源问题。\n竞争力下降：低入住率可能意味着酒店在市场上的竞争力下降，客户满意度和口碑也会受到影响。\n");
		printf("酒店应该及时监测入住率，并分析入住率变化的原因，及时调整营销策略、服务质量和价格策略，以适应市场需求的变化。\n");
	}

}



TIME* CreateTime()
{
	TIME* TIM = (TIME*)calloc(sizeof(TIME), (size_t)1);
	if (NULL == TIM)
	{
		perror("CreatTIME :");
		return NULL;
	}
	return TIM;
}

//typedef struct
//{
//	char tm_sec[SEC];	//当前秒
//	char tm_min[MIN];	//当前分
//	char tm_hour[HOUR];	//当前时
//	char tm_mday[MDAY];	//当前月中的天
//	char tm_mon[MON];	//当前月
//	char tm_year[YEAR];	//当前年
//	char tm_wday[WDAY];	//当前星期
//	char tm_yday[YDAY];	//当前年的第几天
//	char tm_isdst[ISDST];	//当前是否是夏令时 我不知道这什么玩意
//	char hms[HMS];	//时:分:秒   它大概是这个字符串
//	char ymd[YMD];	//年 月 日   它大概是这个字符串
//	char ymd_hms[YMD_HMS]; //年 月 日 时:分:秒
//	char ymd_w_hms[YMD_W_HMS]; //年 月 日 星期 时:分:秒
//	//如果要添加别的形式的时间 可以跟我说
//}TIME;

TIME* refresh_time(TIME* TIM)
{
	if (NULL == TIM)
	{
		perror("TIM == NULL!! ");
		return NULL;
	}
	time_t current_time = 0;
	time(&current_time);
	INT_TIME* t = localtime(&current_time);
	strftime(TIM->tm_year, sizeof(TIM->tm_year), "%Y", t);
	strftime(TIM->tm_mon, sizeof(TIM->tm_mon), "%m", t);
	strftime(TIM->tm_mday, sizeof(TIM->tm_mday), "%d", t);
	strftime(TIM->tm_hour, sizeof(TIM->tm_hour), "%H", t);
	strftime(TIM->tm_min, sizeof(TIM->tm_min), "%M", t);
	strftime(TIM->tm_sec, sizeof(TIM->tm_sec), "%S", t);
	strftime(TIM->tm_wday, sizeof(TIM->tm_wday), "%a", t);
	strftime(TIM->tm_yday, sizeof(TIM->tm_yday), "%j", t);
	strftime(TIM->tm_isdst, sizeof(TIM->tm_isdst), "%Z", t);
	strftime(TIM->hms, sizeof(TIM->hms), "%H:%M:%S", t);
	strftime(TIM->ymd, sizeof(TIM->ymd), "%Y %m %d", t);
	strftime(TIM->ymd_w_hms, sizeof(TIM->ymd_w_hms), "%Y %m %d %wday %H:%M:%S", t);
	strftime(TIM->ymd_hms, sizeof(TIM->ymd_hms), "%Y %m %d %H:%M:%S", t);
	return TIM;
}

void DeCreateTime(TIME* TIM)
{
	free(TIM);
}


DATA_BASE* CreateDataBase()
{
	DATA_BASE* base = (DATA_BASE*)calloc((size_t)1, sizeof(DATA_BASE));
	if (NULL == base)
	{
		perror("CreateDataBase :");
		return NULL;
	}
	base->sz = -1;
	base->maxsz = MINIMUM;
	base->data = (DATA*)calloc(MINIMUM, sizeof(DATA));
	if (NULL == base->data)
	{
		perror("base->data NULL！ :");
		return NULL;
	}
	base->data->sz = -1;
	base->data->maxsz = MINIMUM;
	for (int i = 0;i < MINIMUM;i++)
	{
		base->data[i].data_room = (Room*)calloc(MINIMUM, sizeof(Room));
		if (NULL == base->data[i].data_room)
		{
			perror("data_room NULL! :");
			return NULL;
		}
	}
	return base;
}


void BaseAlloc(DATA_BASE* base)
{
	DATA* tmp = (DATA*)realloc(base->data, (base->maxsz += ADDCOUNT) * sizeof(DATA));
	if (NULL == tmp)
	{
		perror("BaseAlloc :");
		return;
	}
	base->data = tmp;
	for (int i = base->sz + 1;i < base->maxsz;i++)
	{
		base->data[i].data_room = (Room*)calloc(MINIMUM, sizeof(Room));
		if (NULL == base->data[i].data_room)
		{
			perror("BaseAlloc tmp_room :");
			return;
		}
	}
}

static int FindSub(DATA_BASE* base, char* ymd)
{
	for (int i = 0;i <= base->sz;i++)
	{
		if (strcmp(base->data[i].ymd, ymd) == 0)
		{
			return i;
		}
	}
	if (base->sz + 1 == base->maxsz)
	{
		BaseAlloc(base);
	}
	return ++(base->sz);
}

static int isToday(Reserve_manage* Res,const int i,char* ymd)
{
	return (strcmp(Res->Reserve[i].reserve_time_date, ymd) == 0);
}

static int ismale(Reserve_manage* Res,const int i)
{
	if(0 == cmp(Res->Reserve[i].sex,"女"))
	{
		return FALSE;
	}
	return TRUE;
}

static int isAge(Reserve_manage* Res, const int i)
{
	if (cmp(Res->Reserve[i].age,MINOR) < 0)
	{
		return MINOR_;
	}
	else if (cmp(Res->Reserve[i].age,ADULT) < 0)
	{
		return AUDLT_;
	}
	else
	{
		return OLD_;
	}
}
void RomAlloc_(DATA* data)
{
	Room* tmp = (Room*)realloc(data->data_room, (data->maxsz += ADDCOUNT) * sizeof(Room));
	if (NULL == tmp)
	{
		perror("RomAlloc :");
		return;
	}
	data->data_room = tmp;
}


DATE* CreateDate()
{
	DATE* dat = (DATE*)calloc((size_t)1, sizeof(DATE));
	if (NULL == dat)
	{
		perror("CreateDate :");
		return NULL;
	}
	dat->ymd = (char(*)[YMD])calloc(MINIMUM, sizeof(char[YMD]));
	if (NULL == dat->ymd)
	{
		perror("Date dat NULL!  :");
		return NULL;
	}
	dat->maxsz = MINIMUM;
	dat->sz = -1;
	return dat;
}

void DatAlloc(DATE* dat)
{
	char(*tmp)[YMD] = (char(*)[YMD])realloc(dat->ymd,(dat->maxsz += ADDCOUNT) * sizeof(char[YMD]));
	if (NULL == tmp)
	{
		perror("DatAlloc :");
		return;
	}
	dat->ymd = tmp;
}

void FindHistoryDat(Reserve_manage* Res, DATE* dat)
{
	for (int i = 0;i <= Res->sz;i++)
	{
		int find = 1;
		for (int j = 0;j <= dat->sz && find;j++)
		{
			if (0 == (cmp(Res->Reserve[i].reserve_time_date, &dat->ymd[j])))
			{
				find = 0;
			}
		}
		if (find)
		{
			cpy(dat->ymd[++(dat->sz)], Res->Reserve[i].reserve_time_date);
		}
	}
}
void sta(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res, DATA_BASE* base,DATE* dat)
{
	refresh_time(TIM);
	FindHistoryDat(Res, dat);
	for (int n = 0;n <= dat->sz;n++)
	{
		int sub = FindSub(base, &dat->ymd[n]);
		if (sub == base->sz)
		{
			//strcpy(base->data[sub].mday, TIM->tm_mday);
			//strcpy(base->data[sub].mon, TIM->tm_mon);
			//strcpy(base->data[sub].year, TIM->tm_year);
			//strcpy(base->data[sub].wday, TIM->tm_wday);
			//strcpy(base->data[sub].ymd, TIM->ymd);
			//strcpy(base->data[sub].hms, TIM->hms);
			//strcpy(base->data[sub].ymd_hms, TIM->ymd_hms);
			//strcpy(base->data[sub].ymd_w_hms, TIM->ymd_w_hms);
			cpy(base->data[sub].ymd, &dat->ymd[n]);
		}
		int turnover = 0; //营业额
		int total_number = 0;
		int number_minor = 0;
		int number_adult = 0;
		int number_old = 0;

		int number_male = 0;
		int number_female = 0;

		for (int i = 0;i <= base->data[sub].sz;i++)
		{
			base->data[sub].data_room[i].number = 0;
		}

		for (int i = 0;i <= Res->sz;i++)
		{
			if (isToday(Res, i, &base->data[sub].ymd))
			{
				turnover += Res->Reserve[i].price;
				total_number++;
				if (ismale(Res, i))
				{
					number_male++;
				}
				else
				{
					number_female++;
				}
				switch (isAge(Res, i))
				{
				case MINOR_:
					number_minor++;
					break;
				case AUDLT_:
					number_adult++;
					break;
				case OLD_:
					number_old++;
					break;
				}
				int find = 0;
				for (int j = 0;j <= base->data[sub].sz && !find;j++)
				{
					if (0 == (cmp(Res->Reserve[i].type, base->data[sub].data_room[j].type)))
					{
						base->data[sub].data_room[j].number++;
						cpy(base->data[sub].data_room[j].name, Res->Reserve[i].name);
						find = 1;
					}
				}
				if (!find)
				{
					int sz = ++base->data[sub].sz;
					if (sz + 1 == base->data[sub].maxsz)
					{
						RomAlloc_(&base->data[sub]);
					}
					cpy(base->data[sub].data_room[sz].type, Res->Reserve[i].type);
					base->data[sub].data_room[sz].number++;
					cpy(base->data[sub].data_room[sz].hms, Res->Reserve[i].reserve_time_day);
					cpy(base->data[sub].data_room[sz].name, Res->Reserve[i].name);

				}

			}
		}
		base->data[sub].turnover = turnover;
		base->data[sub].total_number = total_number;
		base->data[sub].number_minor = number_minor;
		base->data[sub].number_adult = number_adult;
		base->data[sub].number_old = number_old;
		base->data[sub].number_male = number_male;
		base->data[sub].number_female = number_female;
		int n = 0;
		for (int i = 0;i <= base->data[sub].sz;i++)
		{
			n += base->data[sub].data_room[i].number;
		}

		base->data[sub].occ_rate = (int)((((double)n) / (rom->sz + 1)) * 100);
	}
}


void sta_start(DATA_BASE* base, DATE* dat)
{
	FILE* Fbasec = fopen("./file/Fbasec", "r");
	FILE* Fbase = fopen("./file/Fbase", "r");

	FILE* Fdatc = fopen("./file/Fdatc", "w");
	FILE* Fdat = fopen("./file/Fdat", "w");

	if (NULL != Fbasec && NULL != Fbase && NULL != Fdatc && NULL != Fdat)
	{
		for (int i = 0;i <= base->sz;i++)
		{
			free(base->data[i].data_room);
		}
		fread(&base->sz, sizeof(int), (size_t)1, Fbasec);
		fread(&base->maxsz, sizeof(int), (size_t)1, Fbasec);
		fread(&base->data, sizeof(DATA), base->sz + 1, Fbasec);

		for (int i = 0;i <= base->sz;i++)
		{
			Room* tmp = (Room*)calloc(base->data[i].maxsz, sizeof(Room));
			if (NULL == tmp)
			{
				perror("sta_start Room_tmp :");
				return;
			}
			base->data[i].data_room = tmp;
			fread(base->data[i].data_room, sizeof(Room), base->data[i].sz + 1, Fbase);
		}

		fread(&dat->sz, sizeof(int), (size_t)1, Fdatc);
		fread(&dat->maxsz, sizeof(int), (size_t)1, Fdatc);
		fread(dat->ymd, sizeof(char[YMD]), dat->sz + 1, Fdat);

	}

	if (NULL != Fbasec && NULL != Fbase && NULL != Fdatc && NULL != Fdat)
	{
		fclose(Fbasec);
		fclose(Fbase);
		fclose(Fdatc);
		fclose(Fdat);
	}

	Fbasec = Fbase = Fdatc = Fdat = NULL;
}

void sta_Exit(DATA_BASE* base, DATE* dat)
{
	FILE* Fbasec = fopen("./file/Fbasec", "w");
	FILE* Fbase = fopen("./file/Fbase", "w");
	if (NULL == Fbasec || NULL == Fbase)
	{
		perror("sta_Exit base:");
		return;
	}
	fwrite(&base->sz, sizeof(int), (size_t)1, Fbasec);
	fwrite(&base->maxsz, sizeof(int), (size_t)1, Fbasec);
	fwrite(base->data, sizeof(DATA), ((size_t)base->sz + (size_t)1), Fbasec);
	for (int i = 0;i <= base->sz;i++)
	{
		fwrite(base->data[i].data_room, sizeof(Room), base->sz + 1, Fbase);
	}
	fclose(Fbasec);
	fclose(Fbase);

	Fbasec = Fbase = NULL;

	FILE* Fdatc = fopen("./file/Fdatc", "w");
	FILE* Fdat = fopen("./file/Fdat", "w");
	if (NULL == Fdatc || NULL == Fdat)
	{
		perror("sta_Exit dat:");
		return;
	}
	fwrite(&dat->sz, sizeof(int), (size_t)1, Fdatc);
	fwrite(&dat->maxsz, sizeof(int), (size_t)1, Fdatc);
	fwrite(dat->ymd, sizeof(char[YMD]),dat->sz + 1, Fdat);
	fclose(Fdatc);
	fclose(Fdat);

	Fdatc = Fdat = NULL;
}




int Max(int A, int B, int C)
{
	A = A > B ? A : B;
	A = A > C ? A : C;
	return A;
}


