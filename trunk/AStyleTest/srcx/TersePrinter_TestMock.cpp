// TersePrinter test program.
// The output must be inspected visually.


#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "TersePrinter.h"
// for gmock macros
using namespace testing;

//----------------------------------------------------------------------------
//
//
//----------------------------------------------------------------------------

struct TestClass
{
	// mockedMethod call must be virtual so that the derived method is called.
	virtual int mockedMethod0()
	{
		return 0;
	}
	// mockedMethod call must be virtual so that the derived method is called.
	virtual int mockedMethod1(int param)
	{
		return param;
	}
	void mock0NeverCalled()
	{
		// mocked method is never called
	}
	void mock0CalledOnce()
	{
		mockedMethod0();
	}
	void mock0ThenMock1Called()
	{
		mockedMethod0();
		mockedMethod1(1);
	}

};


struct MockTestClass : public TestClass
{
	MOCK_METHOD0(mockedMethod0, int());
	MOCK_METHOD1(mockedMethod1, int(int));
};

TEST(MockTest, Mock0CalledOnce_OK)
{
	// Mocked method called correctly.
	MockTestClass mtc;
	EXPECT_CALL(mtc, mockedMethod0());
	mtc.mock0CalledOnce();
}

TEST(MockTest, Mock0ThenMock1Called_OK)
{
	// Mocked method 0 called then mocked method 1.
	MockTestClass mtc;
	Expectation mock0called = EXPECT_CALL(mtc, mockedMethod0());
	EXPECT_CALL(mtc, mockedMethod1(_))
	.After(mock0called);
	mtc.mock0ThenMock1Called();
}

TEST(MockTest, Mock0NeverCalled_ShouldBeOnce)
{
	// Mocked method 0 never called.
	MockTestClass mtc;
	EXPECT_CALL(mtc, mockedMethod0());
	mtc.mock0NeverCalled();
}

TEST(MockTest, Mock0CalledOnce_ShouldBeTwice)
{
	// Mocked method 0 called once instead of twice.
	MockTestClass mtc;
	EXPECT_CALL(mtc, mockedMethod0())
	.Times(2);
	mtc.mock0CalledOnce();
}

TEST(MockTest, Mock0CalledBeforeMock1_ExpectedReverse)
{
	// Mocked method 0 called before mocked method 1 instead of after.
	MockTestClass mtc;
	Expectation mock1called = EXPECT_CALL(mtc, mockedMethod1(_));
	EXPECT_CALL(mtc, mockedMethod0())
	.After(mock1called);
	mtc.mock0ThenMock1Called();
	// This prevents an additional error message/
	mtc.mock0CalledOnce();
}

TEST(MockTest, MockMethodNotCalled)
{
	// NOTE: This has the same result as MockMethodCalledWhenNotExpected()
	//       except this also has an error message displayed afterward.
	// The test has an EXPECT_CALL with a mocked method that isn't called.
	// This reults in an "uninteresting mock function call" message.
	// This message is displayed by goglemock and cannot be overridden.
	// A test header will not be displayed before the message.
	// The message should not be displayed when the test is debugged.
	MockTestClass mtc;
	EXPECT_CALL(mtc, mockedMethod1(_));
	mtc.mock0CalledOnce();
}

TEST(MockTest, MockMethodCalledWhenNotExpected)
{
	// NOTE: This has the same result as MockMethodNotCalled().
	//       except this has NO error message displayed.
	// The test has NO EXPECT_CALL when a mocked method is called.
	// This reults in an "uninteresting mock function call" message.
	// This message is displayed by goglemock and cannot be overridden.
	// A test header will not be displayed before the message.
	// The message should not be displayed when the test is debugged.
	MockTestClass mtc;
	mtc.mock0CalledOnce();
}


// Change astyle to indent the ".WillOnce" statements.
// Change the options on the test program.
