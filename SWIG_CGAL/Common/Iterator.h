// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_ITERATOR_H
#define SWIG_CGAL_COMMON_ITERATOR_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/triple.h>

#ifndef SWIG  
template <class T>
struct Iterator_helper{
  
  template <class Iterator>
  static T convert(const Iterator& it,typename boost::enable_if< 
                                                      boost::is_same<
                                                        typename internal::Converter<T>::result_type,
                                                        typename std::iterator_traits<Iterator>::value_type
                                                      >
                                              >::type* =0)
  {
    return T(*it);
  }

  template <class Ti>
  static T convert(const Ti& i,typename boost::enable_if< 
                                    boost::is_same< 
                                      boost::false_type,
                                      typename boost::is_same<
                                        typename internal::Converter<T>::result_type,
                                        typename std::iterator_traits<Ti>::value_type
                                      >::type
                                    >
                                  >::type* =0)
  {
    return T(i);
  }
  

  static T
  default_value(){return T();}
};

template<class T1>
struct Iterator_helper<std::pair<T1,int> >{
  template <class T>
  static std::pair<T1,int> convert(const T& i){
    return std::pair<T1,int>(T1(i->first),i->second);
  }
  
  static std::pair<T1,int>
  default_value(){return std::pair<T1,int>(T1(),-1);}
};

template<class T1>
struct Iterator_helper<std::pair<T1,double> >{
  template <class T>
  static std::pair<T1,double> convert(const T& i){
    return std::pair<T1,double>(T1(i->first),i->second);
  }
  
  static std::pair<T1,double>
  default_value(){return std::pair<T1,double>(T1(),-1);}
};

template<class T1>
struct Iterator_helper<SWIG_CGAL::Triple<T1,int,int> >{
  template <class T>
  static SWIG_CGAL::Triple<T1,int,int> convert(const T& i){
    return SWIG_CGAL::Triple<T1,int,int>(T1(i->first),i->second,i->third);
  }
  
  static SWIG_CGAL::Triple<T1,int,int>
  default_value(){return SWIG_CGAL::Triple<T1,int,int>(T1(),-1,-1);}
};

template<>
struct Iterator_helper<double>{
  template <class T>
  static double convert(const T& i){  return *i; }
  static double default_value(){return 0.;}
};
#endif


#ifdef SWIGPYTHON
#include <SWIG_CGAL/Python/exceptions.h>
#endif

template<class Cpp_iterator,class Value_type>
class SWIG_CGAL_Iterator{
  Cpp_iterator cur;
  Cpp_iterator end;
public:

  SWIG_CGAL_Iterator(){}

  #ifndef SWIG
  SWIG_CGAL_Iterator(
    Cpp_iterator cur_,
    Cpp_iterator end_
  ):cur(cur_),end(end_){}
  #endif
    
  #ifdef SWIGPYTHON
  SWIG_CGAL_Iterator<Cpp_iterator,Value_type> __iter__(){return *this;}

  Value_type next()
  {
    if (cur!=end)
      return Iterator_helper<Value_type>::convert ( (cur++) );
    throw Stop_iteration();
    return Iterator_helper<Value_type>::default_value();
  }
  #else

  #ifdef SWIGJAVA
  Value_type slow_next()
  #else
  Value_type next()
  #endif  
  {
    if (cur!=end)
      return Iterator_helper<Value_type>::convert ( (cur++) );
    return Iterator_helper<Value_type>::default_value();
  }
  #endif //SWIGPYTHON
  
  void next(Value_type& r)
  {
    if (cur!=end)
      r=Iterator_helper<Value_type>::convert ( (cur++) );
    #ifdef SWIGPYTHON
    throw Stop_iteration();
    #endif
  }

  bool hasNext(){
    return cur!=end;
  }
};

template<class Cpp_circulator,class Value_type>
class SWIG_CGAL_Circulator{
  Cpp_circulator cur;
public:
  SWIG_CGAL_Circulator(){}
  #ifndef SWIG
  SWIG_CGAL_Circulator( Cpp_circulator cur_):cur(cur_){}
  #endif
  
  #ifdef SWIGPYTHON
  SWIG_CGAL_Circulator<Cpp_circulator,Value_type> __iter__(){return *this;}
  #endif

  #ifdef SWIGJAVA
  Value_type slow_next()
  #else
  Value_type next()
  #endif
  {
    return Iterator_helper<Value_type>::convert ( (cur++) );
  }
  
  void next(Value_type& r)
  {
    r = Iterator_helper<Value_type>::convert ( (cur++) );
  }
  
  Value_type prev() {
    return Iterator_helper<Value_type>::convert ( (cur--) );
  }
  
  bool hasNext(){return true;}
};



#endif //SWIG_CGAL_COMMON_ITERATOR_H