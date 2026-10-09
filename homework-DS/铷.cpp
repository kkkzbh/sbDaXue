#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
struct Node
{
    char scr;//原字符
    long count;//字符出现的次数
    long parent,lch,rch;
    char code[256];//对应的哈弗曼编码
};
struct Node TNode[512],temp;//TNode相当于字典,temp用于排序
void yasuo();
int jieyasuo();
FILE * readSourceFile();//用于打开待压缩文档
FILE * foundFinalFile();//用于创建并打开压缩文档
void InitialHTree(Node TNode[512]);//用于初始化哈夫曼树
void CreatHTree(Node TNode[512],int n,int m);//用于构建哈夫曼树并计算编码，n为字符种类数，m为哈夫曼结点总数
void InputFinalFile(FILE*ifp,FILE*ofp,int flength,int n);//用于输入压缩文件
int readCompressedData(FILE* ifp, long *flength,char buffer[255]);//从文件初始位置读出压缩文件的信息
void sortCodes(long n) ;//根据编码为字符排序
void decompressData(FILE* ifp, FILE* ofp, long flength,char buffer[255],int n);//解压并写入文件
int main( )
{
    printf("输入1开始压缩\n");
    printf("输入2解压缩\n");
    printf("输入3结束程序\n");
    char c;
    printf("请输入待执行的操作：");
    scanf("%c",&c);
    getchar();
    while(1)
    {
        if(c=='1')
            yasuo();
        else if(c=='2')
        {
            jieyasuo();
        }
        else if(c=='3')
        {
            printf("程序结束！\n");
            break;
        }
        printf("请输入待执行的操作：");
        scanf("%c",&c);
        getchar();
    }
    return 0;
}
FILE* readSourceFile()
{
    FILE*ifp;
    char filename[255];
    printf("请输入待处理的文件地址和文件名及后缀：");
    scanf("%s",filename);
    getchar();
    ifp = fopen(filename,"rb");
    while(ifp==NULL)
    {
        printf("打开文件时出错！\n");
        printf("请重新输入待处理的文件地址和文件名及后缀：");
        scanf("%s",filename);
        getchar();
        ifp=fopen(filename,"rb");
    }
    return ifp;
}

FILE* foundFinalFile()
{
    FILE* ofp;
    char outputfile[255];
    printf("请输入储存处理后的文件地址和文件名及后缀：");
    scanf("%s",outputfile);
    getchar();
    ofp = fopen(outputfile,"wb");
    while(ofp==NULL)
    {
        printf("打开文件时出错！\n");
        printf("请重新输入储处理后的文件地址和文件名及后缀：");
        scanf("%s",outputfile);
        getchar();
        ofp=fopen(outputfile,"wb");
    }
    return ofp;
}

void InitialHTree(Node TNode[512])
{
    int i;
    //构造哈弗曼树，初始化结点
    for(i=0;i<512;i++)
    {
        if(TNode[i].count != 0)
            TNode[i].scr = (unsigned char)i;
        else
            TNode[i].scr = -1; //表示没有该字符
        TNode[i].parent = -1;
        TNode[i].lch = TNode[i].rch = -1;
    }
}

void CreatHTree(Node TNode[512],int n,int m)
{
    int flag;//计数
    long min;
    long lp,i,j;//lp指针
    for(i=n;i<m;i++) //第一个循环是为了找到左孩子节点
    {
        min=999999999;
        for(j=0;j<i;j++)
        {
            if(TNode[j].parent!=-1)
                continue;
            if(min>TNode[j].count)
            {
                lp=j;
                min=TNode[j].count;
                continue;
            }
        }
        TNode[i].count=TNode[lp].count;
        TNode[lp].parent=i;
        TNode[i].lch=lp;
        min=999999999;
        for(j=0;j<i;j++) //第二个循环是为了找到右孩子节点
        {
            if(TNode[j].parent!=-1)
                continue;
            if(min>TNode[j].count)
            {
                lp=j;
                min=TNode[j].count;
                continue;
            }
        }
        TNode[i].count+=TNode[lp].count; //并成父节点
        TNode[i].rch=lp;
        TNode[lp].parent=i;
    }
    //从叶节点开始，沿着其父节点向上追溯,构造哈弗曼编码
    for(i=0;i<n;i++)
    {
        flag= i;
        TNode[i].code[0] = 0;
        while(TNode[flag].parent != -1)
        {
            j = flag;
            flag = TNode[flag].parent;
            if(TNode[flag].lch==j)
            {
                j = strlen(TNode[i].code);
                memmove(TNode[i].code+1,TNode[i].code,j+1);
                TNode[i].code[0]='0';
            }
            else
            {
                j=strlen(TNode[i].code);
                memmove(TNode[i].code+1,TNode[i].code,j+1);
                TNode[i].code[0]='1';
            }
        }
    }
}

