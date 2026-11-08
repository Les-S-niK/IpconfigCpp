#include "network_ifaces.hpp"

#include <net/if.h>

#include <cstdint>
#include <expected>
#include <iterator>

namespace sys_net_ifaces {

[[nodiscard]] auto SysNetIfaces::create() noexcept
    -> std::expected<SysNetIfaces, Errors> {
    struct if_nameindex* sys_net_ifaces_begin = if_nameindex();
    if (sys_net_ifaces_begin == nullptr) {
        return std::unexpected(Errors::CanNotGetSystemNetIfaces);
    }
    ifaces net_ifaces = ifacesToVector(sys_net_ifaces_begin);

    if_freenameindex(sys_net_ifaces_begin);

    return {SysNetIfaces{std::move(net_ifaces)}};
}

SysNetIfaces::SysNetIfaces(ifaces&& net_ifaces) noexcept
    : _net_ifaces(std::move(net_ifaces)) {}

auto SysNetIfaces::ifacesToVector(struct if_nameindex* sys_net_ifaces) noexcept
    -> ifaces {
    constexpr uint8_t ifaces_size_to_reserve = 5;

    ifaces ifaces_vector;
    ifaces_vector.reserve(ifaces_size_to_reserve);

    while (sys_net_ifaces->if_name != nullptr) {
        ifaces_vector.emplace_back(
            SysNetIface{.index = sys_net_ifaces->if_index,
                        .name = sys_net_ifaces->if_name});
        std::advance(sys_net_ifaces, 1);
    }

    return ifaces_vector;
}

[[nodiscard]] auto SysNetIfaces::getIfaces() const noexcept -> ifaces {
    return _net_ifaces;
}

[[nodiscard]] auto SysNetIfaces::getIfacesView() const noexcept
    -> const ifaces& {
    return _net_ifaces;
}

}  // namespace sys_net_ifaces
