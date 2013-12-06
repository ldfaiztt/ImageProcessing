#include "stdafx.h"
#include "CppUnitTest.h"

typedef unsigned char byte;
typedef unsigned long ULONG;

#include <atlimage.h>
#include "../ImageProcessing/MyImage.h"
#include "../ImageProcessing/DPCM_Encoder.h"
#include "../ImageProcessing/DPCM_Decoder.h"

#include "TimeRecorder.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testImageProcessing
{
	TEST_CLASS(testDPCM)
	{
	public:
		testDPCM()
		{
			Logger::WriteMessage(L"Inside the testDPCM Test. \n");
		}

		BEGIN_TEST_CLASS_ATTRIBUTE()
			//TEST_CLASS_ATTRIBUTE(L"Owner", L"Kern")
			TEST_CLASS_ATTRIBUTE(L"Descrioption", L"test DPCM")
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
			ByteVecotrPtr srcVec(new ByteVecotr());
			for (int i = 0; i < 100; i++)
			{
				srcVec->push_back(30 - i);
			}

			TimeRecorder tr;

			wostringstream wostr;
			wostr << L"DPCM code test with array " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			int compress_data_length = 6;
			DPCM_Encoder encoder(compress_data_length);
			BitVectorPtr tmp = encoder.transitData(srcVec);
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			DPCM_Decoder decoder(compress_data_length);
			ByteVecotrPtr dst = decoder.transitData(tmp);
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)tmp->size() / (double)(srcVec->size() * 8) <<L" (compressed / original)" << endl;
			Logger::WriteMessage(wostr.str().c_str());

			Assert::AreEqual(srcVec->size(), dst->size());
			for (int i = 0; i < srcVec->size(); i++)
			{
				Assert::AreEqual((*srcVec)[i], (*dst)[i]);
			}
		}

		TEST_METHOD(TestImageInput)
		{
			typeImgPtr img = typeImgPtr(new MyImage());
			img->Load(L"P1000528_Gray.jpg");
			Assert::IsFalse(img->IsNull());

			//int width = img->GetWidth();
			//int BytesPerPixel = (img->GetBPP() + 7) / 8;
			//int LineNum = width * BytesPerPixel;

			ByteVecotrPtr srcVec = img->toByteVector();

			TimeRecorder tr;

			wostringstream wostr;
			wostr << L"DPCM code test with img " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			int compress_data_length = 6;
			DPCM_Encoder encoder(compress_data_length);
			BitVectorPtr tmp = encoder.transitData(srcVec);
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			DPCM_Decoder decoder(compress_data_length);
			ByteVecotrPtr dst = decoder.transitData(tmp);
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)tmp->size() / (double)(srcVec->size() * 8) << L" (compressed / original)" << endl;
			Logger::WriteMessage(wostr.str().c_str());

			Assert::AreEqual(srcVec->size(), dst->size());

			for (int i = 0; i < srcVec->size(); i++)
			{
				Assert::AreEqual((*srcVec)[i], (*dst)[i]);
			}
		}


	};
}