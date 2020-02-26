#include <bits/stdc++.h>
#include <benchmark/benchmark.h>
#include "solutions.hpp"

using namespace std;

void atFunction(){
    unordered_map<int,int> umap;
    umap[0] = 0;
    for(int i=0;i<100;++i)
    {
        umap[0]+=1;
    }
}

void bracketFuction(){
    unordered_map<int,int> umap;
    umap[0] = 0;
    for(int i=0;i<100;++i)
    {
        umap.at(0)+=1;
    }
}

static void BM_atOperator(benchmark::State & state){
    for(auto _: state)
    atFunction();
}
BENCHMARK(BM_atOperator);

static void BM_bracketFunction(benchmark::State &state){
    for(auto _:state){
        bracketFuction();
    }
}
BENCHMARK(BM_bracketFunction);

// it is faster when there are a lot of Anagrams
static void BM_solution_easy(benchmark::State &state){
    for(auto _:state){
                                  //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        sherlockAndAnagrams_easy("mhmgmbbccbbaffhbncgndbffkjbhmkfncmihhdhcebmchnfacdigflhhbekhfejblegakjjiejeenibemfmkfjbkkmlichlkbnhc");
    }
}

// it is faster when there are few anagrams
BENCHMARK(BM_solution_easy);
static void BM_solution_complicated(benchmark::State &state){
    for(auto _:state){
        sherlockAndAnagrams_complicated("mhmgmbbccbbaffhbncgndbffkjbhmkfncmihhdhcebmchnfacdigflhhbekhfejblegakjjiejeenibemfmkfjbkkmlichlkbnhc");
    }
}
BENCHMARK(BM_solution_complicated);
BENCHMARK_MAIN();