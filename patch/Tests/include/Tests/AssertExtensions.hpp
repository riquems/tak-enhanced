#pragma once
#include "Utils/json.hpp"

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {
            namespace AssertExt {
                template<typename T> static void AreStructurallyEqual(const T& expected, const T& actual, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL) {
                    nlohmann::json left = expected;
                    nlohmann::json right = actual;

                    return Assert::AreEqual(left.dump(), right.dump(), message, pLineInfo);
                }
            }
        }
    }
}