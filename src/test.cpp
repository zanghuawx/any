#include <cassert>

#include <string>

#include <iostream>

#include "any.h"

using utils::any;

using utils::any_cast;

using utils::bad_any_cast;

using std::string;

using std::cout;

using std::cerr;

using std::endl;

void contruct_test()
{
  any def;
  any copy_on_type(42);
  def = 3.14;
  def = string("2.71");
  any def_copy(def);
  def = copy_on_type;
  any e;
  assert(e.empty());
}

template<class T>
void check_cast(any& a, bool should_throw)
{
  bool thrown = false;
  try
  {
    double res = any_cast<T>(a);
    std::cout << res << std::endl;
  }
  catch(bad_any_cast const& err)
  {
    thrown = true;
    std::cerr << err.what() << std::endl;
  }
  assert(should_throw == thrown);
}

void retrieve_value_test()
{
  any ia(42);
  auto res = any_cast<double>(&ia);
  assert(res == nullptr);
  check_cast<double>(ia, true );
  check_cast<int> (ia, false);
}

void swap_test(any& a, any& b)
{
  swap(a, b);
}

void my_cast_test()
{
  any a(5);
  any* ptr_a = &a;
  any& ref_a = a;

  try
  {
    auto b = any_cast<int>(a);
    (void)b;
  }
  catch (const bad_any_cast& e)
  {
    cout << "1 " << e.what() << endl;
  }

  try
  {
    auto b = any_cast<int*>(ptr_a);
    (void)b;
  }
  catch (const bad_any_cast& e)
  {
    cout << "2 " << e.what() << endl;
  }

  try
  {
    int& b = any_cast<int&>(a);
    ++b;
    int c = any_cast<int>(a);
    cout << c << endl;
  }
  catch (const bad_any_cast& e)
  {
    cout << "3 " << e.what() << endl;
  }


  try
  {
    auto c = any_cast<double>(a);
    (void)c;
  }
  catch (const bad_any_cast& e)
  {
    cout << "4 " << e.what() << endl;
  }

  try
  {
    auto c = any_cast<double*>(ptr_a);
    (void)c;
  }
  catch (const bad_any_cast& e)
  {
    cout << "5 " << e.what() << endl;
  }

  try
  {
    double& c = any_cast<double&>(a);
    ++c;
  }
  catch (const bad_any_cast& e)
  {
    cout << "6 " << e.what() << endl;
  }  
  (void)ref_a;
}

int main()
{
  contruct_test();
  retrieve_value_test();
  any a(5), b(string("6"));
  swap_test(a, b);
  my_cast_test();
  return 0;
}

