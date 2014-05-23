
#include <stdio.h>
//#define _DATA_FIELD_COMMUNICATION_DEBUG_ 
#include "CObjectCommunicator.h"

// コンストラクタ
BTerminal::BTerminal(void)
{
	ParentBDataField		= NULL;
	AcquiringID			= NULL;
	AcquiringIDnum		= 0;
	LLDataBuf			= new LLManager;
}

// デストラクタ
BTerminal::~BTerminal(void)
{
	if (LLDataBuf != NULL)
		delete LLDataBuf;
	if (AcquiringID != NULL)
		delete AcquiringID;
}

//---------------------------------------------------------------------------
// ユーザに公開するメンバ関数　ここから
//---------------------------------------------------------------------------

// データフィールド（in_ParentBDataField）に接続
void BTerminal::connectToBDataField(BDataField *in_ParentBDataField)
{
	if (in_ParentBDataField != NULL)
		connectMe(in_ParentBDataField);
}

// データフィールドとの接続解除
void BTerminal::disconnectFromBDataField(void)
{
	releaseMe();
}

// データフィールドにデータを流す
void BTerminal::putData(int ID, char *data, int byte)
{
	sendData(ID, data, byte);
}

// バッファに溜まっているデータの先頭を１つ取得（FIFO）
// データがない場合は *out_data=NULL; *out_byte=0;
//
// GetData()を呼び出す度にDequeue()によって
// 出力バッファ(OutputNode)の内容が更新される。
void BTerminal::getData(char **out_data, int *out_byte)
{
	LLDataBuf->dequeue();
	*out_data = LLDataBuf->OutputNode->data;
	*out_byte = LLDataBuf->OutputNode->byte;
#ifdef _DATA_FIELD_COMMUNICATION_DEBUG_
	printf("GetData() data=%s, byte=%d\n", *out_data, *out_byte);
#endif
}

// 登録IDを追加
void BTerminal::addID(int in_ID)
{
	// IDが何も登録されていない場合
	if (AcquiringID == NULL) {
		AcquiringID = new int;
		AcquiringID[0] = in_ID;
		AcquiringIDnum++;

	// 登録されている場合
	} else {
		// in_IDが既に登録済みなら何もせず終了
		for (int i = 0; i < AcquiringIDnum; i++) {
			if (AcquiringID[i] == in_ID)
				return;
		}
		int *temp = new int[AcquiringIDnum];
		for (int i = 0; i < AcquiringIDnum; i++) {
			temp[i] = AcquiringID[i];
		}
		delete AcquiringID;
		AcquiringIDnum++;
		AcquiringID = new int[AcquiringIDnum];
		for (int i = 0; i < AcquiringIDnum - 1; i++) {
			AcquiringID[i] = temp[i];
		}
		AcquiringID[AcquiringIDnum-1] = in_ID;
	}

#ifdef _DATA_FIELD_COMMUNICATION_DEBUG_
	// ★
	printf("AddID() AcquiringIDnum=%d\n", AcquiringIDnum);
	for (int i = 0; i < AcquiringIDnum; i++) {
		printf("AddID() AcquiringID[%d] = %d\n", i, AcquiringID[i]);
	}
#endif

}

// 登録IDの削除
void BTerminal::removeID(int in_ID)
{
	//
	//１．tempにAcquiringIDをコピー
	//　（その際取り除くIDはコピーしない）
	//２．AcquiringIDを確保し直しtempをAcquiringIDにコピー
	//
	int *temp = new int[AcquiringIDnum];
	int count = 0;
	for (int i = 0; i < AcquiringIDnum; i++) {
		temp[count] = AcquiringID[i];
		if (temp[count] == in_ID)
			continue;
		count++;
	}
	delete AcquiringID;
	AcquiringID = new int[count];
	for (int i = 0; i < count; i++) {
		AcquiringID[i] = temp[i];
	}
	AcquiringIDnum = count;
}

//---------------------------------------------------------------------------
// ユーザに公開するメンバ関数　ここまで
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// データフィールドとのやりとりをする関数　ここから
//---------------------------------------------------------------------------

void BTerminal::connectMe(BDataField *in_ParentBDataField)
{
	if (in_ParentBDataField!=NULL)
		in_ParentBDataField->registBTerminal(this);
	ParentBDataField = in_ParentBDataField;
}

void BTerminal::releaseMe(void)
{
	ParentBDataField->releaseBTerminal(this);
	ParentBDataField = NULL;
}

void BTerminal::sendData(int ID, char *data, int byte)
{
	if (ParentBDataField != NULL)
		ParentBDataField->catchAndSendData(ID, data, byte);
}

// BDataFieldからデータを受け取りバッファへ格納
// ただし登録したIDのデータのみ取得
void BTerminal::receiveData(int ID, char *in_data, int in_byte)
{
#ifdef _DATA_FIELD_COMMUNICATION_DEBUG_
	// ★　
	printf("ReceiveData() this=%p, ID=%d, data=%s, byte=%d\n", this, ID, in_data, in_byte);
#endif
	for (int i = 0; i < AcquiringIDnum; i++) {
		if (AcquiringID[i] == ID) {
#ifdef _DATA_FIELD_COMMUNICATION_DEBUG_
			// ★
			printf("ReceiveData() detect! ID=%d, data=%s, byte=%d\n", ID, in_data, in_byte);
#endif
			LLDataBuf->queue(in_data, in_byte);
			procedure(ID, in_data, in_byte);
		}
	}
}

//---------------------------------------------------------------------------
// データフィールドとのやりとりをする関数　ここまで
//---------------------------------------------------------------------------


BDataField::BDataField(void)
{
	Head			= NULL;
	Tail			= NULL;
}

BDataField::~BDataField(void)
{
}

TERMINALNODE *BDataField::registBTerminal(BTerminal *in_terminal)
{ 
	TERMINALNODE *NodeTemp = new TERMINALNODE;
	NodeTemp->next = Tail;
	NodeTemp->ptr = in_terminal;
	if (Head == NULL) {
		Head = NodeTemp;
	} else {
		NodeTemp->next->back = NodeTemp;
	}

	return Tail = NodeTemp;
}

void BDataField::releaseBTerminal(BTerminal *terminal)
{	
	TERMINALNODE *NodeTemp;

	if (terminal == Tail->ptr) {
		NodeTemp = Tail->next;
		delete Tail;
		Tail = NodeTemp;
		return;
	}

	if (terminal == Head->ptr) {
		NodeTemp = Head->back;
		delete Head;
		Head = NodeTemp;
		Head->next = NULL;
		return;
	}

	for (NodeTemp = Tail->next; NodeTemp != Head->back;) {
		if (NodeTemp->ptr == terminal) {
			NodeTemp->back->next = NodeTemp->next;
			NodeTemp->next->back = NodeTemp->back;
			delete NodeTemp;
			break;
		}
		NodeTemp = NodeTemp->next;
	}

	return;
}

void BDataField::catchAndSendData(int ID, char *data, int byte)
{
	TERMINALNODE *NodeTemp = Tail;
	while (NodeTemp != NULL) {
#ifdef _DATA_FIELD_COMMUNICATION_DEBUG_
		// ★
		printf("CatchAndSendData() NodeTemp->ptr=%p\n", NodeTemp->ptr);
#endif
		NodeTemp->ptr->receiveData(ID, data, byte);
		NodeTemp = NodeTemp->next;
	}
}

