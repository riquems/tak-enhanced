#include "CppUnitTest.h"
#include "Tests/AssertExtensions.hpp"

#include "TAKEnhancedLibrary/Keys/Keys.hpp"
#include "TAKEnhancedLibrary/Keys/KeyComparator.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KeysEqualityTests
{
    TEST_CLASS(KeysEqualityTests)
    {
    public:
        TEST_METHOD(Shift)
        {
            Assert::IsTrue(KeyComparator::isLike(Keys::Shift, Keys::Shift));
            Assert::IsTrue(KeyComparator::isLike(Keys::Shift, Keys::RShift));
            Assert::IsTrue(KeyComparator::isLike(Keys::Shift, Keys::LShift));

            Assert::IsTrue(KeyComparator::isLike(Keys::Shift, Keys::Shift));
            Assert::IsTrue(KeyComparator::isLike(Keys::RShift, Keys::Shift));
            Assert::IsTrue(KeyComparator::isLike(Keys::LShift, Keys::Shift));
        }

        TEST_METHOD(Ctrl)
        {
            Assert::IsTrue(KeyComparator::isLike(Keys::Ctrl, Keys::Ctrl));
            Assert::IsTrue(KeyComparator::isLike(Keys::Ctrl, Keys::RCtrl));
            Assert::IsTrue(KeyComparator::isLike(Keys::Ctrl, Keys::LCtrl));

            Assert::IsTrue(KeyComparator::isLike(Keys::Ctrl, Keys::Ctrl));
            Assert::IsTrue(KeyComparator::isLike(Keys::RCtrl, Keys::Ctrl));
            Assert::IsTrue(KeyComparator::isLike(Keys::LCtrl, Keys::Ctrl));
        }

        TEST_METHOD(Alt)
        {
            Assert::IsTrue(KeyComparator::isLike(Keys::Alt, Keys::Alt));
            Assert::IsTrue(KeyComparator::isLike(Keys::Alt, Keys::RAlt));
            Assert::IsTrue(KeyComparator::isLike(Keys::Alt, Keys::LAlt));

            Assert::IsTrue(KeyComparator::isLike(Keys::Alt, Keys::Alt));
            Assert::IsTrue(KeyComparator::isLike(Keys::RAlt, Keys::Alt));
            Assert::IsTrue(KeyComparator::isLike(Keys::LAlt, Keys::Alt));
        }
    };
}
