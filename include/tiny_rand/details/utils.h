//
// Created by Duval Quentin on 17/04/2017.
//

#ifndef TINYRANDOM_UTILS_H
#define TINYRANDOM_UTILS_H

namespace tiny_rand
{
template<typename Output>
struct to_object
{
   template<typename... Args>
   Output operator()(Args&& ... args) const
   {
      return Output { std::forward<Args&&>(args)...};
   };
};
}

#endif //TINYRANDOM_UTILS_H
