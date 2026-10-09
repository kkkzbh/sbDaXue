

#include"hufio.h"
#include"concept.h"

#ifdef O2


//auto write(const huftree& tree,std::ofstream& ofs) -> void
//{
//    uint sz{ static_cast<uint>(tree.a.size() )};
//    ofs.write(reinterpret_cast<const char*>(&sz),sizeof(sz));
//    for(const auto& it : tree.a)
//    {
//        ofs.write(reinterpret_cast<const char*>(&it),sizeof(it));
//    }
//}
//
//auto read(huftree& tree,std::ifstream& ifs) -> void
//{
//    uint sz;
//    ifs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
//    tree.a.resize(sz);
//    for(auto& it : tree.a)
//    {
//        ifs.read(reinterpret_cast<char*>(&it),sizeof(it));
//    }
//}

//auto write(const deflate_tree& tree,std::ofstream& ofs) -> void
//{
//    uint sz{ static_cast<uint>(tree.a.size() )};
//    ofs.write(reinterpret_cast<const char*>(&sz),sizeof(sz));
//    for(const auto& it : tree.a)
//    {
//        ofs.write(reinterpret_cast<const char*>(&it),sizeof(it));
//    }
//}
//
//auto read(deflate_tree& tree,std::ifstream& ifs) -> void
//{
//    uint sz;
//    ifs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
//    tree.a.resize(sz);
//    for(auto& it : tree.a)
//    {
//        ifs.read(reinterpret_cast<char*>(&it),sizeof(it));
//    }
//}


#endif


