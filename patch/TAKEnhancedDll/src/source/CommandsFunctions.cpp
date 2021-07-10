#include "../CommandsFunctions.h"

void selectBuilding(std::vector<std::string> params)
{
    if (!gameWrapper->isBuildMenuOpen())
        return;

    if (params.size() != 1) {
        logger.log("The number of given parameters is not supported by this command.\n \
                    Command: %s                                                     \n \
                    Number of supported params: 1                                   \n \
                    Number of given params: %d", "Select Building", params.size());
        return;
    }

    int buildingId = std::stoi(params[0]);
    
    gameWrapper->selectBuilding(buildingId);
}

void attack(std::vector<std::string> params) {}
