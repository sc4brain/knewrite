
#include "CObjectCommunicator.h"

LLManager::LLManager(void)
{
	Head = Tail = NULL;
	OutputNode = NULL;
}

LLManager::~LLManager(void)
{
	if (OutputNode != NULL) {
		delete OutputNode;
	}
}

LLNode *LLManager::queue(char *in_data, int in_byte)
{
	LLNode *NodeTemp = new LLNode;
	NodeTemp->data = new char[in_byte];
	NodeTemp->byte = in_byte;
	NodeTemp->next = Tail;
	if (Head == NULL) {
		Head = NodeTemp;
	} else {
		NodeTemp->next->back = NodeTemp;
	}
	for (int i = 0; i < in_byte; i++) {
		NodeTemp->data[i] = (char)in_data[i];
	}
	return Tail = NodeTemp;
}

LLNode *LLManager::dequeue(void)
{
	LLNode *NodeTemp;

	if (OutputNode != NULL) {
		delete OutputNode;
	}
	OutputNode = new LLNode;

	// 先頭がなければ出力をゼロにして終了
	if (Head == NULL) {
		OutputNode->data = NULL;
		OutputNode->byte = 0;
		return Head;
	}

	// 出力ノードにデータを写す
	OutputNode->data = new char[Head->byte];
	for (int i = 0; i < Head->byte; i++) {
		OutputNode->data[i] = Head->data[i];
	}
	OutputNode->byte = Head->byte;

	// 一個前がなければdeleteして終了
	if (Head->back == NULL) {
		delete Head;
		Head = NULL;
		return Head;
	}
	// 一個前をHeadにする
	NodeTemp = Head->back;
	delete Head;
	Head = NodeTemp;
	Head->next = NULL;

	return Head;
}

