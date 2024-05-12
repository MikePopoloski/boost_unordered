# boost_unordered
![](https://github.com/MikePopoloski/boost_unordered/actions/workflows/build.yml/badge.svg)
![GitHub](https://img.shields.io/github/license/MikePopoloski/boost_unordered)

This project is a standalone version of the [boost::unordered](https://github.com/boostorg/unordered) library. boost::unordered_flat{map,set} are some of the fastest and highest quality C++ hashmap implementations out there (major props to the authors), but unfortunately they come with the entire rest of boost as baggage if you want to use them. This repository extracts them and snips out the links to the rest of boost so that you can use just the hashmaps.

### Benefits
First and foremost, if you don't otherwise need boost in your project then this will let you avoid taking a dependency on all of boost, which is absolutely gigantic (something like 750MB of sources alone). This may not matter to you if you already have boost installed on your system, but you do need a relatively recent version to get the flat hashmaps and if you are a library you may not want to introduce a transitive dependency on boost to all of your users.

Even more importantly, the unordered headers pull in a giant tree of other header files from the rest of boost, which has a direct impact on compilation times. Building this simple program:
```
#include <boost/unordered/unordered_flat_map.hpp>
int main() {
}
```

We can see that (on my system) we pull in 275 boost header files:
```
> g++-12 -std=c++20 -O2 main.cpp -M | sed 's/\\$//' | awk '{ for (i=1; i<=NF; i++) print $i }' | grep boost | wc -l
275
```
which are 31424 lines in total:
```
> g++-12 -std=c++20 -O2 main.cpp -M | sed 's/\\$//' | awk '{ for (i=1; i<=NF; i++) print $i }' | grep boost | xargs wc -l
...
  31424 total
```

Using the standalone version:
```
> g++-12 -std=c++20 -O2 -I ~/boost_unordered/include main.cpp -M | sed 's/\\$//' | awk '{ for (i=1; i<=NF; i++) print $i }' | grep boost | wc -l
26
> g++-12 -std=c++20 -O2 -I ~/boost_unordered/include main.cpp -M | sed 's/\\$//' | awk '{ for (i=1; i<=NF; i++) print $i }' | grep boost | xargs wc -l
...
  6322 total
```

So we've chopped out 249 files and 25102 lines of code from each translation unit that includes unordered_flat_map. The compilation speedup on my machine for this toy example is about 10%, though your mileage may vary.

There is also an amalgamated single header, [boost_unordered.hpp](https://github.com/MikePopoloski/boost_unordered/blob/master/boost_unordered.hpp), which includes all four of the unordered_* containers in a single header, weighing in at just under 9k lines.

### Tradeoffs
The standalone library requires a modern C++20 capable compiler and standard library. Assuming you have that then you don't really give up anything. All of the tests still pass. A lot of the stuff cut out is to support old or esoteric compilers -- if that's something you use then stick with the full boost installation.

This library does remove the older unordered_{map,set} implementations. unordered_flat_{map,set} and unordered_node_{map,set} are superior containers in almost all cases, and if you have a case that really needs the old-style non-flat containers then you can use the ones included in std or just fall back to the full boost installation.

One other piece of functionality was removed: containerHash in boost has the ability to automatically compute hash values for structures that are annotated via boost::describe. If you are looking to avoid a boost dependency then you probably aren't annotating your types via boost::describe so this doesn't seem so bad, and it lets us get rid of all of the boost::describe headers.

### How to Use
Two ways:
1. Download the boost_unordered.hpp file and include it in your project.
2. Use as a proper CMake target, by downloading the source or by using something like CMake's FetchContent:
```
FetchContent_Declare(
  boost_unordered
  GIT_REPOSITORY https://github.com/MikePopoloski/boost_unordered
  GIT_TAG v1.0
  GIT_SHALLOW ON)

FetchContent_MakeAvailable(boost_unordered)

target_link_libraries(my_executable PRIVATE boost_unordered)
```

### Methodology
The sources in this repository were produced by executing the [make_unordered.sh](https://github.com/MikePopoloski/boost_unordered/blob/master/make_unordered.sh) script.
