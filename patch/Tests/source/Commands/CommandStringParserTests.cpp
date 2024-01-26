#include "CppUnitTest.h"

#include "Tests/AssertExtensions.hpp"
#include "dky/std.hpp"

#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommand.hpp"
#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/CommandStringParser.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandStringParserTests
{
    TEST_CLASS(CommandStringParserTests)
    {
    public:
        TEST_METHOD(CommandParts)
        {
            auto parts = ICommandStringParser::getCommandParts("SelectBuilding 1");

            std::vector<std::string> expected = { "SelectBuilding", "1" };

            Assert::IsTrue(
                parts == expected,
                std::wstring(
                    std::wstring(L"Expected: ") + dky::vector::to_wstring(expected) +
                    L" Result: " + dky::vector::to_wstring(parts)
                ).c_str()
            );
        }

        TEST_METHOD(ToString)
        {
            auto command = SelectBuildingCommand(
                SelectBuildingCommandParams {
                    .building = 1
                }
            );

            CommandStringParser parser { CommandStringParsers() };

            auto result = parser.toString(command);

            Assert::AreEqual(std::string("SelectBuilding 1"), result);
        }

        TEST_METHOD(FromString)
        {
            std::string commandStr = "RotateBuilding Clockwise";

            CommandStringParser parser{ CommandStringParsers() };

            auto result = parser.fromString(commandStr);

            AssertExt::AreStructurallyEqual(RotateBuildingCommand(
                RotateBuildingCommandParams {
                   .orientation = RotateOrientation::Clockwise
                }
            ), *dynamic_cast<RotateBuildingCommand*>(result.get()));
        }
    };
}
