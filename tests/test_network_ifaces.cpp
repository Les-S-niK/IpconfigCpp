
#include <gtest/gtest.h>
#include <net/if.h>

#include <algorithm>
#include <array>
#include <expected>
#include <string_view>

#include "network_ifaces.hpp"

using sys_net_ifaces::SysNetIface;
using sys_net_ifaces::SysNetIfaces;

namespace {
constexpr std::string_view loopback_iface_name = "lo";
constexpr SysNetIface::praddr loopback_praddr = {127, 0, 0, 1};
constexpr SysNetIface::hwaddr loopback_hwaddr = {0xFF, 0xFF, 0xFF,
                                                 0xFF, 0xFF, 0xFF};

namespace test_utils {

auto isLoopbackIfaceInIfaces(SysNetIfaces::ifaces&& ifaces) -> bool {
    return std::ranges::any_of(
        std::move(ifaces), [&](const SysNetIface& iface) -> bool {
            return iface.getName() == loopback_iface_name;
        });
}
}  // namespace test_utils

class SysNetIfacesFixture : public testing::Test {
   protected:
    using NetIfaces = std::expected<SysNetIfaces, SysNetIfaces::Errors>;

    NetIfaces net_ifaces{
        std::unexpected(NetIfaces::error_type::CanNotGetSystemNetIfaces)};

    void SetUp() override { net_ifaces = SysNetIfaces::create(); }
    void TearDown() override {}
};

TEST_F(SysNetIfacesFixture, createSysNetIfacesReturnClassInstance) {
    ASSERT_TRUE(net_ifaces.has_value());
    ASSERT_FALSE(net_ifaces->getIfaces().empty());
}

TEST_F(SysNetIfacesFixture, getIfacesContainsLoopbackInterface) {
    SysNetIfaces::ifaces ifaces = net_ifaces->getIfaces();
    ASSERT_TRUE(test_utils::isLoopbackIfaceInIfaces(std::move(ifaces)));
}

TEST_F(SysNetIfacesFixture, getPrAddLoopbackEqualsLoPrAddr) {
    SysNetIfaces::ifaces ifaces = net_ifaces->getIfaces();
    for (const auto& iface : ifaces) {
        if (iface.getName() == loopback_iface_name) {
            ASSERT_EQ(iface.getPrAddr(), loopback_praddr);
            GTEST_SUCCEED();
        }
    }
    FAIL();
}

TEST_F(SysNetIfacesFixture, getHwAddLoopbackEqualsLoHwAddr) {
    SysNetIfaces::ifaces ifaces = net_ifaces->getIfaces();
    for (const auto& iface : ifaces) {
        if (iface.getName() == loopback_iface_name) {
            ASSERT_EQ(iface.getHwAddr(), loopback_hwaddr);
            GTEST_SUCCEED();
        }
    }
    FAIL();
}
}  // namespace