void InputFinalFile(FILE*ifp,FILE*ofp,int flength,int n)
{
    unsigned char c;
    char buffer[512];
    int flag,lp,i,j;
    //读取源文件中的每一个字符，按照设置好的编码替换文件中的字符
    fseek(ifp,0,SEEK_SET);//把文件指针指向文件的开头
    fseek(ofp,8,SEEK_SET);//以8位二进制数为单位读取
    buffer[0] = 0;
    flag = 0; //计数器
    lp = 8;//用于指示写入文件位置
    while(!feof(ifp))
    {
        c=fgetc(ifp); //从流中读取一个字符，并增加文件指针的位置
        flag++;
        for(i=0;i<n;i++) //在字符编码表 TNode 中查找与读取的字符 c 匹配的
        {
            if(c==TNode[i].scr)
                break;
        }
        strcat(buffer,TNode[i].code); //把编码添加到buffer结尾处
        j = strlen(buffer);//计算字符串buffer的长度
        c = 0;
        while(j>=8) //位数达到8的倍数，按八位二进制数转化成十进制ASCII码写入文件一次进行压缩
        {
            for(i=0;i<8;i++)
            {
                if(buffer[i]=='1') c=(c<<1)|1;
                else c=c<<1;
            }
            fwrite(&c,1,1,ofp);
            lp++;
            strcpy(buffer,buffer+8);
            j=strlen(buffer);
        }
        if(flag==flength)
            break;
    }
    if(j > 0) //剩余字符数量少于8个
    {
        strcat(buffer,"00000000");
        for(i=0;i<8;i++)
        {
            if(buffer[i]=='1') c=(c<<1)|1;
            else c = c << 1;   //对不足的位数补0
        }
        fwrite(&c,1,1,ofp);
        lp++;
    }
    //将编码信息写入存储文件，便于解压
    fseek(ofp,0,SEEK_SET);//将输出文件的文件指针移动到开头
    fwrite(&flength,1,sizeof(flength),ofp); //将文件长度和哈夫曼编码信息的起始位置写入输出文件
    fwrite(&lp, sizeof(long), 1, ofp);//将文件位置指针lp 写入输出文件
    fseek(ofp,lp,SEEK_SET); //将文件指针移动到哈夫曼编码信息的起始位置
    fwrite(&n,sizeof(long),1,ofp);//将字符编码表中的字符数量写入输出文件
    for(i=0;i<n;i++) //将字符编码表中的每个字符和对应的编码写入输出文件
    {
        temp=TNode[i];
        fwrite(&(TNode[i].scr),1,1,ofp);
        lp++;
        c=strlen(TNode[i].code);
        fwrite(&c,1,1,ofp);
        lp++;
        j=strlen(TNode[i].code);
        if(j % 8!=0) //按八位读取，位数不满8位时，对该位补0
        {
            for(flag=j%8;flag<8;flag++)
                strcat(TNode[i].code,"0");
        }
        while(TNode[i].code[0]!=0)
        {
            c=0;
            for(j=0;j<8;j++)
            {
                if(TNode[i].code[j]=='1')
                    c=(c<<1)|1;
                else c = c << 1;
            }
            strcpy(TNode[i].code,TNode[i].code+8);//把从TNode[i].code+8地址开始且含有NULL结束符的字符串赋值到以TNode[i].code开始的地址空间
            fwrite(&c,1,1,ofp);
            lp++;
        }
        TNode[i]=temp;
    }
    fclose(ifp);
    fclose(ofp);
}

void yasuo()
{
    unsigned char c; //用于临时存储字节数据
    long i,j,m,n; //n为字符总数量，m用于统计字符总长度
    long flength;
    FILE *ifp,*ofp;
    ifp=readSourceFile();
    ofp=foundFinalFile();

    flength = 0;
    //读取ifp文件
    while(!feof(ifp)) //文件结束符（EOF）还没有到达
    {
        fread(&c,1,1,ifp);//按位读取文件
        TNode[c].count++;//记录该字符出现的次数
        flength++; //记录文件的字符总数
    }
    flength--; //将最后一个字符（实际上是 EOF）的计数减一
    TNode[c].count--;//读取文件结束

    InitialHTree(TNode);//初始化哈夫曼树
    //按结点出现的次数排序
    for(i=0;i<256;i++)
    {
        for(j=i+1;j<256;j++)
        {
            if(TNode[i].count < TNode[j].count)
            {
                temp=TNode[i];
                TNode[i] = TNode[j];
                TNode[j] = temp;
            }
        }
    }
    //统计字符种类数
    for(i=0;i<256;i++)
        if(TNode[i].count==0)
            break;
    n=i; //n为字符种类数
    m=2*n-1; //哈夫曼树所需的总节点数 m
    CreatHTree(TNode,n,m);//创建哈夫曼树并算出编码
    InputFinalFile(ifp,ofp,flength,n);//写入压缩文件
    printf("文件压缩成功！\n");
}

