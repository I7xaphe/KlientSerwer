#ifndef _MYBIBLIO_H_
#define _MYBIBLIO_H_

struct argumenty{
	double a;
	double b;
};
typedef struct argumenty argumenty;

double dodawanie( argumenty* arg);
double odejmowanie( argumenty* arg);
double mnozenie( argumenty* arg);
double dzielenie( argumenty *arg);

#endif /*_MYBIBLIO_H_*/

