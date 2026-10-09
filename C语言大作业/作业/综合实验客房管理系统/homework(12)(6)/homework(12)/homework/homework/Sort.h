#pragma once



void Sort(void* dst, size_t block, size_t sz, int (*f)(void* e1, void* e2));

static void Swap(void* e1, void* e2, size_t block);

int INT(void* e1, void* e2);

int Person_index(void* e1, void* e2);

int Person_name(void* e1, void* e2);

int Person_sex(void* e1, void* e2);

int Person_age(void* e1, void* e2);

int Person_idnum(void* e1, void* e2);

int Person_phone(void* e1, void* e2);

int Person_vip(void* e1, void* e2);

int Person_ymd(void* e1, void* e2);

int Room_index(void* e1, void* e2);

int Room_id(void* e1, void* e2);

int Room_type(void* e1, void* e2);

int Room_loaction(void* e1, void* e2);

int Room_state(void* e1, void* e2);

int Room_price(void* e1, void* e2);

int Room_ymd(void* e1, void* e2);

int Room_hms(void* e1, void* e2);

int Res_index(void* e1, void* e2);

int Res_name(void* e1, void* e2);

int Res_vip(void* e1, void* e2);

int Res_price(void* e1, void* e2);

int Res_sex(void* e1, void* e2);

int Res_age(void* e1, void* e2);

int Res_ymd(void* e1, void* e2);

int Res_hms(void* e1, void* e2);

int Res_type(void* e1, void* e2);

int Res_wday(void* e1, void* e2);

int Res_mon(void* e1, void* e2);

int Res_year(void* e1, void* e2);

void menu_Sort_Person(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void menu_Sort_Room(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void menu_Sort_Res(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);







