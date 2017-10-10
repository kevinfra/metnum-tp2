#include <iostream>
#include "matrix/Matrix.h"
#include "io/IO.h"
#include "machines/MachineFactory.h"

void print_usage() {
	std::cerr <<
			"Uso: \"./tp2 -m <method> -i <train_set> -q <test_set> -o <classif>\"\n"
			"\n"
			"donde:\n"
			"- <method>: método a ejecutar (0: kNN, 1: PCA + kNN)\n"
			"- <train_set>: archivo con datos de entrenamiento\n"
			"- <test_set>: archivo con datos de test a clasificar\n"
			"- <classif>: archivo de salida con la clasificación de"
			" los datos de test de <test_set>" << std::endl;
}

int main(int argc, char const *argv[]) {
    const char* unknown = NULL;
	parameters p = {255, NULL, NULL, NULL};
    int res = parse(argc, argv, p, &unknown);
    switch (res) {
        case MISSING_ARG:
            std::cerr << "ERROR: parametros faltantes\n" << std::endl;
            print_usage();
            break;
        case UNKNOWN_METHOD:
            std::cerr << "ERROR: metodo no reconocido \"" << unknown << "\"\n" << std::endl;
            print_usage();
            break;
        case UNKNOWN_ARG:
            std::cerr << "ERROR: parametro no reconocido \"" << unknown << "\"\n" << std::endl;
            print_usage();
            break;
        default:
            break;
    }
    if(res != OK) {
        return res;
    }

	MachineRef machine = MachineFactory::create(p);

    machine->train();
    machine->guess();

	return res;
}
