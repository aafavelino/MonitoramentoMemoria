#include <dirent.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
#include <boost/algorithm/string.hpp>

#include <chrono>
#include <iterator>
#include <thread>

using namespace std;
using namespace boost;

struct processos
{
	string PID;
	string Nome;
	string tam_mem;
	string Swap;
	string Major_faults;
	string Minor_faults;

};


bool isdigit(const std::string& str) {
    return (*str.c_str() >= '0' and *str.c_str() <= '9');
}
int listaArquivos (std::string nomeDir, std::vector<std::string> &pastas) {
    DIR *dir = 0;
    struct dirent *entrada = 0;
    unsigned char isDir = 0x4;
    unsigned char isFile = 0x8;
 
    dir = opendir (nomeDir.c_str());
 
    if (dir == 0) {
        std::cerr << "Nao foi possivel abrir diretorio." << std::endl;
        exit (1);
    }
 
    //Iterar sobre o diretorio
    while (entrada = readdir (dir))
        if ((entrada->d_type == isDir) and isdigit(entrada->d_name[0])){    
                pastas.push_back(entrada->d_name);

        }
    closedir (dir);
     
    return 0;
}
void informacoes_processo(std::vector<std::string> pastas){
    std::string line, token,s;
    std::ofstream info;

    info.open("info_process.txt",std::ofstream::out | std::ofstream::trunc);

    for (int i = 0; i < pastas.size();i++){
    	const char *aux;
        std::ifstream infos("/proc/" + pastas[i] + "/stat");
        info << "DADOS DO PROCESSO "+pastas[i]+"\n";

         while(!infos.eof()){

            getline(infos,line);
            std::istringstream ss(line);
            int counter = 1;

            while(getline(ss, token, ' ')) {
 
 				if (counter == 1) {

		            	info << token <<endl;

		         }else if(counter == 2){

		         	info << token<<endl;

		         }else if(counter == 12){

		         	info <<token<<endl;

		         }else if(counter == 10){

		         	info << token<<endl;

		         }else if(counter == 24){

		         	info <<token<<endl;

		         }else if(counter == 36){

		         	info << token<<endl;

		         }
		        counter++;
		    }

    		
    	}

    	info<<"fim:"+pastas[i]<<endl;
   	}

   	info.close();
}
    


void informacoes_total(){

	std::ofstream info;
    info.open("info_total.txt");

	info << "";

	info.close();

	system("free >> info_total.txt");
	//system("pidof bash | xargs ps -o rss,sz,vsz >> info_total.txt");
}

void ler_total(){

	std::ifstream info("info_total.txt");
	std::string line;
	getline(info,line);
	cout <<	"          total(kb)   usada(kb)   livre(kb) público(kb)    cache(kb)   cache acessível(kb)"<<endl;
	while(!info.eof()){
			getline(info,line);
			std::istringstream ss(line);
        	std::string token;
        	int counter = 1;


        	while(getline(ss, token, ':')) {


        			if ((counter == 1) || (counter == 2))
		            	cout << token;
		            counter++;

		            
		            
		        
        }

        cout << endl;

	}

}
void print(vector <processos> & v)
{

	 for (size_t n = 0; n < v.size(); n++){

	 	if(strlen((v[n].Nome).c_str()) <= 18){
	 		while(strlen((v[n].Nome).c_str()) <= 18)
	 			v[n].Nome = v[n].Nome + " ";
	 	}

	 	if(strlen((v[n].PID).c_str()) <= 4){
	 		while(strlen((v[n].PID).c_str()) <= 4)
	 			v[n].PID = v[n].PID + " ";
	 	}

	 	if(strlen((v[n].Major_faults).c_str()) <= 4){
	 		while(strlen((v[n].Major_faults).c_str()) <= 4)
	 			v[n].Major_faults = v[n].Major_faults + " ";
	 	}

	 	if(strlen((v[n].Minor_faults).c_str()) <= 10){
	 		while(strlen((v[n].Minor_faults).c_str()) <= 10)
	 			v[n].Minor_faults = v[n].Minor_faults + " ";
	 	}
	 	if(strlen((v[n].tam_mem).c_str()) <= 5){
	 		while(strlen((v[n].tam_mem).c_str()) <= 5)
	 			v[n].tam_mem = v[n].tam_mem + " ";
	 	}

	 }
		        
  

  for (size_t n = 0; n < v.size(); n++){
    cout << v[ n].Nome << "              " << v[n].PID<<"                " << v[n].Major_faults << "             "<< v[n].Minor_faults<< "      "<< v[n].tam_mem<<"         "<<v[n].Swap<<endl;

}
  cout << endl;
}

