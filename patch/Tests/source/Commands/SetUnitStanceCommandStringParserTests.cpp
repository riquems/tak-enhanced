#include "CppUnitTest.h"
#include "Tests/AssertExtensions.hpp"

#include "TAKEnhancedLibrary/Commands/SetUnitStance/SetUnitStanceCommand.hpp"
#include "TAKEnhancedLibrary/Commands/SetUnitStance/SetUnitStanceCommandStringParser.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SetUnitStanceCommandStringParserTests
{
    TEST_CLASS(SetUnitStanceCommandStringParserTests)
    {
    public:
        TEST_METHOD(ToString)
        {
            auto command = SetUnitStanceCommand(
                SetUnitStanceCommandParams{
                   .stance = UnitStance::Defensive
                }
            );

            SetUnitStanceCommandStringParser parser;

            auto result = parser.toString(command);

            Assert::AreEqual(std::string("SetUnitStance Defensive"), result);
        }

        TEST_METHOD(FromString)
        {
            std::string commandStr = "SetUnitStance Offensive";

            SetUnitStanceCommandStringParser parser;

            auto result = parser.fromString(commandStr);

            AssertExt::AreStructurallyEqual(SetUnitStanceCommand(
                SetUnitStanceCommandParams {
                   .stance = UnitStance::Offensive
                }
            ), *result);
        }
    };
}
