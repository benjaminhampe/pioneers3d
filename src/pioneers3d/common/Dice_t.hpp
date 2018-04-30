#ifndef PIONEERS3D_COMMON_TYPES_DICE_HPP
#define PIONEERS3D_COMMON_TYPES_DICE_HPP

#include <common/AlphaSonic.hpp>

namespace pioneers3d {

struct Dice_t
{
    int32_t A;
    int32_t B;
    Dice_t() : A(1), B(1) { srand( static_cast< uint32_t >( time( nullptr ) ) ); }
    void randomizeA() { A = rand()%6 + 1; }
    void randomizeB() { B = rand()%6 + 1; }
    void randomize() { randomizeA(); randomizeB(); }
    int32_t sum() const { return A + B; }
    int32_t max() const { return std::max(A,B); }
    int32_t min() const { return std::min(A,B); }
};

} // end namespace pioneers3d

#endif // PIONEERS3D_COMMON_TYPES_DICE_HPP
