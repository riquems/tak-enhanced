#include "CppUnitTest.h"
#include "Tests/AssertExtensions.hpp"

#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommand.hpp"
#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommandStringParser.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SelectBuildingCommandStringParserTests
{
    TEST_CLASS(SelectBuildingCommandStringParserTests)
    {
    public:
         TEST_METHOD(ToString)
         {
             auto command = SelectBuildingCommand(
                 SelectBuildingCommandParams {
                    .building = 1
                 }
             );

             SelectBuildingCommandStringParser parser;

             auto result = parser.toString(command);

             Assert::AreEqual(std::string("SelectBuilding 1"), result);
         }

         TEST_METHOD(FromString)
         {
             std::string commandStr = "SelectBuilding 1";

             SelectBuildingCommandStringParser parser;

             auto result = parser.fromString(commandStr);

             AssertExt::AreStructurallyEqual(SelectBuildingCommand(
                 SelectBuildingCommandParams {
                    .building = 1
                 }
             ), *result);
         }
    };
}
