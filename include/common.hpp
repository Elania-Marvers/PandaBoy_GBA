#ifndef		___COMMON_HPP___
#define		___COMMON_HPP___

#include <iostream>
#include <cstdint>

#define DEFAULT "\033[00m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define ORANGE "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define LGRAY "\033[0;37m"
#define DGRAY "\033[1;30m"
#define LRED "\033[1;31m"
#define LGREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define LBLUE "\033[1;34m"
#define LPURPLE "\033[1;35m"
#define LCYAN "\033[1;36m"
#define WHITE "\033[1;37m"   

namespace std {
  template <typename _CharT, typename _Traits>
  inline basic_ostream<_CharT, _Traits> &
  tab(basic_ostream<_CharT, _Traits> &__os) {
    return __os.put(__os.widen('\t'));
  }
}

#endif
