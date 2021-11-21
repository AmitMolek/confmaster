# confmaster
Easy to use JSON configuration library.

## CMake

```cmake
add_subdirectory(confmaster/)
target_link_libraries(${TARGET_NAME} PRIVATE confmaster)
```

```cpp
#include "confmaster/confmaster.hpp"
```

## Usage

```cpp
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include "confmaster/confmaster.hpp"

#include <unistd.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        std::cout << "Pass the path to the config file" << std::endl;
        return EXIT_FAILURE;
    }

    std::string config_path = std::string(argv[1]);
    rnd::conf::confmaster cmaster(config_path);
    if (!cmaster.is_valid()){
        std::cerr << "Failed to open/parse config file: " << cmaster.error() << std::endl;
        return EXIT_FAILURE;
    }

    try{
        auto result = cmaster.parse<int, std::string>({"id","name"});
        std::cout << "id=" << std::get<0>(result) << std::endl;
        std::cout << "name=" << std::get<1>(result) << std::endl;
    }catch(rnd::conf::confmaster::base_error_type& e){
        std::cerr << "Error occured while parsing config file: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```