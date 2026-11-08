
#ifndef INCLUDE_INCLUDE_NETWORK_IFACES_HPP_
#define INCLUDE_INCLUDE_NETWORK_IFACES_HPP_

#include <net/if.h>

#include <cstdint>
#include <expected>
#include <string>
#include <vector>

namespace sys_net_ifaces {

struct SysNetIface {
    uint32_t index;
    std::string name;
};

class SysNetIfaces {
   public:
    using ifaces = std::vector<SysNetIface>;
    enum class Errors : uint8_t { CanNotGetSystemNetIfaces };

    [[nodiscard]] static auto create() noexcept
        -> std::expected<SysNetIfaces, Errors>;
    [[nodiscard]] auto getIfaces() const noexcept -> ifaces;
    [[nodiscard]] auto getIfacesView() const noexcept -> const ifaces&;

   private:
    ifaces _net_ifaces;

    explicit SysNetIfaces(ifaces&& net_ifaces) noexcept;

    static auto ifacesToVector(struct if_nameindex* sys_net_ifaces) noexcept
        -> ifaces;
};

}  // namespace sys_net_ifaces

#endif  // INCLUDE_INCLUDE_NETWORK_IFACES_HPP_
