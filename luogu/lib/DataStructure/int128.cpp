

fun operator<<(std::ostream& os,__int128 v) -> std::ostream&
{ return os << std::format("{}",v); }