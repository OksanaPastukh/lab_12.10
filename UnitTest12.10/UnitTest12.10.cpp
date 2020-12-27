#include "pch.h"
#include "CppUnitTest.h"
#include "../Project12.10/project12.10.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1210
{
	TEST_CLASS(UnitTest1210)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int result;
			Node* node1 = new Node;
			node1->info = 1;
			Node* node2 = new Node;
			node2->info = 2;
			Node* node3 = new Node;
			node3->info = 3;
			Node* node4 = new Node;
			node4->info = 4;
			Node* node5 = new Node;
			node5->info = 5;
			node1->left = node2;
			node1->right = node5;
			node2->left = node3;
			node2->right = node4;
			node3->left = NULL;
			node3->right = NULL;
			node4->left = NULL;
			node4->right = NULL;
			node5->left = NULL;
			node5->right = NULL;
			result = Count(node1);
			Assert::AreEqual(result, 5);
		}
	};
}
