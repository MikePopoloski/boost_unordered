#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered/unordered_node_map.hpp>
#include <boost/unordered/unordered_node_set.hpp>

int main() {
    boost::unordered_flat_map<std::string, int> map;
    map["asdf"] = 4;
    map.emplace("bar", 5);

    printf("asdf: %d\n", map["asdf"]);
    printf("bar: %d\n", map.find("bar")->second);
}
