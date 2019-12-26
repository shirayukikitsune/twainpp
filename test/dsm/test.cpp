#include <bandit/bandit.h>

#include "dsm.h"
#include "error_code.h"

using namespace snowhouse;
using namespace bandit;

go_bandit([] {
    describe("DSM state", [] {
        kitsune::twain::dsm dsm(nullptr);

        it("should start unloaded", [&] {
            AssertThat(dsm.state(), Equals(kitsune::twain::dsm::state::disconnected));
        });

        it("should transition state", [&] {
            dsm.state(kitsune::twain::dsm::state::ready);

            AssertThat(dsm.state(), Equals(kitsune::twain::dsm::state::ready));
        });
    });

    describe("entry calling", [] {
        it("should throw an error_code if entry is invalid", [] {
            kitsune::twain::dsm dsm(nullptr);
            std::error_code ec;

            dsm(nullptr, nullptr, 0, 0, 0, nullptr, ec);

            AssertThat(ec, Equals(kitsune::twain::error_code::dsm_not_ready));
        });

        it("should call the provided entry", [] {
            int call_count = 0;
            auto entry = [&call_count] (pTW_IDENTITY origin, pTW_IDENTITY destination, TW_UINT32 DG, TW_UINT16 DAT, TW_UINT16 MSG, TW_MEMREF data) -> TW_UINT16 {
                ++call_count;
                return TWRC_SUCCESS;
            };
            kitsune::twain::dsm dsm(entry);

            dsm(nullptr, nullptr, 0, 0, 0, nullptr);

            AssertThat(call_count, Equals(1));
        });
    });

    describe("memory handling", [] {

    });
});

int main(int argc, char** argv) {
    bandit::run(argc, argv);
}
