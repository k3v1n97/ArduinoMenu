/* -*- C++ -*- */
#pragma once

#include "api.h"

//aux class for monometric text measure
template<int szX=1,int szY=1>
struct TextMeasure {
  template<typename O>
  struct Part:O {
    template<typename T>
    static inline Idx measure(T o) {
      #ifdef ARDUINO
        return String(o).length();
      #else
        return _str(o);
      #endif
    }
    inline static constexpr int maxCharWidth() {return 1;}
    inline static constexpr int maxCharHeight() {return 1;}
    int textWidth(const char*s) const {return measure(s);}
    protected:
      #ifndef ARDUINO
      static inline Idx _str(const char*o){return std::string(o).length();}
      template<typename T>
      static inline Idx _str(T i){return std::string(std::to_string(i)).length();}
      #endif
  };
  template<typename O> using Open=Part<O>;
};

template<typename O>
struct PartialDraw:O {
  inline static constexpr bool partialDraw() {return true;}
};

template<typename Dev,Dev& dev>
struct StreamOut {
  template<typename O>
  struct Part:O {
    using This=StreamOut<Dev,dev>::Part<O>;
    inline static void nl() {dev<<endl;}
    template<typename T> inline static void raw(T o) {dev<<o;}
  };
};

template<typename Dev,Dev& dev,typename O>
struct StreamIn:O {
  template<typename Nav>
  inline static bool cmd(Nav& nav) {
    char c;
    dev>>c;
    switch(c) {
      case '+': return nav.cmd(Cmd::Up);
      case '-': return nav.cmd(Cmd::Down);
      case '*': return nav.cmd(Cmd::Enter);
      case '/': return nav.cmd(Cmd::Esc);
      default:return false;
    }
  }
};

struct None:Nil {
  template<bool invY=false>
  inline static constexpr Cmd cmd() {return Cmd::None;}
};

template<Expr... O>
struct StaticMenuOut:Chain<O...,Void>::template To<Obj<StaticMenuOut<O...>>> {
  using Base=typename Chain<O...,Void>::template To<Obj<StaticMenuOut<O...>>>;
  using This=StaticMenuOut<O...>;
  using Base::Base;
};
