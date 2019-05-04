#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<cmath>
#include<ctime>
#include"NLPann.h"
using namespace std;

struct ObjElement
{
	char __ObjName[40];
	char __FileName_1[40];
	char __FileName_2[40];
	char __FileName_3[40];
	char __FileName_4[40];
	char __FileName_5[40];
	char __FileName_6[40];
	char __FileName_7[40];
	char __FileName_8[40];
	char __Function[10];
	int __INUM;
	int __HNUM;
	int __ONUM;
	int __DEPTH;
	int __MAXTIME;
	int __NetworkType;
	int __BatchSize;
	double __LearningRate;
};
class UserObject
{
	private:
		ObjElement __Obj;
	public:
		UserObject *__p;
		UserObject(
		const char *__objname="NULL",
		const char *__filename1="NULL",
		const char *__filename2="NULL",
		const char *__filename3="NULL",
		const char *__filename4="NULL",
		const char *__filename5="NULL",
		const char *__filename6="NULL",
		const char *__filename7="NULL",
		const char *__filename8="NULL",
		const char *__function="NULL",
		int __inum=0,
		int __hnum=0,
		int __onum=0,
		int __depth=0,
		int __maxtime=0,
		int __networktype=0,
		int __batchsize=0,
		double __learningrate=0.1
		)
		{
			strcpy(__Obj.__ObjName,__objname);
			strcpy(__Obj.__FileName_1,__filename1);
			strcpy(__Obj.__FileName_2,__filename2);
			strcpy(__Obj.__FileName_3,__filename3);
			strcpy(__Obj.__FileName_4,__filename4);
			strcpy(__Obj.__FileName_5,__filename5);
			strcpy(__Obj.__FileName_6,__filename6);
			strcpy(__Obj.__FileName_7,__filename7);
			strcpy(__Obj.__FileName_8,__filename8);
			strcpy(__Obj.__Function,__function);
			__Obj.__INUM=__inum;
			__Obj.__HNUM=__hnum;
			__Obj.__ONUM=__onum;
			__Obj.__DEPTH=__depth;
			__Obj.__MAXTIME=__maxtime;
			__Obj.__NetworkType=__networktype;
			__Obj.__BatchSize=__batchsize;
			__Obj.__LearningRate=__learningrate;
			__p=NULL;
		}
		void PrintObj()
		{
			cout<<"         ------------------------------------------------------"<<endl;
			cout<<"         |Name         |"<<__Obj.__ObjName<<endl;
			cout<<"         |File 1       |"<<__Obj.__FileName_1<<endl;
			cout<<"         |File 2       |"<<__Obj.__FileName_2<<endl;
			cout<<"         |File 3       |"<<__Obj.__FileName_3<<endl;
			cout<<"         |File 4       |"<<__Obj.__FileName_4<<endl;
			cout<<"         |File 5       |"<<__Obj.__FileName_5<<endl;
			cout<<"         |File 6       |"<<__Obj.__FileName_6<<endl;
			cout<<"         |File 7       |"<<__Obj.__FileName_7<<endl;
			cout<<"         |File 8       |"<<__Obj.__FileName_8<<endl;
			cout<<"         |Function     |"<<__Obj.__Function<<endl;
			cout<<"         |INUM         |"<<__Obj.__INUM<<endl;
			cout<<"         |HNUM         |"<<__Obj.__HNUM<<endl;
			cout<<"         |ONUM         |"<<__Obj.__ONUM<<endl;
			cout<<"         |DEPTH        |"<<__Obj.__DEPTH<<endl;
			cout<<"         |MAXTIME      |"<<__Obj.__MAXTIME<<endl;
			cout<<"         |LearningRate |"<<__Obj.__LearningRate<<endl;
			cout<<"         |Batch Size   |"<<__Obj.__BatchSize<<endl;
			cout<<"         |Network Type |";
			switch(__Obj.__NetworkType)
			{
				case 1:
					cout<<"BP(Normal neural network)"<<endl;
					break;
				case 2:
					cout<<"BP(Deep neural network)"<<endl;
					break;
				case 3:
					cout<<"RNN seq2seq(Normal neural network)"<<endl;
					break;
				case 4:
					cout<<"RNN seq2seq(Deep neural network)"<<endl;
					break;
				case 5:
					cout<<"LSTM seq2seq(Normal neural network)"<<endl;
					break;
				case 6:
					cout<<"LSTM seq2seq(Deep neural network)"<<endl;
					break;
				case 7:
					cout<<"GRU seq2seq(Normal neural network)"<<endl;
					break;
				case 8:
					cout<<"GRU seq2seq(Deep neural network)"<<endl;
					break;
				case 9:
					cout<<"RNN seq2vec(Normal neural network)"<<endl;
					break;
				case 10:
					cout<<"RNN seq2vec(Deep neural network)"<<endl;
					break;
				case 11:
					cout<<"LSTM seq2vec(Normal neural network)"<<endl;
					break;
				case 12:
					cout<<"LSTM seq2vec(Deep neural network)"<<endl;
					break;
				case 13:
					cout<<"GRU seq2vec(Normal neural network)"<<endl;
					break;
				case 14:
					cout<<"GRU seq2vec(Deep neural network)"<<endl;
					break;
				case 15:
					cout<<"BP char2vec(Normal neural network)"<<endl;
					break;
				default:
					cout<<"Unknown Type"<<endl;
					break;
			}
			cout<<"         ------------------------------------------------------"<<endl;
		}
		ObjElement* getObjPointer()
		{
			return &__Obj;
		}
		bool CheckObjName(string &TempName)
		{
			if(TempName==__Obj.__ObjName)
				return true;
			else
				return false;
		}
		bool CheckObjName(const char *__t)
		{
			if(!strcmp(__t,__Obj.__ObjName))
				return true;
			else
				return false;
		}
		void ObjChange(ObjElement &__temp)
		{
			__Obj=__temp;
			return;
		}
};
class ObjManagement
{
	private:
		UserObject *__Head;
		ObjElement __Datatemp;
	public:
		ObjManagement()
		{
			__Head=new UserObject;
			__Head->__p=NULL;
		}
		~ObjManagement()
		{
			UserObject *Node=__Head;
			UserObject *Temp;
			while(Node->__p!=NULL)
			{
				Temp=Node;
				Node=Node->__p;
				delete Temp;
			}
			delete Node;
		}
		void ObjDataIn()
		{
			UserObject *Node=__Head;
			fstream fin("ObjData.dat",ios::in|ios::binary);
			if(fin.fail())
			{
				cout<<"easyNLP>>[Error]Cannot open important data \"Objdata.dat\" or this data maybe lost!"<<endl;
				system("pause");
				exit(0);
			}
			while(!fin.eof())
			{
				fin.read((char*)&__Datatemp,sizeof(ObjElement));
				if(fin.eof())
					break;
				Node->__p=new UserObject(
				__Datatemp.__ObjName,
				__Datatemp.__FileName_1,
				__Datatemp.__FileName_2,
				__Datatemp.__FileName_3,
				__Datatemp.__FileName_4,
				__Datatemp.__FileName_5,
				__Datatemp.__FileName_6,
				__Datatemp.__FileName_7,
				__Datatemp.__FileName_8,
				__Datatemp.__Function,
				__Datatemp.__INUM,
				__Datatemp.__HNUM,
				__Datatemp.__ONUM,
				__Datatemp.__DEPTH,
				__Datatemp.__MAXTIME,
				__Datatemp.__NetworkType,
				__Datatemp.__BatchSize,
				__Datatemp.__LearningRate
				);
				Node=Node->__p;
				Node->__p=NULL;
			}
			fin.close();
			return;
		}
		void ObjDataOut()
		{
			UserObject *Node=__Head;
			fstream fout("ObjData.dat",ios::out|ios::binary);
			if(fout.fail())
			{
				cout<<"easyNLP>>[Error]Cannot open important data \"Objdata.dat\" or this data maybe lost!"<<endl;
				system("pause");
				exit(0);
			}
			while(Node->__p!=NULL)
			{
				Node=Node->__p;
				fout.write((char*)Node->getObjPointer(),sizeof(ObjElement));
			}
			fout.close(); 
			return;
		}
		void MakeData()
		{
			UserObject *Node=__Head;
			cout<<"easyNLP>>Name of your project: ";
			cin>>__Datatemp.__ObjName;
			while(Node->__p!=NULL)
			{
				Node=Node->__p;
				if(Node->CheckObjName(__Datatemp.__ObjName))
				{
					cout<<"easyNLP>>[Error]You have already created this project!"<<endl<<endl;
					cout<<"         |The project is:"<<endl;
					Node->PrintObj();
					return;
				}
			}
			if(!ObjChoose())
			{
				cout<<"easyNLP>>[Quiting]"<<endl;
				return;
			}
			Node->__p=new UserObject(
			__Datatemp.__ObjName,
			__Datatemp.__FileName_1,
			__Datatemp.__FileName_2,
			__Datatemp.__FileName_3,
			__Datatemp.__FileName_4,
			__Datatemp.__FileName_5,
			__Datatemp.__FileName_6,
			__Datatemp.__FileName_7,
			__Datatemp.__FileName_8,
			__Datatemp.__Function,
			__Datatemp.__INUM,
			__Datatemp.__HNUM,
			__Datatemp.__ONUM,
			__Datatemp.__DEPTH,
			__Datatemp.__MAXTIME,
			__Datatemp.__NetworkType,
			__Datatemp.__BatchSize,
			__Datatemp.__LearningRate
			);
			Node=Node->__p;
			Node->__p=NULL;
			cout<<"easyNLP>>New project is established successfully."<<endl;
		}
		bool ObjChoose()
		{
			string Command;
			cout<<"easyNLP>>"<<endl;
			cout<<"         |1. |BP project(Normal)            |"<<endl;
			cout<<"         |2. |BP project(Deep)              |"<<endl;
			cout<<"         |3. |seq2seq project(RNN:Normal)   |"<<endl;
			cout<<"         |4. |seq2seq project(RNN:Deep)     |"<<endl;
			cout<<"         |5. |seq2seq project(LSTM:Normal)  |"<<endl;
			cout<<"         |6. |seq2seq project(LSTM:Deep)    |"<<endl;
			cout<<"         |7. |seq2seq project(GRU:Normal)   |"<<endl;
			cout<<"         |8. |seq2seq project(GRU:Deep)     |"<<endl;
			cout<<"         |9. |seq2vec project(RNN:Normal)   |"<<endl;
			cout<<"         |10.|seq2vec project(RNN:Deep)     |"<<endl;
			cout<<"         |11.|seq2vec project(LSTM:Normal)  |"<<endl;
			cout<<"         |12.|seq2vec project(LSTM:Deep)    |"<<endl;
			cout<<"         |13.|seq2vec project(GRU:Normal)   |"<<endl;
			cout<<"         |14.|seq2vec project(GRU:Deep)     |"<<endl;
			cout<<"         |15.|char2vec project(BP:Normal)   |"<<endl;
			cout<<"         |16.|I don't want to choose.(quit) |"<<endl;
			while(1)
			{
				cin>>Command;
				if(Command=="1")
				{
					cout<<"easyNLP>>"<<endl;
					cout<<"         |BP project(Normal) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for all layers)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the output file: ";
					cin>>__Datatemp.__FileName_1;
					strcpy(__Datatemp.__FileName_2,"NULL");
					strcpy(__Datatemp.__FileName_3,"NULL");
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function: ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					__Datatemp.__DEPTH=0;
					__Datatemp.__MAXTIME=0;
					__Datatemp.__NetworkType=1;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="2")
				{
					cout<<"easyNLP>>"<<endl;
					cout<<"         |BP project(Deep) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |DEPTH: Number of layers"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for all layers)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the output file: ";
					cin>>__Datatemp.__FileName_1;
					strcpy(__Datatemp.__FileName_2,"NULL");
					strcpy(__Datatemp.__FileName_3,"NULL");
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function: ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					cout<<"easyNLP>>Number of layers: ";
					cin>>__Datatemp.__DEPTH;
					__Datatemp.__MAXTIME=0;
					__Datatemp.__NetworkType=2;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="3")
				{
					cout<<"easyNLP>>[RNN]"<<endl;
					cout<<"         |seq2seq project(RNN/LSTM/GRU:Normal) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the decoder module file: ";
					cin>>__Datatemp.__FileName_2;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_3;
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2seq uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					__Datatemp.__DEPTH=0;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=3;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="4")
				{
					cout<<"easyNLP>>[RNN]"<<endl;
					cout<<"         |seq2seq project(RNN/LSTM/GRU:Deep) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |DEPTH: Number of layers"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the decoder module file: ";
					cin>>__Datatemp.__FileName_2;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_3;
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2seq uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					cout<<"easyNLP>>Number of layers: ";
					cin>>__Datatemp.__DEPTH;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=4;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="5")
				{
					cout<<"easyNLP>>[LSTM]"<<endl;
					cout<<"         |seq2seq project(RNN/LSTM/GRU:Normal) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the decoder module file: ";
					cin>>__Datatemp.__FileName_2;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_3;
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2seq uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					__Datatemp.__DEPTH=0;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=5;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="6")
				{
					cout<<"easyNLP>>[LSTM]"<<endl;
					cout<<"         |seq2seq project(RNN/LSTM/GRU:Deep) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |DEPTH: Number of layers"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the decoder module file: ";
					cin>>__Datatemp.__FileName_2;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_3;
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2seq uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					cout<<"easyNLP>>Number of layers: ";
					cin>>__Datatemp.__DEPTH;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=6;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="7")
				{
					cout<<"easyNLP>>[GRU]"<<endl;
					cout<<"         |seq2seq project(RNN/LSTM/GRU:Normal) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the decoder module file: ";
					cin>>__Datatemp.__FileName_2;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_3;
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2seq uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					__Datatemp.__DEPTH=0;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=7;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="8")
				{
					cout<<"easyNLP>>[GRU]"<<endl;
					cout<<"         |seq2seq project(RNN/LSTM/GRU:Deep) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |DEPTH: Number of layers"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the decoder module file: ";
					cin>>__Datatemp.__FileName_2;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_3;
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2seq uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					cout<<"easyNLP>>Number of layers: ";
					cin>>__Datatemp.__DEPTH;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=8;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="9")
				{
					cout<<"easyNLP>>[RNN]"<<endl;
					cout<<"         |seq2vec project(RNN/LSTM/GRU:Normal) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_2;
					strcpy(__Datatemp.__FileName_3,"NULL");
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2vec uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					__Datatemp.__DEPTH=0;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=9;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="10")
				{
					cout<<"easyNLP>>[RNN]"<<endl;
					cout<<"         |seq2vec project(RNN/LSTM/GRU:Deep) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |DEPTH: Number of layers"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_2;
					strcpy(__Datatemp.__FileName_3,"NULL");
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2vec uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					cout<<"easyNLP>>Number of layers: ";
					cin>>__Datatemp.__DEPTH;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=10;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="11")
				{
					cout<<"easyNLP>>[LSTM]"<<endl;
					cout<<"         |seq2vec project(RNN/LSTM/GRU:Normal) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_2;
					strcpy(__Datatemp.__FileName_3,"NULL");
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2vec uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					__Datatemp.__DEPTH=0;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=11;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="12")
				{
					cout<<"easyNLP>>[LSTM]"<<endl;
					cout<<"         |seq2vec project(RNN/LSTM/GRU:Deep) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |DEPTH: Number of layers"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_2;
					strcpy(__Datatemp.__FileName_3,"NULL");
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2vec uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					cout<<"easyNLP>>Number of layers: ";
					cin>>__Datatemp.__DEPTH;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=12;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="13")
				{
					cout<<"easyNLP>>[GRU]"<<endl;
					cout<<"         |seq2vec project(RNN/LSTM/GRU:Normal) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_2;
					strcpy(__Datatemp.__FileName_3,"NULL");
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2vec uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					__Datatemp.__DEPTH=0;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=13;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="14")
				{
					cout<<"easyNLP>>[GRU]"<<endl;
					cout<<"         |seq2vec project(RNN/LSTM/GRU:Deep) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons"<<endl;
					cout<<"         |DEPTH: Number of layers"<<endl;
					cout<<"         |MAXTIME: Max length of sequence"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of input set file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions(for output layer)"<<endl;
					cout<<"         |Batch size: Size of input/training set batch"<<endl;
					cout<<"         |Learning rate:This decides how fast your model runs"<<endl;
					cout<<"easyNLP>>Name of the encoder module file: ";
					cin>>__Datatemp.__FileName_1;
					cout<<"easyNLP>>Name of the output layer file: ";
					cin>>__Datatemp.__FileName_2;
					strcpy(__Datatemp.__FileName_3,"NULL");
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					cout<<"easyNLP>>Name of input set file: ";
					cin>>__Datatemp.__FileName_7;
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					cout<<"easyNLP>>Name of the activate function(seq2vec uses softmax as output and your function may not work): ";
					cin>>__Datatemp.__Function;
					cout<<"easyNLP>>Number of input layer neurons: ";
					cin>>__Datatemp.__INUM;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					cout<<"easyNLP>>Number of output layer neurons: ";
					cin>>__Datatemp.__ONUM;
					cout<<"easyNLP>>Number of layers: ";
					cin>>__Datatemp.__DEPTH;
					cout<<"easyNLP>>Max length of sequence: ";
					cin>>__Datatemp.__MAXTIME;
					__Datatemp.__NetworkType=14;
					cout<<"easyNLP>>Learning rate(must more than 0 but less than 1): ";
					cin>>__Datatemp.__LearningRate;
					cout<<"easyNLP>>Size of input/training set batch: ";
					cin>>__Datatemp.__BatchSize;
					break;
				}
				else if(Command=="15")
				{
					cout<<"easyNLP>>"<<endl;
					cout<<"         |char2vec project(BP:Normal) needs:"<<endl;
					cout<<"         |INUM: Number of input layer neurons is set to 95"<<endl;
					cout<<"         |HNUM: Number of hidden layer neurons"<<endl;
					cout<<"         |ONUM: Number of output layer neurons is set to 95"<<endl;
					cout<<"         |File: Name of data file"<<endl;
					cout<<"         |File: Name of training set file"<<endl;
					cout<<"         |Function: one of activate functions is set as softmax"<<endl;
					cout<<"         |Learning rate:0.1"<<endl;
					cout<<"easyNLP>>Name of the output data file: ";
					cin>>__Datatemp.__FileName_1;
					strcpy(__Datatemp.__FileName_2,"NULL");
					strcpy(__Datatemp.__FileName_3,"NULL");
					strcpy(__Datatemp.__FileName_4,"NULL");
					strcpy(__Datatemp.__FileName_5,"NULL");
					strcpy(__Datatemp.__FileName_6,"NULL");
					strcpy(__Datatemp.__FileName_7,"NULL");
					cout<<"easyNLP>>Name of training set file: ";
					cin>>__Datatemp.__FileName_8;
					strcpy(__Datatemp.__Function,"softmax");
					__Datatemp.__INUM=95;
					cout<<"easyNLP>>Number of hidden layer neurons: ";
					cin>>__Datatemp.__HNUM;
					__Datatemp.__ONUM=95;
					__Datatemp.__DEPTH=0;
					__Datatemp.__MAXTIME=0;
					__Datatemp.__NetworkType=15;
					__Datatemp.__LearningRate=0.1;
					__Datatemp.__BatchSize=0;
					break;
				}
				else if(Command=="16")
				{
					return false;
				}
				else
					cout<<"easyNLP>>[Error]Undefined choice."<<endl;
			}
			return true;
		}
		void RunModule()
		{
			bool __FoundObj=false;
			UserObject *Node=__Head;
			string temp_obj_name;
			cout<<"easyNLP>>Name of the project: ";
			cin>>temp_obj_name;
			while(Node->__p!=NULL)
			{
				Node=Node->__p;
				if(Node->CheckObjName(temp_obj_name))
				{
					Node->PrintObj();
					__FoundObj=true;
					break;
				}
			}
			if(__FoundObj)
			{
				if(Node->getObjPointer()->__NetworkType==1)
				{
					cout<<"easyNLP>>[Running]BP(Normal neural network)"<<endl;
					NormalBP __MainBP(Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r"))
					{
						__MainBP.INIT();
						__MainBP.Dataout(Node->getObjPointer()->__FileName_1);
					}
					__MainBP.Datain(Node->getObjPointer()->__FileName_1);
					__MainBP.SetFunction(Node->getObjPointer()->__Function);
					__MainBP.SetLearningrate(Node->getObjPointer()->__LearningRate);
					__MainBP.TotalWork(Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_7,Node->getObjPointer()->__FileName_8);
				}
				else if(Node->getObjPointer()->__NetworkType==2)
				{
					cout<<"easyNLP>>[Running]BP(Deep neural network)"<<endl;
					DeepBP __MainBP(Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__DEPTH);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r"))
					{
						__MainBP.INIT();
						__MainBP.Dataout(Node->getObjPointer()->__FileName_1);
					}
					__MainBP.Datain(Node->getObjPointer()->__FileName_1);
					__MainBP.SetFunction(Node->getObjPointer()->__Function);
					__MainBP.SetLearningrate(Node->getObjPointer()->__LearningRate);
					__MainBP.TotalWork(Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_7,Node->getObjPointer()->__FileName_8);
				}
				else if(Node->getObjPointer()->__NetworkType==3)
				{
					cout<<"easyNLP>>[Running]RNN seq2seq(Normal neural network)"<<endl;
					NormalSeq2Seq __MainSeq("rnn",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r")||!fopen(Node->getObjPointer()->__FileName_3,"r"))
					{
						__MainSeq.Dataout("rnn",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					}
					__MainSeq.Datain("rnn",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					__MainSeq.SetFunction(Node->getObjPointer()->__Function);
					__MainSeq.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==4)
				{
					cout<<"easyNLP>>[Running]RNN seq2seq(Deep neural network)"<<endl;
					if(Node->getObjPointer()->__DEPTH>2)
					{
						char Confirm;
						cout<<"easyNLP>>[Warning]Seq2Seq with two more layers may not work well,do you still want to run this model?(y/n)"<<endl;
						cin>>Confirm;
						if(Confirm!='y')
						{
							cout<<"easyNLP>>[Error]Running process cancelled"<<endl;
							return;
						}
					}
					DeepSeq2Seq __MainSeq("rnn",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__DEPTH,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r")||!fopen(Node->getObjPointer()->__FileName_3,"r"))
					{
						__MainSeq.Dataout("rnn",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					}
					__MainSeq.Datain("rnn",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					__MainSeq.SetFunction(Node->getObjPointer()->__Function);
					__MainSeq.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==5)
				{
					cout<<"easyNLP>>[Running]LSTM seq2seq(Normal neural network)"<<endl;
					NormalSeq2Seq __MainSeq("lstm",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r")||!fopen(Node->getObjPointer()->__FileName_3,"r"))
					{
						__MainSeq.Dataout("lstm",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					}
					__MainSeq.Datain("lstm",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					__MainSeq.SetFunction(Node->getObjPointer()->__Function);
					__MainSeq.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==6)
				{
					cout<<"easyNLP>>[Running]LSTM seq2seq(Deep neural network)"<<endl;
					if(Node->getObjPointer()->__DEPTH>2)
					{
						char Confirm;
						cout<<"easyNLP>>[Warning]Seq2Seq with two more layers may not work well,do you still want to run this model?(y/n)"<<endl;
						cin>>Confirm;
						if(Confirm!='y')
						{
							cout<<"easyNLP>>[Error]Running process cancelled"<<endl;
							return;
						}
					}
					DeepSeq2Seq __MainSeq("lstm",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__DEPTH,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r")||!fopen(Node->getObjPointer()->__FileName_3,"r"))
					{
						__MainSeq.Dataout("lstm",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					}
					__MainSeq.Datain("lstm",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					__MainSeq.SetFunction(Node->getObjPointer()->__Function);
					__MainSeq.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==7)
				{
					cout<<"easyNLP>>[Running]GRU seq2seq(Normal neural network)"<<endl;
					NormalSeq2Seq __MainSeq("gru",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r")||!fopen(Node->getObjPointer()->__FileName_3,"r"))
					{
						__MainSeq.Dataout("gru",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					}
					__MainSeq.Datain("gru",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					__MainSeq.SetFunction(Node->getObjPointer()->__Function);
					__MainSeq.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==8)
				{
					cout<<"easyNLP>>[Running]GRU seq2seq(Deep neural network)"<<endl;
					if(Node->getObjPointer()->__DEPTH>2)
					{
						char Confirm;
						cout<<"easyNLP>>[Warning]Seq2Seq with two more layers may not work well,do you still want to run this model?(y/n)"<<endl;
						cin>>Confirm;
						if(Confirm!='y')
						{
							cout<<"easyNLP>>[Error]Running process cancelled"<<endl;
							return;
						}
					}
					DeepSeq2Seq __MainSeq("gru",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__DEPTH,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r")||!fopen(Node->getObjPointer()->__FileName_3,"r"))
					{
						__MainSeq.Dataout("gru",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					}
					__MainSeq.Datain("gru",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2,Node->getObjPointer()->__FileName_3);
					__MainSeq.SetFunction(Node->getObjPointer()->__Function);
					__MainSeq.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==9)
				{
					cout<<"easyNLP>>[Running]RNN seq2vec(Normal neural network)"<<endl;
					NormalSeq2Vec __MainVec("rnn",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r"))
					{
						__MainVec.Dataout("rnn",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					}
					__MainVec.Datain("rnn",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					__MainVec.SetFunction(Node->getObjPointer()->__Function);
					__MainVec.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==10)
				{
					cout<<"easyNLP>>[Running]RNN seq2vec(Deep neural network)"<<endl;
					if(Node->getObjPointer()->__DEPTH>2)
					{
						char Confirm;
						cout<<"easyNLP>>[Warning]Seq2Vec with two more layers may not work well,do you still want to run this model?(y/n)"<<endl;
						cin>>Confirm;
						if(Confirm!='y')
						{
							cout<<"easyNLP>>[Error]Running process cancelled"<<endl;
							return;
						}
					}
					DeepSeq2Vec __MainVec("rnn",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__DEPTH,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r"))
					{
						__MainVec.Dataout("rnn",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					}
					__MainVec.Datain("rnn",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					__MainVec.SetFunction(Node->getObjPointer()->__Function);
					__MainVec.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==11)
				{
					cout<<"easyNLP>>[Running]LSTM seq2vec(Normal neural network)"<<endl;
					NormalSeq2Vec __MainVec("lstm",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r"))
					{
						__MainVec.Dataout("lstm",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					}
					__MainVec.Datain("lstm",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					__MainVec.SetFunction(Node->getObjPointer()->__Function);
					__MainVec.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==12)
				{
					cout<<"easyNLP>>[Running]LSTM seq2vec(Deep neural network)"<<endl;
					if(Node->getObjPointer()->__DEPTH>2)
					{
						char Confirm;
						cout<<"easyNLP>>[Warning]Seq2Vec with two more layers may not work well,do you still want to run this model?(y/n)"<<endl;
						cin>>Confirm;
						if(Confirm!='y')
						{
							cout<<"easyNLP>>[Error]Running process cancelled"<<endl;
							return;
						}
					}
					DeepSeq2Vec __MainVec("lstm",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__DEPTH,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r"))
					{
						__MainVec.Dataout("lstm",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					}
					__MainVec.Datain("lstm",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					__MainVec.SetFunction(Node->getObjPointer()->__Function);
					__MainVec.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==13)
				{
					cout<<"easyNLP>>[Running]GRU seq2vec(Normal neural network)"<<endl;
					NormalSeq2Vec __MainVec("gru",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r"))
					{
						__MainVec.Dataout("gru",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					}
					__MainVec.Datain("gru",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					__MainVec.SetFunction(Node->getObjPointer()->__Function);
					__MainVec.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==14)
				{
					cout<<"easyNLP>>[Running]GRU seq2vec(Deep neural network)"<<endl;
					if(Node->getObjPointer()->__DEPTH>2)
					{
						char Confirm;
						cout<<"easyNLP>>[Warning]Seq2Vec with two more layers may not work well,do you still want to run this model?(y/n)"<<endl;
						cin>>Confirm;
						if(Confirm!='y')
						{
							cout<<"easyNLP>>[Error]Running process cancelled"<<endl;
							return;
						}
					}
					DeepSeq2Vec __MainVec("gru",Node->getObjPointer()->__INUM,Node->getObjPointer()->__HNUM,Node->getObjPointer()->__ONUM,Node->getObjPointer()->__DEPTH,Node->getObjPointer()->__MAXTIME);
					if(!fopen(Node->getObjPointer()->__FileName_1,"r")||!fopen(Node->getObjPointer()->__FileName_2,"r"))
					{
						__MainVec.Dataout("gru",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					}
					__MainVec.Datain("gru",Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_2);
					__MainVec.SetFunction(Node->getObjPointer()->__Function);
					__MainVec.SetLearningRate(Node->getObjPointer()->__LearningRate);
				}
				else if(Node->getObjPointer()->__NetworkType==15)
				{
					cout<<"easyNLP>>[Running]BP char2vec(Normal neural network)"<<endl;
					Char2Vec __MainVec(Node->getObjPointer()->__HNUM);
					__MainVec.TotalWork(Node->getObjPointer()->__FileName_1,Node->getObjPointer()->__FileName_8);
				}
				else
					cout<<"easyNLP>>[Error]Unknown Type"<<endl;
				return;
			}
			cout<<"easyNLP>>[Error]This project does not exist."<<endl;
			return;
		}
		void PrintAllObj()
		{
			UserObject *Node=__Head;
			if(__Head->__p==NULL)
			{
				cout<<"easyNLP>>[Error]Empty list.(0 project inside)"<<endl;
				return;
			}
			while(Node->__p!=NULL)
			{
				Node=Node->__p;
				Node->PrintObj();
			}
			return;
		}
		void FindObj()
		{
			UserObject *Node=__Head;
			string temp_obj_name;
			cout<<"easyNLP>>Name of the project: ";
			cin>>temp_obj_name;
			while(Node->__p!=NULL)
			{
				Node=Node->__p;
				if(Node->CheckObjName(temp_obj_name))
				{
					Node->PrintObj();
					return;
				}
			}
			cout<<"easyNLP>>[Error]This project does not exist."<<endl;
		}
		void EditObj()
		{
			UserObject *Node=__Head;
			ObjElement __Temp;
			string temp_obj_name;
			cout<<"easyNLP>>Name of the project: ";
			cin>>temp_obj_name;
			while(Node->__p!=NULL)
			{
				Node=Node->__p;
				if(Node->CheckObjName(temp_obj_name))
				{
					Node->PrintObj();
					cout<<"easyNLP>>[Editing]"<<endl;
					cout<<"         ------------------------------------------------------"<<endl;
					cout<<"         |Name         |";cin>>__Temp.__ObjName;
					cout<<"         |File 1       |";cin>>__Temp.__FileName_1;
					cout<<"         |File 2       |";cin>>__Temp.__FileName_2;
					cout<<"         |File 3       |";cin>>__Temp.__FileName_3;
					cout<<"         |File 4(NULL) |";cin>>__Temp.__FileName_4;
					cout<<"         |File 5(NULL) |";cin>>__Temp.__FileName_5;
					cout<<"         |File 6(NULL) |";cin>>__Temp.__FileName_6;
					cout<<"         |Input File   |";cin>>__Temp.__FileName_7;
					cout<<"         |Train File   |";cin>>__Temp.__FileName_8;
					cout<<"         |Function     |";cin>>__Temp.__Function;
					cout<<"         |INUM         |";cin>>__Temp.__INUM;
					cout<<"         |HNUM         |";cin>>__Temp.__HNUM;
					cout<<"         |ONUM         |";cin>>__Temp.__ONUM;
					cout<<"         |DEPTH        |";cin>>__Temp.__DEPTH;
					cout<<"         |MAXTIME      |";cin>>__Temp.__MAXTIME;
					cout<<"         |LearningRate |";cin>>__Temp.__LearningRate;
					cout<<"         |Batch Size   |";cin>>__Temp.__BatchSize;
					cout<<"         |Network Type |You Cannot Edit This."<<endl;__Temp.__NetworkType=Node->getObjPointer()->__NetworkType;
					cout<<"         ------------------------------------------------------"<<endl;
					Node->ObjChange(__Temp);
					ObjDataOut();
					return;
				}
			}
			cout<<"easyNLP>>[Error]This project does not exist."<<endl;
		}
		void DeleteObj()
		{
			string DelObjName;
			cout<<"easyNLP>>Input the name of the project you want to delete: ";
			cin>>DelObjName;
			UserObject *Node=__Head;
			UserObject *Temp;
			while(Node->__p!=NULL)
			{
				Temp=Node;
				Node=Node->__p;
				if(Node->CheckObjName(DelObjName))
				{
					Temp->__p=Node->__p;
					delete Node;
					ObjDataOut();
					cout<<"easyNLP>>Finished.(But the data must be deleted by yourself!)"<<endl;
					return;
				}
			}
			cout<<"easyNLP>>[Error]Cannot find this project."<<endl;
			return;
		}
};
void PrintHelp()
{
	cout<<"easyNLP>>[Help]"<<endl;
	cout<<"         |1.|Delete a project     |"<<endl;
	cout<<"         |2.|Create a new project |"<<endl;
	cout<<"         |3.|List all projects    |"<<endl;
	cout<<"         |4.|Run a project        |"<<endl;
	cout<<"         |5.|Clear the screen     |"<<endl;
	cout<<"         |6.|Find a project       |"<<endl;
	cout<<"         |7.|Edit a project       |"<<endl;
	cout<<"         |8.|Quit                 |"<<endl;
	cout<<"easyNLP>>You can find this help with command:\"h\" or \"help\""<<endl;
	return;
}
int main()
{
	ObjManagement __main;
	string Command;
	__main.ObjDataIn();
	PrintHelp();
	while(1)
	{
		cout<<"easyNLP>>";
		cin>>Command;
		if(Command=="h"||Command=="help")
		{
			PrintHelp();
		}
		else if(Command.length()>1)
		{
			cout<<"easyNLP>>[Error]Undefined command."<<endl;
			PrintHelp();
		}
		else if(Command[0]=='1')
			__main.DeleteObj();
		else if(Command[0]=='2')
		{
			__main.MakeData();
			__main.ObjDataOut();
		}
		else if(Command[0]=='3')
		{
			__main.PrintAllObj();
		}
		else if(Command[0]=='4')
		{
			__main.RunModule();
		}
		else if(Command[0]=='5')
		{
			system("cls");
			PrintHelp();
		}
		else if(Command[0]=='6')
		{
			__main.FindObj();
		}
		else if(Command[0]=='7')
		{
			__main.EditObj();
		}
		else if(Command[0]=='8')
		{
			cout<<"easyNLP>>[Quiting]Please wait."<<endl;
			__main.ObjDataOut();
			break;
		}
		else
		{
			cout<<"easyNLP>>[Error]Undefined command."<<endl;
			PrintHelp();
		}
	}
	return 0;
}
