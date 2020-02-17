#include "../src/slider_map.h"
#include <gtest/gtest.h>
#include <ctime>
namespace
{

class SliderMapEasySample: public testing::Test{
protected:  
  string project_dir;
  string rel_path;
  vector<ColorMap> color_maps; 
  SliderMap begin;
  SliderMap end;

  SliderMapEasySample():project_dir{"/home/lenty/scripts/cpp/coding_practice/hackerrank/Contest/projectEurler/#244-Slider/"},
  rel_path{"test/data/input1.txt"},color_maps{read_SliderMap(project_dir,rel_path)},
  begin{color_maps[0],color_maps[1],""}, end{color_maps[1],color_maps[1],""} {}
};

class SliderMapDifficultSample: public testing::Test{
protected:  
  string project_dir;
  string rel_path;
  vector<ColorMap> color_maps; 
  SliderMap begin;
  SliderMap end;

  SliderMapDifficultSample():project_dir{"/home/lenty/scripts/cpp/coding_practice/hackerrank/Contest/projectEurler/#244-Slider/"},
  rel_path{"test/data/input8.txt"},color_maps{read_SliderMap(project_dir,rel_path)},
  begin{color_maps[0],color_maps[1],""}, end{color_maps[1],color_maps[1],""} {}
};





TEST_F(SliderMapEasySample,Move){
  auto case1=begin('U'); 
  EXPECT_EQ(case1.row_idx,1);
  EXPECT_EQ(case1.col_idx,0);
  EXPECT_EQ(case1[0][0],'B');
}

TEST_F(SliderMapEasySample,UnchangedAfterMove){
  auto case1=begin('U');; 
  EXPECT_EQ(begin.row_idx,0);
  EXPECT_EQ(begin.col_idx,0);
  EXPECT_EQ(begin[0][0],'W');
}

TEST_F(SliderMapEasySample,MovementNotAllowed){
  ASSERT_THROW(begin('D'),runtime_error);
}


TEST_F(SliderMapEasySample,Movement){
  EXPECT_TRUE(begin.movementAllowed('L'));
  EXPECT_TRUE(begin.movementAllowed('U'));
  EXPECT_FALSE(begin.movementAllowed('D'));
  EXPECT_FALSE(begin.movementAllowed('R'));
}

TEST_F(SliderMapEasySample,PossibleDirections){
  EXPECT_EQ(begin.possible_dirs,"UL");
}

TEST_F(SliderMapEasySample,NotStepBackFromPreviousAction){
  EXPECT_EQ(begin('L').possible_dirs,"U");
  EXPECT_EQ(begin('U').possible_dirs,"L");
}

TEST_F(SliderMapEasySample,numberOfDiff){
  EXPECT_EQ(begin.n_diff_colors,2);
  EXPECT_EQ(begin('L').n_diff_colors,1);
  EXPECT_EQ(begin('L')('U').n_diff_colors,0);
}

TEST_F(SliderMapEasySample,checksumTest){
  EXPECT_EQ(get_checksum("LU"),18553);
  EXPECT_EQ(get_checksum("LULUR"),19761398);
  
}


TEST_F(SliderMapDifficultSample,TestExecutionTime){
  SliderMap* smap = &begin;
  unsigned int idx{0};
  srand(static_cast<unsigned int>(time(0)));
  for(int i =0; i<100;++i){
    idx = static_cast<unsigned int>(rand()) % smap->possible_dirs.size();    
    auto dir = smap->possible_dirs.at(idx);
    smap = new SliderMap((*smap)(dir));
  }
  smap->print_map();  
}

TEST_F(SliderMapDifficultSample,TestResult){
  string result{"LUULURDRDLLULDRDLURRURUL"};

  SliderMap *smap =&begin;
  for (auto dir:result)
  {
    smap = new SliderMap((*smap)(dir));
  }

  smap->print_map();
}


} // namespace