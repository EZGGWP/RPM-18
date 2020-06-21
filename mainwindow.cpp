#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

///
/// \brief Это конструктор главного окна
/// \param parent Принимает ссылку на виджет-родитель
///
MainWindow::MainWindow(QWidget *parent)	: QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	chView = new QtCharts::QChartView();
	ui->verticalLayout->addWidget(chView);
	ui->centralwidget->setContentsMargins(10, 10, 10, 10);
	QHBoxLayout *box = new QHBoxLayout();
	QPushButton *start = new QPushButton("Start");
	QPushButton *stop = new QPushButton("Stop");
	box->addWidget(start, 1, Qt::AlignLeft);
	box->addWidget(stop, 1, Qt::AlignRight);
	ui->verticalLayout->addLayout(box);
	ui->centralwidget->setLayout(ui->verticalLayout);
	QList<qint32> *sample = new QList<qint32>();

	QRandomGenerator *gen = new QRandomGenerator();
	for (int i = 0; i < 500000; i++) {
		qint32 num = gen->bounded(-15000, 30000);;
		sample->push_back(num);
		if (i % 1000 == 0) {
		}
		*nums << num;
	}
	thread->dataArray = sample;


	chart->addSeries(serie);
	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);
	serie->attachAxis(axisX);
	serie->attachAxis(axisY);

	chView->setChart(chart);
	chView->show();
	connect(time, &QTimer::timeout, this, &MainWindow::updateData);
	connect(start, &QPushButton::clicked, this, &MainWindow::starter);
	connect(stop, &QPushButton::clicked, this, &MainWindow::close);
	thread->moveToThread(calcThread);
}

///
/// \brief Это деструктор главного окна
///
MainWindow::~MainWindow() {
	delete ui;
}

///
/// \brief Это функция, которая обновляет данные на графике
///
void MainWindow::updateData() {
	QList<qint32> *data2 = new QList<qint32>;
	data2 = thread->passData();

	QList<qint32> data(*data2);

	QList<qreal> listForNums;

	for (int i = 0; i < 500000; i += 1000) {
		qint64 temp = 0;

		for (int j = 0; j < 1000; j++) {
			temp += data.value(i+j);

		}
		temp = temp/1000;
		listForNums.push_front(temp);
	}

	QtCharts::QBarSet *nums2 = new QtCharts::QBarSet("Numbers", this);
	serie->clear();

	axisY->setMax(-15000);
	axisY->setMin(30000);
	axisX->setMax(501);
	axisX->setMin(0);

	nums2->append(listForNums);
	serie->append(nums2);

	chView->update();

	if (!thread->finished) {
		time->start(1000);
		calcThread->terminate();
	} else {
		QMessageBox::question(this, "Sotring complete.", "All data was sorted.", QMessageBox::Yes);
		time->stop();
	}
}

///
/// \brief Это слот, который запускает вычиление в отдельном потоке
///
void MainWindow::starter() {
	calcThread->start();
	connect(calcThread, &QThread::started, thread, &CalcThread::run);
	time->start(1000);
};

