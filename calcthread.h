#ifndef CALCTHREAD_H
#define CALCTHREAD_H
#include <QObject>

///
/// \brief Это класс CalcThread, который содержит в себе функционал сортировки пузырьком для загрузки потока
///
class CalcThread : public QObject {
	Q_OBJECT
public:
	///
	/// \brief Это конструктор класса CalcThread
	///
	CalcThread();

	///
	/// \brief Эта функция запускает сортировку
	///
	void run();

	///
	/// \brief Это QList, который содержит данные для сортировки
	///
	QList<qint32> *dataArray;

	///
	/// \brief Это поле сообщает об окончании сортировки
	///
	bool finished = false;

	///
	/// \brief Эта функция выполняет сортировку пузырьком
	///
	void bubbleSort();

public slots:
	///
	/// \brief Это слот для передачи данных в основной поток
	/// \return Возвращает указатель на QList с данными
	///
	QList<qint32>* passData();
};

#endif // CALCTHREAD_H
