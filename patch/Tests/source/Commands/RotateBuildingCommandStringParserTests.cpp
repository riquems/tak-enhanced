#include "CppUnitTest.h"
#include "Tests/AssertExtensions.hpp"

#include "TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommand.hpp"
#include "TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommandStringParser.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RotateBuildingCommandStringParserTests
{
    TEST_CLASS(RotateBuildingCommandStringParserTests)
    {
    public:
        TEST_METHOD(ToString)
        {
            auto command = RotateBuildingCommand(
                RotateBuildingCommandParams{
                   .orientation = RotateOrientation::Clockwise
                }
            );

            RotateBuildingCommandStringParser parser;

            auto result = parser.toString(command);

            Assert::AreEqual(std::string("RotateBuilding Clockwise"), result);
        }

        TEST_METHOD(FromString)
        {
            std::string commandStr = "RotateBuilding CounterClockwise";

            RotateBuildingCommandStringParser parser;

            auto result = parser.fromString(commandStr);

            AssertExt::AreStructurallyEqual(RotateBuildingCommand(
                RotateBuildingCommandParams {
                   .orientation = RotateOrientation::CounterClockwise
                }
            ), *result);
        }
    };
}