void ler_processo(std::vector<std::string> pastas, std::vector<processos> &vetor){

	std::ifstream info("info_process.txt");
	std::string line;

	while(!info.eof()){
			getline(info,line);
			std::istringstream ss(line);
        	std::string token;
        	int counter = 1;

        	for (int i = 0; i < pastas.size(); ++i)
        	{
        		processos aux;

        		counter = 1;

        		if (line == "DADOS DO PROCESSO "+pastas[i]){
        			
        			while(line != "fim:"+pastas[i]){

        				getline(info,line);
        				//cout<<line<<endl;
        				if (counter  == 1){
        					
        					aux.PID = line;

        				}else if(counter == 2){
        					aux.Nome = line;

        				}else if(counter == 3){
        					
        					aux.Minor_faults = line;
        				
        				}else if(counter == 4){
        				
        					aux.Major_faults = line;
        				
        				}else if(counter == 5){
        				
        					aux.tam_mem = line;

        				}else if(counter == 6){
        					aux.Swap = line;
        				}

        				counter++;

        				
        		}

        		
        		vetor.push_back(aux);
        		
        	}



		}
	}



}
void ordenando(std::vector<processos> &vetor){
	int j;
	processos aux;


	for (int i = 0; i < vetor.size(); i++){
		for (j = i + 1; j < vetor.size(); j++){
			if(atoi((vetor[j].tam_mem).c_str()) > atoi((vetor[i].tam_mem).c_str())){
				aux = vetor[j];
				vetor[j] = vetor[i];
				vetor[i] = aux;
			}
		}

	}

}
void printN(std::vector<processos> &v, int qtd){

	 for (size_t n = 0; n < v.size(); n++){

	 	if(strlen((v[n].Nome).c_str()) <= 18){
	 		while(strlen((v[n].Nome).c_str()) <= 18)
	 			v[n].Nome = v[n].Nome + " ";
	 	}

	 	if(strlen((v[n].PID).c_str()) <= 4){
	 		while(strlen((v[n].PID).c_str()) <= 4)
	 			v[n].PID = v[n].PID + " ";
	 	}

	 	if(strlen((v[n].Major_faults).c_str()) <= 4){
	 		while(strlen((v[n].Major_faults).c_str()) <= 4)
	 			v[n].Major_faults = v[n].Major_faults + " ";
	 	}

	 	if(strlen((v[n].Minor_faults).c_str()) <= 10){
	 		while(strlen((v[n].Minor_faults).c_str()) <= 10)
	 			v[n].Minor_faults = v[n].Minor_faults + " ";
	 	}
	 	if(strlen((v[n].tam_mem).c_str()) <= 5){
	 		while(strlen((v[n].tam_mem).c_str()) <= 5)
	 			v[n].tam_mem = v[n].tam_mem + " ";
	 	}

	 }

	for (size_t n = 0; n < qtd; n++){
    cout << v[ n].Nome << "              " << v[n].PID<<"                " << v[n].Major_faults << "             "<< v[n].Minor_faults<< "      "<< v[n].tam_mem<<"         "<<v[n].Swap<<endl;

}

}



int main(int argc, char const *argv[])
{	
    std::vector<std::string> pastas;
    std::vector<processos> vetor;
    std::string opcao;	
    int qtd;

    if (argc < 2) {
        std::cerr << "Diretorio nao fornecido." << std::endl;
        exit (1);
    }

    			cin >> opcao;

			   



			    //cout << "";

			    vetor.clear();
			    remove("info_process.txt");

			    
			    //cout << "";

			if (opcao == "top"){

				 while(true){

						cout << "";

						vetor.clear();
			   		 	remove("info_process.txt");

						listaArquivos (argv[1], pastas);

						informacoes_processo(pastas);


					    cout<< "INFORMAÇÕES DA MEMÓRIA TOTAL "<< endl;
					    informacoes_total();
					    ler_total();
					    ler_processo(pastas,vetor);
					    //informacoes_processo(pastas);

					    ordenando(vetor);

					    cout<< "INFORMAÇÕES DA MEMÓRIA POR PROCESSO "<< endl;

					    cout << "Name                            PID               Major_faults      Minor_faults       Size(kb)       Swap"<<endl;
					  	cout <<"-----------------------------------------------------------------------------------------------------------"<<endl;

					  	pastas.clear();
					    print(vetor);


					    std::this_thread::sleep_for (std::chrono::milliseconds(10000000));

				}

			}else{   
			   
				listaArquivos (argv[1], pastas);

			    informacoes_processo(pastas);

			    cout << "";


		    	cin >> qtd;

			    cout<< "INFORMAÇÕES DA MEMÓRIA TOTAL "<< endl;


			     informacoes_total();
			     ler_total();
			     ler_processo(pastas,vetor);

			     ordenando(vetor);

			    cout<< "INFORMAÇÕES DA MEMÓRIA POR PROCESSO "<< endl;

			    cout << "Name                            PID               Major_faults      Minor_faults       Size(kb)       Swap"<<endl;
			  	cout <<"-----------------------------------------------------------------------------------------------------------"<<endl;


			    printN(vetor,qtd);

			    //std::this_thread::sleep_for (std::chrono::milliseconds(1000000000000));
			    
			}

		    
  

	return EXIT_SUCCESS;
}