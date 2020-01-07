#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

bool lessThan(const DataStruct &a, const DataStruct &b)
{
  if(a.key1 == b.key1)
  {
    if(a.key2 == b.key2)
    {
      return (a.str.size() < b.str.size());
    }
    return (a.key2 < b.key2);
  }
  return (a.key1 < b.key1);
}

class Line : public std::string
{
  friend std::istream& operator>>(std::istream &is, Line &line)
  {
    return std::getline(is, line);
  }
};

DataStruct getDataFromLine(const Line &line)
{
  std::stringstream stream(line);

  DataStruct data;
  stream >> data.key1;

  stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
  stream >> data.key2;

  stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
  std::getline(stream, data.str);

  if(stream.fail())
  {
    throw std::invalid_argument("invalid input");
  }
  return data;
}
void outputData(DataStruct &data)
{
  std::cout << data.key1 << "," << data.key2 << "," << data.str << std::endl;
}
bool notInRange(const DataStruct &data)
{
  return !((data.key1 >= -5 && data.key1 <= 5) && (data.key2 >= -5 && data.key2 <= 5));
}
int main()
{
  std::vector<DataStruct> vec;
  
  try
  {
    std::transform(std::istream_iterator<Line>(std::cin), std::istream_iterator<Line>(),
      std::back_inserter(vec), getDataFromLine);
  }
  catch(const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return 1;
  }

  if(std::any_of(vec.begin(), vec.end(), notInRange))
  {
    std::cerr << "Data value not in range!";
    return 1;
  }

  std::sort(vec.begin(), vec.end(), lessThan);

  std::for_each(vec.begin(), vec.end(), outputData);

  return 0;
}
