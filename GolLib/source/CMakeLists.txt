add_library(GameOfLifeLib GolGrid.cpp GameOfLife.cpp DistributeInitialGrid.cpp GameOfLifeMPI.cpp GameOfLifeStillLifes.cpp)
target_include_directories(GameOfLifeLib PUBLIC ${CMAKE_SOURCE_DIR}/GolLib/include)
#Add OpenMP
target_link_libraries(GameOfLifeLib PUBLIC OpenMP::OpenMP_CXX)

#Add MPI
find_package(MPI REQUIRED)
if(MPI_CXX_FOUND)
    target_link_libraries(GameOfLifeLib PUBLIC MPI::MPI_CXX)
endif()