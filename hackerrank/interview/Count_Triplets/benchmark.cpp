#include<benchmark/benchmark.h>
#include "solution1.hpp"
#include "solution2.hpp"

static void BM_main2(benchmark::State& state) {
  auto filename = "input6.txt";
  auto arr = get_array(filename);
  auto r = get_ratio(filename);
  for (auto _ : state){
    solution2(arr,r);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_main2);

// Define another benchmark
static void BM_main(benchmark::State& state) {
  auto filename = "input6.txt";
  auto arr = get_array(filename);
  auto r = get_ratio(filename);
  for (auto _ : state){
    solution1(arr,r);}
}
BENCHMARK(BM_main);

BENCHMARK_MAIN();