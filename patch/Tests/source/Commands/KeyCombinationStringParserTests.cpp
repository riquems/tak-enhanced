#include "CppUnitTest.h"
#include "Tests/AssertExtensions.hpp"

#include "TAKEnhancedLibrary/Keys/Keys.hpp"
#include "TAKEnhancedLibrary/Keys/KeyCombination.hpp"
#include "TAKEnhancedLibrary/Keys/KeyCombinationStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommand.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KeyCombinationTests
{
    TEST_CLASS(KeyCombinationTests)
    {
    public:
        TEST_METHOD(ToString)
        {
            auto keyCombination = KeyCombination { Keys::Shift, Keys::Return };

            KeyCombinationStringParser parser(Keys{});

            auto result = parser.toString(keyCombination);

            Assert::AreEqual(std::string("SHIFT + Return"), result);
        }

        TEST_METHOD(FromString)
        {
            std::string keyCombinationStr = "SHIFT + Return";

            KeyCombinationStringParser parser(Keys{});

            auto result = parser.fromString(keyCombinationStr);

            Assert::IsTrue(KeyCombination { Keys::Shift, Keys::Return } == result);
        }
    };
}
