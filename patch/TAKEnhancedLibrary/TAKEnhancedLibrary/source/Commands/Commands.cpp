#include "TAKEnhancedLibrary/Commands/Commands.hpp"
#include "TAKEnhancedLibrary/Units/Units.hpp"
#include "TAKEnhancedLibrary/Match/Match.hpp"
#include "TAKCore/Commands.h"
#include "TAKCore/Functions/Functions.h"

using namespace TAKEnhancedLibrary;

void TAKEnhancedLibrary::ExecuteCommand(const std::string& command) {
    bool isTargetCommand = dky::contains(
        TAKCore::Commands::targetCommands,
        [&](const std::string& cmd) {
            return cmd == command;
        }
    );

    if (isTargetCommand) {
        if (!TAKEnhancedLibrary::MatchIsRunning() || TAKEnhancedLibrary::GetMouseHoveredUnit() == nullptr) {
            //logger->debug("Command is a target command and no unit is targetted at the moment. Skipping.");
            return;
        }
    }

    //logger->debug("Executing command %s", command.c_str());

    if (command == TAKCore::Commands::DoNothing)
        return;

    TAKCore::Functions::executeCommand(command.c_str(), false);
}
