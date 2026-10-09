

#ifdef P1321

#include<iostream>
#include<string>

int main()
{
    std::string s;
    std::cin >> s;
    int pos = 0;
    int male = 0;
    int female = 0;
    while((pos = s.find("boy",pos)) != std::string::npos)
    {
        ++male;
        s.replace(pos,3,"...");
    }
    pos = 0;
    while((pos = s.find("bo",pos)) != std::string::npos)
    {
        ++male;
        s.replace(pos,2,"..");
    }
    pos = 0;
    while((pos = s.find("oy",pos)) != std::string::npos)
    {
        ++male;
        s.replace(pos,2,"..");
    }
    pos = 0;
    while((pos = s.find('b',pos)) != std::string::npos)
    {
        ++male;
        s.replace(pos,1,".");
    }
    pos = 0;
    while((pos = s.find('o',pos)) != std::string::npos)
    {
        ++male;
        s.replace(pos,1,".");
    }
    pos = 0;
    while((pos = s.find('y',pos)) != std::string::npos)
    {
        ++male;
        s.replace(pos,1,".");
    }
    pos = 0;
    while((pos = s.find("girl",pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,4,"....");
    }
    pos = 0;
    while((pos = s.find("irl",pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,3,"...");
    }
    pos = 0;
    while((pos = s.find("gir",pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,4,"...");
    }
    pos = 0;
    while((pos = s.find("gi",pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,2,"..");
    }
    pos = 0;
    while((pos = s.find("ir",pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,2,"..");
    }
    pos = 0;
    while((pos = s.find("rl",pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,2,"..");
    }
    pos = 0;
    while((pos = s.find('g',pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,1,".");
    }
    pos = 0;
    while((pos = s.find('i',pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,1,".");
    }
    pos = 0;
    while((pos = s.find('r',pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,1,".");
    }
    pos = 0;
    while((pos = s.find('l',pos)) != std::string::npos)
    {
        ++female;
        s.replace(pos,1,".");
    }
    std::cout << male << '\n' << female;

    return 0;
}

#endif
