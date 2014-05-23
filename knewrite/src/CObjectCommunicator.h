#ifndef ___C_OBJECT_COMMUNICATOR_H___
#define ___C_OBJECT_COMMUNICATOR_H___

#ifndef NULL
#define NULL 0
#endif

//-------------------------------------------------------------------------------------------------
// 線形リストのノードクラス
// (input)Tail -> Node -> Node -> ... -> Node -> Head(Output)
//-------------------------------------------------------------------------------------------------
class LLNode {
public:
	LLNode(void) {
		back = next = NULL;
		byte = 0;
		data = NULL;
	}
	~LLNode(void) { if (data) delete data; data = NULL; }

	char *data;		// ノードが保有するデータ
	int	byte;		// データのサイズ
	LLNode *next;	// 前方ノードへのポインタ
	LLNode *back;	// 後方ノードへのポインタ
};

//-------------------------------------------------------------------------------------------------
// ノード管理用クラス　表からはこれを使う。
//-------------------------------------------------------------------------------------------------
class LLManager {
public:
	LLManager(void);
	~LLManager(void);

	LLNode	*Head;			// 先頭ノードへのポインタ
	LLNode	*Tail;			// 最後尾ノードへのポインタ

	// 最後尾にノードを追加
	LLNode	*queue(char *in_data, int in_byte);
	// 先頭ノードを取り出す　取り出したデータはOutputNodeに格納
	LLNode	*dequeue(void);

	LLNode	*OutputNode;	// 出力データの一時保存場所

};

//-------------------------------------------------------------------------------------------------
//	データフィールド通信を行うクラス	copyright(C) 2008 佐藤陽平
//-------------------------------------------------------------------------------------------------
//
//	使い方
//
//		１．BDataFieldのインスタンス作成
//		２．BTerminalのインスタンス作成
//      (2.5. データ到着と同時にプロセスを走らせたい場合は、
//				BTerminalProcedureを継承したクラスを作り
//				exec()をオーバーライドして走らせたい処理を記述)
//		３．BTerminal::connectToBDataField()でBTerminalをBDataFieldに接続
//		４．BTerminal::addID()で取得するデータのIDを登録
//			BTerminal::putData()でデータをデータフィールドに流す
//			BTerminal::getData()でデータを取得
//		５．BTerminal::disconnectFromBDataField()で接続解除
//		６．BTerminalインスタンスのdelete
//		７．BDataFieldインスタンスのdelete
//
//	memo
//
//		・接続するBTerminalは幾つでも可（だと思う）
//		・IDはintの範囲
//		・BTerminalは各プロセスの端末として使う
//		　（BTerminalを継承してプロセスで用いるデータとのI/Fを追加するとよさ気）
//		・IDを管理するノードを作って、データフィールドにぶら下げておくといいかも
//
//	tips
//
//		・BDataFieldを複数設けてそれぞれに繋がったターミナルを持つプロセスを
//		　つくれば、BDataField間をつなぐことも可（こうすれば使用するIDを増やせる。）
//
//-------------------------------------------------------------------------------------------------
class BTerminal;
class BDataField;

// BDataFieldが各BTerminalを線形リストとして扱う為に用いる
typedef struct _TERMINALNODE {
	BTerminal		*ptr;
	_TERMINALNODE	*next;
	_TERMINALNODE	*back;
} TERMINALNODE;

// 未実装　（使用していない）
//typedef struct _RECEIVEDATABOX {
//	char	*data;
//	int		byte;
//} RECEIVEDATABOX;

class BTerminalProcedure {
 public:
	virtual void exec(int, char *, int) {};
};

//-------------------------------------------------------------------------------------------------
//	ターミナルクラス
//-------------------------------------------------------------------------------------------------
class BTerminal {

	friend class BDataField;

public:
	BTerminal(void);
	virtual ~BTerminal(void);

	// ユーザとのやり取り
	virtual void			connectToBDataField(BDataField *in_ParentBDataField);	// データフィールドに接続
	virtual void			disconnectFromBDataField(void);						// データフィールドとの接続解除
	virtual void			putData(int ID, char *data, int byte);				// データフィールドにデータを流す
	virtual void			getData(char **out_data, int *out_byte);			// バッファからデータを取ってくる
	//void			SetReceiveDataBox(RECEIVEDATABOX *DataBox);			// 未実装
	virtual void			addID(int in_ID);									// 登録IDを追加
	virtual void			removeID(int in_ID);								// 登録IDを削除

protected:	
	// データフィールドとのやり取り
	virtual void			connectMe(BDataField *in_ParentBDataField);
	virtual void			releaseMe(void);
	virtual inline void		sendData(int ID, char *data, int byte);
	virtual void			receiveData(int ID, char *data, int byte);

	BDataField		*ParentBDataField;	// 接続するデータフィールドへのポインタ
	int				*AcquiringID;		// 受け取るデータのID
	int				AcquiringIDnum;		// 登録しているIDの数
	LLManager		*LLDataBuf;			// データフィールドからのデータ受け取りバッファ

	virtual void    procedure(int ID, char *data, int byte) = 0;
};
//-------------------------------------------------------------------------------------------------
//	データフィールドクラス
//-------------------------------------------------------------------------------------------------
class BDataField {

	friend class BTerminal;	// BTerminalからのみメンバ関数にアクセスできる

public:
	BDataField(void);
	~BDataField(void);

private:
	TERMINALNODE*	registBTerminal(BTerminal *terminal);
	void			releaseBTerminal(BTerminal *terminal);
	void			catchAndSendData(int ID, char *data, int byte);

	TERMINALNODE	*Head;
	TERMINALNODE	*Tail;
};

#endif//___C_OBJECT_COMMUNICATOR_H___
