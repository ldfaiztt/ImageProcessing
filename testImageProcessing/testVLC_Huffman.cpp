#include "stdafx.h"
#include "CppUnitTest.h"

typedef unsigned char byte;

#include "../ImageProcessing/MyBinaryTree.h"
#include "../ImageProcessing/HuffmanTreeBuilder.h"
#include "../ImageProcessing/VLC_HuffmanEncoder.h"
#include "../ImageProcessing/VLC_HuffmanDecoder.h"

#include "TimeRecorder.h"

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
			string strSrc = "AATELDALFJADSEWORUNFASDLHFSSCBWERQW";
			ByteVecotrPtr srcVec(new ByteVecotr());
			for each (char c in strSrc)
			{
				srcVec->push_back(c);
			}

			HuffmanTreeBuilder treeBuilder;
			unordered_map<stKey, shared_ptr<typeTreeNode>> leafMap;

			TimeRecorder tr;

			wostringstream wostr;
			wostr << L"huffman code test with array " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			shared_ptr<MyBinaryTree<stNodeData>> tree = treeBuilder.BuildTrees(srcVec, leafMap);
			VLC_HuffmanEncoder encoder(*tree, leafMap);
			BitVectorPtr tmp = encoder.transitData(srcVec);
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			VLC_HuffmanDecoder decoder(tree);
			ByteVecotrPtr dst = decoder.transitData(tmp);
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)tmp->size() / (double)(srcVec->size() * 8) << endl;
			Logger::WriteMessage(wostr.str().c_str());

			Assert::AreEqual(srcVec->size(), dst->size());

			for (int i = 0; i < srcVec->size(); i++)
			{
				Assert::AreEqual((*srcVec)[i], (*dst)[i]);
			}
		}


		TEST_METHOD(TestImgInput)
		{
			typeImgPtr img = typeImgPtr(new MyImage());
			img->Load(L"P1000528_Gray.jpg");
			Assert::IsFalse(img->IsNull());

			int width = img->GetWidth();
			int BytesPerPixel = (img->GetBPP() + 7) / 8;
			int LineNum = width * BytesPerPixel;

			ByteVecotrPtr srcVec = img->toByteVector();

			HuffmanTreeBuilder treeBuilder;
			unordered_map<stKey, shared_ptr<typeTreeNode>> leafMap;
			
			TimeRecorder tr;

			wostringstream wostr;
			wostr << L"huffman code test with img " << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** encoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			shared_ptr<MyBinaryTree<stNodeData>> tree = treeBuilder.BuildTrees(img, leafMap);
			VLC_HuffmanEncoder encoder(*tree, leafMap);
			BitVectorPtr tmp = encoder.transitData(srcVec);
			tr.end();

			wostr.str(L"");
			wostr << L"encoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			/*********************************************************************************/
			/**** decoder                                                                  ***/
			/*********************************************************************************/
			tr.start();
			VLC_HuffmanDecoder decoder(tree);
			ByteVecotrPtr dst = decoder.transitData(tmp);
			tr.end();

			wostr.str(L"");
			wostr << L"decoder time : " << tr.getPeriod() << " " << tr.getPeriodUnit() << endl;
			Logger::WriteMessage(wostr.str().c_str());

			wostr.str(L"");
			wostr << L"compression ratio : " << (double)tmp->size() / (double)(srcVec->size() * 8) << endl;
			Logger::WriteMessage(wostr.str().c_str());

			Assert::AreEqual(srcVec->size(), dst->size());

			for (int i = 0; i < srcVec->size(); i++)
			{
				Assert::AreEqual((*srcVec)[i], (*dst)[i]);
			}
		}
	};
}