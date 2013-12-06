#include "stdafx.h"
#include "CppUnitTest.h"

typedef unsigned char byte;

#include <atlimage.h>
#include "../ImageProcessing/RLC_BytesDecoder.h"
#include "../ImageProcessing/RLC_BytesEncoder.h"

#include "TimeRecorder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testImageProcessing
{		
	//BEGIN_TEST_MODULE_ATTRIBUTE()
	//	TEST_MODULE_ATTRIBUTE(L"Project", L"DemoBusiness")
	//	TEST_MODULE_ATTRIBUTE(L"Owner", L"Kern")
	//	TEST_MODULE_ATTRIBUTE(L"Date", L"11/13/2013")
	//END_TEST_MODULE_ATTRIBUTE()

	TEST_MODULE_INITIALIZE(ModuleStartup)
	{
		Logger::WriteMessage(L"The test is starting.... \n");
	}

	TEST_MODULE_CLEANUP(ModuleFinalize)
	{
		Logger::WriteMessage(L"Finalizing the test. \n");
	}

	TEST_CLASS(testRLC_GrayScale)
	{
	public:
		testRLC_GrayScale()
		{
			Logger::WriteMessage(L"Inside the testRLC_GrayScale Test. \n");
		}

		BEGIN_TEST_CLASS_ATTRIBUTE()
			//TEST_CLASS_ATTRIBUTE(L"Owner", L"Kern")
			TEST_CLASS_ATTRIBUTE(L"Descrioption", L"test RLC_GrayScale")
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

		//TEST_METHOD_INITIALIZE(InitRLCGrayScale)
		//{
		//	img = typeImgPtr(new MyImage());
		//	img->Load(L"P1000528_Gray.jpg");
		//}

		//BEGIN_TEST_METHOD_ATTRIBUTE(Encoder)
		//	TEST_OWNER(L"Kern")
		//	TEST_DESCRIPTION(L"Make sure that data is initialized, as data is private this testclass must be friend to our class")
		//END_TEST_METHOD_ATTRIBUTE()
		
		TEST_METHOD(IMG_WithoutLineTag)
		{
			typeImgPtr img = typeImgPtr(new MyImage());
			img->Load(L"P1000528_Gray.jpg");
			Assert::IsFalse(img->IsNull());
			
			ByteVecotrPtr src = img->toByteVector();

			RLC_BytesEncoder rlcE(0,0xff);
			RLC_BytesDecoder rlcD(0,0xff);
			
			TimeRecorder tr;
			wostringstream wostr;
			wostr << L"test RLC GrayScale without line tag using img " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			ByteVecotrPtr tmp = rlcE.transitData(src);
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			ByteVecotrPtr dst = rlcD.transitData(tmp);
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)tmp->size() / (double)src->size() << L" (compressed / original)" << endl;
			Logger::WriteMessage(wostr.str().c_str());

			Assert::AreEqual(src->size(), dst->size());

			for (int i = 0; i < src->size(); i++ )
			{
				Assert::AreEqual(src->at(i), dst->at(i));
			}
		}

		TEST_METHOD(IMG_WithLineTag)
		{
			typeImgPtr img = typeImgPtr(new MyImage());
			img->Load(L"P1000528_Gray.jpg");
			Assert::IsFalse(img->IsNull());

			int width = img->GetWidth();
			int BytesPerPixel = (img->GetBPP() + 7) / 8;
			int LineNum = width * BytesPerPixel;

			ByteVecotrPtr src = img->toByteVector();

			RLC_BytesEncoder rlcE(LineNum, 0xff);
			RLC_BytesDecoder rlcD(LineNum, 0xff);

			TimeRecorder tr;
			wostringstream wostr;
			wostr << L"test RLC GrayScale with line tag using img " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			ByteVecotrPtr tmp = rlcE.transitData(src);
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			ByteVecotrPtr dst = rlcD.transitData(tmp);
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)tmp->size() / (double)src->size() << L" (compressed / original)" << endl;
			Logger::WriteMessage(wostr.str().c_str());

			Assert::AreEqual(src->size(), dst->size());

			for (int i = 0; i < src->size(); i++)
			{
				Assert::AreEqual(src->at(i), dst->at(i));
			}
		}

		TEST_METHOD(Array_WithoutLineTag)
		{
			ByteVecotrPtr src(new ByteVecotr());
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					src->push_back(i);
				}
			}

			RLC_BytesEncoder rlcE(0,0xff);
			RLC_BytesDecoder rlcD(0,0xff);

			TimeRecorder tr;
			wostringstream wostr;
			wostr << L"test RLC GrayScale without line tag using array " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			ByteVecotrPtr tmp = rlcE.transitData(src);
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			ByteVecotrPtr dst = rlcD.transitData(tmp);
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)tmp->size() / (double)src->size() << L" (compressed / original)" << endl;
			Logger::WriteMessage(wostr.str().c_str());

			Assert::AreEqual(src->size(), dst->size());

			for (int i = 0; i < src->size(); i++)
			{
				Assert::AreEqual(src->at(i), dst->at(i));
			}
		}

		TEST_METHOD(Array_WithLienTag)
		{
			ByteVecotrPtr src(new ByteVecotr());
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					src->push_back(i);
				}
			}

			RLC_BytesEncoder rlcE(5, 0xff);
			RLC_BytesDecoder rlcD(5, 0xff);

			TimeRecorder tr;
			wostringstream wostr;
			wostr << L"test RLC GrayScale with line tag using array " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			ByteVecotrPtr tmp = rlcE.transitData(src);
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			ByteVecotrPtr dst = rlcD.transitData(tmp);
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)tmp->size() / (double)src->size() << L" (compressed / original)" << endl;
			Logger::WriteMessage(wostr.str().c_str());

			Assert::AreEqual(src->size(), dst->size());

			for (int i = 0; i < src->size(); i++)
			{
				Assert::AreEqual(src->at(i), dst->at(i));
			}
		}
	};
}