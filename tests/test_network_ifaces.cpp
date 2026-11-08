
#include <gtest/gtest.h>
#include <net/if.h>

#include <algorithm>
#include <expected>
#include <string_view>

#include "network_ifaces.hpp"

using sys_net_ifaces::SysNetIface;
using sys_net_ifaces::SysNetIfaces;

namespace {
namespace test_utils {
auto isLoopbackIfaceInIfaces(SysNetIfaces::ifaces&& ifaces) -> bool {
    constexpr std::string_view loopback_iface_name = "lo";
    return std::ranges::any_of(std::move(ifaces),
                               [&](const SysNetIface& iface) -> bool {
                                   return iface.name == loopback_iface_name;
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
}  // namespace
