#include <bandit/bandit.h>

#include "dsm.h"
#include "error_code.h"

using namespace snowhouse;
using namespace bandit;

namespace tw = kitsune::twain;

go_bandit([] {
    describe("DSM state", [] {
        kitsune::twain::dsm dsm(nullptr);

        it("should start unloaded", [&] {
            AssertThat(dsm.state(), Equals(tw::dsm::state::disconnected));
        });

        it("should transition state", [&] {
            dsm.state(tw::dsm::state::ready);

            AssertThat(dsm.state(), Equals(tw::dsm::state::ready));
        });
    });

    describe("entry calling", [] {
        it("should throw an error_code if entry is invalid", [] {
            tw::dsm dsm(nullptr);
            std::error_code ec;

            dsm(nullptr, nullptr, tw::data_group::control, 0, 0, nullptr, ec);

            AssertThat(ec, Equals(tw::error_code::dsm_not_ready));
        });

        it("should call the provided entry", [] {
            int call_count = 0;
            auto entry = [&call_count] (tw::identity* origin, tw::identity* destination, uint32_t DG, uint16_t DAT, uint16_t MSG, TW_MEMREF data) -> uint16_t {
                ++call_count;
                return TWRC_SUCCESS;
            };
            tw::dsm dsm(entry);

            dsm(nullptr, nullptr, tw::data_group::control, 0, 0, nullptr);

            AssertThat(call_count, Equals(1));
        });
    });

    describe("connection opening", [] {
        it("should not transition state when connection is unsuccessful", [] {
            tw::dsm dsm(nullptr);
            std::error_code ec;

            dsm.open(nullptr, nullptr, ec);

            AssertThat(ec, Equals(tw::error_code::dsm_not_ready));
            AssertThat(dsm.state(), Equals(tw::dsm::state::disconnected));
        });

        it("should transition state when connection is successful", [] {
            tw::identity identity{};
            auto entry = [] (tw::identity* origin, tw::identity* destination, uint32_t DG, uint16_t DAT, uint16_t MSG, TW_MEMREF data) -> uint16_t {
                return TWRC_SUCCESS;
            };
            tw::dsm dsm(entry);

            dsm.open(&identity, nullptr);

            AssertThat(dsm.state(), Equals(tw::dsm::state::ready));
        });

        it("should request entrypoint when requesting a TWAIN 2.0+ connection", [] {
            tw::identity identity{};
            identity.SupportedGroups |= (uint32_t)DF_DSM2;
            bool called_entrypoint = false;
            auto entry = [&called_entrypoint] (tw::identity* origin, tw::identity* destination, uint32_t DG, uint16_t DAT, uint16_t MSG, TW_MEMREF data) -> uint16_t {
                if (DAT == DAT_ENTRYPOINT) {
                    called_entrypoint = true;
                }
                return TWRC_SUCCESS;
            };
            tw::dsm dsm(entry);

            dsm.open(&identity, nullptr);

            AssertThat(called_entrypoint, IsTrue());
        });
    });

    describe("memory handling", [] {
        it("should be able to allocate and deallocate shared memory", [] {
            tw::dsm dsm(nullptr);

            auto mem = dsm.alloc(128U);

            AssertThat(mem, Is().Not().Null());

            dsm.free(mem);
        });
    });
});

int main(int argc, char** argv) {
    bandit::run(argc, argv);
}
