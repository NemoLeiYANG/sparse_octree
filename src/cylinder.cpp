#include "cylinder.h"

namespace sot {

  cylinder build_at_position(const vec_3 position, const cylinder c) {
    return cylinder( position, c.height(), c.diameter() );
  }

}
