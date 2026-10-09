



namespace std
{

    struct node // NOLINT
    {

        using first_type = int;
        using second_type = int64;

        first_type v;
        second_type w;
    };

    template<>
    struct tuple_size<node> : std::integral_constant<size_t,2>{}; // NOLINT

    template<>
    struct tuple_element<0,node>    // NOLINT
    { using type = node::first_type; };

    template<>
    struct tuple_element<1,node>    // NOLINT
    { using type = node::second_type; };

#define GET(T,C) \
    template<size_t I> \
    fun constexpr get(C T& v) -> C std::tuple_element<I,T>::type& \
    {              \
        if constexpr(I == 0) { \
            return v.v; \
        } else if constexpr(I == 1) { \
            return v.w; \
        } \
    }

#define GET_R(T,C) \
    template<size_t I> \
    fun constexpr get(C T&& v) -> C std::tuple_element<I,T>::type&& \
    {          \
        using type = std::tuple_element_t<I,T>;     \
        if constexpr(I == 0) { \
            return std::forward<type>(v.v); \
        } else if constexpr(I == 1) { \
            return std::forward<type>(v.w); \
        } \
    }

GET(node,)    // NOLINT
GET(node,const)   // NOLINT
GET_R(node,) // NOLINT
GET_R(node,const)  // NOLINT

}

using std::node;

fun dijkstra(int start,const auto& graph)
{
    let path = std::vector(graph.size(),-1);    // 到达这个点需要的前置点
    let dis = std::vector(graph.size(),INF64);
    let vis = std::vector(graph.size(),false);

    dis[start] = 0;

    let que = heap{ std::greater{},[](node v){ return v.w; },[](node v){ return v.v; }};
    que.emplace(start,dis[start]);

    while(not que.empty()) {

        let [i,_] = que.top();
        que.pop();
        vis[i] = true;

        for(let [v,w] in graph[i] | filter([&](node v){ return not vis[v.v]; })) {
            if(dis[i] + w < dis[v]) {
                dis[v] = dis[i] + w;
                path[v] = i;
                que.emplace(v,dis[v]);
            }
        }
    }

    return path;

}