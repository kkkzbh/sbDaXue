

struct node
{
    int v,weight;
};

fun prim(std::vector<std::vector<node>>& graph,int start) -> std::optional<int>
{
let vis = std::vector(graph.size(),false);
let que = std::priority_queue<node,std::vector<node>,decltype([](node x,node y){ return x.weight > y.weight; })>{};
//let que = heap{ std::greater{},[](node v){ return v.weight; },[](node v){ return v.v; }};

vis[start] = true;
for(let [v,weight] in graph[start]) {
que.emplace(v,weight);
}
let cnt = 1;
let ans = 0;
while(not que.empty()) {
let [v,weight] = que.top();
que.pop();
if(vis[v]) {
continue;
}
vis[v] = true;
++cnt;
ans += weight;
for(let [vv,w] in graph[v]) {
if(vis[vv]) {
continue;
}
que.emplace(vv,w);
}
}
if(cnt == graph.size()) {
return ans;
}
return {};
}