int readCompressedData(FILE* ifp, long*flength,char buffer[255])
{
    int len=0,n,m,i,j,p,flag,l;
    unsigned char c;//用于临时存储字节数据
    fseek(ifp,0,SEEK_END);//将文件指针(ifp)移动到文件的尾部
    len = ftell(ifp);//文件指针ifp当前的位置，记录文件当中的字节数
    fseek(ifp,0,SEEK_SET);//将文件指针(ifp)移动到文件的起始位置

    //从输入文件中读取原文件的长度和其他参数
    fread(flength, sizeof(long), 1, ifp);   //读取原文件长
    fread(&flag, sizeof(long), 1, ifp);
    fseek(ifp, flag, SEEK_SET);//从f位置开始往后读
    fread(&n, sizeof(long), 1, ifp); //总共的字符种类数

    //读取原文件的头部信息,字符、编码长度
    for (i = 0; i < n; i ++) //读取压缩文件内容并转换成二进制码
    {
        fread(&TNode[i].scr, 1, 1, ifp);//读取字符i的ASCII码
        fread(&flag, 1, 1, ifp);//读取字符的哈弗曼编码
        p = (long) c;//读编码的长度
        TNode[i].count = p;
        TNode[i].code[0] = 0;

        //计算编码长度所需的字节数
        if (p % 8 > 0) m = p / 8 + 1;
        else
            m = p / 8;
        //读取每个字符的编码，并将其转换为二进制字符串
        for (j = 0; j < m; j ++)
        {
            fread(&c, 1 , 1 , ifp);
            flag = c;
            _itoa(flag, buffer, 2);//将整数flag转换为二进制，并将结果存储在buffer中
            flag = strlen(buffer);
            //将编码补齐为固定长度，并存储在 TNode[i].code中
            for (l = 8; l > flag; l --)
            {
                strcat(TNode[i].code, "0");//位数不足，补零
            }
            strcat(TNode[i].code, buffer);
        }
        TNode[i].code[p] = 0;
    }
    return n;
}

void sortCodes(long n)
{
    int i,j;
    //对编码进行排序，以便解压缩时能够正确匹配编码
    for (i = 0; i < n; i ++)
    {
        for (j = i + 1; j < n; j ++)
        {
            if (strlen(TNode[i].code) > strlen(TNode[j].code))//长度最小，出现次数最多
            {

                temp = TNode[i];
                TNode[i] = TNode[j];
                TNode[j] = temp;//根据出现次数排序

            }
        }
    }
}

void decompressData(FILE* ifp, FILE* ofp, long flength,char buffer[255],int n)
{
    int p,m,i;
    char buffer2[255];
    unsigned char c;//用于临时存储字节数据
    int f,l;
    // 解压数据...
    //获取最长编码长度，并将文件指针移动到解压缩数据的起始位置
    p = strlen(TNode[n-1].code);
    fseek(ifp, 8, SEEK_SET);
    m = 0;
    buffer2[0] = 0;
    while (1)
    {
        while (strlen(buffer2) < (unsigned int)p)
        {
            //循环读取输入文件中的字节，并将其转换为二进制字符串
            fread(&c, 1, 1, ifp);
            f = c;
            _itoa(f, buffer, 2);//f转化成二进制存入buffer中
            f = strlen(buffer);
            //编码字典中查找与当前字符串匹配的编码
            for (l = 8; l > f; l --)
            {
                strcat(buffer2, "0");//不足八位补零
            }
            strcat(buffer2, buffer);
        }
        for (i = 0; i < n; i ++)
        {
            if (memcmp(TNode[i].code, buffer2, TNode[i].count) == 0)
                break;//比较字节数，保证数组保存的二进制数字相同
        }
        //将匹配到的字符写入输出文件
        strcpy(buffer2, buffer2 + TNode[i].count);
        c = TNode[i].scr;//ASCII码
        fwrite(&c, 1, 1, ofp);//写入文件中
        m ++;//将匹配到的字符写入输出文件，并增加已写入字符的计数
        if (m == flength)
            break;//写入字符的数量等于文件长度，退出循环
    }
    fclose(ifp);
    fclose(ofp);
}

int jieyasuo()
{
    char buffer[255];
    long n,flength;//n用于储存字符数，flength用于存储文件长度
    FILE *ifp, *ofp;
    ifp=readSourceFile();
    ofp=foundFinalFile();
    //以二进制写入模式打开用于输出的文件，获取输入文件的长度
    n=readCompressedData( ifp, &flength,buffer);
    sortCodes(n);
    decompressData( ifp, ofp,flength, buffer, n);
    printf("文件解压成功！\n");
    return 1;
}