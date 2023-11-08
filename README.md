# ft_containers
STL containers reimplementation using C++98 

# ft_containers

ft_containers is a project provided in 42 https://42.fr/ Common Core cursus, Where it is required to fully reimplemnt Some STL containers (std::vector, std::stack, std::map and std::set).

In this repository there is a reimplementation of following C++ containers:
- [x] Vector ([std::vector])
- [x] List ([std::list])
- [x] Stack ([std::stack])
- [x] Map ([std::map])

My implementation is based on the official STL containers documentaion:
- [x] [std::vector]: http://www.cplusplus.com/reference/vector/vector
- [x] [std::stack]: http://www.cplusplus.com/reference/stack/stack
- [x] [std::map]: http://www.cplusplus.com/reference/map/map
- [x] [std::set]: http://www.cplusplus.com/reference/set/set

My map/set implementations all use the RedBlack tree data structure (RBT) folder in this repository as the
underlying datastructure.

This implementation comes with a large set of tests in the test directory assosiated with a Makefile.
