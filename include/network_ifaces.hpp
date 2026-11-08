
#ifndef INCLUDE_INCLUDE_NETWORK_IFACES_HPP_
#define INCLUDE_INCLUDE_NETWORK_IFACES_HPP_

#include <net/if.h>

#include <array>
#include <cstdint>
#include <expected>
#include <string>
#include <vector>

namespace sys_net_ifaces {

class SysNetIface {
   public:
    static constexpr uint8_t praddr_size = 4;
    static constexpr uint8_t hwaddr_size = 6;
    using praddr = std::array<uint8_t, praddr_size>;
    using hwaddr = std::array<uint8_t, hwaddr_size>;

    constexpr SysNetIface(uint32_t index, std::string&& name) noexcept;

    [[nodiscard]] auto getIndex() const noexcept -> uint32_t;
    [[nodiscard]] auto getName() const noexcept -> std::string;
    [[nodiscard]] auto getPrAddr() const noexcept -> praddr;
    [[nodiscard]] auto getHwAddr() const noexcept -> hwaddr;
    [[nodiscard]] auto getFlags() const noexcept -> uint32_t;

   private:
    uint32_t _index;
    std::string _name;
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
