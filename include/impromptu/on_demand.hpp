#ifndef IMPROMPTU_ON_DEMAND_HPP
#define IMPROMPTU_ON_DEMAND_HPP

#include <cstddef>
#include <functional>
#include <optional>

namespace impromptu {
template <typename T> class OnDemandValue : std::optional<T> {
  public:
    using Creator = std::function<T()>;

  private:
    Creator _creator;
    bool _set;

  public:
    OnDemandValue(Creator creator) : _creator(creator), _set(false) {}

    const T &get() {
        if (!_set)
            std::optional<T>::operator=(_creator());
        return this->value();
    }
};
} // namespace impromptu

#endif
