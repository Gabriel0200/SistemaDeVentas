#ifndef REPORT_H
#define REPORT_H

class Report
{
public:
	Report() {
		ventas = 0;
	}
	~Report() {

	}
	int getSuma() {
		return ventas;
	}
	int ventasSuma() {
		return ++this->ventas;
	}
private:
	int ventas;
};

#endif