#include "stdafx.h"
#include "CppUnitTest.h"

typedef unsigned char byte;
typedef unsigned long ULONG;

#include <atlimage.h>
#include "../ImageProcessing/MyImage.h"
#include "../ImageProcessing/RLC_BitPlanesEncoder.h"
#include "../ImageProcessing/RLC_BitPlanesDecoder.h"
#include "../ImageProcessing/BitPlaneBuilder.h"

#include "TimeRecorder.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testImageProcessing
{
	TEST_CLASS(testRLC_BitPlane)
	{
	public:
		testRLC_BitPlane()
		{
			Logger::WriteMessage(L"Inside the testBitPlane Test. \n");
		}

		BEGIN_TEST_CLASS_ATTRIBUTE()
			//TEST_CLASS_ATTRIBUTE(L"Owner", L"Kern")
			TEST_CLASS_ATTRIBUTE(L"Descrioption", L"test BitPlane")
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
			for (int i = 0; i < 307200; i++)
			{
				srcVec->push_back(rand() % 256);
			}

			vector<BitVectorPtr> bitplanes;
			vector<ByteVecotrPtr> tmps;
			vector<BitVectorPtr> dstBitPlanes;
			int countTmp = 0;
			BitPlaneBuilder bpB;
			int line_num = bpB.build(srcVec, bitplanes);
			bool preBit = false;

			TimeRecorder tr;

			wostringstream wostr;
			wostr << L"Bit Plane code test with array " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			for each (BitVectorPtr bitplane in bitplanes)
			{
				RLC_BitPlanesEncoder encoder(line_num, preBit);
				ByteVecotrPtr tmp = encoder.transitData(bitplane);

				tmps.push_back(tmp);
				countTmp += tmp->size();
			}
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			for each (ByteVecotrPtr bitplane in tmps)
			{
				RLC_BitPlanesDecoder decoder(line_num, preBit);
				BitVectorPtr bitv = decoder.transitData(bitplane);

				dstBitPlanes.push_back(bitv);
			}			
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)countTmp / srcVec->size() << L" (compressed / original)" << endl;
			Logger::WriteMessage(wostr.str().c_str());

			ByteVecotrPtr dst = bpB.reconstruct(dstBitPlanes);
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

			ByteVecotrPtr srcVec = img->toByteVector();
			vector<BitVectorPtr> bitplanes;
			vector<ByteVecotrPtr> tmps;
			vector<BitVectorPtr> dstBitPlanes;
			int countTmp = 0;
			BitPlaneBuilder bpB;
			int line_num = bpB.build(img, bitplanes);
			bool preBit = false;

			TimeRecorder tr;

			wostringstream wostr;
			wostr << L"Bit Plane code test with Image " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			for each (BitVectorPtr bitplane in bitplanes)
			{
				RLC_BitPlanesEncoder encoder(line_num, preBit);
				ByteVecotrPtr tmp = encoder.transitData(bitplane);

				tmps.push_back(tmp);
				countTmp += tmp->size();
			}
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			for each (ByteVecotrPtr bitplane in tmps)
			{
				RLC_BitPlanesDecoder decoder(line_num, preBit);
				BitVectorPtr bitv = decoder.transitData(bitplane);

				dstBitPlanes.push_back(bitv);
			}
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)countTmp / srcVec->size() << L" (compressed / original)" << endl;
			Logger::WriteMessage(wostr.str().c_str());

			ByteVecotrPtr dst = bpB.reconstruct(dstBitPlanes);
			Assert::AreEqual(srcVec->size(), dst->size());
			for (int i = 0; i < srcVec->size(); i++)
			{
				Assert::AreEqual((*srcVec)[i], (*dst)[i]);
			}
		}
	};
}