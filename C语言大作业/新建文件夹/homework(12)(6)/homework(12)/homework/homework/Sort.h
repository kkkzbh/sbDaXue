#pragma once



void Sort(void* dst, size_t block, size_t sz, int (*f)(void* e1, void* e2));

static void Swap(void* e1, void* e2, size_t block);

int INT(void* e1, void* e2);


int Person_Index(void* e1, void* e2);


int Person_Name(void* e1, void* e2);


int Person_Sex(void* e1, void* e2);


int Person_Age(void* e1, void* e2);


int Person_Idnum(void* e1, void* e2);


int Person_Phone(void* e1, void* e2);


int Person_vip(void* e1, void* e2);


int Person_Ymd(void* e1, void* e2);















