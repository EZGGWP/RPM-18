#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qchart.h"
#include "qchartview.h"
#include "qbarset.h"
#include "qbarseries.h"
#include "calcthread.h"
#include <QValueAxis>
#include <QTimer>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

///
/// \brief Это класс главного окна приложения
///
class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	///
	/// \brief Это конструктор главного окна
	/// \param parent Принимает ссылку на виджет-родитель
	///
	MainWindow(QWidget *parent = nullptr);

	///
	/// \brief Это деструктор главного окна
	///
	~MainWindow();

	///
	/// \brief Это сам график, на который будут выводится данные
	///
	QtCharts::QChart *chart = new QtCharts::QChart();

	///
	/// \brief Это представление того самого графика
	///
	QtCharts::QChartView *chView;

	///
	/// \brief Это серия - последовательность данных, которые отображаются на графике
	///
	QtCharts::QBarSeries *serie = new QtCharts::QBarSeries(this);

	///
	/// \brief Это набор данных, который вкладывается в последовательность
	///
	QtCharts::QBarSet *nums = new QtCharts::QBarSet("Numbers", this);

	///
	/// \brief Это ось абсцисс для графика
	///
	QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();

	///
	/// \brief Это ось ординат для графика
	///
	QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();

	///
	/// \brief Это функция, которая обновляет данные на графике
	///
	void updateData();
	QTimer *time = new QTimer();

	///
	/// \brief Это объект класса CalcThread, который выполняет вычисления
	///
	CalcThread *thread = new CalcThread();
	///
	/// \brief Это сам поток, в котором находится класс CaclThread и в котором происходят вычисления. Не путать с CalcThread.
	///
	QThread *calcThread = new QThread();

private:
	///
	/// \brief Этот объект содержит элементы интерфейса
	///
	Ui::MainWindow *ui;

public slots:
	///
	/// \brief Это слот, который запускает вычиление в отдельном потоке
	///
	void starter();
};
#endif // MAINWINDOW_H
