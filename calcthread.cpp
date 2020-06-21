#include "calcthread.h"
#include <QDebug>

///
/// \brief Это конструктор класса CalcThread
///
CalcThread::CalcThread()  {

}

///
/// \brief Эта функция запускает сортировку
///
void CalcThread::run() {

	qDebug() << "Started";
	bubbleSort();

};

///
/// \brief Эта функция выполняет сортировку пузырьком
///
void CalcThread::bubbleSort() {
	qDebug() << "Calc data size:" << dataArray->size();
	for(int i = 0; i < 499999; i++) {
	   for(int j = i + 1; j < 500000; j++) {

			if (dataArray->value(j) > dataArray->value(i)) {
				dataArray->swapItemsAt(i, j);
		  }
	   }
	}
	finished = true;

};

///
/// \brief Это слот для передачи данных в основной поток
/// \return Возвращает указатель на QList с данными
///
QList<qint32>* CalcThread::passData() {
	return dataArray;
}
