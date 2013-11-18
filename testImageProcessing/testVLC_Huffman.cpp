#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testImageProcessing
{
	TEST_CLASS(testVLC_Huffman)
	{
	public:
		testVLC_Huffman()
		{
			Logger::WriteMessage(L"Inside the testVLC_Huffman Test. \n");
		}

		BEGIN_TEST_CLASS_ATTRIBUTE()
			//TEST_CLASS_ATTRIBUTE(L"Owner", L"Kern")
			TEST_CLASS_ATTRIBUTE(L"Descrioption", L"test VLC_Huffman")
			//TEST_CLASS_ATTRIBUTE(L"Priority", L"Critical")
		END_TEST_CLASS_ATTRIBUTE()

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage(L"Initializing the class. \n");
		}

		TEST_CLASS_CLEANUP(ClassFinalize)
		{
			Logger::WriteMessage(L"Finalizing the class. \n");
		}

		TEST_METHOD(TestArrayInput)
		{

		}


		TEST_METHOD(TestImgInput)
		{

		}
	};
}