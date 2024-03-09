#include <array>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>

#include <variant>

using StringView = std::string_view;

template<typename T, size_t N>
using Array = std::array<T, N>;

template<typename T>
using Stack = std::stack<T>;

template<typename T>
using Queue = std::queue<T>;

template<typename T>
using BinaryHeap = std::priority_queue<T, cxx_rusty::vec::Vec<T>, std::less<T>>;

template<typename T>
using BinaryHeapMax = std::priority_queue<T, cxx_rusty::vec::Vec<T>, std::greater<T>>;

template<typename K, typename V>
using MultiMap = std::multimap<K, V>;

template<typename K, typename V>
using Set = std::set<K, V>;

template<typename K, typename V>
using MultiSet = std::multiset<K, V>;

template<typename K, typename V>
using HashSet = std::unordered_set<K, V>;

template<typename... Args>
using Variant = std::variant<Args...>;