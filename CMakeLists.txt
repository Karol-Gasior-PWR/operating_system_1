cmake_minimum_required(VERSION 3.16)

project(os_project_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Główny target aplikacji
add_executable(os_project_1
    main.cpp
    karol.h
    threadcounter.h threadcounter.cpp)

# Target testowy dla Catch2
add_executable(tests test_algorithm.cpp
    test_utils.h
    test_utils.cpp)

# Znajdź i dołącz Catch2 (zakładam, że zainstalowane w systemie)
find_package(Catch2 REQUIRED)

# Linkuj Catch2 do targetu testowego
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(GNUInstallDirs)
install(TARGETS os_project_1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)









